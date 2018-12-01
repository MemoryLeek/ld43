#ifndef KEYMAPPING_H
#define KEYMAPPING_H

#include "BinaryStream.h"

#include <functional>

template<typename TInstance>
using Callback = void (TInstance::*)();

class KeyMapping
{
	public:
		KeyMapping();

		int key() const;
		void setKey(int key);

		int joystickButton() const;
		void setJoystickButton(int joystickButton);

		template<typename TInstance>
		KeyMapping &onPress(TInstance &instance, Callback<TInstance> callback)
		{
			m_onPress = std::bind(callback, &instance);

			return *this;
		}

		template<typename TInstance>
		KeyMapping &onRelease(TInstance &instance, Callback<TInstance> callback)
		{
			m_onRelease = std::bind(callback, &instance);

			return *this;
		}

		void keyPressed() const;
		void keyReleased() const;

	private:
		friend BinaryStream &operator >>(BinaryStream &stream, KeyMapping &keyMapping);
		friend BinaryStream &operator <<(BinaryStream &stream, const KeyMapping &keyMapping);

		int m_key;
		int m_joystickButton;

		std::function<void()> m_onPress;
		std::function<void()> m_onRelease;
};

#endif // KEYMAPPING_H
