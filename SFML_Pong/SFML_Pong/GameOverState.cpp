#include "Definitions.h"
#include "GameOverState.h"

GameOverState::GameOverState(GameDataRef _data) : data(_data)
{
}

GameOverState::~GameOverState()
{
}

void GameOverState::init()
{
	
}

void GameOverState::handleInput()
{
	sf::Event sfmlEvents;

	while (this->data->window.pollEvent(sfmlEvents))
	{
		if (sfmlEvents.type == sf::Event::Closed)
			this->data->window.close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			;//this->data->window.close();
	}
}


void GameOverState::update(const float & dt)
{

}

void GameOverState::render(const float & dt)
{
	this->data->window.clear();



	this->data->window.display();
}
