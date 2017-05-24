#pragma once
#include "Action.h"
#include "Event.h"
#include "EventMessage.h"
#include "ReactionAttributed.h"

using namespace std;

namespace FieaGameEngine
{
	class ActionEvent : public Action
	{
		RTTI_DECLARATIONS(ActionEvent, Action);

	public:
		//!Constructor
		ActionEvent();

		//!Creates an attributed event, assigns its world & subtype, copies all auxiliary parameters into the event & queues the event w/the given delay
		void Update(WorldState& state);

		//!Sets mSubtype to the given subtype
		void SetSubtype(const std::string subtype);
		
		//!Sets mDelay to the given delay
		void SetDelay(const std::int32_t delay);

		//!Returns a copy of the mSubtype string
		std::string Subtype() const;

		//!Returns a copy of the mDelay integer
		std::int32_t Delay() const;

		//!Destructor
		~ActionEvent();

	private:
		//!Adds prescribed attributes
		virtual void Initialize();

		std::string mSubtype;
		std::int32_t mDelay;
		EventMessage mMessage;
	};
}
