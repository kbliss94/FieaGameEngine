#include "pch.h"
#include "XMLParseHelperString.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(XMLParseHelperString)

		XMLParseHelperString::XMLParseHelperString()
	{
		mInitialized = false;
		mIsClone = false;
	}

	void XMLParseHelperString::Initialize()
	{
		IXMLParseHelper::Initialize();
	}

	bool XMLParseHelperString::StartElementHandler(SharedData& sharedData, std::string name, HashmapType* map)
	{
		if (sharedData.As<SharedDataTable>() == nullptr)
		{
			return false;
		}

		if (name != mName)
		{
			return false;
		}
		else if ((*map)[mTypeIdentifier] != mType)
		{
			return false;
		}

		SharedDataTable* data = static_cast<SharedDataTable*>(&sharedData);
		Datum* appendedDatum = &(data->mScope->Append((*map)[mNameIdentifier]));
		appendedDatum->SetType(DatumType::String);

		std::string valueString = (*map)[mValueIdentifier];
		std::uint32_t index = 0;

		if (map->Find(mIndexIdentifier) != map->end())
		{
			index = stoi((*map)[mIndexIdentifier]);
		}

		appendedDatum->SetFromString(valueString, index);
		return true;
	}

	bool XMLParseHelperString::EndElementHandler(SharedData& sharedData, std::string name)
	{
		if (sharedData.As<SharedDataTable>() == nullptr)
		{
			return false;
		}

		if (name != mName)
		{
			return false;
		}

		return true;
	}

	XMLParseHelperString* XMLParseHelperString::Clone()
	{
		XMLParseHelperString* clonedHelper = new XMLParseHelperString();
		clonedHelper->mIsClone = true;
		return clonedHelper;
	}
}