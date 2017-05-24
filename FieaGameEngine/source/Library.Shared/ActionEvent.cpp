#include "pch.h"
#include "ActionEvent.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionEvent)

	ActionEvent::ActionEvent():
		mSubtype(), mDelay(0), mMessage()
	{
		Action::Initialize();
		Initialize();
	}

	void ActionEvent::Update(WorldState& state)
	{
		state.mAction = this;
		mMessage.SetWorld(*state.mWorld);
		mMessage.SetSubtype(mSubtype);

		for (std::uint32_t i = 0; i < AuxiliaryAttributes().Size(); ++i)
		{
			mMessage.AppendAuxiliaryAttribute(AuxiliaryAttributes()[i].first) = *AuxiliaryAttributes()[i].second;
		}

		shared_ptr<Event<EventMessage>> createdEvent = make_shared<Event<EventMessage>>(mMessage);
		createdEvent->Delay() = std::chrono::milliseconds(mDelay);
		state.mWorld->GetEventQueue()->Enqueue(createdEvent);
	}

	void ActionEvent::SetSubtype(const std::string subtype)
	{
		mSubtype = subtype;
	}

	void ActionEvent::SetDelay(const std::int32_t delay)
	{
		mDelay = delay;
	}

	std::string ActionEvent::Subtype() const
	{
		return mSubtype;
	}

	std::int32_t ActionEvent::Delay() const
	{
		return mDelay;
	}

	ActionEvent::~ActionEvent()
	{

	}

	void ActionEvent::Initialize()
	{
		AddExternalAttribute("Subtype", &mSubtype, sizeof(mSubtype));
		AddExternalAttribute("Delay", &mDelay, sizeof(mDelay));
	}
}