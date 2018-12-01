#ifndef ENEMYDRAWABLE_H
#define ENEMYDRAWABLE_H

#include <SFML/Graphics/Drawable.hpp>

#include "IUpdatable.h"

class Enemy;
class SpriteSheetMapper;

class EnemyDrawable : public sf::Drawable, public IUpdatable
{
	public:
		EnemyDrawable(const Enemy& enemy, const SpriteSheetMapper& spriteSheetMapper);

		void update(float delta) override;

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		const Enemy &m_enemy;
		const SpriteSheetMapper &m_spriteSheetMapper;

		float m_elapsed;

};

#endif // ENEMYDRAWABLE_H
