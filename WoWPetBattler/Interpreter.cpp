#include "Interpreter.h"

Interpreter::Interpreter(QObject *parent) :
  QObject(parent), /*stopped(false),*/ BUILD(56), running(false)
{
	
}

Interpreter::Interpreter(PetStage *petStage, Robot::Window *window) :
	/*stopped(false),*/ BUILD(56), running(false)
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

Interpreter::~Interpreter()
{
	delete[] pixels;
	delete[] points;
	delete image;
	delete window;
	delete petStage;
}

void Interpreter::Start()
{
	Robot::Screen::EnableAero(false);
	//stopped = false;
	running = true;
	//emit running;
	emit OutputToGUI("", "Starting...");
	//Testing();
	Interpret();
}

void Interpreter::Stop()
{
	Robot::Screen::EnableAero(true);
	//stopped = true;
	running = false;
	//emit stopped;
	emit OutputToGUI("Not Running", "Stopped.");
}

void Interpreter::Interpret()
{
	//if (!running || stopped) return;
	if (!running) return;

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
				emit StopTimeout("Addon could not be located. Stopping...");
			
			mutex.lock();
			int elapsed = timer.elapsed();
			if (33 - elapsed > 0)
				waitCondition.wait(&mutex, 33 - elapsed);
			timer.restart();
			mutex.unlock();

			qDebug() << timeoutCount;

			QMetaObject::invokeMethod(this, "Interpret", Qt::QueuedConnection);

			return;
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
			|| pixels[19].R != pixels[6].G || pixels[19].G != pixels[12].B || pixels[19].B != pixels[14].R
			|| pixels[22].R != BUILD || pixels[22].G != pixels[20].R || pixels[22].B != pixels[21].G
			|| pixels[28].R != pixels[3].G || pixels[28].G != BUILD || pixels[28].B != pixels[12].R
			|| pixels[36].R != BUILD || pixels[36].G != pixels[0].R || pixels[36].B != pixels[9].G)
	{
		readSuccess = false;
		oneTimeNotifier = false;
		return;
	}

	//Stop timer, sleep if needed and then reset the timer.
	mutex.lock();
	int elapsed = timer.elapsed();
	if (33 - elapsed > 0)
		waitCondition.wait(&mutex, 33 - elapsed);
	timer.restart();
	mutex.unlock();

	//Queue this function again at the bottom of the event list so we can continue to update from the WoW client.
	QMetaObject::invokeMethod(this, "Interpret", Qt::QueuedConnection);
}

void Interpreter::Testing()
{
	mutex.lock();
	PetTeam* myTeam = petStage->GetPetTeam(1);
	myTeam->AddPet(23);
	myTeam->AddPet(57);
	Pet* myFirstPet = myTeam->GetPet(1);
	Pet* mySecondPet = myTeam->GetPet(2);
	myFirstPet->AddAbility(45, 0, true);
	myFirstPet->AddAbility(53, 0, true);
	mySecondPet->AddAbility(42, 0, true);
	mySecondPet->AddAbility(51, 0, true);
	PetAbility* myFirstPetFirstAbility = myFirstPet->GetPetAbility(1);
	PetAbility* myFirstPetSecondAbility = myFirstPet->GetPetAbility(2);
	PetAbility* mySecondPetFirstAbility = mySecondPet->GetPetAbility(1);
	PetAbility* mySecondPetSecondAbility = mySecondPet->GetPetAbility(2);

	PetStage *newPetStage(new PetStage(*petStage));

	myTeam = newPetStage->GetPetTeam(1);
	myFirstPet = myTeam->GetPet(1);
	mySecondPet = myTeam->GetPet(2);
	myFirstPetFirstAbility = myFirstPet->GetPetAbility(1);
	myFirstPetSecondAbility = myFirstPet->GetPetAbility(2);
	mySecondPetFirstAbility = mySecondPet->GetPetAbility(1);
	mySecondPetSecondAbility = mySecondPet->GetPetAbility(2);

	qDebug() << "newPetStage: mySecondPetSecondAbility =" << mySecondPetSecondAbility->GetCooldown();
	mySecondPetSecondAbility->SetCooldown(2);
	qDebug() << "newPetStage: mySecondPetSecondAbility + 2";
	qDebug() << "newPetStage: mySecondPetSecondAbility =" << mySecondPetSecondAbility->GetCooldown();
	qDebug() << "petStage: mySecondPetSecondAbility = " << petStage->GetPetTeam(1)->GetPet(2)->GetPetAbility(2)->GetCooldown();
	mutex.unlock();
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
