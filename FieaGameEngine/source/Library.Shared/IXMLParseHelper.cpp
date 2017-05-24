#include "pch.h"
#include "IXMLParseHelper.h"

namespace FieaGameEngine
{
	void IXMLParseHelper::Initialize()
	{
		mInitialized = true;
	}

	const bool IXMLParseHelper::IsInitialized() const
	{
		return mInitialized;
	}

	const bool IXMLParseHelper::IsClone() const
	{
		return mIsClone;
	}

	bool IXMLParseHelper::CharDataHandler(SharedData&, std::string, std::uint32_t)
	{
		return false;
	}
}