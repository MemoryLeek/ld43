#ifndef ICOLLISIONINFORMATIONPROVIDER_H
#define ICOLLISIONINFORMATIONPROVIDER_H

#include <vector>

#include <SFML/Graphics/Rect.hpp>

#include "SpawnPoint.h"

class IMapInformationProvider
{
	public:
		virtual bool isCollidable(const unsigned int tx, const unsigned int ty) const = 0;
		virtual bool isCheckpoint(const unsigned int tx, const unsigned int ty) const = 0;
		virtual bool intersectsKillzone(const sf::FloatRect& collisionBox) const = 0;

		virtual std::vector<SpawnPoint> spawnPoints() const = 0;
};

#endif // ICOLLISIONINFORMATIONPROVIDER_H
