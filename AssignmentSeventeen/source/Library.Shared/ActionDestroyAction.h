#pragma once
#include "Action.h"
#include "World.h"
#include "RTTI.h"

namespace FieaGameEngine
{
	class ActionDestroyAction : public Action
	{
		RTTI_DECLARATIONS(ActionDestroyAction, Action);

	public:
		//!Constructor
		ActionDestroyAction();

		//!Removes and deletes an Action from its container
		void Update(WorldState& state);

		//!Sets the name of the Action to destroy from its container
		void SetActionToDestroy(const std::string actionName);

		//!Returns the name of the Action to destroy
		std::string ActionToDestroy() const;

		//!Destructor
		~ActionDestroyAction();

	protected:
		//!Adds prescribed attributes
		virtual void Initialize();

		std::string mActionToDestroy;
	};
}
