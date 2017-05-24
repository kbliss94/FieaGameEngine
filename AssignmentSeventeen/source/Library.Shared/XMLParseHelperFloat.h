#pragma once
#include "IXMLParseHelper.h"
#include "SharedDataTable.h"

namespace FieaGameEngine
{
	class XMLParseHelperFloat final : public IXMLParseHelper
	{
		RTTI_DECLARATIONS(XMLParseHelperFloat, IXMLParseHelper)
		typedef Hashmap<std::string, std::string> HashmapType;

	public:
		XMLParseHelperFloat();
		void Initialize();
		bool StartElementHandler(SharedData& sharedData, std::string name, HashmapType* map);
		bool EndElementHandler(SharedData& sharedData, std::string name);
		XMLParseHelperFloat* Clone();

	private:
		const std::string mName = "entry";
		const std::string mType = "Float";
		const std::string mTypeIdentifier = "type";
		const std::string mNameIdentifier = "name";
		const std::string mValueIdentifier = "value";
		const std::string mIndexIdentifier = "index";
	};
}