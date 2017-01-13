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
	bool isUpgraded();

	//setter 
	void setTexture(sf::Texture texture);
	void setupPosition(sf::Vector2f positionOfPlayer);
	bool HitSomeone;
	float getDamage();
	sf::Time getFirespeed();
	void setupProjectile(int IDOfProjectile);
	void projectile::setupProjectile(int IDOfProjectile, int movY);
	void update();
	void powerUp();
	void endOfPowerUp();
	int getID();

private:
	sf::Time fireSpeed;
	sf::Time normalFireSpeed;
	sf::RectangleShape rect;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Clock clock;
	sf::Vector2f normalSize;

	float movementX, movementY, normalMovementY;
	float damage;
	bool upgraded;
	int type;

};