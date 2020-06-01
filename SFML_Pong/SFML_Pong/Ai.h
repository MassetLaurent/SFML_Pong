#ifndef AI
#define AI

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "State.h"
#include "Ball.h"

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
	void updatePosition(Ball& _ball, sf::RenderWindow& _window);
	void draw(sf::RenderWindow &_window);
};

#endif // !AI
