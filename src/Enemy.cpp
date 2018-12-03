#include <iostream>

#include "ActorMovementHandler.h"
#include "Utility.h"
#include "IMapInformationProvider.h"
#include "behaviors/IEnemyBehavior.h"

#include "Enemy.h"

Enemy::Enemy(IEnemyBehavior& behavior, const IMapInformationProvider& m_mapInformationProvider, const Player &player)
	: m_behavior(behavior)
	, m_mapInformationProvider(m_mapInformationProvider)
	, m_player(player)
	, m_deathTimer(0)
	, m_spawnTimer(0)
	, m_health(0)
	, m_bulletImpactDirection(Direction::Left)
{
}

IEnemyBehavior& Enemy::behavior() const
{
	return m_behavior;
}

void Enemy::kill(Direction bulletImpactDirection)
{
	if (m_health)
	{
		if (m_health--)
		{
			m_deathTimer = 0.2f;
		}
		else
		{
			m_deathTimer = 0.5f;
		}

		m_bulletImpactDirection = bulletImpactDirection;
		m_velocity.x = 0;
		m_velocity.y = 0;
	}
}

bool Enemy::isDead() const
{
	return !m_health;
}

void Enemy::respawn(const sf::Vector2f& position)
{
	m_position = position;
	m_deathTimer = 0;
	m_health = m_behavior.health();
	m_spawnTimer = 1.0f;
}

float Enemy::deathTimer() const
{
	return m_deathTimer;
}

float Enemy::spawnTimer() const
{
	return m_spawnTimer;
}

void Enemy::update(float delta)
{
	if (m_deathTimer > 0)
	{
		m_deathTimer -= delta;
	}

	if (m_spawnTimer > 0)
	{
		m_spawnTimer -= delta;
	}

	ActorMovementHandler::updateActorPosition(*this, m_mapInformationProvider, delta);

	if (m_health && m_spawnTimer <= 0)
	{
		m_behavior.invokeOnActor(*this);
	}

	if (m_deathTimer > 0)
	{
		if (m_bulletImpactDirection == Direction::Right)
		{
			m_position.x +=  delta * 80 * (m_deathTimer / 0.5f);
		}
		else
		{
			m_position.x -= delta * 80 * (m_deathTimer / 0.5f);
		}
	}
}

sf::FloatRect Enemy::collisionBox() const
{
	return m_behavior.currentCollisionBoxForActor(*this);
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
	if (ActorMovementHandler::isOnGround(*this, m_mapInformationProvider))
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
		default:
			break;
	}
}
