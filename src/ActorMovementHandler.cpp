#include "IMapInformationProvider.h"
#include "IMovableActor.h"
#include "Utility.h"

#include "ActorMovementHandler.h"

constexpr int MAX_SOLVE = 100;
constexpr int MAX_DELTA_PX = TILE_SIZE / 2;

void ActorMovementHandler::updateActorPosition(IMovableActor& actor, const IMapInformationProvider& mapInformationProvider, float delta)
{
	auto position = actor.position();
	auto velocity = actor.velocity();
	const auto& collisionBox = actor.collisionBox();

	position += velocity * delta * 200.f;

	for (int i = 0; i < MAX_SOLVE; i++)
	{
		const auto tl = sf::Vector2f(position.x + collisionBox.left, position.y + collisionBox.top);
		const auto tr = sf::Vector2f(position.x + collisionBox.left + collisionBox.width - 1, position.y + collisionBox.top);
		const auto bl = sf::Vector2f(position.x + collisionBox.left, position.y + TILE_SIZE - 1);
		const auto br = sf::Vector2f(position.x + collisionBox.left + collisionBox.width - 1, position.y + TILE_SIZE - 1);

		// Solve left
		if (velocity.x < 0 && (isInsideWall(mapInformationProvider, bl) || isInsideWall(mapInformationProvider, tl)))
		{
			for (int newX = (int)position.x + 1, attempt = 0; attempt < MAX_DELTA_PX; newX++, attempt++)
			{
				const auto nbl = sf::Vector2f(newX + collisionBox.left, position.y + TILE_SIZE - 1);
				const auto ntl = sf::Vector2f(newX + collisionBox.left, position.y + collisionBox.top);

				if (!isInsideWall(mapInformationProvider, nbl) || !isInsideWall(mapInformationProvider, ntl))
				{
					position.x = newX;
					break;
				}
			}
		}

		// Solve right
		if (velocity.x > 0 && (isInsideWall(mapInformationProvider, br) || isInsideWall(mapInformationProvider, tr)))
		{
			for (int newX = (int)position.x - 1, attempt = 0; attempt < MAX_DELTA_PX; newX--, attempt++)
			{
				const auto nbr = sf::Vector2f(newX + collisionBox.left + collisionBox.width - 1, position.y + TILE_SIZE - 1);
				const auto ntr = sf::Vector2f(newX + collisionBox.left + collisionBox.width - 1, position.y + collisionBox.top);

				if (!isInsideWall(mapInformationProvider, nbr) || !isInsideWall(mapInformationProvider, ntr))
				{
					position.x = newX;
					break;
				}
			}
		}

		break;
	}

	for (int i = 0; i < MAX_SOLVE; i++)
	{
		const auto tl = sf::Vector2f(position.x + collisionBox.left, position.y + collisionBox.top);
		const auto tr = sf::Vector2f(position.x + collisionBox.left + collisionBox.width - 1, position.y + collisionBox.top);
		const auto bl = sf::Vector2f(position.x + collisionBox.left, position.y + TILE_SIZE - 1);
		const auto br = sf::Vector2f(position.x + collisionBox.left + collisionBox.width - 1, position.y + TILE_SIZE - 1);

		// Solve floor
		if (velocity.y > 0 && (isInsideWall(mapInformationProvider, bl) || isInsideWall(mapInformationProvider, br)))
		{
			for (int newY = (int)position.y - 1, attempt = 0; attempt < MAX_DELTA_PX; newY--, attempt++)
			{
				const auto nbl = sf::Vector2f(position.x + collisionBox.left, newY + TILE_SIZE - 1);
				const auto nbr = sf::Vector2f(position.x + collisionBox.left + collisionBox.width - 1, newY + TILE_SIZE - 1);

				if (!isInsideWall(mapInformationProvider, nbl) || !isInsideWall(mapInformationProvider, nbr))
				{
					position.y = newY;
					velocity.y = 0;
					break;
				}
			}
		}

		// Solve roof
		if (velocity.y < 0 && (isInsideWall(mapInformationProvider, tl) || isInsideWall(mapInformationProvider, tr)))
		{
			for (int newY = (int)position.y + 1, attempt = 0; attempt < MAX_DELTA_PX; newY++, attempt++)
			{
				const auto ntl = sf::Vector2f(position.x + collisionBox.left, newY + collisionBox.top);
				const auto ntr = sf::Vector2f(position.x + collisionBox.left + collisionBox.width - 1, newY + collisionBox.top);

				if (!isInsideWall(mapInformationProvider, ntl) || !isInsideWall(mapInformationProvider, ntr))
				{
					position.y = newY;
					velocity.y = 0;
					break;
				}
			}
		}
	}

	actor.setPosition(position);

	if (isOnGround(actor, mapInformationProvider))
	{
		velocity.y = 0;
		position.y = Utility::correctTilePosition(position.x, position.y + TILE_SIZE - 2).y * TILE_SIZE;
	}
	else
	{
		velocity.y += (delta * GRAVITY * actor.mass());
	}

	actor.setVelocity(velocity);
}

bool ActorMovementHandler::isOnGround(IMovableActor& actor, const IMapInformationProvider& mapInformationProvider)
{
	const auto& position = actor.position();
	const auto& collisionBox = actor.collisionBox();

	const auto blf = sf::Vector2f(position.x + collisionBox.left, position.y + TILE_SIZE);
	const auto brf = sf::Vector2f(position.x + collisionBox.left + collisionBox.width - 1, position.y + TILE_SIZE);

	return isInsideWall(mapInformationProvider, blf) || isInsideWall(mapInformationProvider, brf);
}

bool ActorMovementHandler::isInsideWall(const IMapInformationProvider& mapInformationProvider, const sf::Vector2f& point)
{
	const auto tilePosition = Utility::correctTilePosition(point);
	return mapInformationProvider.isCollidable(tilePosition.x, tilePosition.y);
}
