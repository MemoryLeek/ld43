#include "SpriteSheetMapper.h"
#include "IBehaviorControllable.h"

#include "StationaryEnemyBehavior.h"

void StationaryEnemyBehavior::update(float delta)
{
}

void StationaryEnemyBehavior::invokeOnActor(IBehaviorControllable& actor)
{
}

sf::Sprite StationaryEnemyBehavior::currentSpriteForActor(const SpriteSheetMapper& spriteSheetMapper, const IBehaviorControllable& actor) const
{
	auto sprite = spriteSheetMapper.get(SpriteId::Blob, 0);
	sprite.setPosition(actor.position());
	return sprite;
}
