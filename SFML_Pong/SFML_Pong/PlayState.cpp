#include <sstream>

#include "Definitions.h"
#include "MainMenuState.h"
#include "PlayState.h"

void PlayState::updateBallDirection()
{
	if (this->ball.getGlobalBounds().intersects(this->borderBottom.getGlobalBounds()) && this->ball.getBallDir().y > 0)
		this->ball.setBallDirection(this->ball.getBallDir().x, -this->ball.getBallDir().y);

	if (this->ball.getGlobalBounds().intersects(this->borderTop.getGlobalBounds()) && this->ball.getBallDir().y < 0)
		this->ball.setBallDirection(this->ball.getBallDir().x, -this->ball.getBallDir().y);

	if (this->ball.getGlobalBounds().intersects(this->player.getGlobalBounds()) && this->ball.getBallDir().x < 0)
	{
		float randAdd = rand() % 20 + 1;
		this->ball.setBallDirection(-this->ball.getBallDir().x + randAdd, this->ball.getBallDir().y + randAdd / 2);
	}

	if (this->ball.getGlobalBounds().intersects(this->ai.getGlobalBounds()) && this->ball.getBallDir().x > 0)
	{
		float randAdd = rand() % 20 + 1;

		float tempDirY(0.f);

		if (ball.getBallDir().y > 0)
			tempDirY = this->ball.getBallDir().y + randAdd;
		else
			tempDirY = this->ball.getBallDir().y - randAdd;

		this->ball.setBallDirection(-this->ball.getBallDir().x - randAdd, tempDirY);
	}
}

PlayState::PlayState(GameDataRef _data) : data(_data)
{
}

PlayState::~PlayState()
{
}

void PlayState::init()
{
	//Init variables
	this->score = 0;
	this->aiScore = 0;
	this->player.init("player");
	this->ai.init("ai");
	this->showHelp = true;
	   
	//background
	this->backgroundTexture.loadFromFile(GAME_BACKGROUND);
	this->backgroundSprite.setTexture(backgroundTexture);
	this->backgroundSprite.setPosition(0.f, 100.f);

	//terrain border
	this->data->assetManager.loadTexture("Terrain_Border", TERRAIN_BORDER_FILEPATH);
	this->data->assetManager.loadTexture("Middle_Line", MIDDLE_LINE_FILEPATH);

			//border top
	this->borderTop.setTexture(data->assetManager.getTexture("Terrain_Border"));
	this->borderTop.setPosition(-5, 110);

			//middle line
	this->middelLine.setTexture(data->assetManager.getTexture("Middle_Line"));
	this->middelLine.setPosition(405, 118);

			//border bottom
	this->borderBottom.setTexture(data->assetManager.getTexture("Terrain_Border"));
	this->borderBottom.setPosition(-5.f, 580.f);

	//texts
	this->font.loadFromFile(MAIN_MENU_FONT);

			//title text
	this->pongText.setFont(font);
	this->pongText.setString("PONG");
	this->pongText.setCharacterSize(90);
	this->pongText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	this->pongText.setFillColor(sf::Color(0, 0, 0, 255));
	this->pongText.setPosition(
		(this->data->window.getSize().x / 2) - this->pongText.getGlobalBounds().width / 2
		, -30.f);

			//player score
	this->playerScoreText.setFont(font);
	this->playerScoreText.setString("Player : 0");
	this->playerScoreText.setCharacterSize(40);
	this->playerScoreText.setStyle(sf::Text::Bold);
	this->playerScoreText.setFillColor(sf::Color(0, 0, 0, 255));
	this->playerScoreText.setPosition(10.f, 15.f);

			//Ai score
	this->aiScoreText.setFont(font);
	this->aiScoreText.setString("0 : Ai");
	this->aiScoreText.setCharacterSize(40);
	this->aiScoreText.setStyle(sf::Text::Bold);
	this->aiScoreText.setFillColor(sf::Color(0, 0, 0, 255));
	this->aiScoreText.setPosition(
		(this->data->window.getSize().x) - (this->aiScoreText.getGlobalBounds().width) - 20
		, 15.f);
}

void PlayState::showInfos()
{
	this->data->assetManager.loadTexture("Infos" ,INFO_FILEPATH);
	this->infosTexture = this->data->assetManager.getTexture("Infos");

	this->infosSprite.setTexture(infosTexture);
	this->infosSprite.setOrigin(infosSprite.getGlobalBounds().width / 2, infosSprite.getGlobalBounds().height / 2);
	this->infosSprite.setPosition(this->data->window.getSize().x / 2, infosSprite.getGlobalBounds().height + 30);

}

void PlayState::updateScore()
{
	if (this->ball.getGlobalBounds().left > this->data->window.getSize().x)
	{
		this->ball.setPlaying(false);
		this->score++;
		restartBall.restart();
		this->ball.init();
	}

	if (this->ball.getGlobalBounds().left < -10)
	{
		this->ball.setPlaying(false);
		this->aiScore++;
		restartBall.restart();
		this->ball.init();
	}

	std::stringstream ss;

	ss << "Player : " << score;

	this->playerScoreText.setString(ss.str());

	ss.str("");

	ss << aiScore << " : Ai";

	this->aiScoreText.setString(ss.str());
}

void PlayState::handleInput()
{
	sf::Event sfmlEvents;

	while (this->data->window.pollEvent(sfmlEvents))
	{
		if (sfmlEvents.type == sf::Event::Closed)
			this->data->window.close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->data->window.close();

		if (sfmlEvents.type == sf::Event::KeyPressed && (	sfmlEvents.key.code == sf::Keyboard::Z || sfmlEvents.key.code == sf::Keyboard::S 
														|| sfmlEvents.key.code == sf::Keyboard::Up || sfmlEvents.key.code == sf::Keyboard::Down))
		{
			this->showHelp = false;
			if(restartBall.getElapsedTime().asSeconds() > 2)
				this->ball.setPlaying(true);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		this->player.updatePosition(-1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player.updatePosition(1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->ai.updatePosition(-1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->ai.updatePosition(1);
}

void PlayState::update(const float & _dt)
{
	if (showHelp)
		this->showInfos();

	ball.update(_dt);

	this->updateScore();

	this->updateBallDirection();
}

void PlayState::render(const float & dt)
{
	this->data->window.clear(sf::Color(220,220,220));

	//draw player, ball et Ai
	this->data->window.draw(backgroundSprite);
	this->data->window.draw(pongText);
	this->data->window.draw(playerScoreText);
	this->data->window.draw(aiScoreText);

	this->data->window.draw(borderTop);
	this->data->window.draw(middelLine);
	this->data->window.draw(borderBottom);


	this->player.draw(this->data->window);
	this->ai.draw(this->data->window);
	this->ball.draw(this->data->window);

	if(showHelp)
		this->data->window.draw(infosSprite);

	this->data->window.display();
}
