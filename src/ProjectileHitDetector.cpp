#include <iostream>

#include "IMovableActor.h"
#include "EnemyPool.h"
#include "IMapInformationProvider.h"
#include "Player.h"

#include "ProjectileHitDetector.h"

ProjectileHitDetector::ProjectileHitDetector(const IMapInformationProvider& mapInformationProvider, const EnemyPool& enemyPool, Player& player)
	: m_mapInformationProvider(mapInformationProvider)
	, m_enemyPool(enemyPool)
	, m_player(player)
{
}

const Enemy* ProjectileHitDetector::queryForEnemyHit(const sf::Vector2u& origin, Direction direction) const
{
	for (const auto& enemy : m_enemyPool.enemies())
	{
		const auto cb = getCollisionBoxInWorldSpace(enemy);
		if (!checkIfTargetIsInLine(origin, direction, cb))
		{
			continue;
		}
		if (checkIfObstructed(origin, direction, sf::Vector2u(cb.left + cb.width / 2, cb.top + cb.height / 2)))
		{
			continue;
		}

		return &enemy;
	}

	return nullptr;
}

const Player* ProjectileHitDetector::queryForPlayerHit(const sf::Vector2u& origin, Direction direction) const
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
		if (origin.y < target.top || origin.y > target.top + target.height)
		{
			return false;
		}
	}

	if (direction == Direction::Up || direction == Direction::Down)
	{
		// Check that we're verticalo
		if (origin.x < target.left || origin.x > target.left + target.width)
		{
			return false;
		}
	}

	switch (direction)
	{
		case Direction::Left:
			return target.left < origin.x;
		case Direction::Right:
			return target.left + target.width > origin.x;
		case Direction::Up:
			return target.top < origin.y;
		case Direction::Down:
			return target.top + target.height > origin.y;
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
			for (int x = originTile.x; x > targetTile.x; x--)
			{
				if (m_mapInformationProvider.isCollidable(x, originTile.y))
				{
					return true;
				}
			}
			break;
		case Direction::Right:
			for (int x = originTile.x; x < targetTile.x; x++)
			{
				if (m_mapInformationProvider.isCollidable(x, originTile.y))
				{
					return true;
				}
			}
			break;
		case Direction::Up:
			for (int y = originTile.y; y > targetTile.y; y--)
			{
				if (m_mapInformationProvider.isCollidable(originTile.x, y))
				{
					return true;
				}
			}
			break;
		case Direction::Down:
			for (int y = originTile.y; y < targetTile.y; y++)
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
