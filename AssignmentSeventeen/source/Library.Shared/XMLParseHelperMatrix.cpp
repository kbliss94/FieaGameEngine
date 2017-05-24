#include "pch.h"
#include "XMLParseHelperMatrix.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(XMLParseHelperMatrix)

	XMLParseHelperMatrix::XMLParseHelperMatrix()
	{
		mInitialized = false;
		mIsClone = false;
	}

	void XMLParseHelperMatrix::Initialize()
	{
		IXMLParseHelper::Initialize();
	}

	bool XMLParseHelperMatrix::StartElementHandler(SharedData& sharedData, std::string name, HashmapType* map)
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
		appendedDatum->SetType(DatumType::Matrix);

		std::string valueString = (*map)[mValueIdentifier];
		std::uint32_t index = 0;

		if (map->Find(mIndexIdentifier) != map->end())
		{
			index = stoi((*map)[mIndexIdentifier]);
		}

		appendedDatum->SetFromString(valueString, index);
		return true;
	}

	bool XMLParseHelperMatrix::EndElementHandler(SharedData& sharedData, std::string name)
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

	XMLParseHelperMatrix* XMLParseHelperMatrix::Clone()
	{
		XMLParseHelperMatrix* clonedHelper = new XMLParseHelperMatrix();
		clonedHelper->mIsClone = true;
		return clonedHelper;
	}
}