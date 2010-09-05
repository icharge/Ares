#ifndef BUILDINGTYPE_EXT_H
#define BUILDINGTYPE_EXT_H

#include <CCINIClass.h>
#include <BuildingTypeClass.h>
#include <InfantryTypeClass.h>
#include <Randomizer.h>
#include <UnitTypeClass.h>
#include <WeaponTypeClass.h>

#include "../_Container.hpp"
#include "../../Ares.h"
#include "../../Utilities/Template.h"

#include <vector>

//ifdef DEBUGBUILD -- legit needs to log things, so no debug
#include "../../Misc/Debug.h"
//endif

class BuildingClass;

#define FOUNDATION_CUSTOM	0x7F

class BuildingTypeExt
{
public:
	typedef BuildingTypeClass TT;

	class cPrismForwarding {
		public:
		//properties
		enum eEnabled {NO, YES, FORWARD, ATTACK} Enabled;	//is this tower a prism tower? FORWARD means can support, but not attack. ATTACK means can attack but not support.
		DynamicVectorClass<BuildingTypeClass *> Targets;	//the types of buiding that this tower can forward to
		Customizable<signed int> MaxFeeds;					//max number of towers that can feed this tower
		Valueable<signed int> MaxChainLength;				//max length of any given (preceding) branch of the network
		Customizable<signed int> MaxNetworkSize;				//max number of towers that can be in the network
		Customizable<int> SupportModifier; 				//Per-building PrismSupportModifier
		Valueable<signed int> DamageAdd; 					//amount of flat damage to add to the firing beam (before multiplier)
		Customizable<int> MyHeight;						//Per-building PrismSupportHeight
		Valueable<signed int> Intensity;						//amount to adjust beam thickness by when supported
		Valueable<int> ChargeDelay;					//the amount to delay start of charging per backward chain
		Valueable<bool> ToAllies;						//can this tower support allies' towers or not
		Valueable<bool> BreakSupport;					//can the slave tower become a master tower at the last second
		Valueable<signed int> SupportWeaponIndex;

		//methods
		signed int GetUnusedWeaponSlot(BuildingTypeClass* );
		void Initialize(BuildingTypeClass* );
		void LoadFromINIFile(BuildingTypeClass *, CCINIClass *);

		// future considerations - move these to BuildingExt's PrismForwarding and refactor first arg
		static int AcquireSlaves_MultiStage(BuildingClass *, BuildingClass *, int, int, int *, int *);
		static int AcquireSlaves_SingleStage(BuildingClass *, BuildingClass *, int, int, int *, int *);
		static bool ValidateSupportTower(BuildingClass *, BuildingClass *, BuildingClass *);
		static void SetChargeDelay(BuildingClass *, int);
		static void SetChargeDelay_Get(BuildingClass * , int , int , int , DWORD *, DWORD *);
		static void SetChargeDelay_Set(BuildingClass * , int , DWORD *, DWORD *, int);
		static void RemoveFromNetwork(BuildingClass *, bool);

		// constructor
		cPrismForwarding() : Enabled(NO),
			MaxFeeds(&RulesClass::Instance->PrismSupportMax),
			MaxChainLength(1),
			MaxNetworkSize(&RulesClass::Instance->PrismSupportMax),
			SupportModifier(&RulesClass::Instance->PrismSupportModifier),
			DamageAdd(0),
			MyHeight(&RulesClass::Instance->PrismSupportHeight),
			Intensity(-2),
			ChargeDelay(1),
			ToAllies(false),
			BreakSupport(false),
			SupportWeaponIndex(-1)
		{};
	};

	class ExtData : public Extension<TT>
	{
	public:
		// solid
		int Solid_Height;

		// foundations
		bool IsCustom;
		int CustomWidth;
		int CustomHeight;
		int OutlineLength;
		CellStruct* CustomData;
		CellStruct* OutlineData;

		// new secret lab
		DynamicVectorClass<TechnoTypeClass *> Secret_Boons;
		bool Secret_RecalcOnCapture;
		bool Secret_Placed;

		// new firestorm wall
		bool Firewall_Is;

		// added on 11.11.09 for #221 and children (Trenches)
		double UCPassThrough; 					//!< How many percent of the shots pass through the building to the occupants? 0.0 = 0%, 1.0 = 100%; Defaults to 0.0.
		double UCFatalRate; 					//!< Chance of an occupant getting killed instantly when a bullet passes through. 0.0 = 0%, 1.0 = 100%; Defaults to 0.0.
		double UCDamageMultiplier; 				//!< How many percent of normal damage are applied if an occupant is hit when a bullet passes through. 0.0 = 0%, 1.0 = 100%; Defaults to 1.0.
		bool BunkerRaidable; 					//!< Can this BuildingType be occupied by hostile forces despite being owned by a player, if empty?
		signed int IsTrench; 					//!< Enables moving between segments - saves ID of a kind of trench. \sa trenchKinds
		BuildingTypeClass * RubbleIntact; 		//!< What BuildingType to turn into when reconstructed. (This is the normal building, set on rubble.)
		BuildingTypeClass * RubbleDestroyed;	//!< What BuildingType to turn into when destroyed. (This is the rubble, set on normal buildings.)
		static std::vector<std::string> trenchKinds; //!< Vector of strings associating known trench names with IsTrench IDs. \sa IsTrench

		// added 03.03.10 for #696 (switch for spied radar behavior)
//		bool LegacyRadarEffect; //!< Whether to use RA's "reveal radar to spy" in addition to RA2's "disrupt radar for victim" on spying of a radar. Defaults to false, requires DisplayProduction to be true. \sa DisplayProduction

		// added 04.03.10 for 633#c2727
//		bool DisplayProduction; //!< Whether to show a factory/radar's production/view to the house who spied it. (RA spy behavior.) Defaults to false. \sa LegacyRadarEffect

		Valueable<bool> InfiltrateCustom;
		Valueable<bool> RevealProduction;
		Valueable<bool> ResetSW;
		Valueable<bool> ResetRadar;
		Valueable<bool> RevealRadar;
		Valueable<bool> GainVeterancy;
		Valueable<int> StolenTechIndex;
		Valueable<int> StolenMoneyAmount;
		Valueable<int> StolenMoneyPercentage;
		Valueable<int> PowerOutageDuration;

		cPrismForwarding PrismForwarding;

		ExtData(const DWORD Canary, TT* const OwnerObject) : Extension<TT>(Canary, OwnerObject),
			Solid_Height (0),
			IsCustom (false),
			CustomWidth (0),
			CustomHeight (0),
			OutlineLength (0),
			CustomData (NULL),
			OutlineData (NULL),
			Firewall_Is (false),
			UCPassThrough (0.0),
			UCFatalRate (0.0),
			UCDamageMultiplier (1.0),
			BunkerRaidable (false),
			IsTrench (-1),
			RubbleIntact (NULL),
			RubbleDestroyed (NULL),

			InfiltrateCustom (false),
			RevealProduction (false),
			ResetSW (false),
			ResetRadar (false),
			RevealRadar (false),
			GainVeterancy (false),
			StolenTechIndex (-1),
			StolenMoneyAmount (0),
			StolenMoneyPercentage (0),
			PowerOutageDuration (0),
			PrismForwarding()
			{ };

		virtual ~ExtData() {
			delete [] CustomData;
			delete [] OutlineData;
		}

		virtual size_t Size() const { return sizeof(*this); };

		virtual void LoadFromINIFile(TT *pThis, CCINIClass *pINI);
		virtual void Initialize(TT *pThis);
		virtual void CompleteInitialization(TT *pThis);

		virtual void InvalidatePointer(void *ptr) {
			AnnounceInvalidPointer(RubbleIntact, ptr);
			AnnounceInvalidPointer(RubbleDestroyed, ptr);
		}

		bool IsLinkable();
	};

	static Container<BuildingTypeExt> ExtMap;
//	static ExtData ExtMap;

	static void UpdateSecretLabOptions(BuildingClass *pThis);
	static bool IsFoundationEqual(BuildingTypeClass *pTBldA, BuildingTypeClass *pTBldB);
};

#endif
