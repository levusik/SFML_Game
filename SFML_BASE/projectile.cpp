#include "projectile.h"


projectile::projectile()
{
	setupProjectile(0);
}
sf::FloatRect projectile::getPosition()
{
	return rect.getGlobalBounds();
}
sf::RectangleShape projectile::getShape()
{
	return rect;
}
sf::Sprite projectile::getSprite()
{
	return sprite;
}
sf::Time projectile::getTime()
{
	return clock.getElapsedTime();
}
void projectile::setTexture(sf::Texture texture)
{
	sprite.setTexture(texture);
}
void projectile::setupPosition(sf::Vector2f positionOfPlayer)
{
	position = positionOfPlayer;
	clock.restart();
}
void projectile::update()
{
	position.x += movementX;
	position.y += movementY;
	if (upgraded && type == 4)
		rect.rotate(1);
	rect.setPosition(position);
}
void projectile::powerUp()
{

	if (type != 4)
	{
		normalSize = rect.getSize();
		rect.setSize(sf::Vector2f(30, 10));
		normalMovementY = 0;
	}
	else
	{
		normalSize = rect.getSize();
		rect.setSize(sf::Vector2f(20, 20));
		normalMovementY = movementY;
		movementY /= 4;
	}
	normalFireSpeed = fireSpeed;
	upgraded = 1;
	damage *= 2;
	fireSpeed /= 2.5f;
}
void projectile::endOfPowerUp()
{
	upgraded = 0;
	rect.setSize(normalSize);
	movementY = normalMovementY;
	damage /= 2;
	fireSpeed = normalFireSpeed;
}
int projectile::getID()
{
	return type;
}
float projectile::getDamage()
{
	return damage;
}
sf::Time projectile::getFirespeed()
{
	return fireSpeed;
}
void projectile::setupProjectile(int IDOfProjectile)
{
	type = IDOfProjectile;
	upgraded = 0;
	HitSomeone = false;
	rect.setPosition(position);
	switch (IDOfProjectile)
	{
		//zwyk�y pocisk od pistoletu
	case 0:
		movementX = 7.5f;
		movementY = 0;
		damage = 2;
		rect.setSize(sf::Vector2f(20,5));
		rect.setFillColor(sf::Color::Color(100,100,100));
		fireSpeed = sf::seconds(0.75f);
		break;
	case 1: //pistolet maszynowy
		movementX = 12.5f;
		movementY = 0;
		damage = 1;
		rect.setSize(sf::Vector2f(20, 5));
		rect.setFillColor(sf::Color::Color(200,50,50));
		fireSpeed = sf::seconds(0.1f);
		break;
	case 2: //karabin szturmowy
		movementX = 10.f;
		movementY = 0.f;
		damage = 3.f;
		rect.setSize(sf::Vector2f(20,5));
		rect.setFillColor(sf::Color::Color(125,125,125));
		fireSpeed = sf::seconds(0.25f);
		break;
	case 3: // karabin snajperski
		movementX = 20.f;
		movementY = 0;
		damage = 20.f;
		rect.setSize(sf::Vector2f(20, 5));
		rect.setFillColor(sf::Color::Color(175,175,175));
		fireSpeed = sf::seconds(1.f);
		break;
	case 4: // shotgun ? 
		movementX = 8.5f;
		movementY = .5f;
		damage = 2.f;
		rect.setSize(sf::Vector2f(10, 10));
		rect.setFillColor(sf::Color::Color(175, 175, 175));
		fireSpeed = sf::seconds(1.f);
		break;
	case 5:
		movementX = 10.f;
		movementY = 0.f;
		damage = 0.1f;
		rect.setSize(sf::Vector2f(5, 5));
		rect.setFillColor(sf::Color::Color(175, 175, 175));
		fireSpeed = sf::seconds(0.001f);
		break;
	default: //kolejne bronie

		break;

	}
	//clock.restart();
	
}
void projectile::setupProjectile(int IDOfProjectile, int movY)
{
	if (IDOfProjectile == 4)
	{
		movementX = 8.5f;
		movementY = movY;
		damage = 4.f;
		rect.setSize(sf::Vector2f(10, 10));
		rect.setFillColor(sf::Color::Color(175, 175, 175));
		fireSpeed = sf::seconds(1.f);
	}
}
bool projectile::isUpgraded()
{
	return upgraded;
}