#pragma once
#include "Attributed.h"
#include "Action.h"
#include "Factory.h"
#include <assert.h>

namespace FieaGameEngine
{
	class Sector;
	class WorldState;

	class Entity : public Attributed
	{
		RTTI_DECLARATIONS(Entity, Attributed);

	public:
		//!Constructor
		Entity();

		//!Destructor
		~Entity() = default;

		//!Returns a string with the name of the entity
		/*!
		Name is stored as an external attribute.
		*/
		std::string Name() const;

		//!Sets the name of the entity
		void SetName(const std::string& name);

		//!Returns the Actions datum
		Datum& Actions();

		//!Instantiates a new Action object & adopts it into the Actions datum
		/*!
		\param className class name of the new Action
		\param instanceName instance name of the new Action
		\return pointer to the newly created Action
		*/
		Action* CreateAction(const std::string& className, const std::string& instanceName);

		//!Adopts the given Action into this Entity
		void AdoptAction(Action& actionToAdopt);

		//!Returns the address of the Sector which contains this object
		Sector* GetSector() const;

		//!Takes a WorldState reference
		void Update(WorldState& state);

	private:
		//!Adds prescribed attributes & nested scopes
		void Initialize();

		std::string mName;
	};
}
