#include "Interpreter.h"


Interpreter::Interpreter(PetStage* petStage, Robot::Window *window) :
	BUILD(56), running(true)
{
	this->petStage = petStage;
	this->window = window;
	this->image = new Robot::Image();
	this->points = new Robot::Point[40];
	this->pixels = new Robot::Color[40];
	this->readSuccess = false;
	this->oneTimeNotifier = false;
	this->timeoutCount = 0;
}


Interpreter::~Interpreter(void)
{
	delete[] pixels;
	delete[] points;
	delete image;
	delete window;
}

void Interpreter::Exit()
{
	running = false;
	if (!wait(2000))
		terminate();
	running = true;
}

void Interpreter::run()
{
	while (running)
	{
		timer.start();

		// do important work here
		if (!readSuccess)
		{
			//Emit message once!
			if (!oneTimeNotifier)
			{
				emit OutputToGUI("Locating Addon", "Locating addon...");
				oneTimeNotifier = true;
			}

			if (!Locate())
			{
				timeoutCount++;
				if (timeoutCount >= 450)
					emit Stop("Addon could not be located. Stopping...");
			
				mutex.lock();
				int elapsed = timer.elapsed();
				if (33 - elapsed > 0)
					msleep(33 - elapsed);
				timer.restart();
				mutex.unlock();

				continue;
			}

			emit OutputToGUI("Running", "Addon located.");
			readSuccess = true;
			timeoutCount = 0;
		}

		//Addon location already known, grab pixels.	
		Robot::Screen::GrabScreen(*window, image, addonBar1);
		for (int i=0; i < 20; i+=1)
			pixels[i] = image->GetPixel(points[i]);

		Robot::Screen::GrabScreen(*window, image, addonBar2);
		for (int i=20; i < 40; i+=1)
			pixels[i] = image->GetPixel(points[i]);

		//Run checksums again to be sure it didn't move.
		if (pixels[0].B != BUILD || pixels[11].R != pixels[9].B || pixels[11].G != pixels[2].R || pixels[11].B != pixels[6].G
				|| pixels[19].R != pixels[16].G || pixels[19].G != pixels[12].B || pixels[19].B != pixels[14].R
				|| pixels[22].R != BUILD || pixels[22].G != pixels[20].R || pixels[22].B != pixels[21].G
				|| pixels[28].R != pixels[3].G || pixels[28].G != BUILD || pixels[28].B != pixels[12].R
				|| pixels[36].R != BUILD || pixels[36].G != pixels[0].R || pixels[36].B != pixels[9].G)
		{
			readSuccess = false;
			oneTimeNotifier = false;
			continue;
		}

		//Lock the access so only this thread can access petStage to update it.
		mutex.lock();

		//Setup pet teams if we are now initialized.
		if ((!petStage->Initialized() && (pixels[0].G & 64) != 0))
		{
			int myPetSpecies1 = ((((pixels[1].R << 3) + (pixels[1].G >> 5))) & 2047);
			if (myPetSpecies1 != 0)
			{
				petStage->GetPetTeam(1)->AddPet(myPetSpecies1, (pixels[1].G & 31), ((pixels[1].B >> 5) & 7),
												((((pixels[1].B & 31) << 1) + ((pixels[2].R >> 7) & 1)) & 63));

				petStage->GetPetTeam(1)->GetPet(1)->AddAbility(((pixels[2].R & 1) != 0),
																(((pixels[2].R >> 5) & 1) + 1),
																((pixels[2].R >> 1) & 15));

				petStage->GetPetTeam(1)->GetPet(1)->AddAbility(((pixels[2].R & 64) != 0),
																(((pixels[2].G >> 7) & 1) + 1),
																((pixels[2].G >> 3) & 15));

				petStage->GetPetTeam(1)->GetPet(1)->AddAbility(((pixels[2].G & 4) != 0),
																(((pixels[2].G >> 1) & 1) + 1),
																(((pixels[2].G << 3) + (pixels[2].B >> 5)) & 15));
			}

			int myPetSpecies2 = ((((pixels[3].R << 3) + (pixels[3].G >> 5))) & 2047);
			if (myPetSpecies2 != 0)
			{
				petStage->GetPetTeam(1)->AddPet(myPetSpecies2, (pixels[3].G & 31), ((pixels[3].B >> 5) & 7),
												((((pixels[3].B & 31) << 1) + ((pixels[4].R >> 7) & 1)) & 63));

				petStage->GetPetTeam(1)->GetPet(2)->AddAbility(((pixels[4].R & 1) != 0),
																(((pixels[4].R >> 5) & 1) + 1),
																((pixels[4].R >> 1) & 15));

				petStage->GetPetTeam(1)->GetPet(2)->AddAbility(((pixels[4].R & 64) != 0),
																(((pixels[4].G >> 7) & 1) + 1),
																((pixels[4].G >> 3) & 15));

				petStage->GetPetTeam(1)->GetPet(2)->AddAbility(((pixels[4].G & 4) != 0),
																(((pixels[4].G >> 1) & 1) + 1),
																(((pixels[4].G << 3) + (pixels[4].B >> 5)) & 15));
			}

			int myPetSpecies3 = ((((pixels[5].R << 3) + (pixels[5].G >> 5))) & 2047);
			if (myPetSpecies3 != 0)
			{
				petStage->GetPetTeam(1)->AddPet(myPetSpecies3, (pixels[5].G & 31), ((pixels[5].B >> 5) & 7),
												((((pixels[5].B & 31) << 1) + ((pixels[6].R >> 7) & 1)) & 63));

				petStage->GetPetTeam(1)->GetPet(3)->AddAbility(((pixels[6].R & 1) != 0),
																(((pixels[6].R >> 5) & 1) + 1),
																((pixels[6].R >> 1) & 15));

				petStage->GetPetTeam(1)->GetPet(3)->AddAbility(((pixels[6].R & 64) != 0),
																(((pixels[6].G >> 7) & 1) + 1),
																((pixels[6].G >> 3) & 15));

				petStage->GetPetTeam(1)->GetPet(3)->AddAbility(((pixels[6].G & 4) != 0),
																(((pixels[6].G >> 1) & 1) + 1),
																(((pixels[6].G << 3) + (pixels[6].B >> 5)) & 15));
			}

			int enemyPetSpecies1 = ((((pixels[7].R << 3) + (pixels[7].G >> 5))) & 2047);
			if (enemyPetSpecies1 != 0)
			{
				petStage->GetPetTeam(2)->AddPet(enemyPetSpecies1, (pixels[7].G & 31), ((pixels[7].B >> 5) & 7),
												((((pixels[7].B & 31) << 1) + ((pixels[8].R >> 7) & 1)) & 63));

				petStage->GetPetTeam(2)->GetPet(1)->AddAbility(((pixels[8].R & 1) != 0),
																(((pixels[8].R >> 5) & 1) + 1),
																((pixels[8].R >> 1) & 15));

				petStage->GetPetTeam(2)->GetPet(1)->AddAbility(((pixels[8].R & 64) != 0),
																(((pixels[8].G >> 7) & 1) + 1),
																((pixels[8].G >> 3) & 15));

				petStage->GetPetTeam(2)->GetPet(1)->AddAbility(((pixels[8].G & 4) != 0),
																(((pixels[8].G >> 1) & 1) + 1),
																(((pixels[8].G << 3) + (pixels[8].B >> 5)) & 15));
			}

			int enemyPetSpecies2 = ((((pixels[9].R << 3) + (pixels[9].G >> 5))) & 2047);
			if (enemyPetSpecies2 != 0)
			{
				petStage->GetPetTeam(2)->AddPet(enemyPetSpecies2, (pixels[9].G & 31), ((pixels[9].B >> 5) & 7),
												((((pixels[9].B & 31) << 1) + ((pixels[10].R >> 7) & 1)) & 63));

				petStage->GetPetTeam(2)->GetPet(2)->AddAbility(((pixels[10].R & 1) != 0),
																(((pixels[10].R >> 5) & 1) + 1),
																((pixels[10].R >> 1) & 15));

				petStage->GetPetTeam(2)->GetPet(2)->AddAbility(((pixels[10].R & 64) != 0),
																(((pixels[10].G >> 7) & 1) + 1),
																((pixels[10].G >> 3) & 15));

				petStage->GetPetTeam(2)->GetPet(2)->AddAbility(((pixels[10].G & 4) != 0),
																(((pixels[10].G >> 1) & 1) + 1),
																(((pixels[10].G << 3) + (pixels[10].B >> 5)) & 15));
			}

			int enemyPetSpecies3 = ((((pixels[12].R << 3) + (pixels[12].G >> 5))) & 2047);
			if (enemyPetSpecies3 != 0)
			{
				petStage->GetPetTeam(2)->AddPet(enemyPetSpecies3, (pixels[12].G & 31), ((pixels[12].B >> 5) & 7),
												((((pixels[12].B & 31) << 1) + ((pixels[13].R >> 7) & 1)) & 63));

				petStage->GetPetTeam(2)->GetPet(3)->AddAbility(((pixels[13].R & 1) != 0),
																(((pixels[13].R >> 5) & 1) + 1),
																((pixels[13].R >> 1) & 15));

				petStage->GetPetTeam(2)->GetPet(3)->AddAbility(((pixels[13].R & 64) != 0),
																(((pixels[13].G >> 7) & 1) + 1),
																((pixels[13].G >> 3) & 15));

				petStage->GetPetTeam(2)->GetPet(3)->AddAbility(((pixels[13].G & 4) != 0),
																(((pixels[13].G >> 1) & 1) + 1),
																(((pixels[13].G << 3) + (pixels[13].B >> 5)) & 15));
			}			
		}

		//When the game has initialized.
		if (petStage->Initialized())
		{
			//Update health pools.
			int healthBlock1 = (pixels[14].R << 16) + (pixels[14].G << 8) + pixels[14].B;
			int healthBlock2 = (pixels[15].R << 16) + (pixels[15].G << 8) + pixels[15].B;
			int healthBlock3 = (pixels[16].R << 16) + (pixels[16].G << 8) + pixels[16].B;
			petStage->GetPetTeam(1)->GetPet(1)->SetHealth(((healthBlock1 >> 12) & 4095));
			petStage->GetPetTeam(1)->GetPet(2)->SetHealth((healthBlock1 & 4095));
			petStage->GetPetTeam(1)->GetPet(3)->SetHealth(((healthBlock2 >> 12) & 4095));
			petStage->GetPetTeam(2)->GetPet(1)->SetHealth((healthBlock2 & 4095));
			petStage->GetPetTeam(2)->GetPet(2)->SetHealth(((healthBlock3 >> 12) & 4095));
			petStage->GetPetTeam(2)->GetPet(3)->SetHealth((healthBlock3 & 4095));

			//Update ability CDs.

			//Update auras on pets.
			//Delete all auras.
		}

		//Send a signal to AI if we...
		/*if ((!petStage->SelectAbility() && (pixels[0].G & 16) != 0)			//Need to select ability.
				|| (!petStage->SelectPet() && (pixels[0].G & 32) != 0)		//Need to select pet.
				|| (petStage->QueueState() != 3 && (pixels[0].R & 3) == 3)	//Need to accept queue.
				|| (petStage->QueueState() == 0 && (pixels[0].R & 3) == 0))	//Need to queue.
			emit RunAI();*/

		//Update petStage.
		petStage->InPetBattle((pixels[0].R & 128) != 0);
		petStage->TeamIsAlive((pixels[0].R & 64) != 0);
		petStage->PlayerIsGhost((pixels[0].R & 32) != 0);
		petStage->PlayerIsDead((pixels[0].R & 16) != 0);
		petStage->PlayerAffectingCombat((pixels[0].R & 8) != 0);
		petStage->QueueEnabled((pixels[0].R & 4) != 0);
		petStage->QueueState((pixels[0].R & 3) != 0);
		petStage->CanAccept((pixels[0].G & 128) != 0);
		petStage->Initialized((pixels[0].G & 64) != 0);
		petStage->SelectPet((pixels[0].G & 32) != 0);
		petStage->SelectAbility((pixels[0].G & 16) != 0);
		petStage->WonLastBattle((pixels[0].G & 8) != 0);

		//Stop if conditions are met.
		if (!petStage->InPetBattle())
		{
			if (!petStage->TeamIsAlive()) { emit Stop("A pet on your team has fainted. Stopping..."); continue; }
			if (petStage->PlayerIsGhost()) { emit Stop("Cannot queue while a ghost. Stopping..."); continue; }
			if (petStage->PlayerIsDead()) { emit Stop("Cannot queue while dead. Stopping..."); continue; }
			if (petStage->PlayerAffectingCombat()) { emit Stop("Cannot queue while in combat. Stopping..."); continue; }
			if (!petStage->QueueEnabled()) { emit Stop("Queue system not enabled. Stopping..."); continue; }
		}

		//Stop timer, sleep if needed and then reset the timer.
		int elapsed = timer.elapsed();
		if (33 - elapsed > 0)
			msleep(33 - elapsed);
		timer.restart();
		mutex.unlock();
	}
}

bool Interpreter::Locate()
{
	Robot::Color border = Robot::Color(16, 8, 12);
	Robot::Screen::GrabScreen(*window, image); //Grab an image of the screen.

	for (int y=0; y < image->GetHeight(); y+=4)
		for (int x=0; x < image->GetWidth(); x+=248)
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
						if (image->GetPixel(x1 - 1, y1) == border)
						{
							a = true;
							x1 -= 1;
						}
						else
							break;

					while(true)
						if (image->GetPixel(x1, y1 - 1) == border)
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
						if (image->GetPixel(x2 + 1, y1) == border)
						{
							a = true;
							x2 += 1;
						}
						else
							break;

					while(true)
						if (image->GetPixel(x1, y2 + 1) == border)
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

				for (int i=0; i < 20; i+=1)
				{
					points[i].X = length * i;
					points[i+20].X = length * i;
				}

				//Verify the results.
				Robot::Color p01 = image->GetPixel(x1 + start + points[0].X, y1 + center); // Uses BUILD; Check for p37
				Robot::Color p03 = image->GetPixel(x1 + start + points[2].X, y1 + center); //Check for p12
				Robot::Color p04 = image->GetPixel(x1 + start + points[3].X, y1 + center); //Check for p29
				Robot::Color p07 = image->GetPixel(x1 + start + points[6].X, y1 + center); //Check for p12
				Robot::Color p10 = image->GetPixel(x1 + start + points[9].X, y1 + center); //Check for p12; Check for p37
				Robot::Color p12 = image->GetPixel(x1 + start + points[11].X, y1 + center); //Uses p03, p07 and p10
				Robot::Color p13 = image->GetPixel(x1 + start + points[12].X, y1 + center); //Check for p20 and p29
				Robot::Color p15 = image->GetPixel(x1 + start + points[14].X, y1 + center); //Check for p20
				Robot::Color p17 = image->GetPixel(x1 + start + points[16].X, y1 + center); //Check for p20
				Robot::Color p20 = image->GetPixel(x1 + start + points[19].X, y1 + center); //Uses p13, p15 and p17
				Robot::Color p21 = image->GetPixel(x1 + start + points[20].X, y1 + 34 + center); //Check for p23
				Robot::Color p22 = image->GetPixel(x1 + start + points[21].X, y1 + 34 + center); //Check for p23
				Robot::Color p23 = image->GetPixel(x1 + start + points[22].X, y1 + 34 + center); //Uses p21, p22 and BUILD
				Robot::Color p29 = image->GetPixel(x1 + start + points[28].X, y1 + 34 + center); //Uses p04, BUILD, p13
				Robot::Color p37 = image->GetPixel(x1 + start + points[36].X, y1 + 34 + center);

				if (p01.B != BUILD || p12.R != p10.B || p12.G != p03.R || p12.B != p07.G
						|| p20.R != p17.G || p20.G != p13.B || p20.B != p15.R
						|| p23.R != BUILD || p23.G != p21.R || p23.B != p22.G
						|| p29.R != p04.G || p29.G != BUILD || p29.B != p13.R
						|| p37.R != BUILD || p37.G != p01.R || p37.B != p10.G)
					continue;

				//Update addon position.
				addonBar1.X = x1 + start;
				addonBar1.Y = y1 + center;
				addonBar1.W = points[19].X + 1;
				addonBar1.H = 1;

				addonBar2 = addonBar1;
				addonBar2.Y = y1 + 34 + center; //34 is the pixel offset.

				//All done.
				return true;
			}
		}
	return false;
}
