#include "pch.h"
#include "TestFoo.h"
#include <cstdint>

namespace FieaGameEngine
{
	Foo::Foo():
		mData(0), mPtr(new std::int32_t)
	{

	}

	void Foo::Data(std::int32_t setData)
	{
		mData = setData;
	}

	std::int32_t Foo::getData() const
	{
		return mData;
	}

	Foo::~Foo()
	{
		delete mPtr;
	}

	Foo::Foo(const Foo& rhs):
		mData(rhs.mData), mPtr(new std::int32_t(*rhs.mPtr))
	{

	}

	Foo &Foo::operator= (const Foo& rhs)
	{
		if (this != &rhs)
		{
			delete mPtr;
			mData = rhs.mData;
			mPtr = new std::int32_t(*rhs.mPtr);
		}

		return *this;
	}

	bool Foo::operator== (const Foo &rhs) const
	{
		return (mData == rhs.mData && *mPtr == *rhs.mPtr);
	}

	bool Foo::operator!= (const Foo &rhs) const
	{
		return (mData != rhs.mData && *mPtr != *rhs.mPtr);
	}
}