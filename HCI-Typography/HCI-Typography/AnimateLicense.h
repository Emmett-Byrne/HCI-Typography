// author Emmett Byrne
// date 28-11-17
#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

enum class AnimType
{
	move,
	somersault
};

struct KeyFrameLicense
{
	sf::Time m_duration; //How long the keyframe lasts
	sf::Time m_timePassed; //The amount of time that the keyframe has been playing for
	sf::Vector2f m_startPositionTitle; //The starting position of the title for the keyframe
	sf::Vector2f m_targetPositionTitle; //The end position of the title for the keyframe
	sf::Vector2f m_startPositionSub; //The starting position of the subText for the keyframe
	sf::Vector2f m_targetPositionSub; //The end position of the subText for the keyframe
	AnimType m_type; //The type of animation
	sf::Vector2f grav = sf::Vector2f(0.0f, 9.8f);
	sf::Vector2f vel;
	float initialVelocity;
	float height = 50;
	float angle = 45;
};

class AnimateLicense
{
public:
	AnimateLicense(sf::Vector2f tPos, sf::Vector2f sPos);
	~AnimateLicense();

	void update(sf::Time t);
	void render(sf::RenderWindow &window);

	void setupSomersault();

	void setKeyframe(int key, sf::Time dur, sf::Vector2f tPos, sf::Vector2f sPos, AnimType type);

	bool isPaused();

private:
	bool m_paused; //Is the animation paused

	sf::Font m_font; //Text font being used
	sf::Text m_title; //The title text
	sf::Text m_sub; //The Subtext

	sf::Vector2f m_titlePosition; //position of title text
	sf::Vector2f m_subPosition; //position of sub text

	KeyFrameLicense m_keyframe[4]; //array of all the keyframes
	int m_currentKeyFrame; //the current keyframe that is playing

	void move(sf::Time t);
	void somersault(sf::Time t);
};

