#include "pch.h"
#include "XMLParseHelperInteger.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(XMLParseHelperInteger)

	XMLParseHelperInteger::XMLParseHelperInteger()
	{
		mInitialized = false;
		mIsClone = false;
	}

	void XMLParseHelperInteger::Initialize()
	{
		IXMLParseHelper::Initialize();
	}

	bool XMLParseHelperInteger::StartElementHandler(SharedData& sharedData, std::string name, HashmapType* map)
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
		appendedDatum->SetType(DatumType::Integer);

		std::string valueString = (*map)[mValueIdentifier];
		std::uint32_t index = 0;

		if (map->Find(mIndexIdentifier) != map->end())
		{
			index = stoi((*map)[mIndexIdentifier]);
		}

		appendedDatum->SetFromString(valueString, index);
		return true;
	}

	bool XMLParseHelperInteger::EndElementHandler(SharedData& sharedData, std::string name)
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

	XMLParseHelperInteger* XMLParseHelperInteger::Clone()
	{
		XMLParseHelperInteger* clonedHelper = new XMLParseHelperInteger();
		clonedHelper->mIsClone = true;
		return clonedHelper;
	}
}