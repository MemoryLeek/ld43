#include "KeyMapping.h"

KeyMapping::KeyMapping()
	: m_key(-1)
	, m_joystickButton(-1)
	, m_mouseButton(-1)
{
}

int KeyMapping::key() const
{
	return m_key;
}

KeyMapping &KeyMapping::setKey(int key)
{
	m_key = key;

	return *this;
}

int KeyMapping::joystickButton() const
{
	return m_joystickButton;
}

KeyMapping &KeyMapping::setJoystickButton(int joystickButton)
{
	m_joystickButton = joystickButton;

	return *this;
}

int KeyMapping::mouseButton() const
{
	return m_mouseButton;
}

KeyMapping &KeyMapping::setMouseButton(int mouseButton)
{
	m_mouseButton = mouseButton;

	return *this;
}

void KeyMapping::keyPressed() const
{
	m_onPress();
}

void KeyMapping::keyReleased() const
{
	m_onRelease();
}

BinaryStream &operator >>(BinaryStream &stream, KeyMapping &keyMapping)
{
	stream >> keyMapping.m_key;
	stream >> keyMapping.m_joystickButton;
	stream >> keyMapping.m_mouseButton;

	return stream;
}

BinaryStream &operator <<(BinaryStream &stream, const KeyMapping &keyMapping)
{
	stream << keyMapping.m_key;
	stream << keyMapping.m_joystickButton;
	stream << keyMapping.m_mouseButton;

	return stream;
}
