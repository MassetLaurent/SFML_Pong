#ifndef RACKET
#define RACKET

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "State.h"

class Racket
{
private:
	GameDataRef data;
	sf::Texture racketTexture;
	sf::Sprite racketSprite;
	std::string playerType;

public:
	Racket();
	virtual ~Racket();

	sf::FloatRect getGlobalBounds();

	void init(std::string _playerType);
	void updatePosition(int _dir_y);
	void draw(sf::RenderWindow &_window);
};

#endif // !RACKET
