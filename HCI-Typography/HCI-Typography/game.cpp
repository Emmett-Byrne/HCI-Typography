/// author Emmett Byrne
// date 25-11-17

#include "Game.h"
#include <iostream>



Game::Game() :
	m_window{ sf::VideoMode{ 800, 600, 32 }, "Typography Animation" },
	m_exitGame{false}, //when true game will exit
	m_author{ sf::Vector2f{ 900, 270 }, sf::Vector2f{ -100, 320 } },
	m_license{ sf::Vector2f{ 900, 270 }, sf::Vector2f{ -100, 320 } }
{
	m_author.setKeyframe(0, sf::seconds(.5f), sf::Vector2f(450, 270), sf::Vector2f(350, 320));
	m_author.setKeyframe(1, sf::seconds(2.0f), sf::Vector2f(350, 270), sf::Vector2f(450, 320));
	m_author.setKeyframe(2, sf::seconds(.5f), sf::Vector2f(-100, 270), sf::Vector2f(900, 320));

	m_license.setKeyframe(0, sf::seconds( .5f ), sf::Vector2f( 900, 270 ), sf::Vector2f( 400, 320 ), AnimType::move);
	m_license.setKeyframe(1, sf::seconds( .5f ), sf::Vector2f( 500, 270 ), sf::Vector2f( 400, 320 ), AnimType::move);
	m_license.setKeyframe(2, sf::seconds( 1.0f ), sf::Vector2f( 400, 270 ), sf::Vector2f( 400, 320 ), AnimType::somersault);
	m_license.setKeyframe(3, sf::seconds( .5f ), sf::Vector2f(-100, 270), sf::Vector2f(900, 320), AnimType::move);

	setupFontAndText(); // load font 
	setupSprite(); // load texture
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

	m_license.update(t_deltaTime);
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_license.render(m_window);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);
}
