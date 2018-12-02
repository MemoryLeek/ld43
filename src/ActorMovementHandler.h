#ifndef ACTORMOVEMENTHANDLER_H
#define ACTORMOVEMENTHANDLER_H

#include <SFML/System/Vector2.hpp>

class IMovableActor;
class IMapInformationProvider;

class ActorMovementHandler
{
	public:
		static void updateActorPosition(IMovableActor& actor, const IMapInformationProvider& mapInformationProvider, float delta);
		static bool isOnGround(IMovableActor& actor, const IMapInformationProvider& mapInformationProvider);

	private:
		static bool isInsideWall(const IMapInformationProvider& mapInformationProvider, const sf::Vector2f& point);
};

#endif // ACTORMOVEMENTHANDLER_H
