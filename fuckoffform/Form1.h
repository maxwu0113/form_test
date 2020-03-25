#pragma once
#include <iostream>
#include <ahm.h>  // include AHM header
#include <ahm_ext.h>  // include extra headers for theHardwareModelEx
#include <ucapi.h>
#include <vector>
#include <sstream>
#include <reuse/ucapiclienttools.h>
#include <reuse/ahmtools.h>
#include <reuse/proptools.h>
#include <fstream>
#include "stdlib.h"
#include <list>
#include <string>
#include "class.h"

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace ahm;
	using namespace std;

	typedef std::vector<ahm::Unit*> CameraUnits;
	// forward
	void findCameras(Unit* pUnit, CameraUnits& cameraUnits, int depth = 0);
	ahm::Unit* selectCamera(Unit* pRootUnit);
	void workWithCamera(Unit* pCameraUnit);
	void acquireImage(Unit& camera);
	bool getPropertyRange(Unit& pCameraUnit, iop::int32 propertyId, iop::float64& minValue, iop::float64& maxValue);
	bool setPropertyValue(Unit& pCameraUnit, iop::int32 propertyId, iop::float64 value);
	bool getPropertyValue(Unit& pCameraUnit, iop::int32 propertyId, iop::float64& propValue);
	iop::string getUcapiPropertyIdName(iop::int32 propertyId);
	void displayAcquisitionEvent(ahm::Unit* pUnit, ahm::Event* pEvent);
	void displayImageInfo(std::ostream& os, ucapi::Image& image);
	std::string toString(ucapi::ImageFormat* pFormat);
	std::string toString(PropertyValue* pPropertyValue);
	bool getImageInfoPropertyValue(ucapi::Image& image, iop::int32 propertyID, iop::float64 returnValue);
	void prepareContinousAcquire(Unit& camera);
	bool isOptionValueAvailable(Unit& pCameraUnit, iop::int32 propertyId, iop::int32 optionValue);
	bool isPropertyAvailable(Unit& pCameraUnit, iop::int32 propertyId);

	CameraUnits cameralist;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::Button^ Linkbutton;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;

	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->Linkbutton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(75, 54);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 20);
			this->comboBox1->TabIndex = 0;
			// 
			// Linkbutton
			// 
			this->Linkbutton->Location = System::Drawing::Point(96, 150);
			this->Linkbutton->Name = L"Linkbutton";
			this->Linkbutton->Size = System::Drawing::Size(75, 23);
			this->Linkbutton->TabIndex = 1;
			this->Linkbutton->Text = L"Link";
			this->Linkbutton->UseVisualStyleBackColor = true;
			this->Linkbutton->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 240);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(33, 12);
			this->label1->TabIndex = 2;
			this->label1->Text = L"label1";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(242, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(648, 483);
			this->pictureBox1->TabIndex = 3;
			this->pictureBox1->TabStop = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(902, 505);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Linkbutton);
			this->Controls->Add(this->comboBox1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
		HardwareModel* pTheHardwareModel = 0;
		if (!pTheHardwareModel)
		{
			pTheHardwareModel = theHardwareModelEx(
#ifdef _WIN64
				"C:\\Users\\EXOSOME\\source\\repos\\form_test\\fuckoffform\\bin64"
#else
				"C:\\Users\\EXOSOME\\source\\repos\\form_test\\fuckoffform\\bin"
#endif
			);
		}
		if (pTheHardwareModel)
		{
			Unit* pRootUnit = pTheHardwareModel->getUnit("");
			CameraUnits cameraUnits;
			findCameras(pRootUnit, cameraUnits);
			cameralist = cameraUnits;
			int selIndex = 0;
			if (cameraUnits.size() > 1)
			{
				do
				{
					for (int i = 0; i < (int)cameraUnits.size(); i++)
					{
						string name = cameraUnits[i]->name();
						String^ Sname = gcnew String(name.c_str());
						comboBox1->Items->Add(gcnew MyItem(Sname, i));
					}

				} while (selIndex >= (int)cameraUnits.size() || selIndex < 0);
			}
		}
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		int cameranum;
		cameranum = ((MyItem^)comboBox1->SelectedItem)->readvalue();
		Unit* ucamera = cameralist[cameranum];
		if (ucamera)
		{
			label1->Text = "try to connect";
			if (!ucamera->initState())
			{
				label1->Text = "camera is not intializde! try to initializing";
				ucamera->init();
				if (ucamera->initState())
				{
					label1->Text = "camera is ok";
				}
				else
				{
					label1->Text = "still NOT initialized";
				}
				prepareContinousAcquire(*ucamera);
				//acquireImage(*ucamera);
			}
		}
	}
private: System::Void Form1_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {

}
};
	void findCameras(Unit* pUnit, CameraUnits& camerasFound, int depth)
	{
		if (pUnit)
		{
			if (pUnit->type())
			{
				if (pUnit->type()->isA(ucapi::UCAPI_CAMERA))
				{
					camerasFound.push_back(pUnit);
				}
			}
			if (pUnit->units())
			{
				for (iop::int32 i = 0; i < pUnit->units()->numUnits(); i++)
				{
					findCameras(pUnit->units()->getUnit(i), camerasFound, depth + 1);
				}
			}
		}
	}
	ahm::Unit* selectCamera(Unit* pUnit) {
		CameraUnits cameraUnits;
		findCameras(pUnit, cameraUnits);

		int selIndex = 0;

		if (cameraUnits.size() > 1) {

			do {
				cout << endl;
				for (int i = 0; i < (int)cameraUnits.size(); i++) {
					cout << "[" << i << "] " << cameraUnits[i]->name() << endl;
				}
				cout << "Select Camera: ";
				{
					char szbuf[128]; cin.getline(szbuf, sizeof(szbuf));
					if (tolower(szbuf[0]) == 'q') { // quit
						return 0;
					}
					selIndex = atoi(szbuf);
				}
			} while (selIndex >= (int)cameraUnits.size() || selIndex < 0);
		}

		if (selIndex >= 0 && selIndex < (int)cameraUnits.size()) {
			return cameraUnits[selIndex];
		}
		return 0;
	}
	void acquireImage(Unit& camera)
	{
		try {
			// Get the acquisition interfaces from the camera
			ucapi::ImageAcquisition* pImageAcquisition = find_valid_itf<ucapi::ImageAcquisition>(&camera, ucapi::ImageAcquisition::IID);
			if (!pImageAcquisition) {
				cout << "cannot acquire image - image acquisition interface not available!" << endl;
				return;
			}
			ucapi::AcquisitionInformation* pAcquisitionInfo = find_valid_itf<ucapi::AcquisitionInformation>(&camera, ucapi::AcquisitionInformation::IID);
			if (!pAcquisitionInfo)
			{
				cout << "cannot acquire image - image acquisition information interface not available!" << endl;
				return;
			}
			// Request exposure time values to be included in the image info
			std::vector<iop::int32> vids;
			vids.push_back(ucapi::PROP_EXPOSURE_TIME);

			// Request image index to be added to the image if supported
			if (pAcquisitionInfo->getValidImageInfoIds()->findId(ucapi::IPROP_IMAGE_SEQUENCE_INDEX) >= 0)
			{
				vids.push_back(ucapi::IPROP_IMAGE_SEQUENCE_INDEX);
			}


			ahm::IdListResult* pInfoIds = ucapi_client_tools::createIdList(vids);

			ahm::EventSinkResult* pAcqEventSink = ucapi_client_tools::createDelegatingEventSink(displayAcquisitionEvent);

			// the acquisition context manages the buffer allocation strategies
			static ucapi::CancellableImageAcquisitionContext* pCancelling = nullptr; // future
			static iop::int32 nImageCount = 0;

			ucapi::CancellableImageAcquisitionContextResult* pAcquisitionContextObject = ucapi_client_tools::createCancellableAcquisitionContext(
				[](ucapi::Image* pImage) {
					if (pImage)
						displayImageInfo(std::cout, *pImage);
					iop::float64 imageIndex = 0;

					//Get image sequence index if not available use fall back image increment
					if (getImageInfoPropertyValue(*pImage, ucapi::IPROP_IMAGE_SEQUENCE_INDEX, imageIndex))
					{
						nImageCount = (iop::int32)imageIndex;
					}
					else
					{
						nImageCount++;
					}

					//stop acquisition after 10 images
					if (pCancelling != nullptr && nImageCount > 10) {
						//pCancelling->setCancelled(true); //¨ú®ø
					}

					pImage->dispose();

				},
				pAcqEventSink->eventSink(), ucapi_client_tools::createSystemMemoryImage, nullptr

					);

			pCancelling = pAcquisitionContextObject->acquisitionContext();

			ucapi::ImageFormatResult* pImageFormat = pAcquisitionInfo->getImageFormat(0);
			if (pImageFormat && pImageFormat->format()) {
				cout << "current image format: " << toString(pImageFormat->format()).c_str() << endl;
				pImageFormat->dispose();
			}
			cout << "acquiring image.." << endl;

			//start continuous acquisition
			pImageAcquisition->acquireContinuous(pAcquisitionContextObject->acquisitionContext(), pInfoIds->idList());


			pAcquisitionContextObject->dispose();
			pInfoIds->dispose(); // no longer needed
		}
		catch (ahm::Exception & ex) {
			std::cout << "a hardware model exception occurred: error code: " << ex.errorClass() << ", error code: " << ex.errorCode() << ", text: " << ex.errorText() << endl; \
		}
	}

	void workWithCamera(Unit* pCameraUnit) {
		if (pCameraUnit) {
			cout << "using camera: " << pCameraUnit->name() << ".." << endl;

			// initialize camera
			if (!pCameraUnit->initState()) {
				cout << "camera is not intialized! - initializing..";
				pCameraUnit->init();
				cout << "camera is now " << (pCameraUnit->initState() ? "" : "still NOT ") << "initialized!" << endl;
			}

			//prepare for acquiring a fast live image
			prepareContinousAcquire(*pCameraUnit);

			// acquire (grab) an image
			acquireImage(*pCameraUnit);

			// get/set exposure time and color saturation via property tools
			iop::float64 minExposure = 0.0, maxExposure = 0.0, curExposure = 0.0;
			iop::int32 propertyId = ucapi::PROP_EXPOSURE_TIME;
			getPropertyRange(*pCameraUnit, propertyId, minExposure, maxExposure);
			// change exposure time to minimum
			setPropertyValue(*pCameraUnit, propertyId, minExposure);
			// get current exposure time
			getPropertyValue(*pCameraUnit, propertyId, curExposure);
			cout << "Exposure time (id:" << propertyId << ") minimum: " << minExposure << " seconds, maximum: " << maxExposure << " seconds, current: " << curExposure << " seconds" << endl;

			propertyId = ucapi::PROP_COLOUR_SATURATION;
			iop::float64 minSaturation = 0.0, maxSaturation = 0.0, curSaturation = 0.0;
			getPropertyRange(*pCameraUnit, propertyId, minSaturation, maxSaturation);
			// change saturation to minimum
			setPropertyValue(*pCameraUnit, propertyId, minSaturation);
			// get current saturation
			getPropertyValue(*pCameraUnit, propertyId, curSaturation);
			cout << "Colour Saturation (id:" << propertyId << ") minimum: " << minSaturation << " maximum: " << maxSaturation << " current: " << curSaturation << endl;
		}
	}

	void prepareContinousAcquire(Unit& camera)
	{
		bool bRet = false;
		iop::int32 valueBinning = ucapi::BINNING_LEVEL_NONE;
		iop::int32 valueStreamingFormatID = 0;
		iop::int32 valueAcquisitionMode = 0;
		iop::float64 valueTriggerMode = 0;

		//deactivate auto brightness if enabled
		bRet = isPropertyAvailable(camera, ucapi::PROP_AUTO_BRIGHTNESS_ENABLED);
		if (bRet)
		{
			iop::float64 fValue = 0;
			getPropertyValue(camera, ucapi::PROP_AUTO_BRIGHTNESS_ENABLED, fValue);
			if (fValue == 1)
			{
				setPropertyValue(camera, ucapi::PROP_AUTO_BRIGHTNESS_ENABLED, false);
			}
		}

		//if camera supports binning or streaming/capture modes
		bRet = isPropertyAvailable(camera, ucapi::PROP_BINNING_LEVEL);
		if (bRet)
		{
			if (isOptionValueAvailable(camera, ucapi::PROP_BINNING_LEVEL, ucapi::BINNING_LEVEL_NONE))
			{
				setPropertyValue(camera, ucapi::PROP_BINNING_LEVEL, ucapi::BINNING_LEVEL_NONE);
			}
		}
		else
		{
			bRet = isPropertyAvailable(camera, ucapi::PROP_STREAMING_FORMAT_ID);
			bRet = bRet && isPropertyAvailable(camera, ucapi::PROP_ACQUISITION_MODE);
			//Set camera to streaming mode
			if (bRet)
			{
				if (isOptionValueAvailable(camera, ucapi::PROP_ACQUISITION_MODE, ucapi::ACQUISITION_MODE_STREAMING))
				{
					setPropertyValue(camera, ucapi::PROP_ACQUISITION_MODE, ucapi::ACQUISITION_MODE_STREAMING);
				}
			}
		}


		bRet = isPropertyAvailable(camera, ucapi::PROP_IMAGE_TRIGGER_MODE);
		//set camera to internal trigger mode
		if (bRet)
		{
			if (isOptionValueAvailable(camera, ucapi::PROP_IMAGE_TRIGGER_MODE, ucapi::IMAGE_TRIGGER_MODE_CONTINUOUS))
			{
				setPropertyValue(camera, ucapi::PROP_IMAGE_TRIGGER_MODE, ucapi::IMAGE_TRIGGER_MODE_CONTINUOUS);
			}
		}

	}

	// display image acquisition events
	void displayAcquisitionEvent(ahm::Unit* pUnit, ahm::Event* pEvent)
	{
		std::ostream& os = cout;
		os << "Unit" << pUnit->name() << " -> ";
		switch (pEvent->eventType())
		{
		case ucapi::IAEV_EXPOSURE_STARTED:
			os << "Exposure started.";
			break;

		case ucapi::IAEV_EXPOSURE_COMPLETE:
			os << "Exposure complete.";
			break;

		case ucapi::IAEV_READOUT_COMPLETE:
			os << "Readout complete.";
			break;

		default:
			os << "Unrecognised acquisition event";
			break;
		}
		os << endl;
	}

	// display the settings of a given pixel format
	std::string pixelFormatToString(iop::int32 pixelFormat)
	{
		std::ostringstream os;
		switch (pixelFormat)
		{
		case ucapi::PIXEL_FORMAT_RGB24:
			os << "RGB24";
			break;
		case ucapi::PIXEL_FORMAT_BGR24:
			os << "BGR24";
			break;
		case ucapi::PIXEL_FORMAT_RGB48:
			os << "RGB48";
			break;
		case ucapi::PIXEL_FORMAT_BGR48:
			os << "BGR48";
			break;
		case ucapi::PIXEL_FORMAT_MONO8:
			os << "MONO8";
			break;
		case ucapi::PIXEL_FORMAT_MONO16:
			os << "MONO16";
			break;
		default:
			os << "Custom [" << pixelFormat << "]";
		}
		return os.str();
	}

	// display the settings of a given image format
	std::string toString(ucapi::ImageFormat* pFormat)
	{
		if (pFormat) {
			ucapi::ImageFormat& format = *pFormat;
			std::ostringstream os;
			os << format.width() << "x" << format.height() << " (" << pixelFormatToString(format.pixelFormat()).c_str() << ")";
			return os.str();
		}
		return "NULL";
	}

	// display the image infos which are delivered with the image property bag
	void displayImageInfo(std::ostream& os, ucapi::Image& image)
	{
		os << "Received image OK - Image format: " << toString(image.imageFormat()).c_str();

		os << " - Image settings (property bag):" << endl;
		// Iterate over the settings stored in the image's property bag...
		for (auto i = 0; i < image.imageInfo()->numSettings(); i++)
		{
			os << "    [" << i << "] ";
			iop::int32 id = image.imageInfo()->getId(i);
			PropertyValue* pValue = image.imageInfo()->findSetting(id);
			os << "id: " << id << "\t" << getUcapiPropertyIdName(id) << "    value: " << toString(pValue).c_str() << endl;
		}
	}

	// get the property value from the image property bag
	bool getImageInfoPropertyValue(ucapi::Image& image, iop::int32 propertyID, iop::float64 returnValue)
	{
		bool bRet = false;
		if (image.imageInfo() != nullptr)
		{
			PropertyValue* pValue = image.imageInfo()->findSetting(propertyID);
			if (pValue != nullptr)
			{
				bRet = property_tools::getFloatValue(pValue, returnValue, &property_tools::_standardConversion);
			}
		}

		return bRet;
	}

	// additional property tools for float and range properties

	bool getPropertyRange(Unit& pCameraUnit, iop::int32 propertyId, iop::float64& minValue, iop::float64& maxValue)
	{
		//Get properties interface
		ahm::Properties* pCameraProperties = find_valid_itf<ahm::Properties>(&pCameraUnit, ahm::Properties::IID);
		if (pCameraProperties)
		{
			//get property
			ahm::Property* pProperty = pCameraProperties->findProperty(propertyId);
			if (pProperty)
			{
				//check info type before query min/max value
				ahm::PropertyInfo::ePropertyInfoType propertyInfoType = ahm::PropertyInfo::ePropertyInfoType(pProperty->getPropertyInfo()->derivedType());

				if (property_tools::infoRange(pProperty)) {
					return property_tools::getFloatValue(property_tools::minRangeValue(pProperty), minValue, &property_tools::_standardConversion)
						&& property_tools::getFloatValue(property_tools::maxRangeValue(pProperty), maxValue, &property_tools::_standardConversion);
				}
				else if (property_tools::infoEnum(pProperty) != nullptr) {
					ahm::PropertyInfoEnum* pInfoEnum = property_tools::infoEnum(pProperty);
					if (pInfoEnum->numOptions() > 0)
					{
						// min is first and max is last in enumeration
						return property_tools::getFloatValue(pInfoEnum->getOption(0), minValue, &property_tools::_standardConversion)
							&& property_tools::getFloatValue(pInfoEnum->getOption(pInfoEnum->numOptions() - 1), maxValue, &property_tools::_standardConversion);
					}
				}
			}
		}
		return false;
	}

	bool setPropertyValue(Unit& pCameraUnit, iop::int32 propertyId, iop::float64 value)
	{
		//Get properties interface
		ahm::Properties* pCameraProperties = find_valid_itf<ahm::Properties>(&pCameraUnit, ahm::Properties::IID);
		if (pCameraProperties)
		{
			//get property and check if writable
			ahm::Property* pProperty = pCameraProperties->findProperty(propertyId);
			if (pProperty && property_tools::isWritable(pProperty))
			{
				//check info type before set value
				ahm::PropertyInfo::ePropertyInfoType propertyInfoType = ahm::PropertyInfo::ePropertyInfoType(pProperty->getPropertyInfo()->derivedType());

				if (property_tools::infoRange(pProperty) != 0) {
					return property_tools::setFloatValue(pProperty, value, &property_tools::_standardConversion);
				}
				else if (property_tools::infoEnum(pProperty) != 0) {
					iop::int32 maxPropertyIndex = property_tools::infoEnum(pProperty)->numOptions();
					// search for value in property enumeration
					for (iop::int32 i = 0; i < maxPropertyIndex; i++)
					{
						iop::float64 testValue = 0;

						//get value from current property index
						if (property_tools::getFloatValue(property_tools::getEnumValue(pProperty, i), testValue, &property_tools::_standardConversion)

							&& testValue == value)// Warning double - compare - matches the exact value!
						{
							return property_tools::setIntValue(pProperty, i);
						}
					}
				}
				else if (pProperty->value()->derivedType() == ahm::PropertyValue::TYPE_BOOL)
				{
					bool bValue = value == 0 ? false : true;
					return property_tools::setBoolValue(pProperty, bValue, &property_tools::_standardConversion);
				}
			}
		}
		return false;
	}

	bool getPropertyValue(Unit& pCameraUnit, iop::int32 propertyId, iop::float64& propValue)
	{
		//get properties interface
		ahm::Properties* pCameraProperties = find_valid_itf<ahm::Properties>(&pCameraUnit, ahm::Properties::IID);
		if (pCameraProperties)
		{
			//get property and check if readable
			ahm::Property* pProperty = pCameraProperties->findProperty(propertyId);
			if (pProperty && property_tools::isReadable(pProperty))
			{
				//check info type before get value
				ahm::PropertyInfo::ePropertyInfoType propertyInfoType = ahm::PropertyInfo::ePropertyInfoType(pProperty->getPropertyInfo()->derivedType());

				if (property_tools::infoRange(pProperty)) {
					return property_tools::getFloatValue(pProperty, propValue, &property_tools::_standardConversion);
				}
				else if (property_tools::infoEnum(pProperty)) {
					//get current index and return value for that index
					iop::int32 propertyIndex = 0;
					return property_tools::getIntValue(pProperty, propertyIndex)
						&& property_tools::getFloatValue(property_tools::getEnumValue(pProperty, propertyIndex), propValue, &property_tools::_standardConversion);
				}
				else if (pProperty->value()->derivedType() == ahm::PropertyValue::TYPE_BOOL)
				{
					bool bRet = false;
					bool bValue = false;
					bRet = property_tools::getBoolValue(pProperty, bValue, &property_tools::_standardConversion);
					propValue = bValue;
					return bRet;
				}
			}
		}
		return false;
	}

	bool isPropertyAvailable(Unit& pCameraUnit, iop::int32 propertyId)
	{
		bool bRet = false;
		ahm::Properties* pCameraProperties = find_valid_itf<ahm::Properties>(&pCameraUnit, ahm::Properties::IID);
		if (pCameraProperties)
		{
			//get property and check if available
			ahm::Property* pProperty = pCameraProperties->findProperty(propertyId);
			if (pProperty)
			{
				bRet = true;
			}
		}
		return bRet;
	}

	bool isOptionValueAvailable(Unit& pCameraUnit, iop::int32 propertyId, iop::int32 optionValue)
	{
		bool bRet = false;

		ahm::Properties* pCameraProperties = find_valid_itf<ahm::Properties>(&pCameraUnit, ahm::Properties::IID);
		if (pCameraProperties)
		{
			//get property and check if available
			ahm::Property* pProperty = pCameraProperties->findProperty(propertyId);
			if (pProperty)
			{
				//if info from type enum
				if (pProperty && pProperty->getPropertyInfo()->derivedType() == ahm::PropertyInfo::TYPE_ENUMERATION)
				{
					ahm::PropertyInfoEnum* pPropInfoEnum = (ahm::PropertyInfoEnum*)pProperty->getPropertyInfo();
					//check if option value is in property info enumeration
					for (iop::int32 i = 0; i < pPropInfoEnum->numOptions(); i++)
					{
						ahm::PropertyValue* pPropValue = pPropInfoEnum->getOption(i);
						if (pPropValue->derivedType() == ahm::PropertyValue::TYPE_INT)
						{
							ahm::PropertyValueInt* pPropValueInt = (PropertyValueInt*)pPropInfoEnum->getOption(i);
							if (pPropValueInt->getValue() == optionValue)
							{
								return true;
							}
						}
					}
				}
			}
		}
		return bRet;
	}

	//Get value from a given PropertyValue.
	std::string toString(PropertyValue* pPropertyValue)
	{
		std::string strResult;
		if (pPropertyValue != nullptr)
		{
			property_tools::getStringValue(pPropertyValue, strResult, &property_tools::_standardConversion);

			if (pPropertyValue->derivedType() == ahm::PropertyValue::TYPE_INDEX)
			{
				strResult.insert(0, "index[");
				strResult.append("]");
			}
			else if (pPropertyValue->derivedType() == ahm::PropertyValue::TYPE_INT_RECT)
			{
				ahm::INT_RECT rect = ((ahm::PropertyValueIntRect*)pPropertyValue)->getValue();
				std::ostringstream os;
				os << "rectangle: top: " << rect.top << " left: " << rect.left << " height: " << rect.height << " width: " << rect.width;
				strResult = os.str();
			}
		}
		return strResult;
	}
	iop::string getUcapiPropertyIdName(iop::int32 propertyId) {
		switch (propertyId) {
#define DISPATCH_UCAPI_PROPERTY_ID(id) case (ucapi::##id): return #id;
			DISPATCH_UCAPI_PROPERTY_ID(PROP_SERIAL_NUMBER) DISPATCH_UCAPI_PROPERTY_ID(PROP_FIRMWARE_HEAD_VERSION) DISPATCH_UCAPI_PROPERTY_ID(PROP_VERSION_INFO)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_SENSOR_XRESOLUTION) DISPATCH_UCAPI_PROPERTY_ID(PROP_SENSOR_YRESOLUTION) DISPATCH_UCAPI_PROPERTY_ID(PROP_PHYSICAL_PIXEL_XSIZE)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_PHYSICAL_PIXEL_YSIZE) DISPATCH_UCAPI_PROPERTY_ID(PROP_LOGICAL_XRESOLUTION) DISPATCH_UCAPI_PROPERTY_ID(PROP_LOGICAL_YRESOLUTION)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_LOGICAL_CENTRE_XOFFSET) DISPATCH_UCAPI_PROPERTY_ID(PROP_LOGICAL_CENTRE_YOFFSET) DISPATCH_UCAPI_PROPERTY_ID(PROP_LOGICAL_PIXEL_XSIZE)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_LOGICAL_PIXEL_YSIZE) DISPATCH_UCAPI_PROPERTY_ID(PROP_IMAGE_TRIGGER_MODE) DISPATCH_UCAPI_PROPERTY_ID(PROP_TRIGGER_POLARITY)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_EXPOSURE_TIME) DISPATCH_UCAPI_PROPERTY_ID(PROP_EMGAIN) DISPATCH_UCAPI_PROPERTY_ID(PROP_GAIN) DISPATCH_UCAPI_PROPERTY_ID(PROP_GAIN_RED)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_GAIN_GREEN) DISPATCH_UCAPI_PROPERTY_ID(PROP_GAIN_BLUE) DISPATCH_UCAPI_PROPERTY_ID(PROP_AUTO_BRIGHTNESS_ENABLED) DISPATCH_UCAPI_PROPERTY_ID(PROP_AUTO_BRIGHTNESS_LEVEL)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_AUTO_BRIGHTNESS_ROI) DISPATCH_UCAPI_PROPERTY_ID(PROP_AUTO_BRIGHTNESS_ROI_ENABLED) DISPATCH_UCAPI_PROPERTY_ID(PROP_COLOUR_SATURATION) DISPATCH_UCAPI_PROPERTY_ID(PROP_BINNING_LEVEL)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_BINNED_BRIGHTNESS_CORRECTION_ENABLED) DISPATCH_UCAPI_PROPERTY_ID(PROP_READOUT_SPEED) DISPATCH_UCAPI_PROPERTY_ID(PROP_PIXEL_DEPTH)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_PIXEL_TYPE) DISPATCH_UCAPI_PROPERTY_ID(PROP_READOUT_REGION) DISPATCH_UCAPI_PROPERTY_ID(PROP_READOUT_REGIONS) DISPATCH_UCAPI_PROPERTY_ID(PROP_GAMMA_LEVEL)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_BLACK_LEVEL) DISPATCH_UCAPI_PROPERTY_ID(PROP_WHITE_LEVEL) DISPATCH_UCAPI_PROPERTY_ID(PROP_AUTO_GAMMA_LEVEL_ENABLED) DISPATCH_UCAPI_PROPERTY_ID(PROP_AUTO_BLACK_LEVEL_ENABLED)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_AUTO_WHITE_LEVEL_ENABLED) DISPATCH_UCAPI_PROPERTY_ID(PROP_SHARPENING_LEVEL)	DISPATCH_UCAPI_PROPERTY_ID(PROP_XMIRRORING_ENABLED) DISPATCH_UCAPI_PROPERTY_ID(PROP_YMIRRORING_ENABLED)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_IMAGE_AVERAGING_MODE) DISPATCH_UCAPI_PROPERTY_ID(PROP_IMAGE_AVERAGING_COUNT) DISPATCH_UCAPI_PROPERTY_ID(PROP_CAPTURE_FORMAT_ID) DISPATCH_UCAPI_PROPERTY_ID(PROP_STREAMING_FORMAT_ID)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_ACQUISITION_MODE) DISPATCH_UCAPI_PROPERTY_ID(PROP_FAN_SPEED_LEVEL) DISPATCH_UCAPI_PROPERTY_ID(PROP_CONTINUOUS_WHITE_BALANCE_ENABLED)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_CONTINUOUS_WHITE_BALANCE_ROI) DISPATCH_UCAPI_PROPERTY_ID(PROP_CONTINUOUS_WHITE_BALANCE_ROI_ENABLED) DISPATCH_UCAPI_PROPERTY_ID(PROP_FOCUS_SCORE_ROI)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_FOCUS_SCORE_ROI_ENABLED) DISPATCH_UCAPI_PROPERTY_ID(PROP_WHITE_SHADING_REFERENCE_FILE) DISPATCH_UCAPI_PROPERTY_ID(PROP_WHITE_SHADING_CORRECTION_ENABLED)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_SATURATION_CORRECTION) DISPATCH_UCAPI_PROPERTY_ID(PROP_HUE_CORRECTION) DISPATCH_UCAPI_PROPERTY_ID(PROP_AVERAGE_COLOUR_ROI)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_AVERAGE_COLOUR_ROI_ENABLED)	DISPATCH_UCAPI_PROPERTY_ID(PROP_PSEUDO_COLOUR_WAVELENGTH) DISPATCH_UCAPI_PROPERTY_ID(PROP_BLACK_BALANCE_LEVEL)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_BLACK_BALANCE_ENABLED) DISPATCH_UCAPI_PROPERTY_ID(PROP_ACQUISITION_TIMEOUT) DISPATCH_UCAPI_PROPERTY_ID(PROP_AUTO_ACQUISITION_TIMEOUT_ENABLED)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_TEMPERATURE) DISPATCH_UCAPI_PROPERTY_ID(PROP_TARGET_TEMPERATURE) DISPATCH_UCAPI_PROPERTY_ID(PROP_FAN_SPEED) DISPATCH_UCAPI_PROPERTY_ID(PROP_MIN_TRIGGER_INTERVAL)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_IMAGE_READOUT_TIME) DISPATCH_UCAPI_PROPERTY_ID(PROP_NIR_MODE_ENABLED) DISPATCH_UCAPI_PROPERTY_ID(PROP_CAMERA_SDK_VERSION) DISPATCH_UCAPI_PROPERTY_ID(PROP_READOUT_OVERLAP_ENABLED)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_EMCCD_MODE) DISPATCH_UCAPI_PROPERTY_ID(PROP_HOTPIXEL_EXPOSURE_THRESHOLD) DISPATCH_UCAPI_PROPERTY_ID(PROP_HOTPIXEL_INTENSITY_THRESHOLD)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_MICROSCANNING_MODE) DISPATCH_UCAPI_PROPERTY_ID(PROP_VERTICAL_SHIFT_TIME) DISPATCH_UCAPI_PROPERTY_ID(PROP_VERTICAL_SHIFT_VOLTAGE_OFFSET)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_COLOUR_TEMPERATURE) DISPATCH_UCAPI_PROPERTY_ID(PROP_NOISE_REDUCTION_LEVEL) DISPATCH_UCAPI_PROPERTY_ID(PROP_NOISE_REDUCTION_ENABLED)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_MICRO_SCANNING_SHARPENING_LEVEL) DISPATCH_UCAPI_PROPERTY_ID(PROP_MICRO_SCANNING_SHARPENING_ENABLED) DISPATCH_UCAPI_PROPERTY_ID(PROP_BLACK_LOCK_THRESHOLD)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_BLACK_LOCK_ENABLED) DISPATCH_UCAPI_PROPERTY_ID(PROP_WHITE_LOCK_THRESHOLD) DISPATCH_UCAPI_PROPERTY_ID(PROP_WHITE_LOCK_ENABLED) DISPATCH_UCAPI_PROPERTY_ID(PROP_ELECTRONCOUNT_SCALING)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_EMCCD_NOISE_REDUCTION_THRESHOLD) DISPATCH_UCAPI_PROPERTY_ID(PROP_EMCCD_NOISE_REDUCTION_ENABLED) DISPATCH_UCAPI_PROPERTY_ID(PROP_ENHANCED_ACQUISITION_MODE) 	DISPATCH_UCAPI_PROPERTY_ID(PROP_HDR_MODE)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_HDR_CONTRAST) DISPATCH_UCAPI_PROPERTY_ID(PROP_TEMPERATURE_PELTIER_ENABLED) DISPATCH_UCAPI_PROPERTY_ID(PROP_MULTI_TAP_READOUT_ENABLED)
				DISPATCH_UCAPI_PROPERTY_ID(PROP_MULTI_TAP_READOUT_SELECTOR) DISPATCH_UCAPI_PROPERTY_ID(PROP_HDR_BRIGHTNESS)
				DISPATCH_UCAPI_PROPERTY_ID(IPROP_IMAGE_VALIDATION_STATE) DISPATCH_UCAPI_PROPERTY_ID(IPROP_IMAGE_SEQUENCE_INDEX) DISPATCH_UCAPI_PROPERTY_ID(PROP_DISPLAY_NAME) DISPATCH_UCAPI_PROPERTY_ID(PROP_PIXEL_ALIGNMENT) DISPATCH_UCAPI_PROPERTY_ID(PROP_DECIMATION_MODE)
		default: return "???";
		}
	}
}
