#include "pch.h"
#include "ActionIf.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionIf)

	ActionIf::ActionIf():
		mCondition(0)
	{
		Action::Initialize();
		Initialize();
	}

	void ActionIf::Update(WorldState& state)
	{
		state.mAction = this;
		Datum* containedActions;

		if (mCondition)
		{
			containedActions = &Then();
		}
		else
		{
			containedActions = &Else();
		}

		for (std::uint32_t i = 0; i < containedActions->Size(); ++i)
		{
			static_cast<Action*>(&(*containedActions)[i])->Update(state);
		}
	}

	std::int32_t ActionIf::Condition() const
	{
		return Find("Condition")->Get<std::int32_t&>();
	}

	void ActionIf::SetCondition(const std::int32_t& condition)
	{
		mCondition = condition;
		Find("Condition")->SetStorage(&mCondition, sizeof(mCondition));
	}

	Datum& ActionIf::Then()
	{
		return (*this)["Then"];
	}
	
	Datum& ActionIf::Else()
	{
		return (*this)["Else"];
	}

	Action* ActionIf::CreateThenAction(const std::string& className, const std::string& instanceName)
	{
		Action* createdAction = Factory<Action>::Create(className);

		if (createdAction != nullptr)
		{
			createdAction->SetName(instanceName);
			Adopt(*createdAction, "Then");
		}

		return createdAction;
	}

	Action* ActionIf::CreateElseAction(const std::string& className, const std::string& instanceName)
	{
		Action* createdAction = Factory<Action>::Create(className);

		if (createdAction != nullptr)
		{
			createdAction->SetName(instanceName);
			Adopt(*createdAction, "Else");
		}

		return createdAction;
	}

	ActionIf::~ActionIf()
	{

	}

	void ActionIf::Initialize()
	{
		AddExternalAttribute("Condition", &mCondition, sizeof(mCondition));

		Scope* removeThenScope = &AddNestedScope("Then");
		Scope* removeElseScope = &AddNestedScope("Else");

		Then().Remove(removeThenScope);
		Else().Remove(removeElseScope);

		delete removeThenScope;
		delete removeElseScope;
	}
}