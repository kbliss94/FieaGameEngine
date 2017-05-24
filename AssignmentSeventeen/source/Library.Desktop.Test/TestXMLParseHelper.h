#pragma once
#include "IXMLParseHelper.h"
#include "TestSharedData.h"

namespace FieaGameEngine
{
	class TestXMLParseHelper final: public IXMLParseHelper
	{
		RTTI_DECLARATIONS(TestXMLParseHelper, IXMLParseHelper)
		typedef Hashmap<std::string, std::string> HashmapType;

	public:
		//!Constructor
		TestXMLParseHelper();
		void Initialize();
		bool StartElementHandler(SharedData& sharedData, std::string name, HashmapType* map);
		bool EndElementHandler(SharedData& sharedData, std::string name);
		bool CharDataHandler(SharedData& sharedData, std::string buffer, std::uint32_t length);
		TestXMLParseHelper* Clone();

	private:
		const std::string mNameOne = "student";
		const std::string mNameTwo = "integer";
	};
}
