#ifndef TECHNOTYPE_EXT_H
#define TECHNOTYPE_EXT_H

#include <MacroHelpers.h> //basically indicates that this is DCoder country

#include <TechnoTypeClass.h>

#include "..\..\Ares.h"
#include "..\_Container.hpp"

class TechnoTypeExt
{
public:
	typedef TechnoTypeClass TT;
	enum SpotlightAttachment { sa_Body, sa_Turret, sa_Barrel };

	class ExtData : public Extension<TT> 
	{
	public:
		DynamicVectorClass<InfantryTypeClass *> Survivors_Pilots;
		int Survivors_PilotChance;
		int Survivors_PassengerChance;

		// animated cameos
//		int Cameo_Interval;
//		int Cameo_CurrentFrame;
//		TimerStruct Cameo_Timer;

		DynamicVectorClass< DynamicVectorClass<int>* > PrerequisiteLists;
		DynamicVectorClass<int> PrerequisiteNegatives;
		DWORD PrerequisiteTheaters;

		// new secret lab
		DWORD Secret_RequiredHouses;
		DWORD Secret_ForbiddenHouses;

		bool Is_Deso;
		bool Is_Deso_Radiation;
		bool Is_Cow;
		bool Is_Spotlighted;

		// spotlights
		int Spot_Height;
		int Spot_Distance;
		SpotlightAttachment Spot_AttachedTo;
		bool Spot_DisableR;
		bool Spot_DisableG;
		bool Spot_DisableB;
		bool Spot_Reverse;

		// these are not implemented at all yet
		DynamicVectorClass<WeaponStruct> Weapons;
		DynamicVectorClass<WeaponStruct> EliteWeapons;

		SHPStruct *Insignia_R, *Insignia_V, *Insignia_E;

		AnimTypeClass *Parachute_Anim;

		ExtData(const DWORD Canary = 0) : 
			Survivors_PilotChance (0),
			Survivors_PassengerChance (0),
			PrerequisiteTheaters (0xFFFFFFFF),
			Secret_RequiredHouses (0),
			Secret_ForbiddenHouses (0),
			Is_Deso (false),
			Is_Deso_Radiation (false),
			Is_Cow (false),
			Is_Spotlighted (false),
			Spot_Height (200),
			Spot_Distance (1024),
			Spot_AttachedTo (sa_Body),
			Spot_DisableR (false),
			Spot_DisableG (false),
			Spot_DisableB (false),
			Spot_Reverse (false),
			Insignia_R (NULL),
			Insignia_V (NULL),
			Insignia_E (NULL),
			Parachute_Anim (NULL)
			{ };

		virtual ~ExtData() { };

		virtual size_t Size() const { return sizeof(*this); };

		virtual void LoadFromINI(TT *pThis, CCINIClass *pINI);
		virtual void Initialize(TT *pThis);
	};

	static Container<TechnoTypeExt> ExtMap;

//	static void ReadWeapon(WeaponStruct *pWeapon, const char *prefix, const char *section, CCINIClass *pINI);
};

#endif