#include "game.h"



game::game()
{
	//konfiguracja okienka
	sf::ContextSettings settings;
	settings.antialiasingLevel = 1;
    window.create(sf::VideoMode(WINDOWWIDTH,WINDOWHEIGHT),"NAZWA APPKI",sf::Style::Default,settings);
	window.setFramerateLimit(30);
	//ustawienie stanu pocz¹tkowego (w domyœle jest to MENU ale narazie PLAY bo PLAY jest trudniejsze do oprogramowania)
	StatusOfMachine = PLAY;
	if (!font.loadFromFile("font.ttf") && DEBUG == 1)
		std::cout << "Problem z czcionk¹ m8\n";
	text.setCharacterSize(30);
	text.setFont(font);
}
void game::run()
{
	while (StatusOfMachine != END)
	{
		StateMachine();
	}

	window.close();
}
// maszyna Stanowa
void game::StateMachine()
{
	switch (StatusOfMachine)
	{
	case MENU:
		stateMENU();
		break;
	case PLAY:
		StatePLAY();
		break;
	}
}
void game::StatePLAY()
{
	//dekleracje zmiennych 
	int counter, counter1, counter2;
	enum CurrentWeapon{PISTOL = 0,MACHINEGUN = 1,ASSAULTRIFLE = 2, SNIPER = 3};
	counter = counter1 = counter2 = 0;


	int Cash, Wave, bulletsLeft;
	CurrentWeapon WhichWeapon;
	Cash = 0;
	Wave = 0;
	bulletsLeft = 999;
	WhichWeapon = PISTOL;
	sf::Time currentFireSpeed;

	//wektor, obiekt i iterator potrzebne do pocisków
	std::vector <projectile> ProjectileArray;
	std::vector <projectile>::iterator iterProj;
	projectile Projectile;
	currentFireSpeed = Projectile.getFirespeed();

	// wektor,obiekt i iterator potrzebne do tworzenia/wyœwietlania przeciwników
	std::vector <enemy> enemyArray;
	std::vector <enemy>::iterator iterEnem;
	enemy Enemy;

	//Gracz
	player Player;

	//Zegar potrzebny do pocisków
	sf::Clock delayBetweenSpawningProjectiles;
	delayBetweenSpawningProjectiles.restart();

	//Zegar potrzebny do przeciwników
	sf::Clock EnemySpawnClock;
	EnemySpawnClock.restart();

	// g³ówna pêtla stanu GRA 
	while (StatusOfMachine == PLAY)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				StatusOfMachine = END;
		}
		//zmiania broni 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			WhichWeapon = PISTOL;
			Projectile.setupProjectile(0);
			currentFireSpeed = Projectile.getFirespeed();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			WhichWeapon = MACHINEGUN;
			Projectile.setupProjectile(1);
			currentFireSpeed = Projectile.getFirespeed();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			WhichWeapon = ASSAULTRIFLE;
			Projectile.setupProjectile(2);
			currentFireSpeed = Projectile.getFirespeed();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			WhichWeapon = SNIPER;
			Projectile.setupProjectile(3);
			currentFireSpeed = Projectile.getFirespeed();
		}

		counter = 0;
		for (iterEnem = enemyArray.begin(); iterEnem != enemyArray.end(); ++iterEnem)
		{
			if (enemyArray[counter].getPosition().left <= LINE)
				StatusOfMachine = END;
			counter++;
		}

		//dodajemy pocisk
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && delayBetweenSpawningProjectiles.getElapsedTime()
			>= currentFireSpeed && bulletsLeft > 0)
		{
			Projectile.setupPosition( Player.getShape().getPosition());
			Projectile.setupProjectile(WhichWeapon);

			ProjectileArray.push_back(Projectile);
			delayBetweenSpawningProjectiles.restart();
			bulletsLeft--;
		}

		// po jakimœ czasie dodajemy kolejnego przeciwnika 
		if (EnemySpawnClock.getElapsedTime() >= sf::seconds(2.f))
		{
			Enemy.setupEnemy(randomEnemy() );
			enemyArray.push_back(Enemy);
			EnemySpawnClock.restart();
		}

		//czyszczenie okna
		window.clear();

		// Sprawdzienie Czy pocisk dotkn¹³ przeciwnika 
		counter = 0;
		for (iterProj = ProjectileArray.begin(); iterProj != ProjectileArray.end(); ++iterProj)
		{
			counter1 = 0;
			for (iterEnem = enemyArray.begin(); iterEnem != enemyArray.end(); ++iterEnem)
			{
				if (ProjectileArray[counter].getPosition().intersects(enemyArray[counter1].getPosition()))
				{
					enemyArray[counter1].Hitted(ProjectileArray[counter].getDamage());
					ProjectileArray[counter].HitSomeone = true;
				}
				counter1++;
			}
			counter++;
		}

		//usuwanie zbêdnych przeciwników
		counter = 0;
		for (iterEnem = enemyArray.begin(); iterEnem != enemyArray.end(); ++iterEnem)
		{
			if (enemyArray[counter].getHP() <= 0)
			{
				enemyArray.erase(iterEnem);
				iterEnem = enemyArray.begin();
				counter = 0;
				//break;
			}
			counter++;
		}

		//Usuwanie zbêdnych pocisków
		counter = 0;
		for (iterProj = ProjectileArray.begin(); iterProj != ProjectileArray.end(); ++iterProj)
		{
			if (ProjectileArray[counter].getTime() >= sf::seconds(2.f) || ProjectileArray[counter].HitSomeone == true)
			{
				ProjectileArray.erase(iterProj);
				break;
			}
			counter++;
		}


		if (DEBUG == 1)
		std::cout << ProjectileArray.size() << " | "<<enemyArray.size()<<"\n";


		counter = 0;
		for (iterEnem = enemyArray.begin(); iterEnem != enemyArray.end(); ++iterEnem)
		{
			enemyArray[counter].update();
			window.draw(enemyArray[counter].getShape());
			counter++;
		}
		//update i rysowanie pocisków 
		counter = 0;
		for (iterProj = ProjectileArray.begin(); iterProj != ProjectileArray.end(); ++iterProj)
		{
			ProjectileArray[counter].update();
			window.draw(ProjectileArray[counter].getShape());
			counter++;
		}
		//HUD
		std::stringstream ss;
		ss << "Broñ : " <<WhichWeapon<< " | Fala : " << Wave << " | Amunicja : " << bulletsLeft << " | Kasa : " << Cash;
		text.setString(ss.str());
		window.draw(text);

		//update Gracza i rysowanie go
		Player.updateMovement();
		Player.update();
		window.draw(Player.getShape());

		//wyœwietlanie rzeczy
		window.display();
	}

}

void game::stateMENU()
{
	while (StatusOfMachine == MENU)
	{



	}
}

int game::randomEnemy()
{
	int randomNum = rand() % 100 + 1;

	// 75 % na wygenerowanie zwyk³ego przeciwnika
	if (randomNum <= 75)
		return 0;
	// 15 % na wygenerowanie szybkiego
	else if (randomNum > 75 && randomNum <= 90)
		return 1;
	// 9 % na ciê¿kiego
	else if (randomNum > 90 && randomNum != 100)
		return 2;
	//1 % na bossa 
	else if (randomNum == 100)
		return 3;
	return 0;
}