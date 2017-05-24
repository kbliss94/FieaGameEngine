#pragma once
#include "assert.h"
#include "expat.h"
#include "Vector.h"
#include "IXMLParseHelper.h"
#include "SharedData.h"
#include "SharedDataTable.h"
#include <stdio.h>
#include <stdlib.h>

namespace FieaGameEngine
{
	class XMLParseMaster final
	{
		typedef Vector<IXMLParseHelper*> VectorType;
		typedef std::pair<std::string, std::string> PairType;
		typedef Hashmap<std::string, std::string> HashmapType;

	public:
		//!Constructor that creates an Expat "object", registers the static callbacks & initializes member vars
		XMLParseMaster(SharedData& sharedData);
		//!Destructor
		virtual ~XMLParseMaster();
		//!Duplicates this object & returns its address
		/*!Object returned should be ready for parsing a fresh file. Denotes that the cloned
		parser is a clone.
		\return address of the duplicate of this object
		*/
		XMLParseMaster* Clone();
		//!Adds the IXMLParseHelper object given to the list
		/*!
		\param helper reference to the IXMLParseHelper object to add to the list
		*/
		void AddHelper(IXMLParseHelper& helper);
		//!Removes the IXMLParseHelper object from the list
		/*!
		\param helper reference to the IXMLParseHelper object to remove from the list
		*/
		void RemoveHelper(IXMLParseHelper& helper);
		//!Checks to see if a helper pointer exists in the helper list
		/*!
		\return true if the helper pointer exists in the list & false otherwise
		*/
		bool HelperExists(IXMLParseHelper& helper);
		//!Returns the number of helpers in the helper list
		std::uint32_t GetNumHelpers();
		//!Parses the text using the parameters given (wraps Expat's parse call)
		/*!
		\param charBuffer a character buffer of XML data
		\param numChars the number of characters in the given buffer
		\param lastChunk boolean indicating whether this is the last chunk of text for this file
		*/
		void Parse(const char* charBuffer, std::uint32_t numChars, bool lastChunk);
		//!Reads in the given file & parses it
		/*!
		\param filename given file to read in & parse
		*/
		void ParseFromFile(const char* filename);
		//!Returns the path for the file being parsed that was passed into ParseFromFile
		/*!Useful for reporting errors encountered while parsing
		\return path for the file being parsed
		*/
		std::string GetFileName() const;
		//!Returns the address of the SharedData associated w/this object
		SharedData& GetSharedData() const;
		//!Associates the given address of a SharedData object w/this object
		/*!
		\param address the address of a given SharedData object
		*/
		void SetSharedData(SharedData& sharedData);
		//!Returns true if the master is a clone & false otherwise
		bool IsClone() const;
		//!Clears helper list
		void RemoveAllHelpers() { mHelperList.Clear(); };


	private:
		//!The callback that Expat will call to handle XML start elements
		/*!Implements the chain of responsibility design pattern
		*/
		static void StartElementHandler(void* userData, const XML_Char *name, const XML_Char **attributes);
		//!The callback that Expat will call to handle XML end elements
		/*!Implements the chain of responsibility design pattern
		*/
		static void EndElementHandler(void* userData, const XML_Char *name);
		//!The callback that Expat will call to handle XML character data
		/*!Implements the chain of responsibility design pattern
		*/
		static void CharDataHandler(void* userData, const XML_Char *string, std::int32_t length);

		XML_Parser mParser;
		VectorType mHelperList;
		bool mIsClone;
		std::string mFilename;
		SharedData* mSharedData;
	};
}
