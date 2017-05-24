#include "pch.h"
#include "World.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(World)

	World::World() :
		mName(), mActionsToDestroy(), mEventQueue(), mCurrentState(nullptr)
	{
		Initialize();
	}

	std::string World::Name() const
	{
		return Find("Name")->Get<std::string&>();
	}

	void World::SetName(const std::string& name)
	{
		mName = name;
		Find("Name")->SetStorage(&mName, mName.length());
	}

	Datum& World::Sectors() 
	{
		return (*this)["Sectors"];
	}

	Sector* World::CreateSector(const std::string& sectorName)
	{
		Sector* createdSector = new Sector;
		createdSector->SetName(sectorName);
		AdoptSector(*createdSector);
		return createdSector;
	}

	void World::AdoptSector(Sector& sectorToAdopt)
	{
		Adopt(sectorToAdopt, "Sectors");
	}

	void World::Update(WorldState& state)
	{
		state.mWorld = this;
		mCurrentState = &state;
		Datum& sectors = (*this)["Sectors"];

		for (std::uint32_t i = 0; i < sectors.Size(); ++i)
		{
			static_cast<Sector*>(&(sectors[i]))->Update(state);
		}

		DestroyActions();
		mEventQueue.Update(state.GetGameTime());
	}

	void World::EnqueueActionToDestroy(Action& actionToDestroy)
	{
		mActionsToDestroy.PushBack(&actionToDestroy);
	}

	void World::DestroyActions()
	{
		for (std::uint32_t i = 0; i < mActionsToDestroy.Size(); ++i)
		{
			mActionsToDestroy[i]->Orphan();
			delete mActionsToDestroy[i];
		}

		mActionsToDestroy.Clear();
	}

	EventQueue* World::GetEventQueue() 
	{
		return &mEventQueue;
	}

	WorldState* World::GetWorldState()
	{
		return mCurrentState;
	}

	void World::Initialize()
	{
		AddExternalAttribute("Name", &mName, sizeof(mName));

		Scope* removeScope = &AddNestedScope("Sectors");
		Sectors().Remove(removeScope);
		delete removeScope;
	}
}