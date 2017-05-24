#pragma once
#include "IXMLParseHelper.h"
#include "SharedDataTable.h"

namespace FieaGameEngine
{
	class XMLParseHelperTable final: public IXMLParseHelper
	{
		RTTI_DECLARATIONS(XMLParseHelperTable, IXMLParseHelper)
		typedef Hashmap<std::string, std::string> HashmapType;

	public:
		XMLParseHelperTable();
		void Initialize();
		bool StartElementHandler(SharedData& sharedData, std::string name, HashmapType* map);
		bool EndElementHandler(SharedData& sharedData, std::string name);
		XMLParseHelperTable* Clone();

	private:
		const std::string mType = "scope";
		const std::string mNameIdentifier = "name";
	};
}
