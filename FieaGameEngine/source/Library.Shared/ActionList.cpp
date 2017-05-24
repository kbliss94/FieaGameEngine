#include "pch.h"
#include "ActionList.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionList)

	ActionList::ActionList()
	{
		Action::Initialize();
		Initialize();
	}

	void ActionList::Update(WorldState& state)
	{
		state.mAction = this;
		Datum& containedActions = (*this)["Actions"];

		for (std::uint32_t i = 0; i < containedActions.Size(); ++i)
		{
			static_cast<Action*>(&(containedActions[i]))->Update(state);
		}
	}

	Action* ActionList::CreateAction(const std::string& className, const std::string& instanceName)
	{
		Action* createdAction = Factory<Action>::Create(className);

		if (createdAction != nullptr)
		{
			createdAction->SetName(instanceName);
			AdoptAction(*createdAction);
		}

		return createdAction;
	}

	void ActionList::AdoptAction(Action& actionToAdopt)
	{
		Adopt(actionToAdopt, "Actions");
	}

	Datum& ActionList::Actions()
	{
		return (*this)["Actions"];
	}

	ActionList::~ActionList()
	{

	}

	void ActionList::Initialize()
	{
		Scope* removeScope = &AddNestedScope("Actions");
		Actions().Remove(removeScope);
		delete removeScope;
	}
}
