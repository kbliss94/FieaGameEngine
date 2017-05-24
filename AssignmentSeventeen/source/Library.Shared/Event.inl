#pragma once
#include "Event.h"

namespace FieaGameEngine
{
	template <typename T>
	RTTI_DEFINITIONS(Event<T>)

	template <typename T>
	Vector<EventSubscriber*> Event<T>::mSubscribers; 

	template <typename T>
	std::mutex Event<T>::mMutex;

	template <typename T>
	Event<T>::Event(const T& message):
		EventPublisher(mSubscribers, mMutex), mMessage(message)
	{

	}

	template <typename T>
	Event<T>::Event(const Event& rhs):
		EventPublisher(rhs.mSubscribers, rhs.mMutex), mMessage(rhs.mMessage)
	{

	}

	template <typename T>
	Event<T>& Event<T>::operator=(const Event& rhs)
	{
		if (this != &rhs)
		{
			mMessage = rhs.mMessage;
			mSubscribers = rhs.mSubscribers;
			EventPublisher::operator=(rhs);
		}

		return *this;
	}

	template <typename T>
	Event<T>::Event(Event&& rhs):
		mMessage(std::move(rhs.mMessage)), mSubscribers(std::move(rhs.mSubscribers)), EventPublisher(std::move(rhs))
	{
		
	}

	template <typename T>
	Event<T>& Event<T>::operator=(Event&& rhs)
	{
		if (this != &rhs)
		{
			mMessage = std::move(rhs.mMessage);
			mSubscribers = std::move(rhs.mSubscribers);
		}

		return *this;
	}

	template <typename T>
	void Event<T>::Subscribe(EventSubscriber& subscriber)
	{
		lock_guard<mutex> lock(mMutex);
		mSubscribers.PushBack(&subscriber);
	}

	template <typename T>
	void Event<T>::Unsubscribe(EventSubscriber& subscriber)
	{
		lock_guard<mutex> lock(mMutex);
		Vector<EventSubscriber*>::Iterator it = mSubscribers.Find(&subscriber);
		mSubscribers.Remove(it);
	}

	template <typename T>
	void Event<T>::UnsubscribeAll()
	{
		lock_guard<mutex> lock(mMutex);
		mSubscribers.Clear();
		mSubscribers.Reserve(10);
	}

	template <typename T>
	std::uint32_t Event<T>::SubscriberAmount()
	{
		return mSubscribers.Size();
	}

	template <typename T>
	const T& Event<T>::Message() const
	{
		return mMessage;
	}
}
