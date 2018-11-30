#include "DummyState.h"
#include "Utility.h"
#include "PlayerDrawable.h"

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
}

void DummyState::keyReleased(const sf::Event::KeyEvent &event)
{
	UNUSED(event);

	m_player.setVelocity(0);
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
	target.draw(playerDrawable);
}
