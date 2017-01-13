#include "enemy.h"

enemy::enemy()
{
	textureOfEnemies[0].loadFromFile("normal_Enemy.png");
	textureOfEnemies[1].loadFromFile("fast_Enemy.png");
	textureOfEnemies[2].loadFromFile("heavy.png");
	textureOfEnemies[3].loadFromFile("Boss.png");

	setupEnemy(0);
	movementSpeed = 4.f;
	hp = 3;
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(position);
	rect.setSize(sf::Vector2f(50,50));
}
void enemy::setupEnemy(int IdOfEnemy)
{
	type = IdOfEnemy;
	switch (IdOfEnemy)
	{
	case 1: //szybki przeciwnik
		sprite.setTexture(textureOfEnemies[1]);
		movementSpeed = 5.f;
		hp = maxHp = 2;
		rect.setFillColor(sf::Color::Yellow);
		rect.setSize(sf::Vector2f(82,60));
		sprite.setTextureRect(sf::IntRect(0,0,82,60));
		break;
	case 2: //Ci�ki
		sprite.setTexture(textureOfEnemies[2]);
		movementSpeed = 1.f;
		maxHp = hp = 10;
		rect.setFillColor(sf::Color::White);
		rect.setSize(sf::Vector2f(96, 80)); 
		sprite.setTextureRect(sf::IntRect(0, 0, 96, 80));
		break;
	case 3:	//boss
		sprite.setTexture(textureOfEnemies[3]);
		movementSpeed = 0.25f;
		maxHp = hp = 100;			
		rect.setFillColor(sf::Color::Magenta);
		rect.setSize(sf::Vector2f(96, 64));
		sprite.setTextureRect(sf::IntRect(0, 0, 96, 64));
		break;
	case 0:	//zwyk�y przeciwnik 
		sprite.setTexture(textureOfEnemies[0]);
		movementSpeed = maxHp = 2.f;
		hp = 3;
		rect.setFillColor(sf::Color::Red);
		rect.setSize(sf::Vector2f(96, 52));
		sprite.setTextureRect(sf::IntRect(0, 0, 96, 52));
		break;
	}
	position = sf::Vector2f(WINDOWWIDTH, rand() % (WINDOWHEIGHT - 125)+ 50);
	rect.setPosition(position);
	slowed = 0;
}
sf::FloatRect enemy::getPosition()
{
	return rect.getGlobalBounds();
}
void enemy::setTexture(sf::Texture texture)
{
	sprite.setTexture(texture);
}
sf::RectangleShape enemy::getShape()
{
	return rect;
}
sf::Sprite enemy::getSprite()
{
	return sprite;
}
void enemy::update()
{
	position.x -= movementSpeed;
	rect.setPosition(position);
	sprite.setPosition(rect.getPosition() );
}
void enemy::Hitted(float minusHP)
{
	hp -= minusHP;
	if (hp <= maxHp / 2 && slowed == false)
	{
		movementSpeed /= 2;
		slowed = true;
	}

}
int enemy::getHP()
{
	return hp;
}
int enemy::getType()
{
	return type;
}
void enemy::slowEnemy()
{
	movementSpeed *= 0.1;
}
void enemy::accelerateEnemy()
{
	movementSpeed *= 10;
}