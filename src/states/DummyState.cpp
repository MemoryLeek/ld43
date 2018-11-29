#include "DummyState.h"
#include "Utility.h"

void DummyState::update(long delta)
{
	UNUSED(delta);
}

void DummyState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(target);
	UNUSED(states);
}
