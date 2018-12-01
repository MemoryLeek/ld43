#include "Utility.h"

#include "SpawnPoint.h"

SpawnPoint::SpawnPoint(const std::string& name, const sf::Vector2f& position)
	: m_type(SpawnTypeResolver::resolve(name))
	, m_position(position.x - TILE_SIZE / 2, position.y - TILE_SIZE)
{
}

SpawnType SpawnPoint::type() const
{
	return m_type;
}

sf::Vector2f SpawnPoint::position() const
{
	return m_position;
}
