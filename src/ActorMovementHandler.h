#ifndef ACTORMOVEMENTHANDLER_H
#define ACTORMOVEMENTHANDLER_H

class IMovableActor;
class IMapInformationProvider;

class ActorMovementHandler
{
	public:
		static void updateActorPosition(IMovableActor& actor, const IMapInformationProvider& mapInformationProvider, float delta);
};

#endif // ACTORMOVEMENTHANDLER_H
