#include "DefaultSettingsProvider.h"
#include "Utility.h"

Settings DefaultSettingsProvider::load() const
{
	Settings settings;

	InputMapping &inputMapping = settings
		.inputMapping();

	inputMapping
		.left()
		.setKey(sf::Keyboard::A);

	inputMapping
		.right()
		.setKey(sf::Keyboard::D);

	return settings;
}

void DefaultSettingsProvider::save(const Settings &settings)
{
	UNUSED(settings);
}
