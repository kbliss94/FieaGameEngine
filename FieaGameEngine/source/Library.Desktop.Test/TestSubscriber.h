#pragma once
#include "EventSubscriber.h"

namespace FieaGameEngine
{
	class TestSubscriber : public EventSubscriber
	{
	public:
		TestSubscriber();
		void Notify(EventPublisher& event);
		bool EventReceived() const;
		~TestSubscriber() = default;

	private:
		bool mEventReceived;
	};
}
