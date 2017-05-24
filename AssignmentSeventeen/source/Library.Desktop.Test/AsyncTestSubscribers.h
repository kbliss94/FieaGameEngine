#pragma once
#include "EventSubscriber.h"
#include "TestFoo.h"
#include "Event.h"
#include "EventQueue.h"
#include <thread>

namespace FieaGameEngine
{
	//!Subscriber that does nothing for its Notify method
	class ControlSubscriber : public EventSubscriber
	{
	public:
		//!Constructor
		ControlSubscriber();

		//!Copy constructor
		ControlSubscriber(const ControlSubscriber& rhs);

		//!Assignment operator
		ControlSubscriber& operator=(const ControlSubscriber& rhs);

		virtual void Notify(EventPublisher& event);

		//!Returns true if the subscriber has been notified by an event & false otherwise
		bool EventReceived() const;

		//!Returns the number of times that the subscriber has been notified by an event
		std::uint32_t TimesNotified() const;

		virtual ~ControlSubscriber() = default;

	protected:
		bool mEventReceived;
		std::uint32_t mTimesNotified;
		mutex mMutex;
	};

	//!Subscriber that creates a new subscriber and subscribes it to the event param in Notify 
	class SubscribeSubscriber final : public ControlSubscriber
	{
	public:
		//!Constructor
		SubscribeSubscriber();

		//!Copy constructor
		SubscribeSubscriber(const SubscribeSubscriber& rhs);
		
		//!Assignment operator
		SubscribeSubscriber& operator=(const SubscribeSubscriber& rhs);

		//!Creates a new subscriber on the heap & subscribes it to Event<Foo>
		void Notify(EventPublisher& event);

		//!Deletes the subscribers that were allocated on the heap in Notify
		~SubscribeSubscriber();

		vector<ControlSubscriber*> mCreatedSubscribers;
	};

	//!Subscriber that unsubscribes itself from the event param in Notify
	class UnsubscribeSubscriber final : public ControlSubscriber
	{
	public:
		//!Constructor
		UnsubscribeSubscriber();

		//!Copy constructor
		UnsubscribeSubscriber(const UnsubscribeSubscriber& rhs);

		//!Assignment operator
		UnsubscribeSubscriber& operator=(const UnsubscribeSubscriber& rhs);

		//!Unsubscribes *this from the event that was passed in
		void Notify(EventPublisher& event);

		~UnsubscribeSubscriber() = default;
	};

	//!Subscriber that enqueues a new event in Notify
	class AddEventSubscriber final : public ControlSubscriber
	{
	public:
		//!Constructor
		AddEventSubscriber(EventQueue& queue);

		//!Copy constructor
		AddEventSubscriber(const AddEventSubscriber& rhs);

		//!Assignment operator
		AddEventSubscriber& operator=(const AddEventSubscriber& rhs);

		//!Creates and enqueues a new event to the queue that was provided in the constructor
		void Notify(EventPublisher& event);

		~AddEventSubscriber() = default;

	private:
		EventQueue* mQueue;
	};

	//!Subscriber that throws an exception in Notify
	class ExceptionSubscriber final : public ControlSubscriber
	{
	public:
		//!Constructor
		ExceptionSubscriber();

		//!Copy constructor
		ExceptionSubscriber(const ExceptionSubscriber& rhs);

		//!Assignment operator
		ExceptionSubscriber& operator=(const ExceptionSubscriber& rhs);

		//!An exception is thrown ("exception thrown from subscriber")
		void Notify(EventPublisher& event);

		~ExceptionSubscriber() = default;
	};
}