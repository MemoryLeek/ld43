#include "Player.h"

Player::Player()
	: m_x(0)
	, m_y(0)
	, m_velocity(0)
	, m_direction(0)
{
}

int Player::x() const
{
	return m_x;
}

void Player::setX(int x)
{
	m_x = x;
}

int Player::y() const
{
	return m_y;
}

void Player::setY(int y)
{
	m_y = y;
}

int Player::direction() const
{
	return m_direction;
}

int Player::velocity() const
{
	return m_velocity;
}

void Player::moveLeft()
{
	m_velocity = -1;
	m_direction = -1;
}

void Player::moveRight()
{
	m_velocity = 1;
	m_direction = 1;
}

void Player::stopMoving()
{
	m_velocity = 0;
}

void Player::update(float delta)
{
	m_x += m_velocity * (delta * 200);
}
