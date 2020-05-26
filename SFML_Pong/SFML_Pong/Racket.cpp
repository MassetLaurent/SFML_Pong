#include "Definitions.h"
#include "Racket.h"

Racket::Racket()
{

}

Racket::~Racket()
{

}

sf::FloatRect Racket::getGlobalBounds()
{
	return racketSprite.getGlobalBounds();
}

void Racket::init(std::string _playerType)
{
	if (_playerType == "player")
	{
		this->racketTexture.loadFromFile(PLAYER_TEXTURE);
		this->racketSprite.setPosition(	10,	280);
		this->racketSprite.scale(sf::Vector2f(0.65f, 0.65f));
	}
	else
	{
		this->racketTexture.loadFromFile(AI_TEXTURE);
		this->racketSprite.setPosition(760, 280);
		this->racketSprite.scale(sf::Vector2f(0.68f, 0.68f));
	}

	this->racketSprite.setTexture(racketTexture);
}

void Racket::updatePosition(int _dir_y)
{
	this->racketSprite.setPosition(
		this->racketSprite.getPosition().x,
		this->racketSprite.getPosition().y + (_dir_y * MOVEMENT_SPEED));

	if (this->racketSprite.getPosition().y < 120)
		this->racketSprite.setPosition(this->racketSprite.getPosition().x, 120);
	else if (this->racketSprite.getPosition().y > 480)
		this->racketSprite.setPosition(this->racketSprite.getPosition().x, 480);
}

void Racket::draw(sf::RenderWindow &_window)
{
	_window.draw(racketSprite);
}
