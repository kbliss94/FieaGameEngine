#include "pch.h"
#include "Sector.h"
#include "World.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Sector)

	Sector::Sector() :
		mName("")
	{
		Initialize();
	}

	std::string Sector::Name() const
	{
		return Find("Name")->Get<std::string&>();
	}

	void Sector::SetName(const std::string& name)
	{
		mName = name;
		Find("Name")->SetStorage(&mName, mName.length());
	}

	Datum& Sector::Entities()
	{
		return (*this)["Entities"];
	}

	Entity* Sector::CreateEntity(const std::string& className, const std::string& instanceName)
	{
		Entity* createdEntity = Factory<Entity>::Create(className);

		if (createdEntity != nullptr)
		{
			createdEntity->SetName(instanceName);
			AdoptEntity(*createdEntity);
		}

		return createdEntity;
	}

	void Sector::AdoptEntity(Entity& entityToAdopt)
	{
		Adopt(entityToAdopt, "Entities");
	}

	World* Sector::GetWorld() const
	{
		return static_cast<World*>(GetParent());
	}

	void Sector::Update(WorldState& state)
	{
		state.mSector = this;
		Datum& entities = (*this)["Entities"];

		for (std::uint32_t i = 0; i < entities.Size(); ++i)
		{
			static_cast<Entity*>(&(entities[i]))->Update(state);
		}
	}

	void Sector::Initialize()
	{
		AddExternalAttribute("Name", &mName, sizeof(mName));

		Scope* removeScope = &AddNestedScope("Entities");
		Entities().Remove(removeScope);
		delete removeScope;
	}
}