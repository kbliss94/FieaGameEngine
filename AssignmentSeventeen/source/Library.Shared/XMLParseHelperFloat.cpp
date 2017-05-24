#include "pch.h"
#include "XMLParseHelperFloat.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(XMLParseHelperFloat)

	XMLParseHelperFloat::XMLParseHelperFloat()
	{
		mInitialized = false;
		mIsClone = false;
	}

	void XMLParseHelperFloat::Initialize()
	{
		IXMLParseHelper::Initialize();
	}

	bool XMLParseHelperFloat::StartElementHandler(SharedData& sharedData, std::string name, HashmapType* map)
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
		appendedDatum->SetType(DatumType::Float);

		std::string valueString = (*map)[mValueIdentifier];
		std::uint32_t index = 0;

		if (map->Find(mIndexIdentifier) != map->end())
		{
			index = stoi((*map)[mIndexIdentifier]);
		}

		appendedDatum->SetFromString(valueString, index);
		return true;
	}

	bool XMLParseHelperFloat::EndElementHandler(SharedData& sharedData, std::string name)
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

	XMLParseHelperFloat* XMLParseHelperFloat::Clone()
	{
		XMLParseHelperFloat* clonedHelper = new XMLParseHelperFloat();
		clonedHelper->mIsClone = true;
		return clonedHelper;
	}
}