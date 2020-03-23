/*
 * Published Abstract Hardware Model Interfaces and Definitions
 * basically applying all hardware
 *
 * Copyright 2002, 2012 (c) Leica Microsystems - All Rights Reserved.
 * 
 *
 * author: H. Wagner, A. Bird, P.Engler
 *
 * created:      21.02.2003
 * last updated: 2012
 *
 * Conceptial changes:
 *  
 * there is a class Property,
 *  - this holds the current value of the Property and gives direct access to its property info
 * 
 * property info:
 *  new: the property id
 *  new: the value type of the property
 *
 * DataValue renamed to PropertyValue
 * - PropertyValue, gives access rights to the value
 *
 * new Value Classes for Arrays and "Compounds"
 * 
 * Compounds are now "PROPERTIES" itself
 * ==> Value type: PropertyValueProperties
 *
 * update: 28.02.2003
 * formalized names according ahm.h and BasicControlValue
 * property id again in Property class
 *
 * update: 10.06.2003
 * various changes.
 *
 * update: 18.12.2003
 * Added PropertyValueFloatRect, PropertyValue::TYPE_FLOATRECT and FLOAT_RECT
 *
 * update: 25.11.2005
 * 
 * Added PropertyValueChangedEvent
 *
 * update 14.05.2008
 * 
 * Added PropertiesResult for temporary properties
 *
 * update for 07.12.2012 
 * 
 * PropertyInfoSteppedRange extends PropertyInfoRange
 * 
 *
 */

#ifdef USE_DEPRECATED_AHM_PROPERTIES
#include "deprecated_ahwprop2.h"
#define PUBLIC_AHM_PROPERTIES_H /* exit on new version */
#endif


#ifndef PUBLIC_AHM_PROPERTIES_H
#define PUBLIC_AHM_PROPERTIES_H
#define AHM_PROPERTIES_VERSION2

#include "ahm.h" // include base defs
#include "ahwbasic.h"  // IID definitions

namespace ahm {

class Property; // forward
class PropertyInfo; // forward
class PropertyValue; // forward

/**
 * Properties interface.
 * The class represents a container for a set of attributes representing
 * the unit's state.
 * It allows a client to iterate over all Properties
 * or to search for a specific property by its id.
 * 
 * IID: PROPERTIES
 */
class Properties  {
public:
	typedef enum eClassInfo { IID=ahm::IID_PROPERTIES, INTERFACE_VERSION=2 } EClassInfo;

	/**
	* How many Properties are inside the container.
	* @return number of properties
	*/
	virtual iop::int32 numProperties() = 0;

	/**
		* Get a Property from the container
		* @param index of property ( 0 <= index < numProperties())
		* @return Property according index.
		*
		* @see numProperties()
		*/
	virtual Property * getProperty(iop::int32 index) = 0;

	/**
		* Retrieve a Property by a property id.
		* @param defined property id
		*
		* @return Property having this or property or null if not found.
		*/
	virtual Property * findProperty(iop::int32 propertyId) = 0;

};

/**
 * Property object
 * Each property has an ID, a value (the current value of the property) and
 * information about the set of valid settings for the property.
 */
class Property  {
public:

	/**
	 *  retrieve the property id
	 */
	virtual iop::int32 id() = 0;

	/**
	* access value of the property 
	*/
	virtual PropertyValue* value() = 0;

	/**
	* get property info 
	*/ 
    virtual PropertyInfo *getPropertyInfo() = 0;
};


/**
 * Base class for property values.
 *
 * Example:
 *	Properties* pProps = get properties interface...
 *	Property* pProp = pProps->getProperty(0);	// Retrieve the first property
 *	// Access the value based on the actual type
 *	switch (pProp->derivedType())
 *	{
 *	case PropertyValue::TYPE_INT:
 *		{
 *			iop::int32 value = ((PropertyValueInt*)pProp)->getValue();
 *		}
 *
 *	case PropertyValue::TYPE_FLOAT:
 *		{
 *			iop::float64 value = ((PropertyValueFloat*)pProp)->getValue();
 *		}
 *
 *		.
 *		.
 *		.
 *	}
 *
 */
class PropertyValue {
public:

	/**
	 * List of defined property value types. 
	 * One of these values will be returned via derivedType()
	 */
	typedef enum ePropertyValueType {
		__TYPE_SCALAR_START=0,
  		TYPE_STRING = __TYPE_SCALAR_START,	// PropertyValueString
		TYPE_INT,							// PropertyValueInt
		TYPE_FLOAT,							// PropertyValueFloat
		TYPE_BOOL,							// PropertyValueBool
		TYPE_UNICODE_STRING,				// PropertyValueUnicodeString
		TYPE_INDEX,							// PropertyValueIndex
		__TYPE_SCALAR_MAX,
		TYPE_PROPERTIES=100,				// PropertyValueProperties
		TYPE_FIXED_ARRAY,					// PropertyValueArray
		TYPE_DYNAMIC_ARRAY,					// PropertyValueDynamicArray
		TYPE_RECT,							// PropertyValueRect - deprecated
		TYPE_FLOAT_RECT						// PropertyValueFloatRect - deprecated

#ifdef AHM_2_0
		,TYPE_INT_RECT						// PropertyValueIntRect
#endif
	} EPropertyValueType;

	/**
	* Retrieve value type to cast this to
	*/
	virtual iop::int32 derivedType() = 0;    

};

/**
 * Basic property information class.
 */
class PropertyInfo  {
public:

	/**
	* List of defined property info types. 
	* One of these values will be returned via derivedType()
	*/
	typedef enum ePropertyInfoType {
		TYPE_BASIC,				// Basic property information - PropertyInfo
		TYPE_RANGE,				// Range of allowed values - PropertyInfoRange
		TYPE_ENUMERATION,		// List of allowed values - PropertyInfoEnum
		TYPE_COMPOUND,			// Multiple ranges and/or lists of allowed values - PropertyInfoCompound
		TYPE_RECT,				// Bounding rectangle for a rectangle property type - PropertyInfoRect
		TYPE_STEPPED_RANGE		// Range of allowed value - with a constant stepsize - PropertyInfoSteppedRange
	} EPropertyInfoType;


	/**
	* The actual type of the PropertyInfoXXX derived class. See ePropertyInfoType.
	*/
	virtual iop::int32 derivedType() = 0;

	/**
	* The type of the property value object associated with this property.
	*	See PropertyValue::ePropertyValueType.
	*
	* NOTE: For enumerated properties (PropertyInfoEnum) the type returned indocates
	*		the type of the underlying enumerated options - ie. the type of value
	*		that will be returned by calls to PropertyInfoEnum::getOption().
	*		The property value and default are always TYPE_INDEX for enumerated
	*		properties.
	*/
	virtual iop::int32 valueType() = 0;

	/**
	* Available access rights.
	*/
	typedef enum ePropertyAccess {
		UNDEF, READ, WRITE, READWRITE
	} EAccessRights;

	/**
	* Retrieve access rights of property.
	*/
	virtual iop::int32 accessRights() = 0;

	/**
	* Retrieve default property value
	*/
	virtual PropertyValue * defaultValue() = 0;
};


/****************************************
 * Property Information types.
 ****************************************/

/**
 * Property range information class (TYPE_RANGE).
 * Describes a range of valid values from which a property can be set. The range
 * is defined by the minimum and maximum limits on the property value.
 */
class PropertyInfoRange : public PropertyInfo
{
public:
	/**
	* Retrieve minimum value
	*/
	virtual PropertyValue* minValue() = 0;

	/**
	* Retrieve maximum value
	*/
	virtual PropertyValue* maxValue() = 0;
};


/**
 * Property stepped range information class (TYPE_STEPPED_RANGE).
 * Describes a range of valid values from which a property can be set. The range
 * is defined by the minimum and maximum limits on the property value.
 * A fixed stepsize can be retrieved. abs(maxValue - minValue)/stepSize is a natural number.
 *
 * possible value types: PropertyValueInt, PropertyValueFloat
 */

class PropertyInfoSteppedRange : public PropertyInfoRange {
public:
	virtual PropertyValue* stepSize() = 0;
};

/**
 * Enumerated property information class (TYPE_ENUMERATION).
 *	Describes a list of possible values to which a property can be set. The
 *	property value contains the index of the currently selected option. The
 *	property value (and the default value) is always of type PropertyValueIndex.
 *
 *
 * Example
 *
 *	Properties* pProps = get properties interface...
 *	Property* pProp = pProps->getProperty(0);	// Retrieve the first property
 *	// See if its an enumerated type
 *	if (pProp->getProperetyInfo()->derivedType() == PropertyInfo::TYPE_ENUMERATION)
 *	{
 *		PropertyInfoEnum* pEnum = (PropertyInfoEnum*)pProp->getPropertyInfo();
 *		// Read back the value associated with the currently selected option
 *		ASSERT(pProp->value()->derivedType() == PropertyValue::TYPE_INDEX);
 *		iop::int32 index = ((PropertyValueIndex*)(pProp->value()))->getIndex();
 *		PropertyValue* pOption = pEnum->getOption(index);
 *		switch (pOption->derivedType())
 *		{
 *		case PropertyValue::TYPE_FLOAT:	// Underlying values are floating point
 *			{
 *				iop::float64 value = ((PropertyValueFloat*)pOption)->getValue();
 *			}
 *
 *		case PropertyValue::TYPE_INT:	// Underlying values are integers
 *			{
 *				iop::int32 value = ((PropertyValueInt*)pOption)->getValue();
 *			}
 *
 *		case PropertyValue::TYPE_STRING:	// Underlying values are strings
 *			{
 *				StringResult* pstrValue = ((PropertyValueString*)pOption)->getValue();
 *				iop::string strVal = pstrValue->value();
 *				// Do something with the string value ...
 *				pstrValue->dispose();
 *			}
 *
 *			.
 *			.
 *			.
 *
 *		}
 *
 *		// Select a new option (2)
 *		if (pEnum->numOptions() > 2) // Check index is valid
 *			((PropertyValueIndex*)(pProp->value()))->setIndex(2);	// select option 2
 *
 *	}
 *	
 */
class PropertyInfoEnum : public PropertyInfo
{
public:
	/**
	* Retrieve the number of options available.
	* @return The number of options.
	*/
	virtual iop::int32 numOptions() = 0;

	/**
	* Retrieve the value of the option at the specified index.
	* (0 <= index <= numOptions()).
	* The type of the PropertyValue returned by this method depends on
	* the underlying type of the enumeration.
	*	Eg. If the enum is a list of strings, this method will return
	*		PropertyValueString objects (TYPE_STRING). If it is a list
	*		of floating point numbers, this method returns PropertyValueFloat
	*		objects (TYPE_FLOAT) etc.
	*/
	virtual PropertyValue* getOption(iop::int32 index) = 0;
};

/**
 * Generic rectangle property information class (TYPE_RECT).
 *	Describes the bounding box for a rectangle.
 *
 * NOTE: The defaultValue method will return a PropertyValueRect that
 *		 contains the default position of the rectangle.
 */
class PropertyValueRect; // forward definition
class PropertyInfoRect : public PropertyInfo
{
public:
	/**
	* Retrieve the bounding rectangle
	* ie. The region within which the rectangle can reside.
	*/
	virtual PropertyValueRect* boundingRect() = 0;
};


/**
 *  Compound information class (TYPE_COMPOUND).
 *	Describes a combination of ranges and enumerated values to which a 
 *	property can be set.
 */
class PropertyInfoCompound : public PropertyInfo
{
public:
	/**
	* Retrieve the number of sub-ranges available.
	* @return The number of sub-ranges.
	*/
	virtual iop::int32 numInfos() = 0;

	/**
	* Retrieve a sub-range by index (0 <= index < numOptions()).
	*	Each sub-range could be a range or an enumeration.
	*/
	virtual PropertyInfo* getInfo(iop::int32 index) = 0;
};


/****************************************
 * Property Value Types.
 ****************************************/

/**
 * String property value class (TYPE_STRING).
 */
class PropertyValueString : public PropertyValue
{
public:
	/**
	* Retrieve the current value of the property.
	*/
	virtual StringResult* getValue() = 0;
	  
	/**
	* Set the value the value
	*/
	virtual void setValue(iop::string newVal) = 0;

	/**
	* Maximum length for the string
	*	Returns MAX_INT if the string length is unconstrained.
	*/
	virtual iop::int32 maxLength() = 0;
};

/**
 * String property value class (TYPE_UNICODESTRING).
 */
class PropertyValueUnicodeString : public PropertyValue
{
public:
	/**
	* Retrieve the current value of the property.
	*/
	virtual UnicodeStringResult* getValue() = 0;
	  
	/**
	* Set the value the value
	*/
	virtual void setValue(iop::unicode_string newVal) = 0;

	/**
	* Maximum length for the string
	*	Returns MAX_INT if the string length is unconstrained.
	*/
	virtual iop::int32 maxLength() = 0;
};


/**
 * Integer property value class (TYPE_INT).
 */
class PropertyValueInt : public PropertyValue
{
public:
	/**
	* Retrieve the current value of the property.
	*/
	virtual iop::int32 getValue() = 0;
	  
	/**
	* modify the current value 
	*/
	virtual void setValue(iop::int32 newVal) = 0;
};

/**
 * Index property value class (TYPE_INDEX).
 *	Used for enumerated types to hold the index of the currently selected option.
 */
class PropertyValueIndex : public PropertyValue
{
public:
	/**
	* Retrieve the current index
	*/
	virtual iop::int32 getIndex() = 0;
	  
	/**
	* Select a new index
	*/
	virtual void setIndex(iop::int32 newVal) = 0;
};

/**
 * Floating point property value class (TYPE_FLOAT).
 */
class PropertyValueFloat : public PropertyValue
{
public:
	/**
	* Retrieve the current value of the property.
	*/
	virtual iop::float64 getValue() = 0;
	  
	/**
	* modify the current value 
	*/
	virtual void setValue(iop::float64 newVal) = 0;
};


/**
 * Boolean property value class (TYPE_BOOL).
 */
class PropertyValueBool : public PropertyValue
{
public:
	/**
	* Retrieve the current value of the property.
	*/
	virtual bool getValue() = 0;
	  
	/**
	* modify the current value 
	*/
	virtual void setValue(bool newVal) = 0;
};

/**
 * Fixed size array (TYPE_FIXED_ARRAY)
 */
class PropertyValueArray : public PropertyValue {
public:
	/**
	* retrieve how many elements are in the array
	*/
	virtual iop::int32 numValues() = 0;

	/**
	* retrieve the lowest valid index - ie. the index of the first
	* element in the array.
	*/
	virtual iop::int32 minIndex() = 0;

	/**
	* retrieve the highest valid index - ie. the index of the last
	* element in the array.
	* NOTE: maxIndex() == minIndex() + numValues() - 1.
	*/
	virtual iop::int32 maxIndex() = 0;

	/**
	* access an element of the array
	*	( minIndex()<= index <= maxIndex() )
	*/
	virtual PropertyValue* getValue(iop::int32 index) = 0;
};

/**
 * Dynamic (resizable) array (TYPE_DYNAMIC_ARRAY)
 */
class PropertyValueDynamicArray : public PropertyValueArray {
public:
	/**
	* retrieve the maximum number of elements that can be in the array.
	*/
	virtual iop::int32 maxSize() = 0;

	/**
	* add a new empty element to the array.
	*/
	virtual PropertyValue* addValue() = 0;

	/**
	* remove an element from the array
	*	( minIndex()<= index <= maxIndex() )
	*/
	virtual void removeValue(iop::int32 index) = 0;

	/**
	* remove all elements from the array
	*/
	virtual void clear() = 0;
};


/**
 * Container property (TYPE_PROPERTIES)
 *	Provides the ability to model hierarchical properties.
 */
class PropertyValueProperties : public PropertyValue {
public:
	/**
	*  get access to elements
	*/
	virtual Properties *properties() = 0;
};


/**
 * Generic rectangle property value. (TYPE_RECT)
 *
 *	left, top, right, bottom values can be TYPE_INT or TYPE_FLOAT.
 *
 *	The associated PropertyInfo object should be a PropertyInfoRect.
 */
class PropertyValueRect : public PropertyValue
{
public:
	/**
	* Left edge
	*/
	virtual PropertyValue* left() = 0;

	/**
	* Top edge
	*/
	virtual PropertyValue* top() = 0;

	/**
	* Right edge
	*/
	virtual PropertyValue* right() = 0;

	/**
	* Bottom edge
	*/
	virtual PropertyValue* bottom() = 0;
};

/**
 * Floating point rectangle property. (TYPE_FLOAT_RECT)
 *
 *	Values are in percent of the available area.
 *
 *	The associated PropertyInfo object should return a PropertyValueFloatRect from
 *	its defaultValue() method.
 */
	/*
	* Floating point rectangle strucure used with PropertyvalueFloatRect
	*
	*	left and right are specified as a percentage of the image width.
	*	top and bottom are specified as a percentage of the image height.
	*/
	struct FLOAT_RECT {
		iop::float64 left;
		iop::float64 top;
		iop::float64 right;
		iop::float64 bottom;
	};

class PropertyValueFloatRect : public PropertyValue
{
public:
	/**
	* Get the rectangle
	*/
	virtual void getValue(FLOAT_RECT& rect) = 0;

	/**
	* Set the rectangle
	*/
	virtual void setValue(FLOAT_RECT& rect) = 0;
};


#ifdef AHM_2_0

struct INT_RECT {
	iop::int32 left;
	iop::int32 top;
	iop::int32 width;
	iop::int32 height;
};

class PropertyValueIntRect : public PropertyValue
{
public:
	/**
	* Get the rectangle
	*/
	virtual INT_RECT getValue() = 0;

	/**
	* Set the rectangle
	*/
	virtual void setValue(INT_RECT& rect) = 0;
};

#endif

	/**
	 * Property Event - fired when a Property has changed
	 */
    class PathPropertyValue;

	class PropertyValueChangedEvent : public Event {
	public:
		typedef enum eClassInfo { EVENT_TYPE = EVENT_PROPERTY_CHANGED } EClassInfo;
		virtual PathPropertyValue *propertyPath() = 0;
		virtual PropertyValue* value() = 0;
	};
	class PathItemPropertyValue;

	class PathPropertyValue {
	public:
		virtual iop::int32 numPathItems() = 0;
		virtual PathItemPropertyValue* pathItem(iop::int32 index) = 0;
	};

	class PathItemPropertyValue {
	public:
		typedef enum eType {
			PROPERTY, // ==> value() returns the property id
			ARRAYINDEX    // ==> value() return the array index
		} EType;
		virtual iop::int32 itemType() = 0;
		virtual iop::int32 value() = 0;
	};

	class PropertiesResult {
	public:
		virtual Properties* properties() = 0;
		/**
		 * don't forget to call dispose to prevent memory leaks
		 */
		virtual void dispose() = 0;
	};


#ifdef AHM_2_0
	class PropertyInfoChangedEvent : public Event {
	public:
		typedef enum eClassInfo { EVENT_TYPE = EVENT_PROPERTY_INFO_CHANGED } EClassInfo;
		/**
		 * identifies the related property
		 */
		virtual PathPropertyValue *propertyPath() = 0;
		// the changed property info object
		virtual PropertyInfo* propertyInfo() = 0;

		typedef enum eInfoChangeHints {
			INFO_CHANGE_ACCESS_RIGHTS  = 0x01,  // access rights are changed
			INFO_CHANGE_RANGE		   = 0x02,	// value range has changed dependent from info type (the list in InfoEnum - or min/max value in case of range
			INFO_CHANGE_DEFAULT_VALUE  = 0x04	// default value is changed
		} EInfoChangeHints;
		// give some hints what is changed in info (bit OR combination of enum EInfoChangeHints)
		virtual iop::int32 changeHints() = 0;
	};

	/**
	 * property enum event
	 * fired when an enum value is changed
	 * - it contains the "index value" and the corresponding value of the enumeration
	 */
	class PropertyValueEnumChangedEvent : public Event {
	public:
		typedef enum eClassInfo { EVENT_TYPE = EVENT_PROPERTY_ENUM_CHANGED } EClassInfo;
		/**
		 * identifies the related property
		 */
		virtual PathPropertyValue *propertyPath() = 0;
		/**
		 * index value - the index in the enumeration 0.. numOptions()-1
		 */
		virtual iop::int32 indexValue() = 0;
		/**
		 * corresponding value in PropertyInfoEnum
		 */
		virtual PropertyValue* optionValue() = 0;
	};
#endif


// bypass mapping of BCV current position as propertyId of exposed type id)
#define BASIC_CONTROL_VALUE_PROPERTY_ID(exposedTypeId) ( 0x7fff0000 + (exposedTypeId))  
#define IS_PROPERTY_ID_BASIC_CONTROL_VALUE(propertyId) ((propertyId) >= 0x7fff0000 && (propertyId)<= 0x7fffffff )
#define EXPOSED_TYPE_ID_FROM_BCV_PROPERTY_ID(propertyId) ( (propertyId)-0x7fff0000)


}//end namespace
#endif

