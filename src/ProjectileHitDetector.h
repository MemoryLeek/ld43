#ifndef PROJECTILEHITDETECTOR_H
#define PROJECTILEHITDETECTOR_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "Utility.h"

class IMapInformationProvider;
class EnemyPool;
class Enemy;
class Player;
class IMovableActor;

class ProjectileHitDetector
{
	public:
		ProjectileHitDetector(const IMapInformationProvider& mapInformationProvider, const EnemyPool& enemyPool, class Player& player);

		const Enemy* queryForEnemyHit(const sf::Vector2u& origin, Direction direction) const;
		const Player* queryForPlayerHit(const sf::Vector2u& origin, Direction direction) const;

	private:
		const IMapInformationProvider& m_mapInformationProvider;
		const EnemyPool& m_enemyPool;
		const Player& m_player;

		sf::IntRect getCollisionBoxInWorldSpace(const IMovableActor& actor) const;

		bool checkIfTargetIsInLine(const sf::Vector2u& origin, Direction direction, const sf::IntRect& target) const;
		bool checkIfObstructed(const sf::Vector2u& origin, Direction direction, const sf::IntRect& target) const;
};

#endif // PROJECTILEHITDETECTOR_H
