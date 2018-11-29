#include <algorithm>

#include "StateTransition.h"

StateTransition::StateTransition(IState *current, IState *next, long duration)
	: m_current(current)
	, m_next(next)
	, m_duration(duration)
	, m_remaining(duration)
{
}

IState *StateTransition::update(long delta)
{
	if ((m_remaining -= delta) <= (m_duration / 2))
	{
		return m_next;
	}

	return m_current;
}

float StateTransition::progress() const
{
	return std::max(m_remaining / m_duration, 0.0f);
}
