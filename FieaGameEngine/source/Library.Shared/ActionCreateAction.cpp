#include "pch.h"
#include "ActionCreateAction.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionCreateAction)

	ActionCreateAction::ActionCreateAction():
		mPrototypeClassName(""), mPrototypeInstanceName("")
	{
		Action::Initialize();
		Initialize();
	}

	void ActionCreateAction::Update(WorldState& state)
	{
		state.mAction = this;
		Action* createdAction = Factory<Action>::Create(mPrototypeClassName);

		if (createdAction != nullptr)
		{
			createdAction->SetName(mPrototypeInstanceName);
			GetParent()->Adopt(*createdAction, "Actions");
		}
	}

	void ActionCreateAction::SetPrototypeClassName(const std::string className)
	{
		mPrototypeClassName = className;
		Find("PrototypeClassName")->SetStorage(&mPrototypeClassName, mPrototypeClassName.length());
	}

	void ActionCreateAction::SetPrototypeInstanceName(const std::string instanceName)
	{
		mPrototypeInstanceName = instanceName;
		Find("PrototypeInstanceName")->SetStorage(&mPrototypeInstanceName, mPrototypeInstanceName.length());
	}

	std::string ActionCreateAction::PrototypeClassName() const
	{
		return Find("PrototypeClassName")->Get<std::string&>();
	}

	std::string ActionCreateAction::PrototypeInstanceName() const
	{
		return Find("PrototypeInstanceName")->Get<std::string&>();
	}

	ActionCreateAction::~ActionCreateAction()
	{

	}

	void ActionCreateAction::Initialize()
	{
		AddExternalAttribute("PrototypeClassName", &mPrototypeClassName, sizeof(mPrototypeClassName));
		AddExternalAttribute("PrototypeInstanceName", &mPrototypeInstanceName, sizeof(mPrototypeInstanceName));
	}
}