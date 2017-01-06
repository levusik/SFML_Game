#pragma once
#include "entity.h"
#define HOWMANYTYPESOFENEMIES 4

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
	int getType();
	
private:
	sf::RectangleShape rect;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Texture textureOfEnemies[HOWMANYTYPESOFENEMIES];
	float movementSpeed;
	int hp;
	int maxHp;
	bool slowed;
	int type;
};