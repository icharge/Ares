#ifndef CMD_AICTRL_H
#define CMD_AICTRL_H

class AIControlCommandClass : public AresCommandClass
{
public:
	//Destructor
	virtual ~AIControlCommandClass(){}

	//CommandClass
	virtual const char* GetName()
	{ return "AIControl"; }

	virtual const wchar_t* GetUIName()
	{ return L"AI Control"; }

	virtual const wchar_t* GetUICategory()
		{ return L"Ares"; }

	virtual const wchar_t* GetUIDescription()
		{ return L"Let the AI assume control."; }

	virtual void Execute(DWORD dwUnk)
	{
		if(this->CheckDebugDeactivated()) {
			return;
		}

		HouseClass* P = HouseClass::Player;

		if(P->CurrentPlayer && P->PlayerControl) {
			//let AI assume control
			P->CurrentPlayer = P->PlayerControl = false;
			P->Production = P->AutocreateAllowed = true;

			//give full capabilities
			P->IQLevel = RulesClass::Global()->MaxIQLevels;
			P->IQLevel2 = RulesClass::Global()->MaxIQLevels;
			P->AIDifficulty = 0;	//brutal!

			//notify
			MessageListClass::Instance->PrintMessage(L"AI assumed control!");

		} else {

			//re-assume control
			P->CurrentPlayer = P->PlayerControl = true;

			//notify
			MessageListClass::Instance->PrintMessage(L"Player assumed control!");
		}
	}

	//Constructor
	AIControlCommandClass(){}
};

#endif
