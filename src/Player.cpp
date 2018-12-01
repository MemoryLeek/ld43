#include <algorithm>
#include <iostream>

#include "Utility.h"

#include "ActorMovementHandler.h"
#include "IMapInformationProvider.h"
#include "Player.h"

constexpr float JUMPVELOCITY = 2.5f;
constexpr float DECAY = 5000.0f;

Player::Player(const IMapInformationProvider& collisionInformationProvider)
	: m_collisionInformationProvider(collisionInformationProvider)
	, m_position(0, 0)
	, m_velocity(0, 0)
	, m_direction(0, 0)
	, m_decay(DECAY)
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

void Player::moveRight()
{
	m_velocity.x = 1;
	m_direction.x = 1;
}

void Player::stopMoving()
{
	m_velocity.x = 0;
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
	const sf::Vector2u currentTile = Utility::tilePosition(x(), y());
	if (!m_collisionInformationProvider.isCollidable(currentTile.x, currentTile.y + 1))
	{
		return;
	}

	if (y() == (int)currentTile.y * TILE_SIZE)
	{
		m_velocity.y = -JUMPVELOCITY;
	}
}

void Player::stopJumping()
{
}

void Player::shoot()
{
	std::cout << "shoot" << std::endl;
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

	ActorMovementHandler::updateActorPosition(*this, m_collisionInformationProvider, delta);

	m_decay -= abs(m_velocity.x) * delta;
}
