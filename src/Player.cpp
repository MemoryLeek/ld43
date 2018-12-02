#include <algorithm>
#include <iostream>
#include <assert.h>

#include "Utility.h"

#include "ActorMovementHandler.h"
#include "Enemy.h"
#include "EnemyPool.h"
#include "IMapInformationProvider.h"
#include "ProjectileHitDetector.h"
#include "Player.h"

constexpr float JUMPVELOCITY = 2.5f;
constexpr float INVULNERABILITY_TIME = 2.f;

Player::Player(const IMapInformationProvider& collisionInformationProvider, const ProjectileHitDetector& projectileHitDetector, EnemyPool& enemyPool)
	: m_collisionInformationProvider(collisionInformationProvider)
	, m_projectileHitDetector(projectileHitDetector)
	, m_enemyPool(enemyPool)
	, m_position(0, 0)
	, m_velocity(0, 0)
	, m_lastCheckpointTilePosition(0, 0)
	, m_direction(0, 0)
	, m_decay(DECAY)
	, m_safeTimer(0)
	, m_shootTimer(0)
{
}

int Player::x() const
{
	return m_position.x;
}

void Player::setX(int x)
{
	m_position.x = x;
}

int Player::y() const
{
	return m_position.y;
}

void Player::setY(int y)
{
	m_position.y = y;
}

sf::Vector2i Player::direction() const
{
	return m_direction;
}

Direction Player::shootDirection() const
{
	if (m_direction.y < 0)
	{
		return Direction::Up;
	}
	else if (m_direction.y > 0)
	{
		return Direction::Down;
	}
	else if (m_direction.x < 0)
	{
		return Direction::Left;
	}

	return Direction::Right;
}

sf::FloatRect Player::collisionBox() const
{
	return sf::FloatRect(9, 10, 14 ,22);
}

sf::Vector2f Player::velocity() const
{
	return m_velocity;
}

void Player::setVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}

int Player::decay() const
{
	return m_decay;
}

void Player::damage(float decay)
{
	if (m_safeTimer > 0)
	{
		// We're still invuln
		return;
	}

	m_decay -= decay;

	if (m_decay > 0)
	{
		m_safeTimer = INVULNERABILITY_TIME;
	}
}

bool Player::isInvulnerable() const
{
	return m_safeTimer > 0;
}

bool Player::isShooting() const
{
	return m_shootTimer > 0;
}

float Player::mass() const
{
	return m_decay / DECAY / 2 + .5f;
}

sf::Vector2f Player::position() const
{
	return m_position;
}

void Player::setPosition(sf::Vector2f position)
{
	m_position = position;
}

void Player::moveLeft()
{
	m_velocity.x = -1;
	m_direction.x = -1;
}

void Player::stopMovingLeft()
{
	if (m_velocity.x < 0)
	{
		m_velocity.x = 0;
	}
}

void Player::moveRight()
{
	m_velocity.x = 1;
	m_direction.x = 1;
}

void Player::stopMovingRight()
{
	if (m_velocity.x > 0)
	{
		m_velocity.x = 0;
	}
}

void Player::lookUp()
{
	m_direction.y = -1;
}

void Player::lookDown()
{
	m_direction.y = 1;
}

void Player::resetLook()
{
	m_direction.y = 0;
}

void Player::jump()
{
	if (!ActorMovementHandler::isOnGround(*this, m_collisionInformationProvider))
	{
		return;
	}

	m_velocity.y = -JUMPVELOCITY;
}

void Player::stopJumping()
{
}

void Player::shoot()
{
	const auto gunPosition = sf::Vector2u(m_position.x + TILE_SIZE / 2, m_position.y + TILE_SIZE / 2);
	auto* result = m_projectileHitDetector.queryForEnemyHit(gunPosition, shootDirection());

	if (result)
	{
		result->kill();
		m_decay = std::min(DECAY, m_decay + DAMAGE);
	}

	m_shootTimer = 0.2;
}

void Player::stopShooting()
{
}

void Player::update(float delta)
{
	const sf::Vector2u currentTile = Utility::tilePosition(x(), y());

	if (m_collisionInformationProvider.isCheckpoint(currentTile.x, currentTile.y) && m_lastCheckpointTilePosition != currentTile)
	{
		std::cout << "Hit new checkpoint: " << currentTile.x << "x" << currentTile.y << std::endl;
		m_lastCheckpointTilePosition = currentTile;
	}

	const auto& cb = collisionBox();
	const auto globalBoundingBox = sf::FloatRect(m_position.x + cb.left, m_position.y + cb.top, cb.width, cb.height);
	if (m_collisionInformationProvider.intersectsKillzone(globalBoundingBox))
	{
		damage(DECAY / 2);
	}

	ActorMovementHandler::updateActorPosition(*this, m_collisionInformationProvider, delta);

	m_decay -= abs(m_velocity.x) * delta;

	if (m_decay <= 0)
	{
		respawn();
	}

	if (m_safeTimer > 0)
	{
		m_safeTimer -= delta;
	}

	if (m_shootTimer > 0)
	{
		m_shootTimer -= delta;
	}
}

void Player::respawn()
{
	m_position = sf::Vector2f(m_lastCheckpointTilePosition.x * TILE_SIZE, m_lastCheckpointTilePosition.y * TILE_SIZE);
	m_decay = DECAY;

	m_enemyPool.respawnAll();
}
