#ifndef GOALSTATE_H
#define GOALSTATE_H

#include "IState.h"

class GoalState : public IState
{
	public:
		GoalState();

		void update(float delta) override;
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		void keyPressed(const sf::Event &event) override;
		void keyReleased(const sf::Event &event) override;

		void mouseButtonPressed(const sf::Event &event) override;
		void mouseButtonReleased(const sf::Event &event) override;

		void joystickButtonPressed(const sf::Event &event) override;
		void joystickButtonReleased(const sf::Event &event) override;

	private:
		sf::Texture m_congratulations;
};

#endif // GOALSTATE_H
