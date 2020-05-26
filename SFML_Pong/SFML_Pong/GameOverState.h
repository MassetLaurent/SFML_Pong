#ifndef GAMEOVERSTATE
#define GAMEOVERSTATE

#include "Game.h"
#include "State.h"

class GameOverState : public State
{
private:
	GameDataRef data;


public:
	GameOverState(GameDataRef _data);
	virtual ~GameOverState();

	void init();

	void handleInput();
	void update(const float &dt);
	void render(const float &dt);
};

#endif // !GAMEOVERSTATE
