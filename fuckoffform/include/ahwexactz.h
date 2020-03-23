/* 
 * Public Abstract Hardware Model Interfaces and Definitions 
 * applying to microscopes
 *
 * Copyright 2009,2010 (c) Leica Microsystems - All Rights Reserved.
 *
 */

#ifndef PUBLIC_AHM_MICROSCOPE_EXACTZFOCUS_H
#define PUBLIC_AHM_MICROSCOPE_EXACTZFOCUS_H

#include "ahwmic.h" // include base defs
#include "ahwmicpropid.h" // reserved ids
namespace ahm {

	typedef enum eExactZTypeIds {
		MICROSCOPE_EXACT_ZFOCUS = MICROSCOPE_RESERVED0,   // "AFC"
		MICROSCOPE_EXACT_ZFOCUS_MIRROR = MICROSCOPE_RESERVED1, // "AFC Mirror"
		MICROSCOPE_EXACT_ZFOCUS_STATE_LED = MICROSCOPE_RESERVED2, // reserved unused! -> property instead of unit
		MICROSCOPE_EXACT_ZFOCUS_DIAPHRAGM = MICROSCOPE_RESERVED4, //  internal diaphragm
		MICROSCOPE_EXACT_ZFOCUS_ADAPTING_LENS = MICROSCOPE_RESERVED5, // internal adapting lens
		MICROSCOPE_EXACT_ZFOCUS_LED = MICROSCOPE_RESERVED6, // internal AFC led illumination
	}EExactZTypeIds;


	typedef enum eExactZInterfaceIds {
		IID_MICROSCOPE_EXACT_ZFOCUS = IID_MICROSCOPE_RESERVED2,
		IID_MICROSCOPE_EXACT_ZFOCUS_ZONE = IID_MICROSCOPE_RESERVED3,
		IID_MICROSCOPE_EXACT_ZFOCUS_OBJECTIVE_ZONES = IID_MICROSCOPE_RESERVED4,
	}EExactZInterfaceIds;

	typedef enum eExactZEventType {
		EVENT_EXACT_ZFOCUS_ZONE_CHANGED		= IID_MICROSCOPE_EXACT_ZFOCUS_ZONE,  // event type same as interface id
		__EXACTZ_EVENT_TYPE_MAX
	} EExactZEventType;


	class ExactZFocusZone {
	public:
		// the zone range
		virtual iop::float64 minZone() = 0;
		virtual iop::float64 maxZone() = 0;
	};

	class ExactZFocusZoneResult {
	public:
		virtual ExactZFocusZone* zone() = 0;
		virtual void dispose() = 0;  // don't forget to dispose
	};

	/**
	 * Special access for exact z focus
	 *
	 * IID: IID_MICROSCOPE_EXACT_ZFOCUS
	 */

	class DirectExactZFocus { // IID: IID_MICROSCOPE_EXACT_ZFOCUS
	public:
		typedef enum eClassInfo { IID = ahm::IID_MICROSCOPE_EXACT_ZFOCUS, VERSION=3} EClassInfo;
		virtual iop::float64 currentSensorValue() = 0;
		virtual iop::int32 hold(iop::float64 f64SensorValue, bool flagOnce = false) = 0;
		// version 2:
		virtual ExactZFocusZoneResult* currentZone() = 0;
		// version 3:
		// hold at current position
		virtual void holdHere(bool flagSearchEdge = false) = 0;
		// start optimization for current position to reuse the sensor value
		virtual void optimizeHere() = 0;
        // stop/halt holding 
		virtual void halt() = 0;
	};


	class ExactZFocusZoneChangedEvent : public Event {
	public:
		typedef enum eClassInfo { EVENT_TYPE = EVENT_EXACT_ZFOCUS_ZONE_CHANGED } EClassInfo;
		virtual ExactZFocusZone* zone() = 0;
	};


	class ExactZFocusObjectiveZones {
	public:
		typedef enum eClassInfo { IID = ahm::IID_MICROSCOPE_EXACT_ZFOCUS_OBJECTIVE_ZONES, VERSION=2} EClassInfo;
		virtual void setObjectiveZonesArticleNo(iop::int32 objectiveIndex, iop::string szArticleNo) = 0;
		virtual ahm::StringResult* getObjectiveZonesArticleNo(iop::int32 objectiveIndex) = 0;
		virtual void flush() = 0; // flush changes
		virtual ahm::StringResult* getObjectiveZonesXml(iop::int32 objectiveIndex) = 0;
		virtual void getObjectiveZonesXmlToFile(iop::int32 objectiveIndex, iop::string szFileName) = 0;

		virtual void setObjectiveZonesXml(iop::int32 objectiveIndex, iop::string szXml) = 0;
		virtual void setObjectiveZonesXmlFromFile(iop::int32 objectiveIndex, iop::string szFileName) = 0;
		// version 2
		virtual iop::int32 numObjectiveZones(iop::int32 objectiveIndex) = 0;
		virtual ExactZFocusZoneResult* getObjectiveZoneRange(iop::int32 objectiveIndex) = 0;
	};
}

// outside namespace
	typedef enum eExactZPropertyIds {
		PROP_OBJECTIVE_EXACT_ZFOCUS_MIN = __PROP_OBJECTIVE_RESERVED1,   // exact z focus min sensor value float
		PROP_OBJECTIVE_EXACT_ZFOCUS_MAX = __PROP_OBJECTIVE_RESERVED2,   // exact z focus max sensor value float

		// Exact focus
		PROP_EXACT_ZFOCUS = 0x1760,
		PROP_EXACT_ZFOCUS_HOLD_MODE,             // int on off
		PROP_EXACT_ZFOCUS_SETPOINT_VALUE,        // double
		PROP_EXACT_ZFOCUS_STATE_LED1,            // int ->enum
		PROP_EXACT_ZFOCUS_STATE_LED2,            // int ->enum
		PROP_EXACT_ZFOCUS_SEARCH_MODE,           // int
		PROP_EXACT_ZFOCUS_GLOBAL_ON_OFF,         // int on off
		PROP_EXACT_ZFOCUS_OBJECTIVE_ZONES,        // array of properties
		PROP_EXACT_ZFOCUS_CONFIGURATION_MODE,     // int 0 ==> default AFC allways active, 1 ==> AF inactive manual activation
		PROP_EXACT_ZFOCUS_LED_CONFIGURATION_MODE, // int 0 ==> default AFC LED always active, 1 ==> LED off after hold once
		PROP_EXACT_ZFOCUS_ZONE_CHANGE_MODE	      // zone change mode (0 - OFF, 1 - ON), 1 is default after switching on - behaviour of zone changing
	} EExactZPropertyIds;


#endif // PUBLIC_AHM_MICROSCOPE_EXACTZFOCUS_H
