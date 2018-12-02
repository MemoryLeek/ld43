#include <iostream>

#include "ActorMovementHandler.h"
#include "Utility.h"
#include "IMapInformationProvider.h"
#include "behaviors/IEnemyBehavior.h"

#include "Enemy.h"

Enemy::Enemy(IEnemyBehavior& behavior, const IMapInformationProvider& m_mapInformationProvider)
	: m_behavior(behavior)
	, m_mapInformationProvider(m_mapInformationProvider)
	, m_isDead(true)
{
}

IEnemyBehavior& Enemy::behavior() const
{
	return m_behavior;
}

void Enemy::kill()
{
	m_isDead = true;
}

bool Enemy::isDead() const
{
	return m_isDead;
}

void Enemy::respawn(const sf::Vector2f& position)
{
	m_position = position;
	m_isDead = false;
}

void Enemy::update(float delta)
{
	UNUSED(delta);

	ActorMovementHandler::updateActorPosition(*this, m_mapInformationProvider, delta);

	if (!m_isDead)
	{
		m_behavior.invokeOnActor(*this);
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
