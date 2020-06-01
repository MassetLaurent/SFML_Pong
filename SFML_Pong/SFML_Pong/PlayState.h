#ifndef PLAYSTATE
#define PLAYSTATE

#include "Game.h"
#include "State.h"
#include "Racket.h"
#include "Ball.h"
#include "Ai.h"

class PlayState : public State
{
private:
	GameDataRef data;

	sf::Font font;
	sf::Text pongText, playerScoreText, player2ScoreText, ballSpeedText;

	sf::Texture backgroundTexture, infosTexture, terrainBorderTexture;
	sf::Sprite backgroundSprite, infosSprite, borderTop, borderBottom, middelLine;

	sf::Clock restartBall;

	Racket player, player2;
	Ai ai;
	Ball ball;

	int score, player2Score;
	bool showHelp, twoPlayers;

public:
	PlayState(GameDataRef _data, bool _twoPlayers = false);
	virtual ~PlayState();

	void init();
	void showInfos();
	void updateScore();
	void updateBallDirection();


	void handleInput();
	void update(const float &dt);
	void render(const float &dt);
};

#endif // !PLAYSTATE
