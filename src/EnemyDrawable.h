#ifndef ENEMYDRAWABLE_H
#define ENEMYDRAWABLE_H

#include <SFML/Graphics/Drawable.hpp>

#include "IUpdatable.h"

class EnemyPool;
class SpriteSheetMapper;

class EnemyDrawable : public sf::Drawable, public IUpdatable
{
	public:
		EnemyDrawable(const EnemyPool& enemyPool, const SpriteSheetMapper& spriteSheetMapper);

		void update(float delta) override;

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		mutable sf::Shader m_enemyShader;

		const EnemyPool &m_enemyPool;
		const SpriteSheetMapper &m_spriteSheetMapper;
};

#endif // ENEMYDRAWABLE_H
