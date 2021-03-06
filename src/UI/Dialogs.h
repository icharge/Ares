#ifndef ARES_DIALOGS_H
#define ARES_DIALOGS_H
#include "registered.h"
#include <WWMouseClass.h>
#include <UI.h>

class Dialogs {
public:

	static const char *StatusString;
	static wchar_t ExceptDetailedMessage[0x400];
	static const int ExceptControlID;

	static void TakeMouse() {
		WWMouseClass::Instance->ReleaseMouse();
		Imports::ShowCursor(1);
	}

	static void ReturnMouse() {
		Imports::ShowCursor(0);
		WWMouseClass::Instance->CaptureMouse();
	}
};

#endif
