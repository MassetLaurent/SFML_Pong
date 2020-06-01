#include <sstream>

#include "Definitions.h"
#include "MainMenuState.h"
#include "PlayState.h"

PlayState::PlayState(GameDataRef _data, bool _twoPlayers) : data(_data), twoPlayers(_twoPlayers)
{
}

PlayState::~PlayState()
{
}

void PlayState::init()
{
	//Init variables
	this->score = 0;
	this->player2Score = 0;
	this->player.init("player");

	if (!twoPlayers)
		this->ai.init("ai");
	else
		this->player2.init("player2");

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
	this->pongText.setFillColor(sf::Color::White);
	this->pongText.setPosition(
		(this->data->window.getSize().x / 2) - this->pongText.getGlobalBounds().width / 2
		, -30.f);

			//player score
	this->playerScoreText.setFont(font);
	this->playerScoreText.setString("1P : 0");
	this->playerScoreText.setCharacterSize(40);
	this->playerScoreText.setStyle(sf::Text::Bold);
	this->playerScoreText.setFillColor(sf::Color::White);
	this->playerScoreText.setPosition(10.f, 15.f);

			//Ai score
	this->player2ScoreText.setFont(font);
	this->player2ScoreText.setString("0 : 2P");
	this->player2ScoreText.setCharacterSize(40);
	this->player2ScoreText.setStyle(sf::Text::Bold);
	this->player2ScoreText.setFillColor(sf::Color::White);
	this->player2ScoreText.setPosition(
		(this->data->window.getSize().x) - (this->player2ScoreText.getGlobalBounds().width) - 20
		, 15.f);

		//ball speed
	this->ballSpeedText.setFont(font);
	this->ballSpeedText.setString("Ball Speed : ");
	this->ballSpeedText.setCharacterSize(30);
	this->ballSpeedText.setStyle(sf::Text::Bold);
	this->ballSpeedText.setFillColor(sf::Color::White);
	this->ballSpeedText.setPosition(
		this->data->window.getSize().x / 2 - this->ballSpeedText.getGlobalBounds().width /2
		, this->pongText.getGlobalBounds().height + 20);
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
		this->player2Score++;
		restartBall.restart();
		this->ball.init();
	}

	std::stringstream ss;

	ss << "1P : " << score;

	this->playerScoreText.setString(ss.str());

	ss.str("");

	ss << player2Score << " : 2P";

	this->player2ScoreText.setString(ss.str());

	ss.str("");

	ss << "Ball Speed : " << ball.getSpeed() ;

	this->ballSpeedText.setString(ss.str());
}

void PlayState::updateBallDirection()
{
	//ball hit the player racket
	if (this->ball.getGlobalBounds().intersects(this->borderBottom.getGlobalBounds()) && this->ball.getBallDir().y > 0)
		this->ball.setBallDirection(this->ball.getBallDir().x, -this->ball.getBallDir().y);

	if (this->ball.getGlobalBounds().intersects(this->borderTop.getGlobalBounds()) && this->ball.getBallDir().y < 0)
		this->ball.setBallDirection(this->ball.getBallDir().x, -this->ball.getBallDir().y);

	if (this->ball.getGlobalBounds().intersects(this->player.getGlobalBounds()) && this->ball.getBallDir().x < 0)
	{
		float randAdd = rand() % 20 + 1;
		this->ball.setBallDirection(-this->ball.getBallDir().x + randAdd, this->ball.getBallDir().y + randAdd / 2);
	}
	
	//ball hit the player2 racket
	if (this->ball.getGlobalBounds().intersects(this->player2.getGlobalBounds()) && this->ball.getBallDir().x > 0)
	{
		float randAdd = rand() % 20 + 1;
		float tempDirY(0.f);

		if (ball.getBallDir().y > 0)
			tempDirY = this->ball.getBallDir().y + randAdd;
		else
			tempDirY = this->ball.getBallDir().y - randAdd;

		this->ball.setBallDirection(-this->ball.getBallDir().x - randAdd, tempDirY);
	}

	//ball hit the AI racket
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

	//player movements
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		this->player.updatePosition(-1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player.updatePosition(1);

	//player2 movements
	if (twoPlayers)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			this->player2.updatePosition(-1);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			this->player2.updatePosition(1);
	}
}

void PlayState::update(const float & _dt)
{
	if (showHelp)
		this->showInfos();

	ball.update(_dt);

	this->updateScore();

	if (!twoPlayers)
		ai.updatePosition(this->ball, this->data->window);

	this->updateBallDirection();
}

void PlayState::render(const float & dt)
{
	// --------- clear frame -------
	this->data->window.clear();

	// --------- draw -------
	//gui
	this->data->window.draw(pongText);
	this->data->window.draw(playerScoreText);
	this->data->window.draw(player2ScoreText);
	this->data->window.draw(ballSpeedText);

	//background
	this->data->window.draw(backgroundSprite);
	this->data->window.draw(borderTop);
	this->data->window.draw(middelLine);
	this->data->window.draw(borderBottom);

	//players or ai
	this->player.draw(this->data->window);

	if (!twoPlayers)
		this->ai.draw(this->data->window);
	else
		this->player2.draw(this->data->window);

	this->ball.draw(this->data->window);

	//help text
	if(showHelp)
		this->data->window.draw(infosSprite);


	// --------- display -------
	this->data->window.display();
}
