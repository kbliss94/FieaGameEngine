#include "pch.h"
#include "XMLParseHelperVector.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(XMLParseHelperVector)

		XMLParseHelperVector::XMLParseHelperVector()
	{
		mInitialized = false;
		mIsClone = false;
	}

	void XMLParseHelperVector::Initialize()
	{
		IXMLParseHelper::Initialize();
	}

	bool XMLParseHelperVector::StartElementHandler(SharedData& sharedData, std::string name, HashmapType* map)
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
		appendedDatum->SetType(DatumType::Vector);

		std::string valueString = (*map)[mValueIdentifier];
		std::uint32_t index = 0;

		if (map->Find(mIndexIdentifier) != map->end())
		{
			index = stoi((*map)[mIndexIdentifier]);
		}

		appendedDatum->SetFromString(valueString, index);
		return true;
	}

	bool XMLParseHelperVector::EndElementHandler(SharedData& sharedData, std::string name)
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

	XMLParseHelperVector* XMLParseHelperVector::Clone()
	{
		XMLParseHelperVector* clonedHelper = new XMLParseHelperVector();
		clonedHelper->mIsClone = true;
		return clonedHelper;
	}
}