#pragma once
#include "RTTI.h"

using namespace std;

namespace FieaGameEngine
{
	class SharedData abstract : public Library::RTTI
	{
	public:
		friend class XMLParseMaster;

		//!Constructor
		SharedData();
		//!Clears the state of the shared data, making it ready for a fresh file
		virtual void Initialize();
		virtual SharedData& Clone() = 0;
		//!Returns true if the object has been initialized, and false otherwise
		const bool IsInitialized() const;
		//!Returns true if the object is a clone, and false otherwise
		const bool IsClone() const;
		//!Assigns the address of the given XMLParseMaster to a private member
		/*!
		\param parseMaster given address of an XMLParseMaster
		*/
		void SetXMLParseMaster(XMLParseMaster* parseMaster);
		//!Returns the address of the XMLParseMaster associated w/this object
		/*!
		\return address of an XMLParseMaster
		*/
		XMLParseMaster* GetXMLParseMaster() const;
		//!Increments the "nesting depth" counter
		/*!Counter is incremented upon the start of each element
		*/
		void IncrementDepth();
		//!Decrements the "nesting depth" counter
		/*!Counter is decremented upon the end of each element
		*/
		void DecrementDepth();
		//!Sets mMaxDepth to the current mNestingDepth if it is greater than the current mMaxDepth
		void UpdateMaxDepth();
		//!Returns the current nesting depth
		const std::uint32_t Depth() const;
		//!Returns the maximum nesting depth reached
		const std::uint32_t MaxDepth() const;

	protected:
		bool mInitialized;
		bool mIsClone;
		std::uint32_t mNestingDepth;
		std::uint32_t mMaxNestingDepth;
		XMLParseMaster* mParseMaster;
	};
}
