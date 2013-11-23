#include "Interpreter.h"

//Constructor
Interpreter::Interpreter(PetStage* petStage, AI* ai, Robot::Window *window) :
	build(56), running(true), queueEnabled(false), readSuccess(false), oneTimeNotifier(false)
{
	this->petStage = petStage;
	this->ai = ai;
	this->window = window;
	this->image = new Robot::Image();
	this->points = new Robot::Point[40];
	this->pixels = new Robot::Color[40];
	this->timeoutCount = 0;
	this->signalEmitted = false;
	this->threadLocked = false;

	//Load preferences.
	this->LoadPreferences();
}

//Destructor
Interpreter::~Interpreter(void)
{
	delete[] this->pixels;
	delete[] this->points;
	delete this->image;
}

//Exits the loop.
void Interpreter::Exit()
{
	//Unlock the thread.
	if ((this->readSuccess && !this->oneTimeNotifier) || !this->petStage->TeamIsAlive())
		this->mutex.unlock();

	this->running = false;
	this->timeoutCount = 0;
	if (!wait(2000))
		this->terminate();

	this->petStage->Reinitialize();		//Thread activity has stopped; reinitialize the stage.
}

//Override function from QThread to run out own loop.
void Interpreter::run()
{
	//In case anything was changed prior to running.
	this->LoadPreferences();

	//Make AI reload its settings incase something changed.
	this->ai->LoadPreferences();

	//Have the AI load its QML resources.
	this->ai->LoadQMLResources();

	//Update bools in case we run it again.
	this->running = true;
	this->readSuccess = false;
	this->oneTimeNotifier = false;
	this->signalEmitted = false;
	this->threadLocked = false;

	while (this->running)
	{
		//Start the timer to limit number of updaters per second.
		this->timer.start();

		if (!this->readSuccess)
		{
			//Emit message once!
			if (!this->oneTimeNotifier)
			{
				emit OutputToGUI("Locating Addon", "Locating addon...");
				this->oneTimeNotifier = true;
			}

			if (!this->Locate())
			{
				this->timeoutCount += 1;
				if (this->timeoutCount >= 450)
					emit Stop("Addon could not be located. Stopping...");
			
				this->mutex.lock();
				int elapsed = timer.elapsed();
				if (33 - elapsed > 0)
					this->msleep(33 - elapsed);
				this->timer.restart();
				this->mutex.unlock();

				continue;
			}

			emit OutputToGUI("Waiting For Battle", "Addon located.");
			this->readSuccess = true;
			this->timeoutCount = 0;
		}

		//Addon location already known, grab pixels.	
		Robot::Screen::GrabScreen(*window, image, addonBar1);
		for (quint8 i=0; i < 20; i+=1)
			this->pixels[i] = image->GetPixel(points[i]);

		Robot::Screen::GrabScreen(*window, image, addonBar2);
		for (quint8 i=20; i < 40; i+=1)
			this->pixels[i] = image->GetPixel(points[i]);

		//Run checksums again to be sure it didn't move.
		if (this->pixels[0].B != build || this->pixels[11].R != this->pixels[9].B || this->pixels[11].G != this->pixels[2].R || this->pixels[11].B != this->pixels[6].G
				|| this->pixels[19].R != this->pixels[16].G || this->pixels[19].G != this->pixels[12].B || this->pixels[19].B != this->pixels[14].R
				|| this->pixels[22].R != build || this->pixels[22].G != this->pixels[20].R || this->pixels[22].B != this->pixels[21].G
				|| this->pixels[28].R != this->pixels[3].G || this->pixels[28].G != build || this->pixels[28].B != this->pixels[12].R
				|| this->pixels[36].R != build || this->pixels[36].G != this->pixels[0].R || this->pixels[36].B != this->pixels[9].G)
		{
			this->readSuccess = false;
			this->oneTimeNotifier = false;
			continue;
		}

		//Lock the access so only this thread can access petStage to update it.
		this->mutex.lock();
		this->threadLocked = true;

		//Setup pet teams if we are now initialized and inform the user of the opponent's pets.
		if ((!this->petStage->Initialized() && (this->pixels[0].G & 64) != 0))
		{
			//Setup up teams.
			this->SetupPetTeams();

			//Create QString for the opponent's teams' pets.
			QString teamComp = "Opponent's Team: " + this->petStage->GetTeam(2)->GetPet(1)->GetName();
			if (this->petStage->GetTeam(2)->GetNumPets() > 1)
				teamComp += ", " + this->petStage->GetTeam(2)->GetPet(2)->GetName();
			if (this->petStage->GetTeam(2)->GetNumPets() > 2)
				teamComp += ", " + this->petStage->GetTeam(2)->GetPet(3)->GetName();
			teamComp += ".";

			//Emit the QString to the GUI.
			emit OutputToGUI(teamComp);
		}

		//Update the stage info if we need to make a move.
		if ((!this->petStage->SelectAbility() && (this->pixels[0].G & 16) != 0) || (!this->petStage->SelectPet() && (this->pixels[0].G & 32) != 0))
		{
			//Temporary delay to try and allow everything to catch up.
			//msleep(2000);

			//Update health pools.
			this->UpdateHealthPools();

			//Update abilities and CDs as well as the active pet for each team.
			this->UpdateAbilities();

			//Update auras on pets.
			this->UpdateAuras();

			//Inform the user we are now selecting a move.
			emit this->OutputToGUI("Selecting Ability", "");

			//Call AI and have it determine our next move.
			this->ai->Run(this->petStage->Initialized() || (this->pixels[0].G & 64) != 0);

			//Inform the user we are now selecting a move.
			emit OutputToGUI("Round Playback", "");

			//Delete all auras.
			for (quint8 i=0; i < 3; i+=1)
				for (quint8 j=0; j < this->petStage->GetTeam(i)->GetNumPets()+1; j+=1)
					this->petStage->GetTeam(i)->GetPet(j)->RemoveAuras();
		}
		else if (this->petStage->InPetBattle() && ((this->pixels[0].R & 128) == 0))
		{
			//Update states to get ensure smooth process.
			this->UpdateStates();

			//Inform us of who won.
			if (this->petStage->WonLastBattle())
				emit OutputToGUI("Victory!");
			else
				emit OutputToGUI("You lose.");
			
			//Record data.
			emit OutputToGUI("Recording Results", "Recording data...");
			QString outputRecord = Recorder::RecordBattle(this->petStage);
			if (petStage->IsPvPBattle())
				Recorder::RecordPets(this->petStage);
			emit OutputToGUI(outputRecord);
			//TODO: Record pet info.
			emit OutputToGUI("Recording complete.");

			this->petStage->Reinitialize();			//We've just left a pet battle so let's reset the stage.

			emit OutputToGUI("Waiting For Battle", "");
		}
		else if (queueEnabled && this->petStage->QueueState() != 3 && (this->pixels[0].R & 3) == 3)
			this->ai->AcceptQueue();
		else if (queueEnabled && !this->petStage->InPetBattle() && this->petStage->QueueState() == 0 && (this->pixels[0].R & 3) == 0)
			this->ai->QueueUp();

		//Update petStage.
		this->UpdateStates();

		//Stop if conditions are met.
		if (!this->petStage->InPetBattle())
		{
			if (!this->petStage->TeamIsAlive() && !signalEmitted) { emit Stop("A pet on your team has fainted. Stopping..."); signalEmitted = true; continue; }
			if (this->petStage->PlayerIsGhost() && !signalEmitted) { emit Stop("Cannot queue while a ghost. Stopping..."); signalEmitted = true; continue; }
			if (this->petStage->PlayerIsDead() && !signalEmitted) { emit Stop("Cannot queue while dead. Stopping..."); signalEmitted = true; continue; }
			if (this->petStage->PlayerAffectingCombat() && !signalEmitted) { emit Stop("Cannot queue while in combat. Stopping..."); signalEmitted = true; continue; }
			if (!this->petStage->QueueEnabled() && !signalEmitted) { emit Stop("Queue system not enabled. Stopping..."); signalEmitted = true; continue; }

			if (!queueEnabled) emit OutputToGUI("Waiting For Battle", "");
		}

		//Stop timer, sleep if needed and then reset the timer.
		int elapsed = timer.elapsed();
		if (33 - elapsed > 0)
			msleep(33 - elapsed);
		timer.restart();
		this->mutex.unlock();
		this->threadLocked = false;
	}

	if (!this->running)
		emit OutputToGUI("Not Running", "");
}

//Load preferences for main window.
void Interpreter::LoadPreferences()
{
	//Grab QSettings.
	QSettings setting("Preferences.ini", QSettings::IniFormat);

	//Open Options group.
	setting.beginGroup("Options");

	//Fetch Aero preferences.
	this->aeroDisabled = !setting.value("DisableAero", false).toBool();

	//Fetch Queue preferences.
	this->queueEnabled = setting.value("PvPEnabled", false).toBool();

	//Close Options group.
	setting.endGroup();
}

//Locates the addon in the game.
bool Interpreter::Locate()
{
	Robot::Color border = Robot::Color(16, 8, 12);
	Robot::Screen::GrabScreen(*(this->window), this->image); //Grab an image of the screen.

	for (int y=0; y < this->image->GetHeight(); y+=4)
		for (int x=0; x < this->image->GetWidth(); x+=248)
		{
			//Pixel is color of border
			if (image->GetPixel(x, y) == border)
			{
				int x1, x2, y1, y2;
				x1 = x2 = x;
				y1 = y2 = y;

				//Find top left.
				bool a, b;
				a = b = true;
				while (a || b)
				{
					a = b = false;

					while(true)
						if (this->image->GetPixel(x1 - 1, y1) == border)
						{
							a = true;
							x1 -= 1;
						}
						else
							break;

					while(true)
						if (this->image->GetPixel(x1, y1 - 1) == border)
						{
							b = true;
							y1 -= 1;
						}
						else
							break;
				}

				//Find bottom right.
				a = b = true;
				while (a || b)
				{
					a = b = false;

					while(true)
						if (this->image->GetPixel(x2 + 1, y1) == border)
						{
							a = true;
							x2 += 1;
						}
						else
							break;

					while(true)
						if (this->image->GetPixel(x1, y2 + 1) == border)
						{
							b = true;
							y2 += 1;
						}
						else
							break;
				}

				//Computer width and height.
				float w = x2 - x1;
				float h = y2 - y1;

				//Check dimensions.
				if (w < 170 || h < 12 || h * 10 > w)
					continue;

				//Locate the points.
				float center = h / 2;
				float start = 16 * (w / 450);
				float length = 22 * (w / 450);

				for (quint8 i=0; i < 20; i+=1)
				{
					this->points[i].X = length * i;
					this->points[i+20].X = length * i;
				}

				//Verify the results.
				Robot::Color p01 = this->image->GetPixel(x1 + start + points[0].X, y1 + center); // Uses build; Check for p37
				Robot::Color p03 = this->image->GetPixel(x1 + start + points[2].X, y1 + center); //Check for p12
				Robot::Color p04 = this->image->GetPixel(x1 + start + points[3].X, y1 + center); //Check for p29
				Robot::Color p07 = this->image->GetPixel(x1 + start + points[6].X, y1 + center); //Check for p12
				Robot::Color p10 = this->image->GetPixel(x1 + start + points[9].X, y1 + center); //Check for p12; Check for p37
				Robot::Color p12 = this->image->GetPixel(x1 + start + points[11].X, y1 + center); //Uses p03, p07 and p10
				Robot::Color p13 = this->image->GetPixel(x1 + start + points[12].X, y1 + center); //Check for p20 and p29
				Robot::Color p15 = this->image->GetPixel(x1 + start + points[14].X, y1 + center); //Check for p20
				Robot::Color p17 = this->image->GetPixel(x1 + start + points[16].X, y1 + center); //Check for p20
				Robot::Color p20 = this->image->GetPixel(x1 + start + points[19].X, y1 + center); //Uses p13, p15 and p17
				Robot::Color p21 = this->image->GetPixel(x1 + start + points[20].X, y1 + 34 + center); //Check for p23
				Robot::Color p22 = this->image->GetPixel(x1 + start + points[21].X, y1 + 34 + center); //Check for p23
				Robot::Color p23 = this->image->GetPixel(x1 + start + points[22].X, y1 + 34 + center); //Uses p21, p22 and build
				Robot::Color p29 = this->image->GetPixel(x1 + start + points[28].X, y1 + 34 + center); //Uses p04, build, p13
				Robot::Color p37 = this->image->GetPixel(x1 + start + points[36].X, y1 + 34 + center);

				if (p01.B != build || p12.R != p10.B || p12.G != p03.R || p12.B != p07.G
						|| p20.R != p17.G || p20.G != p13.B || p20.B != p15.R
						|| p23.R != build || p23.G != p21.R || p23.B != p22.G
						|| p29.R != p04.G || p29.G != build || p29.B != p13.R
						|| p37.R != build || p37.G != p01.R || p37.B != p10.G)
					continue;

				//Update addon position.
				this->addonBar1.X = x1 + start;
				this->addonBar1.Y = y1 + center;
				this->addonBar1.W = points[19].X + 1;
				this->addonBar1.H = 1;

				this->addonBar2 = addonBar1;
				this->addonBar2.Y = y1 + 34 + center; //34 is the pixel offset.

				//All done.
				return true;
			}
		}
	return false;
}

//Sets up pet teams after initializing.
void Interpreter::SetupPetTeams()
{
	bool isWildBattle = ((this->pixels[0].G & 4) != 0);					//Opponent is a wild pet.
	bool isPlayerNPC = ((this->pixels[0].G & 2) != 0);					//Opponent is NPC trainer.
	this->petStage->IsPvPBattle(!isWildBattle && !isPlayerNPC);			//Set PvP flag.

	quint8 pixelCounter = 1;								//Used to determine what pixel block to look at.
	for (quint8 i=1; i < 3; i+=1)
		for (quint8 j=1; j < 6; j+=2)
		{
			//Get the species id and continue if it is valid.
			quint16 species = ((((this->pixels[pixelCounter].R << 3) + (this->pixels[pixelCounter].G >> 5))) & 2047);
			if (species != 0)
			{
				//Add the pet to the team.
				this->petStage->GetTeam(i)->AddPet(species, (this->pixels[pixelCounter].G & 31), ((this->pixels[pixelCounter].B >> 5) & 7),
												((((this->pixels[pixelCounter].B & 31) << 1) + ((this->pixels[pixelCounter+1].R >> 7) & 1)) & 63));

				//Every pet has at least one ability.
				this->petStage->GetTeam(i)->GetPet(((j-1)/2)+1)->AddAbility(((this->pixels[pixelCounter+1].R & 1) != 0),
																		this->petStage->IsPvPBattle(),
																		(((this->pixels[pixelCounter+1].R >> 5) & 1) + 1),
																		((this->pixels[pixelCounter+1].R >> 1) & 15));

				//Check if the pet is able to have a second ability.
				if (this->petStage->GetTeam(i)->GetPet(((j-1)/2)+1)->GetLevel() >= 2 || (isPlayerNPC && i==2))
					this->petStage->GetTeam(i)->GetPet(((j-1)/2)+1)->AddAbility(((this->pixels[pixelCounter+1].R & 64) != 0),
																			this->petStage->IsPvPBattle(),
																			(((this->pixels[pixelCounter+1].G >> 7) & 1) + 1),
																			((this->pixels[pixelCounter+1].G >> 3) & 15));

				//Check if the pet is able to have a third ability.
				if (this->petStage->GetTeam(i)->GetPet(((j-1)/2)+1)->GetLevel() >= 4 || (isPlayerNPC && i==2))
					this->petStage->GetTeam(i)->GetPet(((j-1)/2)+1)->AddAbility(((this->pixels[pixelCounter+1].G & 4) != 0),
																			this->petStage->IsPvPBattle(),
																			(((this->pixels[pixelCounter+1].G >> 1) & 1) + 1),
																			(((this->pixels[pixelCounter+1].G << 3) + (this->pixels[pixelCounter+1].B >> 5)) & 15));

				//Check if the current pet is the active pet of the team.
				if (((this->pixels[pixelCounter+1].B & 16) != 0))
				{
					this->petStage->GetTeam(i)->SetActivePet(((j-1)/2)+1);

					//Get current action and rounds remaining on it.
					if (i == 2)
					{
						this->petStage->GetTeam(i)->GetActivePet()->GetCurrentAction()->SetAction((PetAction::Action)((this->pixels[pixelCounter+1].B >> 2) & 3));
						this->petStage->GetTeam(i)->GetActivePet()->GetCurrentAction()->SetRoundsRemaining((this->pixels[pixelCounter+1].B & 3));
					}
				}
			}

			pixelCounter += 2;			//Increment pixel counter.

			//Skip over checksum pixel.
			if (pixelCounter == 11)
				pixelCounter += 1;
		}
}

//Updates the health pools of all pets.
void Interpreter::UpdateHealthPools()
{
	quint32 healthBlock[] = {(this->pixels[14].R << 16) + (this->pixels[14].G << 8) + this->pixels[14].B,
							(this->pixels[15].R << 16) + (this->pixels[15].G << 8) + this->pixels[15].B,
							(this->pixels[16].R << 16) + (this->pixels[16].G << 8) + this->pixels[16].B};

	quint16 currentHealth[2][3] = {{((healthBlock[0] >> 12) & 4095), (healthBlock[0] & 4095), ((healthBlock[1] >> 12) & 4095)},
									{(healthBlock[1] & 4095), ((healthBlock[2] >> 12) & 4095), (healthBlock[2] & 4095)}};

	for (quint8 i=1; i < 3; i+=1)
		for (quint8 j=i; j < this->petStage->GetTeam(i)->GetNumPets()+1; j+=1)
				this->petStage->GetTeam(i)->GetPet(j)->SetHealth(currentHealth[i-1][j-1]);
}

//Updates all the pets' abilities and each team's active pet.
void Interpreter::UpdateAbilities()
{
	quint8 pixelCounter = 2;			//Used to determine what pixel block to look at.
	for (quint8 i=1; i < 3; i+=1)
		for (quint8 j=1; j < this->petStage->GetTeam(i)->GetNumPets()+1; j+=1)
		{
			this->petStage->GetTeam(i)->GetPet(j)->GetAbility(1)->SetCooldown(((this->pixels[pixelCounter].R >> 1) & 15));
			if (this->petStage->GetTeam(i)->GetPet(j)->GetNumAbilities() >= 2)
				this->petStage->GetTeam(i)->GetPet(j)->GetAbility(2)->SetCooldown(((this->pixels[pixelCounter].G >> 3) & 15));
			if (this->petStage->GetTeam(i)->GetPet(j)->GetNumAbilities() == 3)
				this->petStage->GetTeam(i)->GetPet(j)->GetAbility(3)->SetCooldown((((this->pixels[pixelCounter].G << 3) + (this->pixels[pixelCounter].B >> 5)) & 15));

			//Check if the current pet is the active pet of the team.
			if (((this->pixels[pixelCounter].B & 16) != 0))
			{
				this->petStage->GetTeam(i)->SetActivePet(j);

				//Get current action and rounds remaining on it.
				if (i == 2)
				{
					this->petStage->GetTeam(i)->GetActivePet()->GetCurrentAction()->SetAction((PetAction::Action)((this->pixels[pixelCounter].B >> 2) & 3));
					this->petStage->GetTeam(i)->GetActivePet()->GetCurrentAction()->SetRoundsRemaining((this->pixels[pixelCounter].B & 3));
				}
			}

			pixelCounter += 2;			//Increment pixel counter.

			//Skip over checksum pixel.
			if (pixelCounter == 12)
				pixelCounter += 1;
		}
}

//Updates all the auras in the pet battle.
void Interpreter::UpdateAuras()
{
	for (quint8 i=17; i < 40; i+=1)
	{
		//i is a checksum box and should be ignored.
		if (i == 19 || i == 22 || i == 28 || i == 36)
			continue;

		quint16 auraId = (this->pixels[i].G << 4) + (this->pixels[i].B >> 4);
		if (auraId != 0)
			this->petStage->GetTeam((this->pixels[i].R >> 6))->GetPet(((this->pixels[i].R >> 4) & 3))->AddAura(auraId, (this->pixels[i].R & 15), false);
		else
			break;
	}
}

//Update the states of petStage.
void Interpreter::UpdateStates()
{
	this->petStage->InPetBattle((this->pixels[0].R & 128) != 0);
	this->petStage->TeamIsAlive((this->pixels[0].R & 64) != 0);
	this->petStage->PlayerIsGhost((this->pixels[0].R & 32) != 0);
	this->petStage->PlayerIsDead((this->pixels[0].R & 16) != 0);
	this->petStage->PlayerAffectingCombat((this->pixels[0].R & 8) != 0);
	this->petStage->QueueEnabled((this->pixels[0].R & 4) != 0);
	this->petStage->QueueState((this->pixels[0].R & 3) != 0);
	this->petStage->CanAccept((this->pixels[0].G & 128) != 0);
	this->petStage->Initialized((this->pixels[0].G & 64) != 0);
	this->petStage->SelectPet((this->pixels[0].G & 32) != 0);
	this->petStage->SelectAbility((this->pixels[0].G & 16) != 0);
	this->petStage->WonLastBattle((this->pixels[0].G & 8) != 0);
}
