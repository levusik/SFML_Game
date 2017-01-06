#include "game.h"



game::game()
{
	//konfiguracja okienka
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(WINDOWWIDTH,WINDOWHEIGHT),"NAZWA APPKI",sf::Style::Default,settings);
	window.setFramerateLimit(30);
	//ustawienie stanu pocz¹tkowego (w domyœle jest to MENU ale narazie PLAY bo PLAY jest trudniejsze do oprogramowania)
	StatusOfMachine = MENU;
	if (!font.loadFromFile("font.ttf") && DEBUG == 1)
		std::cout << "Problem z czcionk¹ \n";
	text.setCharacterSize(30);
	text.setFont(font);
}
void game::run()
{
	while (StatusOfMachine != END)
	{
		std::cout << StatusOfMachine << "\n";
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
	case ENDSCR:
		stateEND();
		break;
	case SHOP:
		stateSHOP();
		break;
	}
}
void game::StatePLAY()
{
	//dekleracje zmiennych 
	int counter, counter1, counter2;
	enum CurrentWeapon{PISTOL = 0,MACHINEGUN = 1,ASSAULTRIFLE = 2, SNIPER = 3};
	counter = counter1 = counter2 = 0;

	// zmienne do fal
	bool waveLock = false;
	int numberOfEnemies, typeOfWave;
	sf::Clock timeWave;
	
	
	int bulletsLeft;
	CurrentWeapon WhichWeapon;
	 typeOfWave = 0;
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
		if (waveLock == false)
		{
			//czyszczenie planszy 
			while (ProjectileArray.size())
			{
				for (iterProj = ProjectileArray.begin(); iterProj != ProjectileArray.end(); ++iterProj)
				{
					ProjectileArray.erase(iterProj);
					break;
				}
			}
			while (enemyArray.size())
			{
				for (iterEnem = enemyArray.begin(); iterEnem != enemyArray.end(); ++iterEnem)
				{
					enemyArray.erase(iterEnem);
					break;
				}
			}

			// typy fal : 
			
			// fala bosa ? 
			// czasówka
			// zwyk³a 

			Wave++;
			//  wielokrotnoœci 4 to czasówki
			if (Wave % 4 == 0)
			{
				timeWave.restart();
				typeOfWave = 1;
			}
			else
			{
				typeOfWave = 0;
				numberOfEnemies = 20 + Wave;
				modifyEnemyPercents(80, 8, 8, 4);

				//jakiœ sprytny wzór na przeciwników
				//  ..
				//  ..
				//  ..
			}
			waveLock = true;
		}

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
				StatusOfMachine = ENDSCR;
			counter++;
		}

		//dodajemy pocisk
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && delayBetweenSpawningProjectiles.getElapsedTime()
			>= currentFireSpeed && bulletsLeft > 0)
		{
			Projectile.setupPosition( sf::Vector2f(Player.getShape().getPosition().x + (Player.getShape().getGlobalBounds().width /2),
									Player.getShape().getPosition().y + (Player.getShape().getGlobalBounds().height/2) ));
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
				numberOfEnemies--;

				if (enemyArray[counter].getType() == 0)
					Cash += 5;
				else if (enemyArray[counter].getType() == 1)
					Cash += 10;
				else if (enemyArray[counter].getType() == 2)
					Cash += 15;
				else if (enemyArray[counter].getType() == 3)
					Cash += 50;

				break;
			}
			counter++;
		}

		//Usuwanie zbêdnych pocisków
		counter = 0;
		for (iterProj = ProjectileArray.begin(); iterProj != ProjectileArray.end(); ++iterProj)
		{
			if ((ProjectileArray[counter].getTime() >= sf::seconds(2.f) && 
				ProjectileArray[counter].getShape().getGlobalBounds().left >= WINDOWWIDTH) || ProjectileArray[counter].HitSomeone == true )
			{
				ProjectileArray.erase(iterProj);
				break;
			}
			counter++;
		}


		if (DEBUG == 1)
		std::cout << ProjectileArray.size() << " | "<<enemyArray.size()<<"\n";
		
		//update i rysowanie przeciwników
		counter = 0;
		for (iterEnem = enemyArray.begin(); iterEnem != enemyArray.end(); ++iterEnem)
		{
			enemyArray[counter].update();
			if (DEBUG == 1)
			window.draw(enemyArray[counter].getShape()); // <- kwadrat
			window.draw(enemyArray[counter].getSprite()); // <- grafika
			counter++;
		}

		//update i rysowanie pocisków 
		counter = 0;
		for (iterProj = ProjectileArray.begin(); iterProj != ProjectileArray.end(); ++iterProj)
		{
			ProjectileArray[counter].update();
			//window.draw()						// <- grafika
			window.draw(ProjectileArray[counter].getShape()); 
			counter++;
		}
		//HUD

		if ((typeOfWave == 1 && timeWave.getElapsedTime() >= sf::seconds(60.f)) ||
			(typeOfWave != 1 && numberOfEnemies <= 0))
		{
			waveLock = false;
			StatusOfMachine = SHOP;
		}

		std::stringstream stringStream;
		if (typeOfWave != 1)
		stringStream<<"  Fala : " << Wave <<"| Pozostalo : "<< numberOfEnemies << " | Broñ : " << WhichWeapon << " | Amunicja : " << bulletsLeft << " | Kasa : " << Cash;
		text.setString(stringStream.str());
		window.draw(text);

		//update Gracza i rysowanie go
		Player.updateMovement();
		Player.update();
		
		if (DEBUG == 1)
		window.draw(Player.getShape());   // <- kwadrat
		window.draw(Player.getSprite());	 // <- grafika

		//wyœwietlanie rzeczy
		window.display();
	}

}
void game::stateMENU()
{
	sf::Clock delayBeetweenKeyboardButtons;
	const int howManyOptions = 2;
	std::string options[howManyOptions] = { "Graj","zakoñcz"};
	sf::Text MenuText[howManyOptions];
	int lastOptionMarked = 0;
	int optionMarked = 0;
	MenuText[optionMarked].setFillColor(sf::Color::Green);
	delayBeetweenKeyboardButtons.restart();
	for (int i = 0; i < howManyOptions; ++i)
	{
		MenuText[i].setFont(font);
		MenuText[i].setCharacterSize(80);
		MenuText[i].setString(options[i]);
		MenuText[i].setPosition( WINDOWWIDTH /2 - MenuText[i].getGlobalBounds().width ,
			WINDOWHEIGHT / 2 - MenuText[i].getGlobalBounds().height + i*125 );
	}
	while (StatusOfMachine == MENU)
	{

		sf::Vector2f mouse(sf::Mouse::getPosition());
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				StatusOfMachine = END;
		}
		//obs³uga klawiatury
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			&& delayBeetweenKeyboardButtons.getElapsedTime() >= sf::seconds(0.25f))
		{
			if (optionMarked > 0)
			{
				MenuText[lastOptionMarked].setFillColor(sf::Color::White);
				optionMarked--;
				MenuText[optionMarked].setFillColor(sf::Color::Green);
				lastOptionMarked = optionMarked;
			}
			delayBeetweenKeyboardButtons.restart();
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			&& delayBeetweenKeyboardButtons.getElapsedTime() >= sf::seconds(0.25f))
		{
			if (optionMarked < howManyOptions - 1)
			{
				MenuText[lastOptionMarked].setFillColor(sf::Color::White);
				optionMarked++;
				MenuText[optionMarked].setFillColor(sf::Color::Green);
				lastOptionMarked = optionMarked;
			}
			delayBeetweenKeyboardButtons.restart();
		}
		

		//przechodzenie do stanów za pomoc¹ spacji
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			//je¿eli wcisnêliœmy enter to 
			// przyp 1 - przejœcie do stanu PLAY
			// przyp 2 - przejœcie do stanu END
			switch (optionMarked)
			{
			case 0:
				StatusOfMachine = PLAY;
				break;
			case 1:
				window.close();
				StatusOfMachine = END;
				break;

			}
		}
		
		
		if (DEBUG == 1)
			std::cout << optionMarked << std::endl;


		window.clear();

		for (int i = 0; i < howManyOptions; ++i)
		{
			window.draw(MenuText[i]);
		}

		window.display();
	}
}
void game::stateSHOP()
{
	const int howManyButtons = 4;
	sf::RectangleShape BuyWeapon[howManyButtons];
	sf::RectangleShape BuyAmmo[howManyButtons];
	sf::RectangleShape Play;
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(50);
	text.setString("SKLEP");
	text.setPosition(sf::Vector2f(((WINDOWWIDTH - text.getGlobalBounds().width) / 2), 0));

	Play.setSize(sf::Vector2f(100, 100));
	Play.setFillColor(sf::Color::Green);
	Play.setPosition(sf::Vector2f(WINDOWWIDTH-150,WINDOWHEIGHT-200));

	for (int i = 0; i < 4; ++i)
	{
		BuyWeapon[i].setSize(sf::Vector2f(50, 50));
		BuyWeapon[i].setFillColor(sf::Color::Color((i+1) * 50, 0, 0));
		BuyWeapon[i].setPosition(sf::Vector2f(WINDOWWIDTH/(howManyButtons+2) *(i+1)  ,WINDOWHEIGHT/3));

		BuyAmmo[i].setSize(sf::Vector2f(50, 25));
		BuyAmmo[i].setFillColor(sf::Color::Color((i+1) * 50, 0, 0));
		BuyAmmo[i].setPosition(sf::Vector2f(WINDOWWIDTH / (howManyButtons + 2) *(i + 1),
			WINDOWHEIGHT / 3 + BuyWeapon[i].getGlobalBounds().height + 25 ));
	}
	//zakup amunicji, broni oraz ulepszeñ
	while (StatusOfMachine == SHOP)
	{


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				StatusOfMachine = END;
		}

		if (intersectWithMouse(Play.getGlobalBounds()))
		{
			StatusOfMachine = PLAY;
		}

		window.clear();
		for (int i = 0; i < 4; ++i)
		{
			window.draw(BuyWeapon[i]);
			window.draw(BuyAmmo[i]);
		}

		for (int i = 0; i < 4; ++i)
		{
			if (intersectWithMouse(BuyWeapon[i].getGlobalBounds()))
			{
				std::cout << "ZAKUP BRONI "<<i<<" \n";
			}
			if (intersectWithMouse(BuyAmmo[i].getGlobalBounds()))
			{
				std::cout << "ZAKUP AMUNICJI DO BRONI " << i << "\n";
			}

		}

		window.draw(text);
		window.draw(Play);
		window.display();
	}
}
void game::stateEND()
{
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(80);
	text.setFillColor(sf::Color::Green);
	text.setString("Koniec Gry");
	text.setPosition(sf::Vector2f(WINDOWWIDTH/1.25-text.getGlobalBounds().width ,WINDOWHEIGHT/3));
	sf::Clock EndClock;
	EndClock.restart();

	bool lock = false;

	while (EndClock.getElapsedTime() <= sf::seconds(2.f))
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				lock = true;
				StatusOfMachine = END;
				break;
				break;
			}
		}
		window.clear();
		window.draw(text);
		window.display();
	}
	if (lock == false)
	StatusOfMachine = MENU;
}
void game::modifyEnemyPercents(int enemy1, int enemy2, int enemy3, int enemy4)
{
	AverageEnemyPercent = enemy1;
    FastEnemyPercent = enemy2;
	HeavyEnemyPercent = enemy3;
    BossEnemyPercent = enemy4;
}
int game::randomEnemy()
{
	int randomNum = rand() % 100 + 1;

	if (randomNum <= AverageEnemyPercent)
		return 0;
	else if (randomNum > AverageEnemyPercent && randomNum <= AverageEnemyPercent + FastEnemyPercent)
		return 1;
	else if (randomNum > AverageEnemyPercent + FastEnemyPercent 
		&& randomNum <= AverageEnemyPercent + FastEnemyPercent + HeavyEnemyPercent)
		return 2;
	else if (randomNum > AverageEnemyPercent + FastEnemyPercent + HeavyEnemyPercent )
		return 3;
	return 0;
}
bool game::intersectWithMouse( sf::FloatRect objectPos)
{
	if (sf::Mouse::getPosition(window).x >= objectPos.left &&
		sf::Mouse::getPosition(window).x <= objectPos.left + objectPos.width &&
		sf::Mouse::getPosition(window).y >= objectPos.top &&
		sf::Mouse::getPosition(window).y <= objectPos.top + objectPos.height &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return 1;
	return 0;
}