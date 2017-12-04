// author Emmett Byrne
// date 25-11-17
#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>


class AnimateSplash
{
public:
	AnimateSplash();
	~AnimateSplash();

	void update(sf::Time t);
	void render(sf::RenderWindow &window);
	bool isPaused();
	bool isFinished();

private:
	bool m_paused; //Is the animation paused
	bool m_finished; //Is the animation finished

	sf::Font m_font; //Text font being used
	sf::Text m_text; //The title text

	sf::Texture m_texture; //Background texture
	sf::Sprite m_background; //Background sprite object

	sf::Vector2f m_textPosition; //position of title text
	sf::Vector2f m_spritePosition; //Background position
	sf::Vector2f m_velocity; //Velocity of background
	sf::Vector2f m_gravity; //Gravity vector

	int m_currentKeyFrame; //the current keyframe that is playing

};

