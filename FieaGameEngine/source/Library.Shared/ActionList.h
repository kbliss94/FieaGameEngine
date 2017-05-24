#pragma once
#include "Action.h"
#include "Factory.h"
#include "RTTI.h"

namespace FieaGameEngine
{
	class ActionList : public Action
	{
		RTTI_DECLARATIONS(ActionList, Action);

	public:
		//!Constructor
		ActionList();

		//!Invokes the Update method for each Action contained within this object
		virtual void Update(WorldState& state);

		//!Instantiates a new Action object & adopts it into the Actions datum
		/*!
		\param className class name of the new Action
		\param instanceName instance name of the new Action
		\return pointer to the newly created Action
		*/
		Action* CreateAction(const std::string& className, const std::string& instanceName);

		//!Adopts the given Action into this ActionList
		void AdoptAction(Action& actionToAdopt);

		//!Returns the Actions datum
		Datum& Actions();

		//!Destructor
		~ActionList();

	protected:
		//!Adds prescribed attributes & nested scopes
		virtual void Initialize();
	};
}
