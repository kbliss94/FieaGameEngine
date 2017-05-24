#include "pch.h"
#include "XMLParseHelperTable.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(XMLParseHelperTable)

	XMLParseHelperTable::XMLParseHelperTable()
	{
		mInitialized = false;
		mIsClone = false;
	}

	void XMLParseHelperTable::Initialize()
	{
		IXMLParseHelper::Initialize();
	}

	bool XMLParseHelperTable::StartElementHandler(SharedData& sharedData, std::string name, HashmapType* map)
	{
		if (sharedData.As<SharedDataTable>() == nullptr)
		{
			return false;
		}

		if (name != mType)
		{
			return false;
		}

		SharedDataTable* data = static_cast<SharedDataTable*>(&sharedData);

		if (data->Depth() > 1)
		{
			data->mScope = &(data->mScope->AppendScope((*map)[mNameIdentifier]));
		}

		return true;
	}

	bool XMLParseHelperTable::EndElementHandler(SharedData& sharedData, std::string name)
	{
		if (sharedData.As<SharedDataTable>() == nullptr)
		{
			return false;
		}

		if (name != mType)
		{
			return false;
		}

		SharedDataTable* data = static_cast<SharedDataTable*>(&sharedData);

		if (data->mScope->GetParent() != nullptr)
		{
			data->mScope = data->mScope->GetParent();
		}

		return true;
	}

	XMLParseHelperTable* XMLParseHelperTable::Clone()
	{
		XMLParseHelperTable* clonedHelper = new XMLParseHelperTable();
		clonedHelper->mIsClone = true;
		return clonedHelper;
	}
}