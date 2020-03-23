// 
// Published Abstract Hardware Model Interfaces and Definitions 
// applying to imaging hardware (image sources)
//
// (c) Leica Microsystems 2002-2015 All Rights Reserved
//

//
//  interfaces and ids for "EVENTS"
// 


#ifndef PUBLIC_AHM_EVENTS_H
#define PUBLIC_AHM_EVENTS_H


#include "ahm.h" // include base defs

namespace ahm {

	/**
	 * Event is the base interface for any event objects.
	 */
	class Event {
	public:
		/**
		 * Retrieve the type of event.
		 */
		virtual iop::int32 eventType() = 0;
	};

	/**
	 * EventSink is the interface implemented on a client to receive events from
	 * ahm units that support events (event sources).
	 */
	class EventSink {
	public:
		/**
		 * Called by an event source to transmit an event to the client.
		 */
		virtual void onEvent(Unit* sender, Event* event) = 0;

		/**
		 * Called by an event source to indicate that it is shutting down.
		 */
		virtual void onShutdown(Unit* sender) = 0;
	};

#ifndef AHM_EVENT_SOURCE_VERSION 
#define AHM_EVENT_SOURCE_VERSION 2
#endif

#if AHM_EVENT_SOURCE_VERSION >=2 
	typedef enum eSubscriptionPreferences {
		SUBSCRIPTION_RECEIVE_ALL = 0,
		SUBSCRIPTION_RECEIVE_NEWEST = 1
	} ESubscriptionPreferences;
#endif

	/**
	 * EventSource is the interface implemented on a unit that can generate asynchronous 
	 * events.
	 */

	class EventSource {
	public:
#if AHM_EVENT_SOURCE_VERSION >= 1
		typedef enum eClassInfo { IID=ahm::IID_EVENT_SOURCE, VERSION=AHM_EVENT_SOURCE_VERSION } EClassInfo;
#endif
		/**
		 * Connect to events.
		 */
		virtual void subscribe(EventSink* subscriber) = 0;

		/**
		 * Disconnect from events.
		 */
		virtual void unsubscribe(EventSink* subscriber) = 0;

#if AHM_EVENT_SOURCE_VERSION >= 2
		// Version 2:
		/*
		 * alternative subscribe method
		 * use one of the Ids from enum ESubscriptionPreferences to define
		 * how events should be received for that subscriber
		 */
		virtual void subscribeWithPreferences(EventSink* subscriber, iop::int32 prefs) = 0;
#endif
	};


	typedef enum eEventType {
		__CORE_EVENT_TYPE_START = 0x10,
		EVENT_CORE_RESERVED = __CORE_EVENT_TYPE_START,
#ifdef AHM_2_0
		EVENT_INTERFACE_STATE_CHANGED,
#endif
		__BASIC_EVENT_TYPE_START		=	__IID_BASIC_START,
		EVENT_VALUE_CHANGED		= __BASIC_EVENT_TYPE_START,  // standard BCV event
		EVENT_PROPERTY_CHANGED,	// property value changed
		EVENT_VALUE_CHANGED_STRING,	// proprietary event for string broadcast
#ifdef AHM_2_0
		EVENT_PROPERTY_INFO_CHANGED,
		EVENT_PROPERTY_ENUM_CHANGED,
#endif
		__BASIC_EVENT_TYPE_MAX
	} EEventType;


// sketch:
	/**
	 * Advanced EventSource telling about the supported events
	 */
	class AdvancedEventSource {
	public:
		typedef enum eClassInfo { IID=ahm::IID_ADVANCED_EVENT_SOURCE } EClassInfo;
		/**
		 * Connect to events.
		 */
		virtual void subscribe(EventSink* pSubscriber, iop::int32 eventType) = 0;

		/**
		 * Disconnect from events.
		 */
		virtual void unsubscribe(EventSink* pSubscriber, iop::int32 eventType) = 0;

		/**
		 * Retrieve the supported Event Types. 
		 */
		virtual IdList * supportedEventTypes() = 0;
	};


	/**
	 * Int Value Event - fired when for example a control value has changed
	 */

	class ValueChangedEvent : public Event {
	public:
		typedef enum eClassInfo { EVENT_TYPE = EVENT_VALUE_CHANGED } EClassInfo;
		virtual iop::int32 interfaceId() = 0;
		virtual iop::int32 value() = 0;
	};

	class ValueChangedStringEvent : public Event {
	public:
		typedef enum eClassInfo { EVENT_TYPE = EVENT_VALUE_CHANGED_STRING } EClassInfo;
		virtual iop::int32 interfaceId() = 0;
		virtual iop::string value() = 0;
	};
#ifdef AHM_2_0
	typedef ValueChangedEvent InterfaceStateChangedEvent;  // value changed has iid and an integer value  - this is the interface state!
#endif


	/**
	 * A disposable EventSink
	 */
	class EventSinkResult
	{
	public:
		/**
		 * Get the EventSink object.
		 * @return a pointer to the EventSink object.
		 */
		virtual EventSink* eventSink() = 0;

		/**
		* Release resources.
		*/
		virtual void dispose() = 0;
	};
	 
}
#endif // PUBLIC_AHM_EVENTS_H
