#pragma once
#include "Entity.h"

namespace FieaGameEngine
{
	class TestEntity : public Entity
	{
	public:
		//!Constructor
		TestEntity();

		std::int32_t mTestValue;
	};
}