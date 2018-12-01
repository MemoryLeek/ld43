#include "EnemyPool.h"
#include "SpriteSheetMapper.h"
#include "behaviors/IEnemyBehavior.h"

#include "EnemyDrawable.h"

EnemyDrawable::EnemyDrawable(const EnemyPool& enemyPool, const SpriteSheetMapper& spriteSheetMapper)
	: m_enemyPool(enemyPool)
	, m_spriteSheetMapper(spriteSheetMapper)
{
}

void EnemyDrawable::update(float delta)
{
	UNUSED(delta);
}

void EnemyDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& enemy : m_enemyPool.enemies())
	{
		if (enemy.isDead())
		{
			continue;
		}

		const auto& sprite = enemy.behavior().currentSpriteForActor(m_spriteSheetMapper, enemy);
		target.draw(sprite, states);
	}
}
