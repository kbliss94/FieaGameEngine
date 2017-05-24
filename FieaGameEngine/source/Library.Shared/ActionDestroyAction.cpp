#include "pch.h"
#include "ActionDestroyAction.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionDestroyAction)

	ActionDestroyAction::ActionDestroyAction():
		mActionToDestroy("")
	{
		Action::Initialize();
		Initialize();
	}

	void ActionDestroyAction::Update(WorldState& state)
	{
		state.mAction = this;
		Datum* actions = GetParent()->Find("Actions");
		
		if (actions != nullptr)
		{
			Action* foundAction = nullptr;

			for (std::uint32_t i = 0; i < actions->Size(); ++i)
			{
				foundAction = static_cast<Action*>(&actions->Get<Scope&>(i));
				if (foundAction != nullptr)
				{
					if (foundAction->Name() == mActionToDestroy)
					{
						state.mWorld->EnqueueActionToDestroy(*foundAction);
						break;
					}
				}
			}
		}
	}

	void ActionDestroyAction::SetActionToDestroy(const std::string actionName)
	{
		mActionToDestroy = actionName;
		Find("ActionToDestroy")->SetStorage(&mActionToDestroy, mActionToDestroy.length());
	}

	std::string ActionDestroyAction::ActionToDestroy() const
	{
		return Find("ActionToDestroy")->Get<std::string&>();
	}

	ActionDestroyAction::~ActionDestroyAction()
	{

	}

	void ActionDestroyAction::Initialize()
	{
		AddExternalAttribute("ActionToDestroy", &mActionToDestroy, sizeof(mActionToDestroy));
	}
}