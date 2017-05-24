#pragma once
#include "Hashmap.h"
#include "Attributed.h"
#include <string>

namespace FieaGameEngine
{
	class SharedData;

	class IXMLParseHelper abstract : public Library::RTTI
	{
		typedef Hashmap<std::string, std::string> HashmapType;

	public:
		//!Initializes this helper; will get called just before each file is parsed
		virtual void Initialize();
		//!Returns true if the object is initialized, and false otherwise
		const bool IsInitialized() const;
		//!Returns true if the object is a clone, and false otherwise
		const bool IsClone() const;
		//!Attempts to handle the element start
		/*!
		\param the sharedData object that the handler will be modifying if it can handle the information
		\param name string for the element name
		\param attributeMap hashmap of attribute name-value pairs
		\return true if the routine handles the element & false otherwise
		*/
		virtual bool StartElementHandler(SharedData& sharedData, std::string name, HashmapType* map) = 0;
		//!Attempts to handle the element end
		/*!
		\param the sharedData object that the handler will be modifying if it can handle the information
		\param name string for the element name
		\return true if the routine handles the element & false otherwise
		*/
		virtual bool EndElementHandler(SharedData& sharedData, std::string name) = 0;
		//!Attempts to handle the character data
		/*!
		\param the sharedData object that the handler will be modifying if it can handle the information
		\param charData string buffer of character data
		\param length the number of bytes in the character data buffer
		\return true if the routine handles the element & false otherwise
		*/
		virtual bool CharDataHandler(SharedData& sharedData, std::string buffer, std::uint32_t length);
		//!Creates and returns a pointer to a deep copy of this helper
		virtual IXMLParseHelper* Clone() = 0;		
		//!Destructor
		virtual ~IXMLParseHelper() = default;

	protected:
		bool mInitialized;
		bool mIsClone;
	};
}
