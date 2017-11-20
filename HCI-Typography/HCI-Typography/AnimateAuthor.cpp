#include "AnimateAuthor.h"



AnimateAuthor::AnimateAuthor()
{
}


AnimateAuthor::~AnimateAuthor()
{
}

void AnimateAuthor::update()
{

	m_title.setPosition(m_titlePosition);
	m_sub.setPosition(m_subPosition);
}

void AnimateAuthor::render(sf::RenderWindow & window)
{
	window.draw(m_title);
	window.draw(m_sub);
}
