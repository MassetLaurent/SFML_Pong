#ifndef PLAYSTATE
#define PLAYSTATE

#include "Game.h"
#include "State.h"
#include "Racket.h"
#include "Ball.h"

class PlayState : public State
{
private:
	GameDataRef data;

	sf::Font font;
	sf::Text pongText;
	sf::Text playerScoreText;
	sf::Text aiScoreText;

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
	Racket ai;
	Ball ball;

	void updateBallDirection();
	int score, aiScore;
	bool showHelp;

public:
	PlayState(GameDataRef _data);
	virtual ~PlayState();

	void init();
	void showInfos();
	void updateScore();


	void handleInput();
	void update(const float &dt);
	void render(const float &dt);
};

#endif // !PLAYSTATE
