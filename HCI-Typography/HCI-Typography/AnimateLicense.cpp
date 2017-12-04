// author Emmett Byrne
// date 28-11-17
#include "AnimateLicense.h"
#include <math.h>



AnimateLicense::AnimateLicense(sf::Vector2f tPos, sf::Vector2f sPos) :
	m_paused{ false },
	m_currentKeyFrame{ 0 }
{

	if (!m_font.loadFromFile("ASSETS\\FONTS\\AYearWithoutRain.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_title.setFont(m_font);
	m_sub.setFont(m_font);

	m_title.setString("TitleText");
	m_sub.setString("SubText");

	m_title.setStyle(sf::Text::Bold);

	m_title.setCharacterSize(30);
	m_sub.setCharacterSize(20);

	m_title.setOrigin(m_title.getLocalBounds().width / 2, m_title.getLocalBounds().height / 2);
	m_sub.setOrigin(m_sub.getLocalBounds().width / 2, m_sub.getLocalBounds().height / 2);

	m_keyframe[0].m_startPositionTitle = tPos;
	m_keyframe[0].m_startPositionSub = sPos;

	m_titlePosition = tPos;
	m_subPosition = sPos;
}

AnimateLicense::~AnimateLicense()
{
}

void AnimateLicense::update(sf::Time t)
{
	if (!m_paused)
	{
		if (m_keyframe[m_currentKeyFrame].m_timePassed < m_keyframe[m_currentKeyFrame].m_duration)
		{
			m_keyframe[m_currentKeyFrame].m_timePassed += t;

			if (m_keyframe[m_currentKeyFrame].m_type == AnimType::move)
			{
				move(t);
			}
			if (m_keyframe[m_currentKeyFrame].m_type == AnimType::somersault)
			{
				somersault(t);
			}
		}
		else
		{
			if (m_currentKeyFrame < 3)
			{
				m_titlePosition = m_keyframe[m_currentKeyFrame].m_targetPositionTitle;
				m_subPosition = m_keyframe[m_currentKeyFrame].m_targetPositionSub;

				m_keyframe[m_currentKeyFrame + 1].m_startPositionTitle = m_keyframe[m_currentKeyFrame].m_targetPositionTitle;
				m_keyframe[m_currentKeyFrame + 1].m_startPositionSub = m_keyframe[m_currentKeyFrame].m_targetPositionSub;

				m_currentKeyFrame++;
			}
			else
			{
				m_paused = true;
			}
		}
	}
	else
	{
		std::cout << "Paused" << std::endl;
	}


	m_title.setPosition(m_titlePosition);
	m_sub.setPosition(m_subPosition);
}

void AnimateLicense::render(sf::RenderWindow & window)
{
	window.draw(m_title);
	window.draw(m_sub);
}

void AnimateLicense::setKeyframe(int key, sf::Time dur, sf::Vector2f tPos, sf::Vector2f sPos, AnimType type)
{
	m_keyframe[key].m_duration = dur;
	m_keyframe[key].m_timePassed = sf::Time::Zero;
	m_keyframe[key].m_targetPositionTitle = tPos;
	m_keyframe[key].m_targetPositionSub = sPos;
	m_keyframe[key].m_type = type;

	if (type == AnimType::somersault)
	{
		float temp = m_keyframe[key].height * m_keyframe[key].grav * 2;
		m_keyframe[key].InitialVelocity = sqrt(temp);
	}
}

bool AnimateLicense::isPaused()
{
	return m_paused;
}

void AnimateLicense::move(sf::Time t)
{
	sf::Vector2f moveTitle(m_keyframe[m_currentKeyFrame].m_targetPositionTitle - m_keyframe[m_currentKeyFrame].m_startPositionTitle);
	sf::Vector2f moveSub(m_keyframe[m_currentKeyFrame].m_targetPositionSub - m_keyframe[m_currentKeyFrame].m_startPositionSub);

	float scaler = m_keyframe[m_currentKeyFrame].m_duration.asSeconds() / t.asSeconds();
	moveTitle /= scaler;
	moveSub /= scaler;

	m_titlePosition += moveTitle;
	m_subPosition += moveSub;
}

void AnimateLicense::somersault(sf::Time t)
{
	sf::Vector2f moveTitle(m_keyframe[m_currentKeyFrame].m_targetPositionTitle - m_keyframe[m_currentKeyFrame].m_startPositionTitle);
	sf::Vector2f moveSub(m_keyframe[m_currentKeyFrame].m_targetPositionSub - m_keyframe[m_currentKeyFrame].m_startPositionSub);

	float scaler = m_keyframe[m_currentKeyFrame].m_duration.asSeconds() / t.asSeconds();
	moveTitle /= scaler;
	moveSub /= scaler;

	m_titlePosition += moveTitle;
	m_subPosition += moveSub;
	
	float temp = m_keyframe[m_currentKeyFrame].InitialVelocity * m_keyframe[m_currentKeyFrame].m_timePassed.asSeconds();
	temp += m_keyframe[m_currentKeyFrame].grav / 2 * m_keyframe[m_currentKeyFrame].m_timePassed.asSeconds() * m_keyframe[m_currentKeyFrame].m_timePassed.asSeconds();
	m_titlePosition.y = m_keyframe[m_currentKeyFrame].m_startPositionTitle.y - temp;
}
