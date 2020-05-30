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

void Ai::updatePosition(int _dir_y)
{
	//-------------------mettre en place la logique de déplacement de l'IA-----------


	/*	
	this->racketSprite.setPosition(
		this->racketSprite.getPosition().x,
		this->racketSprite.getPosition().y + (_dir_y * MOVEMENT_SPEED));

	if (this->racketSprite.getPosition().y < 120)
		this->racketSprite.setPosition(this->racketSprite.getPosition().x, 120);
	else if (this->racketSprite.getPosition().y > 480)
		this->racketSprite.setPosition(this->racketSprite.getPosition().x, 480);
	*/
}

void Ai::draw(sf::RenderWindow &_window)
{
	_window.draw(racketSprite);
}
