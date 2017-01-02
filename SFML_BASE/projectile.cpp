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
	position.x += movement;
	rect.setPosition(position);
}
int projectile::getDamage()
{
	return damage;
}
sf::Time projectile::getFirespeed()
{
	return fireSpeed;
}
void projectile::setupProjectile(int IDOfProjectile)
{
	HitSomeone = false;
	rect.setPosition(position);
	switch (IDOfProjectile)
	{
		//zwyk³y pocisk od pistoletu
	case 0:
		movement = 7.5f;
		damage = 1;
		rect.setSize(sf::Vector2f(10,10));
		rect.setFillColor(sf::Color::Color(100,100,100));
		fireSpeed = sf::seconds(0.75f);
		break;
	case 1: //pistolet maszynowy
		movement = 12.5f;
		damage = 2;
		rect.setSize(sf::Vector2f(10, 10));
		rect.setFillColor(sf::Color::Color(200,50,50));
		fireSpeed = sf::seconds(0.1f);
		break;
	case 2: //karabin szturmowy
		movement = 10.f;
		damage = 3;
		rect.setSize(sf::Vector2f(13,13));
		rect.setFillColor(sf::Color::Color(125,125,125));
		fireSpeed = sf::seconds(0.25f);
		break;
	case 3: // karabin snajperski
		movement = 20.f;
		damage = 20;
		rect.setSize(sf::Vector2f(20, 5));
		rect.setFillColor(sf::Color::Color(175,175,175));
		fireSpeed = sf::seconds(1.f);
		break;
	
	default: //kolejne bronie

		break;

	}
	//clock.restart();
	
}