#include <iostream>

#include "LogoState.h"
#include "DummyState.h"
#include "StateHandler.h"
#include "Utility.h"

LogoState::LogoState(StateHandler &stateHandler)
	: m_stateHandler(stateHandler)
	, m_duration(0)
{
	m_logo.loadFromFile("resources/logo.png");
}

void LogoState::update(long delta)
{
	static DummyState dummyState;

	if ((m_duration += delta) >= 2000)
	{
		m_stateHandler.changeState(&dummyState, 1000);
	}
}

void LogoState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(states);

	const sf::Vector2u &imageSize = m_logo.getSize();
	const sf::Vector2u &windowSize = target.getSize();

	sf::Sprite sprite(m_logo);
	sprite.setPosition((windowSize.x - imageSize.x) / 2, (windowSize.y - imageSize.y) / 2);

	target.clear(sf::Color::White);
	target.draw(sprite);
}
