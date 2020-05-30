#ifndef AI
#define AI

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "State.h"

class Ai
{
private:
	sf::Texture racketTexture;
	sf::Sprite racketSprite;

public:
	Ai();
	virtual ~Ai();

	sf::FloatRect getGlobalBounds();

	void init(std::string _playerType);
	void updatePosition(int _dir_y);
	void draw(sf::RenderWindow &_window);
};

#endif // !AI
