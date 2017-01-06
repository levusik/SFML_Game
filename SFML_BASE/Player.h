#pragma once
#include "entity.h"

//narazie korzystam z kwadratów nie ze Sprite'ów bo tak jest mi wygodniej oraz nie mam grafik :/

class player
{
public:
	player();

	//gettery
	sf::FloatRect getPosition();
	sf::RectangleShape getShape();
	sf::Sprite getSprite();
	
	//settery
	void setTexture(sf::Texture texture);

	//update'y
	void update();
	void updateMovement();

private:	
	sf::Texture texture;
	sf::RectangleShape rect;
	sf::Sprite sprite;
	sf::Vector2f position;
	float movementSpeed;

};