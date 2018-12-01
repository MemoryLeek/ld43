#include <iostream>

#include "IMapInformationProvider.h"
#include "IMovableActor.h"
#include "Utility.h"

#include "ActorMovementHandler.h"

constexpr int ACTOROFFSET = 8;

void ActorMovementHandler::updateActorPosition(IMovableActor& actor, const IMapInformationProvider& mapInformationProvider, float delta)
{
	auto position = actor.position();
	auto velocity = actor.velocity();

	const auto& collisionBox = actor.collisionBox();
	const auto currentTile = Utility::tilePosition(position.x, position.y);

	const auto isHittingWallLeft = mapInformationProvider.isCollidable((int)currentTile.x - 1, (int)currentTile.y)
		&& (int)position.x + collisionBox.left < (int)currentTile.x * TILE_SIZE;

	const auto isHittingWallRight = mapInformationProvider.isCollidable((int)currentTile.x + 1, (int)currentTile.y)
		&& (int)position.x - collisionBox.left > (int)currentTile.x * TILE_SIZE;

	if (isHittingWallLeft)
	{
		position.x = currentTile.x * TILE_SIZE - collisionBox.left;
	}
	else if (isHittingWallRight)
	{
		position.x = currentTile.x * TILE_SIZE + collisionBox.left;
	}
	else
	{
		position.x += velocity.x * (delta * 200);
	}

	position.y += velocity.y * (delta * 200);

	const auto isGrounded = mapInformationProvider.isCollidable((int)currentTile.x, (int)currentTile.y + 1)
		&& (int)position.y >= (int)currentTile.y * TILE_SIZE;

	const auto isHittingHead = mapInformationProvider.isCollidable((int)currentTile.x, (int)currentTile.y - 1)
		&& (int)position.y + collisionBox.top < (int)currentTile.y * TILE_SIZE;

	if (isGrounded || isHittingHead)
	{
		velocity.y = 0;
		position.y = currentTile.y * TILE_SIZE;
	}
	else
	{
		velocity.y += (delta * GRAVITY * actor.mass());
	}

	actor.setPosition(position);
	actor.setVelocity(velocity);
}
