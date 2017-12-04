#include "AnimateSplash.h"



AnimateSplash::AnimateSplash() :
	m_spritePosition(400, -300),
	m_textPosition(900, 300),
	m_gravity (0, 9.8f * 400)
{
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\background.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_background.setTexture(m_texture);
	m_background.setOrigin(400, 300);

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

void AnimateSplash::update(sf::Time t)
{
	m_velocity = m_velocity + m_gravity * t.asSeconds();
	m_spritePosition += m_velocity * t.asSeconds() + (m_gravity * (t.asSeconds() * t.asSeconds()) * 0.5f);

	m_text.setPosition(m_textPosition);
	m_background.setPosition(m_spritePosition);
	if (m_spritePosition.y > 300)
	{
		m_velocity *= -1.0f;
		m_velocity *= 0.5f;
		if (m_velocity.y < 2.0f && m_velocity.y > -2.0f)
		{
			m_velocity.y = 0;
		}
		m_spritePosition.y = 300;

		std::cout << m_velocity.y << std::endl;
	}
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
