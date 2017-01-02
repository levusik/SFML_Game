#pragma once
#include "entity.h"

class enemy
{
public:
	enemy();

	sf::RectangleShape getShape();
	sf::Sprite getSprite();
	sf::FloatRect getPosition();
	void setTexture(sf::Texture texture);
	void update();
	void setupEnemy(int IdOfEnemy);
	void Hitted(int minusHP);
	int getHP();
	
private:
	sf::RectangleShape rect;
	sf::Sprite sprite;
	sf::Vector2f position;
	float movementSpeed;
	int hp;
	int maxHp;
	bool slowed;

};