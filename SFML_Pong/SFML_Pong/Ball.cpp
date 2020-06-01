#include <time.h>
#include <iostream>

#include "Ball.h"
#include "Definitions.h"

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
	this->ball.setFillColor(sf::Color::White);
	this->ball.setPosition(398.f, 320.f);

	//init ball directions
	srand(static_cast<unsigned>(time(NULL)));

	// direction X
	int tempDirection = rand() % 80 + 20;

	if (tempDirection % 2 == 0)
		dir_x = (float)tempDirection;
	else
		dir_x = -(float)tempDirection;

	//direction Y
	tempDirection = rand() % 100;

	if (tempDirection % 2 == 0)
		dir_y = (float)tempDirection;
	else
		dir_y = -(float)tempDirection;

	this->speed = 0;
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

float Ball::getSpeed()
{
	return this->speed;
}

void Ball::setBallDirection(float _dir_x, float _dir_y)
{
	this->dir_x = _dir_x;
	this->dir_y = _dir_y;

	this->speed = static_cast<unsigned>(this->dir_x);
	if (this->speed < 0)
		this->speed = speed * -1;
}

void Ball::setPlaying(bool _value)
{
	this->playing = _value;
}

void Ball::update(const float _dt)
{
	if (this->playing)
	{
		this->ball.setPosition(
			this->ball.getPosition().x + (dir_x * BALL_SPEED * _dt),
			this->ball.getPosition().y + (dir_y * BALL_SPEED * _dt)
		);

		if (this->ball.getGlobalBounds().left > 400.f)
			ball.setFillColor(sf::Color::Blue);
		else if (this->ball.getGlobalBounds().width < 400.f)
			ball.setFillColor(sf::Color::Red);
	}
}

void Ball::draw(sf::RenderWindow & _window)
{
	_window.draw(ball);
}
