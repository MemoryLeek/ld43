#include <iostream>
#include <random>

#include "PlayerDrawable.h"
#include "SpriteSheetMapper.h"
#include "Utility.h"
#include "Player.h"

PlayerDrawable::PlayerDrawable(const Player &player, const SpriteSheetMapper &spriteSheetMapper)
	: m_player(player)
	, m_spriteSheetMapper(spriteSheetMapper)
	, m_elapsed(0)
{
	std::default_random_engine generator(TILE_SIZE * TILE_SIZE);

	static std::vector<float> elements(TILE_SIZE * TILE_SIZE);

	std::iota(begin(elements), end(elements), 0);
	std::shuffle(begin(elements), end(elements), generator);

	m_decayShader.loadFromFile("resources/shaders/decay.frag", sf::Shader::Fragment);
	m_decayShader.setUniformArray("lookup", elements.data(), elements.size());
}

void PlayerDrawable::update(float delta)
{
	m_elapsed += delta;

	m_decayShader.setUniform("decay", m_player.decay() / 1000.0f);
}

sf::Sprite PlayerDrawable::spriteForDirection() const
{
	const int direction = m_player.direction();
	const int velocity = (int)m_player.velocity().x;

	const int idleIndex = (int)(m_elapsed * 10) % 5;
	const int runningIndex = (int)(m_elapsed * 20) % 10;

	if (direction == -1)
	{
		if (velocity == 0)
		{
			return m_spriteSheetMapper.get(SpriteId::PlayerIdleLeft, idleIndex);
		}

		return m_spriteSheetMapper.get(SpriteId::PlayerRunningLeft, runningIndex);
	}

	if (velocity == 0)
	{
		return m_spriteSheetMapper.get(SpriteId::PlayerIdleRight, idleIndex);
	}

	return m_spriteSheetMapper.get(SpriteId::PlayerRunningRight, runningIndex);
}

void PlayerDrawable::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(states);

	sf::Sprite sprite = spriteForDirection();
	sprite.setPosition(m_player.x(), m_player.y());

	target.draw(sprite, &m_decayShader);
}
