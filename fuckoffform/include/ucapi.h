//////////////////////////////////////////////////////////////////////////////////////////
// 
// Leica Unified Camera API.
//
// (C) Leica Microsystems Copyright 2012-2016
//
// All rights are reserved. Reproduction or transmission in whole or 
// in part, in any form or by any means, electronic, mechanical or 
// otherwise, is prohibited without the prior written permission of
// the copyright owner.
// 
//////////////////////////////////////////////////////////////////////////////////////////


#ifndef AHM_UCAPI_H
#define AHM_UCAPI_H

#ifndef UCAPI_INCLUDED_AHM
#include <ahwbasic.h> // include base defs
#include <ahwpropid.h>
#include <ahwprop2.h>
#define UCAPI_INCLUDED_AHM
#endif

// UCAPI version number.
#ifndef UCAPI_VERSION_MAJOR
#define UCAPI_VERSION_MAJOR	1
#endif

#ifndef UCAPI_VERSION_MINOR
#define UCAPI_VERSION_MINOR	1
#endif

#define UCAPI_VERSION	UCAPI_VERSION_MAJOR.UCAPI_VERSION_MINOR

#if UCAPI_VERSION_MAJOR >= 1
#if UCAPI_VERSION_MINOR >= 1
// Identifies features added in UCAPI version 1.1.
#define UCAPI_1_1
#endif
#endif

// Emit compiler warnings for references to deprecated types and names.
//#define ENABLE_DEPRECATED_WARNINGS

namespace ucapi
{
	//////////////////////////////////////////////////////////////////////////////////////
	// PropertySetting interface
	//
	//	Represents a property value and the ID of the property to which the value applies.
	//
	//////////////////////////////////////////////////////////////////////////////////////	
	class PropertySetting
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// id
		//
		//	Get the ID of the property with which the setting is associated.
		//
		// Return:	The ID of the associated property.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual iop::int32 id() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// value
		//
		//	Get the property value object that holds the setting value.
		//
		// Return:	A pointer to the PropertyValue object that can be used to access 
		//			and/or change the setting value.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual ahm::PropertyValue* value() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// dispose
		//
		//	Dispose (delete) the setting object.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual void dispose() = 0;
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// PropertySettingList interface
	//
	//	Provides a read-only container that can store a collection of property settings. 
	//	Each setting consists of the ID of a property plus a value for the property. The 
	//	container can contain zero or one settings for a given property ID; it cannot 
	//	contain multiple settings for the same property.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class PropertySettingList
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// numSettings
		//
		//	Get the number of property settings stored in the container.
		//
		// Return:	The number of settings stored in the container.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual iop::int32 numSettings() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// getId
		//
		//	Get the ID of the property setting at the specified index in the container.
		//
		// index:	The index of the setting to access.
		//
		// Return:	The ID of the property setting at the specified index.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual iop::int32 getId(iop::int32 index) = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// findSetting
		//
		//	Retrieve the value object for the specified property.
		//
		// propertyId:	The ID of the property setting to access.
		//
		// Return:	A pointer to the PropertValue object for the specified property, or 
		//			NULL if the there is no setting for the specified property in the 
		//			container.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual ahm::PropertyValue* findSetting(iop::int32 propertyId) = 0;

	};

	//////////////////////////////////////////////////////////////////////////////////////
	// PropertyBag interface
	//
	//	Extends the PropertySettingList container interface to allow settings to be added
	//	to and removed from the container.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class PropertyBag : public PropertySettingList
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// insertSetting
		//
		//	Insert a property setting into the container. If a setting for the same 
		//	property already exists in the container it is overwritten with the new value.
		//
		// pSetting:	The property setting to insert.
		//
		// Remarks:		The PropertySetting object that is inserted into the container 
		//				belongs to the container. The container will manage its lifetime, 
		//				unless it is removed from the container by calling remove; 
		//				PropertySetting::dispose should not be called on a PropertySetting 
		//				instance after inserting it into the property bag.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual void insertSetting(PropertySetting* pSetting) = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// removeSetting
		//
		//	Remove a property setting from the container.
		//
		// propertyId:	The ID of the property setting to remove.
		//
		// Return:	A pointer to the PropertSetting that was removed, or NULL if the 
		//			there is no setting for	the specified property in the container.
		//
		// Remarks:	The caller is responsible for disposing the PropertySetting instance 
		//			returned from this method.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual PropertySetting* removeSetting(iop::int32 propertyId) = 0;
	};


	//////////////////////////////////////////////////////////////////////////////////////
	// PropertyBagResult interface
	//
	//	Provides an interface to a disposable property bag object.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class PropertyBagResult
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// propertyBag
		//
		//	Get the actual property bag
		//
		// Return:	A pointer to PropertyBag object
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual PropertyBag* propertyBag() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// dispose
		//
		//	Dispose (delete) the PropertyBagResult object.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual void dispose() = 0;
	};

// Define unit type IDs in the same range as the property IDs.
#define RESERVED_UNIT_TYPE_UCAPI_FIRST ahm::RESERVED_PROPID_UCAPI_FIRST

	//////////////////////////////////////////////////////////////////////////////////////
	// UCAPI_UNIT_TYPE enumeration
	//
	//	UCAPI unit type ID definitions.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	enum UCAPI_UNIT_TYPE
	{
		__UCAPI_UNIT_TYPE_START						= RESERVED_UNIT_TYPE_UCAPI_FIRST,

		//////////////////////////////////////////////////////////////////////////////////
		// UCAPI_DRIVER
		//
		//	Root driver unit.
		//
		//	Where the camera family supports plug and play:
		//		The root driver unit supports the ucapi::DynamicUnits interface and raises
		//		associated events to inform the client when a camera is connected / 
		//		disconnected and to allow the client to initiate an update of the child 
		//		unit tree.
		//
		//////////////////////////////////////////////////////////////////////////////////
		UCAPI_DRIVER								= __UCAPI_UNIT_TYPE_START,

		//////////////////////////////////////////////////////////////////////////////////
		// UCAPI_CAMERA
		//
		//	Unit that provides image acquisition and control of the settings for an 
		//	individual camera. Camera units are "dynamic" units. At startup the 
		//	UCAPI_DRIVER unit creates a UCAPI_CAMERA child unit for each available camera. 
		//	
		//	Where the camera family supports plug and play:
		//	 	If a camera is unplugged the associated UCAPI_CAMERA unit's initialisation 
		//		state is updated and an event is generated. Most of the unit's interfaces 
		//		become inactive (INTERFACE_STATE_TEMPORARY_INVALID); the unit's Properties
		//		interface remains active but most properties will become inactive 
		//		(access rights = UNDEF). The client should not make any further calls 
		//		to the inactive interfaces or properties.
		//
		//////////////////////////////////////////////////////////////////////////////////
		UCAPI_CAMERA,

		//////////////////////////////////////////////////////////////////////////////////
		// UCAPI_CAMERA_SENSOR
		//
		//	If a camera has multiple sensors that have settings that can be controlled 
		//	separately it creates one UCAPI_CAMERA_SENSOR child unit per sensor to provide 
		//	access to the individual sensor settings.
		//
		//////////////////////////////////////////////////////////////////////////////////
		UCAPI_CAMERA_SENSOR,

		__UCAPI_UNIT_TYPE_MAX

#ifdef UCAPI_1_1
		// Reserved range of IDs for use by the UCAPI runtime / infrastructure.
		,__UCAPI_INFRASTRUCTURE_UNIT_TYPE_FIRST		= __UCAPI_UNIT_TYPE_START + 0x00c0,
		__UCAPI_INFRASTRUCTURE_UNIT_TYPE_LAST		= __UCAPI_UNIT_TYPE_START + 0x00cf,


		// Reserved range of IDs for camera module specific unit types.
		// A camera module can provide custom unit types that expose features that are specific to the
		// camera family or a specific camera within the family supported by the camera module. The ID
		// range is shared by all camera modules, so the interpretation of IDs in the custom range is
		// camera module specific and different camera modules could use the same ID to represent different
		// features. The custom IDs for a camera family are defined in a separate header file and the client
		// must know which camera family(s) it is working with in order to use the custom unit types correctly.
		__UCAPI_CUSTOM_UNIT_TYPE_FIRST				= __UCAPI_UNIT_TYPE_START + 0x00f0,
		__UCAPI_CUSTOM_UNIT_TYPE_LAST				= __UCAPI_UNIT_TYPE_START + 0x00ff
#endif
	};

// Define interface IDs in the same range as the property IDs.
#define RESERVED_IID_UCAPI_FIRST ahm::RESERVED_PROPID_UCAPI_FIRST

	//////////////////////////////////////////////////////////////////////////////////////
	// UCAPI_IID enumeration
	//
	//	UCAPI interface ID definitions.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	enum UCAPI_IID
	{
		__UCAPI_IID_START							= RESERVED_IID_UCAPI_FIRST,

		// ImageAcquisition interface.
		// Level:			Required.
		IID_IMAGE_ACQUISITION						= __UCAPI_IID_START,

		// ImageSequenceAcquisition interface.
		// Level:			Optional.
		IID_IMAGE_SEQUENCE_ACQUISITION,

		// AcquisitionInformation interface.
		// Level:			Required.
		IID_ACQUISITION_INFORMATION,

		// ImageFormatInformation interface.
		// Level:			Required if PROP_CAPTURE_FORMAT_ID and/or PROP_STREAMING_FORMAT_ID are
		//					supported, otherwise prohibited.
		IID_IMAGE_FORMAT_INFORMATION,

		// OneShotWhiteBalance interface.
		// Level:			Optional.
		// Remarks:			See also PROP_CONTINUOUS_WHITE_BALANCE_ENABLED.
		IID_ONE_SHOT_WHITE_BALANCE,

		// WhiteShadingReferenceFileCreation interface.
		// Level:			Optional.
		// Remarks:			See also PROP_WHITE_SHADING_REFERENCE_FILE.
		IID_WHITE_SHADING_REFERENCE_CREATOR,

		// OneShotBlackBalance interface.
		// Level:			Optional.
		// Remarks:			See also PROP_BLACK_BALANCE_LEVEL.
		IID_ONE_SHOT_BLACK_BALANCE,

		// PropertyDependencyInformation interface.
		// Level:			Optional.
		// Remarks:			
		IID_PROPERTY_DEPENDENCY_INFORMATION,

		__UCAPI_IID_MAX,

#ifdef UCAPI_1_1
		// Reserved range of IDs for use by the UCAPI runtime / infrastructure.
		__UCAPI_INFRASTRUCTURE_IID_FIRST			= __UCAPI_IID_START + 0x00c0,
		__UCAPI_INFRASTRUCTURE_IID_LAST				= __UCAPI_IID_START + 0x00cf,
#endif

		// Reserved range of IDs for camera module specific interfaces.
		// A camera module can provide custom interfaces that expose features that are specific to the
		// camera family or a specific camera within the family supported by the camera module. The ID
		// range is shared by all camera modules, so the interpretation of IDs in the custom range is
		// camera module specific and different camera modules could use the same ID to represent different
		// features. The custom IDs for a camera family are defined in a separate header file and the client
		// must know which camera family(s) it is working with in order to use the custom interfaces correctly.
		__UCAPI_CUSTOM_IID_FIRST					= __UCAPI_IID_START + 0x00f0,
		__UCAPI_CUSTOM_IID_LAST						= __UCAPI_IID_START + 0x00ff
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// UCAPI_PROPERTY enumeration
	//
	//	UCAPI property ID definitions.
	//
	// Level Definitions
	//	Required:		The property is implemented on all camera units.
	//	Recommended:	The property is whenever if possible.
	//	Optional:		The property is supported only if the feature is supported by 
	//					the camera.
	//////////////////////////////////////////////////////////////////////////////////////
	enum UCAPI_PROPERTY
	{
		__UCAPI_PROPID_START					= ahm::RESERVED_PROPID_UCAPI_FIRST,

		// The camera serial number 
		// Value type:		TYPE_STRING
		// Info type:		TYPE_BASIC
		// Access rights:	Read only.
		// Units:			None.
		// Level:			Required.
		// Remarks:
		//	The serial number should always be available, even before the camera
		//	is initialised.
		PROP_SERIAL_NUMBER						= __UCAPI_PROPID_START,

		// The camera head firmware version.
		// Value type:		TYPE_STRING
		// Info type:		TYPE_BASIC
		// Access rights:	Read only.
		// Units:			None.
		// Level:			Recommended.
		PROP_FIRMWARE_HEAD_VERSION,

		// Provides version information about the camera software and hardware components.
		// Value type:		TYPE_FIXED_ARRAY [of TYPE_STRING]
		// Info type:		TYPE_BASIC
		// Access rights:	Read only.
		// Units:			None.
		// Level:			Recommended.
		// Remarks:
		//	Each element in the array provides version information for a single software 
		//	or hardware	component.
		PROP_VERSION_INFO,

		// The sensor pixel count in the X/Y-direction.
		// Value type:		TYPE_INT
		// Info type:		TYPE_BASIC
		// Access rights:	Read only.
		// Units:			Physical pixels.
		// Level:			Required.
		PROP_SENSOR_XRESOLUTION,
		PROP_SENSOR_YRESOLUTION,

		// The sensor pixel size the X/Y-direction.
		// Value type:		TYPE_FLOAT
		// Info type:		TYPE_BASIC
		// Access rights:	Read only.
		// Units:			Metres.
		// Level:			Required.
		PROP_PHYSICAL_PIXEL_XSIZE,
		PROP_PHYSICAL_PIXEL_YSIZE,

		// The effective pixel count in the X/Y-direction, accounting for the current camera
		// binning or sub-sampling level.
		// Value type:		TYPE_INT
		// Info type:		TYPE_BASIC
		// Access rights:	Read only.
		// Units:			Logical pixels.
		// Level:			Required.
		PROP_LOGICAL_XRESOLUTION,
		PROP_LOGICAL_YRESOLUTION,

		// The offset of the centre of the current image format in the X/Y-direction.
		// The value specifies the centre offset of the current logical image format, taking 
		// account of the current camera binning or sub-sampling levels, but not including 
		// any readout region(s).
		// For cameras that support pre-defined image formats (via the PROP_CAPTURE_FORMAT_ID 
		// and/or PROP_STREAMING_FORMAT_ID properties), the offset also includes any pre-defined 
		// offsets applied in the camera for the active image format. In this case, the property
		// value is also included in the format settings associated with the ImageFormatDefinition
		// for each pre-defined image format.
		// Value type:		TYPE_FLOAT
		// Info type:		TYPE_BASIC
		// Access rights:	Read only.
		// Units:			Physical pixels.
		// Level:			Optional.
		PROP_LOGICAL_CENTRE_XOFFSET,
		PROP_LOGICAL_CENTRE_YOFFSET,

		// The effective pixel size the X/Y-direction, accounting for the current camera
		// binning or sub-sampling level.
		// Value type:		TYPE_FLOAT
		// Info type:		TYPE_BASIC
		// Access rights:	Read only.
		// Units:			Metres.
		// Level:			Required.
		PROP_LOGICAL_PIXEL_XSIZE,
		PROP_LOGICAL_PIXEL_YSIZE,

		// The camera trigger mode to use to initiate acquisition of an image.
		// Value type:		TYPE_INDEX
		// Info type:		TYPE_ENUM
		// Access rights:	Read / write.
		// Units:			None.
		// Level:			Optional.
		// Remarks: 
		//	See the IMAGE_TRIGGER_MODE enumeration.
		PROP_IMAGE_TRIGGER_MODE,

		// The polarity of the hardware signal that triggers acquisition in hardware trigger mode.
		// Value type:		TYPE_INDEX
		// Info type:		TYPE_ENUM
		// Access rights:	Read / write.
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	See the TRIGGER_POLARITY enumeration.
		PROP_TRIGGER_POLARITY,

		// The camera exposure time
		// Value type:		TYPE_FLOAT / TYPE_INDEX
		// Info type:		TYPE_STEPPED_RANGE / TYPE_ENUM
		// Access rights:	Read / write
		// Units:			Seconds.
		// Level:			Required.
		// Remarks:
		//	See also PROP_AUTO_BRIGHTNESS_ENABLED.
		PROP_EXPOSURE_TIME,

		// The camera electron-multiplying gain
		// Value type:		TYPE_INT / TYPE_INDEX
		// Info type:		TYPE_STEPPED_RANGE / TYPE_ENUM
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		PROP_EMGAIN,

		// The camera amplification
		// Value type:		TYPE_FLOAT / TYPE_STRING / TYPE_INDEX
		// Info type:		TYPE_STEPPED_RANGE / TYPE_ENUM
		// Access rights:	Read / write
		// Units: None.
		// Level: Optional.
		PROP_GAIN,

		// The camera red-channel amplification
		// Value type:		TYPE_FLOAT / TYPE_INDEX
		// Info type:		TYPE_STEPPED_RANGE / TYPE_ENUM
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Required for colour cameras.
		PROP_GAIN_RED,

		// The camera green-channel amplification
		// Value type:		TYPE_FLOAT / TYPE_INDEX
		// Info type:		TYPE_STEPPED_RANGE / TYPE_ENUM
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Required for colour cameras.
		PROP_GAIN_GREEN,

		// The camera blue-channel amplification
		// Value type:		TYPE_FLOAT / TYPE_INDEX
		// Info type:		TYPE_STEPPED_RANGE / TYPE_ENUM
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Required for colour cameras.
		PROP_GAIN_BLUE,

		// Enable / disable auto-brightness.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	When this property is true, the controlled parameters 
		//	(PROP_EXPOSURE_TIME and PROP_GAIN if supported) are read-only.
		PROP_AUTO_BRIGHTNESS_ENABLED,

		// The auto-brightness level to apply when auto-brightness is enabled.
		// Value type:		TYPE_FLOAT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		PROP_AUTO_BRIGHTNESS_LEVEL,

		// The ROI to use for auto-brightness adjustments.
		// Value type:		TYPE_INT_RECT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			Logical pixels (clipped to readout region).
		// Level:			Optional.
		PROP_AUTO_BRIGHTNESS_ROI,

		// Enable / disable use of the auto-brightness ROI.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		PROP_AUTO_BRIGHTNESS_ROI_ENABLED,

		// The camera colour saturation level.
		// Value type:		TYPE_INT / TYPE_INDEX
		// Info type:		TYPE_STEPPED_RANGE / TYPE_ENUM
		// Access rights:	Read / write
		// Units:			Percent.
		// Level:			Optional.
		PROP_COLOUR_SATURATION,

		// The camera binning level.
		// Value type:		TYPE_INDEX (See the BINNING_LEVEL enumeration).
		// Info type:		TYPE_ENUM / TYPE_BASIC (read-only).
		// Access rights:	Read / write.
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	The property value (or option value when implemented as an enumerated property) 
		//	defines the binning levels in the X and Y directions, based on the BINNING_LEVEL 
		//	enumeration.
		//	If the camera supports direct selection between multiple binning levels this property is
		//	implemented as an enumerated property (Info type == TYPE_ENUM).
		//	If the binning level is controlled as part of a set of pre-defined image formats 
		//	(via the PROP_CAPTURE_FORMAT_ID / PROP_STREAMING_FORMAT_ID properties) this property 
		//	is implemented as a basic read-only property (Info type == TYPE_BASIC).
		//	If the camera does not support multiple binning levels this property is not
		//	required.
		PROP_BINNING_LEVEL,

		// Enable / disable brightness correction when a binning level greater than
		// unity is active.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		PROP_BINNED_BRIGHTNESS_CORRECTION_ENABLED,

		// The camera readout speed.
		// Value type:		TYPE_INT / TYPE_INDEX
		// Info type:		TYPE_STEPPED_RANGE / TYPE_ENUM / TYPE_BASIC (read-only)
		// Access rights:	Read / write
		// Units:			Hz.
		// Level:			Optional.
		// Remarks:
		//	If the camera supports direct selection between multiple readout speeds this property is
		//	implemented as a range or enumerated property.
		//	If the readout speed is controlled as part of a set of pre-defined image formats 
		//	(via the PROP_CAPTURE_FORMAT_ID / PROP_STREAMING_FORMAT_ID properties) this property 
		//	is implemented as a basic read-only property (Info type == TYPE_BASIC).
		//	If the camera does not support multiple readout speeds this property is not
		//	required.
		PROP_READOUT_SPEED,

		// The pixel resolution in bits per channel.
		// Value type:		TYPE_INT / TYPE_INDEX
		// Info type:		TYPE_ENUM / TYPE_BASIC (read-only)
		// Units:			Bits.
		// Access rights:	Read / write.
		// Units:			bits per channel.
		// Level:			Required.
		// Remarks:
		//	If only single pixel resolution is supported, this property is implemented as
		//	a basic (Info type == TYPE_BASIC) read-only property.
		PROP_PIXEL_DEPTH,

		// The camera pixel type (RGB, BGR, Mono etc.)
		// Value type:		TYPE_INDEX (See the PIXEL_TYPE enum).
		// Info type:		TYPE_ENUM / TYPE_BASIC (read-only)
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Required.
		// Remarks: 
		//	Provides a mechanism to select the pixel type independent from the
		//	bit-depth of the delivered images.
		//	If only single pixel type is supported, this property is implemented as
		//	a basic (Info type == TYPE_BASIC) read-only property.
		PROP_PIXEL_TYPE,

		// Defines a sub-region of the image sensor to use.
		// Value type:		TYPE_INT_RECT
		// Info type:		TYPE_STEPPED_RANGE.
		// Access rights:	Read / write
		// Units:			Logical pixels.
		// Level:			Optional.
		PROP_READOUT_REGION,

		// Defines multiple sub-regions of the image sensor to use.
		// Value type:		TYPE_DYNAMIC_ARRAY [of TYPE_INT_RECT]
		// Info type:		TYPE_STEPPED_RANGE / TYPE_ENUM
		// Access rights:	Read / write
		// Units:			Logical pixels.
		// Level:			Optional.
		PROP_READOUT_REGIONS,

		// The gamma level setting to apply to the image.
		// Value type:		TYPE_FLOAT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Recommended.
		PROP_GAMMA_LEVEL,

		// The black level setting to apply to the image.
		// Value type:		TYPE_INT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Recommended.
		// Remarks:
		//	All image pixel values which are below the black level are set to zero and levels
		//	between the black level and the white level are rescaled to the full range.
		//	See also PROP_BLACK_LOCK_THRESHOLD.
		PROP_BLACK_LEVEL,

		// The white level setting to apply to the image.
		// Value type:		TYPE_INT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Recommended.
		// Remarks:
		//	All image pixel values which are above the white level are set to the maximum
		//	pixel value and levels between the black level and the white level are rescaled to 
		//	the full range.
		//	See also PROP_WHITE_LOCK_THRESHOLD.
		PROP_WHITE_LEVEL,

		// Enable / disable automatic gamma calculation.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	When this property is true PROP_GAMMA_LEVEL is read-only.
		PROP_AUTO_GAMMA_LEVEL_ENABLED,

		// Enable / disable automatic black level calculation.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	When this property is true PROP_BLACK_LEVEL is read-only.
		PROP_AUTO_BLACK_LEVEL_ENABLED,

		// Enable / disable automatic white level calculation.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	When this property is true PROP_WHITE_LEVEL is read-only.
		PROP_AUTO_WHITE_LEVEL_ENABLED,

		// The sharpening level to apply to the image.
		// Value type:		TYPE_INT / TYPE_INDEX
		// Info type:		TYPE_STEPPED_RANGE / TYPE_ENUM
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		// Remarks:	
		//	A value of zero represents sharpening disabled. If the property
		//	is implemented as a range type, the range minimum must be zero.
		//	If the property is implemented as an enumerated type, the value
		//	at index zero must be zero.
		PROP_SHARPENING_LEVEL,

		// Enable / disable mirroring along the x-axis, i.e. Reflection in a horizontal line
		// through the centre of the image. De facto this is vertical flipping (2015-02-06).
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		// X-Mirroring 
		// false    =>   true
		// +-----+      +-----+
		// |M....|  =>  |.....|
		// |.....|  =>  |W....|
		// +-----+      +-----+
		PROP_XMIRRORING_ENABLED,

		// Enable / disable mirroring along the y-axis, i.e. Reflection in a vertical line
		// through the centre of the image. De facto this is horizontal flipping (2015-02-06).
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		// Y-Mirroring
		// false    =>   true
		// +-----+      +-----+
		// |A....|  =>  |....A|
		// |.....|  =>  |.....|
		// +-----+      +-----+
		PROP_YMIRRORING_ENABLED,
#ifdef UCAPI_1_1
#ifdef ENABLE_DEPRECATED_WARNINGS
		// The functionality provided by PROP_IMAGE_AVERAGING_MODE is replaced by
		// PROP_ENHANCED_ACQUISITION_MODE and the 
		// ENHANCED_ACQUISITION_MODE::ENHANCED_ACQUISITION_SIMPLE_AVERAGE and
		// ENHANCED_ACQUISITION_MODE::ENHANCED_ACQUISITION_RUNNING_AVERAGE options.
#pragma deprecated(PROP_IMAGE_AVERAGING_MODE)
#pragma warning (disable: 4995)
#endif
#endif
		// [deprecated: Use PROP_ENHANCED_ACQUISITION_MODE instead]
		// The type of image averaging to use when acquiring an image.
		// Value type:		TYPE_INDEX
		// Info type:		TYPE_ENUM
		// Access rights:	Read / (write)
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	See the IMAGE_AVERAGING_MODE enum.
		PROP_IMAGE_AVERAGING_MODE,
#ifdef UCAPI_1_1
#ifdef ENABLE_DEPRECATED_WARNINGS
#pragma warning (default: 4995)
#endif
#endif

		// The number of images to average when acquiring an image.
		// Value type:		TYPE_INT / TYPE_INDEX
		// Info type:		TYPE_STEPPED_RANGE / TYPE_ENUM
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		PROP_IMAGE_AVERAGING_COUNT,

		// Provides selection of a capture format from a list of
		// pre-defined formats identified by IDs.
		// Value type:		TYPE_INDEX
		// Info type:		TYPE_ENUM
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		// Remarks: 
		//	If this property is implemented, the ImageFormatInformation interface
		//	should also be implemented to provide information about the 
		//	image format associated with each format ID.
		//	See also the PROP_CAPTURE_FORMAT_ID and PROP_ACQUISITION_MODE properties.
		//	See the PROP_ACQUISITION_MODE property information for further details.
		PROP_CAPTURE_FORMAT_ID,

		// Provides selection of a streaming format from a list of
		// pre-defined formats identified by IDs.
		// Value type:		TYPE_INDEX
		// Info type:		TYPE_ENUM
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	See also the PROP_CAPTURE_FORMAT_ID and PROP_ACQUISITION_MODE properties.
		//	See the PROP_ACQUISITION_MODE property information for further details.
		PROP_STREAMING_FORMAT_ID,

		// Provides a means to select the active acquisition mode, for
		// cameras that support distinct capture and streaming modes.
		// Value type:		TYPE_INDEX
		// Info type:		TYPE_ENUM (See the ACQUISITION_MODE enum).
		// Access rights:	Read / write.
		// Units:			None.
		// Level:			Optional.
		// Remarks: 
		//	Cameras that support distinct capture and streaming modes (with different
		//	pre-defined image formats available in each mode) should implement the
		//	PROP_ACQUISITION_MODE property and the PROP_CAPTURE_FORMAT_ID and 
		//	PROP_STREAMING_FORMAT_ID properties. In this case, the active capture format
		//	and the active streaming format can be selected independently and the format
		//	delivered by the camera module is determined by the PROP_ACQUISITION_MODE setting.
		//
		//	Cameras that support distinct capture and streaming modes but do not support
		//	pre-defined image formats should implement the PROP_ACQUISITION_MODE property 
		//	only.
		//
		//	Cameras that support a single acquisition mode with pre-defined image formats
		//	should implement only the PROP_CAPTURE_FORMAT_ID property.
		PROP_ACQUISITION_MODE,

		// The fan speed level.
		// Value type:		TYPE_INT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		PROP_FAN_SPEED_LEVEL,

		// Enable / disable continuous auto white balance mode.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC.
		// Access rights:	Read / write.
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	For non colour modes, the property should be read-only and false.
		//	When continuous auto white balance is enabled the PROP_GAIN_RED, PROP_GAIN_GREEN, 
		//	PROP_GAIN_BLUE property values are updated after each white balance calculation to reflect 
		//	the new channel gains.
		//	While continuous auto white balance is enabled, the channel gain properties PROP_GAIN_RED, 
		//	PROP_GAIN_GREEN, PROP_GAIN_BLUE are read-only.
		//	See also PROP_CONTINUOUS_WHITE_BALANCE_ROI and PROP_CONTINUOUS_WHITE_BALANCE_ROI_ENABLED.
		PROP_CONTINUOUS_WHITE_BALANCE_ENABLED,

		// The ROI to use for continuous auto white balance calculation.
		// Value type:		TYPE_INT_RECT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			Logical pixels (clipped to readout region).
		// Level:			Optional.
		// Remarks:
		//	See also PROP_CONTINUOUS_WHITE_BALANCE_ENABLED.
		//	If this property is implemented the PROP_CONINUOUS_WHITE_BALANCE_ROI_ENABLED
		//	property must also be implemented.
		PROP_CONTINUOUS_WHITE_BALANCE_ROI,

		// Enable / disable use of the continuous auto white balance ROI.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	See also PROP_CONTINUOUS_WHITE_BALANCE_ENABLED and PROP_CONTINUOUS_WHITE_BALANCE_ROI.
		PROP_CONTINUOUS_WHITE_BALANCE_ROI_ENABLED,

		// The ROI to use for focus score calculation.
		// Value type:		TYPE_INT_RECT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			Logical pixels (clipped to readout region).
		// Level:			Optional.
		// Remarks:
		//	If this property is implemented the PROP_FOCUS_SCORE_ROI_ENABLED
		//	property must also be implemented.
		//	See also IPROP_FOCUS_SCORE.
		PROP_FOCUS_SCORE_ROI,

		// Enable / disable use of the focus score ROI.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	This property controls whether the ROI is used when calculating the focus score; it 
		//	does not enable / disable focus score calculation. The focus score is calculated 
		//	and delivered in the image metadata if the IPROP_FOCUS_SCORE image metedata value is
		//	requested during acquisition (and the camera or extension module supports the focus score 
		//	calculation feature).
		//	See also PROP_FOCUS_SCORE_ROI, IPROP_FOCUS_SCORE.
		PROP_FOCUS_SCORE_ROI_ENABLED,

		// The white shading reference file to use when shading correction is enabled.
		// Value type:		TYPE_STRING.
		// Info type:		TYPE_BASIC.
		// Access rights:	Read / write.
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	See also PROP_WHITE_SHADING_CORRECTION_ENABLED.
		//	The value of the property is the full path to the shading reference file to use.
		//	To change the shading reference file to use, Set a new path on the property value.
		//	To clear the current shading reference file, set the value to an empty string.
		//
		// ERROR_CODE_PARAMETER_INVALID:
		//	The value specified is not a valid file path.
		//
		// ERROR_CODE_FILE_NOT_FOUND:
		//	The specified file does not exist.
		//
		// ERROR_CODE_FILE_READ:
		//	An error occurred when trying to load the shading reference data from the file.
		PROP_WHITE_SHADING_REFERENCE_FILE,

		// Enable / disable shading correction using the current shading reference.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	See also PROP_WHITE_SHADING_REFERENCE_FILE.
		//	Set to read-only and false if there is no shading reference file currently configured 
		//	via	the PROP_WHITE_SHADING_REFERENCE_FILE property.
		PROP_WHITE_SHADING_CORRECTION_ENABLED,

		// The saturation correction to apply to the image data.
		// Value type:		TYPE_INT
		// Info type:		TYPE_STEPPED_RANGE (0 - 100)
		// Access rights:	Read / write
		// Units:			Percent.
		// Level:			Optional.
		// Remarks:
		//	If this property is implemented the PROP_HUE_CORRECTION property must
		//	also be implemented.
		//	A value of zero causes the hue correction to have no effect on the image colour. 
		//	As the value increases to 100 the effect of the hue correction on the image colour
		//	increases.
		PROP_SATURATION_CORRECTION,

		// The hue correction to apply to the image data.
		// Value type:		TYPE_INT
		// Info type:		TYPE_STEPPED_RANGE (0 - 359)
		// Access rights:	Read / write
		// Units:			Degrees.
		// Level:			Optional.
		// Remarks:
		//	If this property is implemented the PROP_SATURATION_CORRECTION property must
		//	also be implemented.
		PROP_HUE_CORRECTION,

		// The ROI to use when calculating the average image colour.
		// Value type:		TYPE_INT_RECT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			Logical pixels (clipped to readout region).
		// Level:			Optional.
		// Remarks:
		//	If this property is implemented the PROP_AVERAGE_COLOUR_ROI_ENABLED
		//	property must also be implemented.
		//	See also IPROP_AVERAGE_COLOUR_RED / GREEN / BLUE.
		PROP_AVERAGE_COLOUR_ROI,

		// Enable / disable use of the average colour ROI.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	This property controls whether the ROI is used when calculating the average colour;	it 
		//	does not enable / disable average colour calculation. The average colour is calculated 
		//	and delivered in the image metadata if any of the IPROP_AVERAGE_COLOUR_RED / GREEN / BLUE
		//	image metadata values are requested during acquisition (and the camera or extension 
		//	module supports the average colour calculation feature).
		//	See also PROP_AVERAGE_COLOUR_ROI, IPROP_AVERAGE_COLOUR_RED / GREEN / BLUE.
		PROP_AVERAGE_COLOUR_ROI_ENABLED,

		// The wavelength to use to generate a pseudo colour image when PROP_PIXEL_TYPE
		// is set to one of the PIXEL_TYPE_PSEUDO_XXX formats.
		// Value type:		TYPE_INT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			Nanometers.
		// Level:			Required if any of the PIXEL_TYPE_PSEUDO_XXX pixel types
		//					is supported, otherwise prohibited.
		// Remarks:
		//	See also PROP_PIXEL_TYPE.
		PROP_PSEUDO_COLOUR_WAVELENGTH,

		// The black balance level to use.
		// Value type:		TYPE_INT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	See also PROP_BLACK_BALANCE_ENABLED and OneShotBlackBalance.
		PROP_BLACK_BALANCE_LEVEL,

		// Enable / disable use of the black balance level.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	See also PROP_BLACK_BALANCE_LEVEL and OneShotBlackBalance.
		PROP_BLACK_BALANCE_ENABLED,

		// Get / set the time to wait for an image to be delivered, in
		// seconds.
		// Value type:		TYPE_FLOAT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			Seconds.
		// Level:			Optional.
		// Remarks:
		//	See also PROP_AUTO_ACQUISITION_TIMEOUT_ENABLED.
		//	The default value provides the recommended minimum timeout
		//	based on the current camera settings.
		PROP_ACQUISITION_TIMEOUT,

		// Enable / disable auto acquisition timeout calculation.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Required if PROP_ACQUISITION_TIMEOUT is supported,
		//					else prohibited.
		// Remarks:
		//	See also PROP_ACQUISITION_TIMEOUT.
		//	When set to true, the PROP_ACQUISITION_TIMEOUT property is 
		//	read-only and its value is calculated based on the current
		//	camera settings.
		//	When set to false, the client can control the timeout by setting
		//	the PROP_ACQUISITION_TIMEOUT property.
		PROP_AUTO_ACQUISITION_TIMEOUT_ENABLED,

		// Current temperature of the camera
		// Value type:		TYPE_FLOAT
		// Info type:		TYPE_BASIC
		// Access rights:	Read only.
		// Units:			Kelvin.
		// Level:			Optional.
		PROP_TEMPERATURE,

		// Get / set the target temperature for camera cooling.
		// Value type:		TYPE_FLOAT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			Kelvin.
		// Level:			Optional.
		PROP_TARGET_TEMPERATURE,

		// Get / set the fan speed.
		// Value type:		TYPE_INT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		PROP_FAN_SPEED,

		// Minimum interval between two triggers in seconds.
		// Value type:		TYPE_FLOAT
		// Info type:		TYPE_BASIC
		// Access rights:	Read
		// Units:			Seconds.
		// Level:			Optional.
		//Remarks: 
		//	Depends on the current camera settings.
		PROP_MIN_TRIGGER_INTERVAL,

		// Readout time of the image.
		// Value type:		TYPE_FLOAT
		// Info type:		TYPE_BASIC
		// Access rights:	Read
		// Units:			Seconds.
		// Level:			Optional.
		//Remarks: 
		//	Depends on the current camera settings.
		PROP_IMAGE_READOUT_TIME,

		// Enable / disable NIR (Near InfraRed) mode.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional
		//Remarks:
		//	When NIR mode is enabled the camera sensitivity to wavelengths 
		//	in the infrared region is increased.
		PROP_NIR_MODE_ENABLED,

		// Get the camera SDK version.
		// Value type:		TYPE_STRING
		// Info type:		TYPE_BASIC
		// Access rights:	Read only
		// Units:			None.
		// Level:			Required
		PROP_CAMERA_SDK_VERSION,

		// Enable / disable overlapped readout.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional
		PROP_READOUT_OVERLAP_ENABLED,

		// Get / set the active EMCCD mode.
		// Value type:		TYPE_INDEX
		// Info type:		TYPE_ENUM
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional
		// Remarks:
		//	See the EMCCD_MODE enumeration.
		PROP_EMCCD_MODE,

		// Get / set the minimum exposure time at which hotspot correction is applied.
		// Value type:		TYPE_FLOAT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			Seconds.
		// Level:			Optional
		PROP_HOTPIXEL_EXPOSURE_THRESHOLD,

		// Get / set the minimum intensity threshold for a pixel to be classified as a
		// "hot" pixel.
		// Value type:		TYPE_INT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional
		PROP_HOTPIXEL_INTENSITY_THRESHOLD,

		// Set the micro-scanning mode to use. (SRING)
		// Value type:		TYPE_INDEX
		// Info type:		TYPE_ENUM
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional
		//Remarks:
		//	For cameras which can shift the sensor to achieve a higher resolution.
		PROP_MICROSCANNING_MODE,

		// Get / set time to shift the electrons to the sensor readout area. (FLOAT)
		// Value type:		TYPE_INDEX
		// Info type:		TYPE_ENUM
		// Access rights:	Read / write
		// Units:			Seconds.
		// Level:			Optional
		PROP_VERTICAL_SHIFT_TIME,

		// Get / set the voltage offset to use when shifting electrons to the sensor. (FLOAT)
		// readout area.
		// Value type:		TYPE_INDEX
		// Info type:		TYPE_ENUM
		// Access rights:	Read / write
		// Units:			Volts.
		// Level:			Optional
		PROP_VERTICAL_SHIFT_VOLTAGE_OFFSET,

		// Get / set a pre-defined colour matrix that controls colour interpretation based on 
		// an illumination temperature. (INT)
		// Value type:		TYPE_INDEX
		// Info type:		TYPE_ENUM
		// Access rights:	Read / write
		// Units:			Kelvin.
		// Level:			Optional
		PROP_COLOUR_TEMPERATURE,

		// Get / set the noise reduction level. (STRING)
		// Value type:		TYPE_INDEX
		// Info type:		TYPE_ENUM
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional
		// Remarks:
		//	See also PROP_NOISE_REDUCTION_ENABLED
		PROP_NOISE_REDUCTION_LEVEL,

		// Enable / disable the camera's noise reduction feature.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional
		// Remarks:
		//	See also PROP_NOISE_REDUCTION_LEVEL
		PROP_NOISE_REDUCTION_ENABLED,

		// Get / set the micro-scanning sharpening level to use. (STRING)
		// Value type:		TYPE_INDEX
		// Info type:		TYPE_ENUM
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional
		// Remarks:
		//	See also PROP_MICRO_SCANNING_SHARPENING_ENABLED and PROP_MICRO_SCANNING_MODE.
		PROP_MICRO_SCANNING_SHARPENING_LEVEL,

		// Enable / disable the camera's micro-scanning sharpening feature.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional
		// Remarks:
		//	See also PROP_MICRO_SCANNING_SHARPENING_LEVEL.
		PROP_MICRO_SCANNING_SHARPENING_ENABLED,

		// Get / set the black-lock threshold.
		// Value type:		TYPE_INT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional
		// Remarks:
		//	All image pixel values which are under the threshold are set to the threshold value.
		//	See also PROP_BLACK_LOCK_ENABLED an PROP_BLACK_LEVEL.
		PROP_BLACK_LOCK_THRESHOLD,

		// Enable / disable the camera's black-lock feature.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional
		// Remarks:
		//	See also PROP_BLACK_LOCK_THRESHOLD.
		PROP_BLACK_LOCK_ENABLED,

		// Get / set the white-lock threshold.
		// Value type:		TYPE_INT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional
		// Remarks:
		//	All image pixel values which are above the threshold are set to the threshold value.
		//	See also PROP_WHITE_LOCK_ENABLED an PROP_WHITE_LEVEL.
		PROP_WHITE_LOCK_THRESHOLD,
		
		// Enable / disable the camera's white-lock feature.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional
		// Remarks:
		//	See also PROP_WHITE_LOCK_THRESHOLD.
		PROP_WHITE_LOCK_ENABLED,

		// Get / set the scaling to use in electron-count mode.
		// Value type:		TYPE_INT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional
		// Remarks:
		//	When PROP_PIXEL_TYPE is set to PIXEL_TYPE_MONO_ELECTRONCOUNT the pixel output value will 
		//	be divided by the scaling factor.
		//	See also PIXEL_TYPE_MONO_ELECTRONCOUNT.
		PROP_ELECTRONCOUNT_SCALING,
		
		// Get / set the EMCCD noise reduction threshold.
		// Value type:		TYPE_INT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional
		// Remarks:
		//	Image pixels generated from the EMCCD with values above the threshold (CIC noise) are corrected.
		//	See also PROP_EMCCD_NOISE_REDUCTION_ENABLED.
		PROP_EMCCD_NOISE_REDUCTION_THRESHOLD,

		// Enable / disable the camera's EMCCD noise reduction feature.
		// Value type:		TYPE_BOOL
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional
		// 
		// Remarks:
		//	See also PROP_EMCCD_NOISE_REDUCTION_THRESHOLD.
		PROP_EMCCD_NOISE_REDUCTION_ENABLED,
		
#ifdef UCAPI_1_1
		// Get / set the enhanced acquisition mode to use when acquiring images.
		// Value type:		TYPE_INDEX
		// Info type:		TYPE_ENUM
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional
		// 
		// Remarks:
		//	The composition mode value is one of the values defined in the
		//	ENHANCED_ACQUISITION_MODE enum.
		PROP_ENHANCED_ACQUISITION_MODE,

		// Get / set the HDR acquisition mode.
		// Value type:		TYPE_INDEX
		// Info type:		TYPE_ENUM
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional (Required if ENHANCED_ACQUISITION_HDR is
		//					supported
		// 
		// Remarks:
		//	The mode value is one of the values defined in the
		//	HDR_MODE enum.
		//	HDR mode is enabled by setting PROP_ENHANCED_ACQUISITION_MODE to
		//	ENHANCED_ACQUISITION_HDR.
		PROP_HDR_MODE,

		// Get / set the contrast level to use for HDR acquisition.
		// Value type:		TYPE_INDEX
		// Info type:		TYPE_ENUM
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional (Required if ENHANCED_ACQUISITION_HDR is
		//					supported
		// 
		// Remarks:
		//	The contrast value is one of the values defined in the
		//	HDR_CONTRAST enum.
		//	HDR mode is enabled by setting PROP_ENHANCED_ACQUISITION_MODE to
		//	ENHANCED_ACQUISITION_HDR.
		PROP_HDR_CONTRAST,

		// Get / set whether Peltier for cooling is enabled
		// Value type:	TYPE_BOOL
		// Info type:	TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional 
		//
		//Remarks:
		//
		PROP_TEMPERATURE_PELTIER_ENABLED,

		// Get / set whether multi tap readout is enabled.
		// Value type:	TYPE_BOOL
		// Info type:	TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional 
		//
		// Remarks:
		// If this property is implemented the sensor supports multiple readout taps
		PROP_MULTI_TAP_READOUT_ENABLED,

		// Select taps through the image is read out.
		// Value type:		TYPE_INDEX
		// Info type:		TYPE_ENUM
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional (Required if PROP_MULTI_TAP_READOUT_ENABLED is
		//					supported
		// 
		// Remarks:
		//	The read out tap orientation is defined in the MULTI_TAP_READOUT_SELECTOR enum
		//	based on the sensor orientation defined in ImageFormat.orientation()
		PROP_MULTI_TAP_READOUT_SELECTOR,

		// Get / set the brightness level to use for HDR acquisition.
		// Value type:		TYPE_FLOAT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional (Required if ENHANCED_ACQUISITION_HDR is
		//					supported
		PROP_HDR_BRIGHTNESS,

		// The camera display name
		// Value type:		TYPE_STRING
		// Info type:		TYPE_BASIC
		// Access rights:	Read only.
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	The display name is optional, camera name will be used as display name when it is not implemented.
		PROP_DISPLAY_NAME,

		// Get the pixel alignment for the for the current PROP_PIXEL_DEPTH and PROP_PIXEL_TYPE
		// Value type:		TYPE_INDEX
		// Info type:		TYPE_ENUM
		// Access rights:	Read only.
		// Units:			None.
		// Level:			Optional. (Required if PROP_PIXEL_DEPTH has values which are not 8 bit aligned)
		// Remarks:
		//	The alignment values are defined in the PIXEL_ALIGNMENT enum.
		//	The property informs about the pixel bit alignment in the memory.
		PROP_PIXEL_ALIGNMENT,

		// Get the decimation mode, if the camera supports it
		// Value type:		TYPE_INT
		// Info type:		TYPE_STEPPED_RANGE
		// Access rights:	Read / write.
		// Units:			None.
		// Level:			Optional
		// Remarks:
		// Currently only used by DMC4500
		PROP_DECIMATION_MODE,
		
		// The path to directory containing sample images for UCAPI Demo Camera.
		// Value type:		TYPE_STRING.
		// Info type:		TYPE_BASIC.
		// Access rights:	Read / write.
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	Currently used only by UCAPI Demo Camera. 
		//	The value of the property is the full path to the sample images directory.
		//	In order to use other images, set the property value to the desired path.
		//	To use default images (colour blocks), set the value to empty string ("").
		PROP_PATH_TO_SAMPLE_IMAGES,

		// Get if the camera delivers images with formats different from the set format
		// Value type:	TYPE_BOOL
		// Info type:	TYPE_BASIC
		// Access rights:	Read only
		// Units:			None.
		// Level:			Optional 
		// 
		// Remarks:
		//	Currently only used by Wifi/Network cameras to allow viewing video on mulitple
		// clients
		PROP_ACCEPT_UNEXPECTED_FORMAT,

		// Get scan count for image format
		// Value type:	TYPE_INT
		// Info type:	TYPE_BASIC
		// Access rights:	Read only
		// Units:			None.
		// Level:			Optional 
		// 
		// Remarks:
		//	Currently only used for JenOptik camera with pixel shift.
		// normal image has scan count = 1
		// images with pixel shift enabled have scan count > 1
		PROP_SCAN_COUNT,

		// Get custom format resolution for width and height
		// Value type:		TYPE_INDEX
		// Info type:		TYPE_ENUM
		// Access rights:	Read write
		// Units:			None.
		// Level:			Optional 
		// 
		// Remarks:
		//	Currently only used for DMC5400 (Baumer)
		// the custom format is created using ROI (partial scan)
		PROP_CUSTOM_FORMAT_XRESOLUTION,
		PROP_CUSTOM_FORMAT_YRESOLUTION,

		// The camera expected connection interface (USB2, USB3, etc.)
		// Value type:		TYPE_STRING
		// Info type:		TYPE_BASIC
		// Access rights:	Read only.
		// Units:			None.
		// Level:			Optional.
		PROP_EXPECTED_CONNECTION_INTERFACE,

		// The camera detected connection interface (USB2, USB3, etc.)
		// Value type:		TYPE_STRING
		// Info type:		TYPE_BASIC
		// Access rights:	Read only.
		// Units:			None.
		// Level:			Optional.
		PROP_DETECTED_CONNECTION_INTERFACE,

		// Default min AE exposure time, used when auto-brightness is enabled.
		// Value type:		TYPE_FLOAT
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			Seconds.
		// Level:			Optional.
		// Remarks:
		//	Not available for user, only for software engineer via camera profiles.
		PROP_AUTO_EXPOSURE_MIN,

		// Default max AE exposure time, used when auto-brightness is enabled.
		// Value type:		TYPE_FLOAT
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			Seconds.
		// Level:			Optional.
		// Remarks:
		//	Not available for user, only for software engineer via camera profiles.
		PROP_AUTO_EXPOSURE_MAX,

		// Default max AE gain, used when auto-brightness is enabled.
		// Value type:		TYPE_FLOAT
		// Info type:		TYPE_BASIC
		// Access rights:	Read / write
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	Not available for user, only for software engineer via camera profiles.
		PROP_AUTO_GAIN_MAX,

#endif
		__UCAPI_PROPID_MAX,

		// Reserved range of IDs for image properties. See UCAPI_IMAGE_PROPERTY enum.
		__UCAPI_IMAGE_PROPID_FIRST		= __UCAPI_PROPID_START + 0x0400,
		__UCAPI_IMAGE_PROPID_LAST		= __UCAPI_PROPID_START + 0x04ff,

		// Reserved range of IDs for use by the UCAPI runtime / infrastructure.
		__UCAPI_INFRASTRUCTURE_PROPID_FIRST		= __UCAPI_PROPID_START + 0x0500,
		__UCAPI_INFRASTRUCTURE_PROPID_LAST		= __UCAPI_PROPID_START + 0x05ff,

		// Reserved range of IDs for camera module specific properties.
		// A camera module can provide custom properties that expose features that are specific to the
		// camera family or a specific camera within the family supported by the camera module. The ID
		// range is shared by all camera modules, so the interpretation of IDs in the custom range is
		// camera module specific and different camera modules could use the same ID to represent different
		// features. The custom IDs for a camera family are defined in a separate header file and the client
		// must know which camera family(s) it is working with in order to use the custom
		// properties correctly.
		__UCAPI_CUSTOM_PROPID_FIRST		= __UCAPI_PROPID_START + 0x0e00,
		__UCAPI_CUSTOM_PROPID_LAST		= __UCAPI_PROPID_START + 0x0eff,
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// UCAPI_IMAGE_PROPERTY enumeration
	//
	//	Image metadata ID Definitions.
	//	Property values which may be included in the Image::imageInfo property bag to 
	//	provide additional information about the image and the context in which it was 
	//	captured.
	//	These property values are not exposed via the Properties interface.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	enum UCAPI_IMAGE_PROPERTY
	{
		__UCAPI_IMAGE_PROPID_START				= __UCAPI_IMAGE_PROPID_FIRST,

		// The index of an image within a capture sequence.
		// Value type:		TYPE_INT
		// Units:			None.
		// Level:			Required.
		//
		// Remarks: 
		//	For single image acquisition (ImageAcquisition::acquire) the sequence index is
		//	always zero.
		//	For continuous image acquisition (ImageAcquisition::acquireContinuous) the first 
		//	image delivered to the acquisition context after the call to acquireContinuous has
		//	index zero. The index then increments for subsequent images.
		//	For sequence acquisition (ImageSequenceAcquisition::acquireSequence) the first 
		//	image in the sequence has index zero and the index then increments for subsequent 
		//	images.
		//	Where multiple images are acquired per capture (e.g. where multiple ROIs are in 
		//	use or the camera has multiple sensors), all the images acquired in a single 
		//	capture operation have the same sequence index.
		IPROP_IMAGE_SEQUENCE_INDEX					= __UCAPI_IMAGE_PROPID_START,

		// The intensity histogram of the image taken before applying any processing that 
		// can compress the dynamic range of the image data (e.g. applying gamma).
		// Value type:		TYPE_FIXED_ARRAY [of TYPE_INT].
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	The histogram contains 2^n bins where n is the bit depth of the image (see the
		//	PROP_PIXEL_DEPTH property).
		IPROP_RAW_IMAGE_HISTOGRAM_INTENSITY,

		// The red channel histogram of the image taken before applying any processing 
		// that can compress the dynamic range of the image data (e.g. applying gamma).
		// Value type:		TYPE_FIXED_ARRAY [of TYPE_INT].
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	The histogram contains 2^n bins where n is the bit depth of the image (see the
		//	PROP_PIXEL_DEPTH property).
		IPROP_RAW_IMAGE_HISTOGRAM_RED,

		// The green channel histogram of the image taken before applying any processing 
		// that can compress the dynamic range of the image data (e.g. applying gamma).
		// Value type:		TYPE_FIXED_ARRAY [of TYPE_INT].
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	The histogram contains 2^n bins where n is the bit depth of the image (see the
		//	PROP_PIXEL_DEPTH property).
		IPROP_RAW_IMAGE_HISTOGRAM_GREEN,

		// The blue channel histogram of the image taken before applying any processing 
		// that can compress the dynamic range of the image data (e.g. applying gamma).
		// Value type:		TYPE_FIXED_ARRAY [of TYPE_INT].
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	The histogram contains 2^n bins where n is the bit depth of the image (see the
		//	PROP_PIXEL_DEPTH property).
		IPROP_RAW_IMAGE_HISTOGRAM_BLUE,

		// The focus score for the image or a region of the image.
		// Value type:		TYPE_FLOAT
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	See also PROP_FOCUS_SCORE_ROI, PROP_FOCUS_SCORE_ROI_ENABLED.
		IPROP_FOCUS_SCORE,

		// The red channel value of the average colour of the image or a 
		// region of the image.
		// Value type:		TYPE_INT
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	See also PROP_AVERAGE_COLOUR_ROI, PROP_AVERAGE_COLOUR_ROI_ENABLED.
		IPROP_AVERAGE_COLOUR_RED,

		// The green channel value of the average colour of the image or a 
		// region of the image.
		// Value type:		TYPE_INT
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	See also PROP_AVERAGE_COLOUR_ROI, PROP_AVERAGE_COLOUR_ROI_ENABLED.
		IPROP_AVERAGE_COLOUR_GREEN,

		// The blue channel value of the average colour of the image or a 
		// region of the image.
		// Value type:		TYPE_INT
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	See also PROP_AVERAGE_COLOUR_ROI, PROP_AVERAGE_COLOUR_ROI_ENABLED.
		IPROP_AVERAGE_COLOUR_BLUE,

		// The RGB colour palette for an indexed image.
		// Value type:		TYPE_FIXED_ARRAY [of TYPE_INT].
		// Units:			None.
		// Level:			Optional.
		// Remarks:
		//	The palette contains 2^n entries where n is the number of bits in each index (e.g. for
		//	an 8-bit indexed image the palette contains 2^8 == 256 entries).
		//	Each entry in the palette is a Rgb24Quad that contains the red, green and blue channel 
		//	values.
		IPROP_COLOUR_PALETTE_RGB24,

		// The validation status of the image.
		// Value type:		TYPE_INT
		// Access rights:	Read.
		// Units:			None.
		// Level:			Optional.
		// Remarks: 
		//   0 valid, others invalid		
		//   For more information see IMAGE_VALIDATION_STATE enum
		IPROP_IMAGE_VALIDATION_STATE,

		// CompositionResultType Indicates that this image is a result of a ImageCompositionContext and what kind of Composition Operation was used.
		// Value type:		TYPE_INT
		// Access rights:	Read.
		// Units:			None.
		// Level:			Optional.
		// Remarks: Indicates this image is a resul of a ImageCompositionContext. -1 = UNKNOWN, 0 = NONE / Invalid, ... all others see ENHANCED_ACQUISITION_MODE
		//   0 invalid, others valid		
		IPROP_IMAGE_COMPOSITION_RESULT_TYPE,

		__UCAPI_IMAGE_PROPID_MAX
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// UCAPI_ERROR_CODE enumeration
	//
	//	UCAPI specific error code definitions.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	enum UCAPI_ERROR_CODE
	{
		__UCAPI_ERROR_CODE_START					= ahm::ERROR_CODE_UCAPI_START,

		// Image contains too many under-exposed pixels to complete the requested operation.
		ERROR_CODE_IMAGE_TOO_DARK					= __UCAPI_ERROR_CODE_START,

		// Image contains too many over-exposed pixels to complete the requested operation.
		ERROR_CODE_IMAGE_TOO_BRIGHT,

		// Image contains too many under and/or over-exposed pixels to complete the requested 
		// operation.
		ERROR_CODE_IMAGE_INCORRECT_BRIGHTNESS,

		// Image contains too many under-exposed pixels in red channel to complete the requested operation.
		ERROR_CODE_IMAGE_RED_CHANNEL_TOO_DARK,

		// Image contains too many under-exposed pixels in green channel to complete the requested operation.
		ERROR_CODE_IMAGE_GREEN_CHANNEL_TOO_DARK,

		// Image contains too many under-exposed pixels in blue channel to complete the requested operation.
		ERROR_CODE_IMAGE_BLUE_CHANNEL_TOO_DARK,

		// Image contains too many over-exposed pixels in red channel to complete the requested operation.
		ERROR_CODE_IMAGE_RED_CHANNEL_TOO_BRIGHT,

		// Image contains too many over-exposed pixels in green channel to complete the requested operation.
		ERROR_CODE_IMAGE_GREEN_CHANNEL_TOO_BRIGHT,

		// Image contains too many over-exposed pixels in blue channel to complete the requested operation.
		ERROR_CODE_IMAGE_BLUE_CHANNEL_TOO_BRIGHT,

		// Image format is not supported (not necessarily global, can be limited to current context or algorithm). 
		ERROR_CODE_PIXEL_FORMAT_UNSUPPORTED,

		__UCAPI_ERROR_CODE_MAX
	};


	//////////////////////////////////////////////////////////////////////////////////////
	// ACQUISITION_MODE enumeration
	//
	//	Acquisition mode for cameras that support distinct capture and streaming modes.
	//	See PROP_ACQUISITION_MODE.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	enum ACQUISITION_MODE
	{
		// Select the acquisition mode that is optimised for high quality image capture.
		ACQUISITION_MODE_CAPTURE,

		// Select the acquisition mode that is optimised for fast image streaming.
		ACQUISITION_MODE_STREAMING,

		// 
		ACQUISITION_MODE_SEQUENCE_CAPTURE,
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// IMAGE_TRIGGER_MODE enumeration
	//
	//	Camera trigger mode options when acquiring single images.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	enum IMAGE_TRIGGER_MODE
	{
		//////////////////////////////////////////////////////////////////////////////////
		// IMAGE_TRIGGER_MODE_CONTINUOUS
		//
		//	Camera runs in continuous mode - trigger is generated internally in the 
		//	camera. Acquisition of a new image is initiated as soon as the previous 
		//	acquisition is complete. Depending on the camera capabilities and active 
		//	settings (image format, exposure time etc.) image capture may be overlapped 
		//	with image readout.
		//
		//////////////////////////////////////////////////////////////////////////////////
		IMAGE_TRIGGER_MODE_CONTINUOUS		= 0x01,

		//////////////////////////////////////////////////////////////////////////////////
		// IMAGE_TRIGGER_MODE_SOFTWARE
		//
		//	Acquisition of a new image or sequence of images is initiated when a signal 
		//	is sent to the camera from the driver (in software).
		//
		//////////////////////////////////////////////////////////////////////////////////
		IMAGE_TRIGGER_MODE_SOFTWARE			= 0x02,

		//////////////////////////////////////////////////////////////////////////////////
		// IMAGE_TRIGGER_MODE_HARDWARE
		//
		//	Acquisition of a new image or sequence of images is initiated when a hardware 
		//	signal is received by the camera.
		//
		//////////////////////////////////////////////////////////////////////////////////
		IMAGE_TRIGGER_MODE_HARDWARE			= 0x04
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// TRIGGER_POLARITY enumeration
	//
	//	Camera trigger polarity options.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	enum TRIGGER_POLARITY
	{
		//////////////////////////////////////////////////////////////////////////////////
		// TRIGGER_POLARITY_FALLING_EDGE
		//
		//	Acquisition is triggered when the hardware trigger input transitions from 
		//	high to low.
		//
		//////////////////////////////////////////////////////////////////////////////////
		TRIGGER_POLARITY_FALLING_EDGE,

		//////////////////////////////////////////////////////////////////////////////////
		// TRIGGER_POLARITY_RISING_EDGE
		//
		//	Acquisition is triggered when the hardware trigger input transitions from 
		//	low to high.
		//
		//////////////////////////////////////////////////////////////////////////////////
		TRIGGER_POLARITY_RISING_EDGE,

		//////////////////////////////////////////////////////////////////////////////////
		// TRIGGER_POLARITY_LOW_LEVEL
		//
		//	Acquisition is continuously triggered while the hardware trigger input is at 
		//	a low level.
		//
		//////////////////////////////////////////////////////////////////////////////////
		TRIGGER_POLARITY_LOW_LEVEL,

		//////////////////////////////////////////////////////////////////////////////////
		// TRIGGER_POLARITY_HIGH_LEVEL
		//
		//	Acquisition is continuously triggered while the hardware trigger input is at 
		//	a high level.
		//
		//////////////////////////////////////////////////////////////////////////////////
		TRIGGER_POLARITY_HIGH_LEVEL
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// BINNING_LEVEL enumeration
	//
	//	Camera binning level definitions.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	enum BINNING_LEVEL
	{
		//////////////////////////////////////////////////////////////////////////////////
		// BINNING_LEVEL_X_MASK
		//
		//	Mask to extract the bits that contain the number of pixels that are combined 
		//	in the X direction.
		//
		// Example:
		//	iop::int32 xBinning = (BINNING_LEVEL_4x4 & BINNING_LEVEL_X_MASK) >> 16;
		//	// Or just
		//	iop::int32 xBinning = BINNING_LEVEL_4x4 >> 16;
		//
		//////////////////////////////////////////////////////////////////////////////////
		BINNING_LEVEL_X_MASK	= 0xffff0000,

		//////////////////////////////////////////////////////////////////////////////////
		// BINNING_LEVEL_Y_MASK
		//
		//	Mask to extract the bits that contain the number of pixels that are combined 
		//	in the Y direction.
		//
		// Example:
		//	iop::int32 yBinning = BINNING_LEVEL_4x4 & BINNING_LEVEL_Y_MASK;
		//
		//////////////////////////////////////////////////////////////////////////////////
		BINNING_LEVEL_Y_MASK	= 0x0000ffff,

		//////////////////////////////////////////////////////////////////////////////////
		// BINNING_LEVEL_XxY
		//
		//	Predefined binning levels for common square binning patterns.
		//
		//	BINNING_LEVEL_1x1 => No binning (same as BINNING_LEVEL_NONE).
		//	BINNING_LEVEL_2x2 => Combine 2 pixels in x-direction and 2 pixels in 
		//	y-direction (total 4 pixels).
		//	BINNING_LEVEL_3x3 => Combine 3 pixels in x-direction and 3 pixels in 
		//	y-direction (total 9 pixels) etc.
		//
		//////////////////////////////////////////////////////////////////////////////////
		BINNING_LEVEL_NONE	= 0x00010001,
		BINNING_LEVEL_1x1	= 0x00010001,
		BINNING_LEVEL_2x2	= 0x00020002,
		BINNING_LEVEL_3x3	= 0x00030003,
		BINNING_LEVEL_4x4	= 0x00040004,
		BINNING_LEVEL_5x5	= 0x00050005,
		BINNING_LEVEL_6x6	= 0x00060006,
		BINNING_LEVEL_7x7	= 0x00070007,
		BINNING_LEVEL_8x8	= 0x00080008,
		BINNING_LEVEL_16x16	= 0x00100010,
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// Rgb24Quad
	//
	//	Provides 8-bit red, green and blue colour channel values packed into the lower
	//	24-bits of a 32-bit integer.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	typedef struct Rgb24Quad
	{
		// Blue channel value.
		iop::byte blue;

		// Green channel value.
		iop::byte green;

		// Red channel value.
		iop::byte red;

		// Padding byte.
		iop::byte reserved;
	} Rgb24Quad;

	//////////////////////////////////////////////////////////////////////////////////////
	// PIXEL_TYPE enumeration
	//
	//	Image pixel type definitions.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	enum PIXEL_TYPE
	{
		__PIXEL_TYPE_MIN	= 0x00000000,

		// Pixel type / channel order.
		PIXEL_TYPE_UNKNOWN			= __PIXEL_TYPE_MIN,
		PIXEL_TYPE_INDEXED			= 0x00000001,
		PIXEL_TYPE_MONO				= 0x00000002,
		PIXEL_TYPE_RGB				= 0x00000003,
		PIXEL_TYPE_BGR				= 0x00000004,
		PIXEL_TYPE_BAYER			= 0x00000005,

		// Flags that the pixel type is packed. 
		// Example:
		// PROP_PIXEL_TYPE == PIXEL_TYPE_MONO | PIXEL_TYPE_PACKED_FLAG and
		// PROP_PIXEL_DEPTH == 12, the format of captured images will be PIXEL_FORMAT_CUSTOM_FLAG | 0x00000C00
		// In 3 bytes the information of two pixels will be stored. 
		// Nibble 1-3 : First Pixel
		// Nibble 4-6 = Second pixel
		PIXEL_TYPE_PACKED_FLAG			= 0x20000000,

		// Extended image pixel type definitions.
		//
		//	PROP_PIXEL_TYPE can support these values in addition to the PIXEL_TYPE values
		//	to allow selection of the camera output, but they are not valid as the pixel 
		//	type component of a pixel format.
		//
		//	Example:
		//	With PROP_PIXEL_TYPE == PIXEL_TYPE_MONO_REDGREEN and 
		//	PROP_PIXEL_DEPTH == 8, the format of captured images will be PIXEL_FORMAT_MONO8. 
		//

		// Flag that indicates that a pixel type includes extended information about the pixel
		// content.
		EXTENDED_PIXEL_TYPE_FLAG	= 0x40000000,

		// Mask to extract the base pixel type from extended pixel type definitions.
		BASE_PIXEL_TYPE_MASK	= 0x0000000F,

		// Each pixel has a single channel containing the red colour channel value. 
		PIXEL_TYPE_MONO_RED			= EXTENDED_PIXEL_TYPE_FLAG | PIXEL_TYPE_MONO | 0x00000010,

		// Each pixel has a single channel containing the green colour channel value.
		PIXEL_TYPE_MONO_GREEN		= EXTENDED_PIXEL_TYPE_FLAG | PIXEL_TYPE_MONO | 0x00000020,

		// Each pixel has a single channel containing the blue colour channel value.
		PIXEL_TYPE_MONO_BLUE		= EXTENDED_PIXEL_TYPE_FLAG | PIXEL_TYPE_MONO | 0x00000030,

		// Each pixel has a single channel containing a combination of the red and green colour channel values.
		PIXEL_TYPE_MONO_REDGREEN	= EXTENDED_PIXEL_TYPE_FLAG | PIXEL_TYPE_MONO | 0x00000040,

		// Each pixel has a single channel containing a combination of the red and blue colour channel values.
		PIXEL_TYPE_MONO_REDBLUE		= EXTENDED_PIXEL_TYPE_FLAG | PIXEL_TYPE_MONO | 0x00000050,

		// Each pixel has a single channel containing a combination of the green and blue colour channel values.
		PIXEL_TYPE_MONO_GREENBLUE	= EXTENDED_PIXEL_TYPE_FLAG | PIXEL_TYPE_MONO | 0x00000060,

		// Each pixel has three channels containing a colour value calculated based on the wavelength set via
		// the PROP_PSEUDO_COLOUR_WAVELENGTH property.
		PIXEL_TYPE_PSEUDO_RGB		= EXTENDED_PIXEL_TYPE_FLAG | PIXEL_TYPE_RGB | 0x00000070,
		PIXEL_TYPE_PSEUDO_BGR		= EXTENDED_PIXEL_TYPE_FLAG | PIXEL_TYPE_BGR | 0x00000070,
		PIXEL_TYPE_PSEUDO_INDEXED	= EXTENDED_PIXEL_TYPE_FLAG | PIXEL_TYPE_INDEXED | 0x00000070,

		// Each pixel contains a scaled electron count.
		PIXEL_TYPE_MONO_ELECTRONCOUNT	= EXTENDED_PIXEL_TYPE_FLAG | PIXEL_TYPE_MONO | 0x00000080,
	
		__PIXEL_TYPE_MAX,
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// PIXEL_FORMAT enumeration
	//
	//	Image pixel format definitions.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	enum PIXEL_FORMAT
	{
		// Channel type / order information.
		PIXEL_TYPE_MASK		= 0x0000000F,

		// Bits per pixel information.
		PIXEL_FORMAT_BPP_MASK				= 0x0000FFF0,
		PIXEL_FORMAT_8BPP					= 0x00000080,
		PIXEL_FORMAT_16BPP					= 0x00000100,
		PIXEL_FORMAT_24BPP					= 0x00000180,
		PIXEL_FORMAT_48BPP					= 0x00000300,


		// Flag to indicate that a pixel format is a custom format.
		PIXEL_FORMAT_CUSTOM_FLAG = 0x80000000,

		// Packed pixel formats.
		PIXEL_FORMAT_MONO8		= PIXEL_TYPE_MONO | PIXEL_FORMAT_8BPP,
		PIXEL_FORMAT_MONO16		= PIXEL_TYPE_MONO | PIXEL_FORMAT_16BPP,
		PIXEL_FORMAT_RGB24		= PIXEL_TYPE_RGB | PIXEL_FORMAT_24BPP,
		PIXEL_FORMAT_BGR24		= PIXEL_TYPE_BGR | PIXEL_FORMAT_24BPP,
		PIXEL_FORMAT_RGB48		= PIXEL_TYPE_RGB | PIXEL_FORMAT_48BPP,
		PIXEL_FORMAT_BGR48		= PIXEL_TYPE_BGR | PIXEL_FORMAT_48BPP,

		// Indexed pixel formats.
		// For indexed images the colour palette is provided by an IPROP_COLOUR_PALETTE_RGB24
		// property setting in the image metadata.
		PIXEL_FORMAT_INDEXED8	= PIXEL_TYPE_INDEXED | PIXEL_FORMAT_8BPP
	};


	//////////////////////////////////////////////////////////////////////////////////////
	// PIXEL_ALIGNMENT enumeration
	//
	//	Provides information about the pixel bit alignment within the pixel data buffer.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	enum PIXEL_ALIGNMENT
	{
		//Pixel bits and memory fits together
		PIXEL_ALIGNMENT_NONE	= 0,

		// The bits are aligned right. So the most significant bits (MSB) are not used
		// Example:
		// 12 bits word alignment: 0x0FFF
		PIXEL_ALIGNMENT_LOW_BITS		= 1,

		// The bits are aligned left. So the least significant bits (LSB) are not used
		// Example:
		// 12 bits word alignment: 0xFFF0
		PIXEL_ALIGNMENT_HIGH_BITS		= 2

	};

	//////////////////////////////////////////////////////////////////////////////////////
	// IMAGE_ORIENTATION enumeration.
	//
	//	Provides information about the layout of the pixel data within the pixel data 
	//	buffer.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	// orientation of image: 
    // bird's view: (0)-->(1)           (0)--->   <---(1)
    //               ^     |             |             |
    //               |     V             V             V
    //              (3)<--(2)
    //                                   ^             ^
    //                                   |             |
    //                                  (3)--->   <---(2)
	//////////////////////////////////////////////////////////////////////////////////////
	enum IMAGE_ORIENTATION
	{
		//////////////////////////////////////////////////////////////////////////////////
		// IMAGE_ORIENTATION_ORIGIN_TOP_LEFT
		//
		//	The first row in memory is the top row of the image. The first pixel of each 
		//	row is the leftmost image pixel.
		//	
		//////////////////////////////////////////////////////////////////////////////////
		IMAGE_ORIENTATION_ORIGIN_TOP_LEFT = 0,

		//////////////////////////////////////////////////////////////////////////////////
		// IMAGE_ORIENTATION_ORIGIN_TOP_RIGHT
		//
		//	The first row in memory is the top row of the image. The first pixel of each 
		//	row is the rightmost image pixel.
		//	
		//////////////////////////////////////////////////////////////////////////////////
		IMAGE_ORIENTATION_ORIGIN_TOP_RIGHT = 1,


		//////////////////////////////////////////////////////////////////////////////////
		// IMAGE_ORIENTATION_ORIGIN_BOTTOM_RIGHT
		//
		//	The first row in memory is the bottom row of the image. The first pixel of 
		//	each row is the rightmost image pixel.
		//	
		//////////////////////////////////////////////////////////////////////////////////
		IMAGE_ORIENTATION_ORIGIN_BOTTOM_RIGHT = 2,
		
		//////////////////////////////////////////////////////////////////////////////////
		// IMAGE_ORIENTATION_ORIGIN_BOTTOM_LEFT
		//
		//	The first row in memory is the bottom row of the image. The first pixel of 
		//	each row is the leftmost image pixel.
		//	
		//////////////////////////////////////////////////////////////////////////////////
		IMAGE_ORIENTATION_ORIGIN_BOTTOM_LEFT = 3
	};


	//////////////////////////////////////////////////////////////////////////////////////
	// IMAGE_VALIDATION_STATE enumeration
	//
	//	Provides information about the image validation state.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	enum IMAGE_VALIDATION_STATE
	{
		IMAGE_VALIDATION_STATE_VALID						= 0x00000000,
		IMAGE_VALIDATION_STATE_X_MOVING						= 0x00000001,
		IMAGE_VALIDATION_STATE_Y_MOVING						= 0x00000002,
		IMAGE_VALIDATION_STATE_Z_MOVING						= 0x00000004,
		IMAGE_VALIDATION_STATE_ZOOM_MOVING					= 0x00000008,
		IMAGE_VALIDATION_STATE_TILT_MOVING					= 0x00000010,
		IMAGE_VALIDATION_STATE_ANGLE_MOVING					= 0x00000020,
		IMAGE_VALIDATION_STATE_SHUTTER_CLOSED				= 0x00000040,
		IMAGE_VALIDATION_STATE_AE_RUNNING					= 0x00000080,
		IMAGE_VALIDATION_STATE_AWB_RUNNING					= 0x00000100,
		IMAGE_VALIDATION_STATE_COUNTER_HARDWAREMOTION		= 0x00000200,
		IMAGE_VALIDATION_STATE_COUNTER_3A					= 0x00000400,
		IMAGE_VALIDATION_STATE_COUNTER_HDR_ROLLING			= 0x00000800,
		IMAGE_VALIDATION_STATE_COUNTER_HDR_WAIT_MIC			= 0x00001000
	};

#ifdef UCAPI_1_1
#ifdef ENABLE_DEPRECATED_WARNINGS
	// IMAGE_AVERAGING_MODE option values are replaced by:
	//	ENHANCED_ACQUISITION_MODE::ENHANCED_ACQUISITION_SIMPLE_AVERAGE
	//	ENHANCED_ACQUISITION_MODE::ENHANCED_ACQUISITION_RUNNING_AVERAGE
#pragma deprecated(IMAGE_AVERAGING_MODE, IAM_NONE, IAM_SIMPLE_AVERAGE, IAM_RUNNING_AVERAGE)
#pragma warning (disable: 4995)
#endif
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	// [deprecated: Use ENHANCED_ACQUISITION_MODE instead]
	// IMAGE_AVERAGING_MODE enumeration.
	//
	//	Averaging mode definitions.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	enum IMAGE_AVERAGING_MODE
	{
		//////////////////////////////////////////////////////////////////////////////////
		// [deprecated: Use ENHANCED_ACQUISITION_MODE::ENHANCED_ACQUISITION_NONE instead]
		// IAM_NONE
		//
		//	Image averaging is disabled.
		//
		//////////////////////////////////////////////////////////////////////////////////
		IAM_NONE,

		//////////////////////////////////////////////////////////////////////////////////
		// [deprecated: Use ENHANCED_ACQUISITION_MODE::ENHANCED_ACQUISITION_SIMPLE_AVERAGE
		// instead]
		// IAM_SIMPLE_AVERAGE
		//
		//	Capture N images and take the average to produce each result image.
		//
		//////////////////////////////////////////////////////////////////////////////////
		IAM_SIMPLE_AVERAGE,

		//////////////////////////////////////////////////////////////////////////////////
		// [deprecated: Use ENHANCED_ACQUISITION_MODE::ENHANCED_ACQUISITION_RUNNING_AVERAGE
		// instead]
		// IAM_RUNNING_AVERAGE
		//
		//	Capture N images and take the average to produce the first result. Then 
		//	combine each new image with the previous N-1 images to produce subsequent
		//	result images.
		//
		//////////////////////////////////////////////////////////////////////////////////
		IAM_RUNNING_AVERAGE
	};
#ifdef UCAPI_1_1
#ifdef ENABLE_DEPRECATED_WARNINGS
#pragma warning (default: 4995)
#endif
#endif

	//////////////////////////////////////////////////////////////////////////////////////
	// EMCCD_MODE enumeration
	//
	//	EMCCD mode definitions.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	enum EMCCD_MODE
	{
		//////////////////////////////////////////////////////////////////////////////////
		// EMCCD_DISABLED
		//
		//	The EMCCD amplification of the sensor is disabled.
		//
		//////////////////////////////////////////////////////////////////////////////////
		EMCCD_DISABLED,

		//////////////////////////////////////////////////////////////////////////////////
		// EMCCD_ENABLED
		//
		//	The EMCCD amplification of the sensor is enabled.
		//
		//////////////////////////////////////////////////////////////////////////////////
		EMCCD_ENABLED,

		//////////////////////////////////////////////////////////////////////////////////
		// EMCCD_ADVANCED
		//
		//	The EMCCD amplification of the sensor is in enabled and the range is extended.
		//
		//////////////////////////////////////////////////////////////////////////////////
		EMCCD_ADVANCED
	};

#ifdef UCAPI_1_1
	//////////////////////////////////////////////////////////////////////////////////////
	// ENHANCED_ACQUISITION_MODE enumeration
	//
	//	Enhanced acquisition mode definitions.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	enum ENHANCED_ACQUISITION_MODE
	{
		//////////////////////////////////////////////////////////////////////////////////
		// ENHANCED_ACQUISITION_NONE
		//
		//	Image composition is disabled.
		//
		//////////////////////////////////////////////////////////////////////////////////
		ENHANCED_ACQUISITION_NONE,

		//////////////////////////////////////////////////////////////////////////////////
		// ENHANCED_ACQUISITION_HDR
		//
		//	High dynamic range acquisition mode. The resultant image contains extended
		//	dynamic range information.
		//
		//////////////////////////////////////////////////////////////////////////////////
		ENHANCED_ACQUISITION_HDR,

		//////////////////////////////////////////////////////////////////////////////////
		// ENHANCED_ACQUISITION_EXTENDED_FOCUS
		//
		//	Extended focus acquisition mode (e.g. Iris-Fusion). The resultant image 
		//	contains extended focus information.
		//
		//////////////////////////////////////////////////////////////////////////////////
		ENHANCED_ACQUISITION_EXTENDED_FOCUS,

		//////////////////////////////////////////////////////////////////////////////////
		// ENHANCED_ACQUISITION_SIMPLE_AVERAGE
		//
		//	Simple image averaging mode. Multiple images are averaged to produce a 
		//	resultant image with increased SnR. The number of images to be averaged "N" is
		//	defined by the PROP_IMAGE_AVERAGING_COUNT property. 
		//	N images are acquired and the average is taken to produce each result image. 
		//
		//////////////////////////////////////////////////////////////////////////////////
		ENHANCED_ACQUISITION_SIMPLE_AVERAGE,

		//////////////////////////////////////////////////////////////////////////////////
		// ENHANCED_ACQUISITION_RUNNING_AVERAGE
		//
		//	Running (moving) image averaging mode. Multiple images are averaged to 
		//	produce a resultant image with increased SnR. The number of images to be 
		//	averaged "N" is defined by the PROP_IMAGE_AVERAGING_COUNT property.
		//	N images are acquired and the average is taken to produce the first result. 
		//	Then each new image is combined with the previous N-1 images to produce 
		//	subsequent result images.
		//
		//////////////////////////////////////////////////////////////////////////////////
		ENHANCED_ACQUISITION_RUNNING_AVERAGE
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// HDR_MODE enumeration
	//
	//	High Dynamic Range acquisition mode definitions.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	enum HDR_MODE
	{
		//////////////////////////////////////////////////////////////////////////////////
		// HDR_MODE_SYMMETRIC
		//
		//	Acquire and compose a set of images at different scene brightnesses centred 
		//	on the initial scene brightness.
		//
		//////////////////////////////////////////////////////////////////////////////////
		HDR_MODE_SYMMETRIC,

		//////////////////////////////////////////////////////////////////////////////////
		// HDR_MODE_ANTI_GLARE
		//
		//	Acquire and compose a set of images at different scene brightnesses at and 
		//	below the initial scene brightness, to create a result image with reduced
		//	pixel saturation.
		//
		//////////////////////////////////////////////////////////////////////////////////
		HDR_MODE_ANTI_GLARE
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// HDR_CONTRAST enumeration
	//
	//	High Dynamic Range image acquisition contrast level definitions. Controls the 
	//	number and relative brightness of the input images. Increasing the contrast
	//	level increases the number of images and/or the relative brightness step between
	//	the images.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	enum HDR_CONTRAST
	{
		//////////////////////////////////////////////////////////////////////////////////
		// HDR_CONTRAST_LOW
		//
		//	Generate a low contrast HDR image.
		//
		//////////////////////////////////////////////////////////////////////////////////
		HDR_CONTRAST_LOW,

		//////////////////////////////////////////////////////////////////////////////////
		// HDR_CONTRAST_MEDIUM
		//
		//	Generate a medium contrast HDR image.
		//
		//////////////////////////////////////////////////////////////////////////////////
		HDR_CONTRAST_MEDIUM,

		//////////////////////////////////////////////////////////////////////////////////
		// HDR_CONTRAST_HIGH
		//
		//	Generate a high contrast HDR image.
		//
		//////////////////////////////////////////////////////////////////////////////////
		HDR_CONTRAST_HIGH,

		//////////////////////////////////////////////////////////////////////////////////
		// HDR_CONTRAST_VERY_HIGH
		//
		//	Generate a very high contrast HDR image.
		//
		//////////////////////////////////////////////////////////////////////////////////
		HDR_CONTRAST_VERY_HIGH
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// MULTI_TAP_READOUT_SELECTOR enumeration
	//
	//  Multi tap readout selector controls the quadrants whereby the image is readout.
	//	There is the possibility to use all four taps or just two of them. In general using
	//	multi tap readout decreases the readout time of the image.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	enum MULTI_TAP_READOUT_SELECTOR
	{
		
		//////////////////////////////////////////////////////////////////////////////////
		// MULTI_TAP_READOUT_SELECTOR_TOP_
		//
		//	Used readout taps
		//
		//////////////////////////////////////////////////////////////////////////////////
		MULTI_TAP_READOUT_SELECTOR_TOP_LEFT			= 0x1,
		MULTI_TAP_READOUT_SELECTOR_TOP_RIGHT		= 0x2,
		MULTI_TAP_READOUT_SELECTOR_BOTTOM_LEFT		= 0x4,
		MULTI_TAP_READOUT_SELECTOR_BOTTOM_RIGHT		= 0x8,


		//////////////////////////////////////////////////////////////////////////////////
		// MULTI_TAP_READOUT_SELECTOR_QUAD
		//
		//	Use all readout taps
		//
		//////////////////////////////////////////////////////////////////////////////////
		MULTI_TAP_READOUT_SELECTOR_QUAD				=	MULTI_TAP_READOUT_SELECTOR_TOP_LEFT | MULTI_TAP_READOUT_SELECTOR_TOP_RIGHT | 
														MULTI_TAP_READOUT_SELECTOR_BOTTOM_LEFT | MULTI_TAP_READOUT_SELECTOR_BOTTOM_RIGHT

	};
#endif

	//////////////////////////////////////////////////////////////////////////////////////
	// ImageFormat interface
	//
	//	Provides information about the format of an image, including its size, pixel 
	//	format and layout in memory.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class ImageFormat
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// width
		//
		//	Get the width of the image in pixels.
		//
		// Return:	The width of the image in pixels.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual iop::int32 width() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// height
		//
		//	Get the height of the image in pixels.
		//
		// Return:	The height of the image in pixels.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual iop::int32 height() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// pixelFormat
		//
		//	Get the pixel format of the image. See the PIXEL_FORMAT enumeration.
		//
		// Return:	The pixel format of the image.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual iop::int32 pixelFormat() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// imageOrientation
		//
		//	Get the pixel data layout information.
		//
		// Return:	A IMAGE_ORIENTATION value that indicates how the pixel data is 
		//	arranged in memory.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual IMAGE_ORIENTATION orientation() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// stride
		//
		//	Get the number of bytes from the start of one row of image data to the start 
		//	of the next row.
		//
		// Return:	The image stride in bytes.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual iop::int32 stride() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// pixelBufferSize
		//
		//	Get the size of the buffer that contains the image data.
		//
		// Return:	The size of the pixel data buffer in bytes.
		//
		// Remarks:
		//	The return type is platform specific (32-bit on 32-bit OS, 64-bit on 64-bit
		//	OS) to allow for the possibility of working with large contiguous images where 
		//	the platform can support them.2
		//
		//////////////////////////////////////////////////////////////////////////////////
		typedef size_t size_type;
		virtual size_type pixelBufferSize() = 0;
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// ImageFormatResult interface
	//
	//	Provides an interface to a disposable image format object.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class ImageFormatResult
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// format
		//
		//	Get the image format information.
		//
		// Return:	A pointer to an ImageFormat object.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual ImageFormat* format() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// dispose
		//
		//	Dispose (delete) the ImageFormatResult object.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual void dispose() = 0;
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// Image interface
	//
	//	Represents an image and provides methods to get information about the image and 
	//	to access the pixel data.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class Image
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// imageFormat
		//
		//	Get information about the image format.
		//
		// Return:	A pointer to an ImageFormat object that contains information about 
		//	the image format.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual ImageFormat* imageFormat() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// imageInfo
		//
		//	Get the property bag container that holds information about the image.
		//
		// Return:	A pointer to the property bag container associated with the image.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual PropertyBag* imageInfo() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// lockPixelData
		//
		//	Lock the image's pixel data so that it can be accessed via the pixelData method.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual void lockPixelData() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// pixelBufferSize
		//
		//	Get a pointer to the image's pixel data.
		//
		// Return:	A pointer to the pixel data for the image if the image is locked, 
		//			else NULL.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual iop::byte* pixelData() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// unlockPixelData
		//
		//	Unlock the image's pixel data.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual void unlockPixelData() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// dispose
		//
		//	Dispose (delete) the image object.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual void dispose() = 0;
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// IMAGE_ACQUISITION_EVENT_TYPE enumeration
	//
	//	Image acquisition event type definitions.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	enum IMAGE_ACQUISITION_EVENT_TYPE
	{
		// The image sensor has started collecting image data.
		IAEV_EXPOSURE_STARTED = 1,
		
		// The image sensor has finished collecting image data.
		IAEV_EXPOSURE_COMPLETE,

		// The image data has been transferred out of the camera.
		IAEV_READOUT_COMPLETE,

		// The camera is ready for sequence acquisition.
		IAEV_READY_TO_CAPTURE_SEQUENCE
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// ImageAcquisitionContext interface
	//
	//	Interface provided by an image acquisition client to provide the resources 
	//	required for an acquisition operation and receive the acquired images.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class ImageAcquisitionContext
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// eInterfaceInfo
		//
		//	Interface version information.
		//
		//////////////////////////////////////////////////////////////////////////////////
		enum eInterfaceInfo
		{
			INTERFACE_VERSION	= 1
		};

		//////////////////////////////////////////////////////////////////////////////////
		// interfaceVersion
		//
		//	Get the version of the ImageAcquisitionContext interface implemented by the 
		//	context object.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual iop::int32 interfaceVersion() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// allocImageBuffer
		//
		//	Get access to an image buffer.
		//
		// pImageFormat:	The format for the image buffer.
		//
		// Return:	A pointer to an image buffer, or NULL if allocation fails.
		//
		// Remarks:	The caller is responsible for managing the lifetime of the image 
		//			buffer and if appropriate releasing it by calling Image::dispose().
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual Image* allocImageBuffer(ImageFormat* pImageFormat) = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// onImageAcquired
		//
		//	Called when an image is acquired.
		//
		// pImage:	The image.
		//
		// Remarks:	The callee is responsible for managing the lifetime of the image 
		//			buffer and including releasing it by calling Image::dispose().
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual void onImageAcquired(Image* pImage) = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// isCancelled
		//
		//	Get whether the acquisition operation has been cancelled.
		//
		// Return:	True if the operation has been cancelled, else false.
		//
		// Remarks:	During an acquisition operation the driver should check periodically 
		//			whether the operation has been cancelled. If so, the driver should stop 
		//			the acquisition operation, perform any necessary cleanup and then 
		//			return from the acquisition method.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual bool isCancelled() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// acquisitionEventSink
		//
		//	Get the event sink to use to pass acquisition events to the acquisition 
		//	client.
		//
		// Return:	A pointer to the event sink to use, or NULL if the client does not 
		//			require acquisition events.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual ahm::EventSink* acquisitionEventSink() = 0;
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// ImageAcquisition interface
	//
	//	Provides methods to execute a "single shot" image capture using the current 
	//	camera settings.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class ImageAcquisition
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// eInterfaceInfo
		//
		//	Interface ID and interface version information.
		//
		//////////////////////////////////////////////////////////////////////////////////
		enum eInterfaceInfo
		{
			IID					= IID_IMAGE_ACQUISITION,
			INTERFACE_VERSION	= 1
		};

		//////////////////////////////////////////////////////////////////////////////////
		// acquire
		//
		//	Acquire one or more images in a single shot using the current camera settings.
		//
		// pContext:	The acquisition context to use for the acquisition operation.
		//
		// pImageInfoPropIds:	A list of property IDs for the property values to be 
		//						included in the	captured image(s) imageInfo property bag. 
		//						Can be NULL or an empty list, in which case no additional 
		//						information is added to the image(s).
		//						See also ImageInformation::getValidImageInfoIds.
		//
		// Remarks:
		//	Images are delivered to the caller via the acquisition context. The method
		//	is synchronous and does not return until after the image(s) has been captured
		//	and delivered to the acquisition context or the operation is cancelled by 
		//	setting the isCancelled member of the context to true.
		//
		//	The caller is responsible for disposing the images passed to the context.
		//
		//	Most commonly a single image will be captured and transferred to the caller 
		//	via a single call to pContext->onImageAcquired.
		//	If the camera supports multiple ROIs and / or multiple sensors then depending 
		//	on the camera settings several images may be captured in a single shot; in this 
		//	case, each image will be transferred to the caller via separate calls to 
		//	pContext->onImageAcquired.
		//	Where multiple images are captured, each image will have one or more values 
		//	added to its imageInfo PropertyBag to indicate the source of the image 
		//	(eg. the capture region and/or sensor from which the image was acquired).
		//
		// ERROR_CODE_INVALID_OPERATION:
		//	Another acquisition operation is already in progress.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual void acquire(
			ImageAcquisitionContext* pContext, ahm::IdList* pImageInfoPropIds) = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// acquireContinuous
		//
		//	Start continuous image acquisition.
		//
		// pContext:	The acquisition context to use for the acquisition operation.
		//
		// pImageInfoPropIds:	A list of property IDs for the property values to be 
		//						included in the	captured image(s) imageInfo property bag. 
		//						Can be NULL or an empty list, in which case no additional 
		//						information is added to the image(s).
		//						See also ImageInformation::getValidImageInfoIds.
		//
		// Remarks:
		//	Images are delivered to the caller via the acquisition context.
		//	Acquisition continues until the isCancelled member of the acquisition context
		//	returns true.
		//	The method is synchronous and does not return until the operation is cancelled
		//	by setting the isCancelled member of the context to true.
		//
		//	The caller is responsible for disposing the images passed to the context.
		//	Most commonly a single image will be captured and transferred to the caller 
		//	per capture cycle.
		//	If the camera supports multiple ROIs and / or multiple sensors then depending 
		//	on the camera settings several images may be captured per cycle; in this 
		//	case, each image will be transferred to the caller via separate calls to 
		//	pContext->onImageAcquired.
		//	Where multiple images are captured in each capture cycle, each image will have 
		//	one or more values added to its imageInfo PropertyBag to indicate the source 
		//	of the image (eg. the ROI and/or sensor from which the image was acquired).
		//
		// ERROR_CODE_INVALID_OPERATION:
		//	Another acquisition operation is already in progress.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual void acquireContinuous(
			ImageAcquisitionContext* pContext, ahm::IdList* pImageInfoPropIds) = 0;
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// AcquisitionSequenceStep interface
	//
	//	Base interface for steps in an acquisition sequence.
	//
	// Remarks:
	//	An acquisition sequence can contain a combination of image captures (configured
	//	via ImageCaptureDefinition objects) and child sequences (configured via
	//	ImageSequenceDefinition objects).
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class AcquisitionSequenceStep
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// eStepType
		//
		//	Defines the types of acquisition step that can be added to acquisition 
		//	sequences.
		//
		//////////////////////////////////////////////////////////////////////////////////
		enum eStepType
		{
			// An image capture step (ImageCaptureDefinition).
			CAPTURE_STEP,

			// A child sequence step (AcquisitionSequenceDefinition).
			SEQUENCE_STEP
		};

		//////////////////////////////////////////////////////////////////////////////////
		// stepType
		//
		//	Get the type of the acquisition step.
		//
		// Return:	An eStepType value that identifies the type of the step.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual iop::int32 stepType() const = 0;
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// ImageCaptureDefinition interface
	//
	//	Provides an acquisition sequence step that defines the settings for a single 
	//	image acquisition operation.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class ImageCaptureDefinition : public AcquisitionSequenceStep
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// settings
		//
		//	Get the acquisition settings for this step.
		//
		// Return:	The property bag that contains the acquisition settings for this step.
		//
		// Remarks:
		//	Attempting to modify the settings while sequence acquisition is in progress 
		//	will result in an ERROR_CODE_INVALID_OPERATION exception.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual PropertyBag* settings() const = 0;
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// AcquisitionSequenceDefinition interface
	//
	//	Provides an acquisition sequence step that defines a sequence of image acquisition 
	//	operations.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class AcquisitionSequenceDefinition : public AcquisitionSequenceStep
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// maxSteps
		//
		//	Get the maximum number of steps that can be added to the sequence.
		//
		// Return:	The maximum number of steps that can be added to the sequence 
		//			definition.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual iop::int32 maxSteps() const = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// numSteps
		//
		//	Get the number of steps currently defined in the sequence.
		//
		// Return:	The number of steps currently contained in the sequence definition.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual iop::int32 numSteps() const = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// numCaptures
		//
		//	Get / set the number of capture operations to execute.
		//
		// numCaptures:	The number of capture operations to execute.
		//
		// Return:	The number of capture operations currently configured.
		//
		// Remarks:
		//	If the number of capture operations configured is greater than the number 
		//	of steps at this level of the sequence definition, the system cycles around the 
		//	steps in the sequence definition. If the sequence contains child sequences,
		//	each child sequence counts as a single step.
		//
		// ERROR_CODE_INVALID_OPERATION:
		//	Sequence acquisition is in progress.
		//
		// ERROR_CODE_PARAMETER_INVALID:
		//	The value requested in numCaptures is not supported.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual iop::int32 numCaptures() const = 0;
		virtual void setNumCaptures(iop::int32 numCaptures) = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// maxCaptures
		//
		//	Get the maximum number of capture operations that can be configured.
		//
		// Return:	The maximum number of capture operations that can be configured.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual iop::int32 maxCaptures() const = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// getStep
		//
		//	retrieve one of the steps in the sequence.
		//
		// index:	The index of the step to access.
		//
		// Return:	A SequenceAcquisitionStep that contains the step definition.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual AcquisitionSequenceStep* getStep(iop::int32 index) const = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// addStep
		//
		//	Add a step into the sequence definition.
		//
		// stepType:	An eStepType value that defines the type of step to add.
		//
		// Return:	A new instance of a SequenceAcquisitionStep derived type corresponding
		//			to the specified stepType.
		//
		// ERROR_CODE_INVALID_OPERATION:
		//	Sequence acquisition is in progress or the sequence already contains
		//	the maximum number of steps.
		//
		// ERROR_CODE_PARAMETER_INVALID:
		//	The requested step type is not supported.
		//
		// Remarks:	The step is added to the end of the sequence.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual AcquisitionSequenceStep* addStep(iop::int32 stepType) = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// queryAddStep
		//
		//	Check whether an acquisition step of a specified type can be added to the 
		//	sequence.
		//
		// stepType:	An eStepType value that defines the type of step to add.
		//
		// Return:	True if the specified type of property can be added, otherwise false.
		//
		// Remarks:	False is returned if the requested step type is not supported,
		//			or if the number of steps in the sequence has already reached the 
		//			maximum limit.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual bool queryAddStep(iop::int32 stepType) const = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// isPropertySupported
		//
		//	Get whether the specified property can be included in capture definitions
		//	at this sequence level.
		//
		// Return:	True if the property is supported for sequence capture, else false.
		//
		// Remarks:	If a camera supports multiple sequence levels (i.e. loops within
		//			loops), the set of properties that can be included at each level 
		//			may be different.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual bool isPropertySupported(iop::int32 propId) const = 0;
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// ImageSequenceAcquisition interface
	//
	//	Provides methods to configure an image acquisition sequence and to execute
	//	the sequence to capture a set of images.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class ImageSequenceAcquisition
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// eInterfaceInfo
		//
		//	Interface ID and interface version information.
		//
		//////////////////////////////////////////////////////////////////////////////////
		enum eInterfaceInfo
		{
			IID					= IID_IMAGE_SEQUENCE_ACQUISITION,
			INTERFACE_VERSION	= 1
		};

		//////////////////////////////////////////////////////////////////////////////////
		// sequenceDefinition
		//
		//	Get the object that can be used to configure the acquisition sequence.
		//
		// Return:	A sequence definition object that can be used to configure 
		//			the sequence acquisition settings.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual AcquisitionSequenceDefinition* sequenceDefinition() const = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// maxSequenceLevels
		//
		//	Get the maximum number of levels of child sequences that can be configured.
		//
		// Return:	The maximum number of levels.
		//
		// Remarks:
		//	The value returned does not include the root sequence definition, so a value
		//	of zero means that the system does not support child loops.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual iop::int32 maxSequenceLevels() const = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// clear
		//
		//	Clear the sequence definition.
		//
		// Remarks:	Removes all the steps from all levels in the sequence definition.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual void clearSequence() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// acquireSequence
		//
		//	Acquire a sequence of images using the current camera settings and sequence 
		//	definition.
		//
		// pContext:	The acquisition context to use for the acquisition operation.
		//
		// pImageInfoPropIds:	A list of property IDs for the property values to be 
		//						included in the captured image(s) imageInfo property bag. 
		//						Can be NULL or an empty	list, in which case no additional 
		//						information is added to the image(s).
		//						See also ImageInformation::getValidImageInfoIds.
		//
		// Remarks:
		//	The caller is responsible for disposing the images transferred to the context.
		//	Most commonly each capture will result in a single image, but if the camera 
		//	supports multiple ROIs and / or multiple sensors then depending on the camera 
		//	settings several images may be acquired per	capture operation.
		//	Each image is transferred to the caller via a call to 
		//	pContext->onImageAcquired.
		//	Each image has a sequence index (IPROP_IMAGE_SEQUENCE_INDEX) included in its 
		//	imageInfo property bag.
		//	Where multiple images are acquired per capture, all the images resulting from 
		//	the same capture operation will have the same sequence index; one or more 
		//	additional values will be added to each image's imageInfo PropertyBag to 
		//	indicate the source of the image (e.g. which readout region and/or sensor the 
		//	image was captured from).
		//
		// ERROR_CODE_INVALID_OPERATION:
		//	Another acquisition operation is already in progress.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual void acquireSequence(
			ImageAcquisitionContext* pContext,
			ahm::IdList* pImageInfoPropIds) = 0;
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// AcquisitionInformation interface
	//
	//	Provides access to acquisition information such as the active image format.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class AcquisitionInformation
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// eInterfaceInfo
		//
		//	Interface ID and interface version information.
		//
		//////////////////////////////////////////////////////////////////////////////////
		enum eInterfaceInfo
		{
			IID					= IID_ACQUISITION_INFORMATION,
			INTERFACE_VERSION	= 1
		};

		//////////////////////////////////////////////////////////////////////////////////
		// getImageCount
		//
		//	Get the number of images that will be delivered per acquisition.
		//	In most cases a single image will be delivered per acquisition, but if the 
		//	device supports multiple readout regions (via PROP_READOUT_REGIONS) or 
		//	multiple sensors then multiple images may be delivered.
		//
		// Return:	The number of images that will be delivered per acquisition.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual iop::int32 getImageCount() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// getImageFormat
		//
		//	Get information about the format of the image that will be delivered when an
		//	image is acquired, based on the current camera settings.
		//
		// imageIndex:	If the camera delivers multiple images per acquisition, the	index
		//				of the image for which to retrieve the format. Otherwise,
		//				this parameter should be set to zero.
		//
		// Return:	A pointer to an ImageFormatResult that contains the image format
		//			information. The caller is responsible for disposing the result.
		//
		// ERROR_CODE_PARAMETER_INVALID:
		//	(imageIndex < zero) or (imageIndex >= the number of images per acquisition).
		//
		// Remarks:
		//	The format information returned is the format of the image that will actually be
		//	delivered if an image is acquired using the current camera settings.
		//	It takes account of all the camera settings	that affect the image format, 
		//	including the active acquisition mode and image format ID (if supported), binning 
		//	level, sub-sampling level, bit depth, image type and any readout region set on the 
		//	camera.
		//////////////////////////////////////////////////////////////////////////////////
		virtual ImageFormatResult* getImageFormat(iop::int32 imageIndex) = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// getValidImageInfoIds
		//
		//	Get the list of image info IDs that can be included with acquired images in
		//	the Image::imageInfo property bag.
		//
		// Return:	A pointer to an IdList that contains the image info IDs that are
		//			available, based on the current acquisition settings.
		//
		// Remarks:
		//	When acquiring an image, the client can request additional metadata to be 
		//	included with the image by passing an ID list to the acquisition method.
		//	For each of the IDs in the list passed to an acquisition method, if the ID
		//	is currently valid the current value associated with the ID will be added 
		//	to the image's imageInfo property bag; if the ID is not currently valid, it
		//	is ignored.
		//	The client can use the getValidImageInfoIds method to determine which ID
		//	requests can be satisfied based on the current acquisition settings.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual ahm::IdList* getValidImageInfoIds() = 0;
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// ImageFormatDefinition interface
	//
	//	Provides information about a pre-defined image format, including the format ID 
	//	and the width and height of the image.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class ImageFormatDefinition
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// formatId
		//
		//	Get the ID of the image format.
		//
		// Return:	The format's ID.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual iop::int32 id() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// formatSettings
		//
		//	Get the settings that are determined by the image format.
		//
		// Return:	A pointer to a PropertySettingList that contains the list of
		//			property values that are applied when the format is selected as the
		//			active format.
		//
		// Remarks:
		//	The settings list contains the values of all the properties that will be
		//	affected when the format is selected.
		//	The list always contains values for PROP_LOGICAL_XRESOLUTION,
		//	PROP_LOGICAL_YRESOLUTION, PROP_LOGICAL_PIXEL_XSIZE,	PROP_LOGICAL_PIXEL_YSIZE.
		//	The list also contains additional values for any other camera properties that 
		//	are	determined by the format (e.g. PROP_BINNING_LEVEL, PROP_READOUT_SPEED etc).
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual PropertySettingList* formatSettings() = 0;
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// ImageFormatDefinitionResult interface
	//
	//	Provides access to a disposable image format definition object.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class ImageFormatDefinitionResult
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// formatDefinition
		//
		//	Get the image format definition.
		//
		// Return:	A pointer to an ImageFormatDefinition object.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual ImageFormatDefinition* formatDefinition() = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// dispose
		//
		//	Dispose (delete) the ImageFormatDefinitionResult object.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual void dispose() = 0;
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// ImageFormatInformation interface
	//
	//	Provides information about the available image formats.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class ImageFormatInformation
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// eInterfaceInfo
		//
		//	Interface ID and interface version information.
		//
		//////////////////////////////////////////////////////////////////////////////////
		enum eInterfaceInfo
		{
			IID					= IID_IMAGE_FORMAT_INFORMATION,
			INTERFACE_VERSION	= 1
		};

		//////////////////////////////////////////////////////////////////////////////////
		// getFormatDefinition
		//
		//	Get the image format definition corresponding to a format ID.
		//
		// formatId:	The ID of the format for which to retrieve information.
		//
		// Return:	A pointer to an ImageFormatDefinitionResult that contains information 
		//			about the specified image format. The caller is responsible for 
		//			disposing the result.
		//
		// ERROR_CODE_INVALID_OPERATION:
		//	The camera does not support format IDs (PROP_CAPTURE_FORMAT_ID / 
		//	PROP_STREAMING_FORMAT_ID).
		//
		// ERROR_CODE_PARAMETER_INVALID:
		//	The formatId specified is not supported by the camera.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual ImageFormatDefinitionResult* getFormatDefinition(iop::int32 formatId) = 0;
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// OneShotWhiteBalance interface
	//
	//	Provides support for one-shot white balance operations.
	//
	// Remarks:
	//	The interface state is set to TEMPORARY_INVALID while the active image format
	//	is a mono format.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class OneShotWhiteBalance
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// eInterfaceInfo
		//
		//	Interface ID and interface version information.
		//
		//////////////////////////////////////////////////////////////////////////////////
		enum eInterfaceInfo
		{
			IID					= IID_ONE_SHOT_WHITE_BALANCE,
			INTERFACE_VERSION	= 1
		};

		//////////////////////////////////////////////////////////////////////////////////
		// executeWhiteBalance
		//
		//	Perform a one-shot white balance operation.
		//
		// pRoi:	A pointer to an INT_RECT that defines the region of the image to use
		//			to calculate the white balance, in logical pixel coordinates. The ROI
		//			is clipped to the active readout region if necessary.
		//			If pRoi is NULL the white balance is performed on the full image (or
		//			full readout region if active).
		//
		// ERROR_CODE_INVALID_OPERATION:
		//	Continuous auto white balance is currently active 
		//	(PROP_CONTINUOUS_WHITE_BALANCE_ENABLED is currently set to true).
		//	An acquisition operation is in progress.
		//
		// ERROR_CODE_IMAGE_TOO_DARK:
		//	The image contains too many over-exposed pixels.
		//
		// ERROR_CODE_IMAGE_TOO_BRIGHT:
		//	The image contains too many under-exposed pixels.
		//
		// Remarks:
		//	If the operation completes successfully the PROP_GAIN_RED, PROP_GAIN_BLUE and
		//	PROP_GAIN_GREEN property values are updated.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual void executeWhiteBalance(ahm::INT_RECT* pRoi) = 0;
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// OneShotBlackBalance interface
	//
	//	Provides support for one-shot black balance operations.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class OneShotBlackBalance
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// eInterfaceInfo
		//
		//	Interface ID and interface version information.
		//
		//////////////////////////////////////////////////////////////////////////////////
		enum eInterfaceInfo
		{
			IID					= IID_ONE_SHOT_BLACK_BALANCE,
			INTERFACE_VERSION	= 1
		};

		//////////////////////////////////////////////////////////////////////////////////
		// executeBlackBalance
		//
		//	Perform a one-shot black balance operation.
		//
		// pRoi:	A pointer to an INT_RECT that defines the region of the image to use
		//			to calculate the black balance, in logical pixel coordinates. The ROI
		//			is clipped to the active readout region if necessary.
		//			If pRoi is NULL the black balance is performed on the full image (or
		//			full readout region if active).
		//
		// ERROR_CODE_IMAGE_TOO_DARK:
		//	The image contains too many over-exposed pixels.
		//
		// ERROR_CODE_IMAGE_TOO_BRIGHT:
		//	The image contains too many under-exposed pixels.
		//
		// Remarks:
		//	If the operation completes successfully the PROP_BLACK_BALANCE_LEVEL is updated.
		//	The new black balance level is applied only if the PROP_BLACK_BALANCE_ENABLED
		//	property is set to true.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual void executeBlackBalance(ahm::INT_RECT* pRoi) = 0;
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// WhiteShadingReferenceCreator interface
	//
	//	Provides methods to create and save white shading references.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class WhiteShadingReferenceCreator
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// eInterfaceInfo
		//
		//	Interface ID and interface version information.
		//
		//////////////////////////////////////////////////////////////////////////////////
		enum eInterfaceInfo
		{
			IID					= IID_WHITE_SHADING_REFERENCE_CREATOR,
			INTERFACE_VERSION	= 1
		};

		//////////////////////////////////////////////////////////////////////////////////
		// createShadingReferenceFile
		//
		//	Create a white shading reference and save it to a file.
		//
		// fileName:	The full path to the file in which to save the shading reference.
		//				If the file exists it is overwritten.
		//
		// ERROR_CODE_INVALID_OPERATION:
		//	An acquisition operation is in progress.
		//
		// ERROR_CODE_PARAMETER_INVALID:
		//	fileName is NULL or empty or is not a valid file path.
		//
		// ERROR_CODE_FILE_WRITE:
		//	An error occurred when trying to save the shading reference to the file.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual void createShadingReferenceFile(iop::string fileName) = 0;
	};

	//////////////////////////////////////////////////////////////////////////////////////
	// PropertyDependencyInformation interface
	//
	//	Provides methods to get dependency information about properties.
	//
	//////////////////////////////////////////////////////////////////////////////////////
	class PropertyDependencyInformation
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////
		// eInterfaceInfo
		//
		//	Interface ID and interface version information.
		//
		//////////////////////////////////////////////////////////////////////////////////
		enum eInterfaceInfo
		{
			IID					= IID_PROPERTY_DEPENDENCY_INFORMATION,
			INTERFACE_VERSION	= 1
		};

		//////////////////////////////////////////////////////////////////////////////////
		// eDependencyType
		//
		//	The types of dependency information that can be queried.
		//
		//////////////////////////////////////////////////////////////////////////////////
		enum eDependencyType
		{
			// Query for properties that affect another property's value.
			// Generally only applicable to read-only properties.
			DEPENDENCY_TYPE_VALUE,

			// Query for properties that affect another property's default value.
			DEPENDENCY_TYPE_DEFAULT_VALUE,

			// Query for properties that affect another property's access rights.
			DEPENDENCY_TYPE_ACCESS_RIGHTS
		};

		//////////////////////////////////////////////////////////////////////////////////
		// getDeterminants
		//
		//	Get the properties that affect the value or metadata of another property.
		//
		// propId:	The ID of the dependent property.
		//
		// dependencyType:	A value from the eDependencyType enum that specifies the type
		//					of dependency to query.
		//
		// Return:	If dependency information is available for the specified property, a 
		//			pointer to an IdListResult that contains the IDs of the properties on 
		//			which the specified attribute of the property depends, otherwise NULL.
		//			If the specified attribute of the property is independent of other 
		//			properties the returned list is empty.
		//			If the requested property is not supported, the return value is NULL.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual ahm::IdListResult* getDeterminants(
			iop::int32 propId, eDependencyType dependencyType) = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// queryValue
		//
		//	Get the value of a dependent property given a set of values for its
		//	determinant	properties.
		//
		// propId:	The ID of the dependent property.
		//
		// pDeterminants:	A pointer to a list of property settings to use to determine
		//					the value of the dependent property.
		//
		// Return:	If the dependent value can be determined, a pointer to a PropertySetting 
		//			that contains the value of the dependent property, given the specified 
		//			values of the determinant properties. If the dependent value cannot be 
		//			determined or the requested property is not supported, the return 
		//			value is NULL.
		//
		// ERROR_CODE_PARAMETER_INVALID:
		//	pDeterminants is NULL.
		//
		// Remarks:
		//	If pDeterminants is empty, the current value of the property is returned.
		//	If pDeterminants includes property settings that do not affect the requested 
		//	property they are ignored.
		//	If pDeterminants does not include settings for all the determinant properties,
		//	the current value of any missing determinants is used.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual PropertySetting* queryValue(
			iop::int32 propId,
			PropertySettingList* pDeterminants) = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// queryDefaultValue
		//
		//	Get the default value of a dependent property given a set of values for its
		//	determinant	properties.
		//
		// propId:	The ID of the dependent property.
		//
		// pDeterminants:	A pointer to a list of property settings to use to determine
		//					the value of the dependent property.
		//
		// Return:	If the default value can be determined, a pointer to a PropertySetting 
		//			that contains the default value of the dependent property, given the 
		//			specified values of the determinant properties. If the default value 
		//			cannot be determined or the requested property is not supported, the 
		//			return value is NULL.
		//
		// ERROR_CODE_PARAMETER_INVALID:
		//	pDeterminants is NULL.
		//
		// Remarks:
		//	If pDeterminants is empty, the current default value of the property
		//	is returned.
		//	If pDeterminants includes property settings that do not affect the requested 
		//	property they are ignored.
		//	If pDeterminants does not include settings for all the determinant properties,
		//	the current value of any missing determinants is used.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual PropertySetting* queryDefaultValue(
			iop::int32 propId,
			PropertySettingList* pDeterminants) = 0;

		//////////////////////////////////////////////////////////////////////////////////
		// queryAccessRights
		//
		//	Get the access rights of a dependent property given a set of values for its
		//	determinant	properties.
		//
		// propId:	The ID of the dependent property.
		//
		// pDeterminants:	A pointer to a list of property settings to use to determine
		//					the access rights of the dependent property.
		//
		// Return:	If the access rights cannot be determined or the property is not 
		//			supported PropertyInfo::EAccessRights::UNDEF is returned.
		//			Otherwise a combination of the PropertyInfo::EAccessRights flags 
		//			that specify the access rights of the property given the specified
		//			determinant values. 
		//
		// ERROR_CODE_PARAMETER_INVALID:
		//	pDeterminants is NULL.
		//
		// Remarks:
		//	If pDeterminants is empty, the property's current access rights 
		//	are returned.
		//	If pDeterminants includes property settings that do not affect the requested 
		//	property they are ignored.
		//	If pDeterminants does not include settings for all the determinant properties,
		//	the current value of any missing determinants is used.
		//
		//////////////////////////////////////////////////////////////////////////////////
		virtual iop::int32 queryAccessRights(
			iop::int32 propId,
			PropertySettingList* pDeterminants) = 0;
	};
} // namespace ucapi

#endif
