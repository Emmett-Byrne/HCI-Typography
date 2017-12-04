// author Emmett Byrne
// date 25-11-17
#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

struct KeyFrameProducer
{
	sf::Time m_duration; //How long the keyframe lasts
	sf::Time m_timePassed; //The amount of time that the keyframe has been playing for
	sf::Vector2f m_startPositionTitle; //The starting position of the title for the keyframe
	sf::Vector2f m_targetPositionTitle; //The end position of the title for the keyframe
	sf::Vector2f m_startPositionSub; //The starting position of the subText for the keyframe
	sf::Vector2f m_targetPositionSub; //The end position of the subText for the keyframe
};

class AnimateProducer
{
public:
	AnimateProducer(sf::Vector2f tPos, sf::Vector2f sPos);
	~AnimateProducer();

	void update(sf::Time t);
	void render(sf::RenderWindow &window);

	void setKeyframe(int key, sf::Time dur, sf::Vector2f tPos, sf::Vector2f sPos);

	bool isPaused();

private:
	bool m_paused; //Is the animation paused

	sf::Font m_font; //Text font being used
	sf::Text m_title; //The title text
	sf::Text m_sub; //The Subtext

	sf::Vector2f m_titlePosition; //position of title text
	sf::Vector2f m_subPosition; //position of sub text

	KeyFrameProducer m_keyframe[11]; //array of all the keyframes
	int m_currentKeyFrame; //the current keyframe that is playing
};

