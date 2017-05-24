#pragma once
#include "Reaction.h"
#include "EventMessage.h"
#include "Event.h"

using namespace std;

namespace FieaGameEngine
{
	class ReactionAttributed final: public Reaction
	{
	public:
		//!Constructor
		ReactionAttributed();

		//!Accepts attributed events 
		/*!
		If the event subtype matches the reaction subtype, copies the attributed "arguments" to this instance of ReactionAttribute
		& then executes ActionList::Update
		*/
		void Notify(EventPublisher& event);
		
		//!Destructor
		~ReactionAttributed();

	private:
		//!Adds prescribed attributes
		void Initialize();

		std::string mSubtype;
	};
}
