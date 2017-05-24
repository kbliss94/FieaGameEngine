#pragma once
#include "IXMLParseHelper.h"
#include "SharedDataTable.h"

namespace FieaGameEngine
{
	class XMLParseHelperInteger final : public IXMLParseHelper
	{
		RTTI_DECLARATIONS(XMLParseHelperInteger, IXMLParseHelper)
		typedef Hashmap<std::string, std::string> HashmapType;

	public:
		XMLParseHelperInteger();
		void Initialize();
		bool StartElementHandler(SharedData& sharedData, std::string name, HashmapType* map);
		bool EndElementHandler(SharedData& sharedData, std::string name);
		XMLParseHelperInteger* Clone();

	private:
		const std::string mName = "entry";
		const std::string mType = "Integer";
		const std::string mTypeIdentifier = "type";
		const std::string mNameIdentifier = "name";
		const std::string mValueIdentifier = "value";
		const std::string mIndexIdentifier = "index";
	};
}
