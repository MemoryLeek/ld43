#ifndef PLAYERDRAWABLE_H
#define PLAYERDRAWABLE_H

#include "IUpdatable.h"

#include <SFML/Graphics.hpp>

class Player;
class SpriteSheetMapper;

class PlayerDrawable : public sf::Drawable, public IUpdatable
{
	public:
		PlayerDrawable(const Player &player, const SpriteSheetMapper &spriteSheetMapper);

		void update(float delta) override;

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	private:
		sf::Sprite spriteForDirection() const;

		const Player &m_player;
		const SpriteSheetMapper &m_spriteSheetMapper;

		float m_elapsed;
};

#endif // PLAYERDRAWABLE_H
