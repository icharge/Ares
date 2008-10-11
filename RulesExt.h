#ifndef RULES_EXT_H
#define RULES_EXT_H

#include <YRPP.h>
#include <MacroHelpers.h> //basically indicates that this is DCoder country
#include "Ares.h"

#include <hash_map>

class RulesClassExt
{
	public:

	class RulesClassData
	{
		public:
			bool Data_Initialized;
			void Initialize();
			RulesClassData() { this->Data_Initialized = false; }
	};

	private:
		static RulesClassData* Data;

	static RulesClassData* Global()
	{
		if(!Data)
		{
			Data = new RulesClassData();
		}
		return Data;
	};

	public:
	static void _stdcall Addition(CCINIClass* pINI);
	static void _stdcall TypeData(CCINIClass* pINI);
	static void _stdcall Load(IStream *pStm);
	static void _stdcall Save(IStream *pStm);

};

#endif