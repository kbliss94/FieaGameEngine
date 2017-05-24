#pragma once
#include "Attributed.h"
#include "Sector.h"
#include "WorldState.h"
#include "EventQueue.h"

namespace FieaGameEngine
{
	class World final : public Attributed
	{
		RTTI_DECLARATIONS(World, Attributed);

	public:
		//!Constructor
		World();

		//!Destructor
		~World() = default;

		//!Returns the name of the world as a string
		/*!
		Name is stored as an external attribute
		*/
		std::string Name() const;

		//!Sets the name of the world
		void SetName(const std::string& name);

		//!Returns a reference to the Datum containing Sectors
		Datum& Sectors();

		//!Instantiates a new sector, adopts it into this world
		/*!
		\param sectorName name of the new sector
		\return the address of the newly created sector
		*/
		Sector* CreateSector(const std::string& sectorName);

		//!Adopts a Sector into this World
		void AdoptSector(Sector& sectorToAdopt);

		//!Iterates through the contained Sectors & calls their Update methods
		void Update(WorldState& state);

		//!Adds pointer to the given Action to the mActionsToDestroy vector
		/*!
		\param actionToDestroy reference to the Action that will be destroyed
		*/
		void EnqueueActionToDestroy(Action& actionToDestroy);

		//!Returns a pointer to the event queue associated with this instance
		EventQueue* GetEventQueue();

		//!Returns a pointer to the world state associated with this instance
		WorldState* GetWorldState();

	private:
		//!Adds prescribed attributes & nested scopes
		void Initialize();

		//!Deletes the Action pointers held in mActionsToDestroy & clears out the vector afterwards
		void DestroyActions();

		std::string mName;
		Vector<Action*> mActionsToDestroy;
		EventQueue mEventQueue;
		WorldState* mCurrentState;
	};
}
