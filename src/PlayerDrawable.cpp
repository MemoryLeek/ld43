#include <iostream>
#include <random>
#include <numeric>

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

	m_decayShader.setUniform("decay", m_player.decay() / DECAY);
}

sf::Sprite PlayerDrawable::spriteForDirection() const
{
	const sf::Vector2i &direction = m_player.direction();
	const sf::Vector2f &velocity = m_player.velocity();

	const int runningIndex = (int)(m_elapsed * 20) % 4;

	if (direction.y < 0)
	{
		return m_spriteSheetMapper.get(SpriteId::PlayerLookingUp, 0);
	}

	if (direction.y > 0)
	{
		return m_spriteSheetMapper.get(SpriteId::PlayerLookingDown, 0);
	}

	if (direction.x < 0)
	{
		if (velocity.x == 0)
		{
			return m_spriteSheetMapper.get(SpriteId::PlayerIdleLeft, 0);
		}

		return m_spriteSheetMapper.get(SpriteId::PlayerRunningLeft, runningIndex);
	}

	if (velocity.x == 0)
	{
		return m_spriteSheetMapper.get(SpriteId::PlayerIdleRight, 0);
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
