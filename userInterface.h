#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "modules.h";

class UImoduleSettings {
	int numberOfSettings;
	UImoduleSettings(int numberOfSettings_);
public:
	vector<vector<string>> settings; // stores all the settings and setting types

	void addToggleSetting();
	void addKeySetting();
	void addNumberSetting();
	void addDirectionSetting();

	void getSetting();
};



#endif
