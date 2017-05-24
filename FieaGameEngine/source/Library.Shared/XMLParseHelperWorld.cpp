#include "pch.h"
#include "XMLParseHelperWorld.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(XMLParseHelperWorld)

	XMLParseHelperWorld::XMLParseHelperWorld()
	{
		mInitialized = false;
		mIsClone = false;
	}

	void XMLParseHelperWorld::Initialize()
	{
		IXMLParseHelper::Initialize();
	}

	bool XMLParseHelperWorld::StartElementHandler(SharedData& sharedData, std::string name, HashmapType* map)
	{
		if (sharedData.As<SharedDataTable>() == nullptr)
		{
			return false;
		}

		SharedDataTable* data = static_cast<SharedDataTable*>(&sharedData);

		if (data->Depth() == 1 && name != mWorldType)
		{
			return false;
		}

		if (data->Depth() == 2 && name != mSectorType)
		{
			return false;
		}

		if (data->Depth() > 2)
		{
			if (name != mSectorType && name != mEntityType && name != mActionType)
			{
				return false;
			}
		}

		if (data->Depth() == 1 && name == mWorldType)
		{
			data->mWorld->SetName((*map)[mNameIdentifier]);
		}

		if (data->Depth() > 1)
		{
			if (name == mSectorType)
			{
				data->mWorld->CreateSector((*map)[mNameIdentifier]);
			}

			if (name == mEntityType)
			{
				data->mState.mSector->CreateEntity((*map)[mClassIdentifier], (*map)[mNameIdentifier]);
			}

			if (name == mActionType)
			{
				if ((*map)[mClassIdentifier] == "ActionCreateAction")
				{
					ActionCreateAction* parsedAction = nullptr;

					if (data->mState.mAction != nullptr)
					{
						parsedAction = static_cast<ActionCreateAction*>(static_cast<ActionList*>(data->mState.mAction->GetParent())->CreateAction((*map)[mClassIdentifier], (*map)[mNameIdentifier]));
					}
					else if (data->mState.mEntity != nullptr)
					{
						parsedAction = static_cast<ActionCreateAction*>(data->mState.mEntity->CreateAction((*map)[mClassIdentifier], (*map)[mNameIdentifier]));
					}

					parsedAction->SetPrototypeClassName((*map)[mProtoClassIdentifier]);
					parsedAction->SetPrototypeInstanceName((*map)[mProtoNameIdentifier]);
				}
				else if ((*map)[mClassIdentifier] == "ActionDestroyAction")
				{
					ActionDestroyAction* parsedAction = nullptr;

					if (data->mState.mAction != nullptr)
					{
						parsedAction = static_cast<ActionDestroyAction*>(static_cast<ActionList*>(data->mState.mAction)->CreateAction((*map)[mClassIdentifier], (*map)[mNameIdentifier]));
					}
					else if (data->mState.mEntity != nullptr)
					{
						parsedAction = static_cast<ActionDestroyAction*>(data->mState.mEntity->CreateAction((*map)[mClassIdentifier], (*map)[mNameIdentifier]));
					}

					parsedAction->SetActionToDestroy((*map)[mDestroyNameIdentifier]);
				}
				else if ((*map)[mClassIdentifier] == "ActionEvent")
				{
					ActionEvent* parsedAction = nullptr;

					if (data->mState.mAction != nullptr)
					{
						parsedAction = static_cast<ActionEvent*>(static_cast<ActionList*>(data->mState.mAction)->CreateAction((*map)[mClassIdentifier], (*map)[mNameIdentifier]));
					}
					else if (data->mState.mEntity != nullptr)
					{
						parsedAction = static_cast<ActionEvent*>(data->mState.mEntity->CreateAction((*map)[mClassIdentifier], (*map)[mNameIdentifier]));
					}

					parsedAction->SetSubtype((*map)[mSubtypeIdentifier]);
					parsedAction->SetDelay(stoi((*map)[mDelayIdentifier]));
				}
				else
				{
					if (data->mState.mAction != nullptr)
					{
						static_cast<ActionList*>(data->mState.mAction)->CreateAction((*map)[mClassIdentifier], (*map)[mNameIdentifier]);
					}
					else if (data->mState.mEntity != nullptr)
					{
						data->mState.mEntity->CreateAction((*map)[mClassIdentifier], (*map)[mNameIdentifier]);
					}
				}
			}
		}

		data->Update();

		if (name == mWorldType)
		{
			data->mScope = data->mState.mWorld;
		}
		else if (name == mSectorType)
		{
			data->mScope = data->mState.mSector;
		}
		else if (name == mEntityType)
		{
			data->mScope = data->mState.mEntity;
		}
		else if (name == mActionType)
		{
			data->mScope = data->mState.mAction;
		}

		return true;
	}

	bool XMLParseHelperWorld::EndElementHandler(SharedData& sharedData, std::string name)
	{
		if (sharedData.As<SharedDataTable>() == nullptr)
		{
			return false;
		}

		if (name != mWorldType && name != mSectorType && name != mEntityType && name != mActionType)
		{
			return false;
		}

		SharedDataTable* data = static_cast<SharedDataTable*>(&sharedData);

		if (name == mWorldType)
		{
			data->mState.mWorld = nullptr;
		}
		else if (name == mSectorType)
		{
			data->mState.mSector = nullptr;
		}
		else if (name == mEntityType)
		{
			data->mState.mEntity = nullptr;
		}
		else if (name == mActionType)
		{
			data->mState.mAction = nullptr;
		}

		return true;
	}

	XMLParseHelperWorld* XMLParseHelperWorld::Clone()
	{
		XMLParseHelperWorld* clonedHelper = new XMLParseHelperWorld();
		clonedHelper->mIsClone = true;
		return clonedHelper;
	}
}