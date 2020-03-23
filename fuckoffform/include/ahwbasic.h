/* 
 * Published Abstract Hardware Model Interfaces and Definitions 
 * basically applying all hardware
 *
 * Copyright 2002-2013 (c) Leica Microsystems - All Rights Reserved.
 *
 * 
 */



#ifndef PUBLIC_AHM_BASIC_HARDWARE_H
#define PUBLIC_AHM_BASIC_HARDWARE_H

#include "ahm.h" // include base defs

namespace ahm {


	/**
	 *  basic unit type ids
	 */
	typedef enum ebasictid {
		__BASIC_START = 0x100,
		CALIBRATABLE = __BASIC_START,	// unit can be calibrated 
		CONFIGURABLE,					// unit can be configured
		EMULATED,						// emulated unit (demo/simulated)
		__BASIC_MAX
	} EBasicTypeId;


	/**
	 * basic interface ids
	 */
	typedef enum basiciid {
		__IID_BASIC_START=0x100,
		IID_BASIC_CONTROL_VALUE=__IID_BASIC_START,
		IID_BASIC_CALIBRATION,
		IID_AUTO_CALIBRATION,
		IID_BASIC_CONFIGURATION,
		IID_PROPERTIES,
		IID_SNAPSHOTS,
		IID_EVENT_SOURCE,
		//35°
		IID_DELTA_CONTROL_VALUE,
		IID_BASIC_CONTROL_VALUE_VELOCITY,
		IID_LIMIT_CONTROL_VALUE,
		IID_BASIC_CONTROL_STATE,
		IID_HALT_CONTROL_VALUE,
		IID_DIRECTED_CONTROL_VALUE_ASYNC,
		IID_BASIC_CONTROL_VALUE_ASYNC,
		IID_FACTORY_SETTINGS,
		IID_ADVANCED_EVENT_SOURCE,
		IID_DEFINED_CONTROL_VALUES,
		IID_BASIC_CONTROL_VALUE_SPECIAL,
        IID_PROPERTIES_UI,
		IID_ALTERNATING_CONTROL_UNITS,
		IID_DIRECTED_CONTROL_VALUE_ASYNC_VELOCITY,
		IID_LIMIT_SWITCHES,
		IID_LOGGING,
		IID_BASIC_CONTROL_VALUE_TIMING,
		IID_BASIC_CONTROL_VALUE_SETS,
		IID_BASIC_CONTROL_VALUE_HYSTERESIS_CORRECTED,
		IID_PROPERTY_ID_NAMES,
		IID_DELTA_CONTROL_VALUE_ASYNC,
		IID_BASIC_CONTROL_VALUE_ACCELERATION,
		IID_DELTA_CONTROL_VALUE_SPECIAL,
		IID_RESERVED_DIAGNOSTICS,
		IID_PNP_SIMULATOR,
		__IID_BASIC_MAX
	} EBasicInterfaceId;


	/**
	 *
	 * Metrics Ids  for MetricsConverter
	 */
	typedef enum metricsid {
		METRICS_NONE,
		METRICS_MICRONS,
		METRICS_VOLTAGE,
		METRICS_DIMENSIONLESS, // pure numbers
		METRICS_LIGHTYEARS,
		METRICS_MACH,
		METRICS_MICRONS_PER_SECOND,
		METRICS_DEGREES_KELVIN,
		METRICS_LINEPAIR_PER_MILLIMETERS,
		METRICS_DEGREES,  // ° angle
		METRICS_DEGREES_CELCIUS, // temperature ° C
		METRICS_MICRONS_PER_SECOND_SQUARED, // acceleration microns/s^2
		// MORE TO COME ...
		__METRICS_MAX
	} EMetricsId;

	/**
	 * The class MetricsConverter can be used to convert integer values
	 * from the BasicControlValue to a metrics value.
	 *
	 */

	class MetricsConverter {
	public:
		/**
		 *  Convert Control Value to double
		 */
		virtual iop::float64 getMetricsValue(iop::int32 nControlValue) = 0;
		/**
		 *  Convert a metrics value to a control value
		 */
		
		virtual iop::int32 getControlValue(iop::float64 dMetricsValue) = 0;


		/**
		 * Retrieve the Metrics ID for this connverter
		 */


		virtual iop::int32 metricsId() = 0;
	};


	/**
	 * The class MetricsConverters represents a container for MetricsConver
	 */
	class MetricsConverters {
	public:
		/**
		 *  Look for a special MetricsConverter.
		 *  @param metricsId - one of the ids defined in EMetricsId.
		 *  @return on success the appropriate MetricsConverter, when not available ==> 0
		 */
		virtual MetricsConverter * findMetricsConverter(iop::int32 metricsId) = 0;
	};


	/**
	 * Hardware Units providing interface objects implementing BasicControlValue
	 * allow to change a current value on the hardware unit.
	 * The value to be changed is in the integer range. A proper value
	 * can be in the range defined by minControlValue() and maxControlValue().
	 * Note: minControlValue() >= v <= maxControlValue()
	 *
	 * When a hardware unit does not allow to change that value for some reason
	 * (that function is not supported) the set method will result in an exception.
	 *
     * A converion of that control value will be supplied via metricsConverts();
	 * when metricsConverters return NULL there is no conversion available.
	 *
	 * IID: IID_BASIC_CONTROL_VALUE
	 */
		
	class BasicControlValue { // IID_BASIC_CONTROL_VALUE
	public:
		typedef enum eClassInfo { IID = IID_BASIC_CONTROL_VALUE } EClassInfo;
		/**
		 *  Retrieve Minimum Control Value
		 *  @return integer
		 */
		virtual iop::int32 minControlValue() = 0;
		/**
		 *  Retrieve Maximum Control Value
		 *  @return integer
		 */
		
		virtual iop::int32 maxControlValue() = 0;
		/**
		 *  Change the control value of a hardware unit.
		 *  @param control value
		 */
		
		virtual void setControlValue(iop::int32 ival) = 0;
		/**
		 *  Retrieve the current control value of a hardware unit.
		 *  @param control value
		 */
		
		virtual iop::int32 getControlValue() = 0;
		
		/**
		 *  Get the available Metrics Converters.
		 *  @param control value
		 */
		virtual MetricsConverters * metricsConverters() = 0;
	};
	
	
	
	/**
	 * class BasicCalibration supports basic calibration for hardware units
	 * 
	 * IID: IID_BASIC_CALIBRATION
	 */

	class BasicCalibration { // IID_BASIC_CALIBRATION
	public:
		typedef enum eClassInfo { IID = IID_BASIC_CALIBRATION } EClassInfo;
		virtual bool isCalibrated() = 0;
	};

	/**
	 * class AutoCalibration supports simple automatic calibration for hardware units
	 * 
	 */

	class AutoCalibration : public BasicCalibration { // IID_AUTO_CALIBRATION
	public:
		typedef enum eClassInfo { IID = IID_AUTO_CALIBRATION } EClassInfo;
		virtual void calibrate() = 0;
	};

	class BasicConfiguration { // IID_BASIC_CONFIGURATION
	public:
		typedef enum eClassInfo { IID = IID_BASIC_CONFIGURATION } EClassInfo;
		virtual bool isConfigured() = 0;
	};


	//35DEGREES
	/**
	 * class to change a control value in relative way BasicControlValue
	 * Units implementing this function in hardware will provide this interface
	 * 
	 * IID: IID_DELTA_CONTROL_VALUE
	 *
	 * @see BasicControlValue
 	 */

	class DeltaControlValue { // IID_DELTA_CONTROL_VALUE,
	public:
		typedef enum eClassInfo { IID = IID_DELTA_CONTROL_VALUE } EClassInfo;
		/**
		 *  Change the control value of a hardware unit relative to 
		 *  it's current control value.
		 *
		 *  @param control value
		 */
		
		virtual void setControlValueDelta(iop::int32 ival) = 0;

		/**
		 *  Get the available Metrics Converters.
		 *  @param control value
		 */
		virtual MetricsConverters * metricsConverters() = 0;
	};


	/**
	 * class to control the current velocity of a unit
	 * 
	 * IID: IID_BASIC_CONTROL_VALUE_VELOCITY
	 *
	 * @see BasicControlValue
 	 */
	class BasicControlValueVelocity : public BasicControlValue {
	public:
		typedef enum eClassInfo { IID = IID_BASIC_CONTROL_VALUE_VELOCITY } EClassInfo;
	}; // IID_BASIC_CONTROL_VALUE_VELOCITY



	/**
	 * class to modify the range limits of a BasicControlValue
	 * 
	 * IID: IID_LIMIT_CONTROL_VALUE
	 *
	 * @see BasicControlValue
 	 */

	class LimitControlValue { // IID_LIMIT_CONTROL_VALUE,
	public:
		/**
		 *  Retrieve Minimum Control Value
		 *  @return integer
		 */
		virtual iop::int32 minControlValue() = 0;
		/**
		 *  Retrieve Maximum Control Value
		 *  @return integer
		 */
		virtual iop::int32 maxControlValue() = 0;

		/**
		 *  Change the Minimum Control Value
		 *  
		 */
		virtual void setMinControlValue(iop::int32 ival) = 0;
		/**
		 * Change the Maximum Control Value
		 *  
		 */
		virtual void setMaxControlValue(iop::int32 ival) = 0;
		/**
		 * Reset the limits to it's original values
		 *  
		 */
		virtual void reset() = 0;

		/**
		 *  Get the available Metrics Converters.
		 *  @param control value
		 */
		virtual MetricsConverters * metricsConverters() = 0;


#define LIMIT_CONTROL_VALUE_VERSION2
#ifdef LIMIT_CONTROL_VALUE_VERSION2

		typedef enum eClassInfo { IID=IID_LIMIT_CONTROL_VALUE, VERSION = 2 } EClassInfo;
		// VERSION 2:
		/*
		 * retrieve full world range min without reset
		 */

		virtual iop::int32 minWorldControlValue() = 0;
		/*
		 * retrieve full world range max without reset
		 */
		virtual iop::int32 maxWorldControlValue() = 0;
#endif
	};

	/**
	 * class to get current control state of a unit
	 * 
	 * IID: IID_BASIC_CONTROL_STATE
	 */
	class BasicControlState {// IID_BASIC_CONTROL_STATE
	public:
		typedef enum eClassInfo { IID = IID_BASIC_CONTROL_STATE } EClassInfo;
		virtual bool isChanging() = 0;
	};


	class HaltControlValue { // IID_HALT_CONTROL_VALUE
	public:
		typedef enum eClassInfo { IID = IID_HALT_CONTROL_VALUE } EClassInfo;
		virtual void halt() = 0;
	};

	
	class DirectedControlValueAsync {//	IID_DIRECTED_CONTROL_VALUE_ASYNC
	public:
		typedef enum eClassInfo { IID = IID_DIRECTED_CONTROL_VALUE_ASYNC } EClassInfo;
		virtual void startTowardsMin() =  0;
		virtual void startTowardsMax() = 0;
	};

	class AsyncResult {
	public:
		typedef enum eState { INPROGRESS, COMPLETED, STOPPED, OVERRIDDEN } EState;
		virtual	iop::int32 state() = 0;
		virtual void dispose() = 0; // discard the returned object
	};
	
	class BasicControlValueAsync { // IID_BASIC_CONTROL_VALUE_ASYNC
	public:
		typedef enum eClassInfo { IID = IID_BASIC_CONTROL_VALUE_ASYNC } EClassInfo;
		virtual BasicControlValue* basicControlValue() = 0;
		virtual AsyncResult *setControlValueAsync(iop::int32 ival) = 0;
	};


	class FactorySettings { // IID_FACTORY_SETTINGS
	public:
		typedef enum eClassInfo { IID = IID_FACTORY_SETTINGS } EClassInfo;
		virtual void reset() = 0;
	};

	/**
	 * The DefinedControlValues interface refers to a list special 
	 * positions or values of a hardware unit.
	 * For example a DM6000 ZDrive defines two special positions 
	 * for the "lower z" and "focus". Those and similar things
	 * can be exposed via DefinedControlValues.
     *
	 *
	 * IID: IID_DEFINED_CONTROL_VALUES
	 */


class DefinedControlValue; // forward

class DefinedControlValues { // IID_DEFINED_CONTROL_VALUES
public:
	typedef enum eClassInfo { IID=ahm::IID_DEFINED_CONTROL_VALUES /*, INTERFACE_VERSION=... */ } EClassInfo;
    /** retrieve the number of "defined" values */
	virtual iop::int32 numDefinedControlValues() = 0;
	/** get access to value by index (0<=index<numDefinedControlValues()) */
	virtual DefinedControlValue* getDefinedControlValue(iop::int32 index) = 0;
	
	/* find by id */
	virtual DefinedControlValue* findDefinedControlValue(iop::int32 id) = 0;
	/* give id names */
	virtual ahm::IdNames * definedNames() = 0;
};	
	
	
class DefinedControlValue {
public:
	/**
	 *  refine a defined value
	 *  @param nControlValue new value @see BasicControlValue
	 */
	virtual void setDefinedValue(iop::int32 nControlValue) = 0;

	/**
	 *  retrieve the current value of a defined value
	 *  @return current set control value
	 */

	virtual iop::int32 definedValue() = 0;

	/**
	 *  reset a defined value
	 *  @param id one of the defined ids  (@see defines() and @see definedNames() 
	 */
	virtual void resetDefinedValue() = 0;
	/**
	 *  retrieve if a defined value is set
	 *  @return current set value
	 */
	virtual bool isDefinedValueSet() = 0;
	/**
	 * access to metrics converters for defined values
	 * 
	 */
	virtual MetricsConverters* metricsConverters() = 0;


	/**
	 * retrieve the id of the defined value
	 */
	virtual iop::int32 id() = 0;


	};



/**

   void setFocus(ahm::DefinedControlValues *pDCVs, iop::int32 nControlValueZ){
   	
   	  if(pDCVs){
   	  	ahm::DefinedControlValue *pFocusValue = pDCVs->findDefinedValue(MICROSCOPE_ZDRIVE_FOCUS);
   	  	if(pFocusValue){
   	  		pFocusValue->setDefinedValue(nControlValueZ);
   	  	}
   	  }
   }
   
   
   - or -
   void setDefined(ahm::DefinedControlValues *pDCVs, iop::string szname, iop::int32 nControlValue){
   	if(pDCVs && pDCVs->definedNames()){
   		ahm::DefinedControlValue *
   		pDefinedValue = pDCVs->findDefinedValue(pDCVs->definedNames()->findId(szname));
   		if(pDefinedValue){
   			pDefinedValue->setDefinedValue(nControlValue);
   		}
   	}
   	
   	
   }

**/





}// end namespace

#include "ahwevents.h"

namespace ahm {
// Events

	typedef EEventType EBasicEventType;

	/**
	 * class for generic a special second BasicControlValue
	 * 
	 * IID: IID_BASIC_CONTROL_VALUE_SPECIAL
	 *
	 * @see BasicControlValue
 	 */
	class BasicControlValueSpecial : public BasicControlValue {// IID_BASIC_CONTROL_VALUE_SPECIAL
	public:
		typedef enum eClassInfo { IID = IID_BASIC_CONTROL_VALUE_SPECIAL } EClassInfo;
	};


	/**
	* class for another special BasicControlValue
	* 
	* IID: IID_BASIC_CONTROL_VALUE_HYSTERESIS_CORRECTED
	*
	* @see BasicControlValue
	*/
	class BasicControlValueHysteresisCorrected : public BasicControlValue {
	public:
		typedef enum eClassInfo { IID = IID_BASIC_CONTROL_VALUE_HYSTERESIS_CORRECTED } EClassInfo;
	}; // IID_BASIC_CONTROL_VALUE_HYSTERESIS_CORRECTED


	/**
	 * class for alternating control of multiple units
	 * 
	 * IID: IID_ALTERNATING_CONTROL_UNITS
	 *
	 *
     * @see BasicControlValue
	 *
 	 **/


	class AlternatingControlUnits {
	public:
		typedef enum eClassInfo { IID=IID_ALTERNATING_CONTROL_UNITS } EClassInfo;

		/**
		 * retrieve the list of units which are alternating controllable.
		 *
		 */
		virtual ahm::Units * alternatingUnits() = 0;

		/**
		 * retrieve which of the alternating units is currently active.
		 * - which is the one -
		 */
		virtual ahm::Unit* activeUnit() = 0;

		/**
		 * make one of the alternating units the active one.
		 *
		 */
		virtual void activateUnit(ahm::Unit* pUnit) = 0;
	};



	class DirectedControlValueAsyncVelocity {//	IID_DIRECTED_CONTROL_VALUE_ASYNC_VELOCITY,
	public:
		typedef enum eClassInfo { IID=ahm::IID_DIRECTED_CONTROL_VALUE_ASYNC_VELOCITY } EClassInfo;
		virtual void startTowardsMinVelocity(iop::int32 velocity) =  0;
		virtual void startTowardsMaxVelocity(iop::int32 velocity) = 0;
		virtual MetricsConverters* metricsConverters() = 0;
	};


	class LimitSwitch {
	public:
		/** retrieve limit switch id */
		virtual iop::int32 id() = 0;
		virtual bool isSwitched()= 0;
	};

	class LimitSwitches { // IID_LIMIT_SWITCHES
	public:
		typedef enum eClassInfo { IID=ahm::IID_LIMIT_SWITCHES /*, INTERFACE_VERSION=... */ } EClassInfo;


		typedef enum eSwitchId { SWITCH_MIN=0x1000, SWITCH_MAX } ESwitchId;

		/** retrieve the number of limit switches */
		virtual iop::int32 numLimitSwitches() = 0;
		/** get access to value by index (0<=index<numLimitSwitches()) */
		virtual LimitSwitch* getLimitSwitch(iop::int32 index) = 0;
		
		/* find by id */
		virtual LimitSwitch* findLimitSwitch(iop::int32 id) = 0;
	};	



	class Logging { // IID_LOGGING 
	public:
		typedef enum eClassInfo { IID=ahm::IID_LOGGING /*, INTERFACE_VERSION=... */ } EClassInfo;
		/**
		 * add text to logging
		 */
		virtual void addText(iop::string szText) = 0;
	};

	

	class BasicControlValueTiming {
	public:
		typedef enum eClassInfo { IID = IID_BASIC_CONTROL_VALUE_TIMING } EClassInfo;
		virtual iop::float64 estimatedTimeMillis(iop::int32 posFrom, iop::int32 posTo, bool bInclResponseTime=true) = 0;
	};


	class BasicControlValueSet : public ahm::Reserved {
	public:
		virtual bool isSupported(ahm::Unit *pTargetunit, iop::int32 iid=ahm::IID_BASIC_CONTROL_VALUE) = 0;
		virtual void reset() = 0;
		virtual void setControlValue(ahm::Unit *pTargetUnit, iop::int32 nControlValue, iop::int32 iid=ahm::IID_BASIC_CONTROL_VALUE) = 0;
		virtual iop::int32 getControlValue(ahm::Unit *pTargetUnit, iop::int32 iid=ahm::IID_BASIC_CONTROL_VALUE) = 0;
		virtual void dispose() = 0; // please, don't forget to discard the set when no longer used!
	};

	class IBasicControlValueSetSelector {
	public:
		virtual iop::int32 version() = 0; // for future use return 1 here
		virtual bool isSelected(ahm::Unit *pUnit, iop::int32 iid=ahm::IID_BASIC_CONTROL_VALUE) = 0;
	};

	class BasicControlValueSets {
	public:
		typedef enum eClassInfo { IID = IID_BASIC_CONTROL_VALUE_SETS, VERSION = 2 } EClassInfo;
		virtual BasicControlValueSet * createControlSet() = 0;
		virtual void flush(BasicControlValueSet* pControlSet) = 0; // execute
		// version 2
		// read all or anything defined by a client side ISelector object
		virtual void read(BasicControlValueSet *pControlSet, IBasicControlValueSetSelector *pSelector=0) = 0;
	};

	class PropertyIdNames : public IdNames {
	public:
		typedef enum eClassInfo { IID = IID_PROPERTY_ID_NAMES } EClassInfo;
	};
	
	/**
	 * move relative async
	 */ 
	class DeltaControlValueAsync { // IID_DELTA_CONTROL_VALUE_ASYNC
	public:
		typedef enum eClassInfo { IID = IID_DELTA_CONTROL_VALUE_ASYNC } EClassInfo;
		virtual ahm::AsyncResult* setControlValueDeltaAsync(iop::int32 ival) = 0;
		virtual MetricsConverters * metricsConverters() = 0;
	};

	/**
	 * class to control the current acceleration of a unit
	 * 
	 * IID: IID_BASIC_CONTROL_VALUE_ACCELERATION
	 *
	 * @see BasicControlValue
 	 */
	class BasicControlValueAcceleration : public BasicControlValue {
	public:
		typedef enum eClassInfo { IID = IID_BASIC_CONTROL_VALUE_ACCELERATION } EClassInfo;
	};


	/**
	 * class for generic a special second DeltaControlValue
	 * 
	 * IID: IID_DELTA_CONTROL_VALUE_SPECIAL
	 *
	 * @see DeltaControlValue
 	 */
	class DeltaControlValueSpecial : public DeltaControlValue {// IID_DELTA_CONTROL_VALUE_SPECIAL
	public:
		typedef enum eClassInfo { IID = IID_DELTA_CONTROL_VALUE_SPECIAL } EClassInfo;
	};


}//end namespace

#endif

