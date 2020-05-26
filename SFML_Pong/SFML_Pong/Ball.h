#ifndef BALL
#define BALL

#include <SFML/Graphics.hpp>

class Ball
{
private:
	sf::CircleShape ball;

	bool playing;
	float dir_x, dir_y;

public:
	Ball();
	virtual ~Ball();

	void init();

	sf::FloatRect getGlobalBounds();
	sf::Vector2f getBallDir();
	void setBallDirection(float _dir_x, float _dir_y);
	void setPlaying(bool _value);

	void update();
	void draw(sf::RenderWindow &_window);
};

#endif // !BALL
