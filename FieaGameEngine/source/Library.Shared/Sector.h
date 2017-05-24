#pragma once
#include "Attributed.h"
#include "Entity.h"
#include "WorldState.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class World;

	class Sector final : public Attributed
	{
		RTTI_DECLARATIONS(Sector, Attributed);

	public:
		//!Constructor
		Sector();

		//!Destructor
		~Sector() = default;

		//!Returns the name of the sector as a string
		/*!
		Name is stored as an external attribute
		*/
		std::string Name() const;

		//!Sets the name of the vector
		void SetName(const std::string& name);

		//!Returns the Datum reference that stores the contained Entities in the sector
		Datum& Entities();

		//!Makes a new object of the given type & adopts the entity into the sector
		/*!
		\param className class name of an entity
		\param instanceName instance name of an entity
		\return address of the newly created entity
		*/
		Entity* CreateEntity(const std::string& className, const std::string& instanceName);

		//!Adopts an Entity into this Sector
		void AdoptEntity(Entity& entityToAdopt);

		//!Returns the address of the world that owns this sector
		World* GetWorld() const;

		//!Iterates through the contained Entities & calls their Update methods
		void Update(WorldState& state);

	private:
		//!Adds prescribed attributes & nested scopes
		void Initialize();

		std::string mName;
	};
}
