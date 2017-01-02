#pragma once
#include "entity.h"

class projectile
{
public:
	projectile();

	// gettery
	sf::FloatRect getPosition();
	sf::RectangleShape getShape();
	sf::Sprite getSprite();
	sf::Time getTime();

	//setter 
	void setTexture(sf::Texture texture);
	void setupPosition(sf::Vector2f positionOfPlayer);
	bool HitSomeone;
	int getDamage();
	sf::Time getFirespeed();
	void setupProjectile(int IDOfProjectile);
	void update();

private:
	sf::Time fireSpeed;
	sf::RectangleShape rect;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Clock clock;

	float movement;
	float damage;

};