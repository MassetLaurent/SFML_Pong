#ifndef SPLASHSTATE
#define SPLASHSTATE

#include "Game.h"
#include "State.h"

class SplashState : public State
{
private:
	GameDataRef data;
	sf::Texture splash;
	sf::Sprite splashSprite;
	sf::Clock splashClock;

public:
	SplashState(GameDataRef _data);
	virtual ~SplashState();

	void init();

	void handleInput();
	void update(const float &dt);
	void render(const float &dt);
};

#endif // !SPLASHSTATE
