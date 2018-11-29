#ifndef STATETRANSITION_H
#define STATETRANSITION_H

class IState;

class StateTransition
{
	public:
		StateTransition(IState *current, IState *next, long duration);

		IState *update(long delta);

		float progress() const;

	private:
		IState *m_current;
		IState *m_next;

		float m_duration;
		float m_remaining;
};


#endif // STATETRANSITION_H
