#pragma once
#include "IXMLParseHelper.h"
#include "SharedDataTable.h"
#include "ActionCreateAction.h"
#include "ActionDestroyAction.h"
#include "ActionEvent.h"

namespace FieaGameEngine
{
	class XMLParseHelperWorld final : public IXMLParseHelper
	{
		RTTI_DECLARATIONS(XMLParseHelperWorld, IXMLParseHelper)
		typedef Hashmap<std::string, std::string> HashmapType;

	public:
		XMLParseHelperWorld();
		void Initialize();
		bool StartElementHandler(SharedData& sharedData, std::string name, HashmapType* map);
		bool EndElementHandler(SharedData& sharedData, std::string name);
		XMLParseHelperWorld* Clone();

	private:
		const std::string mWorldType = "world";
		const std::string mSectorType = "sector";
		const std::string mEntityType = "entity";
		const std::string mActionType = "action";
		const std::string mClassIdentifier = "class";
		const std::string mNameIdentifier = "name";
		const std::string mProtoClassIdentifier = "prototypeClass";
		const std::string mProtoNameIdentifier = "prototypeName";
		const std::string mDestroyNameIdentifier = "destroyName";
		const std::string mSubtypeIdentifier = "subtype";
		const std::string mDelayIdentifier = "delay";
	};
}