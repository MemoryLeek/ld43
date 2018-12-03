#include "Enemy.h"
#include "SpriteSheetMapper.h"
#include "EnemyPool.h"
#include "EnemyDrawable.h"

#include "behaviors/IEnemyBehavior.h"

EnemyDrawable::EnemyDrawable(const EnemyPool& enemyPool, const SpriteSheetMapper& spriteSheetMapper)
	: m_enemyPool(enemyPool)
	, m_spriteSheetMapper(spriteSheetMapper)
{
	m_enemyShader.loadFromFile("resources/shaders/enemy.frag", sf::Shader::Fragment);
}

void EnemyDrawable::update(float delta)
{
	UNUSED(delta);


}

void EnemyDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	UNUSED(states);

	for (const auto& enemy : m_enemyPool.enemies())
	{
		const auto deathTimer = enemy->deathTimer();

		if (enemy->isDead() && deathTimer <= 0)
		{
			continue;
		}

		if (deathTimer > 0)
		{
			m_enemyShader.setUniform("opacity", deathTimer / 0.5f);
		}
		else
		{
			m_enemyShader.setUniform("opacity", 1.0f);
		}

		const auto& sprite = enemy->behavior().currentSpriteForActor(m_spriteSheetMapper, *enemy);
		target.draw(sprite, &m_enemyShader);
	}
}
