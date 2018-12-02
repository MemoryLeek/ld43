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

	static std::vector<sf::Uint32> elements(TILE_SIZE * TILE_SIZE);

	for (sf::Uint8 x = 0; x < TILE_SIZE; x++)
	{
		for (sf::Uint8 y = 0; y < TILE_SIZE; y++)
		{
			const sf::Uint8 pixel[] =  { x, y, 0, 0 };

			elements[x + (y * TILE_SIZE)] = *(sf::Uint32 *)pixel;
		}
	}

	std::shuffle(begin(elements), end(elements), generator);

	sf::Image image;
	image.create(TILE_SIZE, TILE_SIZE, (sf::Uint8 *)elements.data());

	m_decayTexture.loadFromImage(image);

	m_decayShader.loadFromFile("resources/shaders/decay.frag", sf::Shader::Fragment);
	m_decayShader.setUniform("lookup", m_decayTexture);
}

void PlayerDrawable::update(float delta)
{
	m_elapsed += delta;

	m_decayShader.setUniform("decay", m_player.decay() / DECAY);


	const auto opacity = m_player.isInvulnerable()
		? ((int)(m_elapsed * 10) % 2) * .6f
		: 1.f;

	m_decayShader.setUniform("opacity", opacity);
}

sf::Sprite PlayerDrawable::spriteForDirection() const
{
	const sf::Vector2i &direction = m_player.direction();
	const sf::Vector2f &velocity = m_player.velocity();

	const int runningIndex = getSpriteIndex();

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
			if (m_player.isShooting())
			{
				return m_spriteSheetMapper.get(SpriteId::PlayerIdleLeftShooting, 0);
			}

			return m_spriteSheetMapper.get(SpriteId::PlayerIdleLeft, 0);
		}

		if (m_player.isShooting())
		{
			return m_spriteSheetMapper.get(SpriteId::PlayerRunningLeftShooting, runningIndex);
		}

		return m_spriteSheetMapper.get(SpriteId::PlayerRunningLeft, runningIndex);
	}

	if (velocity.x == 0)
	{
		if (m_player.isShooting())
		{
			return m_spriteSheetMapper.get(SpriteId::PlayerIdleRightShooting, 0);
		}

		return m_spriteSheetMapper.get(SpriteId::PlayerIdleRight, 0);
	}

	if (m_player.isShooting())
	{
		return m_spriteSheetMapper.get(SpriteId::PlayerRunningRightShooting, runningIndex);
	}

	return m_spriteSheetMapper.get(SpriteId::PlayerRunningRight, runningIndex);
}

int PlayerDrawable::getSpriteIndex() const
{
	if (m_player.velocity().y != 0)
	{
		return 0;
	}

	return (int)(m_elapsed * 20) % 4;
}

void PlayerDrawable::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(states);

	sf::Sprite sprite = spriteForDirection();
	sprite.setPosition(m_player.x(), m_player.y());

	target.draw(sprite, &m_decayShader);
}
