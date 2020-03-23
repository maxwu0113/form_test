
#ifndef AHM_TOOLS_H
#define AHM_TOOLS_H

#include "../ahm.h"

template <class clazz> clazz* find_itf(ahm::Unit *pUnit, iop::int32 iid){
	if(pUnit && pUnit->interfaces()){
		ahm::Interface* pInterface = pUnit->interfaces()->findInterface(iid);
		return pInterface? (clazz*) pInterface->object() : 0;
	}
	return 0;
}

template <class clazz> clazz* find_itf_version(ahm::Unit *pUnit, iop::int32 iid, iop::int32 minimumVersion){
	if(pUnit && pUnit->interfaces()){
		ahm::Interface* pInterface = pUnit->interfaces()->findInterface(iid);
		return pInterface && pInterface->interfaceVersion() >= minimumVersion ? (clazz*) pInterface->object() : 0;
	}
	return 0;
}

template <class clazz> clazz* find_valid_itf(ahm::Unit *pUnit, iop::int32 iid)
{
	if(pUnit && pUnit->interfaces())
	{
		ahm::Interface* pInterface = pUnit->interfaces()->findInterface(iid);
		if ((pInterface != nullptr) &&
			(pInterface->interfaceState() != ahm::Interface::INTERFACE_STATE_TEMPORARY_INVALID))
		{
			return (clazz*) pInterface->object();
		}
		return nullptr;
	}
	return 0;
}

template <class clazz> clazz* find_valid_itf_version(ahm::Unit *pUnit, iop::int32 iid, iop::int32 minimumVersion)
{
	if(pUnit && pUnit->interfaces())
	{
		ahm::Interface* pInterface = pUnit->interfaces()->findInterface(iid);
		if ((pInterface != nullptr) &&
			(pInterface->interfaceVersion() >= minimumVersion) &&
			(pInterface->interfaceState() != ahm::Interface::INTERFACE_STATE_TEMPORARY_INVALID))
		{
			return (clazz*) pInterface->object();
		}
		return nullptr;
	}
	return 0;
}

// findUnit: tool function to find a unit with a given type id in the unit tree
ahm::Unit *findUnit(ahm::Unit *pUnit, ahm::TypeId typeId);
#endif
