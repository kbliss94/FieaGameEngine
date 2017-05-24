#include "pch.h"
#include "CppUnitTest.h"
#include "SList.h"
#include "TestFoo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{		
	TEST_CLASS(SListTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD(IteratorPreIncrement)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			std::int32_t secondTestInt = 20;
			std::int32_t *secondTestPtr = &secondTestInt;
			Foo secondTestFoo;
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intList.PushBack(testInt);
			ptrList.PushBack(testPtr);
			fooList.PushBack(testFoo);

			intList.PushBack(secondTestInt);
			ptrList.PushBack(secondTestPtr);
			fooList.PushBack(secondTestFoo);

			SList<std::int32_t>::Iterator intIt;
			SList<std::int32_t *>::Iterator ptrIt;
			SList<Foo>::Iterator fooIt;
			intIt = intList.begin();
			ptrIt = ptrList.begin();
			fooIt = fooList.begin();

			++intIt;
			++ptrIt;
			++fooIt;

			Foo test = *fooIt;

			Assert::AreEqual(*intIt, secondTestInt);
			Assert::AreEqual(*ptrIt, secondTestPtr);
			Assert::AreEqual(test.getData(), secondTestFoo.getData());
		}

		TEST_METHOD(IteratorPostIncrement)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			std::int32_t secondTestInt = 20;
			std::int32_t *secondTestPtr = &secondTestInt;
			Foo secondTestFoo;
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intList.PushBack(testInt);
			ptrList.PushBack(testPtr);
			fooList.PushBack(testFoo);

			intList.PushBack(secondTestInt);
			ptrList.PushBack(secondTestPtr);
			fooList.PushBack(secondTestFoo);

			SList<std::int32_t>::Iterator intIt;
			SList<std::int32_t *>::Iterator ptrIt;
			SList<Foo>::Iterator fooIt;
			intIt = intList.begin();
			ptrIt = ptrList.begin();
			fooIt = fooList.begin();

			intIt++;
			ptrIt++;
			fooIt++;

			Foo test = *fooIt;

			Assert::AreEqual(*intIt, secondTestInt);
			Assert::AreEqual(*ptrIt, secondTestPtr);
			Assert::AreEqual(test.getData(), secondTestFoo.getData());
		}

		TEST_METHOD(IteratorDereferenceOperator)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			intList.PushBack(testInt);
			ptrList.PushBack(testPtr);
			fooList.PushBack(testFoo);

			SList<std::int32_t>::Iterator intIt;
			SList<std::int32_t *>::Iterator ptrIt;
			SList<Foo>::Iterator fooIt;
			intIt = intList.begin();
			ptrIt = ptrList.begin();
			fooIt = fooList.begin();

			Foo test = *fooIt;

			Assert::AreEqual(*intIt, testInt);
			Assert::AreEqual(*ptrIt, testPtr);
			Assert::AreEqual(test.getData(), testFoo.getData());

			const SList<std::int32_t>::Iterator constIntIt(intIt);
			Assert::AreEqual(*constIntIt, *intIt);

			SList<std::int32_t>::Iterator invalidIt;
			const SList<std::int32_t>::Iterator constInvalidIt;

			auto expressionOne = [&invalidIt] {*invalidIt; };
			Assert::ExpectException<std::exception>(expressionOne);

			auto expressionTwo = [&constInvalidIt] {*constInvalidIt; };
			Assert::ExpectException<std::exception>(expressionTwo);
		}

		TEST_METHOD(IteratorNotEqualOperator)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			intList.PushBack(testInt);
			ptrList.PushBack(testPtr);
			fooList.PushBack(testFoo);

			SList<std::int32_t>::Iterator intItOne;
			SList<std::int32_t *>::Iterator ptrItOne;
			SList<Foo>::Iterator fooItOne;
			intItOne = intList.begin();
			ptrItOne = ptrList.begin();
			fooItOne = fooList.begin();

			SList<std::int32_t>::Iterator intItTwo;
			SList<std::int32_t *>::Iterator ptrItTwo;
			SList<Foo>::Iterator fooItTwo;
			intItTwo = intList.end();
			ptrItTwo = ptrList.end();
			fooItTwo = fooList.end();

			bool intTest = false;
			bool ptrTest = false;
			bool fooTest = false;

			if (intItOne != intItTwo)
			{
				intTest = true;
			}

			if (ptrItOne != ptrItTwo)
			{
				ptrTest = true;
			}

			if (fooItOne != fooItTwo)
			{
				fooTest = true;
			}

			//Int tests
			Assert::IsTrue(intTest);

			//Int pointer tests
			Assert::IsTrue(ptrTest);

			//Foo tests
			Assert::IsTrue(fooTest);
		}

		TEST_METHOD(IteratorEqualOperator)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			intList.PushBack(testInt);
			ptrList.PushBack(testPtr);
			fooList.PushBack(testFoo);

			SList<std::int32_t>::Iterator intItOne;
			SList<std::int32_t *>::Iterator ptrItOne;
			SList<Foo>::Iterator fooItOne;
			intItOne = intList.begin();
			ptrItOne = ptrList.begin();
			fooItOne = fooList.begin();

			SList<std::int32_t>::Iterator intItTwo;
			SList<std::int32_t *>::Iterator ptrItTwo;
			SList<Foo>::Iterator fooItTwo;
			intItTwo = intList.begin();
			ptrItTwo = ptrList.begin();
			fooItTwo = fooList.begin();

			bool intTest = false;
			bool ptrTest = false;
			bool fooTest = false;

			if (intItOne == intItTwo)
			{
				intTest = true;
			}

			if (ptrItOne == ptrItTwo)
			{
				ptrTest = true;
			}

			if (fooItOne == fooItTwo)
			{
				fooTest = true;
			}

			//Int tests
			Assert::IsTrue(intTest);

			//Int pointer tests
			Assert::IsTrue(ptrTest);

			//Foo tests
			Assert::IsTrue(fooTest);
		}

		TEST_METHOD(SListConstructor)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;

			std::uint32_t initialSize = 0;

			//Int tests
			Assert::AreEqual(initialSize, intList.Size());

			//Int pointer tests
			Assert::AreEqual(initialSize, ptrList.Size());

			//Foo tests
			Assert::AreEqual(initialSize, fooList.Size());
		}

		TEST_METHOD(SListPushFront)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;
			std::uint32_t size = 0;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);
			
			intList.PushFront(testInt);
			ptrList.PushFront(testPtr);
			fooList.PushFront(testFoo);
			++size;

			//Int tests
			Assert::AreEqual(testInt, intList.Front());
			Assert::AreEqual(size, intList.Size());

			//Int pointer tests
			Assert::AreEqual(*testPtr, *ptrList.Front());
			Assert::AreEqual(size, ptrList.Size());

			//Foo tests
			Assert::AreEqual(testInt, fooList.Front().getData());
			Assert::AreEqual(size, fooList.Size());

			std::int32_t secondTestInt = 20;
			std::int32_t *secondTestPtr = &secondTestInt;
			Foo secondTestFoo;
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intList.PushFront(secondTestInt);
			ptrList.PushFront(secondTestPtr);
			fooList.PushFront(secondTestFoo);
			++size;

			//Int tests
			Assert::AreEqual(secondTestInt, intList.Front());
			Assert::AreEqual(size, intList.Size());

			//Int pointer tests
			Assert::AreEqual(*secondTestPtr, *ptrList.Front());
			Assert::AreEqual(size, ptrList.Size());

			//Foo tests
			Assert::AreEqual(secondTestInt, fooList.Front().getData());
			Assert::AreEqual(size, fooList.Size());
		}

		TEST_METHOD(SListPopFront)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;
			std::uint32_t size = 0;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			std::int32_t secondTestInt = 20;
			std::int32_t *secondTestPtr = &secondTestInt;
			Foo secondTestFoo;
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			std::int32_t thirdTestInt = 30;
			std::int32_t *thirdTestPtr = &thirdTestInt;
			Foo thirdTestFoo;
			thirdTestPtr = &thirdTestInt;
			thirdTestFoo.Data(thirdTestInt);

			intList.PushFront(testInt);
			ptrList.PushFront(testPtr);
			fooList.PushFront(testFoo);
			++size;

			intList.PushFront(secondTestInt);
			ptrList.PushFront(secondTestPtr);
			fooList.PushFront(secondTestFoo);
			++size;

			intList.PushFront(thirdTestInt);
			ptrList.PushFront(thirdTestPtr);
			fooList.PushFront(thirdTestFoo);
			++size;

			intList.PopFront();
			ptrList.PopFront();
			fooList.PopFront();
			--size;

			//Int tests
			Assert::AreEqual(secondTestInt, intList.Front());
			Assert::AreEqual(size, intList.Size());

			//Int pointer tests
			Assert::AreEqual(*secondTestPtr, *ptrList.Front());
			Assert::AreEqual(size, ptrList.Size());
			
			//Foo tests
			Assert::AreEqual(secondTestInt, fooList.Front().getData());
			Assert::AreEqual(size, fooList.Size());

			intList.PopFront();
			ptrList.PopFront();
			fooList.PopFront();
			--size;

			//Int tests
			Assert::AreEqual(testInt, intList.Front());
			Assert::AreEqual(size, intList.Size());

			//Int pointer tests
			Assert::AreEqual(*testPtr, *ptrList.Front());
			Assert::AreEqual(size, ptrList.Size());

			//Foo tests
			Assert::AreEqual(testInt, fooList.Front().getData());
			Assert::AreEqual(size, fooList.Size());
		}

		TEST_METHOD(SListPushBack)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;
			std::uint32_t size = 0;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			std::int32_t secondTestInt = 20;
			std::int32_t *secondTestPtr = &secondTestInt;
			Foo secondTestFoo;
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intList.PushBack(testInt);
			ptrList.PushBack(testPtr);
			fooList.PushBack(testFoo);
			++size;

			intList.PushBack(secondTestInt);
			ptrList.PushBack(secondTestPtr);
			fooList.PushBack(secondTestFoo);
			++size;

			//Int tests
			Assert::AreEqual(testInt, intList.Front());
			Assert::AreEqual(secondTestInt, intList.Back());
			Assert::AreEqual(size, intList.Size());

			//Int pointer tests
			Assert::AreEqual(*testPtr, *ptrList.Front());
			Assert::AreEqual(*secondTestPtr, *ptrList.Back());
			Assert::AreEqual(size, ptrList.Size());

			//Foo tests
			Assert::AreEqual(testInt, fooList.Front().getData());
			Assert::AreEqual(secondTestInt, fooList.Back().getData());
			Assert::AreEqual(size, fooList.Size());
		}

		TEST_METHOD(SListIsEmpty)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			//Int tests
			Assert::IsTrue(intList.IsEmpty());

			//Int pointer tests
			Assert::IsTrue(ptrList.IsEmpty());

			//Foo tests
			Assert::IsTrue(fooList.IsEmpty());

			intList.PushFront(testInt);
			ptrList.PushFront(testPtr);
			fooList.PushFront(testFoo);

			//Int tests
			Assert::IsFalse(intList.IsEmpty());

			//Int pointer tests
			Assert::IsFalse(ptrList.IsEmpty());

			//Foo tests
			Assert::IsFalse(fooList.IsEmpty());
		}

		TEST_METHOD(SListFront)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			std::int32_t secondTestInt = 20;
			std::int32_t *secondTestPtr = &secondTestInt;
			Foo secondTestFoo;
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intList.PushFront(testInt);
			ptrList.PushFront(testPtr);
			fooList.PushFront(testFoo);

			//Int tests
			Assert::AreEqual(testInt, intList.Front());

			//Int pointer tests
			Assert::AreEqual(testPtr, ptrList.Front());

			//Foo tests
			Assert::AreEqual(testInt, fooList.Front().getData());

			intList.PushFront(secondTestInt);
			ptrList.PushFront(secondTestPtr);
			fooList.PushFront(secondTestFoo);

			//Int tests
			Assert::AreNotEqual(testInt, intList.Front());

			//Int pointer tests
			Assert::AreNotEqual(testPtr, ptrList.Front());

			//Foo tests
			Assert::AreNotEqual(testInt, fooList.Front().getData());

			std::int32_t modifyFrontInt = 5;
			std::int32_t *modifyFrontPtr = &modifyFrontInt;
			Foo modifyFrontFoo;
			modifyFrontPtr = &modifyFrontInt;
			modifyFrontFoo.Data(modifyFrontInt);

			intList.Front() = modifyFrontInt;
			ptrList.Front() = modifyFrontPtr;
			fooList.Front().Data(modifyFrontInt);


			//Int tests
			Assert::AreEqual(modifyFrontInt, intList.Front());

			//Int pointer tests
			Assert::AreEqual(modifyFrontPtr, ptrList.Front());

			//Foo tests
			Assert::AreEqual(modifyFrontInt, fooList.Front().getData());

			const SList<std::int32_t> constIntList(intList);
			Assert::AreEqual(constIntList.Front(), intList.Front());

			SList<int32_t> emptyIntList;
			const SList<int32_t> constEmptyIntList;

			auto expressionOne = [&emptyIntList] {emptyIntList.Front(); };
			Assert::ExpectException<std::exception>(expressionOne);

			auto expressionTwo = [&constEmptyIntList] {constEmptyIntList.Front(); };
			Assert::ExpectException<std::exception>(expressionTwo);
		}

		TEST_METHOD(SListBack)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			std::int32_t secondTestInt = 20;
			std::int32_t *secondTestPtr = &secondTestInt;
			Foo secondTestFoo;
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intList.PushFront(testInt);
			ptrList.PushFront(testPtr);
			fooList.PushFront(testFoo);

			//Int tests
			Assert::AreEqual(testInt, intList.Back());

			//Int pointer tests
			Assert::AreEqual(testPtr, ptrList.Back());

			//Foo tests
			Assert::AreEqual(testInt, fooList.Back().getData());

			intList.PushBack(secondTestInt);
			ptrList.PushBack(secondTestPtr);
			fooList.PushBack(secondTestFoo);

			//Int tests
			Assert::AreNotEqual(testInt, intList.Back());

			//Int pointer tests
			Assert::AreNotEqual(testPtr, ptrList.Back());

			//Foo tests
			Assert::AreNotEqual(testInt, fooList.Back().getData());

			std::int32_t modifyBackInt= 5;
			std::int32_t *modifyBackPtr = &modifyBackInt;
			Foo modifyBackFoo;
			modifyBackPtr = &modifyBackInt;
			modifyBackFoo.Data(modifyBackInt);

			intList.Front() = modifyBackInt;
			ptrList.Front() = modifyBackPtr;
			fooList.Front().Data(modifyBackInt);

			//Int tests
			Assert::AreEqual(modifyBackInt, intList.Front());

			//Int pointer tests
			Assert::AreEqual(modifyBackPtr, ptrList.Front());

			//Foo tests
			Assert::AreEqual(modifyBackInt, fooList.Front().getData());

			const SList<std::int32_t> constIntList(intList);
			Assert::AreEqual(constIntList.Front(), intList.Front());

			SList<int32_t> emptyIntList;
			const SList<int32_t> constEmptyIntList;

			auto expressionOne = [&emptyIntList] {emptyIntList.Back(); };
			Assert::ExpectException<std::exception>(expressionOne);

			auto expressionTwo = [&constEmptyIntList] {constEmptyIntList.Back(); };
			Assert::ExpectException<std::exception>(expressionTwo);
		}

		TEST_METHOD(SListSize)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;
			std::uint32_t testSize = 3;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			for (std::uint32_t i = 0; i < testSize; ++i)
			{
				intList.PushFront(testInt);
				ptrList.PushFront(testPtr);
				fooList.PushFront(testFoo);
			}

			//Int tests
			Assert::AreEqual(testSize, intList.Size());

			//Int pointer tests
			Assert::AreEqual(testSize, ptrList.Size());

			//Foo tests
			Assert::AreEqual(testSize, fooList.Size());
		}

		TEST_METHOD(SListCopyConstructor)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			std::int32_t secondTestInt = 20;
			std::int32_t *secondTestPtr = &secondTestInt;
			Foo secondTestFoo;
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intList.PushBack(testInt);
			ptrList.PushBack(testPtr);
			fooList.PushBack(testFoo);

			intList.PushBack(secondTestInt);
			ptrList.PushBack(secondTestPtr);
			fooList.PushBack(secondTestFoo);

			SList<std::int32_t> secondIntList(intList);
			SList<std::int32_t *> secondPtrList(ptrList);
			SList<Foo> secondFooList(fooList);

			//Int tests
			Assert::AreEqual(secondIntList.Front(), intList.Front());
			Assert::AreEqual(secondIntList.Size(), intList.Size());

			//Int pointer tests
			Assert::AreEqual(secondPtrList.Front(), ptrList.Front());
			Assert::AreEqual(secondPtrList.Size(), ptrList.Size());

			//Foo tests
			Assert::AreEqual(secondFooList.Front().getData(), fooList.Front().getData());
			Assert::AreEqual(secondFooList.Size(), fooList.Size());
		}

		TEST_METHOD(SListMoveConstructor)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			std::int32_t secondTestInt = 20;
			std::int32_t *secondTestPtr = &secondTestInt;
			Foo secondTestFoo;
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intList.PushBack(testInt);
			ptrList.PushBack(testPtr);
			fooList.PushBack(testFoo);

			intList.PushBack(secondTestInt);
			ptrList.PushBack(secondTestPtr);
			fooList.PushBack(secondTestFoo);

			std::int32_t rhsIntFront = intList.Front();
			std::int32_t* rhsPtrFront = ptrList.Front();
			std::int32_t rhsFooFront = fooList.Front().getData();
			std::uint32_t rhsIntSize = intList.Size();
			std::uint32_t rhsPtrSize = ptrList.Size();
			std::uint32_t rhsFooSize = fooList.Size();

			SList<std::int32_t> secondIntList(std::move(intList));
			SList<std::int32_t *> secondPtrList(std::move(ptrList));
			SList<Foo> secondFooList(std::move(fooList));

			//Int tests
			Assert::AreEqual(secondIntList.Front(), rhsIntFront);
			Assert::AreEqual(secondIntList.Size(), rhsIntSize);

			//Int pointer tests
			Assert::AreEqual(secondPtrList.Front(), rhsPtrFront);
			Assert::AreEqual(secondPtrList.Size(), rhsPtrSize);

			//Foo tests
			Assert::AreEqual(secondFooList.Front().getData(), rhsFooFront);
			Assert::AreEqual(secondFooList.Size(), rhsFooSize);

			Assert::IsTrue(intList.IsEmpty());
			Assert::IsTrue(ptrList.IsEmpty());
			Assert::IsTrue(fooList.IsEmpty());
		}

		TEST_METHOD(SListAssignmentOperator)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			std::int32_t secondTestInt = 20;
			std::int32_t *secondTestPtr = &secondTestInt;
			Foo secondTestFoo;
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intList.PushBack(testInt);
			ptrList.PushBack(testPtr);
			fooList.PushBack(testFoo);

			intList.PushBack(secondTestInt);
			ptrList.PushBack(secondTestPtr);
			fooList.PushBack(secondTestFoo);

			SList<std::int32_t> secondIntList;
			SList<std::int32_t *> secondPtrList;
			SList<Foo> secondFooList;

			secondIntList = intList;
			secondPtrList = ptrList;
			secondFooList = fooList;

			//Int tests
			Assert::AreEqual(secondIntList.Front(), intList.Front());
			Assert::AreEqual(secondIntList.Size(), intList.Size());

			//Int pointer tests
			Assert::AreEqual(secondPtrList.Front(), ptrList.Front());
			Assert::AreEqual(secondPtrList.Size(), ptrList.Size());

			//Foo tests
			Assert::AreEqual(secondFooList.Front().getData(), fooList.Front().getData());
			Assert::AreEqual(secondFooList.Size(), fooList.Size());
		}

		TEST_METHOD(SListMoveAssignmentOperator)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			std::int32_t secondTestInt = 20;
			std::int32_t *secondTestPtr = &secondTestInt;
			Foo secondTestFoo;
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intList.PushBack(testInt);
			ptrList.PushBack(testPtr);
			fooList.PushBack(testFoo);

			intList.PushBack(secondTestInt);
			ptrList.PushBack(secondTestPtr);
			fooList.PushBack(secondTestFoo);

			SList<std::int32_t> secondIntList;
			SList<std::int32_t *> secondPtrList;
			SList<Foo> secondFooList;

			std::int32_t rhsIntFront = intList.Front();
			std::int32_t* rhsPtrFront = ptrList.Front();
			std::int32_t rhsFooFront = fooList.Front().getData();
			std::uint32_t rhsIntSize = intList.Size();
			std::uint32_t rhsPtrSize = ptrList.Size();
			std::uint32_t rhsFooSize = fooList.Size();

			secondIntList = std::move(intList);
			secondPtrList = std::move(ptrList);
			secondFooList = std::move(fooList);

			//Int tests
			Assert::AreEqual(secondIntList.Front(), rhsIntFront);
			Assert::AreEqual(secondIntList.Size(), rhsIntSize);

			//Int pointer tests
			Assert::AreEqual(secondPtrList.Front(), rhsPtrFront);
			Assert::AreEqual(secondPtrList.Size(), rhsPtrSize);

			//Foo tests
			Assert::AreEqual(secondFooList.Front().getData(), rhsFooFront);
			Assert::AreEqual(secondFooList.Size(), rhsFooSize);

			Assert::IsTrue(intList.IsEmpty());
			Assert::IsTrue(ptrList.IsEmpty());
			Assert::IsTrue(fooList.IsEmpty());
		}

		TEST_METHOD(SListClear)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;
			std::uint32_t clearSize = 0;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			std::int32_t secondTestInt = 20;
			std::int32_t *secondTestPtr = &secondTestInt;
			Foo secondTestFoo;
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intList.PushBack(testInt);
			ptrList.PushBack(testPtr);
			fooList.PushBack(testFoo);

			intList.PushBack(secondTestInt);
			ptrList.PushBack(secondTestPtr);
			fooList.PushBack(secondTestFoo);

			intList.Clear();
			ptrList.Clear();
			fooList.Clear();

			//Int tests
			Assert::AreEqual(clearSize, intList.Size());

			//Int pointer tests
			Assert::AreEqual(clearSize, ptrList.Size());

			//Foo tests
			Assert::AreEqual(clearSize, fooList.Size());
		}

		TEST_METHOD(SListBegin)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			std::int32_t secondTestInt = 20;
			std::int32_t *secondTestPtr = &secondTestInt;
			Foo secondTestFoo;
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intList.PushBack(testInt);
			ptrList.PushBack(testPtr);
			fooList.PushBack(testFoo);

			intList.PushBack(secondTestInt);
			ptrList.PushBack(secondTestPtr);
			fooList.PushBack(secondTestFoo);

			SList<std::int32_t>::Iterator intBeginIt;
			SList<std::int32_t *>::Iterator ptrBeginIt;
			SList<Foo>::Iterator fooBeginIt;
			intBeginIt = intList.begin();
			ptrBeginIt = ptrList.begin();
			fooBeginIt = fooList.begin();

			SList<std::int32_t>::Iterator intEndIt;
			SList<std::int32_t *>::Iterator ptrEndIt;
			SList<Foo>::Iterator fooEndIt;
			intEndIt = intList.end();
			ptrEndIt = ptrList.end();
			fooEndIt = fooList.end();

			bool intTest = false;
			bool ptrTest = false;
			bool fooTest = false;

			if (intEndIt == intBeginIt)
			{
				intTest = true;
			}

			if (ptrEndIt == ptrBeginIt)
			{
				ptrTest = true;
			}

			if (fooEndIt == fooBeginIt)
			{
				fooTest = true;
			}

			//Int tests
			Assert::AreEqual(*intBeginIt, testInt);
			Assert::IsFalse(intTest);

			//Int pointer tests
			Assert::AreEqual(*ptrBeginIt, testPtr);
			Assert::IsFalse(ptrTest);

			Foo test = *fooBeginIt;

			//Foo tests
			Assert::AreEqual(test.getData(), testFoo.getData());
			Assert::IsFalse(fooTest);
		}

		TEST_METHOD(SListEnd)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;

			SList<std::int32_t>::Iterator intBeginIt;
			SList<std::int32_t *>::Iterator ptrBeginIt;
			SList<Foo>::Iterator fooBeginIt;
			intBeginIt = intList.begin();
			ptrBeginIt = ptrList.begin();
			fooBeginIt = fooList.begin();

			SList<std::int32_t>::Iterator intEndIt;
			SList<std::int32_t *>::Iterator ptrEndIt;
			SList<Foo>::Iterator fooEndIt;
			intEndIt = intList.end();
			ptrEndIt = ptrList.end();
			fooEndIt = fooList.end();

			bool intTest = false;
			bool ptrTest = false;
			bool fooTest = false;

			if (intEndIt == intBeginIt)
			{
				intTest = true;
			}

			if (ptrEndIt == ptrBeginIt)
			{
				ptrTest = true;
			}

			if (fooEndIt == fooBeginIt)
			{
				fooTest = true;
			}

			//Int tests
			Assert::IsTrue(intTest);
			
			//Int pointer tests
			Assert::IsTrue(ptrTest);

			//Foo tests
			Assert::IsTrue(fooTest);
		}
		
		TEST_METHOD(SListInsertAfter)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;
			SList<std::int32_t> secondIntList;
			SList<std::int32_t *> secondPtrList;
			SList<Foo> secondFooList;
			std::uint32_t size = 3;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			std::int32_t secondTestInt = 20;
			std::int32_t *secondTestPtr = &secondTestInt;
			Foo secondTestFoo;
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			std::int32_t thirdTestInt = 30;
			std::int32_t *thirdTestPtr = &thirdTestInt;
			Foo thirdTestFoo;
			thirdTestPtr = &thirdTestInt;
			thirdTestFoo.Data(thirdTestInt);

			intList.PushBack(testInt);
			ptrList.PushBack(testPtr);
			fooList.PushBack(testFoo);

			intList.PushBack(secondTestInt);
			ptrList.PushBack(secondTestPtr);
			fooList.PushBack(secondTestFoo);

			SList<std::int32_t>::Iterator intBeginIt;
			SList<std::int32_t *>::Iterator ptrBeginIt;
			SList<Foo>::Iterator fooBeginIt;
			intBeginIt = intList.begin();
			ptrBeginIt = ptrList.begin();
			fooBeginIt = fooList.begin();

			SList<std::int32_t>::Iterator secondIntBeginIt;
			SList<std::int32_t *>::Iterator secondPtrBeginIt;
			SList<Foo>::Iterator secondFooBeginIt;
			secondIntBeginIt = secondIntList.begin();
			secondPtrBeginIt = secondPtrList.begin();
			secondFooBeginIt = secondFooList.begin();

			intList.InsertAfter(thirdTestInt, intBeginIt);
			ptrList.InsertAfter(thirdTestPtr, ptrBeginIt);
			fooList.InsertAfter(thirdTestFoo, fooBeginIt);

			secondIntList.InsertAfter(thirdTestInt, secondIntBeginIt);
			secondPtrList.InsertAfter(thirdTestPtr, secondPtrBeginIt);
			secondFooList.InsertAfter(thirdTestFoo, secondFooBeginIt);

			secondIntBeginIt = secondIntList.begin();
			secondPtrBeginIt = secondPtrList.begin();
			secondFooBeginIt = secondFooList.begin();

			//Int tests
			Assert::AreEqual(size, intList.Size());
			Assert::AreEqual(*secondIntBeginIt, thirdTestInt);

			//Int pointer tests
			Assert::AreEqual(size, ptrList.Size());
			Assert::AreEqual(*secondPtrBeginIt, thirdTestPtr);

			Foo test = *secondFooBeginIt;

			//Foo tests
			Assert::AreEqual(size, fooList.Size());
			Assert::AreEqual(test.getData(), thirdTestFoo.getData());

			SList<int32_t>::Iterator invalidIt;

			auto expressionOne = [&intList, &invalidIt, &testInt] {intList.InsertAfter(testInt, invalidIt); };
			Assert::ExpectException<std::exception>(expressionOne);
		}

		TEST_METHOD(SListFind)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			std::int32_t secondTestInt = 20;
			std::int32_t *secondTestPtr = &secondTestInt;
			Foo secondTestFoo;
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			std::int32_t thirdTestInt = 30;
			std::int32_t *thirdTestPtr = &thirdTestInt;
			Foo thirdTestFoo;
			thirdTestPtr = &thirdTestInt;
			thirdTestFoo.Data(thirdTestInt);

			intList.PushBack(testInt);
			ptrList.PushBack(testPtr);
			fooList.PushBack(testFoo);

			intList.PushBack(secondTestInt);
			ptrList.PushBack(secondTestPtr);
			fooList.PushBack(secondTestFoo);

			SList<std::int32_t>::Iterator intIt;
			SList<std::int32_t>::Iterator secondIntIt;
			SList<std::int32_t *>::Iterator ptrIt;
			SList<std::int32_t *>::Iterator secondPtrIt;
			SList<Foo>::Iterator fooIt;
			SList<Foo>::Iterator secondFooIt;

			intIt = intList.Find(testInt);
			ptrIt = ptrList.Find(testPtr);
			fooIt = fooList.Find(testFoo);

			secondIntIt = intList.Find(thirdTestInt);
			secondPtrIt = ptrList.Find(thirdTestPtr);
			secondFooIt = fooList.Find(thirdTestFoo);

			//Int tests
			Assert::AreEqual(*intIt, testInt);

			//Int pointer tests
			Assert::AreEqual(*ptrIt, testPtr);

			Foo test = *fooIt;

			//Foo tests
			Assert::AreEqual(test.getData(), testFoo.getData());
		}

		TEST_METHOD(SListRemove)
		{
			SList<std::int32_t> intList;
			SList<std::int32_t *> ptrList;
			SList<Foo> fooList;
			std::uint32_t size = 1;

			std::int32_t testInt = 10;
			std::int32_t *testPtr = &testInt;
			Foo testFoo;
			testPtr = &testInt;
			testFoo.Data(testInt);

			std::int32_t secondTestInt = 20;
			std::int32_t *secondTestPtr = &secondTestInt;
			Foo secondTestFoo;
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intList.PushBack(testInt);
			ptrList.PushBack(testPtr);
			fooList.PushBack(testFoo);

			intList.PushBack(secondTestInt);
			ptrList.PushBack(secondTestPtr);
			fooList.PushBack(secondTestFoo);

			intList.Remove(testInt);
			ptrList.Remove(testPtr);
			fooList.Remove(testFoo);

			//Int tests
			Assert::AreEqual(size, intList.Size());

			//Int pointer tests
			Assert::AreEqual(size, ptrList.Size());

			//Foo tests
			Assert::AreEqual(size, fooList.Size());
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

	_CrtMemState SListTest::sStartMemState;
}