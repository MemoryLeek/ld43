#include "DummyState.h"
#include "Utility.h"

void DummyState::keyPressed(const sf::Event::KeyEvent &event)
{
	UNUSED(event);
}

void DummyState::keyReleased(const sf::Event::KeyEvent &event)
{
	UNUSED(event);
}

void DummyState::update(long delta)
{
	UNUSED(delta);
}

void DummyState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(states);

	target.clear(sf::Color::Red);
}
