#pragma once

#include "entity.h"
#include "Player.h"
#include "projectile.h"
#include "enemy.h"


class game
{
public:
	//konstruktor, destruktor i metoda publiczna odpowiadaj¹ca za uruchomienie gry
	game();
	void run();

private:
	//metody prywatne
	void StateMachine();
	void StatePLAY();
	void stateMENU();
	void stateSHOP();
	void stateEND();
	void modifyEnemyPercents(int enemy1, int enemy2, int enemy3, int enemy4);
	bool intersectWithMouse(sf::FloatRect objectPos);

	int randomEnemy();

	sf::RenderWindow window;
	enum Status{MENU,PLAY,SHOP,ENDSCR,END};
	Status StatusOfMachine;
	sf::Font font;
	sf::Text text;

	// Szansa na wylosowanie przeciwnika 
	int AverageEnemyPercent = 98;
	int FastEnemyPercent = 1;
	int HeavyEnemyPercent = 1;
	int BossEnemyPercent = 0;
	int Wave = 0;
	int Cash = 0;
	enum CurrentWeapon { PISTOL = 0, MACHINEGUN = 1, ASSAULTRIFLE = 2, SNIPER = 3 };
	bool PermissionToWeapon[4];
	sf::Time DelayBetweenEnemies;
	std::vector <int> Bullets;

	int addBullets(int WhichWeapon);
};