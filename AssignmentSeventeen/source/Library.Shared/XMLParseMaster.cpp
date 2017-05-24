#include "pch.h"
#include "XMLParseMaster.h"

using namespace std;

namespace FieaGameEngine
{
	XMLParseMaster::XMLParseMaster(SharedData& sharedData) :
		mParser(XML_ParserCreate(nullptr)), mHelperList(VectorType()), mIsClone(false), mFilename(""), mSharedData(&sharedData)
	{
		sharedData.SetXMLParseMaster(this);
		XML_SetUserData(mParser, &sharedData);
		XML_SetElementHandler(mParser, StartElementHandler, EndElementHandler);
		XML_SetCharacterDataHandler(mParser, CharDataHandler);
	}

	XMLParseMaster::~XMLParseMaster()
	{
		if (mIsClone)
		{
			for (std::uint32_t i = 0; i < mHelperList.Size(); ++i)
			{
				delete mHelperList[i];
			}

			delete mSharedData;
		}

		XML_ParserFree(mParser);
	}

	XMLParseMaster* XMLParseMaster::Clone()
	{
		XMLParseMaster* parserClone;
		parserClone = new XMLParseMaster(mSharedData->Clone());

		for (auto& it : mHelperList)
		{
			parserClone->mHelperList.PushBack(it->Clone());
		}
		
		parserClone->mIsClone = true;
		return parserClone;
	}

	void XMLParseMaster::AddHelper(IXMLParseHelper& helper)
	{
		if (mIsClone)
		{
			throw std::exception("Cannot add helper to a clone.");
		}

		mHelperList.PushBack(&helper);
	}

	void XMLParseMaster::RemoveHelper(IXMLParseHelper& helper)
	{
		if (!mIsClone)
		{
			VectorType::Iterator it = mHelperList.Find(&helper);
			mHelperList.Remove(it);
		}
	}

	bool XMLParseMaster::HelperExists(IXMLParseHelper& helper)
	{
		if (mHelperList.Find(&helper) != mHelperList.end())
		{
			return true;
		}

		return false;
	}

	std::uint32_t XMLParseMaster::GetNumHelpers()
	{
		return mHelperList.Size();
	}

	void XMLParseMaster::Parse(const char* charBuffer, std::uint32_t numChars, bool lastChunk)
	{
		if (!mSharedData->mInitialized)
		{
			mSharedData->Initialize();
		}

		for (std::uint32_t i = 0; i < mHelperList.Size(); ++i)
		{
			if (!mHelperList[i]->IsInitialized())
			{
				mHelperList[i]->Initialize();
			}
		}

		XML_Parse(mParser, charBuffer, numChars, lastChunk);
	}

	void XMLParseMaster::ParseFromFile(const char* filename)
	{
		FILE* file;
		char* buffer = nullptr;
		long size;
		file = fopen(filename, "r");

		if (file != nullptr)
		{
			mFilename = filename;
			fseek(file, 0, SEEK_END);
			size = ftell(file);
			rewind(file);

			buffer = (char*)malloc(sizeof(char)*(size+1));

			if (buffer != nullptr)
			{
				fread(buffer, 1, (size), file);

				for (std::int32_t i = 0; i < size; ++i)
				{
					if (buffer[i] == '\n' || buffer[i] == '\t')
					{
						buffer[i] = ' ';
					}
				}

				buffer[size] = '\0';
				Parse(buffer, static_cast<std::uint32_t>(strlen(buffer)), true);
			}
		}

		fclose(file);
		free(buffer);
	}

	std::string XMLParseMaster::GetFileName() const
	{
		return mFilename;
	}

	SharedData& XMLParseMaster::GetSharedData() const
	{
		return *mSharedData;
	}

	void XMLParseMaster::SetSharedData(SharedData& sharedData)
	{
		if (mIsClone)
		{
			throw std::exception("Cannot change shared data for a clone.");
		}

		mSharedData = &sharedData;
		sharedData.SetXMLParseMaster(this);
	}

	void XMLParseMaster::StartElementHandler(void* userData, const XML_Char *name, const XML_Char **attributes)
	{
		SharedData* data;
		data = static_cast<SharedData*>(userData);
		assert (data != nullptr);
		assert(attributes != nullptr);

		VectorType* helperList = &(data->GetXMLParseMaster()->mHelperList);
		data->IncrementDepth();
		data->UpdateMaxDepth();

		HashmapType attributeMap;

		for (std::uint32_t i = 0; attributes[i] != 0; ++++i)
		{
			attributeMap[attributes[i]] = attributes[i + 1];
		}

		for (std::uint32_t i = 0; i < helperList->Size(); ++i)
		{
			if ((*helperList)[i]->StartElementHandler(*data, name, &attributeMap))
			{
				break;
			}
		}
	}

	void XMLParseMaster::EndElementHandler(void* userData, const XML_Char *name)
	{
		SharedData* data;
		data = static_cast<SharedData*>(userData);
		VectorType* helperList = &(data->GetXMLParseMaster()->mHelperList);

		for (std::uint32_t i = 0; i < helperList->Size(); ++i)
		{
			if ((*helperList)[i]->EndElementHandler(*data, name))
			{
				break;
			}
		}

		data->DecrementDepth();
	}

	void XMLParseMaster::CharDataHandler(void* userData, const XML_Char *string, std::int32_t length)
	{
		SharedData* data;
		data = static_cast<SharedData*>(userData);
		VectorType* helperList = &(data->GetXMLParseMaster()->mHelperList);

		for (std::uint32_t i = 0; i < helperList->Size(); ++i)
		{
			if ((*helperList)[i]->CharDataHandler(*data, string, length))
			{
				break;
			}
		}
	}

	bool XMLParseMaster::IsClone() const
	{
		return mIsClone;
	}
}