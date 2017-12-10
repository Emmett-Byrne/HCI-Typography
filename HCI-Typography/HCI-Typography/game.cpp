/// author Emmett Byrne
// date 25-11-17

#include "Game.h"
#include <iostream>



Game::Game() :
	m_window{ sf::VideoMode{ 800, 600, 32 }, "Typography Animation" },
	m_exitGame{false}, //when true game will exit
	m_author{ sf::Vector2f{ 900, 270 }, sf::Vector2f{ -100, 320 } },
	m_license{ sf::Vector2f{ 900, 270 }, sf::Vector2f{ -100, 320 } },
	m_producer{ sf::Vector2f{ 400, 700 }, sf::Vector2f{ 400, -100 } }
{
	if (!LevelLoader::load(1, m_creditsData))
	{
		return;
	}

	m_author.setKeyframe(0, sf::seconds(.5f), sf::Vector2f(450, 270), sf::Vector2f(350, 320));
	m_author.setKeyframe(1, sf::seconds(2.0f), sf::Vector2f(350, 270), sf::Vector2f(450, 320));
	m_author.setKeyframe(2, sf::seconds(.5f), sf::Vector2f(-100, 270), sf::Vector2f(900, 320));

	m_license.setKeyframe(0, sf::seconds( .5f ), sf::Vector2f( 900, 270 ), sf::Vector2f( 400, 320 ), AnimType::move);
	m_license.setKeyframe(1, sf::seconds( .5f ), sf::Vector2f( 500, 270 ), sf::Vector2f( 400, 320 ), AnimType::move);
	m_license.setKeyframe(2, sf::seconds( 1.0f ), sf::Vector2f( 400, 270 ), sf::Vector2f( 400, 320 ), AnimType::somersault);
	m_license.setKeyframe(3, sf::seconds( .5f ), sf::Vector2f(-100, 270), sf::Vector2f(900, 320), AnimType::move);

	m_producer.setKeyframe(0, sf::seconds(.5f), sf::Vector2f(400, 320), sf::Vector2f(400, 270));
	m_producer.setKeyframe(1, sf::seconds(.5f), sf::Vector2f(400, 320), sf::Vector2f(400, 270));
	m_producer.setKeyframe(2, sf::seconds(.5f), sf::Vector2f(250, 320), sf::Vector2f(400, 270));
	m_producer.setKeyframe(3, sf::seconds(.5f), sf::Vector2f(250, 320), sf::Vector2f(400, 270));
	m_producer.setKeyframe(4, sf::seconds(.5f), sf::Vector2f(250, 220), sf::Vector2f(400, 270));
	m_producer.setKeyframe(5, sf::seconds(.5f), sf::Vector2f(250, 220), sf::Vector2f(400, 270));
	m_producer.setKeyframe(6, sf::seconds(.5f), sf::Vector2f(400, 220), sf::Vector2f(400, 270));
	m_producer.setKeyframe(7, sf::seconds(.5f), sf::Vector2f(400, 220), sf::Vector2f(400, 270));
	m_producer.setKeyframe(8, sf::seconds(.5f), sf::Vector2f(400, 270), sf::Vector2f(400, 320));
	m_producer.setKeyframe(9, sf::seconds(.5f), sf::Vector2f(400, 270), sf::Vector2f(400, 320));
	m_producer.setKeyframe(10, sf::seconds(.5f), sf::Vector2f(400, -100), sf::Vector2f(400, 700));
}


Game::~Game()
{
}


void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if ( sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	m_splash.update(t_deltaTime);
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_splash.render(m_window);
	m_window.display();
}
