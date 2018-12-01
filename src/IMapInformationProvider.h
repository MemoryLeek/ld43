#ifndef ICOLLISIONINFORMATIONPROVIDER_H
#define ICOLLISIONINFORMATIONPROVIDER_H

#include <vector>

#include "SpawnPoint.h"

class IMapInformationProvider
{
	public:
		virtual bool isCollidable(const unsigned int tx, const unsigned int ty) const = 0;
		virtual bool isCheckpoint(const unsigned int tx, const unsigned int ty) const = 0;

		virtual std::vector<SpawnPoint> spawnPoints() const = 0;
};

#endif // ICOLLISIONINFORMATIONPROVIDER_H
