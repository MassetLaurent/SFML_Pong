#include "Ball.h"
#include "Definitions.h"

#include <iostream>

//constrructor
Ball::Ball()
{
	this->init();
}

Ball::~Ball()
{
}



//methodes
void Ball::init()
{
	this->playing = false;

	this->ball.setRadius(10.f);
	this->ball.setFillColor(sf::Color(200,200,200));
	this->ball.setPosition(398, 320);

	//init ball directions
	srand(time(0));
	// direction X
	int tempDirection = rand() % 100;

	if (tempDirection % 2 == 0)
		dir_x = 1;
	else
		dir_x = -1;

	//direction Y
	tempDirection = rand() % 100;

	if (tempDirection % 2 == 0)
		dir_y = 1;
	else
		dir_y = -1;
		//dir_y = (float)-tempDirection / 50;
}

sf::FloatRect Ball::getGlobalBounds()
{
	return this->ball.getGlobalBounds();
}

sf::Vector2f Ball::getBallDir()
{
	sf::Vector2f tempDirection(this->dir_x, this->dir_y);
	return tempDirection;
}

void Ball::setBallDirection(float _dir_x, float _dir_y)
{
	this->dir_x = _dir_x;
	this->dir_y = _dir_y;
}

void Ball::setPlaying(bool _value)
{
	this->playing = _value;
}

void Ball::update()
{
	if (this->playing)
	{
		this->ball.setPosition(
			this->ball.getPosition().x + (dir_x * BALL_SPEED),
			this->ball.getPosition().y + (dir_y * BALL_SPEED)
		);

		if (this->ball.getGlobalBounds().left > 400)
			ball.setFillColor(sf::Color::Blue);
		else if (this->ball.getGlobalBounds().width < 400)
			ball.setFillColor(sf::Color::Red);
	}
}

void Ball::draw(sf::RenderWindow & _window)
{
	_window.draw(ball);
}
