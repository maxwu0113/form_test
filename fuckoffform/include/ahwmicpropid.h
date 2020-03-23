/**
 ** Copyright (c) 2002-2014 Leica Microsystems - All Rights Reserved
 **
 ** ahwmicpropid.h: Property ids for microscope properties
 **
 **/
#ifndef PUBLIC_AHM_MICROSCOPE_PROPID_H
#define PUBLIC_AHM_MICROSCOPE_PROPID_H


typedef enum eproperties
{
	PROP_STAND = 0x100,			// stand properties
	PROP_STAND_ARTICLE_CODE,    // "Typenschild"-Information     Ariticle No.
	PROP_STAND_ORDER_NUMBER,	// "Typenschild"-Information     Order No.
	PROP_STAND_SERIAL_NUMBER,   // "Typenschild"-Information     Ariticle No.
	PROP_STAND_ASSEMBLY_QUARTER,// "Typenschild"-Information     Quarter of Assembly
	PROP_STAND_CONSTRUCTION_STATE,// "Typenschild"-Information     construction level
	PROP_STAND_CONSTRUCTION_LEVEL = PROP_STAND_CONSTRUCTION_STATE, // alias
	PROP_STAND_DATE,			// "Typenschild"-Information     Date of Assembly
	PROP_STAND_NAME,			// "Typenschild"-Information     Name Information
	PROP_STAND_METHODS,			// Methods, the stand is supporting
	PROP_STAND_ACT_METHOD,		// the current method????
	PROP_STAND_METHOD_PAR,		// RESERVED
	PROP_STAND_INFO_DATA,		// RESERVED HOST info records
	PROP_STAND_PROTECTED,		// protected access to Factory settings
	PROP_STAND_ALLOW_OPERATING_CONTROLS,  // disable/enable stand controls ( stand buttons, touchscreen, ...)
	PROP_STAND_CONFIGURATION_MODE, //enable/disable configuration mode
	PROP_STAND_CONFIGURATION_SOFTWARE_VERSION_INFOS, // string version infos of configuration software used to configure the stand (i.e. product version, or config db version)

	PROP_FIRMWARE=0x200,					// Firmware information (array)
	PROP_FIRMWARE_MODULE_NAME,			// firmware module name
	PROP_FIRMWARE_MODULE_VERSION,		// firmware module version
	PROP_DRIVER_VERSION,					// For Firmware package tracking base on driver version
	PROP_DRIVER_MAJOR_VERSION,			//same as above
	PROP_DRIVER_MINOR_VERSION,			//same as above
	PROP_DRIVER_MAINTENANCE_VERSION,	//same as above
	PROP_DRIVER_READY,					// True - Driver ready & device Ready, False - Driver or Device not ok.

	// ADAPTING LENS PROPERTIES
	PROP_ADAPTING_LENS=0x900,	// internal property tl adapting lens
	PROP_ADAPTING_LENS_FIXPOS1, // internal property tl adapting lens
	PROP_ADAPTING_LENS_FIXPOS2, // internal property tl adapting lens
	PROP_ADAPTING_LENS_BYPASS,  // internal property tl adapting lens

	// NOSEPIECE PROPERTIES / OR COMMON
	PROP_NOSEPIECE=0x1000,	// nosepiece properties
	PROP_OBJECTIVES,		// array of objectives
	PROP_OBJECTIVE,			// objective information
	PROP_MAGNIFICATION,		// the mag
	PROP_ARTICLE_NO,		// article no
	PROP_APERTURE,			// aperture for objective
	PROP_METHODS,			// the methods
	PROP_OBJECTIVE_TYPE,	// objective type dry, imm, combi
	PROP_CONDENSER_TURRET_POSITION,	// condenser turret pos depending on method
	PROP_DIC_TURRET_POSITION,		// dic turret pos depending on method
	PROP_FIELD_DIA_TL,			// TL field diaphragm pos depending on method
	PROP_APERTURE_DIA_TL,		// TL aperture diaphragm pos depending on method
	PROP_FIELD_DIA_IL,			// IL field diaphragm pos depending on method
	PROP_APERTURE_DIA_IL,		// IL aperture diaphragm pos depending on method
	PROP_LAMP_INTENSITY,		// lamp intensity depending on method
	PROP_STEPWIDTH,			    // step width property   ( Janus, Skywalker)
	PROP_ADJUST,                // adjust property (adjust current position)
	PROP_PARFOCALITY,			// parfocality for mot Z/Nosepiece CM
	PROP_NOSEPIECE_MODE_DRY_IMM,     // stand mode dry/imm
	PROP_NOSEPIECE_MODE_AUTO_LOWERZ, // automatically lower z depending on immersion objectives

	PROP_STEP_MODE,            // property allowing to change between fine and coarse mode (Discovery ZDrive, Stage)
	PROP_OBJECTIVE_TYPE_COMBI_FLAG, // W (OBJECTIVE_TYPE) ==> Combi Yes/No
	PROP_OBJECTIVE_SPECIALTIES,   	// objective tirf 2005/12/09
	PROP_OBJECTIVE_FORCE_AUTO_LOWERZ,     // flag if automatic lowering if forced for this objective
	PROP_TL_SHUTTER_MODE,           // TL Shutter mode 2006/07/12  change automatics on shutter  
	PROP_PARCENTRICITY_X,			// 2006/08/01 parcentricity (calibrate x,y for objectives) in control steps!
	PROP_PARCENTRICITY_Y,			// 2006/08/01 parcentricity (calibrate x,y for objectives) in control steps!
	PROP_PARCENTRICITY_MODE,        // 2006/08/01 parcentricity enable/disable parcentricity automatics
	PROP_SMARTMOVE_SENSITIVITY_FACTOR,     // 2006/09/01 float64 factor for smart move sensitivity
	PROP_OBJECTIVE_DIPPING,					// 2007/04/24 dipping in control steps for objectives
	PROP_TURN_MODE,        //2007/07/10 mode 1 ==> turn - do not move over max position
	PROP_PATHO_MODE,       //2007/09/07 special patho mode 0:Normal, 1:Shutter in; 2:Quick check;
	PROP_OBJECTIVE_TIRF_SCAN_CONVERSION_X,		// tirf aperture to scan controls conversion factors
	PROP_OBJECTIVE_TIRF_SCAN_CONVERSION_Y,
	PROP_OBJECTIVE_TIRF_ALIGN_START_POS,		// start position of tirf auto-align
	PROP_OBJECTIVE_TIRF_ALIGN_END_POS,			// end position of tirf auto-align
	PROP_OBJECTIVE_TIRF_ALIGN_SPEED,			// scanner speed at tirf auto-align
	PROP_OBJECTIVE_TIRF_ALIGN_SB_RATIO,			// minimum signal to background light ratio for a valid tirf auto-align
	PROP_OBJECTIVE_TIRF_ALIGN_THRESHOLD,		// tirf zone threshold
	PROP_PITCH,                                 // float pitch in millimeters 2008/02/11 DM stage x,y
	PROP_OBJECTIVE_COVERGLASS,					// 2008/05/15 string "-", millimeters/ range of millimeters "0.7-1.2"
	PROP_OBJECTIVE_FREE_WORKING_DISTANCE,       // string free working distance
	PROP_OBJECTIVE_TYPENAME,                    // string objective type name (class) for example HCX PL FLUOTAR
	__PROP_OBJECTIVE_RESERVED0_START,
	__PROP_OBJECTIVE_RESERVED0_MAX=__PROP_OBJECTIVE_RESERVED0_START+16, // reserved
	PROP_HARDWARE_CONTROLLER_GENERATION, // hardware generation of controller (zdrive, stage)
	__PROP_OBJECTIVE_RESERVED1,
	__PROP_OBJECTIVE_RESERVED2,
	PROP_OBLIQUE_ILLUMINATION,  // int 0 off, int on
	PROP_MOTCORR_OBJECTIVE_INDEX, // int index of objective attached to mot corr
	PROP_OBJECTIVE_ILLUMINATION_MODE,		//  int switch on of objective (in)dependent illumination mode DM8/12000
	PROP_OBJECTIVE_AUTO_LOWERZ_DISTANCE,			// int auto lowering z distance in control steps

	// ILTURRET PROPERTIES
	PROP_ILTURRET = 0x1100,		// IL turret proerties
	PROP_ILTURRET_CUBES,		// array of cube
	PROP_ILTURRET_CUBE,			// cube struct
	PROP_ILTURRET_CUBE_NAME,	// name of cube
	PROP_ILTURRET_CUBE_DAZZLEPROTECTION,	// dazzle protection of cube
	PROP_ILTURRET_DAZZLEPROTECTION_MODE, // reserved
	PROP_ILTURRET_CUBE_METHODS,		// cube methods
	PROP_ILTURRET_SHUTTER_MODE,     // shutter mode 2005/02/17 change automatics on shutter
	PROP_IL_SHUTTER_MODE = PROP_ILTURRET_SHUTTER_MODE, // 2006/07/12 alias
	PROP_ILTURRET_CUBE_SPECIALTIES,   // cube tirf 2005/11/16
	PROP_ILTURRET_CUBE_FILTERSET,     // filter set name for external filters

	PROP_ILTURRET_CUBE_EXCITER_WAVELENGTH_MIN = 0x1110, //  min wavelength in nano meters for exciter
	PROP_ILTURRET_CUBE_EXCITER_WAVELENGTH_MAX,			//  max wavelength in nano meters for exciter
	PROP_ILTURRET_CUBE_BEAMSPLITTER_WAVELENGTH,			//  wavelength in nano meters for beamsplitter
	PROP_ILTURRET_CUBE_EMITTER_WAVELENGTH_MIN,			//  min wavelength in nano meters for emitter
	PROP_ILTURRET_CUBE_EMITTER_WAVELENGTH_MAX,			//  max wavelength in nano meters for exciter, for infinity use -1
	PROP_ILTURRET_CUBE_EMITTER_BANDS,					//  emitter bands comintation of color abbreviations (R , RG, RGB, GY)
	PROP_ILTURRET_CUBE_EXCITER_WAVELENGTH_BANDS,        //  string multiple wavelength bands in nano meters for exciter
	PROP_ILTURRET_CUBE_BEAMSPLITTER_WAVELENGTHES,       //  string multiple wavelengthes in nano meters for beamsplitter
	PROP_ILTURRET_CUBE_EMITTER_WAVELENGTH_BANDS,        //  string multiple wavelength bands in nano meters for emitter
	PROP_ILTURRET_CUBE_LED_WAVELENGTHES,                //  string  matching LED wavelengthes



	// COMPARISON BRIDGE
	PROP_COMPARISON_BRIDGE = 0x1140,	// comparison bridge properties
	PROP_COMPARISON_DIA_LEFT,			// position of the left diaphragm
	PROP_COMPARISON_DIA_RIGHT,			// position of the right diaphragm
	PROP_COMPARISON_BRIDGE_MASTER,		// set the left or right side to master for sync x,y or z pos
	PROP_COMPARISON_SYNC,				// get or set sync button 0 -> disable; 1 -> enable;
	PROP_COMPARISON_SYNC_FAST_MODE,     // xyz sync fast mode  0-> fast mode off, 1 fast mode on
	PROP_COMPARISON_SYNC_LEFT_RIGHT_OFFSET, // DMFSC left/right offset x,y

	// GROUP... = 0x1180, =0x11C0

	// MAGNIFICACTION CHANGER
	PROP_MAGCHANGER  =  0x1180,   		// magnification changer
	PROP_MAGCHANGER_LENSES,       		// array of lenses
	PROP_MAGCHANGER_LENS,         		// mag chg lens struct
	PROP_MAGCHANGER_LENS_NAME,    		// lens name of magchg
	PROP_MAGCHANGER_GAP1,		  		// gap
	PROP_MAGCHANGER_SETUP,        		// setup mag changer (mags)
	PROP_MAGCHANGER_LEFT_RIGHT_EQUAL,	// left and right mag is equal (Janus)

	// Condenser turret
	PROP_CONDENSERTURRET = 0x1200,	// Condenser turret
	PROP_CONDENSERTURRET_PRISMS,	// array of prisms
	PROP_CONDENSERTURRET_PRISM,		// condenser turret prism
	PROP_CONDENSERTURRET_PRISM_NAME,

	// Condenser
	PROP_CONDENSER = 0x1240,      // condenser top
	PROP_CONDENSER_NAME,          // S3, S21, ...
	PROP_CONDENSER_TOP_AUTO_MAGNIFICATION,      // objective magnification for automatic switching the top
	PROP_CONDENSER_TOP_MODE,                    // automatic on/off


	// IL FAST FILTERS (IFW)

	PROP_IFW = 0x1260,
	PROP_IFW_FILTERS,
	PROP_IFW_FILTER,
	PROP_IFW_FILTER_NAME,

	// TL FILTER (DMI)
	PROP_TL_FILTER = 0x12A0,
	PROP_TL_FILTER_NAME, // name of the filter


	// FAST FILTER WHEELS
	PROP_IL_FAST_FILTER_WHEEL = 0x12B0,
	PROP_IL_FAST_FILTER_WHEEL_FILTERSET_NAME,
	PROP_IL_FAST_FILTER_WHEEL_FILTERS_SETUP,
	PROP_IL_FAST_FILTER_WHEEL_FILTERS,
	PROP_IL_FAST_FILTER_WHEEL_FILTER_NAME,
	PROP_IL_FAST_FILTER_WHEEL_FILTER_TYPE,
	PROP_IL_FAST_FILTER_WHEEL_FILTER_TYPE_INDEX,

	// IL LEDS
	PROP_IL_LED = 0x12C0,
	PROP_IL_LED_NAME,
	PROP_IL_LED_WAVELENGTH,
	PROP_IL_LED_MAXPOWER,
	PROP_IL_LED_DAC_TABLE,
	PROP_IL_LED_SETUP_PROTECTION, 
	PROP_IL_LED_REVISION,
	PROP_IL_LED_WAVELENGTH_BANDWIDTH,
	PROP_IL_LED_RGBCOLOR,
	PROP_IL_LED_CONSTRUCTION_LEVEL,
	PROP_IL_LEDS_CHANNELSPECIFICINTENSITY,
	PROP_IL_LEDS_COMBI_LIGHT_SOURCE,

	//DIC turret
	PROP_DICTURRET = 0x1300,
	PROP_DICTURRET_PRISMS,
	PROP_DICTURRET_PRISM,
	PROP_DICTURRET_PRISM_NAME,
	PROP_DICTURRET_PRISM_FINE_POSITIONS, // int holding values per per objective

	// IL Field Diaphragm (overdue)
	PROP_IL_FIELD_DIAPHRAGM = 0x1310,
	PROP_IL_FIELD_DIAPHRAGM_ITEMS,
	PROP_IL_FIELD_DIAPHRAGM_ITEM,
	PROP_IL_FIELD_DIAPHRAGM_ITEM_DESCRIPTION,
	PROP_IL_FIELD_DIAPHRAGM_ITEM_TYPE,
	PROP_IL_FIELD_DIAPHRAGM_ITEM_TYPE_INDEX,


	// preferred control layout
	PROP_CONTROL_PREFERENCE = 0x1390,
	PROP_CONTROL_LANGUAGE, // English, Deutsch,...
	PROP_CONTROL_SCALE_UNIT, // metric, inch, MIL,...
	PROP_CONTROL_AUDIO_FEEDBACK, // type of audio feedback
	PROP_CONTROL_CONFIG_LOCK, // lock the configuration for restricted user
	PROP_CONTROL_COORDINATE_SYSTEM, // polar, cartesian,...
	PROP_CONTROL_POSITIONING, // absolute, relative,...
	PROP_CONTROL_MEASUREMENT, // reticule circle, field of view,...

	//FKey
	PROP_FKEYS_GROUP = 0x1400,
	PROP_FKEYS,
	PROP_FKEY_NAME,
	PROP_FKEY_FUNCTION,
	PROP_FKEY_CONTROLLED_DEVICE,
	PROP_FOOTSWITCHES,				// Array of maximum 5 footswitches
	PROP_FOOTSWITCH,				// footswitch contains firmware and 2 pedals
	PROP_FOOTSWITCH_LEFT_PEDAL,		// left pedal of the footswitch
	PROP_FOOTSWITCH_RIGHT_PEDAL,	// right pedal of the footswitch
	PROP_FOOTSWITCH_PEDAL_DEVICE,	// controlled device by one pedal
	PROP_FOOTSWITCH_PEDAL_FUNCTION,	// called function of one pedal
	PROP_FOOTSWITCH_PEDAL_MAX_VELOCITY,		// Max Velocity when full press.
	PROP_FOOTSWITCH_PEDAL_OLD_FEATURE,
	PROP_FKEY_LEDS,
	PROP_FKEY_LED,
	PROP_FKEY_LOCATION,
	PROP_FKEY_LED_NAME,
	PROP_FKEY_LED_FUNCTION,
	PROP_FKEY_LED_LOCATION,
	PROP_FKEY_LED_INFOS,
	PROP_FKEYS_TEST_MODE, // int enable/disable fkey test

	//FunctionWheel
	PROP_FWHEELS = 0x1420,
	PROP_FWHEEL,
	PROP_FWHEEL_CONTROLLED_DEVICE,
	PROP_FWHEEL_FUNCTION,
	PROP_FWHEEL_FINE_RESOLUTION,
	PROP_FWHEEL_COARSE_RESOLUTION,
	PROP_FWHEEL_SELECTED_RESOLUTION,
	PROP_FWHEEL_DIRECTION,
	PROP_FWHEEL_UPPER_LIMIT,
	PROP_FWHEEL_LOWER_LIMIT,
	PROP_FWHEEL_RESOLUTION,
	PROP_FWHEEL_MAX_VELOCITY = PROP_FWHEEL_RESOLUTION,	// for JoyStick

	//Memory Function
	PROP_MEM= 0x1440,
	PROP_MEM_MEMORY,    // struct
	PROP_MEM_OBJECTIVE_NO,    // objective index (INT)
	PROP_MEM_METHOD,          // method no (INT) see MicroscopeContrastingMethods
	PROP_MEM_CUBE_NO,         // il turret cube index (INT)
	PROP_MEM_XML_DESCRIPTION,	// Display the Memory Description in XML.

	// Lamp Switch Properties
	PROP_TL_IL_LAMP_SWITCH = 0x1460,
	PROP_TL_IL_LAMP_SWITCH_BEHAVIOUR,     // behaviour of lamp switch - when external lamp (IL) TL can stay powered on
	PROP_ZOOM_INTENSITY_CONTROL_MODE,     // tlbase MDG4x: control the intensity depending on the zoom position
	PROP_ZOOM_APERTURE_CONTROL_MODE,      // tlbase MDG4x: control the aperture depending on the zoom position
	PROP_TL_CONTRAST_MODE,                // tlbase MDG4x: contrast modes BF=1, RC=2, DF=3
	PROP_CONSTANT_IMAGE_BRIGHTNESS_STATES, // To prevent heating up of LED at optimal exposure timee

	// Ports
	PROP_PORTS=0x1500,
	PROP_ERGOTUBE,			// MZ16FA ergo tube present
	PROP_COAX,				// MZ16FA COAX
	PROP_PORTS_PORT,        // DM6000 Port struct
	PROP_PORTS_PORT_NAME,   // DM6000 Ports
	PROP_PORTS_STATES,      // DM6000 Port States
	PROP_PORTS_STATE,       // DM6000 Port State
	PROP_PORTS_STATE_INFO,  // DM6000 Port state info
	PROP_PORTS_PORTS,       // PORT ARRAY!
	PROP_PORTS_NUM_PORTS,   // config the number of ports for manual ports
	PROP_PORTS_NUM_STATES,  // config the number of port states for manual ports
	PROP_PORTS_PORT_CAMERA_INFO, // attached camera info
	PROP_YTUBE,             // SMS automak 2004/10/18
	PROP_ULTRALOWTUBE,      // SMS 2005/01/04
	PROP_VISUAL_TUBE,       // Struct for VisualTube info 2011/01/13
	PROP_PORTS_ACCESSORIES, // Struct for Accessories used in Optics (Coax,...) 2011/01/13
	PROP_PORTS_SETUP_MAGNIFICATIONS, // intrinsic magnfications of tube (like DM8/12000 without cmounts)

	PROP_SIDEPORTS=0x1540,  // DMI Side Port(s)
	PROP_SIDEPORTS_PRISMS,
	PROP_SIDEPORTS_PRISM,
	PROP_SIDEPORTS_PRISM_NAME,
	PROP_SIDEPORTS_NUM_PRISMS,
	PROP_BOTTOMPORT=0x1560, // DMI Bottom Port

	// ZDRIVE
	PROP_ZDRIVE= 0x1600,    // properties struct for ZDrive
	PROP_ZDRIVE_THRESHOLD_LIMIT_MODE, // determine if the "threshold" limits the moves by hardware
	PROP_ZDRIVE_INITIALIZATION_MODE, // determine the init procedure of the zdrive after power on
	PROP_ZDRIVE_WORLD_MAX,           // world max string
	PROP_ZDRIVE_INITIALIZATION_DISTANCE, // (floating point) initialization distance in millimeters after power on - see also PROP_ZDRIVE_INITIALIZATION_MODE
	PROP_ZDRIVE_INITIALIZATION_POSITION, // int value in steps - position for initialization according init mode and init distance  (readonly) 

	PROP_ZDRIVE_CLOSED_LOOP = 0x1620,
	PROP_ZDRIVE_CLOSED_LOOP_MODE,			// int closed loop operation mode
	PROP_ZDRIVE_CLOSED_LOOP_PARAMETERS,		// struct - group closed loop parameters
	PROP_ZDRIVE_CLOSED_LOOP_SINGLE_POSITIONING_ERROR_RANGE,		// int range in nano meters
	PROP_ZDRIVE_CLOSED_LOOP_NUM_CORRECTING_REPOSITIONS,			// int count
	PROP_ZDRIVE_CLOSED_LOOP_WAITTIME_SINGLE_CORRECTION,			// int wait time in milliseconds
	PROP_ZDRIVE_CLOSED_LOOP_CYCLIC_POSITIONING_ERROR_RANGE,		// int range in nano meters

	// STAGE
	PROP_STAGE = 0x1640,     // properties struct for Stage
	PROP_STAGE_ORIENTATION,  // orientation of stage: 
                             // bird's view: (0)-->(1)           (0)--->   <---(1)
                             //               A     |             |             |
                             //               |     V             V             V
                             //              (3)<--(2)
                             //                                   A             A
                             //                                   |             |
                             //                                  (3)--->   <---(2)
	PROP_STAGE_START_POSITION,	// stage position after initialisation (calibration)
	PROP_STAGE_ACCELERATION,	// acceleration of the stage motor
	// Universal stage parameters
	PROP_UNIVERSAL_STAGE_NAME,				// name of the stage
	PROP_UNIVERSAL_STAGE_ORIENTATION,		// orientation (0 ... 3)
	PROP_UNIVERSAL_STAGE_PITCH_X,			// pitch X, float in millimeters
	PROP_UNIVERSAL_STAGE_PITCH_Y,			// pitch Y, float in millimeters
	PROP_UNIVERSAL_STAGE_FULL_STEPS_COUNT,	// full steps count, integer
	PROP_UNIVERSAL_STAGE_TRAVEL_RANGE_X,	// travel range in X, float in millimeters
	PROP_UNIVERSAL_STAGE_TRAVEL_RANGE_Y,	// travel range in Y, float in millimeters
	PROP_UNIVERSAL_STAGE_MAX_SPEED_X,		// max speed in X, float in millimeters
	PROP_UNIVERSAL_STAGE_MAX_SPEED_Y,		// max speed in Y, float in millimeters
	PROP_UNIVERSAL_STAGE_ACCELERATION,		// stage acceleration, float in millimeters
	PROP_UNIVERSAL_STAGE_DECELERATION,		// stage deceleration, float in millimeters
	PROP_UNIVERSAL_STAGE_LIMIT_SWITCHES_PER_AXIS, // number of limit switches per axis, integer
	PROP_UNIVERSAL_STAGE_MOTOR_CURRENT,		// motor current (mAh), integer
	PROP_UNIVERSAL_STAGE_GAIN,				// gain, integer
	PROP_UNIVERSAL_STAGE_HANDWHEELSPEED,	// multiple values, string (e.g. 100 400 700 4000)
	PROP_UNIVERSAL_STAGE_INIT_SPEED_X,		// init speed in X, float in millimeters
	PROP_UNIVERSAL_STAGE_INIT_SPEED_Y,		// init speed in Y, float in millimeters

	// LASER
	PROP_LASER = 0x1660,
	PROP_LASER_WAVELENGTH,
	PROP_LASER_INTENSITY,
	PROP_LASER_INTENSITIES,
	PROP_LASERBOX_SETUP,
	PROP_LASER_POWERED,

	// TIRF
	PROP_TIRF = 0x1680,      					// properties struct for Tirf module
	PROP_TIRF_SCANNER_CHANNEL_CENTER_POS,		// start position of tirf scanner channel
	PROP_TIRF_IMM_COVERSLIP_REFRACTION_INDEX,	// refraction index of coverslip
	PROP_TIRF_CULTURE_MEDIUM_REFRACTION_INDEX,	// refraction index of culture medium
	PROP_TIRF_PENETRATION_DEPTHS,				// array of possible tirf penetration depths
	PROP_TIRF_COLLIMATOR_SYNCHRONIZED_MODE,		// collimator mode (boolean 0: collimator adjustable 1: synchronized to z drive
	PROP_TIRF_LASER_WAVELENGTH,					// laser wavelength value (used for calculation of tirf penetration depth)
	PROP_TIRF_INCIDENT_ANGLE,					// laser incident angle
	PROP_TIRF_LASER_CENTER,						// scanner/collimator position where the laser enters the objective pupil center
	PROP_TIRF_SMARTMOVE_MODE,					// 0: default behavior (e.g. xyz-control) 1: tirf behavior (scanner/collimator control)
	PROP_TIRF_OPERATION_MODE,					// currently unused 
	PROP_TIRF_ALIGN_MODE,						// 1: align mode activated 0: align mode deactivated
	PROP_TIRF_FINETUNE_MODE,					// 1: fluo cube fine tuning mode activated 0: fine tuning mode deactivated
	PROP_TIRF_ALIGN_LASER_INTENSITY,			// laser intensity value used at tirf auto-alignment
	PROP_TIRF_SENSOR_INTENSITY,                 // tirf sensor intensity 
	PROP_TIRF_USED_LASER_WAVELENGTHES,			// string ';' separated list to modify PROP_TIRF_PENETRATION_DEPTHS
	PROP_TIRF_ALIGN_LASER_WAVELENGTH,			// laser wavelength to be used at tirf auto-alignment
	PROP_TIRF_AFC_LASER_CENTER,                 // laser center afc mirror for tirf cube finetuning

	//SDCONFOCAL
	PROP_SDCONFOCAL = 0x1700,
	PROP_SDCONFOCAL_WHEEL_ITEMS,
	PROP_SDCONFOCAL_WHEEL_ITEM,
	PROP_SDCONFOCAL_WHEEL_ITEM_NAME,
	PROP_SDCONFOCAL_NUM_WHEEL_ITEMS,
	PROP_SDCONFOCAL_WHEEL_EXCITATION_INDEX,
	PROP_SDCONFOCAL_WHEEL_EMISSION_INDEX,
	PROP_SDCONFOCAL_WHEEL_DICHROIC_INDEX,

	//SEQUENCER
	PROP_SEQUENCER = 0x1720,
	PROP_SEQUENCER_EXT_TRIGGER_OUTPUT_MODE,
	PROP_SEQUENCER_EXT_TRIGGER_OUTPUT_LINE,
	PROP_SEQUENCER_EXT_TRIGGER_INPUT_MODE,
	PROP_SEQUENCER_EXT_TRIGGER_INPUT_LINE,
	PROP_SEQUENCER_NIDAQ_START_TRIGGER,
	PROP_SEQUENCER_NIDAQ_CLOCK_DIVIDER,
	PROP_SEQUENCER_EXT_TRIGGER_OUTPUT_MODES, // optional modes per line
	PROP_SEQUENCER_SYSTEM_TRIGGERS,		 // Listnode for all system triggers
	PROP_SEQUENCER_SYSTEM_TRIGGER_ID,		 // Unique numerical identifier of this physical connector
	PROP_SEQUENCER_SYSTEM_TRIGGER_NAME,		 // Unique name of this physical connector
	PROP_SEQUENCER_SYSTEM_TRIGGER_FUNCTION,	 // Logical function allocated to this physical connector
	PROP_SEQUENCER_BNC_TRIGGERS,
	PROP_SEQUENCER_BNC_TRIGGER_ID,			 // Unique numerical identifier of this physical connector
	PROP_SEQUENCER_BNC_TRIGGER_NAME,		 // Unique name of this physical connector
	PROP_SEQUENCER_BNC_TRIGGER_FUNCTION,	 // Logical function allocated to this physical connector
	PROP_SEQUENCER_EXPOSURETIME_FACTOR,     // double factor in milliseconds i.e. 1.0 or 0.1
	
	// Camera interface unit (for Touch Control Unit)
	PROP_CAMERAIF = 0x1740,
	PROP_CAMERAIF_RESOLUTION,
	PROP_CAMERAIF_EXPOSURETIME,

	__PROP_RESERVED0 = 0x1760,
	__PROP_RESERVED0_MAX = __PROP_RESERVED0 +15,


	PROP_WATERPUMP = 0x1780,
	PROP_WATERPUMP_FREQUENCY,
	PROP_WATERPUMP_AMPLITUDE,

	// properties for climatecontrol units
	PROP_CLIMATE_CONTROL = 0x1790,
	PROP_CLIMATE_CONTROL_NAME,				// string, name of climate control (readonly)
	PROP_CLIMATE_CONTROL_ENABLED,			// int, 0 disabled and 1 enabled
	PROP_CLIMATE_CONTROL_SENSOR_VALUE,		// int, sensor value in "°C * 10" or "% * 10" (readonly)
	PROP_CLIMATE_CONTROL_DIMENSION_UNIT,	// string "°C" or "%" (readonly)
	PROP_CLIMATE_CONTROL_ENABLE_POSSIBLE,	// int, 1 enable and disable is possible, 0 enable and disable is NOT possible

	// optics data properties for stereo microscope
	PROP_OPTDATA_FOCAL_LENGTH = 0x1800,
	PROP_OPTDATA_FRONT_FOCAL_LENGTH,
	PROP_OPTDATA_BACK_FOCAL_LENGTH,
	PROP_OPTDATA_DIAMETER_EXIT_PUPIL,
	PROP_OPTDATA_DIAMETER_ENTRANCE_PUPIL_EASTERN,
	PROP_OPTDATA_DIAMETER_ENTRANCE_PUPIL_WESTERN,
	PROP_OPTDATA_HEIGHT_EXIT_PUPIL,
	PROP_OPTDATA_HEIGHT_ENTRANCE_PUPIL,
	PROP_OPTDATA_WORKING_DISTANCE,
	PROP_OPTDATA_FIELD_NUMBER,
	PROP_OPTDATA_FIELD_OF_VIEW,
	PROP_OPTDATA_DEPTH_OF_FIELD,
	PROP_OPTDATA_NUMERICAL_APERTURE,
	PROP_OPTDATA_RESOLUTION,
	PROP_OPTDATA_LATERAL_EASTERN_X,
	PROP_OPTDATA_LATERAL_WESTERN_X,
	PROP_OPTDATA_LATERAL_EASTERN_Y,
	PROP_OPTDATA_LATERAL_WESTERN_Y,
	PROP_OPTDATA_GAMMA,
	PROP_OPTDATA_ACC_SHIFT_X,
	PROP_OPTDATA_ACC_SHIFT_Y,
	PROP_OPTDATA_ACC_SHIFT_Z,
	// Sirius Adapter
	PROP_RL_ADAPTER,
	PROP_CX_ADAPTER,
	// ISO Ratch mode selection between Zoom, Visual or Video
	PROP_ISO_RATCH_MODE,

	// properties for SPIM Method
	PROP_SPIM_FILTER_TURRET = 0x01840,
	PROP_SPIM_FILTER,
	PROP_SPIM_FILTER_ID,
	PROP_SPIM_FILTER_NAME,
	PROP_SPIM_FILTER_TRANSMISSION_BANDS,
	PROP_SPIM_FILTER_SUPPRESSION_BANDS,
	PROP_SPIM_OBJECTIVE_TURRET,
	PROP_SPIM_OBJECTIVE_ARTICLE_NO,
	PROP_SPIM_MIRROR_DEVICE_ARTICLE_NO,
	PROP_SPIM_MIRROR_DEVICE_NAME,
	PROP_SPIM_MIRROR_DEVICE_MIRRORS,
	PROP_SPIM_MIRROR_DISTANCE,
	PROP_SPIM_MIRROR_HEIGHT,
	PROP_SPIM_MIRROR_ANGLE,
	PROP_SPIM_MIRROR_DEVICE_MIRROR,
	PROP_SPIM_MIRROR_DEVICE_FOCAL_PLANE_DISTANCE,


	// properties for Simultaneous Acquisition systems
	PROP_SIM_ACQ_SYSTEM = 0x1900,
	PROP_SIM_ACQ_SYSTEM_NAME,					// string, name of Simultaneous Acquisition system	
	PROP_SIM_ACQ_SYSTEM_SPLITTER_EXCHANGEABLE,	// bool, whether splitting element (filter slide/cube) is exchangeable (by user)
	PROP_SIM_ACQ_SYSTEM_SPLITTER_ARTICLE_NO,	// string, article number of splitting element (cube)
	PROP_SIM_ACQ_SYSTEM_BYPASS_AVAILABLE,		// bool, true if bypass mode available, false otherwise 
	PROP_SIM_ACQ_SYSTEM_SPLIT_ACTIVE,			// bool, true if wavelength ranges being split, false otherwise	
	PROP_SIM_ACQ_SYSTEM_HANDLING_KIND,			// string, "UNKNOWN"/"MANUAL"/"CODED"/"MOTORISED"
	PROP_SIM_ACQ_SYSTEM_IN_PORT,				// string, input port (= microscope output doc-port)
	PROP_SIM_ACQ_SYSTEM_SPLITTER_NAME,			// string name of splitting element
	PROP_SIM_ACQ_SYSTEM_SPLITTER_EMITTER_WAVELENGTH_BANDS,     //  string multiple wavelength bands in nano meters for emitter

	__PROP_RESERVED1 = 0x1f00, // realtime timestamps
	__PROP_RESERVED1_MAX = __PROP_RESERVED1 +15,

	__PROP_RESERVED2 = 0x1f20,
	__PROP_RESERVED2_MAX = __PROP_RESERVED2 +31,

	// last possible property id is 0x1fff here
} EProperties;

#endif // PUBLIC_AHM_MICROSCOPE_PROPID_H
