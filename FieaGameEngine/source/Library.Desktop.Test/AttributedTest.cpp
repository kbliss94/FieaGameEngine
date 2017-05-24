#include "pch.h"
#include "CppUnitTest.h"
#include "AttributedFoo.h"
//do i need to include attributed.h

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(AttributedTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD(AttributedFooConstructor)
		{
			AttributedFoo testFoo;

			Assert::IsTrue(testFoo[0].Type() == DatumType::Pointer);
			Assert::IsTrue(testFoo[1].Type() == DatumType::Integer);
			Assert::IsTrue(testFoo[2].Type() == DatumType::Float);
			Assert::IsTrue(testFoo[3].Type() == DatumType::String);
			Assert::IsTrue(testFoo[4].Type() == DatumType::Vector);
			Assert::IsTrue(testFoo[5].Type() == DatumType::Matrix);
			Assert::IsTrue(testFoo[6].Type() == DatumType::Integer);
			Assert::IsTrue(testFoo[7].Type() == DatumType::Float);
			Assert::IsTrue(testFoo[8].Type() == DatumType::String);
			Assert::IsTrue(testFoo[9].Type() == DatumType::Vector);
			Assert::IsTrue(testFoo[10].Type() == DatumType::Matrix);
			Assert::IsTrue(testFoo[11].Type() == DatumType::Table);
			Assert::IsTrue(testFoo[12].Type() == DatumType::Table);

			const AttributedFoo constTestFoo;

			Assert::IsTrue(constTestFoo[0].Type() == DatumType::Pointer);
			Assert::IsTrue(constTestFoo[1].Type() == DatumType::Integer);
			Assert::IsTrue(constTestFoo[2].Type() == DatumType::Float);
			Assert::IsTrue(constTestFoo[3].Type() == DatumType::String);
			Assert::IsTrue(constTestFoo[4].Type() == DatumType::Vector);
			Assert::IsTrue(constTestFoo[5].Type() == DatumType::Matrix);
			Assert::IsTrue(constTestFoo[6].Type() == DatumType::Integer);
			Assert::IsTrue(constTestFoo[7].Type() == DatumType::Float);
			Assert::IsTrue(constTestFoo[8].Type() == DatumType::String);
			Assert::IsTrue(constTestFoo[9].Type() == DatumType::Vector);
			Assert::IsTrue(constTestFoo[10].Type() == DatumType::Matrix);
			Assert::IsTrue(constTestFoo[11].Type() == DatumType::Table);
			Assert::IsTrue(constTestFoo[12].Type() == DatumType::Table);
		}

		TEST_METHOD(AttributedCopyConstructor)
		{
			AttributedFoo testFooRHS;

			Datum* firstAuxiliary = &testFooRHS.AppendAuxiliaryAttribute("auxiliary one");
			Datum* secondAuxiliary = &testFooRHS.AppendAuxiliaryAttribute("auxiliary two");

			Assert::IsTrue(*firstAuxiliary == testFooRHS[testFooRHS.AuxiliaryBegin()]);
			Assert::IsTrue(*secondAuxiliary == testFooRHS[testFooRHS.AuxiliaryBegin() + 1]);

			AttributedFoo testFooLHS(testFooRHS);

			Assert::IsTrue(testFooLHS[testFooLHS.AuxiliaryBegin()] == testFooRHS[testFooRHS.AuxiliaryBegin()]);
			Assert::IsTrue(testFooLHS[testFooLHS.AuxiliaryBegin() + 1] == testFooRHS[testFooRHS.AuxiliaryBegin() + 1]);
			
			for (std::uint32_t i = 1; i < (testFooLHS.AuxiliaryBegin() + 1); ++i)
			{
				Assert::IsTrue(testFooLHS[i] == testFooRHS[i]);
			}

			const AttributedFoo constTestFooLHS(testFooRHS);

			Assert::IsTrue(testFooLHS[testFooLHS.AuxiliaryBegin()] == testFooRHS[testFooRHS.AuxiliaryBegin()]);
			Assert::IsTrue(testFooLHS[testFooLHS.AuxiliaryBegin() + 1] == testFooRHS[testFooRHS.AuxiliaryBegin() + 1]);

			for (std::uint32_t i = 1; i < (testFooLHS.AuxiliaryBegin() + 1); ++i)
			{
				Assert::IsTrue(testFooLHS[i] == testFooRHS[i]);
			}
		}

		TEST_METHOD(AttributedAssignmentOperator)
		{
			AttributedFoo testFooRHS;
			AttributedFoo testFooLHS;

			Datum* firstAuxiliary = &testFooRHS.AppendAuxiliaryAttribute("auxiliary one");
			Datum* secondAuxiliary = &testFooRHS.AppendAuxiliaryAttribute("auxiliary two");

			Assert::IsTrue(*firstAuxiliary == testFooRHS[testFooRHS.AuxiliaryBegin()]);
			Assert::IsTrue(*secondAuxiliary == testFooRHS[testFooRHS.AuxiliaryBegin() + 1]);

			auto testExpressionOne = [&testFooLHS] {testFooLHS[testFooLHS.AuxiliaryBegin()]; };
			Assert::ExpectException<std::exception>(testExpressionOne);

			testFooLHS = testFooRHS;

			Assert::IsTrue(testFooLHS[testFooLHS.AuxiliaryBegin()] == testFooRHS[testFooRHS.AuxiliaryBegin()]);
			Assert::IsTrue(testFooLHS[testFooLHS.AuxiliaryBegin() + 1] == testFooRHS[testFooRHS.AuxiliaryBegin() + 1]);
		}

		TEST_METHOD(AttributedMoveConstructor)
		{
			AttributedFoo testFooRHS;

			Datum* firstAuxiliary = &testFooRHS.AppendAuxiliaryAttribute("auxiliary one");
			Datum* secondAuxiliary = &testFooRHS.AppendAuxiliaryAttribute("auxiliary two");

			Assert::IsTrue(*firstAuxiliary == testFooRHS[testFooRHS.AuxiliaryBegin()]);
			Assert::IsTrue(*secondAuxiliary == testFooRHS[testFooRHS.AuxiliaryBegin() + 1]);

			Datum RHSAuxiliaryFirst = testFooRHS[testFooRHS.AuxiliaryBegin()];
			Datum RHSAuxiliarySecond = testFooRHS[testFooRHS.AuxiliaryBegin() + 1];

			AttributedFoo testFooLHS(std::move(testFooRHS));
			Assert::IsTrue(testFooLHS[testFooLHS.AuxiliaryBegin()] == RHSAuxiliaryFirst);
			Assert::IsTrue(testFooLHS[testFooLHS.AuxiliaryBegin() + 1] == RHSAuxiliarySecond);
		}

		TEST_METHOD(AttributedMoveAssignmentOperator)
		{
			AttributedFoo testFooRHS;
			AttributedFoo testFooLHS;

			Datum* firstAuxiliary = &testFooRHS.AppendAuxiliaryAttribute("auxiliary one");
			Datum* secondAuxiliary = &testFooRHS.AppendAuxiliaryAttribute("auxiliary two");

			Assert::IsTrue(*firstAuxiliary == testFooRHS[testFooRHS.AuxiliaryBegin()]);
			Assert::IsTrue(*secondAuxiliary == testFooRHS[testFooRHS.AuxiliaryBegin() + 1]);

			auto testExpressionOne = [&testFooLHS] {testFooLHS[testFooLHS.AuxiliaryBegin()]; };
			Assert::ExpectException<std::exception>(testExpressionOne);

			Datum RHSAuxiliaryFirst = testFooRHS[testFooRHS.AuxiliaryBegin()];
			Datum RHSAuxiliarySecond = testFooRHS[testFooRHS.AuxiliaryBegin() + 1];

			testFooLHS = std::move(testFooRHS);

			Assert::IsTrue(testFooLHS[testFooLHS.AuxiliaryBegin()] == RHSAuxiliaryFirst);
			Assert::IsTrue(testFooLHS[testFooLHS.AuxiliaryBegin() + 1] == RHSAuxiliarySecond);
		}

		TEST_METHOD(AttributedIsAttribute)
		{
			AttributedFoo testFoo;

			testFoo.AppendAuxiliaryAttribute("auxiliary one");
			testFoo.AppendAuxiliaryAttribute("auxiliary two");

			Assert::IsTrue(testFoo.IsAttribute("auxiliary one"));
			Assert::IsTrue(testFoo.IsAttribute("auxiliary two"));

			Assert::IsTrue(testFoo.IsAttribute("int"));
			Assert::IsTrue(testFoo.IsAttribute("float"));
			Assert::IsTrue(testFoo.IsAttribute("string"));
			Assert::IsTrue(testFoo.IsAttribute("vector"));
			Assert::IsTrue(testFoo.IsAttribute("matrix"));
			Assert::IsTrue(testFoo.IsAttribute("scope"));

			Assert::IsTrue(testFoo.IsAttribute("external int"));
			Assert::IsTrue(testFoo.IsAttribute("external float"));
			Assert::IsTrue(testFoo.IsAttribute("external string"));
			Assert::IsTrue(testFoo.IsAttribute("external vector"));
			Assert::IsTrue(testFoo.IsAttribute("external matrix"));
			Assert::IsTrue(testFoo.IsAttribute("adopted scope"));

			Assert::IsFalse(testFoo.IsAttribute("hi"));

			const AttributedFoo constTestFoo(testFoo);

			Assert::IsTrue(constTestFoo.IsAttribute("auxiliary one"));
			Assert::IsTrue(constTestFoo.IsAttribute("auxiliary two"));

			Assert::IsTrue(constTestFoo.IsAttribute("int"));
			Assert::IsTrue(constTestFoo.IsAttribute("float"));
			Assert::IsTrue(constTestFoo.IsAttribute("string"));
			Assert::IsTrue(constTestFoo.IsAttribute("vector"));
			Assert::IsTrue(constTestFoo.IsAttribute("matrix"));
			Assert::IsTrue(constTestFoo.IsAttribute("scope"));

			Assert::IsTrue(constTestFoo.IsAttribute("external int"));
			Assert::IsTrue(constTestFoo.IsAttribute("external float"));
			Assert::IsTrue(constTestFoo.IsAttribute("external string"));
			Assert::IsTrue(constTestFoo.IsAttribute("external vector"));
			Assert::IsTrue(constTestFoo.IsAttribute("external matrix"));
			Assert::IsTrue(constTestFoo.IsAttribute("adopted scope"));

			Assert::IsFalse(constTestFoo.IsAttribute("hi"));
		}

		TEST_METHOD(AttributedIsPrescribedAttribute)
		{
			AttributedFoo testFoo;

			Assert::IsTrue(testFoo.IsPrescribedAttribute("int"));
			Assert::IsTrue(testFoo.IsPrescribedAttribute("float"));
			Assert::IsTrue(testFoo.IsPrescribedAttribute("string"));
			Assert::IsTrue(testFoo.IsPrescribedAttribute("vector"));
			Assert::IsTrue(testFoo.IsPrescribedAttribute("matrix"));
			Assert::IsTrue(testFoo.IsPrescribedAttribute("scope"));

			Assert::IsTrue(testFoo.IsPrescribedAttribute("external int"));
			Assert::IsTrue(testFoo.IsPrescribedAttribute("external float"));
			Assert::IsTrue(testFoo.IsPrescribedAttribute("external string"));
			Assert::IsTrue(testFoo.IsPrescribedAttribute("external vector"));
			Assert::IsTrue(testFoo.IsPrescribedAttribute("external matrix"));
			Assert::IsTrue(testFoo.IsPrescribedAttribute("adopted scope"));

			Assert::IsFalse(testFoo.IsPrescribedAttribute("hi"));

			const AttributedFoo constTestFoo(testFoo);

			Assert::IsTrue(constTestFoo.IsPrescribedAttribute("int"));
			Assert::IsTrue(constTestFoo.IsPrescribedAttribute("float"));
			Assert::IsTrue(constTestFoo.IsPrescribedAttribute("string"));
			Assert::IsTrue(constTestFoo.IsPrescribedAttribute("vector"));
			Assert::IsTrue(constTestFoo.IsPrescribedAttribute("matrix"));
			Assert::IsTrue(constTestFoo.IsPrescribedAttribute("scope"));

			Assert::IsTrue(constTestFoo.IsPrescribedAttribute("external int"));
			Assert::IsTrue(constTestFoo.IsPrescribedAttribute("external float"));
			Assert::IsTrue(constTestFoo.IsPrescribedAttribute("external string"));
			Assert::IsTrue(constTestFoo.IsPrescribedAttribute("external vector"));
			Assert::IsTrue(constTestFoo.IsPrescribedAttribute("external matrix"));
			Assert::IsTrue(constTestFoo.IsPrescribedAttribute("adopted scope"));

			Assert::IsFalse(constTestFoo.IsPrescribedAttribute("hi"));
		}

		TEST_METHOD(AttributedIsAuxiliaryAttribute)
		{
			AttributedFoo testFoo;

			testFoo.AppendAuxiliaryAttribute("auxiliary one");
			testFoo.AppendAuxiliaryAttribute("auxiliary two");

			Assert::IsTrue(testFoo.IsAuxiliaryAttribute("auxiliary one"));
			Assert::IsTrue(testFoo.IsAuxiliaryAttribute("auxiliary two"));

			Assert::IsFalse(testFoo.IsAuxiliaryAttribute("int"));
			Assert::IsFalse(testFoo.IsAuxiliaryAttribute("float"));
			Assert::IsFalse(testFoo.IsAuxiliaryAttribute("string"));
			Assert::IsFalse(testFoo.IsAuxiliaryAttribute("vector"));
			Assert::IsFalse(testFoo.IsAuxiliaryAttribute("matrix"));
			Assert::IsFalse(testFoo.IsAuxiliaryAttribute("scope"));

			Assert::IsFalse(testFoo.IsAuxiliaryAttribute("external int"));
			Assert::IsFalse(testFoo.IsAuxiliaryAttribute("external float"));
			Assert::IsFalse(testFoo.IsAuxiliaryAttribute("external string"));
			Assert::IsFalse(testFoo.IsAuxiliaryAttribute("external vector"));
			Assert::IsFalse(testFoo.IsAuxiliaryAttribute("external matrix"));
			Assert::IsFalse(testFoo.IsAuxiliaryAttribute("adopted scope"));

			Assert::IsFalse(testFoo.IsAuxiliaryAttribute("hi"));

			const AttributedFoo constTestFoo(testFoo);

			Assert::IsTrue(constTestFoo.IsAuxiliaryAttribute("auxiliary one"));
			Assert::IsTrue(constTestFoo.IsAuxiliaryAttribute("auxiliary two"));

			Assert::IsFalse(constTestFoo.IsAuxiliaryAttribute("int"));
			Assert::IsFalse(constTestFoo.IsAuxiliaryAttribute("float"));
			Assert::IsFalse(constTestFoo.IsAuxiliaryAttribute("string"));
			Assert::IsFalse(constTestFoo.IsAuxiliaryAttribute("vector"));
			Assert::IsFalse(constTestFoo.IsAuxiliaryAttribute("matrix"));
			Assert::IsFalse(constTestFoo.IsAuxiliaryAttribute("scope"));

			Assert::IsFalse(constTestFoo.IsAuxiliaryAttribute("external int"));
			Assert::IsFalse(constTestFoo.IsAuxiliaryAttribute("external float"));
			Assert::IsFalse(constTestFoo.IsAuxiliaryAttribute("external string"));
			Assert::IsFalse(constTestFoo.IsAuxiliaryAttribute("external vector"));
			Assert::IsFalse(constTestFoo.IsAuxiliaryAttribute("external matrix"));
			Assert::IsFalse(constTestFoo.IsAuxiliaryAttribute("adopted scope"));

			Assert::IsFalse(constTestFoo.IsAuxiliaryAttribute("hi"));
		}

		TEST_METHOD(AttributedAppendAuxiliaryAttribute)
		{
			AttributedFoo testFoo;
			
			Datum* firstAuxiliary = &testFoo.AppendAuxiliaryAttribute("auxiliary one");
			Datum* secondAuxiliary = &testFoo.AppendAuxiliaryAttribute("auxiliary two");

			//test for exception thrown
			auto testExpressionOne = [&testFoo] {testFoo.AppendAuxiliaryAttribute("int"); };
			Assert::ExpectException<std::exception>(testExpressionOne);
			auto testExpressionTwo = [&testFoo] {testFoo.AppendAuxiliaryAttribute("external int"); };
			Assert::ExpectException<std::exception>(testExpressionTwo);

			//test if attribute
			Assert::IsTrue(testFoo.IsAttribute("auxiliary one"));
			Assert::IsTrue(testFoo.IsAttribute("auxiliary two"));
			//test if prescribed
			Assert::IsFalse(testFoo.IsPrescribedAttribute("auxiliary one"));
			Assert::IsFalse(testFoo.IsPrescribedAttribute("auxiliary two"));
			//test if auxiliary
			Assert::IsTrue(testFoo.IsAuxiliaryAttribute("auxiliary one"));
			Assert::IsTrue(testFoo.IsAuxiliaryAttribute("auxiliary two"));

			Assert::IsTrue(*firstAuxiliary == testFoo[testFoo.AuxiliaryBegin()]);
			Assert::IsTrue(*secondAuxiliary == testFoo[testFoo.AuxiliaryBegin() + 1]);
		}

		TEST_METHOD(AttributedAuxiliaryBegin)
		{
			AttributedFoo testFoo;
			std::uint32_t prescribedAmount = 12;

			Assert::AreEqual(prescribedAmount + 1, testFoo.AuxiliaryBegin());

			Datum* firstAuxiliary = &testFoo.AppendAuxiliaryAttribute("auxiliary one");
			Datum* secondAuxiliary = &testFoo.AppendAuxiliaryAttribute("auxiliary two");

			Assert::AreEqual(prescribedAmount + 1, testFoo.AuxiliaryBegin());

			Assert::IsTrue(*firstAuxiliary == testFoo[testFoo.AuxiliaryBegin()]);
			Assert::IsTrue(*secondAuxiliary == testFoo[testFoo.AuxiliaryBegin() + 1]);

			const AttributedFoo constTestFoo(testFoo);

			Assert::AreEqual(prescribedAmount + 1, constTestFoo.AuxiliaryBegin());

			Assert::IsTrue(*firstAuxiliary == constTestFoo[testFoo.AuxiliaryBegin()]);
			Assert::IsTrue(*secondAuxiliary == constTestFoo[testFoo.AuxiliaryBegin() + 1]);
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

	_CrtMemState AttributedTest::sStartMemState;
}