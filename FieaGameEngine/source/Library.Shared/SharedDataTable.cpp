#include "pch.h"
#include "SharedDataTable.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(SharedDataTable)

	SharedDataTable::SharedDataTable():
		mState()
	{
		mInitialized = false;
		mIsClone = false;
		mWorld = new World();
		mScope = mWorld;
	}

	SharedDataTable& SharedDataTable::Clone()
	{
		SharedDataTable* clonedData = new SharedDataTable();
		clonedData->mIsClone = true;
		clonedData->SetXMLParseMaster(GetXMLParseMaster());
		return *clonedData;
	}

	void SharedDataTable::Initialize()
	{
		SharedData::Initialize();
	}

	SharedDataTable::~SharedDataTable()
	{
		mWorld->Clear();
		delete mWorld;
	}

	void SharedDataTable::Update()
	{
		mWorld->Update(mState);
	}
}