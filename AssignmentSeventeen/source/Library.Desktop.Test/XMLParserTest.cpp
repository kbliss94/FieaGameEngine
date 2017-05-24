#include "pch.h"
#include "CppUnitTest.h"
#include "XMLParseMaster.h"
#include "TestXMLParseHelper.h"
#include "TestSharedData.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(XMLParserTest)
	{
	public:

		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		/*IXMLParseHelper*/
		TEST_METHOD(ParseHelperConstructor)
		{
			TestXMLParseHelper helper;
			Assert::IsFalse(helper.IsInitialized());
		}

		TEST_METHOD(ParseHelperInitialize)
		{
			TestXMLParseHelper helper;
			helper.Initialize();
			Assert::IsTrue(helper.IsInitialized());
		}

		TEST_METHOD(ParseHelperClone)
		{
			TestXMLParseHelper helper;
			TestXMLParseHelper* clonedHelper;
			clonedHelper = helper.Clone();
			
			Assert::IsFalse(clonedHelper->IsInitialized());

			delete clonedHelper;
		}

		/*SharedData*/
		TEST_METHOD(SharedDataConstructor)
		{
			TestSharedData data;
			std::uint32_t depth = 0;
			XMLParseMaster* master = nullptr;
			std::uint32_t age = 0;

			Assert::IsTrue(depth == data.Depth());
			Assert::IsTrue(master == data.GetXMLParseMaster());
			Assert::IsTrue(age == data.mAge);
			Assert::IsFalse(data.IsInitialized());
		}

		TEST_METHOD(SharedDataClone)
		{
			TestSharedData data;
			TestSharedData* clonedData;
			clonedData = &data.Clone();
			std::uint32_t depth = 0;
			XMLParseMaster* master = nullptr;
			std::uint32_t age = 0;

			Assert::IsTrue(depth == data.Depth());
			Assert::IsTrue(master == data.GetXMLParseMaster());
			Assert::IsTrue(age == data.mAge);

			delete clonedData;
		}

		TEST_METHOD(SharedDataInitialize)
		{
			TestSharedData data;
			std::uint32_t age = 0;
			Assert::IsTrue(age == data.mAge);

			data.mAge = 4;
			age = 4;
			Assert::IsTrue(age == data.mAge);

			data.Initialize();
			age = 0;
			Assert::IsTrue(age == data.mAge);
		}

		TEST_METHOD(SharedDataSetGetXMLMaster)
		{
			TestSharedData data;
			XMLParseMaster* masterPtr = nullptr;

			Assert::IsTrue(masterPtr == data.GetXMLParseMaster());

			XMLParseMaster master(data);
			masterPtr = &master;
			data.SetXMLParseMaster(masterPtr);
			Assert::IsTrue(masterPtr == data.GetXMLParseMaster());
		}

		TEST_METHOD(SharedDataIncrementDepth)
		{
			TestSharedData data;
			std::uint32_t depth = 0;
			Assert::IsTrue(depth == data.Depth());

			data.IncrementDepth();
			++depth;

			Assert::IsTrue(depth == data.Depth());

			data.IncrementDepth();
			++depth;

			Assert::IsTrue(depth == data.Depth());
		}

		TEST_METHOD(SharedDataDecrementDepth)
		{
			TestSharedData data;
			std::uint32_t depth = 0;
			Assert::IsTrue(depth == data.Depth());

			data.IncrementDepth();
			data.IncrementDepth();
			++depth;
			data.DecrementDepth();

			Assert::IsTrue(depth == data.Depth());

			data.DecrementDepth();
			--depth;
			Assert::IsTrue(depth == data.Depth());
		}

		TEST_METHOD(SharedDataDepth)
		{
			TestSharedData data;
			std::uint32_t depth = 0;
			Assert::IsTrue(depth == data.Depth());
		}

		/*XMLParseMaster*/
		TEST_METHOD(ParseMasterConstructor)
		{
			TestSharedData data;
			TestSharedData* dataPtr = &data;
			XMLParseMaster master(data);

			Assert::IsTrue(dataPtr->Equals(&master.GetSharedData()));
			Assert::IsTrue("" == master.GetFileName());
		}

		TEST_METHOD(ParseMasterClone)
		{
			TestSharedData data;
			XMLParseMaster master(data);
			XMLParseMaster* clonedMaster = master.Clone();

			Assert::IsTrue("" == master.GetFileName());
			Assert::IsTrue("" == clonedMaster->GetFileName());

			delete clonedMaster;
		}
		
		TEST_METHOD(ParseMasterAddHelper)
		{
			TestSharedData data;
			XMLParseMaster master(data);
			TestXMLParseHelper helper;

			master.AddHelper(helper);
			Assert::IsTrue(master.HelperExists(helper));

			XMLParseMaster* clonedMaster = master.Clone();

			auto testExpressionOne = [&clonedMaster, &helper] {clonedMaster->AddHelper(helper); };
			Assert::ExpectException<std::exception>(testExpressionOne);

			Assert::IsTrue(1 == master.GetNumHelpers());
			Assert::IsTrue(1 == clonedMaster->GetNumHelpers());

			TestXMLParseHelper helperTwo;
			master.AddHelper(helperTwo);
			Assert::IsTrue(2 == master.GetNumHelpers());

			delete clonedMaster;
		}

		TEST_METHOD(ParseMasterRemoveHelper)
		{
			TestSharedData data;
			XMLParseMaster master(data);
			TestXMLParseHelper helper;

			master.AddHelper(helper);
			Assert::IsTrue(master.HelperExists(helper));

			XMLParseMaster* clonedMaster = master.Clone();

			clonedMaster->RemoveHelper(helper);
			master.RemoveHelper(helper);
			Assert::IsFalse(master.HelperExists(helper));

			Assert::IsTrue(0 == master.GetNumHelpers());
			Assert::IsTrue(1 == clonedMaster->GetNumHelpers());

			delete clonedMaster;
		}

		TEST_METHOD(ParseMasterParse)
		{
			TestSharedData data;
			XMLParseMaster master(data);
			TestXMLParseHelper helper;
			//const char* xml = "<integer name=\"Age\" value=\"22\" />";
			const char* xml = "<student> <integer name=\"Age\" value=\"22\" /> </student>";

			master.AddHelper(helper);
			master.Parse(xml, static_cast<std::uint32_t>(strlen(xml)), true);
			Assert::IsTrue(22 == data.mAge);
			Assert::IsTrue(2 == data.MaxDepth());
			Assert::IsTrue(0 == data.Depth());

			XMLParseMaster* clonedMaster = master.Clone();
			clonedMaster->Parse(xml, static_cast<std::uint32_t>(strlen(xml)), true);
			
			TestSharedData* clonedData = static_cast<TestSharedData*>(&clonedMaster->GetSharedData());
			Assert::IsTrue(22 == clonedData->mAge);
			Assert::IsTrue(2 == clonedData->MaxDepth());
			Assert::IsTrue(0 == clonedData->Depth());
			delete clonedMaster;

			master.RemoveAllHelpers();
		}

		TEST_METHOD(ParseMasterParseFromFile)
		{
			TestSharedData data;
			XMLParseMaster master(data);
			TestXMLParseHelper helper;
			const char* filename = "..\\..\\..\\xml2.txt";

			master.AddHelper(helper);
			master.ParseFromFile(filename);

			Assert::IsTrue(filename == master.GetFileName());
			Assert::IsTrue(22 == data.mAge);
			Assert::IsTrue(2 == data.MaxDepth());
			Assert::IsTrue(0 == data.Depth());

			master.RemoveAllHelpers();
		}

		TEST_METHOD(ParseMasterGetSharedData)
		{
			TestSharedData data;
			TestSharedData* dataPtr = &data;
			XMLParseMaster master(data);

			Assert::IsTrue(dataPtr->Equals(&master.GetSharedData()));
		}

		TEST_METHOD(ParseMasterSetSharedData)
		{
			TestSharedData data;
			TestSharedData* dataPtr = &data;
			XMLParseMaster master(data);

			Assert::IsTrue(dataPtr->Equals(&master.GetSharedData()));

			TestSharedData dataTwo;
			TestSharedData* dataPtrTwo = &dataTwo;
			master.SetSharedData(*dataPtrTwo);

			Assert::IsTrue(dataPtrTwo->Equals(&master.GetSharedData()));
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
			UNREFERENCED_PARAMETER(diffMemState);
			UNREFERENCED_PARAMETER(endMemState);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState XMLParserTest::sStartMemState;
}