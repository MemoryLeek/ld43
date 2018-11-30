#include "Player.h"

Player::Player()
	: m_x(0)
	, m_y(0)
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

void Player::setDirection(int direction)
{
	m_direction = direction;
}

void Player::update(float delta)
{
	m_x += m_direction * (delta * 1000);
}
