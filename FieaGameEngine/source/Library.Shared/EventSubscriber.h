#pragma once

namespace FieaGameEngine
{
	class EventPublisher;

	class EventSubscriber abstract
	{
	public:
		virtual void Notify(EventPublisher& event) = 0;
	};
}
