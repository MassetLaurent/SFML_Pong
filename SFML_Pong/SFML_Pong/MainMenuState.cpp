#include "Definitions.h"
#include "MainMenuState.h"
#include "PlayState.h"

MainMenuState::MainMenuState(GameDataRef _data) : data(_data)
{
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::init()
{
	background.loadFromFile(MENU_BACKGROUND);
	this->backgroundSprite.setTexture(background);

	this->font.loadFromFile(MAIN_MENU_FONT);

	this->pongText.setFont(font);
	this->pongText.setString("PONG");
	this->pongText.setCharacterSize(90);
	this->pongText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	this->pongText.setFillColor(sf::Color(190, 190, 190));
	this->pongText.setPosition(
		(this->data->window.getSize().x /2) - this->pongText.getGlobalBounds().width /2 + 26
		, -12);

	this->startText.setFont(font); 
	this->startText.setCharacterSize(60);
	this->startText.setString("Start");
	//this->startText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	this->startText.setFillColor(sf::Color(190, 190, 190));
	this->startText.setPosition(
		(this->data->window.getSize().x / 2) - this->pongText.getGlobalBounds().width / 2 + 50,
		120.f
		);

	this->quitText.setFont(font);
	this->quitText.setCharacterSize(60);
	this->quitText.setString("Quit");
	//this->startText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	this->quitText.setFillColor(sf::Color(190, 190, 190));
	this->quitText.setPosition(
		this->data->window.getSize().x / 2 - 50.f,
		480.f
	);	
}

void MainMenuState::handleInput()
{
	sf::Event sfmlEvents;

	while (this->data->window.pollEvent(sfmlEvents))
	{
		if (sfmlEvents.type == sf::Event::Closed)
			this->data->window.close();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->data->window.close();

		if (startText.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(this->data->window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->data->stateMachine.addState(StateRef(new PlayState(data)), false);

		if (quitText.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(this->data->window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->data->window.close();
	}
}


void MainMenuState::update(const float & dt)
{

}

void MainMenuState::render(const float & dt)
{
	this->data->window.clear();

	this->data->window.draw(backgroundSprite);
	this->data->window.draw(pongText);
	this->data->window.draw(startText);
	this->data->window.draw(quitText);

	this->data->window.display();
}
