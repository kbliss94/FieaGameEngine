#pragma once
#include <memory>
#include <thread>
#include <future>
#include <algorithm>
#include "EventPublisher.h"
#include "Event.h"
#include "GameTime.h"
#include "Vector.h"

using namespace std;

namespace FieaGameEngine
{
	class EventQueue
	{
		typedef std::chrono::milliseconds milliseconds;
		typedef Vector<shared_ptr<EventPublisher>>::Iterator IteratorType;
		typedef Vector<shared_ptr<EventPublisher>> VectorType;

	public:
		//!Constructor
		EventQueue();

		//!Enqueues the event using the given information
		/*!
		\param publisher the event that will be added to the queue
		\param time used to get the current GameTime
		*/
		void Enqueue(const shared_ptr<EventPublisher>& event);

		//!Sends the event given immediately
		void Send(EventPublisher& event) const;

		//!Publishes any queued events that have expired
		/*!
		Is called during Game's Update method
		\param time used to check whether the enqueued events have expired or not
		*/
		void Update(const Library::GameTime& time);

		//!Clears the event queue
		void Clear();

		//!Indicates whether or not the event queue is empty
		/*!
		\return returns true if the queue is empty & false otherwise
		*/
		bool IsEmpty() const;

		//!Returns the number of events in the queue
		std::uint32_t Size() const;

	private:
		//!Sorts the event queue so that the unexpired events are at the front and the expired events are at the end
		/*!
		return the index at which the first expired event in the partition is located
		*/
		std::uint32_t SortQueue(const Library::GameTime& time);

		VectorType mQueue;
		std::mutex mMutex;
	};
}
