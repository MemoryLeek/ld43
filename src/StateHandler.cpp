#include <cmath>

#include "StateHandler.h"
#include "Utility.h"

#include "states/LogoState.h"

StateHandler::StateHandler()
	: m_transition(nullptr, new LogoState(*this), 0)
	, m_state(nullptr)
{
}

void StateHandler::keyPressed(const sf::Event::KeyEvent &event)
{
	UNUSED(event);
}

void StateHandler::keyReleased(const sf::Event::KeyEvent &event)
{
	UNUSED(event);
}

void StateHandler::update(long delta)
{
	m_state = m_transition.update(delta);

	if (m_state)
	{
		m_state->update(delta);
	}
}

void StateHandler::changeState(IState *next, long duration)
{
	m_transition = StateTransition(m_state, next, duration);
}

void StateHandler::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(states);

	if (m_state)
	{
		target.draw(*m_state);
	}

	sf::RectangleShape rectangle(sf::Vector2f(target.getSize()));
	rectangle.setFillColor(sf::Color(0, 0, 0, sin(m_transition.progress() * M_PI) * 255));

	target.draw(rectangle);
}
