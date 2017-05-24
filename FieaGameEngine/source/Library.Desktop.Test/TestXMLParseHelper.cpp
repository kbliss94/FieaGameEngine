#include "pch.h"
#include "TestXMLParseHelper.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(TestXMLParseHelper)

	TestXMLParseHelper::TestXMLParseHelper()
	{
		mInitialized = false;
	}

	void TestXMLParseHelper::Initialize()
	{
		IXMLParseHelper::Initialize();
	}

	bool TestXMLParseHelper::StartElementHandler(SharedData& sharedData, std::string name, HashmapType* map)
	{
		if (sharedData.As<TestSharedData>() == nullptr)
		{
			return false;
		}

		if (name == mNameOne)
		{
			return true;
		}
		if (name != mNameTwo)
		{
			return false;
		}

		TestSharedData* data = static_cast<TestSharedData*>(&sharedData);

		HashmapType::Iterator mapIt;
		mapIt = map->begin();

		std::string element0;
		std::string element1;
		std::string element2;
		std::string element3;

		element0 = mapIt->first;
		element1 = mapIt->second;
		++mapIt;
		element2 = mapIt->first;
		element3 = mapIt->second;

		if (element1 == "Age")
		{
			//static_cast<TestSharedData*>(dataPtr)->mAge = std::stoi(element3);
			data->mAge = std::stoi(element3);
		}

		return true;
	}

	bool TestXMLParseHelper::EndElementHandler(SharedData& sharedData, std::string name)
	{
		//SharedData* dataPtr = &sharedData;

		//if (dataPtr->As<TestSharedData>() == nullptr)
		//{
		//	return false;
		//}

		if (sharedData.As<TestSharedData>() == nullptr)
		{
			return false;
		}

		if (name != mNameOne && name != mNameTwo)
		{
			return false;
		}

		return true;
	}

	bool TestXMLParseHelper::CharDataHandler(SharedData& sharedData, std::string buffer, std::uint32_t length)
	{
		//SharedData* dataPtr = &sharedData;

		//if (dataPtr->As<TestSharedData>() == nullptr)
		//{
		//	return false;
		//}

		if (sharedData.As<TestSharedData>() == nullptr)
		{
			return false;
		}

		std::uint32_t bufferLength;
		bufferLength = length;
		std::string paramBuffer;
		paramBuffer = buffer;

		return true;
	}

	TestXMLParseHelper* TestXMLParseHelper::Clone()
	{
		TestXMLParseHelper* clonedHelper = new TestXMLParseHelper;
		return clonedHelper;
	}
}