#include "pch.h"
#include "Entity.h"
#include "Sector.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Entity)

	Entity::Entity() :
		mName("")
	{
		Initialize();
	}

	std::string Entity::Name() const
	{
		return Find("Name")->Get<std::string&>();
	}

	void Entity::SetName(const std::string& name)
	{
		mName = name;
		Find("Name")->SetStorage(&mName, mName.length());
	}

	Datum& Entity::Actions()
	{
		return (*this)["Actions"];
	}

	Action* Entity::CreateAction(const std::string& className, const std::string& instanceName)
	{
		Action* createdAction =  Factory<Action>::Create(className);

		if (createdAction != nullptr)
		{
			createdAction->SetName(instanceName);
			AdoptAction(*createdAction);
		}

		return createdAction;
	}

	void Entity::AdoptAction(Action& actionToAdopt)
	{
		Adopt(actionToAdopt, "Actions");
	}

	Sector* Entity::GetSector() const
	{
		return static_cast<Sector*>(GetParent());
	}

	void Entity::Update(WorldState& state)
	{
		state.mEntity = this;
		Datum& actions = (*this)["Actions"];

		for (std::uint32_t i = 0; i < actions.Size(); ++i)
		{
			static_cast<Action*>(&(actions[i]))->Update(state);
		}
	}

	void Entity::Initialize()
	{
		AddExternalAttribute("Name", &mName, sizeof(mName));

		Scope* removeScope = &AddNestedScope("Actions");
		Actions().Remove(removeScope);
		delete removeScope;
	}
}