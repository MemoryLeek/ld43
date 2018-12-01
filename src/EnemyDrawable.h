#ifndef ENEMYDRAWABLE_H
#define ENEMYDRAWABLE_H

#include <SFML/Graphics/Drawable.hpp>

class Enemy;
class SpriteSheetMapper;

class EnemyDrawable : public sf::Drawable
{
	public:
		EnemyDrawable(const Enemy& enemy, const SpriteSheetMapper& spriteSheetMapper);

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		const Enemy &m_enemy;
		const SpriteSheetMapper &m_spriteSheetMapper;
};

#endif // ENEMYDRAWABLE_H
