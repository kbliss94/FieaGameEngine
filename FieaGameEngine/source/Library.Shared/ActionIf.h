#pragma once
#include "Action.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class ActionIf : public Action
	{
		RTTI_DECLARATIONS(ActionIf, Action)

	public:
		//!Constructor
		ActionIf();

		//!Invokes the Update method on each contained Action
		virtual void Update(WorldState& state);

		//!Returns the integer condition
		std::int32_t Condition() const;

		//!Sets the integer condition
		void SetCondition(const std::int32_t& condition);

		//!Returns reference to Then Datum
		Datum& Then();

		//!Returns reference to Else Datum
		Datum& Else();

		//!Creates an Action to be added to the Then Datum
		Action* CreateThenAction(const std::string& className, const std::string& instanceName);

		//!Creates an Action to be added to the Else Datum
		Action* CreateElseAction(const std::string& className, const std::string& instanceName);

		//!Destructor
		~ActionIf();

	protected:
		//!Adds prescribed attributes & nested scopes
		virtual void Initialize();
		std::int32_t mCondition;
	};
}