// author Emmett Byrne
// date 25-11-17
#include "AnimateAuthor.h"



AnimateAuthor::AnimateAuthor(sf::Vector2f tPos, sf::Vector2f sPos) : 
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


AnimateAuthor::~AnimateAuthor()
{
}

void AnimateAuthor::update(sf::Time t)
{
	if (!m_paused)
	{
		if (m_keyframe[m_currentKeyFrame].m_timePassed < m_keyframe[m_currentKeyFrame].m_duration)
		{
			sf::Vector2f moveTitle(m_keyframe[m_currentKeyFrame].m_targetPositionTitle - m_keyframe[m_currentKeyFrame].m_startPositionTitle);
			sf::Vector2f moveSub(m_keyframe[m_currentKeyFrame].m_targetPositionSub - m_keyframe[m_currentKeyFrame].m_startPositionSub);

			float scaler = m_keyframe[m_currentKeyFrame].m_duration.asSeconds() / t.asSeconds();
			moveTitle /= scaler;
			moveSub /= scaler;

			m_titlePosition += moveTitle;
			m_subPosition += moveSub;

			m_keyframe[m_currentKeyFrame].m_timePassed += t;
		}
		else
		{
			if (m_currentKeyFrame < 2)
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

void AnimateAuthor::render(sf::RenderWindow & window)
{
	window.draw(m_title);
	window.draw(m_sub);
}

void AnimateAuthor::setKeyframe(int key, sf::Time dur, sf::Vector2f tPos, sf::Vector2f sPos)
{
	m_keyframe[key].m_duration = dur;
	m_keyframe[key].m_timePassed = sf::Time::Zero;
	m_keyframe[key].m_targetPositionTitle = tPos;
	m_keyframe[key].m_targetPositionSub = sPos;
}

bool AnimateAuthor::isPaused()
{
	return m_paused;
}
