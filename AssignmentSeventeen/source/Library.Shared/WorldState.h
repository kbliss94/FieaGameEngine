#pragma once
#include "GameTime.h"

namespace FieaGameEngine
{
	class WorldState
	{
	public:
		//!Constructor
		WorldState();

		//!Get the current game time
		Library::GameTime GetGameTime() const;

		//!Set the current game time
		void SetGameTime();

		//!Pointers to the object that is currently being processed
		class World* mWorld;
		class Sector* mSector;
		class Entity* mEntity;
		class Action* mAction;

	private:
		Library::GameTime mTime;
		Library::GameClock mClock;
	};
}
