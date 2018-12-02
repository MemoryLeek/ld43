#ifndef SPAWNPOINT_H
#define SPAWNPOINT_H

#include <string>

#include <SFML/System/Vector2.hpp>

enum class SpawnType
{
	Unknown,
	Blob,
	Expandy,
	TurretLeft,
	TurretRight,
};

struct SpawnTypeResolver
{
	static SpawnType resolve(const std::string& name)
	{
		if (name == "blob")
		{
			return SpawnType::Blob;
		}

		if (name == "expandy")
		{
			return SpawnType::Expandy;
		}

		if (name == "turret_left")
		{
			return SpawnType::TurretLeft;
		}

		if (name == "turret_right")
		{
			return SpawnType::TurretRight;
		}

		return SpawnType::Unknown;
	}
};

class SpawnPoint
{
	public:
		SpawnPoint(const std::string& name, const sf::Vector2f& position);

		SpawnType type() const;
		sf::Vector2f position() const;

	private:
		const SpawnType m_type;
		const sf::Vector2f m_position;
};

#endif // SPAWNPOINT_H
