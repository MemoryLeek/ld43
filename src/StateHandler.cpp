#include <cmath>

#include "StateHandler.h"
#include "Utility.h"

#include "states/LogoState.h"
#include "states/TransitionState.h"

StateHandler::StateHandler()
	: m_state(new LogoState(*this))
{
}

void StateHandler::keyPressed(const sf::Event::KeyEvent &event)
{
	m_state->keyPressed(event);
}

void StateHandler::keyReleased(const sf::Event::KeyEvent &event)
{
	m_state->keyReleased(event);
}

void StateHandler::update(long delta)
{
	m_state->update(delta);
}

void StateHandler::changeState(IState *next, long duration)
{
	m_state = new TransitionState(*this, *m_state, *next, duration);
}

void StateHandler::changeState(IState *next)
{
	m_state = next;
}

void StateHandler::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(states);

	target.draw(*m_state);
}