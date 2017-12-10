/// author Emmett Byrne
// date 25-11-17

#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "AnimateAuthor.h"
#include "AnimateLicense.h"
#include "AnimateProducer.h"
#include "AnimateSplash.h"
#include "AnimateCredits.h"
#include "LevelLoader.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	AnimateAuthor m_author;
	AnimateLicense m_license;
	AnimateProducer m_producer;
	AnimateSplash m_splash;
	AnimateCredits m_credits;

	LevelData m_creditsData;

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

};

#endif // !GAME

