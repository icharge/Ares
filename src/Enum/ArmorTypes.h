#ifndef ARMORS_H
#define ARMORS_H

#include <ArrayClasses.h>
#include <CCINIClass.h>
#include <WarheadTypeClass.h>

#include <Conversions.h>

#include "../Ext/WarheadType/Body.h"
#include "../Ares.h"
#include "../Ares.CRT.h"

#include "_Enumerator.hpp"

class ArmorType;

class ArmorType  : public Enumerable<ArmorType>
{
	public:
		int DefaultIndex;
		WarheadTypeExt::VersesData DefaultVerses;

	ArmorType(const char *Title) {
		AresCRT::strCopy(this->Name, Title, 31);
		DefaultIndex = -1;
		Array.AddItem(this);
	}

	virtual ~ArmorType() {
		ArmorType *placeholder = this;
		Array.RemoveItem(Array.FindItemIndex(&placeholder));
	}

	virtual void LoadFromINI(CCINIClass *pINI);

	static void LoadForWarhead(CCINIClass *pINI, WarheadTypeClass* pWH);
	static void AddDefaults();
};

#endif
