#include "DummyState.h"
#include "Utility.h"
#include "PlayerDrawable.h"

DummyState::DummyState(const sf::Texture& spriteSheet)
	: m_spriteSheetMapper(spriteSheet)
	, m_map("resources/maps/1.tmx", spriteSheet)
{
}

void DummyState::keyPressed(const sf::Event::KeyEvent &event)
{
	if (event.code == sf::Keyboard::A)
	{
		m_player.setVelocity(-1);
	}

	if (event.code == sf::Keyboard::D)
	{
		m_player.setVelocity(1);
	}

	if (event.code == sf::Keyboard::J)
	{
		m_mapVelocity.x = -1;
	}

	if (event.code == sf::Keyboard::L)
	{
		m_mapVelocity.x = 1;
	}

	if (event.code == sf::Keyboard::I)
	{
		m_mapVelocity.y = -1;
	}

	if (event.code == sf::Keyboard::K)
	{
		m_mapVelocity.y = 1;
	}
}

void DummyState::keyReleased(const sf::Event::KeyEvent &event)
{
	UNUSED(event);

	m_player.setVelocity(0);
	m_mapVelocity = sf::Vector2f();
}

void DummyState::update(float delta)
{
	UNUSED(delta);

	m_player.update(delta);
	m_map.moveOffset(m_mapVelocity);
}

void DummyState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(states);

	PlayerDrawable playerDrawable(m_player, m_spriteSheetMapper);

	target.clear(sf::Color::Red);
	target.draw(m_map);
	target.draw(playerDrawable);
}
