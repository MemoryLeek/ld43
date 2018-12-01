#ifndef SETTINGSPROVIDER_H
#define SETTINGSPROVIDER_H

#include "ISettingsProvider.h"
#include "DefaultSettingsProvider.h"

class SettingsProvider : public ISettingsProvider
{
	const char *FILENAME = "settings.dat";

	public:
		SettingsProvider();

		Settings load() const override;

		void save(const Settings &settings) override;

	private:
		DefaultSettingsProvider m_fallbackProvider;
};

#endif // SETTINGSPROVIDER_H
