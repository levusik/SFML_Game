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
	int randomEnemy();

	sf::RenderWindow window;
	enum Status{MENU,PLAY,END};
	Status StatusOfMachine;
	sf::Font font;
	sf::Text text;
};