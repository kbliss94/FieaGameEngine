#include "pch.h"
#include "CppUnitTest.h"
#include "Scope.h"
#include "TestFoo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(ScopeTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD(RTTITests)
		{
			Scope testScope;
			Library::RTTI* testPtr = &testScope;

			Assert::IsTrue(nullptr == testPtr->QueryInterface(5));
			Assert::IsFalse(testPtr->Is(5));
			Assert::IsFalse(testPtr->Is("kaitlyn"));
			Assert::IsFalse(nullptr == testPtr->As<Scope>());
			Assert::IsTrue(&testScope == testPtr->As<Scope>());
		}

		TEST_METHOD(ScopeConstructor)
		{
			Scope k;

			Assert::IsTrue(k.GetParent() == nullptr);
		}

		TEST_METHOD(ScopeCopyConstructor)
		{
			Scope originalScope;
			Datum* healthDatum;
			Datum* nameDatum;
			Datum* ageDatum;
			Datum* vectorDatum;
			Datum* matrixDatum;
			Datum* ptrDatum;
			std::int32_t health = 80;
			std::string name = "kaitlyn";
			std::float_t age = 22.5f;
			glm::vec4 vector = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			glm::mat4 matrix = glm::mat4(1.0f);
			Foo testPtr;
			testPtr.Data(health);

			healthDatum = &originalScope.Append("Health");
			healthDatum->Set(health);
			nameDatum = &originalScope.Append("Name");
			nameDatum->Set(name);
			ageDatum = &originalScope.Append("Age");
			ageDatum->Set(age);
			vectorDatum = &originalScope.Append("Vector");
			vectorDatum->Set(vector);
			matrixDatum = &originalScope.Append("Matrix");
			matrixDatum->Set(matrix);
			ptrDatum = &originalScope.Append("Pointer");
			ptrDatum->Set(&testPtr);
			&originalScope.AppendScope("Scope");

			Scope copyScope(originalScope);

			Assert::IsTrue(*originalScope.Find("Health") == *copyScope.Find("Health"));
			Assert::IsTrue(*originalScope.Find("Name") == *copyScope.Find("Name"));
			Assert::IsTrue(*originalScope.Find("Age") == *copyScope.Find("Age"));
			Assert::IsTrue(*originalScope.Find("Vector") == *copyScope.Find("Vector"));
			Assert::IsTrue(*originalScope.Find("Matrix") == *copyScope.Find("Matrix"));
			Assert::IsTrue(*originalScope.Find("Pointer") == *copyScope.Find("Pointer"));
			Assert::IsTrue(*originalScope.Find("Scope") == *copyScope.Find("Scope"));
			Assert::IsTrue(originalScope == copyScope);
		}

		TEST_METHOD(ScopeMoveConstructor)
		{
			Scope originalScope;
			Datum* healthDatum;
			Datum* nameDatum;
			Datum* ageDatum;
			Datum* vectorDatum;
			Datum* matrixDatum;
			Datum* ptrDatum;
			std::int32_t health = 80;
			std::string name = "kaitlyn";
			std::float_t age = 22.5f;
			glm::vec4 vector = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			glm::mat4 matrix = glm::mat4(1.0f);
			Foo testPtr;
			testPtr.Data(health);

			healthDatum = &originalScope.Append("Health");
			healthDatum->Set(health);
			nameDatum = &originalScope.Append("Name");
			nameDatum->Set(name);
			ageDatum = &originalScope.Append("Age");
			ageDatum->Set(age);
			vectorDatum = &originalScope.Append("Vector");
			vectorDatum->Set(vector);
			matrixDatum = &originalScope.Append("Matrix");
			matrixDatum->Set(matrix);
			ptrDatum = &originalScope.Append("Pointer");
			ptrDatum->Set(&testPtr);
			&originalScope.AppendScope("Scope");

			Scope copyScope(std::move(originalScope));

			Assert::IsTrue(*healthDatum == *copyScope.Find("Health"));
			Assert::IsTrue(*nameDatum == *copyScope.Find("Name"));
			Assert::IsTrue(*ageDatum == *copyScope.Find("Age"));
			Assert::IsTrue(*vectorDatum == *copyScope.Find("Vector"));
			Assert::IsTrue(*matrixDatum == *copyScope.Find("Matrix"));
			Assert::IsTrue(*ptrDatum == *copyScope.Find("Pointer"));
			Assert::IsTrue(copyScope.Find("Scope")->Type() == DatumType::Table);
		}

		TEST_METHOD(ScopeAssignmentOperator)
		{
			Scope testScope;
			Datum* healthDatum;
			Datum* nameDatum;
			Datum* ageDatum;
			Datum* vectorDatum;
			Datum* matrixDatum;
			Datum* ptrDatum;
			std::int32_t health = 80;
			std::string name = "kaitlyn";
			std::float_t age = 22.5f;
			glm::vec4 vector = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			glm::mat4 matrix = glm::mat4(1.0f);
			Foo testPtr;
			testPtr.Data(health);

			healthDatum = &testScope.Append("Health");
			healthDatum->Set(health);
			nameDatum = &testScope.Append("Name");
			nameDatum->Set(name);
			ageDatum = &testScope.Append("Age");
			ageDatum->Set(age);
			vectorDatum = &testScope.Append("Vector");
			vectorDatum->Set(vector);
			matrixDatum = &testScope.Append("Matrix");
			matrixDatum->Set(matrix);
			ptrDatum = &testScope.Append("Pointer");
			ptrDatum->Set(&testPtr);
			&testScope.AppendScope("Scope");

			Scope testScopeTwo;
			testScopeTwo = testScope;

			Assert::IsTrue(*testScope.Find("Health") == *testScopeTwo.Find("Health"));
			Assert::IsTrue(*testScope.Find("Name") == *testScopeTwo.Find("Name"));
			Assert::IsTrue(*testScope.Find("Age") == *testScopeTwo.Find("Age"));
			Assert::IsTrue(*testScope.Find("Vector") == *testScopeTwo.Find("Vector"));
			Assert::IsTrue(*testScope.Find("Matrix") == *testScopeTwo.Find("Matrix"));
			Assert::IsTrue(*testScope.Find("Pointer") == *testScopeTwo.Find("Pointer"));
			Assert::IsTrue(*testScope.Find("Scope") == *testScopeTwo.Find("Scope"));
			Assert::IsTrue(testScope == testScopeTwo);
		}

		TEST_METHOD(ScopeMoveAssignmentOperator)
		{
			Scope testScope;
			Datum* healthDatum;
			Datum* nameDatum;
			Datum* ageDatum;
			Datum* vectorDatum;
			Datum* matrixDatum;
			Datum* ptrDatum;
			std::int32_t health = 80;
			std::string name = "kaitlyn";
			std::float_t age = 22.5f;
			glm::vec4 vector = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			glm::mat4 matrix = glm::mat4(1.0f);
			Foo testPtr;
			testPtr.Data(health);

			healthDatum = &testScope.Append("Health");
			healthDatum->Set(health);
			nameDatum = &testScope.Append("Name");
			nameDatum->Set(name);
			ageDatum = &testScope.Append("Age");
			ageDatum->Set(age);
			vectorDatum = &testScope.Append("Vector");
			vectorDatum->Set(vector);
			matrixDatum = &testScope.Append("Matrix");
			matrixDatum->Set(matrix);
			ptrDatum = &testScope.Append("Pointer");
			ptrDatum->Set(&testPtr);
			&testScope.AppendScope("Scope");

			Scope testScopeTwo;
			testScopeTwo = std::move(testScope);

			Assert::IsTrue(*healthDatum == *testScopeTwo.Find("Health"));
			Assert::IsTrue(*nameDatum == *testScopeTwo.Find("Name"));
			Assert::IsTrue(*ageDatum == *testScopeTwo.Find("Age"));
			Assert::IsTrue(*vectorDatum == *testScopeTwo.Find("Vector"));
			Assert::IsTrue(*matrixDatum == *testScopeTwo.Find("Matrix"));
			Assert::IsTrue(*ptrDatum == *testScopeTwo.Find("Pointer"));
			Assert::IsTrue(testScopeTwo.Find("Scope")->Type() == DatumType::Table);
		}

		TEST_METHOD(ScopeFind)
		{
			Scope testScope;
			const Scope* constTestScope = &testScope;
			Datum* healthDatum;
			Datum* nameDatum;
			Datum* ageDatum;
			Datum* vectorDatum;
			Datum* matrixDatum;
			Datum* ptrDatum;
			std::int32_t health = 80;
			std::string name = "kaitlyn";
			std::float_t age = 22.5f;
			glm::vec4 vector = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			glm::mat4 matrix = glm::mat4(1.0f);
			Foo testPtr;
			testPtr.Data(health);

			healthDatum = &testScope.Append("Health");
			healthDatum->Set(health);
			nameDatum = &testScope.Append("Name");
			nameDatum->Set(name);
			ageDatum = &testScope.Append("Age");
			ageDatum->Set(age);
			vectorDatum = &testScope.Append("Vector");
			vectorDatum->Set(vector);
			matrixDatum = &testScope.Append("Matrix");
			matrixDatum->Set(matrix);
			ptrDatum = &testScope.Append("Pointer");
			ptrDatum->Set(&testPtr);
			&testScope.AppendScope("Scope");

			Assert::IsTrue(*healthDatum == *testScope.Find("Health"));
			Assert::IsTrue((*testScope.Find("Health")).Get<std::int32_t&>() == health);
			Assert::IsTrue(*nameDatum == *testScope.Find("Name"));
			Assert::IsTrue((*testScope.Find("Name")).Get<std::string&>() == name);
			Assert::IsTrue(*ageDatum == *testScope.Find("Age"));
			Assert::IsTrue((*testScope.Find("Age")).Get<std::float_t&>() == age);
			Assert::IsTrue(*vectorDatum == *testScope.Find("Vector"));
			Assert::IsTrue((*testScope.Find("Vector")).Get<glm::vec4&>() == vector);
			Assert::IsTrue(*matrixDatum == *testScope.Find("Matrix"));
			Assert::IsTrue((*testScope.Find("Matrix")).Get<glm::mat4&>() == matrix);
			Assert::IsTrue(*ptrDatum == *testScope.Find("Pointer"));
			Assert::IsTrue((*testScope.Find("Pointer")).Get<Library::RTTI*&>() == &testPtr);
			Assert::IsTrue((*testScope.Find("Scope")).Type() == DatumType::Table);
			Assert::IsTrue(nullptr == testScope.Find("Year"));

			Assert::IsTrue(*healthDatum == *constTestScope->Find("Health"));
			Assert::IsTrue((*constTestScope->Find("Health")).Get<std::int32_t&>() == health);
			Assert::IsTrue(*nameDatum == *constTestScope->Find("Name"));
			Assert::IsTrue((*constTestScope->Find("Name")).Get<std::string&>() == name);
			Assert::IsTrue(*ageDatum == *constTestScope->Find("Age"));
			Assert::IsTrue((*constTestScope->Find("Age")).Get<std::float_t&>() == age);
			Assert::IsTrue(*vectorDatum == *testScope.Find("Vector"));
			Assert::IsTrue((*constTestScope->Find("Vector")).Get<glm::vec4&>() == vector);
			Assert::IsTrue(*matrixDatum == *testScope.Find("Matrix"));
			Assert::IsTrue((*constTestScope->Find("Matrix")).Get<glm::mat4&>() == matrix);
			Assert::IsTrue(*ptrDatum == *testScope.Find("Pointer"));
			Assert::IsTrue((*constTestScope->Find("Pointer")).Get<Library::RTTI*&>() == &testPtr);
			Assert::IsTrue((*constTestScope->Find("Scope")).Type() == DatumType::Table);
			Assert::IsTrue(nullptr == constTestScope->Find("Year"));
		}

		TEST_METHOD(ScopeSearch)
		{
			Scope testScope;
			Datum* healthDatum;
			Datum* nameDatum;
			Datum* ageDatum;
			Datum* scopeDatum;
			Datum* childHealthDatum;
			Scope* childScope = nullptr;
			std::int32_t health = 80;
			std::string name = "kaitlyn";
			std::float_t age = 22.5f;

			healthDatum = &testScope.Append("Health");
			healthDatum->Set(health);
			nameDatum = &testScope.Append("Name");
			nameDatum->Set(name);
			ageDatum = &testScope.Append("Age");
			ageDatum->Set(age);
			childScope = &testScope.AppendScope("Scope");
			childHealthDatum = &testScope.AppendScope("Scope").Append("ChildHealth");

			Datum* foundDatum;
			foundDatum = testScope.Search("Health");
			Assert::IsTrue(foundDatum == healthDatum);
			Assert::IsTrue(*foundDatum == *healthDatum);

			Assert::IsTrue(foundDatum == healthDatum);
			Assert::IsTrue(*foundDatum == *healthDatum);

			scopeDatum = testScope.Search("Scope");
			Assert::IsTrue(childScope->GetParent() == &testScope);
			childScope->Search("Health");
			Assert::IsTrue(*(testScope.Find("Health")) == *(childScope->Search("Health")));
		}

		TEST_METHOD(ScopeAppend)
		{
			Scope testScope;
			Datum* healthDatum;
			Datum secondHealthDatum;
			std::int32_t health = 10;

			healthDatum = &testScope.Append("Health");
			healthDatum->SetType(DatumType::Integer);
			healthDatum->Set(health);

			Assert::IsTrue(testScope[0] == *healthDatum);
			
			secondHealthDatum = testScope.Append("Health");

			Assert::IsTrue(testScope[0] == *healthDatum);
			auto testExpressionOne = [&testScope] {testScope[1]; };
			Assert::ExpectException<std::exception>(testExpressionOne);
			Assert::IsTrue(*healthDatum == secondHealthDatum);

			Datum* weatherDatum;
			Datum secondWeatherDatum;
			std::float_t weather = 89.5f;

			weatherDatum = &testScope.Append("Weather");
			weatherDatum->SetType(DatumType::Float);
			weatherDatum->Set(weather);

			Assert::IsTrue(testScope[0] == *healthDatum);
			Assert::IsTrue(testScope[1] == *weatherDatum);

			secondWeatherDatum = testScope.Append("Weather");

			Assert::IsTrue(testScope[1] == *weatherDatum);
			auto testExpressionTwo = [&testScope] {testScope[2]; };
			Assert::ExpectException<std::exception>(testExpressionTwo);
			Assert::IsTrue(*weatherDatum == secondWeatherDatum);

			Datum* nameDatum;
			Datum secondNameDatum;
			std::string name = "kaitlyn";

			nameDatum = &testScope.Append("Name");
			nameDatum->SetType(DatumType::String);
			nameDatum->Set(name);

			Assert::IsTrue(testScope[0] == *healthDatum);
			Assert::IsTrue(testScope[1] == *weatherDatum);
			Assert::IsTrue(testScope[2] == *nameDatum);

			secondNameDatum = testScope.Append("Name");

			Assert::IsTrue(testScope[2] == *nameDatum);
			auto testExpressionThree = [&testScope] {testScope[3]; };
			Assert::ExpectException<std::exception>(testExpressionThree);
			Assert::IsTrue(*nameDatum == secondNameDatum);

			Datum* vectorDatum;
			Datum secondVectorDatum;
			glm::vec4 vector = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

			vectorDatum = &testScope.Append("Vector");
			vectorDatum->SetType(DatumType::Vector);
			vectorDatum->Set(vector);

			Assert::IsTrue(testScope[0] == *healthDatum);
			Assert::IsTrue(testScope[1] == *weatherDatum);
			Assert::IsTrue(testScope[2] == *nameDatum);
			Assert::IsTrue(testScope[3] == *vectorDatum);

			secondVectorDatum = testScope.Append("Vector");

			Assert::IsTrue(testScope[3] == *vectorDatum);
			auto testExpressionFour = [&testScope] {testScope[4]; };
			Assert::ExpectException<std::exception>(testExpressionFour);
			Assert::IsTrue(*vectorDatum == secondVectorDatum);

			Datum* matrixDatum;
			Datum secondMatrixDatum;
			glm::mat4 matrix = glm::mat4(1.0f);

			matrixDatum = &testScope.Append("Matrix");
			matrixDatum->SetType(DatumType::Matrix);
			matrixDatum->Set(matrix);

			Assert::IsTrue(testScope[0] == *healthDatum);
			Assert::IsTrue(testScope[1] == *weatherDatum);
			Assert::IsTrue(testScope[2] == *nameDatum);
			Assert::IsTrue(testScope[3] == *vectorDatum);
			Assert::IsTrue(testScope[4] == *matrixDatum);

			secondMatrixDatum = testScope.Append("Matrix");

			Assert::IsTrue(testScope[4] == *matrixDatum);
			auto testExpressionFive = [&testScope] {testScope[5]; };
			Assert::ExpectException<std::exception>(testExpressionFive);
			Assert::IsTrue(*matrixDatum == secondMatrixDatum);

			Datum* ptrDatum;
			Datum secondPtrDatum;
			Foo testPtr;
			testPtr.Data(health);

			ptrDatum = &testScope.Append("Pointer");
			ptrDatum->SetType(DatumType::Pointer);
			ptrDatum->Set(&testPtr);

			Assert::IsTrue(testScope[0] == *healthDatum);
			Assert::IsTrue(testScope[1] == *weatherDatum);
			Assert::IsTrue(testScope[2] == *nameDatum);
			Assert::IsTrue(testScope[3] == *vectorDatum);
			Assert::IsTrue(testScope[4] == *matrixDatum);
			Assert::IsTrue(testScope[5] == *ptrDatum);

			secondPtrDatum = testScope.Append("Pointer");

			Assert::IsTrue(testScope[5] == *ptrDatum);
			auto testExpressionSix = [&testScope] {testScope[6]; };
			Assert::ExpectException<std::exception>(testExpressionSix);
			Assert::IsTrue(*vectorDatum == secondVectorDatum);
		}

		TEST_METHOD(ScopeAppendScope)
		{
			Scope outerScope;
			Scope* innerScope;
			Scope* innerScopeTwo;

			Datum* healthDatum;
			std::int32_t health = 80;
			healthDatum = &outerScope.Append("Health");
			healthDatum->Set(health);

			innerScope = &outerScope.AppendScope("Inner");

			Assert::IsTrue(outerScope[0].Type() == DatumType::Integer);
			Assert::IsTrue(outerScope[1].Type() == DatumType::Table);
			Assert::IsTrue(outerScope[1].Size() == 1);

			innerScopeTwo = &outerScope.AppendScope("Inner");

			auto testExpression = [&outerScope] {outerScope[2]; };
			Assert::ExpectException<std::exception>(testExpression);
			Assert::IsTrue(outerScope[1].Size() == 2);

			Assert::IsTrue(&outerScope == innerScope->GetParent());
			Assert::IsTrue(&outerScope == innerScopeTwo->GetParent());

			auto testExpressionTwo = [&outerScope] {outerScope.AppendScope("Health"); };
			Assert::ExpectException<std::exception>(testExpressionTwo);
		}

		TEST_METHOD(ScopeOrphan)
		{
			Scope parentScope;
			Datum* healthDatum;
			Datum* nameDatum;
			Datum* ageDatum;
			std::int32_t health = 80;
			std::string name = "kaitlyn";
			std::float_t age = 22.5f;

			healthDatum = &parentScope.Append("Health");
			healthDatum->Set(health);
			nameDatum = &parentScope.Append("Name");
			nameDatum->Set(name);
			ageDatum = &parentScope.Append("Age");
			ageDatum->Set(age);
			parentScope.AppendScope("Scope");

			Scope* childScope = new Scope();
			childScope->Append("Health");

			parentScope.Adopt(*childScope, "Scope");

			Assert::IsTrue(&parentScope == childScope->GetParent());
			Assert::IsTrue((*parentScope.Find("Scope"))[1] == *childScope);

			childScope->Orphan();
			Assert::IsTrue(nullptr == childScope->GetParent());

			delete childScope;
		}

		TEST_METHOD(ScopeAdopt)
		{
			Scope parentScope;
			Datum* healthDatum;
			Datum* nameDatum;
			Datum* ageDatum;
			std::int32_t health = 80;
			std::string name = "kaitlyn";
			std::float_t age = 22.5f;

			healthDatum = &parentScope.Append("Health");
			healthDatum->Set(health);
			nameDatum = &parentScope.Append("Name");
			nameDatum->Set(name);
			ageDatum = &parentScope.Append("Age");
			ageDatum->Set(age);
			parentScope.AppendScope("Scope");

			Scope* childScope = new Scope();
			parentScope.Adopt(*childScope, "Scope");

			Assert::IsTrue(&parentScope == childScope->GetParent());
			Assert::IsTrue((*parentScope.Find("Scope"))[1] == *childScope);

			Scope* childScopeTwo = new Scope();
			parentScope.Adopt(*childScopeTwo, "ScopeTwo");

			Assert::IsTrue(&parentScope == childScopeTwo->GetParent());
			Assert::IsTrue((*parentScope.Find("Scope"))[0] == *childScopeTwo);

			Scope parentScopeTwo;
			parentScopeTwo.Adopt(*childScopeTwo, "Scope");

			Assert::IsTrue(&parentScopeTwo == childScopeTwo->GetParent());
			Assert::IsTrue((*parentScopeTwo.Find("Scope"))[0] == *childScopeTwo);
		}

		TEST_METHOD(ScopeGetParent)
		{
			const Scope constScope;
			Scope outerScope;
			Scope* innerScope = new Scope();
			
			outerScope.Adopt(*innerScope, "Scope");

			Assert::IsTrue(nullptr == outerScope.GetParent());
			Assert::IsTrue(&outerScope == innerScope->GetParent());
			Assert::IsTrue(nullptr == constScope.GetParent());
		}
		
		TEST_METHOD(ScopeAppendBracketOperator)
		{
			Scope testScope;
			Datum* healthDatum;
			Datum secondHealthDatum;
			std::int32_t health = 10;

			healthDatum = &testScope["Health"];
			healthDatum->SetType(DatumType::Integer);
			healthDatum->Set(health);

			Assert::IsTrue(testScope[0] == *healthDatum);

			secondHealthDatum = testScope["Health"];

			Assert::IsTrue(testScope[0] == *healthDatum);

			auto testExpressionOne = [&testScope] {testScope[1]; };
			Assert::ExpectException<std::exception>(testExpressionOne);

			Assert::IsTrue(*healthDatum == secondHealthDatum);

			Datum* weatherDatum;
			Datum secondWeatherDatum;
			std::float_t weather = 89.5f;

			weatherDatum = &testScope["Weather"];
			weatherDatum->SetType(DatumType::Float);
			weatherDatum->Set(weather);

			Assert::IsTrue(testScope[0] == *healthDatum);
			Assert::IsTrue(testScope[1] == *weatherDatum);

			secondWeatherDatum = testScope["Weather"];

			Assert::IsTrue(testScope[1] == *weatherDatum);
			auto testExpressionTwo = [&testScope] {testScope[2]; };
			Assert::ExpectException<std::exception>(testExpressionTwo);
			Assert::IsTrue(*weatherDatum == secondWeatherDatum);
		}

		TEST_METHOD(ScopeIndexBracketOperator)
		{
			Scope testScope;
			const Scope* constTestScope = &testScope;
			Datum* healthDatum;
			Datum* nameDatum;
			Datum* ageDatum;
			std::int32_t health = 80;
			std::string name = "kaitlyn";
			std::float_t age = 22.5f;

			healthDatum = &testScope.Append("Health");
			healthDatum->Set(health);
			nameDatum = &testScope.Append("Name");
			nameDatum->Set(name);
			ageDatum = &testScope.Append("Age");
			ageDatum->Set(age);

			Assert::IsTrue(*healthDatum == testScope[0]);
			Assert::IsTrue(*nameDatum == testScope[1]);
			Assert::IsTrue(*ageDatum == testScope[2]);
			Assert::IsTrue(*healthDatum == (*constTestScope)[0]);
			Assert::IsTrue(*nameDatum == (*constTestScope)[1]);
			Assert::IsTrue(*ageDatum == (*constTestScope)[2]);

			auto testExpression = [&testScope] {testScope[5]; };
			Assert::ExpectException<std::exception>(testExpression);
			auto constTestExpression = [&constTestScope] {(*constTestScope)[5]; };
			Assert::ExpectException<std::exception>(constTestExpression);

			Scope testScopeTwo;

			auto testExpressionTwo = [&testScopeTwo] {testScopeTwo[1]; };
			Assert::ExpectException<std::exception>(testExpressionTwo);
		}

		TEST_METHOD(ScopeEqualComparisonOperator)
		{
			Scope lhsScope;
			Scope rhsScope;
			const Scope* constLhsScope = &lhsScope;
			const Scope* constRhsScope = &rhsScope;

			Assert::IsTrue(lhsScope == rhsScope);
			Assert::IsTrue(*constLhsScope == *constRhsScope);

			Datum* lhsHealthDatum;
			Datum* lhsNameDatum;
			Datum* lhsAgeDatum;
			Datum* rhsHealthDatum;
			Datum* rhsNameDatum;
			Datum* rhsAgeDatum;
			std::int32_t health = 80;
			std::string name = "kaitlyn";
			std::float_t age = 22.5f;

			lhsHealthDatum = &lhsScope.Append("Health");
			lhsHealthDatum->Set(health);
			lhsNameDatum = &lhsScope.Append("Name");
			lhsNameDatum->Set(name);
			lhsAgeDatum = &lhsScope.Append("Age");
			lhsAgeDatum->Set(age);
			lhsScope.AppendScope("Scope");

			rhsHealthDatum = &rhsScope.Append("Health");
			rhsHealthDatum->Set(health);
			rhsNameDatum = &rhsScope.Append("Name");
			rhsNameDatum->Set(name);
			rhsAgeDatum = &rhsScope.Append("Age");
			rhsAgeDatum->Set(age);
			rhsScope.AppendScope("Scope");

			Assert::IsTrue(lhsScope == rhsScope);
			Assert::IsTrue(*constLhsScope == *constRhsScope);

			lhsScope.Append("Test");

			Assert::IsFalse(lhsScope == rhsScope);
			Assert::IsFalse(*constLhsScope == *constRhsScope);
		}

		TEST_METHOD(ScopeNotEqualComparisonOperator)
		{
			Scope lhsScope;
			Scope rhsScope;
			const Scope* constLhsScope = &lhsScope;
			const Scope* constRhsScope = &rhsScope;

			Assert::IsFalse(lhsScope != rhsScope);
			Assert::IsFalse(*constLhsScope != *constRhsScope);

			Datum* lhsHealthDatum;
			Datum* lhsNameDatum;
			Datum* lhsAgeDatum;
			Datum* rhsHealthDatum;
			Datum* rhsNameDatum;
			Datum* rhsAgeDatum;
			std::int32_t health = 80;
			std::string name = "kaitlyn";
			std::float_t age = 22.5f;

			lhsHealthDatum = &lhsScope.Append("Health");
			lhsHealthDatum->Set(health);
			lhsNameDatum = &lhsScope.Append("Name");
			lhsNameDatum->Set(name);
			lhsAgeDatum = &lhsScope.Append("Age");
			lhsAgeDatum->Set(age);
			lhsScope.AppendScope("Scope");

			rhsHealthDatum = &rhsScope.Append("Health");
			rhsHealthDatum->Set(health);
			rhsNameDatum = &rhsScope.Append("Name");
			rhsNameDatum->Set(name);
			rhsAgeDatum = &rhsScope.Append("Age");
			rhsAgeDatum->Set(age);

			Assert::IsTrue(lhsScope != rhsScope);
			Assert::IsTrue(*constLhsScope != *constRhsScope);

			rhsScope.AppendScope("Scope");

			Assert::IsFalse(lhsScope != rhsScope);
			Assert::IsFalse(*constLhsScope != *constRhsScope);
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

	_CrtMemState ScopeTest::sStartMemState;
}