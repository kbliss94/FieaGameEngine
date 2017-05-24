#include "pch.h"
#include "SharedData.h"

namespace FieaGameEngine
{
	SharedData::SharedData() :
		mNestingDepth(0), mMaxNestingDepth(0),mParseMaster(nullptr)
	{

	}

	void SharedData::Initialize()
	{
		mNestingDepth = 0;
		mMaxNestingDepth = 0;
		mInitialized = true;
	}

	const bool SharedData::IsInitialized() const
	{
		return mInitialized;
	}

	const bool SharedData::IsClone() const
	{
		return mIsClone;
	}

	void SharedData::SetXMLParseMaster(XMLParseMaster* parseMaster)
	{
		mParseMaster = parseMaster;
	}

	XMLParseMaster* SharedData::GetXMLParseMaster() const
	{
		return mParseMaster;
	}

	void SharedData::IncrementDepth()
	{
		++mNestingDepth;
	}

	void SharedData::DecrementDepth()
	{
		if (mNestingDepth > 0)
		{
			--mNestingDepth;
		}
	}

	void SharedData::UpdateMaxDepth()
	{
		if (mNestingDepth > mMaxNestingDepth)
		{
			mMaxNestingDepth = mNestingDepth;
		}
	}

	const std::uint32_t SharedData::Depth() const
	{
		return mNestingDepth;
	}

	const std::uint32_t SharedData::MaxDepth() const
	{
		return mMaxNestingDepth;
	}
}