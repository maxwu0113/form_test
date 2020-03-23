/**
 * \mainpage Published Abstract Hardware Model
 *
 * The following figure shows the flow a client program can use
 * The Abstract Hardware Model.<p>
 * For more details look a the class descriptions of <B>HardwareModel</B> and <B>Unit</B>.<p>
 * <p>
 * <img src="ahmflow.gif"/>
 * <p>
 * @see ahm::HardwareModel, ahm::Unit
 */
/*
 * Copyright 2002-2014 (c) Leica Microsystems - All Rights Reserved.
 *
 */


#ifndef PUBLIC_AHM_H
#define PUBLIC_AHM_H

#ifndef AHM_2_0
#define AHM_2_0
#endif

#ifndef AHM_2_1
#ifndef FORCE_NO_AHM_2_1
#define AHM_2_1
#endif
#endif

#ifndef AHM_PNP
#ifndef FORCE_NO_AHM_PNP
#define AHM_PNP
#endif
#endif

// include interop services

#include "iop/iop.h"
#include "ahmerr.h"

/**
 * namespace ahm holds all classes of the Abstract Hardware Model
 */

namespace ahm {

	/**
	 * Type for unique number for Interface Ids (IIDs) used in Interface class
	 * 
     */
	typedef iop::int32 InterfaceId;
	
	
	/**
	 * The class Interface holds pair of IID and the object (pointer) implementing the
	 * related interface class.
	 */

	class Interface {
	public:
		typedef enum eClassInfo { CLASS_VERSION=2 } EClassInfo;
		virtual InterfaceId interfaceId() = 0;
		virtual void * object() = 0;
		virtual iop::int32 interfaceVersion() = 0;
#ifdef AHM_2_0
		typedef enum eInterfaceState {
			INTERFACE_STATE_VALID = 1,   /* default: interface is valid during whole lifetime of interface */
			INTERFACE_STATE_TEMPORARY_VALID = 2, /* interface is valid now */
			INTERFACE_STATE_TEMPORARY_INVALID = 0 /* interface is not valid now */
		} EInterfaceState;
		/**
		 *  is the interface valid now
		 */
		virtual iop::int32 interfaceState() = 0;
#endif
	};

	/**
	 * The class Interfaces is container for Interface objects
	 * 
	 */
	class Interfaces {
		public:
		/**
		 * Retrieve information, interface object is available.
		 * @param iid the Interface Id to look for.
		 * @return true or false  
		 */
		virtual bool hasInterface(InterfaceId iid)=0;
		/**
		 * Find the first interface object
		 * @param iid the Interface Id to look for.
		 * @return Interface object or 0 (when not in container).
		 */
		
		virtual Interface* findInterface(InterfaceId iid)=0;

		/**
		 * How many interface objects are in the container.
		 * @return number of interfaces
		 */
		
		virtual iop::int32 numInterfaces()=0;

		/**
		 * Get a pointer to interface object from the container
		 * @param index of object ( 0 <= index < numInterfaces())
		 * @return Interface obect of index
		 *
		 * @see numInterfaces()
		 */
		virtual Interface *getInterface(iop::int32 index) = 0;
	};



	class Units; // forward
	class UnitType; // forward


	/**
	 * The class Unit represents a Abstract Hardware Unit.
	 * It mainly gives access to "child" Units and the Interfaces
	 * available for the hardware unit.
	 *
	 */

	class Unit {
	public:
		/**
		 * Retrieve the string name of the hardware unit
		 */
		virtual iop::string  name() = 0;

#ifndef AHM_2_1
		typedef enum emode { UNDEF=-1, DISABLED, ENABLED, MAX } Mode;
		virtual  Mode mode() = 0; //deprecated
#else
		typedef enum eConst { UNIQUEID_NONE = 0} EConst;
		/**
		 * Retrieve unique "object" id for the unit object
		 */
		virtual iop::int32 uniqueId() = 0;
#endif

		/**
		 * Retrieve the UnitType of this hareware unit.
		 * @return pointer!=0
		 */

		virtual  UnitType *type() = 0;

		/**
		 * Get access to the child units of this unit
		 * @return Units object or 0.
		 */
		virtual Units *units() = 0;

		/**
		 * A child Unit delivers it's parent.
		 * @return the parent Unit or 0 (when no parent).
		 */

		virtual Unit *parent() = 0;

		/**
		 * Retrieve the Interfaces available for the hardware unit.
		 * @return Interfaces or 0.
		 */
		virtual Interfaces * interfaces() = 0;


		/**
		 *  Retrieve if hardware unit is initialized
		 */
		virtual bool initState() = 0;


		/**
		 * Initialize the hardware unit.
		 */
		virtual void init() = 0;


		/**
		 * dispose allocated resources for this hardware unit.
		 * ATTENTION: Use this to free resources, when no longer needed.
		 *            After dispose calls to Unit objects may cause crashes.
		 */
		virtual void dispose()=0;
 	};



       /**
        * The class Units is a container for Unit objects
        */

	class Units {
	public:

		/**
		 * How many Unit objects are in the container.
		 * @return number of Unit objects.
		 */

		virtual iop::int32 numUnits()=0;
		/**
		 * Get a pointer to Unit object from the container
		 * @param index of object ( 0 <= index < numUnits())
		 * @return Unit obect of index
		 *
		 * @see numUnits()
		 */
		
		virtual Unit *getUnit(iop::int32 index) = 0;
	};



	/**
	 *  Id Type for the harware unit type.
	 */

	typedef iop::int32 TypeId;
	
	
	/**
	 * The class UnitType classifies a hardware unit.
	 * It will hold one exposed type id.
	 * And a list of type ids a hardware unit is compatible with.
	 */

	class UnitType {
	public:
	  /**
	   * The exposed type id, may tell what a hardware unit is mainly. 
	   */
		virtual TypeId exposedTypeId() = 0;

	   /**
	    * Retrieve if a hardware unit is comatible with a special TypeId.
	    * 
	    */
	   		
		virtual bool isA(TypeId typeId) = 0;
		/**
		 * How many TypeIds are hold by the unit  tye
		 * @return number of type ids.
		 *
		 * @see getTypeId
		 */

		virtual iop::int32 numTypeIds() = 0;
		/**
		 * Get TypeId by index.
		 * @param index of object ( 0 <= index < numTypeIds())
		 * @return TypeId for index
		 *
		 * @see numTypeIds()
		 */
		virtual TypeId getTypeId(iop::int32 index)=0;
	};

	/**
	 * Exception class for exceptions thrown by the abstract hardware model.
	 */
	class Exception {
    	public:
		virtual ~Exception(){}
		/**
		 *  Retrieve error class number 
		 *  @see "ahmerr.h"
		 */		
		virtual iop::int32 errorClass() = 0;
		
		/**
		 *  Retrieve error code number 
		 *  @see "ahmerr.h"
		 */		
		virtual iop::int32 errorCode() = 0;
		
		/**
		 *  Retrieve error text description of the exception.
		 *  @see "ahmerr.h"
		 */		
		virtual iop::string errorText() = 0;
	};



	class IdNames; // forward

	/**
	 * The class HardwareModel gives access 
	 * to the functionality of the abstract hardware model.
	 * It mainly gives access to hardware units.
	 *
	 */	

	class HardwareModel {
	public:
		typedef enum eClassInfo { VERSION=3 } EClassInfo;
		/**
		 *  Request access to a hardware unit.
		 *  @param hardware unit locater (for example entry in hardware unit config DB)
		 *  @return Unit object or 0 (if not available)
	     */
	 
		virtual ahm::Unit * getUnit(iop::string locatehw)=0;
		
		/**
		 * dispose allocated resources for this hardware model
		 * ATTENTION: Use this to free resources, when no longer needed.
		 *            After dispose calls to the HardwareModel object may cause crashes.
		 */
		virtual void dispose()=0;
		
		/**
		* Retrieve version string of hardware model 
		*/		
		virtual iop::string version() = 0;
		
		/*** VERSION 2 ... */

		/** set file name of ahmconfig.xml */
		virtual void setConfigFileName(iop::string szfnConfig) = 0;
		/** set file name of ahmconfig.xml */
		virtual iop::string configFileName() = 0;

		/*** VERSION 3 ... */
		typedef enum eIdNames { IDNAMES_TYPEID, IDNAMES_INTERFACEID, IDNAMES_PROPERTYID } EIdNames;
		/** get id name tables for unit type ids, Interface Ids, ProperyIds, ...*/
		virtual ahm::IdNames* idNames(iop::int32 tabledId) = 0;
	};

	/**
	 *  core hardwaremodel unit type ids
	 */
	typedef enum ecoretid {
		__CORE_START = 0x10,
		FOLDER = __CORE_START,  // unit is a folder holding other units
		SHARED, // unit is shared
		REMOTE,
#ifdef AHM_PNP
		DYNAMIC_UNITS,
#endif
		__CORE_MAX
	} ECoreTypeId;


	/**
	 *  core hardwaremodel interface ids
	 */
	typedef enum ecoreiid {
		__IID_CORE_START = 0x10,
		IID_DRIVER_INFO = __IID_CORE_START,
		IID_SESSION,
		IID_ALL_SESSIONS,
		IID_RESERVED,
		IID_INIT_STATE,
		IID_DYNAMIC_UNITS,
		IID_ORIGINAL_DRIVER_INFO,
		__IID_CORE_MAX
	} ECoreInterfaceId;


	/**
	 *  StringResult embedded string objects for returned strings
	 */
	class StringResult {
	public:
		/**
		 *  Retrieve embedded string value
		 */
		virtual iop::string value() = 0;

		/**
		 *  dispose - release allocated String resources
		 */
		virtual void dispose() = 0;
	};

	/**
	 * StringResult embedded string objects for returned strings
	 * UNICODE variant
	 */
	class UnicodeStringResult {
	public:
		/**
		 *  Retrieve embedded string value
		 */
		virtual iop::unicode_string value() = 0;

		/**
		 *  dispose - release allocated String resources
		 */
		virtual void dispose() = 0;
	};


	/* common tool classes */
	class IdNames {
	public:
		/**
		 * find a string name for an id
		 * if not found return is null
		 */
		virtual iop::string findName(iop::int32 id) = 0;

		/**
		 * find the id for a given name
		 * if not found return is -1
		 */
		virtual iop::int32 findId(iop::string szname) = 0;
	};


	class IdList  {
	public:
		/**
		 * Retrieve the number of ids in the list
		 */
		virtual iop::int32 numIds() = 0;
		/**
		 * Get the id for a given index
		 * @param 0>= index < numIds
		 */
		virtual iop::int32 getId(iop::int32 index) = 0;

		/**
		 * Find out if an id is in the list
		 * @param id
		 * @return on success the zero based index in the list
		 * when the id is not in the list @return <0
		 */
		virtual iop::int32 findId(iop::int32 id) = 0;
	};

	/**
	 * A disposable IdList.
	 */
	class IdListResult
	{
	public:
		/**
		 * Get the IdList object.
		 * @return a pointer to the managed IdList object.
		 */
		virtual IdList* idList() = 0;

		/**
		 * Release resources.
		 */
		virtual void dispose() = 0;
	};

    class DriverInfo { // IID_DRIVER_INFO
    public:
		typedef enum eClassInfo { IID=ahm::IID_DRIVER_INFO, VERSION=2 } EClassInfo;
		/**
		 *  Retrieve driver's name
		 */
		virtual iop::string driverName() = 0;
        /**
		 *  Retrieve driver version
		 *  
		 */
		virtual iop::string driverVersion() = 0;

		// VERSION:2
		/**
		 * retrieve driver instance id of unit
		 */
		virtual iop::int32 instanceId() = 0;
    };

	class OriginalDriverInfo : public DriverInfo { // IID_ORIGINAL_DRIVER_INFO
	public:
		typedef enum eClassInfo { IID = ahm::IID_ORIGINAL_DRIVER_INFO, VERSION = DriverInfo::VERSION } EClassInfo;

	};

#ifdef AHM_2_0
	class InitState { // IID_INIT_STATE
    public:
		typedef enum eClassInfo { IID=ahm::IID_INIT_STATE } EClassInfo;
		typedef enum eInitState { INIT_STATE_NONE=0, INIT_STATE_INIT=1, INIT_STATE_INUSE = -1, INIT_STATE_DISCONNECTED=-2} EInitState;

		/**
		 * @return current init state (EInitState)
		 */ 
		virtual iop::int32 initState() = 0;

		/**
		 *  invoke init procedure
		 */
		virtual void init() = 0;
        /**
		 *  un_initialize - suspend hardware access - but not dispose
		 */
		virtual void uninit() = 0;
    };
#endif


#ifdef AHM_PNP
	/**
	 *  Receive changes by plug and play to be implemented by client
	 */
	class IUnitsChanged {
	public:
		typedef enum eUnitChangeInfo {UNIT_ADDED = 1, UNIT_REMOVED = -1} EUnitChangeInfo;
		/**
		 * changes on the dynamic unit tree are forwarded as unit changes
		 * @param changeInfo @see EUnitChangeInfo
		 * @param pChangeUnit - the Unit pointer added or removed
		 *
		 * ATTENTION - call Unit::dipose() on removed units
		 */
		virtual void noteUnitsChanged(iop::int32 changeInfo, Unit *pChangedUnit) = 0;
	};

	class DynamicUnits { // IID_DYNAMIC_UNITS
    public:
		typedef enum eClassInfo { IID=ahm::IID_DYNAMIC_UNITS } EClassInfo;
	
		typedef enum eDynamicUnitsState {DYNAMIC_UNITS_STATE_UNDEF = -1, DYNAMIC_UNITS_STATE_COMPLETE=0, DYNAMIC_UNITS_STATE_CHANGED} EDynamicUnitsState;

		/**
		 * @return current dynamic units state (EDynamicUnitsState)
		 */ 
		virtual iop::int32 dynamicUnitsState() = 0;

		/**
		 *  invoke update procedure
		 *
		 *  optionally add an object implementing IUnitsChanged
		 *  to receive which units where added or removed
		 *  
		 *  ATTENTION: when passing a change receiver - explicitly call dispose()
		 *             on the removed units.
		 *             Added units are bound to their parent
		 *
		 */
		virtual void updateUnits(IUnitsChanged *pChangeReceiver) = 0;
    };

#endif

	typedef enum eSessionState { SESSION_STATE_UNDEF = -1, SESSION_STATE_SUSPENDED = 0, SESSION_STATE_RESUMED=1 } ESessionState;

	class Session { // IID_SESSION
    public:
		typedef enum eClassInfo { IID=ahm::IID_SESSION } EClassInfo;

		/**
		 * @return current session state (ESessionState)
		 */ 
		virtual iop::int32 sessionState() = 0;

		/**
		 *  suspend session
		 */
		virtual void suspend() = 0;
        /**
		 *  resume session
		 */
		virtual void resume() = 0;
    };


	class AllSessions { // IID_ALL_SESSIONS
    public:
		typedef enum eClassInfo { IID=ahm::IID_ALL_SESSIONS } EClassInfo;
		/**
		 * @return current session state (ESessionState)
		 */ 

		virtual iop::int32 sessionState() = 0;

		/**
		 *  suspend session
		 */
		 virtual void suspendAll() = 0;
        /**
		 *  resume session
		 */
		virtual void resumeAll() = 0;
    };

	
	/**
	 * list of constant strings
	 */

	class StringList {
	public:
		/** 
		 * retrieve number of strings in list
		 */
		virtual iop::int32 numValues() = 0;
		/**
		 * retrieve string by index ( 0 <= index < numValues() )
		 * on success string != null
		 */
		 
		virtual iop::string getValue(iop::int32 index) = 0;
	};


	/**
	 * list of strings to be implemented by ahm client
	 */

	typedef StringList IStringList;



	/* 
	 *list of strings as result has to be disposed by client
	 */


	class StringListResult {
	public:
		virtual StringList* getStrings() = 0;  
		/**
		* dispose allocated resources for this hardware unit.
		* ATTENTION: Use this to free resources, when no longer needed.
		*            After dispose calls to Unit objects may cause crashes.
		*/
		virtual void dispose()=0;
	};


	/**
	 * table of integer values
	 */
	class IntValueTable {
	public:

		/**
		 * retrieve number of rows
		 */
		virtual iop::int32 numRows() = 0;
		/**
		 * retrieve number of columns
		 */
		virtual iop::int32 numColumns() = 0;
		/**
		 * retrieve stored value in table
		 */
		virtual iop::int32 getValue(iop::int32 rowIndex, iop::int32 columnIndex) = 0;
	};


    class Reserved {
    public:
		typedef enum eClassInfo { IID=ahm::IID_RESERVED } EClassInfo;
		virtual iop::int32 reserved(void *, iop::int32)=0;
    };


}; // namespace ahm


/**
 * Published DLL entry point
 * Call this to get the singleton hardware model
 *
 */
AHM_API ahm::HardwareModel *  theHardwareModel();



#endif // PUBLIC_AHM_H


