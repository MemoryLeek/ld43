#include "DefaultSettingsProvider.h"
#include "Utility.h"

Settings DefaultSettingsProvider::load() const
{
	Settings settings;

	InputMapping &inputMapping = settings
		.inputMapping();

	inputMapping
		.up()
		.setKey(sf::Keyboard::W);

	inputMapping
		.down()
		.setKey(sf::Keyboard::S);

	inputMapping
		.left()
		.setKey(sf::Keyboard::A);

	inputMapping
		.right()
		.setKey(sf::Keyboard::D);

	inputMapping
		.jump()
		.setJoystickButton(0)
		.setKey(sf::Keyboard::Space);

	inputMapping
		.shoot()
		.setJoystickButton(1)
		.setKey(sf::Keyboard::LShift)
		.setMouseButton(sf::Mouse::Left);

	return settings;
}

void DefaultSettingsProvider::save(const Settings &settings)
{
	UNUSED(settings);
}
