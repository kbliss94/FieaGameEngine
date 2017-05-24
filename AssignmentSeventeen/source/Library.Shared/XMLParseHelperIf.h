#pragma once
#include "IXMLParseHelper.h"
#include "SharedDataTable.h"
#include "ActionIf.h"

namespace FieaGameEngine
{
	class XMLParseHelperIf final : public IXMLParseHelper
	{
		RTTI_DECLARATIONS(XMLParseHelperIf, IXMLParseHelper)
		typedef Hashmap<std::string, std::string> HashmapType;

	public:
		XMLParseHelperIf();
		void Initialize();
		bool StartElementHandler(SharedData& sharedData, std::string name, HashmapType* map);
		bool EndElementHandler(SharedData& sharedData, std::string name);
		XMLParseHelperIf* Clone();

	private:
		const std::string mIfType = "if";
		const std::string mThenType = "then";
		const std::string mElseType = "else";
		const std::string mConditionIdentifier = "condition";
		const std::string mClassIdentifier = "class";
		const std::string mNameIdentifier = "name";
	};
}
