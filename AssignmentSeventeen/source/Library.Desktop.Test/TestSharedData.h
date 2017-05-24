#pragma once
#include "SharedData.h"

namespace FieaGameEngine
{
	class TestSharedData final: public SharedData
	{
		RTTI_DECLARATIONS(TestSharedData, SharedData)

	public:
		//!Constructor
		TestSharedData();
		//!Creates & returns a pointer to a deep copy of the current shared data
		TestSharedData& Clone();
		//!Prepares shared data for new information
		void Initialize();

		std::uint32_t mAge;
	};
}
