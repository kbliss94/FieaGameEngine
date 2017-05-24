#include "pch.h"
#include "CppUnitTest.h"
#include "XMLParseMaster.h"
#include "SharedDataTable.h"
#include "XMLParseHelperTable.h"
#include "XMLParseHelperInteger.h"
#include "XMLParseHelperFloat.h"
#include "XMLParseHelperString.h"
#include "XMLParseHelperVector.h"
#include "XMLParseHelperMatrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(XMLTableParserTest)
	{
	public:

		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		/*SharedDataTable*/

		TEST_METHOD(SharedDataTableConstructor)
		{
			SharedDataTable data;
			std::uint32_t depth = 0;
			XMLParseMaster* master = nullptr;

			Assert::IsTrue(depth == data.Depth());
			Assert::IsTrue(master == data.GetXMLParseMaster());
			Assert::IsFalse(data.IsInitialized());
			Assert::IsNull(data.mScope->GetParent());
		}

		TEST_METHOD(SharedDataTableClone)
		{
			SharedDataTable data;
			XMLParseMaster master(data);
			SharedDataTable* clonedData = &data.Clone();

			Assert::IsTrue(clonedData->IsClone());
			Assert::IsTrue(clonedData->GetXMLParseMaster() == data.GetXMLParseMaster());

			delete clonedData;
		}

		TEST_METHOD(SharedDataTableInitialize)
		{
			SharedDataTable data;
			XMLParseMaster master(data);
			XMLParseHelperTable tableHelper;
			XMLParseHelperInteger integerHelper;
			const char* xml = "<scope name=\"Level 1\"> <entry type=\"Integer\" name=\"Health\" value=\"10\"/> </scope>";

			master.AddHelper(tableHelper);
			master.AddHelper(integerHelper);
			master.Parse(xml, static_cast<std::uint32_t>(strlen(xml)), true);

			data.Initialize();

			Assert::IsTrue(0 == data.Depth());
			Assert::IsTrue(0 == data.MaxDepth());
			Assert::IsTrue(data.IsInitialized());
		}

		/*All ParseHelper Types*/
		
		TEST_METHOD(ParseHelperConstructors)
		{
			XMLParseHelperTable tableHelper;
			XMLParseHelperInteger integerHelper;
			XMLParseHelperFloat floatHelper;
			XMLParseHelperString stringHelper;
			XMLParseHelperVector vectorHelper;
			XMLParseHelperMatrix matrixHelper;

			Assert::IsFalse(tableHelper.IsInitialized());
			Assert::IsFalse(integerHelper.IsInitialized());
			Assert::IsFalse(floatHelper.IsInitialized());
			Assert::IsFalse(stringHelper.IsInitialized());
			Assert::IsFalse(vectorHelper.IsInitialized());
			Assert::IsFalse(matrixHelper.IsInitialized());
		}

		TEST_METHOD(ParseHelperInitialize)
		{
			XMLParseHelperTable tableHelper;
			XMLParseHelperInteger integerHelper;
			XMLParseHelperFloat floatHelper;
			XMLParseHelperString stringHelper;
			XMLParseHelperVector vectorHelper;
			XMLParseHelperMatrix matrixHelper;

			tableHelper.Initialize();
			integerHelper.Initialize();
			floatHelper.Initialize();
			stringHelper.Initialize();
			vectorHelper.Initialize();
			matrixHelper.Initialize();

			Assert::IsTrue(tableHelper.IsInitialized());
			Assert::IsTrue(integerHelper.IsInitialized());
			Assert::IsTrue(floatHelper.IsInitialized());
			Assert::IsTrue(stringHelper.IsInitialized());
			Assert::IsTrue(vectorHelper.IsInitialized());
			Assert::IsTrue(matrixHelper.IsInitialized());
		}

		TEST_METHOD(ParseHelperClone)
		{
			XMLParseHelperTable tableHelper;
			XMLParseHelperInteger integerHelper;
			XMLParseHelperFloat floatHelper;
			XMLParseHelperString stringHelper;
			XMLParseHelperVector vectorHelper;
			XMLParseHelperMatrix matrixHelper;

			XMLParseHelperTable* tableHelperClone;
			XMLParseHelperInteger* integerHelperClone;
			XMLParseHelperFloat* floatHelperClone;
			XMLParseHelperString* stringHelperClone;
			XMLParseHelperVector* vectorHelperClone;
			XMLParseHelperMatrix* matrixHelperClone;

			tableHelperClone = tableHelper.Clone();
			integerHelperClone = integerHelper.Clone();
			floatHelperClone = floatHelper.Clone();
			stringHelperClone = stringHelper.Clone();
			vectorHelperClone = vectorHelper.Clone();
			matrixHelperClone = matrixHelper.Clone();

			Assert::IsTrue(tableHelperClone->IsClone());
			Assert::IsTrue(integerHelperClone->IsClone());
			Assert::IsTrue(floatHelperClone->IsClone());
			Assert::IsTrue(stringHelperClone->IsClone());
			Assert::IsTrue(vectorHelperClone->IsClone());
			Assert::IsTrue(matrixHelperClone->IsClone());

			delete tableHelperClone;
			delete integerHelperClone;
			delete floatHelperClone;
			delete stringHelperClone;
			delete vectorHelperClone;
			delete matrixHelperClone;
		}

		/*ParseHelperInteger*/

		TEST_METHOD(ParseHelperIntegerParse)
		{
			SharedDataTable data;
			XMLParseMaster master(data);
			XMLParseHelperTable tableHelper;
			XMLParseHelperInteger integerHelper;
			const char* xml = "<scope name=\"Level 1\"> <entry type=\"Integer\" name=\"Health\" value=\"10\"/> </scope>";

			master.AddHelper(tableHelper);
			master.AddHelper(integerHelper);
			master.Parse(xml, static_cast<std::uint32_t>(strlen(xml)), true);
			Datum* healthDatum = data.mScope->Find("Health");

			Assert::IsTrue(2 == data.MaxDepth());
			Assert::IsNotNull(healthDatum);
			Assert::IsTrue(healthDatum->Type() == DatumType::Integer);
			Assert::IsTrue(10 == healthDatum->Get<std::int32_t&>());
		}

		/*ParseHelperFloat*/

		TEST_METHOD(ParseHelperFloatParse)
		{
			SharedDataTable data;
			XMLParseMaster master(data);
			XMLParseHelperTable tableHelper;
			XMLParseHelperFloat floatHelper;
			const char* xml = "<scope name=\"Level 1\"> <entry type=\"Float\" name=\"Age\" value=\"22.5\"/> </scope>";

			master.AddHelper(tableHelper);
			master.AddHelper(floatHelper);
			master.Parse(xml, static_cast<std::uint32_t>(strlen(xml)), true);
			Datum* ageDatum = data.mScope->Find("Age");

			Assert::IsTrue(2 == data.MaxDepth());
			Assert::IsNotNull(ageDatum);
			Assert::IsTrue(ageDatum->Type() == DatumType::Float);
			Assert::IsTrue(22.5 == ageDatum->Get<std::float_t&>());
		}

		/*ParseHelperString*/

		TEST_METHOD(ParseHelperStringParse)
		{
			SharedDataTable data;
			XMLParseMaster master(data);
			XMLParseHelperTable tableHelper;
			XMLParseHelperString stringHelper;
			const char* xml = "<scope name=\"Level 1\"> <entry type=\"String\" name=\"Alias\" value=\"kb\"/> </scope>";

			master.AddHelper(tableHelper);
			master.AddHelper(stringHelper);
			master.Parse(xml, static_cast<std::uint32_t>(strlen(xml)), true);
			Datum* aliasDatum = data.mScope->Find("Alias");

			Assert::IsTrue(2 == data.MaxDepth());
			Assert::IsNotNull(aliasDatum);
			Assert::IsTrue(aliasDatum->Type() == DatumType::String);
			Assert::IsTrue("kb" == aliasDatum->Get<std::string&>());
		}

		/*ParseHelperVector*/

		TEST_METHOD(ParseHelperVectorParse)
		{
			SharedDataTable data;
			XMLParseMaster master(data);
			XMLParseHelperTable tableHelper;
			XMLParseHelperVector vectorHelper;
			const char* xml = "<scope name=\"Level 1\"> <entry type=\"Vector\" name=\"Location\" value=\"vec4(1.00, 1.00, 1.00, 1.00)\"/> </scope>";
			
			master.AddHelper(tableHelper);
			master.AddHelper(vectorHelper);
			master.Parse(xml, static_cast<std::uint32_t>(strlen(xml)), true);
			Datum* vectorDatum = data.mScope->Find("Location");

			Assert::IsTrue(2 == data.MaxDepth());
			Assert::IsNotNull(vectorDatum);
			Assert::IsTrue(vectorDatum->Type() == DatumType::Vector);
			Assert::IsTrue(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) == vectorDatum->Get<glm::vec4&>());
		}

		/*ParseHelperMatrix*/

		TEST_METHOD(ParseHelperMatrixParse)
		{
			SharedDataTable data;
			XMLParseMaster master(data);
			XMLParseHelperTable tableHelper;
			XMLParseHelperMatrix matrixHelper;
			const char* xml = "<scope name=\"Level 1\"> <entry type=\"Matrix\" name=\"Location\" value=\"mat4x4((1.00, 0.00, 0.00, 0.00), (0.00, 1.00, 0.00, 0.00), (0.00, 0.00, 1.00, 0.00), (0.00, 0.00, 0.00, 1.00))\"/> </scope>";

			master.AddHelper(tableHelper);
			master.AddHelper(matrixHelper);
			master.Parse(xml, static_cast<std::uint32_t>(strlen(xml)), true);
			Datum* matrixDatum = data.mScope->Find("Location");

			Assert::IsTrue(2 == data.MaxDepth());
			Assert::IsNotNull(matrixDatum);
			Assert::IsTrue(matrixDatum->Type() == DatumType::Matrix);
			Assert::IsTrue(glm::mat4(1.0f) == matrixDatum->Get<glm::mat4&>());
		}

		/*ParseHelperTable*/

		TEST_METHOD(ParseHelperTableParse)
		{
			SharedDataTable data;
			XMLParseMaster master(data);
			XMLParseHelperTable tableHelper;
			XMLParseHelperInteger integerHelper;
			const char* xml = "<scope name=\"Level 1\"> <scope name=\"Player\"> <entry type=\"Integer\" name=\"Health\" value=\"10\"/> </scope> </scope>";

			master.AddHelper(tableHelper);
			master.AddHelper(integerHelper);
			master.Parse(xml, static_cast<std::uint32_t>(strlen(xml)), true);
			Datum* playerDatum = data.mScope->Find("Player");

			Assert::IsTrue(3 == data.MaxDepth());
			Assert::IsNotNull(playerDatum);

			Scope* playerScope = &(*playerDatum)[0];
			Datum* healthDatum = playerScope->Find("Health");
			Assert::IsTrue(healthDatum->Type() == DatumType::Integer);
			Assert::IsTrue(healthDatum->Get<std::int32_t&>() == 10);
		}

		TEST_METHOD(ParseHelperTableParseFile)
		{
			SharedDataTable data;
			XMLParseMaster master(data);
			XMLParseHelperTable tableHelper;
			XMLParseHelperInteger integerHelper;
			XMLParseHelperFloat floatHelper;
			XMLParseHelperString stringHelper;
			XMLParseHelperVector vectorHelper;
			XMLParseHelperMatrix matrixHelper;
			const char* filename = "..\\..\\..\\scopeXML.txt";

			master.AddHelper(tableHelper);
			master.AddHelper(integerHelper);
			master.AddHelper(floatHelper);
			master.AddHelper(stringHelper);
			master.AddHelper(vectorHelper);
			master.AddHelper(matrixHelper);
			master.ParseFromFile(filename);
			Datum* playerDatum = data.mScope->Find("Player");

			Assert::IsTrue(4 == data.MaxDepth());
			Assert::IsNotNull(playerDatum);

			Scope* playerScope = &(*playerDatum)[0];
			Datum* healthDatum = playerScope->Find("Health");
			Assert::IsTrue(healthDatum->Type() == DatumType::Integer);
			Assert::IsTrue(healthDatum->Get<std::int32_t&>() == 10);

			Datum* ageDatum = playerScope->Find("Ages");
			Assert::IsTrue(ageDatum->Type() == DatumType::Float);
			Assert::IsTrue(ageDatum->Get<std::float_t&>() == 19.5);
			Assert::IsTrue(ageDatum->Get<std::float_t&>(1) == 22.5);

			Datum* aliasesDatum = playerScope->Find("Aliases");
			Assert::IsTrue(aliasesDatum->Type() == DatumType::Table);

			Scope* aliasesScope = &(*aliasesDatum)[0];
			Datum* aliasDatum = aliasesScope->Find("Alias");
			Assert::IsTrue(aliasDatum->Get<std::string&>() == "kb");
			Assert::IsTrue(aliasDatum->Get<std::string&>(1) == "tb");

			Datum* vectorDatum = playerScope->Find("Vector");
			Assert::IsTrue(vectorDatum->Type() == DatumType::Vector);
			Assert::IsTrue(vectorDatum->Get<glm::vec4&>() == glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

			Datum* matrixDatum = playerScope->Find("Matrix");
			Assert::IsTrue(matrixDatum->Type() == DatumType::Matrix);
			Assert::IsTrue(matrixDatum->Get<glm::mat4&>() == glm::mat4(1.0f));

			XMLParseMaster* masterClone = master.Clone();
			SharedDataTable* masterCloneData = static_cast<SharedDataTable*>(&(masterClone->GetSharedData()));

			Assert::IsTrue(0 == masterCloneData->Depth());
			Assert::IsTrue(0 == masterCloneData->MaxDepth());
			Assert::IsNull(masterCloneData->mScope->Find("Player"));

			delete masterClone;
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

	_CrtMemState XMLTableParserTest::sStartMemState;
}