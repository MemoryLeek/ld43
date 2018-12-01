#include "DummyState.h"
#include "Utility.h"
#include "PlayerDrawable.h"
#include "Settings.h"

DummyState::DummyState(Settings &settings, const sf::Texture& spriteSheet)
	: m_settings(settings)
	, m_spriteSheetMapper(spriteSheet)
	, m_map("resources/maps/1.tmx", spriteSheet)
{
	InputMapping &inputMapping = settings
		.inputMapping();

	inputMapping
		.left()
		.onPress(m_player, &Player::moveLeft)
		.onRelease(m_player, &Player::stopMoving);

	inputMapping
		.right()
		.onPress(m_player, &Player::moveRight)
		.onRelease(m_player, &Player::stopMoving);
}

void DummyState::keyPressed(const sf::Event &event)
{
	KeyMapping *mapping = m_settings
		.inputMapping()
		.find(event);

	if (mapping)
	{
		mapping->keyPressed();
	}
}

void DummyState::keyReleased(const sf::Event &event)
{
	KeyMapping *mapping = m_settings
		.inputMapping()
		.find(event);

	if (mapping)
	{
		mapping->keyReleased();
	}
}

void DummyState::update(float delta)
{
	UNUSED(delta);

	m_player.update(delta);
}

void DummyState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(states);

	PlayerDrawable playerDrawable(m_player, m_spriteSheetMapper);

	target.clear(sf::Color::Red);
	target.draw(m_map);
	target.draw(playerDrawable);
}
