#include "pch.h"
#include "EventPublisher.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(EventPublisher)
	typedef std::chrono::high_resolution_clock::time_point time_point;
	typedef std::chrono::milliseconds milliseconds;

	EventPublisher::EventPublisher(Vector<EventSubscriber*>& subscribers, mutex& mutex) :
		mSubscriberList(&subscribers), mTimeEnqueued(), mDelay(), mMutexPtr(&mutex)
	{

	}

	EventPublisher::EventPublisher(const EventPublisher& rhs):
		mSubscriberList(rhs.mSubscriberList), mTimeEnqueued(rhs.mTimeEnqueued), mDelay(rhs.mDelay), mMutexPtr(rhs.mMutexPtr)
	{

	}

	EventPublisher& EventPublisher::operator=(const EventPublisher& rhs)
	{
		if (this != &rhs)
		{
			mSubscriberList = rhs.mSubscriberList;
			mTimeEnqueued = rhs.mTimeEnqueued;
			mDelay = rhs.mDelay;
			mMutexPtr = rhs.mMutexPtr;
		}

		return *this;
	}

	EventPublisher::EventPublisher(EventPublisher&& rhs):
		mSubscriberList(rhs.mSubscriberList), mTimeEnqueued(rhs.mTimeEnqueued), mDelay(rhs.mDelay), mMutexPtr(rhs.mMutexPtr)
	{
		rhs.mSubscriberList = nullptr;
		rhs.mTimeEnqueued = time_point();
		rhs.mDelay = milliseconds();
		rhs.mMutexPtr = nullptr;
	}

	EventPublisher& EventPublisher::operator=(EventPublisher&& rhs)
	{
		if (this != &rhs)
		{
			mSubscriberList = rhs.mSubscriberList;
			mTimeEnqueued = rhs.mTimeEnqueued;
			mDelay = rhs.mDelay;
			mMutexPtr = rhs.mMutexPtr;

			rhs.mSubscriberList = nullptr;
			rhs.mTimeEnqueued = time_point();
			rhs.mDelay = milliseconds();
			rhs.mMutexPtr = nullptr;
		}

		return *this;
	}

	void EventPublisher::SetTime(time_point& timeEnqueued, milliseconds delay)
	{
		mTimeEnqueued = timeEnqueued;
		mDelay = delay;
	}

	time_point& EventPublisher::TimeEnqueued()
	{
		return mTimeEnqueued;
	}

	milliseconds& EventPublisher::Delay()
	{
		return mDelay;
	}

	bool EventPublisher::IsExpired(time_point& currentTime)
	{
		return ((mTimeEnqueued + mDelay) <= currentTime);
	}

	void EventPublisher::Deliver()
	{
		mutex subscriberListMutex;
		vector<future<void>> futures;
		Vector<EventSubscriber*> subscribers;

		{
			lock_guard<mutex> lock(subscriberListMutex);

			for (std::uint32_t i = 0; i < mSubscriberList->Size(); ++i)
			{
				subscribers.PushBack((*mSubscriberList)[i]);
			}
		}

		for (auto& subscriber : subscribers)
		{
			futures.emplace_back(async([&]()
			{
				subscriber->Notify(*this);
			}));
		}

		for (auto& f : futures)
		{
			f.get();
		}
	}
}