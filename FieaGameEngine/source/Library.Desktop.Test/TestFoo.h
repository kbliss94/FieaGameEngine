#pragma once
#include "RTTI.h"

//!Test class
/*!
Used within unit tests
*/

namespace FieaGameEngine
{
	class Foo : public Library::RTTI
	{
		RTTI_DECLARATIONS(Foo, Library::RTTI);

	public:
		//!Constructor
		Foo();
		//!Sets the data value to the value specified
		/*!
		\param setData an integer value that mData will be set to
		*/
		void Data(std::int32_t setData);
		//!Returns the value of mData
		/*!
		\return the integer value of mData
		*/
		std::int32_t getData() const;
		//!Destructor
		~Foo();
		//!Copy constructor
		Foo(const Foo& rhs);
		//!Assignment operator
		Foo& operator= (const Foo& rhs);
		//!Comparison operator
		bool operator== (const Foo &rhs) const;
		bool operator!= (const Foo &rhs) const;

	private:
		//!Private integer 
		std::int32_t mData;
		//!Private pointer set to null
		std::int32_t *mPtr;
	};
}