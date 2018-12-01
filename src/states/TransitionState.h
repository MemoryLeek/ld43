#ifndef TRANSITIONSTATE_H
#define TRANSITIONSTATE_H

#include "IState.h"

class StateHandler;

class TransitionState : public IState
{
	public:
		TransitionState(StateHandler &stateHandler, IState &subject, IState &next, float duration);

		void keyPressed(const sf::Event &event) override;
		void keyReleased(const sf::Event &event) override;

		void mouseButtonPressed(const sf::Event &event) override;
		void mouseButtonReleased(const sf::Event &event) override;

		void update(float delta) override;

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	private:
		IState &getCurrentState() const;

		StateHandler &m_stateHandler;

		IState &m_subject;
		IState &m_next;

		float m_duration;
		float m_remaining;
};

#endif // TRANSITIONSTATE_H
