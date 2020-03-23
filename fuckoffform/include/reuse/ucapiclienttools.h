#ifndef UCAPI_CLIENTS_REUSABLE_TOOLS_H
#define UCAPI_CLIENTS_REUSABLE_TOOLS_H

#include <ahm.h>
#include <ahwbasic.h>
#include <ahwevents.h>
#include <ucapi.h>
#include <vector>



#ifndef UCAPI_DRAFT
namespace ucapi {

	class CancellableImageAcquisitionContext : public ucapi::ImageAcquisitionContext {
	public:
		virtual void setCancelled(bool flagCancelled) = 0;
	};


	class CancellableImageAcquisitionContextResult {
	public:
		virtual CancellableImageAcquisitionContext *acquisitionContext() = 0;
		virtual void dispose() = 0;
	};


}
#endif

namespace ucapi_client_tools {


	//////////////////////////////////////////////////////////////////////////////////
	// createSystemMemoryImage
	//
	//	Create an image object in system memory
	//
	// Return:	A pointer to the Image that was created.
	//
	// Remarks:	The caller is responsible for disposing the Image instance 
	//			returned from this method.
	//
	//////////////////////////////////////////////////////////////////////////////////
	ucapi::Image* createSystemMemoryImage(ucapi::ImageFormat *pFormat,  void *pvdata=0);

	//////////////////////////////////////////////////////////////////////////////////
	// createPropertyBag
	//
	//	Create a property an empty property bag.
	//
	// Return:	A pointer to the PropertyBagResult that was created.
	//
	// Remarks:	The caller is responsible for disposing the PropertyBagResult instance 
	//			returned from this method.
	//
	//////////////////////////////////////////////////////////////////////////////////
	ucapi::PropertyBagResult* createPropertyBag();


	//////////////////////////////////////////////////////////////////////////////////
	// createPropertySetting
	//
	//	Create a property setting for the specified property object, with an empty 
	//	value.
	//
	// prop:	The property for which to create a property setting object.
	//
	// Return:	A pointer to the PropertSetting that was created.
	//
	// Remarks:	The caller is responsible for disposing the PropertySetting instance 
	//			returned from this method.
	//
	//////////////////////////////////////////////////////////////////////////////////
	ucapi::PropertySetting* createPropertySetting(ahm::Property *pProperty);

	//////////////////////////////////////////////////////////////////////////////////
	// clonePropertySetting
	//
	//	Create a property setting for the specified property object, and copy the 
	//	current property value into the setting.
	//
	// prop:	The property for which to create a property setting object.
	//
	// Return:	A pointer to the PropertSetting that was created.
	//
	// Remarks:	The caller is responsible for disposing the PropertySetting instance 
	//			returned from this method.
	//
	//////////////////////////////////////////////////////////////////////////////////
	ucapi::PropertySetting* clonePropertySetting(ahm::Property *pProperty);

	/*
	 * create disposable on the fly EventSink implementation
	 */
	typedef void(*FuncOnEventCallback)(ahm::Unit*, ahm::Event*);
	ahm::EventSinkResult* createDelegatingEventSink(FuncOnEventCallback onEventCallback);


	ahm::IdListResult* createIdList(const std::vector<iop::int32>& ids);


	typedef void(*FuncOnImageAcquired)(ucapi::Image* pImage);
	typedef ucapi::Image* (*FuncOnAllocImageBuffer)(ucapi::ImageFormat* pFormat, void *pvData);

	// Attention acq context does not own EventSink!
	ucapi::CancellableImageAcquisitionContextResult * createCancellableAcquisitionContext(FuncOnImageAcquired onImageAcquiredCallback, ahm::EventSink* pEventSink, FuncOnAllocImageBuffer onAllocImageCallback, void *pvdata);

}// end namespace 
#endif

