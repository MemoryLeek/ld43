#include <algorithm>
#include <iostream>

#include "Utility.h"

#include "ICollisionInformationProvider.h"
#include "Player.h"

constexpr int SIZE = 32;
constexpr float JUMPVELOCITY = 2.5f;

Player::Player(const ICollisionInformationProvider& collisionInformationProvider)
	: m_collisionInformationProvider(collisionInformationProvider)
	, m_position(0, 0)
	, m_velocity(0, 0)
	, m_mass(1)
	, m_direction(0)
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

	if (y() == currentTile.y * SIZE)
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

	const auto isHittingWallLeft = m_collisionInformationProvider.isCollidable(currentTile.x - 1, currentTile.y) && x() < currentTile.x * SIZE;
	const auto isHittingWallRight = m_collisionInformationProvider.isCollidable(currentTile.x + 1, currentTile.y) && x() > currentTile.x * SIZE;

	if (isHittingWallLeft || isHittingWallRight)
	{
		m_position.x = currentTile.x * SIZE;
	}
	else
	{
		m_position.x += m_velocity.x * (delta * 200);
	}

	m_position.y += m_velocity.y * (delta * 200);

	const auto isGrounded = m_collisionInformationProvider.isCollidable(currentTile.x, currentTile.y + 1) && y() >= currentTile.y * SIZE;
	const auto isHittingHead = m_collisionInformationProvider.isCollidable(currentTile.x, currentTile.y - 1) && y() < currentTile.y * SIZE;

	if (isGrounded || isHittingHead)
	{
		m_velocity.y = 0;
		m_position.y = currentTile.y * SIZE;
	}
	else
	{
		m_velocity.y += (delta * GRAVITY * m_mass);
	}
}

sf::Vector2i Player::tilePosition() const
{
	return sf::Vector2i((x() + SIZE / 2) / SIZE, (y() + SIZE / 2) / SIZE);
}
