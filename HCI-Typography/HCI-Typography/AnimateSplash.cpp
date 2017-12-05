#include "AnimateSplash.h"



AnimateSplash::AnimateSplash() :
	m_spritePosition(400, -300),
	m_textPosition(900, 300),
	m_textStart(900, 300),
	m_slideTarget(400, 300),
	m_exitTarget(400, -300),
	m_gravity (0, 9.8f * 400),
	m_currentKeyFrame(0)
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

	m_slideDuration = sf::seconds(1.0f);
	m_exitDuration = sf::seconds(1.0f);
}


AnimateSplash::~AnimateSplash()
{
}

void AnimateSplash::update(sf::Time t)
{
	if (m_currentKeyFrame == 0)
	{
		fall(t);
	}
	if (m_currentKeyFrame == 1)
	{
		slide(t);
	}
	if (m_currentKeyFrame == 2)
	{
		exit(t);
	}

	m_text.setPosition(m_textPosition);
	m_background.setPosition(m_spritePosition);
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

void AnimateSplash::play()
{
	m_paused = true;
}

void AnimateSplash::fall(sf::Time t)
{
	m_velocity = m_velocity + m_gravity * t.asSeconds();
	m_spritePosition += m_velocity * t.asSeconds() + (m_gravity * (t.asSeconds() * t.asSeconds()) * 0.5f);

	if (m_spritePosition.y > 300)
	{
		m_velocity *= -1.0f;
		m_velocity *= 0.5f;
		if (m_velocity.y < 25.0f && m_velocity.y > -25.0f)
		{
			m_currentKeyFrame++;
			m_timer = sf::Time::Zero;

			
		}
		m_spritePosition.y = 300;
	}
}

void AnimateSplash::slide(sf::Time t)
{
	sf::Vector2f moveText(m_slideTarget - m_textStart);

	float scaler = m_slideDuration.asSeconds() / t.asSeconds();
	moveText /= scaler;

	m_textPosition += moveText;

	m_timer += t;

	if (m_timer >= m_slideDuration)
	{
		m_paused = true;
		m_currentKeyFrame++;
		m_textPosition = m_slideTarget;
		m_timer = sf::Time::Zero;
	}
}

void AnimateSplash::exit(sf::Time t)
{
	sf::Vector2f move(m_exitTarget - m_slideTarget);

	float scaler = m_exitDuration.asSeconds() / t.asSeconds();
	move /= scaler;

	m_textPosition += move;
	m_spritePosition += move;

	m_timer += t;

	if (m_timer >= m_exitDuration)
	{
		m_finished = true;
		m_currentKeyFrame++;
	}
}