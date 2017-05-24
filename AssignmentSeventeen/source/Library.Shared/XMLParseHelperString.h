#pragma once
#include "IXMLParseHelper.h"
#include "SharedDataTable.h"

namespace FieaGameEngine
{
	class XMLParseHelperString final : public IXMLParseHelper
	{
		RTTI_DECLARATIONS(XMLParseHelperString, IXMLParseHelper)
			typedef Hashmap<std::string, std::string> HashmapType;

	public:
		XMLParseHelperString();
		void Initialize();
		bool StartElementHandler(SharedData& sharedData, std::string name, HashmapType* map);
		bool EndElementHandler(SharedData& sharedData, std::string name);
		XMLParseHelperString* Clone();

	private:
		const std::string mName = "entry";
		const std::string mType = "String";
		const std::string mTypeIdentifier = "type";
		const std::string mNameIdentifier = "name";
		const std::string mValueIdentifier = "value";
		const std::string mIndexIdentifier = "index";
	};
}
