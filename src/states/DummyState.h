#ifndef DUMMYSTATE_H
#define DUMMYSTATE_H

#include "IState.h"
#include "Camera.h"
#include "EnemyDrawable.h"
#include "Map.h"
#include "Player.h"
#include "SpriteSheetMapper.h"
#include "InputMapping.h"
#include "PlayerDrawable.h"
#include "EnemyFactory.h"
#include "EnemyPool.h"
#include "ProjectileHitDetector.h"
#include "GoalState.h"

class Settings;
class StateHandler;

class DummyState : public IState
{
	public:
		DummyState(Settings &settings, const sf::Texture& spriteSheet, StateHandler &stateHandler);

		void keyPressed(const sf::Event &event) override;
		void keyReleased(const sf::Event &event) override;

		void mouseButtonPressed(const sf::Event &event) override;
		void mouseButtonReleased(const sf::Event &event) override;

		void update(float delta) override;

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	private:
		Settings &m_settings;

		SpriteSheetMapper m_spriteSheetMapper;
		Map m_map;
		Player m_player;
		PlayerDrawable m_playerDrawable;
		Camera m_camera;
		StateHandler &m_stateHandler;
		GoalState m_goalState;

		EnemyFactory m_enemyFactory;
		EnemyPool m_enemyPool;
		EnemyDrawable m_enemyDrawable;

		ProjectileHitDetector m_projectileHitDetector;
};

#endif // DUMMYSTATE_H
