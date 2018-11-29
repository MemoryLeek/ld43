#include <cmath>

#include "TransitionState.h"
#include "StateHandler.h"
#include "Utility.h"

TransitionState::TransitionState(StateHandler &stateHandler, IState &subject, IState &next, long duration)
	: m_stateHandler(stateHandler)
	, m_subject(subject)
	, m_next(next)
	, m_duration(duration)
	, m_remaining(duration)
{
}

void TransitionState::keyPressed(const sf::Event::KeyEvent &event)
{
	UNUSED(event);
}

void TransitionState::keyReleased(const sf::Event::KeyEvent &event)
{
	UNUSED(event);
}

void TransitionState::update(long delta)
{
	if ((m_remaining -= delta) <= 0)
	{
		m_stateHandler.changeState(&m_next);
	}
}

void TransitionState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(states);

	IState &state = getCurrentState();

	target.draw(state);

	const float progress = std::max(0.0f, m_remaining / m_duration);
	const float alpha = sin(progress * M_PI) * 255;

	sf::RectangleShape rectangle(sf::Vector2f(target.getSize()));
	rectangle.setFillColor(sf::Color(0, 0, 0, alpha));

	target.draw(rectangle);
}

IState &TransitionState::getCurrentState() const
{
	if (m_remaining <= (m_duration / 2))
	{
		return m_next;
	}

	return m_subject;
}
