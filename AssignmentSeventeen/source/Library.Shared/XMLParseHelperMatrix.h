#pragma once
#include "IXMLParseHelper.h"
#include "SharedDataTable.h"

namespace FieaGameEngine
{
	class XMLParseHelperMatrix final : public IXMLParseHelper
	{
		RTTI_DECLARATIONS(XMLParseHelperMatrix, IXMLParseHelper)
		typedef Hashmap<std::string, std::string> HashmapType;

	public:
		XMLParseHelperMatrix();
		void Initialize();
		bool StartElementHandler(SharedData& sharedData, std::string name, HashmapType* map);
		bool EndElementHandler(SharedData& sharedData, std::string name);
		XMLParseHelperMatrix* Clone();

	private:
		const std::string mName = "entry";
		const std::string mType = "Matrix";
		const std::string mTypeIdentifier = "type";
		const std::string mNameIdentifier = "name";
		const std::string mValueIdentifier = "value";
		const std::string mIndexIdentifier = "index";
	};
}
