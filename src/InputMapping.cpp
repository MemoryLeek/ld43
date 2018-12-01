#include "InputMapping.h"

KeyMapping &InputMapping::up()
{
	return m_up;
}

KeyMapping &InputMapping::down()
{
	return m_down;
}

KeyMapping &InputMapping::left()
{
	return m_left;
}

KeyMapping &InputMapping::right()
{
	return m_right;
}

KeyMapping &InputMapping::jump()
{
	return m_jump;
}

KeyMapping &InputMapping::shoot()
{
	return m_shoot;
}

KeyMapping *InputMapping::find(const sf::Event &event)
{
	static KeyMapping *mappings[]
	{
		&m_up,
		&m_down,
		&m_left,
		&m_right,
		&m_jump,
		&m_shoot,
	};

	for (KeyMapping *mapping : mappings)
	{
		const int key = mapping->key();
		const int joystickButton = mapping->joystickButton();
		const int mouseButton = mapping->mouseButton();

		switch (event.type)
		{
			case sf::Event::JoystickButtonPressed:
			case sf::Event::JoystickButtonReleased:
			{
				if (joystickButton == (int)event.joystickButton.button)
				{
					return mapping;
				}

				break;
			}

			case sf::Event::KeyPressed:
			case sf::Event::KeyReleased:
			{
				if (key == event.key.code)
				{
					return mapping;
				}

				break;
			}

			case sf::Event::MouseButtonPressed:
			case sf::Event::MouseButtonReleased:
			{
				if (mouseButton == event.mouseButton.button)
				{
					return mapping;
				}
			}

			default:
			{
				break;
			}
		}
	}

	return nullptr;
}

BinaryStream &operator >>(BinaryStream &stream, InputMapping &inputMapping)
{
	stream >> inputMapping.m_up;
	stream >> inputMapping.m_down;
	stream >> inputMapping.m_left;
	stream >> inputMapping.m_right;
	stream >> inputMapping.m_jump;
	stream >> inputMapping.m_shoot;

	return stream;
}

BinaryStream &operator <<(BinaryStream &stream, const InputMapping &inputMapping)
{
	stream << inputMapping.m_up;
	stream << inputMapping.m_down;
	stream << inputMapping.m_left;
	stream << inputMapping.m_right;
	stream << inputMapping.m_jump;
	stream << inputMapping.m_shoot;

	return stream;
}
