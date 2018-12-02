#include "GoalState.h"
#include "Utility.h"

GoalState::GoalState()
{
	m_congratulations.loadFromFile("resources/congratulations.png");
}

void GoalState::update(float delta)
{
	UNUSED(delta);
}

void GoalState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(states);

	const sf::Vector2u &imageSize = m_congratulations.getSize();
	const sf::Vector2u &windowSize = target.getSize();

	sf::Sprite sprite(m_congratulations);
	sprite.setPosition((windowSize.x - imageSize.x) / 2, (windowSize.y - imageSize.y) / 2);

	target.setView(target.getDefaultView());
	target.clear(sf::Color::Black);
	target.draw(sprite);
}

void GoalState::keyPressed(const sf::Event &event)
{
	UNUSED(event);
}

void GoalState::keyReleased(const sf::Event &event)
{
	UNUSED(event);
}

void GoalState::mouseButtonPressed(const sf::Event &event)
{
	UNUSED(event);
}

void GoalState::mouseButtonReleased(const sf::Event &event)
{
	UNUSED(event);
}
