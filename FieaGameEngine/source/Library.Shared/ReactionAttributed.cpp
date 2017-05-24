#include "pch.h"
#include "ReactionAttributed.h"

namespace FieaGameEngine
{
	ReactionAttributed::ReactionAttributed():
		mSubtype("EventMessage")
	{
		Initialize();
		Event<EventMessage>::Subscribe(*this);
	}

	void ReactionAttributed::Notify(EventPublisher& event)
	{
		Event<EventMessage>* attributedEvent;
		attributedEvent = static_cast<Event<EventMessage>*>(&event);

		if (attributedEvent->Message().GetSubtype() == mSubtype)
		{
			Vector<std::pair<std::string, Datum*>> auxiliaryAtts = attributedEvent->Message().AuxiliaryAttributes();

			for (std::uint32_t i = 0; i < auxiliaryAtts.Size(); ++i)
			{
				AppendAuxiliaryAttribute(auxiliaryAtts[i].first) = *auxiliaryAtts[i].second;
			}

			if (attributedEvent->Message().GetWorld() != nullptr)
			{
				ActionList::Update(*attributedEvent->Message().GetWorld()->GetWorldState());
			}
		}
	}

	void ReactionAttributed::Initialize()
	{
		AddExternalAttribute("Subtype", &mSubtype, sizeof(mSubtype));
	}

	ReactionAttributed::~ReactionAttributed()
	{
		Event<EventMessage>::Unsubscribe(*this);
	}
}