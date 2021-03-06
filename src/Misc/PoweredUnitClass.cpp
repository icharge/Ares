#include <BuildingClass.h>
#include <HouseClass.h>
#include <GeneralStructures.h>
#include "../Ext/Building/Body.h"
#include "../Ext/TechnoType/Body.h"
#include "Debug.h"
#include "EMPulse.h"
#include "PoweredUnitClass.h"

bool PoweredUnitClass::IsPoweredBy(HouseClass* Owner) const
{
	for(int i = 0; i < Owner->Buildings.Count; ++i)	{
		auto Building  = Owner->Buildings.GetItem(i);
		auto BExt = TechnoExt::ExtMap.Find(Building);
		auto inArray = this->Ext->PoweredBy.Contains(Building->Type);

		if(inArray && !Building->BeingWarpedOut && !Building->IsUnderEMP() && BExt->IsOperated() && Building->IsPowerOnline()) {
			return true;
		}
	}
	
	return false;
}

void PoweredUnitClass::PowerUp()
{
	TechnoExt::ExtData* e = TechnoExt::ExtMap.Find(this->Techno);
	if( !this->Techno->IsUnderEMP() && e->IsOperated() ) {
		EMPulse::DisableEMPEffect2(this->Techno);
	}
}

bool PoweredUnitClass::PowerDown()
{
	if( EMPulse::IsDeactivationAdvisable(this->Techno) ) {
		// destroy if EMP.Threshold would crash this unit when in air
		if( EMPulse::EnableEMPEffect2(this->Techno) || ( this->Ext->EMP_Threshold && this->Techno->IsInAir() ) ) {
			return false;
		}
	}

	return true;
}

bool PoweredUnitClass::Update()
{
	if( (Unsorted::CurrentFrame - this->LastScan) < this->ScanInterval ) return true;

	if(!this->Techno->IsAlive || !this->Techno->Health || this->Techno->InLimbo) return true;

	HouseClass* Owner = this->Techno->Owner;
	bool HasPower     = this->IsPoweredBy(Owner);
	
	this->Powered = HasPower;
	
	if(HasPower && this->Techno->Deactivated) {
		this->PowerUp();
	} else if(!HasPower && !this->Techno->Deactivated) {
		// don't shutdown units inside buildings (warfac, barracks, shipyard) because that locks up the factory and the robot tank did it
		auto WhatAmI = this->Techno->WhatAmI();
		if((WhatAmI != InfantryClass::AbsID && WhatAmI != UnitClass::AbsID) || (!this->Techno->GetCell()->GetBuilding())) {
			return this->PowerDown();
		}
	}

	LastScan = Unsorted::CurrentFrame;
	return true;
}
