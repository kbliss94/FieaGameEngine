#include "pch.h"
#include "XMLParseHelperIf.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(XMLParseHelperIf)

	XMLParseHelperIf::XMLParseHelperIf()
	{
		mInitialized = false;
		mIsClone = false;
	}

	void XMLParseHelperIf::Initialize()
	{
		IXMLParseHelper::Initialize();
	}

	bool XMLParseHelperIf::StartElementHandler(SharedData& sharedData, std::string name, HashmapType* map)
	{
		if (sharedData.As<SharedDataTable>() == nullptr)
		{
			return false;
		}

		if (name != mIfType && name != mThenType && name != mElseType)
		{
			return false;
		}

		SharedDataTable* data = static_cast<SharedDataTable*>(&sharedData);

		if (name == mIfType)
		{
			ActionIf* createdActionIf = nullptr;

			if (data->mState.mAction != nullptr && data->mState.mAction->Is("ActionList"))
			{
				createdActionIf = static_cast<ActionIf*>(static_cast<ActionList*>(data->mState.mAction)->CreateAction("ActionIf", mIfType));
			}
			else if (data->mState.mEntity != nullptr)
			{
				createdActionIf = static_cast<ActionIf*>(data->mState.mEntity->CreateAction("ActionIf", mIfType));
			}

			if (createdActionIf != nullptr)
			{
				createdActionIf->SetCondition(std::stoi((*map)[mConditionIdentifier]));
			}

			data->mScope = createdActionIf;
		}
		else if (name == mThenType)
		{
			(static_cast<ActionIf*>(data->mScope))->CreateThenAction((*map)[mClassIdentifier], (*map)[mNameIdentifier]);
		}
		else if (name == mElseType)
		{
			(static_cast<ActionIf*>(data->mScope))->CreateElseAction((*map)[mClassIdentifier], (*map)[mNameIdentifier]);
		}

		return true;
	}

	bool XMLParseHelperIf::EndElementHandler(SharedData& sharedData, std::string name)
	{
		if (sharedData.As<SharedDataTable>() == nullptr)
		{
			return false;
		}

		if (name != mIfType && name != mThenType && name != mElseType)
		{
			return false;
		}

		if (name == mIfType)
		{
			SharedDataTable* data = static_cast<SharedDataTable*>(&sharedData);
			data->Update();
			data->mScope = data->mScope->GetParent();
		}

		return true;
	}

	XMLParseHelperIf* XMLParseHelperIf::Clone()
	{
		XMLParseHelperIf* clonedHelper = new XMLParseHelperIf();
		clonedHelper->mIsClone = true;
		return clonedHelper;
	}
}