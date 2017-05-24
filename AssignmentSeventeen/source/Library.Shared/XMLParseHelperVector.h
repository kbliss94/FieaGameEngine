#pragma once
#include "IXMLParseHelper.h"
#include "SharedDataTable.h"

namespace FieaGameEngine
{
	class XMLParseHelperVector final : public IXMLParseHelper
	{
		RTTI_DECLARATIONS(XMLParseHelperVector, IXMLParseHelper)
		typedef Hashmap<std::string, std::string> HashmapType;

	public:
		XMLParseHelperVector();
		void Initialize();
		bool StartElementHandler(SharedData& sharedData, std::string name, HashmapType* map);
		bool EndElementHandler(SharedData& sharedData, std::string name);
		XMLParseHelperVector* Clone();

	private:
		const std::string mName = "entry";
		const std::string mType = "Vector";
		const std::string mTypeIdentifier = "type";
		const std::string mNameIdentifier = "name";
		const std::string mValueIdentifier = "value";
		const std::string mIndexIdentifier = "index";
	};
}
