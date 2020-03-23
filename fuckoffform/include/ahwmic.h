/*
 * Public Abstract Hardware Model Interfaces and Definitions
 * applying to microscopes
 *
 * Copyright 2002-2016 (c) Leica Microsystems - All Rights Reserved.
 *
 */

#ifndef PUBLIC_AHM_MICROSCOPE_H
#define PUBLIC_AHM_MICROSCOPE_H


#include "ahwbasic.h" // include base defs
#include "ahwprop2.h" // INT_RECT used

namespace ahm {


	/**
	 * hardware unit type ids for microscopes.
	 */
	typedef enum emictid {
		__MICROSCOPE_START = 0x1000,
		MICROSCOPE=__MICROSCOPE_START,
		MICROSCOPE_UNIT,
		MICROSCOPE_MOTORIZED_UNIT,
		MICROSCOPE_CODED_UNIT,
		MICROSCOPE_NOSEPIECE,
		MICROSCOPE_ZDRIVE,
		MICROSCOPE_TL_AXIS,
		MICROSCOPE_IL_AXIS,
		MICROSCOPE_IL_TURRET,
		MICROSCOPE_APERTURE_DIAPHRAGM,
		MICROSCOPE_FIELD_DIAPHRAGM,
		MICROSCOPE_CONDENSER,
		MICROSCOPE_CONDENSER_TURRET,
		MICROSCOPE_SWITCHABLE_CONDENSER_TOP,
		MICROSCOPE_FUNCTION_KEYS,
		MICROSCOPE_POLARIZER,
		MICROSCOPE_STAGE,
		MICROSCOPE_LENS,
		MICROSCOPE_TL_ADAPTING_LENS,
		MICROSCOPE_SHUTTER,
		MICROSCOPE_DIC_TURRET,
		MICROSCOPE_SCREEN,
		MICROSCOPE_TOUCHSCREEN,
		MICROSCOPE_LAMP,
		MICROSCOPE_TL_IL_LAMP_SWITCH,
		MICROSCOPE_MAGNIFICATION_CHANGER,
		MICROSCOPE_X_UNIT,
		MICROSCOPE_Y_UNIT,
		MICROSCOPE_Z_UNIT,
		MICROSCOPE_COMPARISON_BRIDGE,
		MICROSCOPE_LEFT_STAND,
		MICROSCOPE_RIGHT_STAND,
		MICROSCOPE_OBSERVATION_DIAPHRAGM,
		MICROSCOPE_COLOUR_COMPENSATION,
		MICROSCOPE_TURRET,  // general "turret"
		MICROSCOPE_INCIDENT_LIGHT_UNIT,
		MICROSCOPE_TRANSMITTED_LIGHT_UNIT,
		MICROSCOPE_TL_SHUTTER,
		MICROSCOPE_IL_SHUTTER,
		STEREO_MICROSCOPE,
		MICROSCOPE_DIAPHRAGM,
		MICROSCOPE_IRIS_DIAPHRAGM,
		MICROSCOPE_MOTORZOOM,
		MICROSCOPE_FLUORESCENCE_UNIT,
		MICROSCOPE_TL_APERTURE_DIAPHRAGM,
		MICROSCOPE_TL_FIELD_DIAPHRAGM,
		MICROSCOPE_IL_APERTURE_DIAPHRAGM,
		MICROSCOPE_IL_FIELD_DIAPHRAGM,
		MICROSCOPE_IL_ATTENUATOR,
		MICROSCOPE_PORTS,
		MICROSCOPE_TL_POLARIZER,
		MICROSCOPE_MANUAL_UNIT,  // the unit does not provide electronic support
		MICROSCOPE_MANUAL_DIC_SLIDER,
		MICROSCOPE_SLIDER,
		MICROSCOPE_EXTERNAL_UNIT,
		MICROSCOPE_CONTROLLER_BOARD,
		MICROSCOPE_STAGE_LR_SYNC,
		MICROSCOPE_ZDRIVE_LR_SYNC,
		MICROSCOPE_COAXIAL_LIGHT_UNIT,
		MICROSCOPE_OBLIQUE_LIGHT_UNIT,
		MICROSCOPE_MEMORY_FUNCTION_UNIT,
		MICROSCOPE_VIRTUAL_UNIT,
		MICROSCOPE_ZDRIVE_FINE,
		MACROSCOPE,
		MICROSCOPE_SIDEPORTS,
		MICROSCOPE_BOTTOMPORT,
		MICROSCOPE_SCREEN_CONTRAST,
		MICROSCOPE_SCREEN_ILLUMINATION,
		MICROSCOPE_IL_EXCITATION_MANAGER,
		MICROSCOPE_IL_FAST_FILTERS, // (IFW)
		MICROSCOPE_TL_FILTER,
		MICROSCOPE_TL_FILTER1,
		MICROSCOPE_TL_FILTER2,
		MICROSCOPE_TL_MIRROR,
		MICROSCOPE_IL_MIRROR,
		MICROSCOPE_MIRROR,
		MICROSCOPE_TIRF_UNIT,
		MICROSCOPE_TIRF_POSITIONER,
		MICROSCOPE_TIRF_COLLIMATOR,
		MICROSCOPE_TIRF_LASER,
		MICROSCOPE_LASER,
		MICROSCOPE_TIRF_SAFETY_ATTENUATOR,
		MICROSCOPE_TIRF_SHUTTER,
		MICROSCOPE_TL_ATTENUATOR,
		MICROSCOPE_TL_ISOCOL,
		MICROSCOPE_LIGHT_UNIT,
		MICROSCOPE_FUNCTION_WHEELS,
		MICROSCOPE_HAND_CONTROL,
		MICROSCOPE_STAGE_WELL_HANDLING,
		MICROSCOPE_DUOPORT,
		MICROSCOPE_VISUAL_ZOOM,
		MICROSCOPE_VIDEO_ZOOM,
		MICROSCOPE_IL_FAST_FILTER_WHEELS,
		MICROSCOPE_IL_FAST_FILTER_WHEEL,
		MICROSCOPE_IL_FAST_FILTER_WHEEL_ATTENUATOR,
		MICROSCOPE_IL_FAST_FILTER_WHEEL_EXCITER,
		MICROSCOPE_IL_FAST_FILTER_WHEEL_EMITTER,
		MICROSCOPE_FOOT_CONTROL,
		MICROSCOPE_CLS_SHUTTER,
		MICROSCOPE_CONOSCOPY_UNIT,
		MICROSCOPE_PORT_MAGNIFICATION_CHANGER,
		MICROSCOPE_TL_CCIC_FILTER,
		MICROSCOPE_UNIVERSAL_MANUAL_CONTROL,
		MICROSCOPE_JOYSTICK,
		MICROSCOPE_SMARTMOVE,
		MICROSCOPE_SEQUENCER,
		MICROSCOPE_SEQUENCING,
		MICROSCOPE_SDCONFOCAL_UNIT,
		MICROSCOPE_SDCONFOCAL_EXCITATION_WHEEL,
		MICROSCOPE_SDCONFOCAL_EMISSION_WHEEL,
		MICROSCOPE_SDCONFOCAL_DICHROIC_WHEEL,
		MICROSCOPE_SDCONFOCAL_DISK_SLIDER,
		MICROSCOPE_SDCONFOCAL_SHUTTER,
		MICROSCOPE_SDCONFOCAL_PRISM_SLIDER,
		MICROSCOPE_SDCONFOCAL_FRAP_IRIS,
		MICROSCOPE_SDCONFOCAL_VAR_INTENSITY_IRIS,
		MICROSCOPE_SDCONFOCAL_ILTURRET,
		MICROSCOPE_COLD_LIGHT_SOURCE,
		MICROSCOPE_CLS_LAMP,
		MICROSCOPE_IL_LAMP,
		MICROSCOPE_TL_LAMP,
		MICROSCOPE_OL_LAMP,
		MICROSCOPE_CL_LAMP,
		MICROSCOPE_CL_SHUTTER,
		MICROSCOPE_OL_SHUTTER,
		MICROSCOPE_ARCLIGHT_UNIT,
		MICROSCOPE_ARCLIGHT_INTENSITY,
		MICROSCOPE_ARCLIGHT_SHUTTER,
		MICROSCOPE_ARCLIGHT_SCENE,
		MICROSCOPE_RINGLIGHT_UNIT,
		MICROSCOPE_RINGLIGHT_INTENSITY,
		MICROSCOPE_RINGLIGHT_SHUTTER,
		MICROSCOPE_RINGLIGHT_SCENE,
		MICROSCOPE_SDCONFOCAL_SPINNING_DISK,
		MICROSCOPE_SEQUENCER_TIMESTAMPS,
		MICROSCOPE_CAMERA_INTERFACE,
		MICROSCOPE_FILES,
		MICROSCOPE_IL_LEDS,
		MICROSCOPE_IL_LED,
		MICROSCOPE_LEDCXI_UNIT,		//Follow Marketing name convention, LED Coax Illumination
		MICROSCOPE_LEDCXI_INTENSITY,
		MICROSCOPE_LEDCXI_SHUTTER,
		MICROSCOPE_LEDCXI_SCENE,
		MICROSCOPE_LEDNVI_UNIT,		//Follow Marketing name convention, LED Near Vertical Illumination
		MICROSCOPE_LEDNVI_INTENSITY,
		MICROSCOPE_LEDNVI_SHUTTER,
		MICROSCOPE_LEDNVI_SCENE,
		MICROSCOPE_SMARTTOUCH,		// SmartTouch (TCU)
		MICROSCOPE_ZOOM_DISPLAY,	// display for M205A, M205FA 
		MICROSCOPE_DATA_CONVERSION_INTERFACE,	// communication ports at focus column (DCI-MST5x)
		MICROSCOPE_IL_LEDS_SLIDER,
		MICROSCOPE_RESERVED0, 
		MICROSCOPE_RESERVED1, 
		MICROSCOPE_LED_UNIT,      // configurable external LED illumination unit
		MICROSCOPE_LED_INTENSITY, // intensity control of LED illumination
		MICROSCOPE_LED_SHUTTER,   // shutter control of LED illumination
		MICROSCOPE_LED_SCENE,     // scene control of LED illumination
		MICROSCOPE_RESERVED2,
		INVERTED_MICROSCOPE,   // inform if microscope is inverted
		MICROSCOPE_ROTARY_HEAD,   // rotary head for VZ-series
		MICROSCOPE_LEDHDI_UNIT,  // LED HDI
		MICROSCOPE_LEDHDI_INTENSITY,
		MICROSCOPE_LEDHDI_SHUTTER,
		MICROSCOPE_LEDHDI_SCENE,
		MICROSCOPE_DVMLED1_UNIT,  // DVMLED 1
		MICROSCOPE_DVMLED1_INTENSITY,
		MICROSCOPE_DVMLED1_SHUTTER,
		MICROSCOPE_DVMLED2_UNIT,  // DVMLED 2
		MICROSCOPE_DVMLED2_INTENSITY,
		MICROSCOPE_DVMLED2_SHUTTER,
		MICROSCOPE_SEQUENCER_REALTIME_TIMESTAMPS, // alternative timestamps unit
		MICROSCOPE_IL_STRUCTURED_ILLUMINATION,
		MICROSCOPE_IL_STRUCTURED_ILLUMINATION_APERTURE_DIAPHRAGM,
		MICROSCOPE_RESERVED3,
		MICROSCOPE_WATERPUMP,
		MICROSCOPE_IL_UV_SHUTTER,
		MICROSCOPE_RESERVED4,
		MICROSCOPE_RESERVED5,
		MICROSCOPE_RESERVED6,
		MICROSCOPE_RESERVED7,
		MICROSCOPE_RESERVED8,
		MICROSCOPE_RESERVED9,
		MICROSCOPE_TL_CONTRASTING_TUNING, // TL Contrasting Tuning for MDG4x
		MICROSCOPE_TL_TILT, // TL tilt table for Brightfield and Darkfield.
		MICROSCOPE_TL_INTENSITY,
		MICROSCOPE_NOSEPIECE_MOTCORR, // motorized corr
		MICROSCOPE_CONTRASTING_METHODS_AUTOMATED,
		MICROSCOPE_VIDEO_DEPTH_OF_FIELD_UNIT,
		MICROSCOPE_VIDEO_RESOLUTION_UNIT,
		MICROSCOPE_VIDEO_FIELD_OF_VIEW_WIDTH_UNIT,
		MICROSCOPE_VIDEO_FIELD_OF_VIEW_HEIGHT_UNIT,
		MICROSCOPE_VISUAL_DEPTH_OF_FIELD_UNIT,
		MICROSCOPE_VISUAL_RESOLUTION_UNIT,
		MICROSCOPE_VISUAL_FIELD_OF_VIEW_UNIT,
		MICROSCOPE_LEDSLI_UNIT,
		MICROSCOPE_LEDSLI_INTENSITY,
		MICROSCOPE_LEDSLI_SHUTTER,
		MICROSCOPE_LEDSLI_SCENE,
		MICROSCOPE_ACTIVE_UNIT,
		MICROSCOPE_NUMERICAL_APERTURE_UNIT,
		MICROSCOPE_RESERVED10,
		MICROSCOPE_HAND_CONTROL_Z,
		MICROSCOPE_BACKLIGHT_INTENSITY, // intensity control of Device BackLight illumination
		MICROSCOPE_BACKLIGHT_SHUTTER,   // shutter control of Device BackLight illumination
		MICROSCOPE_POSITIONS_MEMORY,	// virtual unit positions store DM8/12000
		MICROSCOPE_DVM, // DVM and VZ series (Digital Versatile Microscope)
		MICROSCOPE_DMS, // DMS Series (Cyclop)
		MICROSCOPE_GENERIC, // TO Define a unit that is generic
		MICROSCOPE_CLIMATE_CONTROL,
		MICROSCOPE_CLIMATE_UNIT,
		MICROSCOPE_ZDRIVE_CLOSED_LOOP,
		MICROSCOPE_LASER_DUAL_SHUTTER,
		MICROSCOPE_STAGE_ROTATION_UNIT,
		MICROSCOPE_COLUMN_TILT_UNIT,
		MICROSCOPE_SIMULTANEOUS_IMAGING_SYSTEM, // Splitter, Multi-View, MultiCam (like Photometrics DV2 & QV2, Andor Optosplit II & TuCam, etc.)
		MICROSCOPE_FUNCTION_KEYS_LEDS,
		MICROSCOPE_LEDBLI_UNIT,
		MICROSCOPE_LEDBLI_INTENSITY,
		MICROSCOPE_LEDBLI_SHUTTER,
		MICROSCOPE_LEDDI_UNIT,  // LED DI
		MICROSCOPE_LEDDI_INTENSITY,
		MICROSCOPE_LEDDI_SHUTTER,
		COMPOUND_MATERIAL_MICROSCOPE,
		MICROSCOPE_SPIM_OBJECTIVE_HOLDER,
		MICROSCOPE_SPIM_FILTER_TURRET,
		MICROSCOPE_SPIM_OBJECTIVE_TURRET,
		MICROSCOPE_T_HOUSE,
		MICROSCOPE_TESTABLE_KEYS,
		MICROSCOPE_ACQUIMATOR,
		MICROSCOPE_DVM_AUTOFOCUS,	// DVM internal autofocus
		MICROSCOPE_FRAP,
		MICROSCOPE_FRAP_DIAPHRAGM,
		MICROSCOPE_FRAP_LASER,
		MICROSCOPE_IL_UV_LAMP, // DM8/12000 UV lamp
		MICROSCOPE_RFID_UNIT,  // unit supports RFID for detecting components - not mandatory when unit is always RFID based
		MICROSCOPE_SEQUENCER_ADVANCED,
		MICROSCOPE_SEQUENCER_ADVANCED_UNIT, // sub unit of seq. adv.
		MICROSCOPE_SEQUENCER_ADVANCED_TTL,  // ttl (digital) input or output unit
		MICROSCOPE_SEQUENCER_ADVANCED_ANALOG,// analog input or output unit
		MICROSCOPE_SEQUENCER_ADVANCED_LASERBOX,
		MICROSCOPE_FIBERSWITCH,
		MICROSCOPE_SEQUENCER_ADVANCED_LASER,
		MICROSCOPE_SEQUENCER_ADVANCED_INPUT, // input
		MICROSCOPE_SEQUENCER_ADVANCED_OUTPUT, // output
		MICROSCOPE_SEQUENCER_ADVANCED_LASERBOX_GENERIC, // to distinguish laserboxes
		MICROSCOPE_SEQUENCER_ADVANCED_TIRF_LASER,
		MICROSCOPE_SCANHEAD,
		MICROSCOPE_SCANHEAD_DIAPHRAGM,
		MICROSCOPE_SCANHEAD_ATTENUATOR,
		MICROSCOPE_SCANHEAD_AFOCAL_LENS,
		MICROSCOPE_SCANHEAD_SHIFT_PRISM,
		MICROSCOPE_INFINITY_SCANNER,
        MICROSCOPE_LASER_SPECTROSCOPY,
		MICROSCOPE_SEQUENCER_ADVANCED_LASER_DUAL_SHUTTER,
		MICROSCOPE_BARCODE_SCANNER,
		MICROSCOPE_IL_LAMP_SWITCH,
		MICROSCOPE_SEQUENCER_ADVANCED_PULSED_LASER,
		MICROSCOPES,
		MICROSCOPE_LIGHT_GUARD,
		MICROSCOPE_BARCODE_SCANNERS,
		MICROSCOPE_SEQUENCER_ADVANCED_PULSED_LASER_GUARD,
		__MICROSCOPE_MAX
	} EMicroscopeTypeId;

	typedef enum microscopeiid {
		__MICROSCOPE_IID_START=0x1000,
		IID_MICROSCOPE_CONTRASTING_METHODS = __MICROSCOPE_IID_START,
		IID_MICROSCOPE_CONTRASTING_METHODS_SPECIAL,
		IID_MICROSCOPE_RESERVED0,
		IID_MICROSCOPE_MEMORY,
		IID_MICROSCOPE_CONTRASTING_METHODS_LOOKAHEAD,
		IID_MICROSCOPE_RESERVED1,
		IID_MICROSCOPE_SHEARING,
		IID_MICROSCOPE_IL_SHEARING,
		IID_MICROSCOPE_TIRF_CALIBRATION,
		IID_MICROSCOPE_TIRF_AZIMUTH,
		IID_MICROSCOPE_TIRF_APERTURE,
		IID_MICROSCOPE_TRIGGER_TABLE,
		IID_MICROSCOPE_IL_FAST_FILTER_WHEEL_CALIBRATION,
		IID_MICROSCOPE_REFLECTION,
		IID_MICROSCOPE_LASER_SEQUENCING,
		IID_MICROSCOPE_TIRF_SEQUENCING,
		IID_MICROSCOPE_CALIBRATION_TABLE,
		IID_MICROSCOPE_SCENE_SEQUENCE,
		IID_MICROSCOPE_SEQUENCER_TIMESTAMPS,
		IID_MICROSCOPE_SEQUENCER_CONTROL,
		IID_MICROSCOPE_TIRF_SERVICE,
		IID_MICROSCOPE_FILES_OBJECTIVE,
		IID_MICROSCOPE_ZOOM_CALIBRATION,
		IID_MICROSCOPE_RESERVED2,
		IID_MICROSCOPE_RESERVED3,
		IID_MICROSCOPE_RESERVED4,
		IID_MICROSCOPE_SEQUENCER_TRIGGERING_SETUP,
		IID_ACQUIMATOR,
		IID_MICROSCOPE_DVM_AUTOFOCUS,
		IID_MICROSCOPE_IL_TURRET_RFID_SETUP,
		IID_MICROSCOPE_CONTRASTING_METHODS_UPDATE,
		IID_MICROSCOPE_SEQADV_CONTROL,
		IID_MICROSCOPE_SEQADV_CONTROL_ERROR,
		IID_MICROSCOPE_SCANHEAD_CONTROL,
		IID_MICROSCOPE_LASER_SPECTROSCOPY,    // DSO: Interface to rapID Unit
		IID_MICROSCOPE_BARCODE_SCANNER,
		__MICROSCOPE_IID_MAX,
	} EMicroscopeInterfaceId;



	/**
	 * With the MicroscopeContrastingMethods interface
	 * the current contrasting method can be retrieved or changed.
	 * MicroscopeContrastingMethods is supported by DM40000 and DM5000
	 *
	 * IID: IID_MICROSCOPE_CONTRASTING_METHODS
	 */

	class MicroscopeContrastingMethods { // IID_MICROSCOPE_CONTRASTING_METHODS
	public:

		/**
		 *  Retrieve the current active method
		 *  @return integer based method id
		 */
		virtual iop::int32 getContrastingMethod() = 0;
		/**
		 *  Retrieve the current active method
		 *  @return integer based method id
		 */
		virtual void setContrastingMethod(iop::int32 methodId) = 0;

#define MICROSCOPE_CONTRASTING_METHODS_VERSION2
#ifdef MICROSCOPE_CONTRASTING_METHODS_VERSION2
		typedef enum eClassInfo { IID=ahm::IID_MICROSCOPE_CONTRASTING_METHODS, INTERFACE_VERSION=2 } EClassInfo;

		/**
		 * Retrieve all methods.
		 * This is the list of all methods supported by the driver.
		 */
		virtual IdList * allMethods() = 0;

		/**
		 * Retrieve the supported methods.
		 * This is the list of of the actual configured methods supported by
		 * the actual connected hardware.
		 * Meaning these methods are currently supported.
		 */
		virtual IdList * supportedMethods() = 0;

		/**
		 * name service
		 */
		virtual IdNames *methodNames() = 0;
#endif
	};


	typedef enum eMicrocopeDefinedValueIds {
		__MICROSCOPE_DEFINED_VALUE_START=0x1000,
		MICROSCOPE_ZDRIVE_FOCUS,
		MICROSCOPE_ZDRIVE_LOWER_THRESHOLD,
		MICROSCOPE_ZDRIVE_UPPER_THRESHOLD,
		__MICROSCOPE_DEFINED_VALUE_MAX
	} EMicrocopeDefinedValueIds;



	/**
	 **  special interface for CS access
	 **
	 **  IID: IID_MICROSCOPE_CONTRASTING_METHODS_SPECIAL
	 **/

	class MicroscopeContrastingMethodsSpecial { // IID_MICROSCOPE_CONTRASTING_METHODS_SPECIAL
	public:
		typedef enum eClassInfo { IID = IID_MICROSCOPE_CONTRASTING_METHODS_SPECIAL } EClassInfo;
		virtual void toggleCSMethod() = 0;
	};



	/**
	 * With the MicroscopeMemoryFunctions interface
	 * ...
	 *
	 * IID: IID_MICROSCOPE_MEMORY
	 */

	class MicroscopeMemory { // IID_MICROSCOPE_MEMORY
	public:
		typedef enum eClassInfo { IID = IID_MICROSCOPE_MEMORY } EClassInfo;
		virtual iop::int32 minMemory()=0;
		virtual iop::int32 maxMemory()=0;
		virtual void clearMemory(iop::int32 index) = 0;
		virtual void saveCurrentToMemory(iop::int32 index)=0;
		virtual void recallMemory(iop::int32 index) = 0;
		virtual bool isMemorySet(iop::int32 index) = 0;
	};


	/**
	 ** Interface for contrasting methods look ahead
	 ** allows to lookahead or preselect the  prism or cube for automatic
	 ** for the next change to a contrasting method.
	 ** Related interface: MicroscopeContrastingMethods
	 **
	 **  IID: IID_MICROSCOPE_CONTRASTING_METHODS_LOOKAHEAD
	 **/

	class MicroscopeContrastingMethodsLookahead { // IID_MICROSCOPE_CONTRASTING_METHODS_LOOKAHEAD
	public:
		typedef enum eClassInfo { IID = IID_MICROSCOPE_CONTRASTING_METHODS_LOOKAHEAD } EClassInfo;

		/**
		 ** get the look ahead control value for the contrasting method passed by
		 ** passed by method id
		 **/

		virtual iop::int32 lookaheadControlValue(iop::int32 methodId) = 0;
		/**
		 ** set the look ahead control value for the contrasting method passed by
		 ** passed by method id
		 ** via MicroscopeContrastingMethod::setContrastinMethod,
		 ** this position/control value will be set.
		 **/


		virtual void setLookaheadControlValue(iop::int32 methodId, iop::int32 nLookheadControlValue) = 0;
	};




	class ShearingEntry : public Reserved {
	public:
		// use properties: PROP_CONDENSER_TURRET_POSITION, PROP_DIC_TURRET_POSITION
		virtual void setPosition(iop::int32 propertyId, iop::int32 pos) = 0;
		virtual iop::int32 getPosition(iop::int32 propertyId) = 0;
	};

	class ShearingTable : public Reserved {
	public:
		virtual iop::int32 numEntries() = 0;
		virtual void clear() = 0;
		virtual ShearingEntry* addEntry() = 0;
		virtual ShearingEntry* getEntry(iop::int32 index) = 0;
		virtual void dispose() = 0;
	};


	// interface class // IID_MICROSCOPE_SHEARING
	class MicroscopeShearing {
	public:
		typedef enum eClassInfo { IID = IID_MICROSCOPE_SHEARING } EClassInfo;
		virtual ShearingTable * getObjectiveShearing(iop::int32 objectivePos) = 0;
		virtual void setObjectiveShearing(iop::int32 objectivePos, ShearingTable *pShearingTable) = 0;
		virtual ShearingTable * createShearingTable() = 0;

		virtual void clearShearing(iop::int32 objectivePos) = 0;
		virtual void activateShearing(iop::int32 shearingTableIndex) = 0;   // activates Shering for current objective ( 0>=index< numEntries )
		virtual iop::int32 activeShearing() = 0;
	};

	class MicroscopeIlShearing : public MicroscopeShearing {
	public:
		typedef enum eClassInfo { IID = IID_MICROSCOPE_IL_SHEARING } EClassInfo;
	};


	// interface class // IID_MICROSCOPE_TIRF_CALIBRATION
	class TirfCalibration : public ahm::AutoCalibration {
	public:
		//typedef enum eCalibrationMode { CALIBRATE_TIRF_SIMPLE, CALIBRATE_TIRF_AND_ALIGN } ECalibrationMode;

#define IID_MICROSCOPE_TIRF_CALIBRATION2
#ifdef IID_MICROSCOPE_TIRF_CALIBRATION2
		typedef enum eClassInfo { IID=ahm::IID_MICROSCOPE_TIRF_CALIBRATION, INTERFACE_VERSION=2 } EClassInfo;
#else
		typedef enum eClassInfo { IID = IID_MICROSCOPE_TIRF_CALIBRATION } EClassInfo;
#endif
		virtual void align() = 0;
		virtual bool isFineTuned() = 0;
	};

	// interface class // IID_MICROSCOPE_TIRF_APERTURE
	class TirfAperture : public ahm::BasicControlValue {
	public:
		typedef enum eClassInfo { IID = IID_MICROSCOPE_TIRF_APERTURE } EClassInfo;
	};

	// interface class // IID_MICROSCOPE_TIRF_AZIMUTH
	class TirfAzimuth : public ahm::BasicControlValue {
	public:
		typedef enum eClassInfo { IID = IID_MICROSCOPE_TIRF_AZIMUTH } EClassInfo;
		typedef enum eDirections {	NORTH=0,
									NORTHEAST=45,
									EAST=90,
									SOUTHEAST=135,
									SOUTH=180,
									SOUTHWEST=225,
									WEST=270,
									NORTHWEST=315
								} EDirection;
		
	};

	// interface class // IID_MICROSCOPE_TIRF_SERVICE
	class TirfService {
	public:
		typedef enum eClassInfo { IID = IID_MICROSCOPE_TIRF_SERVICE } EClassInfo;

		virtual iop::int32 penetrationDepthIndexFromAperture(iop::int32 waveLength, iop::float64 tirfAperture) = 0;
		virtual iop::float64 apertureFromPenetrationDepthIndex(iop::int32 waveLength, iop::int32 penetrationDepthIndex) = 0;

	};


	class MicroscopeTriggerTable {
	public:
		typedef enum eClassInfo { IID = IID_MICROSCOPE_TRIGGER_TABLE } EClassInfo;

		/*
		 * clear complete table
		 */
		virtual void clearTable() = 0;

		/*
		 * clear unit "column"
		 */
		virtual void clear(ahm::Unit *pUnit) = 0;
		/*
		 * retrieve number of entries for unit "column"
		 */
		virtual iop::int32 numEntries(ahm::Unit *pUnit) = 0;

		/*
		 * retrieve entry (position) from unit "column"
		 */

		virtual iop::int32 getEntry(ahm::Unit *pUnit, iop::int32 index) = 0;

		/*
		 * add new position entry for unit
		 */

		virtual void add(ahm::Unit *pUnit, iop::int32 nControlValue) = 0;
		/**
		 * copy table to microsocope
		 */
		virtual void flush() = 0;

		/*
		 * retrieve current index (cursor) for unit
		 */
		virtual iop::int32 triggerIndex(ahm::Unit *pUnit) = 0;
		/*
		 * retrieve current index (cursor) for unit
		 */
		virtual void setTriggerIndex(ahm::Unit *pUnit, iop::int32 index) = 0;
		/**
		 * trigger mode
		 */
		virtual iop::int32 triggerMode() = 0;
		virtual void setTriggerMode(iop::int32 mode) = 0;
	};


	class MicroscopeIlFastFilterWheelCalibration : public ahm::AutoCalibration {
	public:
		typedef enum eClassInfo { IID = IID_MICROSCOPE_IL_FAST_FILTER_WHEEL_CALIBRATION } EClassInfo;
		virtual void startCalibration() = 0; // start calibration mode
	};

	class MicroscopeReflection {
	public:
		typedef enum eClassInfo { IID = IID_MICROSCOPE_REFLECTION } EClassInfo;
		virtual iop::int32 checkCommandSupport(iop::string command) = 0;
		virtual ahm::TypeId getExposedTypeId(iop::string command) = 0;
	};



	class MicroscopeCalibrationTable {
	public:
		typedef enum eClassInfo { IID = IID_MICROSCOPE_CALIBRATION_TABLE } EClassInfo;
		virtual iop::int32 numEntries() = 0;
		virtual iop::int32 encoderEntry(iop::int32 index) = 0;
		virtual iop::float64 calibratedEntry(iop::int32 index) = 0;
		virtual iop::float64 hysteresisEntry(iop::int32 indexEntry) = 0;
	};

	class MicroscopeZoomCalibration {
	public:
		typedef enum eClassInfo { IID = IID_MICROSCOPE_ZOOM_CALIBRATION } EClassInfo;
		//! is the device calibrated
		virtual bool isCalibrated() = 0;
		//! start calibration mode
		virtual void startCalibration() = 0;
		//! save current calibrated data
		virtual bool saveCalibration() = 0;
		//! get the calibrated data
		virtual iop::string getCalibrationData() = 0;
		//! set the zoom with calibrated data
		virtual bool setCalibrationData(iop::string data) = 0;
		//! clear the calibration data
		virtual bool clearCalibration() = 0;
		//! goto calibrated position
		virtual void gotoCalibrationPos() = 0;
	};

	// DVM only
	class MicroscopeDVMAutofocus {
	public:
		typedef enum eClassInfo { IID = IID_MICROSCOPE_DVM_AUTOFOCUS, VERSION=2 } EClassInfo;
		// start autofocus 
		// parameter flagContinuous
		// - false -> single autofocus
		// - true -> start autofocus and keep focusing
		virtual void startAutofocusAsync(bool flagContinuous) = 0;
		// halt autofocus (interrupt - or stop continous)  
		virtual void halt() = 0;
		virtual bool isContinuous() = 0;
		virtual iop::int32 getState() = 0;
		// run autofocus once, returns state (synchronous)
		virtual iop::int32 runAutofocus() = 0;

		// RegionOfInterest ROI
		virtual ahm::INT_RECT getROI() = 0;
		virtual void setROI(ahm::INT_RECT *pROI) = 0;

		// get valid region of ROI
		virtual ahm::INT_RECT getValidRegionOfROI() = 0;

		// min and max ROI
		virtual ahm::INT_RECT getMinROI() = 0;
		virtual ahm::INT_RECT getMaxROI() = 0;
	};


	// interface class // IID_MICROSCOPE_IL_TURRET_RFID_SETUP
	class MicroscopeIlTurretRFIDSetup : public ahm::AutoCalibration {
	public:
		typedef enum eClassInfo { IID = IID_MICROSCOPE_IL_TURRET_RFID_SETUP } EClassInfo;
		/**
		 *  flush - stores cube data for position
		 */
		virtual void flushCubeData(iop::int32 pos) = 0;
	};


   /**
	** Interface for contrasting methods update
    ** The supported contrasting methods can change during the lifetime of the unit tree
	** for example by configuration.
	** MicroscopeContrastingMethods returns a "constant" IdList for the methods.
	** Accessing and iterating the supported list would be unpredictable when the list
	** changes in between.
    **
	**  IID: IID_MICROSCOPE_CONTRASTING_METHODS_UPDATE
	**/

	class MicroscopeContrastingMethodsUpdate {
	public:
		typedef enum eClassInfo { IID = IID_MICROSCOPE_CONTRASTING_METHODS_UPDATE } EClassInfo;

		/**
		 * update supported methods
		 * 
		 * advanced - 
		 * synchronizes the supported methods IdList from MicroscopeContrastingMethods
		 * call this when you are safe the list is not iterated
		 *
		 *  - usually this is not neccessary - because the configuration does not change during unit lifetime
		 */

		virtual void updateSupportedMethods() = 0;
	};



};

#endif // PUBLIC_AHM_MICROSCOPE_H
