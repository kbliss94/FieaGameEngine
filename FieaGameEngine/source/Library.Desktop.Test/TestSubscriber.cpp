#include "pch.h"
#include "TestSubscriber.h"

namespace FieaGameEngine
{
	TestSubscriber::TestSubscriber() :
		mEventReceived(false)
	{

	}

	void TestSubscriber::Notify(EventPublisher& event)
	{
		event;
		mEventReceived = true;
	}

	bool TestSubscriber::EventReceived() const
	{
		return mEventReceived;
	}
}