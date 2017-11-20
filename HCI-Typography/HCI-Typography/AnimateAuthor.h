#pragma once
#include <SFML\Graphics.hpp>

struct KeyFrame
{
	sf::Time m_duration; //How long the keyframe lasts
	sf::Time m_timePassed; //The amount of time that the keyframe has been playing for
	sf::Vector2f m_startPositionTitle; //The starting position of the title for the keyframe
	sf::Vector2f m_targetPositionTitle; //The end position of the title for the keyframe
	sf::Vector2f m_startPositionSub; //The starting position of the subText for the keyframe
	sf::Vector2f m_targetPositionSub; //The end position of the subText for the keyframe
};

class AnimateAuthor
{
public:
	AnimateAuthor();
	~AnimateAuthor();

	void update(); 
	void render(sf::RenderWindow &window);

private:
	bool m_paused; //Is the animation paused
	int m_currentKeyFrame; //the current keyframe that is playing

	sf::Text m_title; //The title text
	sf::Text m_sub; //The Subtext

	sf::Vector2f m_titlePosition; //position of title text
	sf::Vector2f m_subPosition; //position of sub text
};

