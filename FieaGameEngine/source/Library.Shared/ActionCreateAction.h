#pragma once
#include "Action.h"
#include "Factory.h"
#include "RTTI.h"

namespace FieaGameEngine
{
	class ActionCreateAction : public Action
	{
		RTTI_DECLARATIONS(ActionCreateAction, Action);

	public:
		//!Constructor
		ActionCreateAction();

		//!Creates & adds an Action to its container
		void Update(WorldState& state);

		//!Sets the prototype class name attribute
		void SetPrototypeClassName(const std::string className);

		//!Sets the prototype instance name attribute
		void SetPrototypeInstanceName(const std::string instanceName);

		//!Returns the name of the prototype class
		std::string PrototypeClassName() const;

		//!Returns the name of the prototype instance
		std::string PrototypeInstanceName() const;

		//!Destructor
		~ActionCreateAction();

	protected:
		//!Adds prescribed attributes
		virtual void Initialize();

		std::string mPrototypeClassName;
		std::string mPrototypeInstanceName;
	};
}
