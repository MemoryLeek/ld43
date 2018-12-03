#include "TurretBehavior.h"
#include "Utility.h"
#include "SpriteSheetMapper.h"
#include "IBehaviorControllable.h"
#include "ProjectileHitDetector.h"
#include "Player.h"
#include "IMapInformationProvider.h"

TurretBehavior::TurretBehavior(int spawnDirection
	, ProjectileHitDetector &projectileHitDetector
	, const IMapInformationProvider& mapInformationProvider
	, Player &player
	)
	: m_mapInformationProvider(mapInformationProvider)
	, m_projectileHitDetector(projectileHitDetector)
	, m_player(player)
	, m_spawnDirection(spawnDirection)
{
}

void TurretBehavior::update(float delta)
{
	for (auto &state : m_states)
	{
		if ((state.second.elapsed += delta) > 3)
		{
			state.second.direction = !state.second.direction;
			state.second.elapsed = 0;
		}

		if (state.second.shootingTimer > -1)
		{
			state.second.shootingTimer -= delta;
		}
		else
		{
			state.second.shootingTimer = 0;
		}
	}

	for (auto i = m_bullets.begin(); i < m_bullets.end(); i++)
	{
		Bullet &bullet = *i;

		if (bullet.direction == Direction::Left)
		{
			bullet.position.x -= delta * 1000;
		}
		else
		{
			bullet.position.x += delta * 1000;
		}

		const auto btx = round(bullet.position.x / TILE_SIZE);
		const auto bty = round(bullet.position.y / TILE_SIZE);

		if (m_mapInformationProvider.isCollidable(btx, bty))
		{
			m_bullets.erase(i);
		}

		const sf::Vector2f &position = m_player.position();

		const sf::FloatRect bulletRect(bullet.position.x - 1, bullet.position.y - 1, 3, 3);
		const sf::FloatRect bbox(position.x, position.y + 8, TILE_SIZE, TILE_SIZE - 8);

		if (bbox.intersects(bulletRect))
		{
			m_player.damage(DECAY / 2);
			m_bullets.erase(i);
		}
	}
}

sf::Vector2u getGunPosition(IBehaviorControllable &actor, const TurretState &state)
{
	if (state.direction == 0)
	{
		return sf::Vector2u(actor.position().x + 7, actor.position().y + 27);
	}

	return sf::Vector2u(actor.position().x + TILE_SIZE - 7, actor.position().y + 27);
}

void TurretBehavior::invokeOnActor(IBehaviorControllable &actor)
{
	const auto &iterator = m_states.find(&actor);

	if (iterator == m_states.end())
	{
		m_states[&actor].direction = m_spawnDirection;
	}

	auto &state = m_states[&actor];

	if (state.shootingTimer > -1)
	{
		return;
	}

	const auto &gunPosition = getGunPosition(actor, state);
	const auto player = m_projectileHitDetector.queryForPlayerHit(gunPosition, (Direction)state.direction);

	if (player)
	{
		m_bullets.push_back({ gunPosition, (Direction)state.direction });

		state.shootingTimer = 0.2;
	}
}

sf::Sprite TurretBehavior::currentSpriteForActor(const SpriteSheetMapper &spriteSheetMapper, const IBehaviorControllable &actor) const
{
	const auto &state = getTurretState(actor);
	const auto spriteId = getSprite(state);
	const auto index = getSpriteIndex(state);

	sf::Sprite sprite = spriteSheetMapper.get(spriteId, index);
	sprite.setPosition(actor.position());

	return sprite;
}

sf::FloatRect TurretBehavior::currentCollisionBoxForActor(const IBehaviorControllable &actor) const
{
	const auto &state = getTurretState(actor);
	const auto index = getSpriteIndex(state);

	return sf::FloatRect(8, 21 - index, 15, 11 + index);
}

std::vector<Bullet> TurretBehavior::bullets() const
{
	return m_bullets;
}

TurretState TurretBehavior::getTurretState(const IBehaviorControllable &actor) const
{
	static TurretState invalid;

	const auto &iterator = m_states.find(&actor);

	if (iterator == m_states.end())
	{
		return invalid;
	}

	return (*iterator).second;
}

SpriteId TurretBehavior::getSprite(const TurretState &state) const
{
	if (state.direction == 0)
	{
		if (state.shootingTimer > 0)
		{
			return SpriteId::TurretShootingLeft;
		}

		return SpriteId::TurretLookingLeft;
	}

	if (state.shootingTimer > 0)
	{
		return SpriteId::TurretShootingRight;
	}

	return SpriteId::TurretLookingRight;
}

int TurretBehavior::getSpriteIndex(const TurretState &state) const
{
	if (state.shootingTimer > 0)
	{
		return 0;
	}

	const float start = std::max(0.0f, (0.5f - state.elapsed) / 0.5f);
	const float end = std::max(0.0f, (state.elapsed - 2.5f) / 0.5f);

	return (start + end) * 6;
}
