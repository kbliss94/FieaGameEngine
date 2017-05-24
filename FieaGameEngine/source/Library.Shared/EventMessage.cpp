#include "pch.h"
#include "EventMessage.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(EventMessage)

	EventMessage::EventMessage():
		Attributed(), mSubtype(), mWorld(nullptr)
	{

	}

	EventMessage::EventMessage(const EventMessage& rhs):
		Attributed(rhs), mSubtype(rhs.mSubtype), mWorld(rhs.mWorld)
	{
		
	}

	EventMessage& EventMessage::operator=(const EventMessage& rhs)
	{
		if (this != &rhs)
		{
			Attributed::operator=(rhs);
			mSubtype = rhs.mSubtype;
			mWorld = rhs.mWorld;
		}

		return *this;
	}

	void EventMessage::SetSubtype(const std::string& subtype)
	{
		mSubtype = subtype;
	}

	const std::string EventMessage::GetSubtype() const
	{
		return mSubtype;
	}

	void EventMessage::SetWorld(World& world)
	{
		mWorld = &world;
	}

	World* EventMessage::GetWorld() const
	{
		return mWorld;
	}
}
