#include <iostream>

#include "LogoState.h"
#include "DummyState.h"
#include "StateHandler.h"
#include "Utility.h"

LogoState::LogoState(StateHandler &stateHandler, Settings &settings, const sf::Texture& spriteSheet)
	: m_dummyState(settings, spriteSheet, stateHandler)
	, m_stateHandler(stateHandler)
	, m_duration(0.0f)
{
	m_logo.loadFromFile("resources/logo.png");
}

void LogoState::keyPressed(const sf::Event &event)
{
	UNUSED(event);

	nextState();
}

void LogoState::keyReleased(const sf::Event &event)
{
	UNUSED(event);
}

void LogoState::mouseButtonPressed(const sf::Event &event)
{
	UNUSED(event);
}

void LogoState::mouseButtonReleased(const sf::Event &event)
{
	UNUSED(event);
}

void LogoState::joystickButtonPressed(const sf::Event &event)
{
	UNUSED(event);

	nextState();
}

void LogoState::joystickButtonReleased(const sf::Event &event)
{
	UNUSED(event);
}

void LogoState::update(float delta)
{
	if ((m_duration += delta) >= 1)
	{
		nextState();
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

void LogoState::nextState()
{
	m_stateHandler.changeState(&m_dummyState, 0.5f);
}
