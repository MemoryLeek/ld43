#include "DummyState.h"
#include "Utility.h"
#include "PlayerDrawable.h"
#include "Settings.h"

DummyState::DummyState(Settings &settings, const sf::Texture& spriteSheet)
	: m_settings(settings)
	, m_spriteSheetMapper(spriteSheet)
	, m_map("resources/maps/1.tmx", spriteSheet)
	, m_player(m_map)
	, m_playerDrawable(m_player, m_spriteSheetMapper)
	, m_enemyFactory(m_player, m_map)
	, m_enemyPool(m_enemyFactory, m_map)
	, m_enemyDrawable(m_enemyPool, m_spriteSheetMapper)
	, m_projectileHitDetector(m_map, m_enemyPool, m_player)
{
	InputMapping &inputMapping = settings
		.inputMapping();

	inputMapping
		.up()
		.onPress(m_player, &Player::lookUp)
		.onRelease(m_player, &Player::resetLook);

	inputMapping
		.down()
		.onPress(m_player, &Player::lookDown)
		.onRelease(m_player, &Player::resetLook);

	inputMapping
		.left()
		.onPress(m_player, &Player::moveLeft)
		.onRelease(m_player, &Player::stopMoving);

	inputMapping
		.right()
		.onPress(m_player, &Player::moveRight)
		.onRelease(m_player, &Player::stopMoving);

	inputMapping
		.jump()
		.onPress(m_player, &Player::jump)
		.onRelease(m_player, &Player::stopJumping);

	inputMapping
		.shoot()
		.onPress(m_player, &Player::shoot)
		.onRelease(m_player, &Player::stopShooting);
}

void DummyState::keyPressed(const sf::Event &event)
{
	KeyMapping *mapping = m_settings
		.inputMapping()
		.find(event);

	if (mapping)
	{
		mapping->keyPressed();
	}
}

void DummyState::keyReleased(const sf::Event &event)
{
	KeyMapping *mapping = m_settings
		.inputMapping()
		.find(event);

	if (mapping)
	{
		mapping->keyReleased();
	}
}

void DummyState::mouseButtonPressed(const sf::Event &event)
{
	KeyMapping *mapping = m_settings
		.inputMapping()
		.find(event);

	if (mapping)
	{
		mapping->keyPressed();
	}
}

void DummyState::mouseButtonReleased(const sf::Event &event)
{
	KeyMapping *mapping = m_settings
		.inputMapping()
		.find(event);

	if (mapping)
	{
		mapping->keyReleased();
	}
}

void DummyState::update(float delta)
{
	UNUSED(delta);

	m_player.update(delta);
	m_playerDrawable.update(delta);

	m_enemyFactory.update(delta);
	m_enemyPool.update(delta);

	m_camera.setTarget(sf::Vector2f(m_player.x() + TILE_SIZE / 2, m_player.y() + TILE_SIZE / 2));
	m_camera.update(delta);
}

void DummyState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	UNUSED(states);

	auto view = target.getDefaultView();
	view.setCenter(m_camera.position());
	target.setView(view);

	target.clear(sf::Color(124, 115, 139));
	target.draw(m_map);
	target.draw(m_playerDrawable);
	target.draw(m_enemyDrawable);
}
