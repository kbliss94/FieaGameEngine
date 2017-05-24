#include "pch.h"
#include "TestSharedData.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(TestSharedData)

	TestSharedData::TestSharedData():
		mAge(0)
	{
		mInitialized = false;
		mIsClone = false;
	}

	void TestSharedData::Initialize()
	{
		SharedData::Initialize();
		mAge = 0;
	}

	TestSharedData& TestSharedData::Clone()
	{
		TestSharedData* clonedData = new TestSharedData;
		clonedData->mIsClone = true;
		clonedData->SetXMLParseMaster(GetXMLParseMaster());
		return *clonedData;
	}
}