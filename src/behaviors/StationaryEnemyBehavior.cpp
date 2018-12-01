#include "SpriteSheetMapper.h"
#include "IBehaviorControllable.h"

#include "StationaryEnemyBehavior.h"
#include "Utility.h"

void StationaryEnemyBehavior::update(float delta)
{
	UNUSED(delta);
}

void StationaryEnemyBehavior::invokeOnActor(IBehaviorControllable& actor)
{
	UNUSED(actor);
}

sf::Sprite StationaryEnemyBehavior::currentSpriteForActor(const SpriteSheetMapper& spriteSheetMapper, const IBehaviorControllable& actor) const
{
	auto sprite = spriteSheetMapper.get(SpriteId::Blob, 0);
	sprite.setPosition(actor.position());
	return sprite;
}

sf::FloatRect StationaryEnemyBehavior::currentCollisionBoxForActor(const IBehaviorControllable& actor) const
{
	return sf::FloatRect(4, 16, 25, 16);
}
