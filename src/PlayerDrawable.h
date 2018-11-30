#ifndef PLAYERDRAWABLE_H
#define PLAYERDRAWABLE_H

#include <SFML/Graphics.hpp>

class Player;
class SpriteSheetMapper;

class PlayerDrawable : public sf::Drawable
{
	public:
		PlayerDrawable(const Player &player, const SpriteSheetMapper &spriteSheetMapper);

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	private:
		const Player &m_player;
		const SpriteSheetMapper &m_spriteSheetMapper;
};

#endif // PLAYERDRAWABLE_H
