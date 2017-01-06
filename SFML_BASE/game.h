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
	int AverageEnemyPercent = 80;
	int FastEnemyPercent = 7;
	int HeavyEnemyPercent = 8;
	int BossEnemyPercent = 5;
	int Wave = 0;
	int Cash = 0;
};