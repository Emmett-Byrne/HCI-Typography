#include "AnimateSplash.h"



AnimateSplash::AnimateSplash()
{
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\background.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_background.setTexture(m_texture);
	m_background.setOrigin(400, 300);
	m_background.setPosition(400, -300);

	if (!m_font.loadFromFile("ASSETS\\FONTS\\AYearWithoutRain.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_text.setFont(m_font);
	m_text.setString("Click to Continue");
	m_text.setStyle(sf::Text::Bold);
	m_text.setCharacterSize(30);
	m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
}


AnimateSplash::~AnimateSplash()
{
}

void AnimateSplash::render(sf::RenderWindow & window)
{
	window.draw(m_background);
	window.draw(m_text);
}

bool AnimateSplash::isPaused()
{
	return m_paused;
}

bool AnimateSplash::isFinished()
{
	return m_finished;
}
