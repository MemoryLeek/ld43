#include <algorithm>
#include <iostream>

#include "Utility.h"

#include "ICollisionInformationProvider.h"
#include "Player.h"

constexpr int PLAYEROFFSET = 8;

constexpr float JUMPVELOCITY = 2.5f;
constexpr float DECAY = 1000.0f;

Player::Player(const ICollisionInformationProvider& collisionInformationProvider)
	: m_collisionInformationProvider(collisionInformationProvider)
	, m_position(0, 0)
	, m_velocity(0, 0)
	, m_direction(0)
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

int Player::direction() const
{
	return m_direction;
}

const sf::Vector2f& Player::velocity() const
{
	return m_velocity;
}

int Player::decay() const
{
	return m_decay;
}

float Player::mass() const
{
	return m_decay / DECAY;
}

void Player::moveLeft()
{
	m_velocity.x = -1;
	m_direction = -1;
}

void Player::moveRight()
{
	m_velocity.x = 1;
	m_direction = 1;
}

void Player::stopMoving()
{
	m_velocity.x = 0;
}

void Player::jump()
{
	const sf::Vector2i currentTile = tilePosition();
	if (!m_collisionInformationProvider.isCollidable(currentTile.x, currentTile.y + 1))
	{
		return;
	}

	if (y() == currentTile.y * TILE_SIZE)
	{
		m_velocity.y = -JUMPVELOCITY;
	}
}

void Player::stopJumping()
{
}

void Player::update(float delta)
{
	const sf::Vector2i currentTile = tilePosition();

	const auto isHittingWallLeft = m_collisionInformationProvider.isCollidable(currentTile.x - 1, currentTile.y) && x() + PLAYEROFFSET < currentTile.x * TILE_SIZE;
	const auto isHittingWallRight = m_collisionInformationProvider.isCollidable(currentTile.x + 1, currentTile.y) && x() - PLAYEROFFSET > currentTile.x * TILE_SIZE;

	if (isHittingWallLeft)
	{
		m_position.x = currentTile.x * TILE_SIZE - PLAYEROFFSET;
	}
	else if (isHittingWallRight)
	{
		m_position.x = currentTile.x * TILE_SIZE + PLAYEROFFSET;
	}
	else
	{
		m_position.x += m_velocity.x * (delta * 200);
	}

	m_position.y += m_velocity.y * (delta * 200);

	const auto isGrounded = m_collisionInformationProvider.isCollidable(currentTile.x, currentTile.y + 1) && y() >= currentTile.y * TILE_SIZE;
	const auto isHittingHead = m_collisionInformationProvider.isCollidable(currentTile.x, currentTile.y - 1) && y() + PLAYEROFFSET < currentTile.y * TILE_SIZE;

	if (isGrounded || isHittingHead)
	{
		m_velocity.y = 0;
		m_position.y = currentTile.y * TILE_SIZE;
	}
	else
	{
		m_velocity.y += (delta * GRAVITY * mass());
	}

	m_decay -= abs(m_velocity.x) * delta;
}

sf::Vector2i Player::tilePosition() const
{
	return sf::Vector2i((x() + TILE_SIZE / 2) / TILE_SIZE, (y() + TILE_SIZE - 1) / TILE_SIZE);
}
