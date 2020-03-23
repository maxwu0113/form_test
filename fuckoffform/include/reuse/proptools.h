/** 
 ** Copyright (c) 2014 Leica Microsystems - All Rights Reserved
 ** 
 ** Tool functions for AHM properties
 **
 **/

#ifndef AHM_PROPERTIES_TOOLBOX_H
#define AHM_PROPERTIES_TOOLBOX_H
#include "../ahwprop2.h"  // include property definitions
#include <vector>
#include <string>

namespace ahm {
	namespace property_tools {

	/**
	 * set of tool functions for property access
	 * 
     */

	class IValueConversion; // forward

	/**
	 *  get/set a property value by string
	 * returns true when value !=null and value type matches string of can be converted via option conversion object
	 */
	bool getStringValue(ahm::PropertyValue *pValue, std::string &strresult, IValueConversion *pConversion = 0);
	bool setStringValue(ahm::PropertyValue *pValue, const std::string& strval, IValueConversion *pConversion = 0);
	bool getStringValue(ahm::Property *pProperty, std::string &strresult, IValueConversion *pConversion = 0);
	bool setStringValue(ahm::Property *pProperty, const std::string& strvalue, IValueConversion *pConversion = 0);
	bool getStringValue(ahm::Properties* pProperties, iop::int32 id, std::string &strresult, IValueConversion *pConversion = 0);
	bool setStringValue(ahm::Properties* pProperties, iop::int32 id, const std::string& strvalue, IValueConversion *pConversion = 0);

	bool getIntValue(ahm::PropertyValue *pValue, iop::int32& iresult, IValueConversion *pConversion = 0);
	bool setIntValue(ahm::PropertyValue *pValue, iop::int32 ivalue, IValueConversion *pConversion = 0);
	bool getIntValue(ahm::Property *pProperty, iop::int32& iresult, IValueConversion *pConversion = 0);
	bool setIntValue(ahm::Property *pProperty, iop::int32 ivalue, IValueConversion *pConversion = 0);
	bool getIntValue(ahm::Properties* pProperties, iop::int32 id, iop::int32& iresult, IValueConversion *pConversion = 0);
	bool setIntValue(ahm::Properties* pProperties, iop::int32 id, iop::int32 ivalue, IValueConversion *pConversion = 0);

	bool getFloatValue(ahm::PropertyValue *pValue, iop::float64& f64result, IValueConversion *pConversion = 0);
	bool setFloatValue(ahm::PropertyValue *pValue, iop::float64 f64value, IValueConversion *pConversion = 0);
	bool getFloatValue(ahm::Property *pProperty, iop::float64& f64result, IValueConversion *pConversion = 0);
	bool setFloatValue(ahm::Property *pProperty, iop::float64 f64value, IValueConversion *pConversion = 0);
	bool getFloatValue(ahm::Properties* pProperties, iop::int32 id, iop::float64& f64result, IValueConversion *pConversion = 0);
	bool setFloatValue(ahm::Properties* pProperties, iop::int32 id, iop::float64 f64value, IValueConversion *pConversion = 0);

	bool getBoolValue(ahm::PropertyValue *pValue, bool& bresult, IValueConversion *pConversion = 0);
	bool setBoolValue(ahm::PropertyValue *pValue, bool bvalue, IValueConversion *pConversion = 0);
	bool getBoolValue(ahm::Property *pProperty, bool& bresult, IValueConversion *pConversion = 0);
	bool setBoolValue(ahm::Property *pProperty, bool bvalue, IValueConversion *pConversion = 0);
	bool getBoolValue(ahm::Properties* pProperties, iop::int32 id, bool& bresult, IValueConversion *pConversion = 0);
	bool setBoolValue(ahm::Properties* pProperties, iop::int32 id, bool bvalue, IValueConversion *pConversion = 0);

	bool getUnicodeStringValue(ahm::PropertyValue *pValue, std::wstring &wstrresult, IValueConversion *pConversion = 0);
	bool setUnicodeStringValue(ahm::PropertyValue *pValue, const std::wstring& wstrvalue, IValueConversion *pConversion = 0);
	bool getUnicodeStringValue(ahm::Property *pProperty, std::wstring &wstrresult, IValueConversion *pConversion = 0);
	bool setUnicodeStringValue(ahm::Property *pProperty, const std::wstring& wstrvalue, IValueConversion *pConversion = 0);
	bool getUnicodeStringValue(ahm::Properties* pProperties, iop::int32 id, std::wstring &wstrresult, IValueConversion *pConversion = 0);
	bool setUnicodeStringValue(ahm::Properties* pProperties, iop::int32 id, const std::wstring& wstrvalue, IValueConversion *pConversion = 0);

	bool isArray(ahm::PropertyValue* pValue);
	bool isArray(ahm::Property* pProperty);
	
	bool isProperties(ahm::PropertyValue* pValue);
	bool isProperties(ahm::Property* pProperty);

	bool isScalar(ahm::PropertyValue* pValue);
	bool isScalar(ahm::Property* pProperty);

	bool isArray(ahm::PropertyValue* pValue);
	bool isArray(ahm::Property* pProperty);

	bool isProperties(ahm::PropertyValue* pValue);
	bool isProperties(ahm::Property* pProperty);

	bool isScalar(ahm::PropertyValue* pValue);
	bool isScalar(ahm::Property* pProperty);

	bool isRect(ahm::PropertyValue* pValue);
	bool isRect(ahm::Property* pProperty);
	


	// array access
	ahm::PropertyValue* getIndexedValue(ahm::PropertyValue *pValue, iop::int32 index);
	ahm::PropertyValue* getIndexedValue(ahm::Property* pProperty, iop::int32 index);

	ahm::Properties* properties(ahm::PropertyValue* pValue);
	ahm::Properties* properties(ahm::Property* pProperty);
	ahm::Properties* properties(ahm::Unit *pUnit);

	bool isReadable(ahm::Property *pProperty);
	bool isWritable(ahm::Property *pProperty);

	ahm::PropertyInfoEnum* infoEnum(ahm::Property *pProperty);
	ahm::PropertyInfoRange* infoRange(ahm::Property *pProperty);
	ahm::PropertyValue * getEnumValue(ahm::Property *pProperty, iop::int32 index);

	ahm::PropertyInfoRange* infoRange(ahm::Property *pProperty);
	ahm::PropertyValue* minRangeValue(ahm::Property *pProperty);
	ahm::PropertyValue* maxRangeValue(ahm::Property *pProperty);
	ahm::PropertyInfoSteppedRange* infoSteppedRange(ahm::Property *pProperty);
	ahm::PropertyValue* rangeStepSizeValue(ahm::Property *pProperty);


	bool isReadable(ahm::PropertyInfo *pPropertyInfo);
	bool isWritable(ahm::PropertyInfo *pPropertyInfo);

	ahm::PropertyInfoEnum* infoEnum(ahm::PropertyInfo *pPropertyInfo);
	ahm::PropertyInfoRange* infoRange(ahm::PropertyInfo *pPropertyInfo);
	ahm::PropertyValue * getEnumValue(ahm::PropertyInfo *pPropertyInfo, iop::int32 index);
	ahm::PropertyInfoRange* infoRange(ahm::PropertyInfo *pPropertyInfo);
	ahm::PropertyValue* minRangeValue(ahm::PropertyInfo *pPropertyInfo);
	ahm::PropertyValue* maxRangeValue(ahm::PropertyInfo *pPropertyInfo);
	ahm::PropertyInfoSteppedRange* infoSteppedRange(ahm::PropertyInfo *pPropertyInfo);
	ahm::PropertyValue* rangeStepSizeValue(ahm::PropertyInfo *pPropertyInfo);

	void copy_scalar(ahm::PropertyValue *pTarget, ahm::PropertyValue *pSource);
	void copy_rect(ahm::PropertyValue *pTarget, ahm::PropertyValue *pSource);



// interface for optional automatic value conversion
	class IValueConversion {
	public:
		typedef enum eClassInfo { VERSION = 1 } EClassInfo;

		virtual bool convertStringToInt(iop::string strvalue, iop::int32& iresult) = 0;
		virtual bool convertIntToString(iop::int32 ival, std::string & strresult) = 0;

		virtual bool convertStringToBool(iop::string strvalue, bool& bresult) = 0;
		virtual bool convertBoolToString(bool bval, std::string & strresult) = 0;

		virtual bool convertStringToFloat(iop::string strvalue, iop::float64& f64result) = 0;
		virtual bool convertFloatToString(iop::float64 f64val, std::string & strresult) = 0;

		virtual bool convertUnicodeStringToInt(iop::unicode_string strvalue, iop::int32& iresult) = 0;
		virtual bool convertIntToUnicodeString(iop::int32 ival, std::wstring & wstrresult) = 0;

		virtual bool convertUnicodeStringToBool(iop::unicode_string strvalue, bool& bresult) = 0;
		virtual bool convertBoolToUnicodeString(bool bval, std::wstring & wstrresult) = 0;

		virtual bool convertUnicodeStringToFloat(iop::unicode_string strvalue, iop::float64& f64result) = 0;
		virtual bool convertFloatToUnicodeString(iop::float64 f64val, std::wstring & wstrresult) = 0;

		virtual bool convertStringToUnicodeString(iop::string strvalue, std::wstring& wstrresult) = 0;
		virtual bool convertUnicodeStringToString(iop::unicode_string wstrvalue, std::string & strresult) = 0;

        virtual bool convertIntToBool(iop::int32 ival, bool &bresult) = 0;
        virtual bool convertBoolToInt(bool bval, iop::int32 &iresult) = 0;

        virtual bool convertFloatToInt(iop::float64 f64val,  iop::int32 &iresult) = 0;
        virtual bool convertIntToFloat(iop::int32 ival, iop::float64 &f64result) = 0;

		virtual bool convertFloatToBool(iop::float64 f64val, bool &bresult) = 0;
        virtual bool convertBoolToFloat(bool bval, iop::float64 &f64result) = 0;

	};


	extern IValueConversion& _standardConversion; // export standard conversion object 

	extern void __test();

}
}
#endif