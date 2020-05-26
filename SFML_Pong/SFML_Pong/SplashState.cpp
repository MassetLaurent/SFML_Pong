#include "Definitions.h"
#include "SplashState.h"
#include "MainMenuState.h"


//constructor
SplashState::SplashState(GameDataRef _data) : data(_data)
{
}

SplashState::~SplashState()
{
}

//methodes
void SplashState::init()
{
	splash.loadFromFile(SPLASH_BACKGROUND_FILEPATH);
	splashSprite.setTexture(splash);
}

void SplashState::handleInput()
{
	sf::Event sfmlEvents;

	while (this->data->window.pollEvent(sfmlEvents))
	{
		if (sfmlEvents.type == sf::Event::Closed)
			this->data->window.close();
	}
}

void SplashState::update(const float & dt)
{
	if (this->splashClock.getElapsedTime().asSeconds() > SPLASH_DURATION)
		this->data->stateMachine.addState(StateRef(new MainMenuState(data)), true);
}

void SplashState::render(const float & dt)
{
	this->data->window.clear();

	this->data->window.draw(splashSprite);

	this->data->window.display();
}
