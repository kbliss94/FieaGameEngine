#pragma once
#include <chrono>
#include <memory>
#include <thread>
#include <future>
#include <vector>
#include "RTTI.h"
#include "Vector.h"
#include "EventSubscriber.h"

using namespace std;

namespace FieaGameEngine
{
	class EventPublisher abstract : public Library::RTTI
	{
		RTTI_DECLARATIONS(EventPublisher, Library::RTTI);
		typedef std::chrono::high_resolution_clock::time_point time_point;
		typedef std::chrono::milliseconds milliseconds;

	public:
		//!Constructor
		/*!
		\param subscribers list of subscribers
		*/
		EventPublisher(Vector<EventSubscriber*>& subscribers, mutex& mutex);

		//!Destructor
		~EventPublisher() = default;

		//!Copy constructor
		EventPublisher(const EventPublisher& rhs);

		//!Assignment operator
		EventPublisher& operator=(const EventPublisher& rhs);

		//!Move constructor
		EventPublisher(EventPublisher&& rhs);

		//!Move assignment operator
		EventPublisher& operator=(EventPublisher&& rhs);

		//!Assigns the given values to mTimeEnqueued & mDelay
		/*!
		\param timeEnqueued the current time passed in that will be assigned to mTimeEnqueued
		\param delay the time delay that will be assigned to mDelay (optional value of 0)
		*/
		void SetTime(time_point& timeEnqueued, milliseconds delay = static_cast<milliseconds>(0));

		//!Returns the time when this event was enqueued
		time_point& TimeEnqueued();

		//!Returns the amount of time after being enqueued that this event expires
		milliseconds& Delay();

		//!Takes the current time & calculates whether the event has expired or not
		/*!
		\return true if the event has expired & false otherwise
		*/
		bool IsExpired(time_point& currentTime);

		//!Notifies all subscribers of this event
		void Deliver();

	protected:
		Vector<EventSubscriber*>* mSubscriberList;
		time_point mTimeEnqueued;
		milliseconds mDelay;
		std::mutex* mMutexPtr;
	};
}

