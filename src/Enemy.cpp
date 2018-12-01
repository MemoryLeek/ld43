#include "ActorMovementHandler.h"
#include "Utility.h"
#include "IMapInformationProvider.h"
#include "behaviors/IEnemyBehavior.h"

#include "Enemy.h"

Enemy::Enemy(IEnemyBehavior& behavior, const IMapInformationProvider& m_mapInformationProvider)
	: m_behavior(behavior)
	, m_mapInformationProvider(m_mapInformationProvider)
	, m_position(96, 0)
{
}

void Enemy::update(float delta)
{
	UNUSED(delta);

	ActorMovementHandler::updateActorPosition(*this, m_mapInformationProvider, delta);

	m_behavior.invokeOnActor(*this);
}

sf::Vector2f Enemy::position() const
{
	return m_position;
}

void Enemy::setPosition(sf::Vector2f position)
{
	m_position = position;
}

sf::Vector2f Enemy::velocity() const
{
	return m_velocity;
}

void Enemy::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}

float Enemy::mass() const
{
	return 1.f;
}

void Enemy::jump(float velocity)
{
	const sf::Vector2u currentTile = Utility::tilePosition(m_position.x, m_position.y);
	if (!m_mapInformationProvider.isCollidable(currentTile.x, currentTile.y + 1))
	{
		return;
	}

	if ((int)m_position.y == (int)currentTile.y * TILE_SIZE)
	{
		m_velocity.y = -velocity;
	}
}

void Enemy::move(Direction direction, float velocity)
{
	switch (direction)
	{
		case Direction::Left:
			m_velocity.x = -velocity;
			break;
		case Direction::Right:
			m_velocity.x = velocity;
			break;
	}
}
