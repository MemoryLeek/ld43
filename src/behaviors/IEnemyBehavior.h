#ifndef IENEMYBEHAVIOR_H
#define IENEMYBEHAVIOR_H

#include <SFML/Graphics/Sprite.hpp>

#include "IUpdatable.h"

class IBehaviorControllable;
class SpriteSheetMapper;

class IEnemyBehavior : public IUpdatable
{
	public:
		virtual void invokeOnActor(IBehaviorControllable& actor) = 0;
		virtual sf::Sprite currentSpriteForActor(const SpriteSheetMapper& spriteSheetMapper, const IBehaviorControllable& actor) const = 0;
};

#endif // IENEMYBEHAVIOR_H
