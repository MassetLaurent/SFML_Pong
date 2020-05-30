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
	this->pongText.setFillColor(sf::Color::White);
	this->pongText.setPosition(
		(this->data->window.getSize().x /2) - this->pongText.getGlobalBounds().width /2 + 26
		, -12);

	this->onePlayerText.setFont(font);
	this->onePlayerText.setCharacterSize(50);
	this->onePlayerText.setString("1P Mode");
	this->onePlayerText.setFillColor(sf::Color(255, 150, 50));
	this->onePlayerText.setPosition(
		data->window.getSize().x / 2.f - onePlayerText.getGlobalBounds().width - 100.f,
		data->window.getSize().y / 2.f - 100.f
	);

	this->twoPlayerText.setFont(font);
	this->twoPlayerText.setCharacterSize(50);
	this->twoPlayerText.setString("2P Mode");
	this->twoPlayerText.setFillColor(sf::Color(255, 150, 50));
	this->twoPlayerText.setPosition(
		data->window.getSize().x / 2 + 100.f,
		data->window.getSize().y / 2 - 100.f
	);

	this->quitText.setFont(font);
	this->quitText.setCharacterSize(60);
	this->quitText.setString("Quit");
	this->quitText.setFillColor(sf::Color::White);
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

		if (onePlayerText.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(this->data->window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->data->stateMachine.addState(StateRef(new PlayState(data, false)), false);

		if (twoPlayerText.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(this->data->window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->data->stateMachine.addState(StateRef(new PlayState(data, true)), false);

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
	this->data->window.draw(onePlayerText);
	this->data->window.draw(twoPlayerText);
	this->data->window.draw(quitText);

	this->data->window.display();
}
