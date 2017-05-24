#pragma once
#include "Scope.h"
#include "ActionList.h"
#include "World.h"
#include "WorldState.h"
#include "SharedData.h"

namespace FieaGameEngine
{
	class SharedDataTable : public SharedData
	{
		RTTI_DECLARATIONS(SharedDataTable, SharedData)

	public:
		//!Constructor
		SharedDataTable();
		//!Clones the current SharedDataTable by creating a new one on the heap & clearing the clone's scope
		/*!
		\return reference to cloned SharedDataTable 
		*/
		SharedDataTable& Clone();
		//!Calls SharedData's initialize & clears out the member scope
		void Initialize();
		//!Destructor
		~SharedDataTable();
		//!Updates all of the objects contained within mState
		void Update();

		Scope* mScope;
		World* mWorld;
		WorldState mState;
	};
}
