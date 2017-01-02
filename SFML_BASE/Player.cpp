#include "Player.h"

player::player()
{
	movementSpeed = 6.f;
	position = sf::Vector2f(LINE, WINDOWHEIGHT / 2);
	rect.setFillColor(sf::Color::Green);
    rect.setPosition(sf::Vector2f(position));
	rect.setSize(sf::Vector2f(50,50));
}
sf::RectangleShape player::getShape()
{
	return rect;
}
void player::setTexture(sf::Texture texture)
{
	sprite.setTexture(texture);
}
sf::Sprite player::getSprite()
{
	return sprite;
}
sf::FloatRect player::getPosition()
{
	return rect.getGlobalBounds();
}
void player::update()
{
	rect.setPosition(position);
}
void player::updateMovement()
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		&& rect.getGlobalBounds().top > 0)
	{
		position.y -= movementSpeed;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		&& rect.getGlobalBounds().top + rect.getGlobalBounds().height < WINDOWHEIGHT)
	{
		position.y += movementSpeed;
	}
}