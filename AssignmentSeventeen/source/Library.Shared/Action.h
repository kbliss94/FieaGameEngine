#pragma once
#include "Attributed.h"
#include "WorldState.h"

namespace FieaGameEngine
{
	class Entity;

	class Action abstract: public Attributed
	{
	public:
		virtual void Update(WorldState& state) = 0;

		//!Returns a string with the name of the entity
		/*!
		Name is stored as an external attribute.
		*/
		std::string Name() const;

		//!Sets the name of the entity
		/*!
		\param name the name of the newly created Entity
		*/
		void SetName(const std::string& name);

	protected:
		//!Adds prescribed attributes
		virtual void Initialize();

		std::string mName;
	};
}