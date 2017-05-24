#include "pch.h"
#include "AsyncTestSubscribers.h"

namespace FieaGameEngine
{
	//ControlSubscriber

	ControlSubscriber::ControlSubscriber() :
		mEventReceived(false), mTimesNotified(0)
	{

	}

	ControlSubscriber::ControlSubscriber(const ControlSubscriber& rhs):
		mEventReceived(rhs.mEventReceived), mTimesNotified(rhs.mEventReceived)
	{

	}

	ControlSubscriber& ControlSubscriber::operator=(const ControlSubscriber& rhs)
	{
		if (this != &rhs)
		{
			mEventReceived = rhs.mEventReceived;
			mTimesNotified = rhs.mTimesNotified;
		}

		return *this;
	}

	void ControlSubscriber::Notify(EventPublisher& event)
	{
		lock_guard<mutex> lock(mMutex);
		event;
		mEventReceived = true;
		++mTimesNotified;
	}

	bool ControlSubscriber::EventReceived() const
	{
		return mEventReceived;
	}

	std::uint32_t ControlSubscriber::TimesNotified() const
	{
		return mTimesNotified;
	}

	//SubscribeSubscriber

	SubscribeSubscriber::SubscribeSubscriber():
		ControlSubscriber(), mCreatedSubscribers()
	{

	}

	SubscribeSubscriber::SubscribeSubscriber(const SubscribeSubscriber& rhs):
		ControlSubscriber(rhs), mCreatedSubscribers(rhs.mCreatedSubscribers)
	{

	}

	SubscribeSubscriber& SubscribeSubscriber::operator=(const SubscribeSubscriber& rhs)
	{
		if (this != &rhs)
		{		
			ControlSubscriber::operator=(rhs);
			mCreatedSubscribers = rhs.mCreatedSubscribers;
		}

		return *this;
	}

	void SubscribeSubscriber::Notify(EventPublisher& event)
	{
		lock_guard<mutex> lock(mMutex);
		mEventReceived = true;
		++mTimesNotified;

		ControlSubscriber* newSubscriber = new ControlSubscriber;
		mCreatedSubscribers.push_back(newSubscriber);
		static_cast<Event<Foo>*>(&event)->Subscribe(*newSubscriber);
	}

	SubscribeSubscriber::~SubscribeSubscriber()
	{
		for (std::uint32_t i = 0; i < mCreatedSubscribers.size(); ++i)
		{
			delete (mCreatedSubscribers[i]);
		}
	}

	//UnsubscribeSubscriber

	UnsubscribeSubscriber::UnsubscribeSubscriber():
		ControlSubscriber()
	{

	}

	UnsubscribeSubscriber::UnsubscribeSubscriber(const UnsubscribeSubscriber& rhs):
		ControlSubscriber(rhs)
	{

	}

	UnsubscribeSubscriber& UnsubscribeSubscriber::operator=(const UnsubscribeSubscriber& rhs)
	{
		if (this != &rhs)
		{
			ControlSubscriber::operator=(rhs);
		}

		return *this;
	}

	void UnsubscribeSubscriber::Notify(EventPublisher& event)
	{
		lock_guard<mutex> lock(mMutex);
		mEventReceived = true;
		++mTimesNotified;

		static_cast<Event<Foo>*>(&event)->Unsubscribe(*this);
	}

	//AddEventSubscriber

	AddEventSubscriber::AddEventSubscriber(EventQueue& queue) :
		ControlSubscriber(), mQueue(&queue)
	{

	}

	AddEventSubscriber::AddEventSubscriber(const AddEventSubscriber& rhs) :
		ControlSubscriber(rhs), mQueue(rhs.mQueue)
	{

	}

	AddEventSubscriber& AddEventSubscriber::operator=(const AddEventSubscriber& rhs)
	{
		if (this != &rhs)
		{
			ControlSubscriber::operator=(rhs);
			mQueue = rhs.mQueue;
		}

		return *this;
	}

	void AddEventSubscriber::Notify(EventPublisher& event)
	{
		lock_guard<mutex> lock(mMutex);
		mEventReceived = true;
		++mTimesNotified;

		event;
		Foo f;
		mQueue->Enqueue(make_shared<Event<Foo>>(f));
	}

	//ExceptionSubscriber

	ExceptionSubscriber::ExceptionSubscriber() :
		ControlSubscriber()
	{

	}

	ExceptionSubscriber::ExceptionSubscriber(const ExceptionSubscriber& rhs) :
		ControlSubscriber(rhs)
	{

	}

	ExceptionSubscriber& ExceptionSubscriber::operator=(const ExceptionSubscriber& rhs)
	{
		if (this != &rhs)
		{
			ControlSubscriber::operator=(rhs);
		}

		return *this;
	}

	void ExceptionSubscriber::Notify(EventPublisher& event)
	{
		lock_guard<mutex> lock(mMutex);
		mEventReceived = true;
		++mTimesNotified;
		event;

		throw std::exception("exception thrown from subscriber");
	}
}
