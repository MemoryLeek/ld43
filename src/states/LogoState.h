#ifndef LOGOSTATE_H
#define LOGOSTATE_H

#include "DummyState.h"
#include "IState.h"

class StateHandler;

class LogoState : public IState
{
	public:
		LogoState(StateHandler &stateHandler);

		void keyPressed(const sf::Event::KeyEvent &event) override;
		void keyReleased(const sf::Event::KeyEvent &event) override;

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
