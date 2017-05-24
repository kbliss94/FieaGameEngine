#include "pch.h"
#include "CppUnitTest.h"
#include "Datum.h"
#include "Scope.h"
#include "TestFoo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Foo);

	TEST_CLASS(DatumTest)
	{
	public:
		const std::uint32_t bigSize = 20;
		const std::uint32_t smallSize = 10;

		std::int32_t testInt = 1;
		std::int32_t testIntTwo = 2;
		std::float_t testFloat = 1.1f;
		std::float_t testFloatTwo = 2.2f;
		std::string testString = "k";
		std::string testStringTwo = "b";
		glm::vec4 testVector = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 testVectorTwo = glm::vec4(2.0f, 2.0f, 2.0f, 2.0f);
		glm::mat4 testMatrix = glm::mat4(1.0f);
		glm::mat4 testMatrixTwo = glm::mat4(2.0f);
		Foo testFoo;
		Foo* testPtr = &testFoo;
		Foo testFooTwo;
		Foo* testPtrTwo = &testFooTwo;
		Scope testScope;
		Scope testScopeTwo;

		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD(DatumDefaultConstructor)
		{
			Datum k;

			Assert::IsTrue(DatumType::Unknown == k.Type());
			Assert::IsTrue(0 == k.Size());
		}

		TEST_METHOD(DatumCopyConstructor)
		{
			testPtr->Data(testInt);

			Datum intDatum;
			Datum floatDatum;
			Datum stringDatum;
			Datum vectorDatum;
			Datum matrixDatum;
			Datum ptrDatum;

			intDatum.Set(testInt);
			floatDatum.Set(testFloat);
			stringDatum.Set(testString);
			vectorDatum.Set(testVector);
			matrixDatum.Set(testMatrix);
			ptrDatum.Set(testPtr);

			Datum intDatumTwo(intDatum);
			Datum floatDatumTwo(floatDatum);
			Datum stringDatumTwo(stringDatum);
			Datum vectorDatumTwo(vectorDatum);
			Datum matrixDatumTwo(matrixDatum);
			Datum ptrDatumTwo(ptrDatum);

			const Datum constIntDatum(intDatum);
			const Datum constFloatDatum(floatDatum);
			const Datum constStringDatum(stringDatum);
			const Datum constVectorDatum(vectorDatum);
			const Datum constMatrixDatum(matrixDatum);
			const Datum constPtrDatum(ptrDatum);

			Assert::IsTrue(intDatum.Size() == intDatumTwo.Size());
			Assert::IsTrue(intDatum.Type() == intDatumTwo.Type());
			Assert::IsTrue(intDatum.Get<std::int32_t&>() == intDatumTwo.Get<std::int32_t&>());

			Assert::IsTrue(floatDatum.Size() == floatDatumTwo.Size());
			Assert::IsTrue(floatDatum.Type() == floatDatumTwo.Type());
			Assert::IsTrue(floatDatum.Get<std::float_t&>() == floatDatumTwo.Get<std::float_t&>());

			Assert::IsTrue(stringDatum.Size() == stringDatumTwo.Size());
			Assert::IsTrue(stringDatum.Type() == stringDatumTwo.Type());
			Assert::IsTrue(stringDatum.Get<std::string&>() == stringDatumTwo.Get<std::string&>());

			Assert::IsTrue(vectorDatum.Size() == vectorDatumTwo.Size());
			Assert::IsTrue(vectorDatum.Type() == vectorDatumTwo.Type());
			Assert::IsTrue(vectorDatum.Get<glm::vec4&>() == vectorDatumTwo.Get<glm::vec4&>());

			Assert::IsTrue(matrixDatum.Size() == matrixDatumTwo.Size());
			Assert::IsTrue(matrixDatum.Type() == matrixDatumTwo.Type());
			Assert::IsTrue(matrixDatum.Get<glm::mat4&>() == matrixDatumTwo.Get<glm::mat4&>());

			Assert::IsTrue(ptrDatum.Size() == ptrDatumTwo.Size());
			Assert::IsTrue(ptrDatum.Type() == ptrDatumTwo.Type());
			Assert::IsTrue(ptrDatum.Get<Library::RTTI*&>() == ptrDatumTwo.Get<Library::RTTI*&>());

			//Const datum tests

			Assert::IsTrue(intDatum.Size() == constIntDatum.Size());
			Assert::IsTrue(intDatum.Type() == constIntDatum.Type());
			Assert::IsTrue(intDatum.Get<std::int32_t&>() == constIntDatum.Get<const std::int32_t&>());

			Assert::IsTrue(floatDatum.Size() == constFloatDatum.Size());
			Assert::IsTrue(floatDatum.Type() == constFloatDatum.Type());
			Assert::IsTrue(floatDatum.Get<std::float_t&>() == constFloatDatum.Get<const std::float_t&>());

			Assert::IsTrue(stringDatum.Size() == constStringDatum.Size());
			Assert::IsTrue(stringDatum.Type() == constStringDatum.Type());
			Assert::IsTrue(stringDatum.Get<std::string&>() == constStringDatum.Get<const std::string&>());

			Assert::IsTrue(vectorDatum.Size() == constVectorDatum.Size());
			Assert::IsTrue(vectorDatum.Type() == constVectorDatum.Type());
			Assert::IsTrue(vectorDatum.Get<glm::vec4&>() == constVectorDatum.Get<const glm::vec4&>());

			Assert::IsTrue(matrixDatum.Size() == constMatrixDatum.Size());
			Assert::IsTrue(matrixDatum.Type() == constMatrixDatum.Type());
			Assert::IsTrue(matrixDatum.Get<glm::mat4&>() == constMatrixDatum.Get<const glm::mat4&>());

			Assert::IsTrue(ptrDatum.Size() == constPtrDatum.Size());
			Assert::IsTrue(ptrDatum.Type() == constPtrDatum.Type());
			Assert::IsTrue(ptrDatum.Get<Library::RTTI*&>() == constPtrDatum.Get<const Library::RTTI*&>());
		}

		TEST_METHOD(DatumAssignmentOperator)
		{
			testPtr->Data(testInt);
			testPtrTwo->Data(testIntTwo);

			Datum intDatum;
			Datum floatDatum;
			Datum stringDatum;
			Datum vectorDatum;
			Datum matrixDatum;
			Datum ptrDatum;
			Datum tableDatum;

			intDatum.SetType(DatumType::Integer);
			floatDatum.SetType(DatumType::Float);
			stringDatum.SetType(DatumType::String);
			vectorDatum.SetType(DatumType::Vector);
			matrixDatum.SetType(DatumType::Matrix);
			ptrDatum.SetType(DatumType::Pointer);
			tableDatum.SetType(DatumType::Table);

			intDatum.SetSize(smallSize);
			floatDatum.SetSize(smallSize);
			stringDatum.SetSize(smallSize);
			vectorDatum.SetSize(smallSize);
			matrixDatum.SetSize(smallSize);
			ptrDatum.SetSize(1);
			tableDatum.SetSize(smallSize);

			intDatum.Set(testInt);
			floatDatum.Set(testFloat);
			stringDatum.Set(testString);
			vectorDatum.Set(testVector);
			matrixDatum.Set(testMatrix);
			ptrDatum.Set(testPtr);
			tableDatum.Set(testScope);

			Datum intDatumTwo;
			Datum floatDatumTwo;
			Datum stringDatumTwo;
			Datum vectorDatumTwo;
			Datum matrixDatumTwo;
			Datum ptrDatumTwo;
			Datum tableDatumTwo;

			//assigning an internal datum to another internal datum

			intDatumTwo = intDatum;
			floatDatumTwo = floatDatum;
			stringDatumTwo = stringDatum;
			vectorDatumTwo = vectorDatum;
			matrixDatumTwo = matrixDatum;
			ptrDatumTwo = ptrDatum;
			tableDatumTwo = tableDatum;

			Assert::IsTrue(intDatum.Size() == intDatumTwo.Size());
			Assert::IsTrue(intDatum.Type() == intDatumTwo.Type());
			Assert::IsTrue(intDatum.Get<std::int32_t&>() == intDatumTwo.Get<std::int32_t&>());

			Assert::IsTrue(floatDatum.Size() == floatDatumTwo.Size());
			Assert::IsTrue(floatDatum.Type() == floatDatumTwo.Type());
			Assert::IsTrue(floatDatum.Get<std::float_t&>() == floatDatumTwo.Get<std::float_t&>());

			Assert::IsTrue(stringDatum.Size() == stringDatumTwo.Size());
			Assert::IsTrue(stringDatum.Type() == stringDatumTwo.Type());
			Assert::IsTrue(stringDatum.Get<std::string&>() == stringDatumTwo.Get<std::string&>());

			Assert::IsTrue(vectorDatum.Size() == vectorDatumTwo.Size());
			Assert::IsTrue(vectorDatum.Type() == vectorDatumTwo.Type());
			Assert::IsTrue(vectorDatum.Get<glm::vec4&>() == vectorDatumTwo.Get<glm::vec4&>());

			Assert::IsTrue(matrixDatum.Size() == matrixDatumTwo.Size());
			Assert::IsTrue(matrixDatum.Type() == matrixDatumTwo.Type());
			Assert::IsTrue(matrixDatum.Get<glm::mat4&>() == matrixDatumTwo.Get<glm::mat4&>());

			Assert::IsTrue(ptrDatum.Size() == ptrDatumTwo.Size());
			Assert::IsTrue(ptrDatum.Type() == ptrDatumTwo.Type());
			Assert::IsTrue(ptrDatum.Get<Library::RTTI*&>() == ptrDatumTwo.Get<Library::RTTI*&>());

			Assert::IsTrue(tableDatum.Size() == tableDatumTwo.Size());
			Assert::IsTrue(tableDatum.Type() == tableDatumTwo.Type());
			Assert::IsTrue(tableDatum.Get<Scope&>() == tableDatumTwo.Get<Scope&>());

			auto testExpression = [&intDatumTwo, &vectorDatum] {intDatumTwo = vectorDatum; };
			Assert::ExpectException<std::exception>(testExpression);

			static const std::uint32_t arraySize = 5;
			std::int32_t intArray[arraySize] = { 1, 2, 3, 4, 5 };
			std::float_t floatArray[arraySize] = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f };
			std::string stringArray[arraySize] = { "how", "are", "you", "doing" , "today" };
			glm::vec4 vectorArray[arraySize] = { testVector, testVector, testVector, testVector, testVector };
			glm::mat4 matrixArray[arraySize] = { testMatrix, testMatrix, testMatrix, testMatrix, testMatrix };
			Library::RTTI* ptrArray[arraySize] = { testPtr, testPtr, testPtr, testPtr, testPtr };

			std::int32_t intArrayTwo[arraySize] = { 4, 6, 3, 4, 5 };
			std::float_t floatArrayTwo[arraySize] = { 1.6f, 2.2f, 3.3f, 4.4f, 5.5f };
			std::string stringArrayTwo[arraySize] = { "bye", "are", "you", "doing" , "today" };
			glm::vec4 vectorArrayTwo[arraySize] = { testVector, testVector, testVector, testVector, testVector };
			glm::mat4 matrixArrayTwo[arraySize] = { testMatrix, testMatrix, testMatrix, testMatrix, testMatrix };
			Library::RTTI* ptrArrayTwo[arraySize] = { testPtrTwo, testPtrTwo, testPtrTwo, testPtrTwo, testPtrTwo };

			Datum intDatumFour;
			Datum floatDatumFour;
			Datum stringDatumFour;
			Datum vectorDatumFour;
			Datum matrixDatumFour;
			Datum ptrDatumFour;

			intDatumFour.SetStorage(intArray, arraySize);
			floatDatumFour.SetStorage(floatArray, arraySize);
			stringDatumFour.SetStorage(stringArray, arraySize);
			vectorDatumFour.SetStorage(vectorArray, arraySize);
			matrixDatumFour.SetStorage(matrixArray, arraySize);
			ptrDatumFour.SetStorage(ptrArray, arraySize);

			Datum intDatumFive;
			Datum floatDatumFive;
			Datum stringDatumFive;
			Datum vectorDatumFive;
			Datum matrixDatumFive;
			Datum ptrDatumFive;

			//assigning empty datum with internal storage to one with external storage

			intDatumFive = intDatumFour;
			floatDatumFive = floatDatumFour;
			stringDatumFive = stringDatumFour;
			vectorDatumFive = vectorDatumFour;
			matrixDatumFive = matrixDatumFour;
			ptrDatumFive = ptrDatumFour;

			auto testExpressionTwo = [&intDatum, &intDatumFour] {intDatum = intDatumFour; };
			Assert::ExpectException<std::exception>(testExpressionTwo);

			Datum intDatumSix;
			Datum floatDatumSix;
			Datum stringDatumSix;
			Datum vectorDatumSix;
			Datum matrixDatumSix;
			Datum ptrDatumSix;

			intDatumSix.SetStorage(intArrayTwo, arraySize);
			floatDatumSix.SetStorage(floatArrayTwo, arraySize);
			stringDatumSix.SetStorage(stringArrayTwo, arraySize);
			vectorDatumSix.SetStorage(vectorArrayTwo, arraySize);
			matrixDatumSix.SetStorage(matrixArrayTwo, arraySize);
			ptrDatumSix.SetStorage(ptrArrayTwo, arraySize);

			//assigning an initialized external datum to another external datum

			intDatumFour = intDatumSix;
			floatDatumFour = floatDatumSix;
			stringDatumFour = stringDatumSix;
			vectorDatumFour = vectorDatumSix;
			matrixDatumFour = matrixDatumSix;
			ptrDatumFour = ptrDatumSix;

			Assert::IsTrue(intDatumFour == intDatumSix);
			Assert::IsTrue(floatDatumFour == floatDatumSix);
			Assert::IsTrue(stringDatumFour == stringDatumSix);
			Assert::IsTrue(vectorDatumFour == vectorDatumSix);
			Assert::IsTrue(matrixDatumFour == matrixDatumSix);
			Assert::IsTrue(ptrDatumFour == ptrDatumSix);

			//assigning an initialized external datum to an initialized internal datum

			intDatumFour = intDatum;
			floatDatumFour = floatDatum;
			stringDatumFour = stringDatum;
			vectorDatumFour = vectorDatum;
			matrixDatumFour = matrixDatum;
			ptrDatumFour = ptrDatum;

			Assert::IsTrue(intDatumFour == intDatum);
			Assert::IsTrue(floatDatumFour == floatDatum);
			Assert::IsTrue(stringDatumFour == stringDatum);
			Assert::IsTrue(vectorDatumFour == vectorDatum);
			Assert::IsTrue(matrixDatumFour == matrixDatum);
			Assert::IsTrue(ptrDatumFour == ptrDatum);

			//Scalar operator= tests

			Datum intDatumThree;
			Datum floatDatumThree;
			Datum stringDatumThree;
			Datum vectorDatumThree;
			Datum matrixDatumThree;
			Datum ptrDatumThree;

			intDatumTwo = testIntTwo;
			intDatumThree = testIntTwo;

			Assert::IsTrue(intDatumTwo.Size() == 1);
			Assert::IsTrue(intDatumTwo.Get<std::int32_t&>() == testIntTwo);
			Assert::IsTrue(intDatumThree.Size() == 1);
			Assert::IsTrue(intDatumThree.Type() == DatumType::Integer);
			Assert::IsTrue(intDatumThree.Get<std::int32_t&>() == testIntTwo);

			floatDatumTwo = testFloatTwo;
			floatDatumThree = testFloatTwo;

			Assert::IsTrue(floatDatumTwo.Size() == 1);
			Assert::IsTrue(floatDatumTwo.Get<std::float_t&>() == testFloatTwo);
			Assert::IsTrue(floatDatumThree.Size() == 1);
			Assert::IsTrue(floatDatumThree.Type() == DatumType::Float);
			Assert::IsTrue(floatDatumThree.Get<std::float_t&>() == testFloatTwo);

			stringDatumTwo = testStringTwo;
			stringDatumThree = testStringTwo;

			Assert::IsTrue(stringDatumTwo.Size() == 1);
			Assert::IsTrue(stringDatumTwo.Get<std::string&>() == testStringTwo);
			Assert::IsTrue(stringDatumThree.Size() == 1);
			Assert::IsTrue(stringDatumThree.Type() == DatumType::String);
			Assert::IsTrue(stringDatumThree.Get<std::string&>() == testStringTwo);

			vectorDatumTwo = testVectorTwo;
			vectorDatumThree = testVectorTwo;

			Assert::IsTrue(vectorDatumTwo.Size() == 1);
			Assert::IsTrue(vectorDatumTwo.Get<glm::vec4&>() == testVectorTwo);
			Assert::IsTrue(vectorDatumThree.Size() == 1);
			Assert::IsTrue(vectorDatumThree.Type() == DatumType::Vector);
			Assert::IsTrue(vectorDatumThree.Get<glm::vec4&>() == testVectorTwo);

			matrixDatumTwo = testMatrixTwo;
			matrixDatumThree = testMatrixTwo;

			Assert::IsTrue(matrixDatumTwo.Size() == 1);
			Assert::IsTrue(matrixDatumTwo.Get<glm::mat4&>() == testMatrixTwo);
			Assert::IsTrue(matrixDatumThree.Size() == 1);
			Assert::IsTrue(matrixDatumThree.Type() == DatumType::Matrix);
			Assert::IsTrue(matrixDatumThree.Get<glm::mat4&>() == testMatrixTwo);

			Library::RTTI* testRttiPtr = testPtr;

			ptrDatumTwo = testRttiPtr;
			ptrDatumThree = testRttiPtr;

			Assert::IsTrue(ptrDatumTwo.Size() == 1);
			Assert::IsTrue(ptrDatumTwo.Get<Library::RTTI*&>() == testRttiPtr);
			Assert::IsTrue(ptrDatumThree.Size() == 1);
			Assert::IsTrue(ptrDatumThree.Type() == DatumType::Pointer);
			Assert::IsTrue(ptrDatumThree.Get<Library::RTTI*&>() == testRttiPtr);

			auto intExpression = [&intDatumThree] {intDatumThree = 5.0f; };
			Assert::ExpectException<std::exception>(intExpression);

			auto floatExpression = [&floatDatumThree] {floatDatumThree = 5; };
			Assert::ExpectException<std::exception>(floatExpression);

			auto stringExpression = [&stringDatumThree] {stringDatumThree = 5; };
			Assert::ExpectException<std::exception>(stringExpression);

			auto vectorExpression = [&vectorDatumThree] {vectorDatumThree = 5; };
			Assert::ExpectException<std::exception>(vectorExpression);

			auto matrixExpression = [&matrixDatumThree] {matrixDatumThree = 5; };
			Assert::ExpectException<std::exception>(matrixExpression);

			auto ptrExpression = [&ptrDatumThree] {ptrDatumThree = 5; };
			Assert::ExpectException<std::exception>(ptrExpression);
		}

		TEST_METHOD(DatumBracketOperator)
		{
			Datum tableDatum;

			Scope scopeOne;
			Scope scopeTwo;
			Scope scopeThree;

			tableDatum.Set(scopeOne, 0);
			tableDatum.Set(scopeTwo, 1);
			tableDatum.Set(scopeThree, 2);

			Assert::IsTrue(scopeOne == tableDatum[0]);
			Assert::IsTrue(scopeTwo == tableDatum[1]);
			Assert::IsTrue(scopeThree == tableDatum[2]);
		}

		TEST_METHOD(DatumSetType)
		{
			Datum intDatum;
			Datum floatDatum;
			Datum stringDatum;
			Datum vectorDatum;
			Datum matrixDatum;
			Datum ptrDatum;

			Assert::IsTrue(DatumType::Unknown == intDatum.Type());
			Assert::IsTrue(DatumType::Unknown == floatDatum.Type());
			Assert::IsTrue(DatumType::Unknown == stringDatum.Type());
			Assert::IsTrue(DatumType::Unknown == vectorDatum.Type());
			Assert::IsTrue(DatumType::Unknown == matrixDatum.Type());
			Assert::IsTrue(DatumType::Unknown == ptrDatum.Type());

			intDatum.SetType(DatumType::Integer);
			floatDatum.SetType(DatumType::Float);
			stringDatum.SetType(DatumType::String);
			vectorDatum.SetType(DatumType::Vector);
			matrixDatum.SetType(DatumType::Matrix);
			ptrDatum.SetType(DatumType::Pointer);

			Assert::IsTrue(DatumType::Integer == intDatum.Type());
			Assert::IsTrue(DatumType::Float == floatDatum.Type());
			Assert::IsTrue(DatumType::String == stringDatum.Type());
			Assert::IsTrue(DatumType::Vector == vectorDatum.Type());
			Assert::IsTrue(DatumType::Matrix == matrixDatum.Type());
			Assert::IsTrue(DatumType::Pointer == ptrDatum.Type());

			Datum k;

			k.SetType(DatumType::Integer);

			auto kExpressionOne = [&k] {k.SetType(DatumType::Float); };
			Assert::ExpectException<std::exception>(kExpressionOne);

			auto kExpressionTwo = [&k] {k.SetType(DatumType::String); };
			Assert::ExpectException<std::exception>(kExpressionTwo);

			auto kExpressionThree = [&k] {k.SetType(DatumType::Vector); };
			Assert::ExpectException<std::exception>(kExpressionThree);

			auto kExpressionFour = [&k] {k.SetType(DatumType::Matrix); };
			Assert::ExpectException<std::exception>(kExpressionFour);

			auto kExpressionFive = [&k] {k.SetType(DatumType::Pointer); };
			Assert::ExpectException<std::exception>(kExpressionFive);

			Datum t;
			t.SetType(DatumType::Float);

			auto tExpression = [&t] {t.SetType(DatumType::Integer); };
			Assert::ExpectException<std::exception>(tExpression);
		}

		TEST_METHOD(DatumSetSize)
		{
			Datum intDatum;
			Datum floatDatum;
			Datum stringDatum;
			Datum vectorDatum;
			Datum matrixDatum;
			Datum ptrDatum;

			Assert::IsTrue(0 == intDatum.Size());
			Assert::IsTrue(0 == floatDatum.Size());
			Assert::IsTrue(0 == stringDatum.Size());
			Assert::IsTrue(0 == vectorDatum.Size());
			Assert::IsTrue(0 == matrixDatum.Size());
			Assert::IsTrue(0 == ptrDatum.Size());

			intDatum.SetSize(bigSize);
			floatDatum.SetSize(bigSize);
			stringDatum.SetSize(bigSize);
			vectorDatum.SetSize(bigSize);
			matrixDatum.SetSize(bigSize);
			ptrDatum.SetSize(bigSize);

			Assert::IsTrue(bigSize == intDatum.Size());
			Assert::IsTrue(bigSize == floatDatum.Size());
			Assert::IsTrue(bigSize == stringDatum.Size());
			Assert::IsTrue(bigSize == vectorDatum.Size());
			Assert::IsTrue(bigSize == matrixDatum.Size());
			Assert::IsTrue(bigSize == ptrDatum.Size());

			intDatum.SetSize(smallSize);
			floatDatum.SetSize(smallSize);
			stringDatum.SetSize(smallSize);
			vectorDatum.SetSize(smallSize);
			matrixDatum.SetSize(smallSize);
			ptrDatum.SetSize(smallSize);

			Assert::IsTrue(smallSize == intDatum.Size());
			Assert::IsTrue(smallSize == floatDatum.Size());
			Assert::IsTrue(smallSize == stringDatum.Size());
			Assert::IsTrue(smallSize == vectorDatum.Size());
			Assert::IsTrue(smallSize == matrixDatum.Size());
			Assert::IsTrue(smallSize == ptrDatum.Size());

			Datum intDatumTwo;
			Datum floatDatumTwo;
			Datum stringDatumTwo;
			Datum vectorDatumTwo;
			Datum matrixDatumTwo;
			Datum ptrDatumTwo;

			static const std::uint32_t arraySize = 5;
			std::int32_t intArray[arraySize] = { 1, 2, 3, 4, 5 };
			std::float_t floatArray[arraySize] = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f };
			std::string stringArray[arraySize] = { "how", "are", "you", "doing" , "today" };
			glm::vec4 vectorArray[arraySize] = { testVector, testVector, testVector, testVector, testVector };
			glm::mat4 matrixArray[arraySize] = { testMatrix, testMatrix, testMatrix, testMatrix, testMatrix };
			Library::RTTI* ptrArray[arraySize] = { testPtr, testPtr , testPtr, testPtr, testPtr };

			intDatumTwo.SetStorage(intArray, arraySize);
			floatDatumTwo.SetStorage(floatArray, arraySize);
			stringDatumTwo.SetStorage(stringArray, arraySize);
			vectorDatumTwo.SetStorage(vectorArray, arraySize);
			matrixDatumTwo.SetStorage(matrixArray, arraySize);
			ptrDatumTwo.SetStorage(ptrArray, arraySize);

			std::uint32_t size = 5;

			auto intExpression = [&intDatumTwo, &size] {intDatumTwo.SetSize(size); };
			Assert::ExpectException<std::exception>(intExpression);

			auto floatExpression = [&floatDatumTwo, &size] {floatDatumTwo.SetSize(size); };
			Assert::ExpectException<std::exception>(floatExpression);

			auto stringExpression = [&stringDatumTwo, &size] {stringDatumTwo.SetSize(size); };
			Assert::ExpectException<std::exception>(stringExpression);

			auto vectorExpression = [&vectorDatumTwo, &size] {vectorDatumTwo.SetSize(size); };
			Assert::ExpectException<std::exception>(vectorExpression);

			auto matrixExpression = [&matrixDatumTwo, &size] {matrixDatumTwo.SetSize(size); };
			Assert::ExpectException<std::exception>(matrixExpression);

			auto ptrExpression = [&ptrDatumTwo, &size] {ptrDatumTwo.SetSize(size); };
			Assert::ExpectException<std::exception>(ptrExpression);
		}

		TEST_METHOD(DatumSetGet)
		{
			testPtr->Data(testInt);
			testPtrTwo->Data(testIntTwo);

			Datum intDatum;
			Datum floatDatum;
			Datum stringDatum;
			Datum vectorDatum;
			Datum matrixDatum;
			Datum ptrDatum;
			Datum tableDatum;

			intDatum.SetType(DatumType::Integer);
			floatDatum.SetType(DatumType::Float);
			stringDatum.SetType(DatumType::String);
			vectorDatum.SetType(DatumType::Vector);
			matrixDatum.SetType(DatumType::Matrix);
			ptrDatum.SetType(DatumType::Pointer);
			tableDatum.SetType(DatumType::Table);

			intDatum.SetSize(smallSize);
			floatDatum.SetSize(smallSize);
			stringDatum.SetSize(smallSize);
			vectorDatum.SetSize(smallSize);
			matrixDatum.SetSize(smallSize);
			ptrDatum.SetSize(smallSize);
			tableDatum.SetSize(smallSize);

			intDatum.Set(testInt);
			floatDatum.Set(testFloat);
			stringDatum.Set(testString);
			vectorDatum.Set(testVector);
			matrixDatum.Set(testMatrix);
			ptrDatum.Set(testPtr);
			tableDatum.Set(testScope);

			Assert::IsTrue(testInt == intDatum.Get<std::int32_t&>(0));
			Assert::IsTrue(testFloat == floatDatum.Get<std::float_t&>(0));
			Assert::IsTrue(testString == stringDatum.Get<std::string&>(0));
			Assert::IsTrue(testVector == vectorDatum.Get<glm::vec4&>(0));
			Assert::IsTrue(testMatrix == matrixDatum.Get<glm::mat4&>(0));
			Assert::IsTrue(testPtr == ptrDatum.Get<Library::RTTI*&>(0));
			Assert::IsTrue(testScope == tableDatum.Get<Scope&>(0));

			const Datum constIntDatum(intDatum);
			const Datum constFloatDatum(floatDatum);
			const Datum constStringDatum(stringDatum);
			const Datum constVectorDatum(vectorDatum);
			const Datum constMatrixDatum(matrixDatum);
			const Datum constPtrDatum(ptrDatum);
			const Datum constTableDatum(tableDatum);

			Assert::IsTrue(testInt == constIntDatum.Get<const std::int32_t&>(0));
			Assert::IsTrue(testFloat == constFloatDatum.Get<const std::float_t&>(0));
			Assert::IsTrue(testString == constStringDatum.Get<const std::string&>(0));
			Assert::IsTrue(testVector == constVectorDatum.Get<const glm::vec4&>(0));
			Assert::IsTrue(testMatrix == constMatrixDatum.Get<const glm::mat4&>(0));
			Assert::IsTrue(testPtr == constPtrDatum.Get<const Library::RTTI*&>(0));
			Assert::IsTrue(testScope == constTableDatum.Get<const Scope&>(0));

			std::int32_t testIntThree = 1;
			std::float_t testFloatThree = 1.1f;

			//Set exceptions

			auto intSetExpression = [&intDatum, &testFloatThree] {intDatum.Set(testFloatThree); };
			Assert::ExpectException<std::exception>(intSetExpression);

			auto floatSetExpression = [&floatDatum, &testIntThree] {floatDatum.Set(testIntThree); };
			Assert::ExpectException<std::exception>(floatSetExpression);

			auto stringSetExpression = [&stringDatum, &testIntThree] {stringDatum.Set(testIntThree); };
			Assert::ExpectException<std::exception>(stringSetExpression);

			auto vectorSetExpression = [&vectorDatum, &testIntThree] {vectorDatum.Set(testIntThree); };
			Assert::ExpectException<std::exception>(vectorSetExpression);

			auto matrixSetExpression = [&matrixDatum, &testIntThree] {matrixDatum.Set(testIntThree); };
			Assert::ExpectException<std::exception>(matrixSetExpression);

			auto ptrSetExpression = [&ptrDatum, &testIntThree] {ptrDatum.Set(testIntThree); };
			Assert::ExpectException<std::exception>(ptrSetExpression);

			auto tableSetExpression = [&tableDatum, &testIntThree] {tableDatum.Set(testIntThree); };
			Assert::ExpectException<std::exception>(tableSetExpression);

			//Get exceptions

			auto intGetExpression = [&intDatum] {intDatum.Get<std::float_t&>(); };
			Assert::ExpectException<std::exception>(intGetExpression);

			auto floatGetExpression = [&floatDatum] {floatDatum.Get<std::int32_t&>(); };
			Assert::ExpectException<std::exception>(floatGetExpression);

			auto stringGetExpression = [&stringDatum] {stringDatum.Get<std::float_t&>(); };
			Assert::ExpectException<std::exception>(stringGetExpression);

			auto vectorGetExpression = [&vectorDatum] {vectorDatum.Get<std::float_t&>(); };
			Assert::ExpectException<std::exception>(vectorGetExpression);

			auto matrixGetExpression = [&matrixDatum] {matrixDatum.Get<std::float_t&>(); };
			Assert::ExpectException<std::exception>(matrixGetExpression);

			auto ptrGetExpression = [&ptrDatum] {ptrDatum.Get<std::float_t&>(); };
			Assert::ExpectException<std::exception>(ptrGetExpression);

			auto tableGetExpression = [&tableDatum] {tableDatum.Get<std::float_t&>(); };
			Assert::ExpectException<std::exception>(tableGetExpression);

			auto intGetExpressionTwo = [&intDatum] {intDatum.Get<std::int32_t&>(50); };
			Assert::ExpectException<std::exception>(intGetExpressionTwo);

			auto floatGetExpressionTwo = [&floatDatum] {floatDatum.Get<std::float_t&>(50); };
			Assert::ExpectException<std::exception>(floatGetExpressionTwo);

			auto stringGetExpressionTwo = [&stringDatum] {stringDatum.Get<std::string&>(50); };
			Assert::ExpectException<std::exception>(stringGetExpressionTwo);

			auto vectorGetExpressionTwo = [&vectorDatum] {vectorDatum.Get<glm::vec4&>(50); };
			Assert::ExpectException<std::exception>(vectorGetExpressionTwo);

			auto matrixGetExpressionTwo = [&matrixDatum] {matrixDatum.Get<glm::mat4&>(50); };
			Assert::ExpectException<std::exception>(matrixGetExpressionTwo);

			auto ptrGetExpressionTwo = [&ptrDatum] {ptrDatum.Get<Library::RTTI*&>(50); };
			Assert::ExpectException<std::exception>(ptrGetExpressionTwo);

			auto tableGetExpressionTwo = [&tableDatum] {tableDatum.Get<Scope&>(50); };
			Assert::ExpectException<std::exception>(tableGetExpressionTwo);

			//Const get exceptions

			auto constIntGetExpression = [&constIntDatum] {constIntDatum.Get<const std::float_t&>(); };
			Assert::ExpectException<std::exception>(constIntGetExpression);

			auto constFloatGetExpression = [&constFloatDatum] {constFloatDatum.Get<const std::int32_t&>(); };
			Assert::ExpectException<std::exception>(constFloatGetExpression);

			auto constStringGetExpression = [&constStringDatum] {constStringDatum.Get<const std::float_t&>(); };
			Assert::ExpectException<std::exception>(constStringGetExpression);

			auto constVectorGetExpression = [&constVectorDatum] {constVectorDatum.Get<const std::float_t&>(); };
			Assert::ExpectException<std::exception>(constVectorGetExpression);

			auto constMatrixGetExpression = [&constMatrixDatum] {constMatrixDatum.Get<const std::float_t&>(); };
			Assert::ExpectException<std::exception>(constMatrixGetExpression);

			auto constPtrGetExpression = [&constPtrDatum] {constPtrDatum.Get<const std::float_t&>(); };
			Assert::ExpectException<std::exception>(constPtrGetExpression);

			auto constTableGetExpression = [&constTableDatum] {constTableDatum.Get<const std::float_t&>(); };
			Assert::ExpectException<std::exception>(constTableGetExpression);

			auto constIntGetExpressionTwo = [&constIntDatum] {constIntDatum.Get<const std::int32_t&>(50); };
			Assert::ExpectException<std::exception>(constIntGetExpressionTwo);

			auto constFloatGetExpressionTwo = [&constFloatDatum] {constFloatDatum.Get<const std::float_t&>(50); };
			Assert::ExpectException<std::exception>(constFloatGetExpressionTwo);

			auto constStringGetExpressionTwo = [&constStringDatum] {constStringDatum.Get<const std::string&>(50); };
			Assert::ExpectException<std::exception>(constStringGetExpressionTwo);

			auto constVectorGetExpressionTwo = [&constVectorDatum] {constVectorDatum.Get<const glm::vec4&>(50); };
			Assert::ExpectException<std::exception>(constVectorGetExpressionTwo);

			auto constMatrixGetExpressionTwo = [&constMatrixDatum] {constMatrixDatum.Get<const glm::mat4&>(50); };
			Assert::ExpectException<std::exception>(constMatrixGetExpressionTwo);

			auto constPtrGetExpressionTwo = [&constPtrDatum] {constPtrDatum.Get<const Library::RTTI*&>(50); };
			Assert::ExpectException<std::exception>(constPtrGetExpressionTwo);

			auto constTableGetExpressionTwo = [&constTableDatum] {constTableDatum.Get<const Scope&>(50); };
			Assert::ExpectException<std::exception>(constTableGetExpressionTwo);
		}

		TEST_METHOD(DatumComparisonOperators)
		{
			testPtr->Data(testInt);
			testPtrTwo->Data(testIntTwo);

			Datum intDatum;
			Datum floatDatum;
			Datum stringDatum;
			Datum vectorDatum;
			Datum matrixDatum;
			Datum ptrDatum;

			intDatum.SetType(DatumType::Integer);
			floatDatum.SetType(DatumType::Float);
			stringDatum.SetType(DatumType::String);
			vectorDatum.SetType(DatumType::Vector);
			matrixDatum.SetType(DatumType::Matrix);
			ptrDatum.SetType(DatumType::Pointer);

			intDatum.SetSize(smallSize);
			floatDatum.SetSize(smallSize);
			stringDatum.SetSize(smallSize);
			vectorDatum.SetSize(smallSize);
			matrixDatum.SetSize(smallSize);
			ptrDatum.SetSize(1);

			intDatum.Set(testInt);
			floatDatum.Set(testFloat);
			stringDatum.Set(testString);
			vectorDatum.Set(testVector);
			matrixDatum.Set(testMatrix);
			ptrDatum.Set(testPtr);

			Datum intDatumTwo(intDatum);
			Datum floatDatumTwo(floatDatum);
			Datum stringDatumTwo(stringDatum);
			Datum vectorDatumTwo(vectorDatum);
			Datum matrixDatumTwo(matrixDatum);
			Datum ptrDatumTwo(ptrDatum);

			const Datum constIntDatum(intDatum);
			const Datum constFloatDatum(floatDatum);
			const Datum constStringDatum(stringDatum);
			const Datum constVectorDatum(vectorDatum);
			const Datum constMatrixDatum(matrixDatum);
			const Datum constPtrDatum(ptrDatum);

			Assert::IsTrue(intDatum == intDatumTwo);
			Assert::IsTrue(floatDatum == floatDatumTwo);
			Assert::IsTrue(stringDatum == stringDatumTwo);
			Assert::IsTrue(vectorDatum == vectorDatumTwo);
			Assert::IsTrue(matrixDatum == matrixDatumTwo);
			Assert::IsTrue(ptrDatum == ptrDatumTwo);

			Assert::IsTrue(intDatum == constIntDatum);
			Assert::IsTrue(floatDatum == constFloatDatum);
			Assert::IsTrue(stringDatum == constStringDatum);
			Assert::IsTrue(vectorDatum == constVectorDatum);
			Assert::IsTrue(matrixDatum == constMatrixDatum);
			Assert::IsTrue(ptrDatum == constPtrDatum);

			Assert::IsTrue(intDatum != floatDatum);
			Assert::IsTrue(floatDatum != intDatum);
			Assert::IsTrue(stringDatum != vectorDatum);
			Assert::IsTrue(vectorDatum != stringDatum);
			Assert::IsTrue(matrixDatum != ptrDatum);
			Assert::IsTrue(ptrDatum != matrixDatum);

			Assert::IsTrue(constIntDatum != constFloatDatum);
			Assert::IsTrue(constFloatDatum != constIntDatum);
			Assert::IsTrue(constStringDatum != constIntDatum);
			Assert::IsTrue(constVectorDatum != constIntDatum);
			Assert::IsTrue(constMatrixDatum != constIntDatum);
			Assert::IsTrue(constPtrDatum != constIntDatum);

			intDatum.Set(testInt, 1);
			floatDatum.Set(testFloat, 1);
			stringDatum.Set(testString, 1);
			vectorDatum.Set(testVector, 1);
			matrixDatum.Set(testMatrix, 1);
			ptrDatum.Set(testPtr, 1);

			Assert::IsFalse(intDatum == intDatumTwo);
			Assert::IsFalse(floatDatum == floatDatumTwo);
			Assert::IsFalse(stringDatum == stringDatumTwo);
			Assert::IsFalse(vectorDatum == vectorDatumTwo);
			Assert::IsFalse(matrixDatum == matrixDatumTwo);
			Assert::IsFalse(ptrDatum == ptrDatumTwo);

			Library::RTTI* test = testPtr;

			Assert::IsFalse(intDatum == testInt);
			Assert::IsFalse(floatDatum == testFloat);
			Assert::IsFalse(stringDatum == testString);
			Assert::IsFalse(vectorDatum == testVector);
			Assert::IsFalse(matrixDatum == testMatrix);
			Assert::IsFalse(ptrDatum == test);

			Assert::IsTrue(intDatum != testInt);
			Assert::IsTrue(floatDatum != testFloat);
			Assert::IsTrue(stringDatum != testString);
			Assert::IsTrue(vectorDatum != testVector);
			Assert::IsTrue(matrixDatum != testMatrix);
			Assert::IsTrue(ptrDatum != test);
		}

		TEST_METHOD(DatumSetStorage)
		{
			testPtr->Data(testInt);
			testPtrTwo->Data(testIntTwo);

			Datum intDatum;
			Datum floatDatum;
			Datum stringDatum;
			Datum vectorDatum;
			Datum matrixDatum;
			Datum ptrDatum;

			intDatum.SetType(DatumType::Integer);
			floatDatum.SetType(DatumType::Float);
			stringDatum.SetType(DatumType::String);
			vectorDatum.SetType(DatumType::Vector);
			matrixDatum.SetType(DatumType::Matrix);
			ptrDatum.SetType(DatumType::Pointer);

			intDatum.SetSize(smallSize);
			floatDatum.SetSize(smallSize);
			stringDatum.SetSize(smallSize);
			vectorDatum.SetSize(smallSize);
			matrixDatum.SetSize(smallSize);
			ptrDatum.SetSize(smallSize);

			intDatum.Set(testInt);
			floatDatum.Set(testFloat);
			stringDatum.Set(testString);
			vectorDatum.Set(testVector);
			matrixDatum.Set(testMatrix);
			ptrDatum.Set(testPtr);

			static const std::uint32_t arraySize = 5;
			std::int32_t intArray[arraySize] = { 1, 2, 3, 4, 5 };
			std::float_t floatArray[arraySize] = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f };
			std::string stringArray[arraySize] = { "how", "are", "you", "doing" , "today" };
			glm::vec4 vectorArray[arraySize] = { testVector, testVector, testVector, testVector, testVector };
			glm::mat4 matrixArray[arraySize] = { testMatrix, testMatrix, testMatrix, testMatrix, testMatrix };
			Library::RTTI* ptrArray[arraySize] = { testPtr, testPtr , testPtr, testPtr, testPtr };

			Datum intDatumTwo;
			Datum floatDatumTwo;
			Datum stringDatumTwo;
			Datum vectorDatumTwo;
			Datum matrixDatumTwo;
			Datum ptrDatumTwo;

			intDatumTwo.SetStorage(intArray, arraySize);
			floatDatumTwo.SetStorage(floatArray, arraySize);
			stringDatumTwo.SetStorage(stringArray, arraySize);
			vectorDatumTwo.SetStorage(vectorArray, arraySize);
			matrixDatumTwo.SetStorage(matrixArray, arraySize);
			ptrDatumTwo.SetStorage(ptrArray, arraySize);

			Assert::IsTrue(intDatumTwo.Type() == DatumType::Integer);
			Assert::AreEqual(intDatumTwo.Size(), arraySize);
			Assert::IsTrue(floatDatumTwo.Type() == DatumType::Float);
			Assert::AreEqual(floatDatumTwo.Size(), arraySize);
			Assert::IsTrue(stringDatumTwo.Type() == DatumType::String);
			Assert::AreEqual(stringDatumTwo.Size(), arraySize);
			Assert::IsTrue(vectorDatumTwo.Type() == DatumType::Vector);
			Assert::AreEqual(vectorDatumTwo.Size(), arraySize);
			Assert::IsTrue(matrixDatumTwo.Type() == DatumType::Matrix);
			Assert::AreEqual(matrixDatumTwo.Size(), arraySize);
			Assert::IsTrue(ptrDatumTwo.Type() == DatumType::Pointer);
			Assert::AreEqual(ptrDatumTwo.Size(), arraySize);
		}

		TEST_METHOD(DatumSetFromString)
		{
			testPtr->Data(testInt);
			testPtrTwo->Data(testIntTwo);

			Datum intDatum;
			Datum floatDatum;
			Datum stringDatum;
			Datum vectorDatum;
			Datum matrixDatum;
			Datum ptrDatum;

			intDatum.SetType(DatumType::Integer);
			floatDatum.SetType(DatumType::Float);
			stringDatum.SetType(DatumType::String);
			vectorDatum.SetType(DatumType::Vector);
			matrixDatum.SetType(DatumType::Matrix);
			ptrDatum.SetType(DatumType::Pointer);

			intDatum.SetSize(smallSize);
			floatDatum.SetSize(smallSize);
			stringDatum.SetSize(smallSize);
			vectorDatum.SetSize(smallSize);
			matrixDatum.SetSize(smallSize);
			ptrDatum.SetSize(smallSize);

			intDatum.SetFromString("5");
			floatDatum.SetFromString("2.2");
			stringDatum.SetFromString("hi");
			vectorDatum.SetFromString("vec4(1.00, 1.00, 1.00, 1.00)");
			matrixDatum.SetFromString("mat4x4((1.00, 0.00, 0.00, 0.00), (0.00, 1.00, 0.00, 0.00), (0.00, 0.00, 1.00, 0.00), (0.00, 0.00, 0.00, 1.00))");

			Assert::IsTrue(intDatum.Get<std::int32_t&>() == 5);
			Assert::IsTrue(floatDatum.Get<std::float_t&>() == std::stof("2.2"));
			Assert::IsTrue(stringDatum.Get<std::string&>() == "hi");
			Assert::IsTrue(vectorDatum.Get<glm::vec4&>() == glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			Assert::IsTrue(matrixDatum.Get<glm::mat4&>() == glm::mat4(1.0f));

			auto ptrExpression = [&ptrDatum] {ptrDatum.SetFromString("hi"); };
			Assert::ExpectException<std::exception>(ptrExpression);

			Datum k;
			auto kExpression = [&k] {k.SetFromString("5"); };
			Assert::ExpectException<std::exception>(kExpression);
		}

		TEST_METHOD(DatumToString)
		{
			testPtr->Data(testInt);
			testPtrTwo->Data(testIntTwo);

			Datum intDatum;
			Datum floatDatum;
			Datum stringDatum;
			Datum vectorDatum;
			Datum matrixDatum;
			Datum ptrDatum;

			intDatum.SetType(DatumType::Integer);
			floatDatum.SetType(DatumType::Float);
			stringDatum.SetType(DatumType::String);
			vectorDatum.SetType(DatumType::Vector);
			matrixDatum.SetType(DatumType::Matrix);
			ptrDatum.SetType(DatumType::Pointer);

			intDatum.SetSize(smallSize);
			floatDatum.SetSize(smallSize);
			stringDatum.SetSize(smallSize);
			vectorDatum.SetSize(smallSize);
			matrixDatum.SetSize(smallSize);
			ptrDatum.SetSize(smallSize);

			intDatum.Set(testInt);
			floatDatum.Set(testFloat);
			stringDatum.Set(testString);
			vectorDatum.Set(testVector);
			matrixDatum.Set(testMatrix);
			ptrDatum.Set(testPtr);

			std::string intString = intDatum.ToString();
			std::string floatString = floatDatum.ToString();
			std::string stringString = stringDatum.ToString();
			std::string vectorString = vectorDatum.ToString();
			std::string matrixString = matrixDatum.ToString();
			std::string ptrString;

			const Datum constIntDatum(intDatum);
			const Datum constFloatDatum(floatDatum);
			const Datum constStringDatum(stringDatum);
			const Datum constVectorDatum(vectorDatum);
			const Datum constMatrixDatum(matrixDatum);
			const Datum constPtrDatum(ptrDatum);

			Assert::IsTrue(intString == "1");
			Assert::IsTrue(floatString == "1.100000");
			Assert::IsTrue(stringString == "k");
			Assert::IsTrue(vectorString == "vec4(1.000000, 1.000000, 1.000000, 1.000000)");
			Assert::IsTrue(matrixString == "mat4x4((1.000000, 0.000000, 0.000000, 0.000000), (0.000000, 1.000000, 0.000000, 0.000000), (0.000000, 0.000000, 1.000000, 0.000000), (0.000000, 0.000000, 0.000000, 1.000000))");

			auto testExpression = [&ptrDatum, &ptrString] {ptrString = ptrDatum.ToString(); };
			Assert::ExpectException<std::exception>(testExpression);

			std::string intStringTwo = constIntDatum.ToString();
			std::string floatStringTwo = constFloatDatum.ToString();
			std::string stringStringTwo = constStringDatum.ToString();
			std::string vectorStringTwo = constVectorDatum.ToString();
			std::string matrixStringTwo = constMatrixDatum.ToString();
			std::string ptrStringTwo;

			Assert::IsTrue(intStringTwo == "1");
			Assert::IsTrue(floatStringTwo == "1.100000");
			Assert::IsTrue(stringStringTwo == "k");
			Assert::IsTrue(vectorStringTwo == "vec4(1.000000, 1.000000, 1.000000, 1.000000)");
			Assert::IsTrue(matrixStringTwo == "mat4x4((1.000000, 0.000000, 0.000000, 0.000000), (0.000000, 1.000000, 0.000000, 0.000000), (0.000000, 0.000000, 1.000000, 0.000000), (0.000000, 0.000000, 0.000000, 1.000000))");

			auto testExpressionTwo = [&ptrDatum, &ptrStringTwo] {ptrStringTwo = ptrDatum.ToString(); };
			Assert::ExpectException<std::exception>(testExpressionTwo);
		}

		TEST_METHOD(DatumClear)
		{
			testPtr->Data(testInt);
			testPtrTwo->Data(testIntTwo);

			Datum intDatum;
			Datum floatDatum;
			Datum stringDatum;
			Datum vectorDatum;
			Datum matrixDatum;
			Datum ptrDatum;

			intDatum.Set(testInt);
			floatDatum.Set(testFloat);
			stringDatum.Set(testString);
			vectorDatum.Set(testVector);
			matrixDatum.Set(testMatrix);
			ptrDatum.Set(testPtr);

			intDatum.Set(testInt, 1);
			floatDatum.Set(testFloat, 1);
			stringDatum.Set(testString, 1);
			vectorDatum.Set(testVector, 1);
			matrixDatum.Set(testMatrix, 1);
			ptrDatum.Set(testPtrTwo, 1);

			intDatum.Clear();
			floatDatum.Clear();
			stringDatum.Clear();
			vectorDatum.Clear();
			matrixDatum.Clear();
			ptrDatum.Clear();

			Assert::IsTrue(0 == intDatum.Size());
			Assert::IsTrue(0 == floatDatum.Size());
			Assert::IsTrue(0 == stringDatum.Size());
			Assert::IsTrue(0 == vectorDatum.Size());
			Assert::IsTrue(0 == matrixDatum.Size());
			Assert::IsTrue(0 == ptrDatum.Size());
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

	_CrtMemState DatumTest::sStartMemState;
}