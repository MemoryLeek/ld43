#include "Enemy.h"
#include "SpriteSheetMapper.h"
#include "EnemyPool.h"
#include "EnemyDrawable.h"

#include "behaviors/IEnemyBehavior.h"
#include "behaviors/TurretBehavior.h"

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

		TurretBehavior *turretBehavior = dynamic_cast<TurretBehavior *>(&enemy->behavior());

		if (turretBehavior)
		{
			const auto &bullets = turretBehavior->bullets();

			for (const auto &bullet : bullets)
			{
				sf::RectangleShape bulletRect;
				bulletRect.setPosition(sf::Vector2f(bullet.position.x - 2, bullet.position.y - 1));
				bulletRect.setSize(sf::Vector2f(5, 3));
				bulletRect.setFillColor(sf::Color(0xa69cb6ff));

				target.draw(bulletRect);
			}
		}
	}
}
