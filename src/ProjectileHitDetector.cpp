#include <iostream>

#include "IMovableActor.h"
#include "EnemyPool.h"
#include "IMapInformationProvider.h"
#include "Player.h"

#include "ProjectileHitDetector.h"

ProjectileHitDetector::ProjectileHitDetector(const IMapInformationProvider& mapInformationProvider, EnemyPool& enemyPool, Player& player)
	: m_mapInformationProvider(mapInformationProvider)
	, m_enemyPool(enemyPool)
	, m_player(player)
{
}

Enemy* ProjectileHitDetector::queryForEnemyHit(const sf::Vector2u& origin, Direction direction) const
{
	for (auto enemy : m_enemyPool.enemies())
	{
		const auto cb = getCollisionBoxInWorldSpace(*enemy);
		if (!checkIfTargetIsInLine(origin, direction, cb))
		{
			continue;
		}
		if (checkIfObstructed(origin, direction, sf::Vector2u(cb.left + cb.width / 2, cb.top + cb.height / 2)))
		{
			continue;
		}

		return enemy;
	}

	return nullptr;
}

Player* ProjectileHitDetector::queryForPlayerHit(const sf::Vector2u& origin, Direction direction) const
{
	const auto cb = getCollisionBoxInWorldSpace(m_player);
	if (checkIfTargetIsInLine(origin, direction, cb)
		&& !checkIfObstructed(origin, direction, sf::Vector2u(cb.left + cb.width / 2, cb.top + cb.height / 2)))
	{
		return &m_player;
	}

	return nullptr;
}

sf::IntRect ProjectileHitDetector::getCollisionBoxInWorldSpace(const IMovableActor& actor) const
{
	const auto& unOffsettedPosition = actor.position();
	const auto& localCollisionBox = actor.collisionBox();

	return sf::IntRect(unOffsettedPosition.x + localCollisionBox.left
		, unOffsettedPosition.y + localCollisionBox.top
		, localCollisionBox.width
		, localCollisionBox.height);
}

bool ProjectileHitDetector::checkIfTargetIsInLine(const sf::Vector2u& origin, Direction direction, const sf::IntRect& target) const
{
	if (direction == Direction::Left || direction == Direction::Right)
	{
		// Check that we're horizoontal
		if ((int)origin.y < (target.top - 4) || (int)origin.y > (target.top + target.height + 4))
		{
			return false;
		}
	}

	if (direction == Direction::Up || direction == Direction::Down)
	{
		// Check that we're verticalo
		if ((int)origin.x < target.left || (int)origin.x > target.left + target.width)
		{
			return false;
		}
	}

	switch (direction)
	{
		case Direction::Left:
			return target.left < (int)origin.x;
		case Direction::Right:
			return target.left + target.width > (int)origin.x;
		case Direction::Up:
			return target.top < (int)origin.y;
		case Direction::Down:
			return target.top + target.height > (int)origin.y;
	}

	return false;
}

bool ProjectileHitDetector::checkIfObstructed(const sf::Vector2u& origin, Direction direction, const sf::Vector2u& target) const
{
	const auto originTile = Utility::correctTilePosition(origin.x, origin.y);
	const auto targetTile = Utility::correctTilePosition(target.x, target.y);

	switch (direction)
	{
		case Direction::Left:
			for (unsigned int x = originTile.x; x > targetTile.x; x--)
			{
				if (m_mapInformationProvider.isCollidable(x, originTile.y))
				{
					return true;
				}
			}
			break;
		case Direction::Right:
			for (unsigned int x = originTile.x; x < targetTile.x; x++)
			{
				if (m_mapInformationProvider.isCollidable(x, originTile.y))
				{
					return true;
				}
			}
			break;
		case Direction::Up:
			for (unsigned int y = originTile.y; y > targetTile.y; y--)
			{
				if (m_mapInformationProvider.isCollidable(originTile.x, y))
				{
					return true;
				}
			}
			break;
		case Direction::Down:
			for (unsigned int y = originTile.y; y < targetTile.y; y++)
			{
				if (m_mapInformationProvider.isCollidable(originTile.x, y))
				{
					return true;
				}
			}
			break;
	}

	return false;
}
