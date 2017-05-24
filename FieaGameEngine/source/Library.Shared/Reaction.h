#pragma once
#include "ActionList.h"
#include "EventSubscriber.h"

namespace FieaGameEngine
{
	class Reaction abstract : public ActionList, public EventSubscriber
	{
	RTTI_DECLARATIONS(Reaction, ActionList);

	public:

	};
}
