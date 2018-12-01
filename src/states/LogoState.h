#ifndef LOGOSTATE_H
#define LOGOSTATE_H

#include "DummyState.h"
#include "IState.h"

class StateHandler;

class LogoState : public IState
{
	public:
		LogoState(StateHandler &stateHandler, Settings &settings, const sf::Texture& spriteSheet);

		void keyPressed(const sf::Event &event) override;
		void keyReleased(const sf::Event &event) override;

		void mouseButtonPressed(const sf::Event &event) override;
		void mouseButtonReleased(const sf::Event &event) override;

		void update(float delta) override;

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	private:
		void nextState();

		sf::Texture m_logo;

		DummyState m_dummyState;
		StateHandler &m_stateHandler;

		float m_duration;
};


#endif // LOGOSTATE_H
