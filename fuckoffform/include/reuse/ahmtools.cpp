#include "reuse/ahmtools.h"
// findUnit: tool function to find a unit with a given type id in the unit tree
ahm::Unit *findUnit(ahm::Unit *pUnit, ahm::TypeId typeId){
	// test unit's type for given typeId
	if(pUnit && pUnit->type()){
		if(pUnit->type()->isA(typeId)){
			return pUnit; // ok it is!
		}
		else {
			if(pUnit->units()){
				// recursively find unit in child units
				for(iop::int32 i = 0;i<pUnit->units()->numUnits();i++){
					ahm::Unit *pDeepUnit = findUnit(pUnit->units()->getUnit(i), typeId);
					if(pDeepUnit){
						return pDeepUnit; // stop recursion
					}
				}
			}
		}
	}
	return 0; // unit with type id was not found
}
