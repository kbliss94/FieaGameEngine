#pragma once
#include "EventPublisher.h"

using namespace std;

namespace FieaGameEngine
{
	template <typename T>
	class Event : public EventPublisher
	{
		RTTI_DECLARATIONS(Event<T>, EventPublisher);

	public:
		//!Constructor
		/*!
		\param message the event payload/information
		*/
		Event(const T& message);

		//!Destructor
		~Event() = default;

		//!Copy constructor
		Event(const Event& rhs);

		//!Assignment operator
		Event& operator=(const Event& rhs);

		//!Move constructor
		Event(Event&& rhs);

		//!Move assignment operator
		Event& operator=(Event&& rhs);

		//!Adds the given subscriber to the list of subscribers for this event type
		static void Subscribe(EventSubscriber& subscriber);

		//! Removes the given subscriber from the list of subscribers for this event type
		static void Unsubscribe(EventSubscriber& subscriber);

		//!Unsubscribes all subscribers to this event type
		static void UnsubscribeAll();

		//!Returns the number of subscribers to this event type
		static std::uint32_t SubscriberAmount();

		//!Returns the message object
		const T& Message() const;

	private:
		T mMessage;
		static Vector<EventSubscriber*> mSubscribers;
		static std::mutex mMutex;
	};
}

#include "Event.inl"
