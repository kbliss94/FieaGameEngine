#include "pch.h"
#include "WorldState.h"

namespace FieaGameEngine
{
	WorldState::WorldState():
		mWorld(nullptr), mSector(nullptr), mEntity(nullptr), mAction(nullptr), mTime(), mClock()
	{
		
	}

	Library::GameTime WorldState::GetGameTime() const
	{
		return mTime;
	}

	void WorldState::SetGameTime()
	{
		mTime.SetCurrentTime(mClock.CurrentTime());
	}
}