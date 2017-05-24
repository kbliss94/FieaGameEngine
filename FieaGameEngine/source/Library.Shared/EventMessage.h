#pragma once
#include "Attributed.h"
#include "World.h"

using namespace std;

namespace FieaGameEngine
{
	class EventMessage : public Attributed
	{
		RTTI_DECLARATIONS(EventMessage, Attributed);

	public:
		//!Constructor
		EventMessage();

		//!Copy constructor
		EventMessage(const EventMessage& rhs);

		//!Assignment operator
		EventMessage& operator=(const EventMessage& rhs);

		//!Sets the object's subtype to the subtype passed in
		void SetSubtype(const std::string& subtype);

		//!Returns a copy of this object's subtype as a string
		const std::string GetSubtype() const;

		//!Sets the object's world pointer to the world passed in
		void SetWorld(World& world);

		//!Returns a copy of this object's world that will process the message
		World* GetWorld() const;

	private:
		std::string mSubtype;
		World* mWorld;
	};
}

