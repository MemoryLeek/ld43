#include "Utility.h"

#include "Camera.h"

constexpr float SPEED = 20;

Camera::Camera()
	: m_position(10 * TILE_SIZE + TILE_SIZE / 2, 6 * TILE_SIZE + TILE_SIZE / 2) // This is GREAT, it's apparently impossible to run update() before draw()
{
}

const sf::Vector2f&Camera::position() const
{
	return m_position;
}

void Camera::setTarget(const sf::Vector2f& target)
{
	m_target = target;
}

void Camera::update(float delta)
{
	m_position = Utility::lerp(m_position, m_target, delta * SPEED);
}
