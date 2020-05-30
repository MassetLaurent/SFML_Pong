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
	sf::Text pongText;
	sf::Text playerScoreText;
	sf::Text player2ScoreText;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Texture infosTexture;
	sf::Sprite infosSprite;

	sf::Texture terrainBorderTexture;

	sf::Sprite borderTop;
	sf::Sprite borderBottom;
	sf::Sprite middelLine;

	sf::Clock restartBall;

	Racket player;
	Racket player2;
	Ai ai;
	Ball ball;

	int score, player2Score;
	bool showHelp;
	bool twoPlayers;

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
