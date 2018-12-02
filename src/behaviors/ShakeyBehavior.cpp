#include "ShakeyBehavior.h"
#include "Utility.h"
#include "IMapInformationProvider.h"
#include "IBehaviorControllable.h"
#include "SpriteSheetMapper.h"
#include "ProjectileHitDetector.h"
#include "Player.h"

ShakeyBehavior::ShakeyBehavior(const IMapInformationProvider &mapInformationProvider
	, const ProjectileHitDetector &projectileHitDetector
	, Player& player
	)
	: m_mapInformationProvider(mapInformationProvider)
	, m_projectileHitDetector(projectileHitDetector)
	, m_player(player)
{
}

void ShakeyBehavior::update(float delta)
{
	for (auto &pair : m_states)
	{
		pair.second.elapsed += delta;
	}
}

std::array<sf::Vector2u, 2> ShakeyBehavior::getTilesToCheck(int direction, const sf::Vector2f &position) const
{
	if (direction == 0)
	{
		return
		{
			sf::Vector2u(floor(position.x / TILE_SIZE), position.y / TILE_SIZE),
			sf::Vector2u(floor(position.x / TILE_SIZE), position.y / TILE_SIZE + 1),
		};
	}

	return
	{
		sf::Vector2u(ceil(position.x / TILE_SIZE), position.y / TILE_SIZE),
		sf::Vector2u(ceil(position.x / TILE_SIZE), position.y / TILE_SIZE + 1),
	};
}

bool ShakeyBehavior::shouldChangeDirection(int direction, IBehaviorControllable &actor) const
{
	const auto &position = actor.position();
	const auto &tilesToCheck = getTilesToCheck(direction, position);

	if (m_mapInformationProvider.isCollidable(tilesToCheck[0].x, tilesToCheck[0].y))
	{
		return true;
	}

	if (m_mapInformationProvider.isCollidable(tilesToCheck[1].x, tilesToCheck[1].y))
	{
		return false;
	}

	return true;
}

ShakeyState ShakeyBehavior::getShakeyState(const IBehaviorControllable &actor) const
{
	static ShakeyState invalid;

	const auto &iterator = m_states.find(&actor);

	if (iterator == m_states.end())
	{
		return invalid;
	}

	return (*iterator).second;
}

SpriteId ShakeyBehavior::getSpriteId(const ShakeyState &state) const
{
	if (state.state == 1)
	{
		if (state.direction == 0)
		{
			return SpriteId::ShakeyPreparingLeft;
		}

		return SpriteId::ShakeyPreparingRight;
	}

	if (state.state == 2)
	{
		if (state.direction == 0)
		{
			return SpriteId::ShakeyChargingLeft;
		}

		return SpriteId::ShakeyChargingRight;
	}

	if (state.direction == 0)
	{
		return SpriteId::ShakeyWalkingLeft;
	}

	return SpriteId::ShakeyWalkingRight;
}

int ShakeyBehavior::getSpriteIndex(const ShakeyState &state) const
{
	if (state.state == 1)
	{
		return (int)(state.elapsed * 5) % 4;
	}

	return (int)(state.elapsed * 10) % 4;
}

void ShakeyBehavior::invokeOnActor(IBehaviorControllable &actor)
{
	auto &state = m_states[&actor];

	if (shouldChangeDirection(state.direction, actor))
	{
		state.state = 0;
		state.direction = !state.direction;
	}

	const sf::Vector2u eyePosition(actor.position() + sf::Vector2f(16, 16));

	if (state.state == 0)
	{
		if (m_projectileHitDetector.queryForPlayerHit(eyePosition, (Direction)state.direction))
		{
			state.elapsed = 0;
			state.state = 1;
		}
	}

	if (state.state == 0)
	{
		actor.move((Direction)state.direction, 0.2f);
	}

	if (state.state == 1)
	{
		if (state.elapsed > 0.5f)
		{
			state.state = 2;
			state.elapsed = 0;
		}
	}

	if (state.state == 2)
	{
		actor.move((Direction)state.direction, 1.0f);
	}

	const auto playerBox = sf::FloatRect(m_player.position().x + m_player.collisionBox().left
		, m_player.position().y + m_player.collisionBox().top
		, m_player.collisionBox().width
		, m_player.collisionBox().height);

	const auto collisionBox = currentCollisionBoxForActor(actor);
	const auto actorBox = sf::FloatRect(actor.position().x + collisionBox.left
		, actor.position().y + collisionBox.top
		, collisionBox.width
		, collisionBox.height);

	if (actorBox.intersects(playerBox))
	{
		m_player.damage(DECAY / 2);
	}
}

sf::Sprite ShakeyBehavior::currentSpriteForActor(const SpriteSheetMapper &spriteSheetMapper, const IBehaviorControllable &actor) const
{
	const auto &state = getShakeyState(actor);
	const auto spriteId = getSpriteId(state);
	const auto index = getSpriteIndex(state);

	sf::Sprite sprite = spriteSheetMapper.get(spriteId, index);
	sprite.setPosition(actor.position());

	return sprite;
}

sf::FloatRect ShakeyBehavior::currentCollisionBoxForActor(const IBehaviorControllable &actor) const
{
	UNUSED(actor);

	return sf::FloatRect(12, 14, 11, 25);
}
