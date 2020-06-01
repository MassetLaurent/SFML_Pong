#include "Definitions.h"
#include "Ai.h"

Ai::Ai()
{

}

Ai::~Ai()
{

}

sf::FloatRect Ai::getGlobalBounds()
{
	return racketSprite.getGlobalBounds();
}

void Ai::init(std::string _playerType)
{
	this->racketTexture.loadFromFile(AI_TEXTURE);
	this->racketSprite.setTexture(racketTexture);
	this->racketSprite.setPosition(760, 280);
	this->racketSprite.scale(sf::Vector2f(0.68f, 0.68f));
}

void Ai::updatePosition(Ball& _ball, sf::RenderWindow& _window)
{
	if (_ball.getGlobalBounds().left > _window.getSize().x / 2)
	{
		if (_ball.getGlobalBounds().top > racketSprite.getGlobalBounds().top)
			racketSprite.setPosition(racketSprite.getPosition().x, racketSprite.getPosition().y +  MOVEMENT_SPEED);
		else
			racketSprite.setPosition(racketSprite.getPosition().x, racketSprite.getPosition().y - MOVEMENT_SPEED);
		
		if (racketSprite.getGlobalBounds().top >= _window.getSize().y - racketSprite.getGlobalBounds().height - 17)
			racketSprite.setPosition(racketSprite.getPosition().x, _window.getSize().y - racketSprite.getGlobalBounds().height - 18);
	}
}

void Ai::draw(sf::RenderWindow &_window)
{
	_window.draw(racketSprite);
}
