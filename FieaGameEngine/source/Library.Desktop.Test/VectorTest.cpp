#include "pch.h"
#include "CppUnitTest.h"
#include "Vector.h"
#include "TestFoo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(VectorTest)
	{
	public:
		Vector<std::int32_t> emptyIntVector;
		Vector<std::int32_t *> emptyPtrVector;
		Vector<Foo> emptyFooVector;

		std::int32_t testInt = 10;
		std::int32_t secondTestInt = 20;
		std::int32_t thirdTestInt = 30;
		std::int32_t *testPtr = &testInt;
		std::int32_t *secondTestPtr = &secondTestInt;
		std::int32_t *thirdTestPtr = &thirdTestInt;
		Foo testFoo;
		Foo secondTestFoo;
		Foo thirdTestFoo;

		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD(VectorDefaultConstructor)
		{
			Assert::IsTrue(emptyIntVector.IsEmpty());
			Assert::IsTrue(emptyPtrVector.IsEmpty());
			Assert::IsTrue(emptyFooVector.IsEmpty());
		}

		TEST_METHOD(VectorBracketOperator)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;

			testPtr = &testInt;
			testFoo.Data(testInt);
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);
			thirdTestPtr = &thirdTestInt;
			thirdTestFoo.Data(thirdTestInt);

			intVector.PushBack(testInt);
			intVector.PushBack(secondTestInt);
			intVector.PushBack(thirdTestInt);
			ptrVector.PushBack(testPtr);
			ptrVector.PushBack(secondTestPtr);
			ptrVector.PushBack(thirdTestPtr);
			fooVector.PushBack(testFoo);
			fooVector.PushBack(secondTestFoo);
			fooVector.PushBack(thirdTestFoo);

			Assert::AreEqual(testInt, intVector[0]);
			Assert::AreEqual(secondTestInt, intVector[1]);
			Assert::AreEqual(thirdTestInt, intVector[2]);

			Assert::AreEqual(testPtr, ptrVector[0]);
			Assert::AreEqual(secondTestPtr, ptrVector[1]);
			Assert::AreEqual(thirdTestPtr, ptrVector[2]);

			Assert::IsTrue(testFoo == fooVector[0]);
			Assert::IsTrue(secondTestFoo == fooVector[1]);
			Assert::IsTrue(thirdTestFoo == fooVector[2]);

			auto intExpression = [&intVector] {intVector[7]; };
			Assert::ExpectException<std::exception>(intExpression);

			auto ptrExpression = [&ptrVector] {ptrVector[7]; };
			Assert::ExpectException<std::exception>(ptrExpression);

			auto fooExpression = [&fooVector] {fooVector[7]; };
			Assert::ExpectException<std::exception>(fooExpression);
		}

		TEST_METHOD(VectorFront)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;

			testPtr = &testInt;
			testFoo.Data(testInt);
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);
			thirdTestPtr = &thirdTestInt;
			thirdTestFoo.Data(thirdTestInt);

			auto intExpression = [&intVector] {intVector.Front(); };
			Assert::ExpectException<std::exception>(intExpression);

			auto ptrExpression = [&ptrVector] {ptrVector.Front(); };
			Assert::ExpectException<std::exception>(ptrExpression);

			auto fooExpression = [&fooVector] {fooVector.Front(); };
			Assert::ExpectException<std::exception>(fooExpression);

			intVector.PushBack(testInt);
			ptrVector.PushBack(testPtr);
			fooVector.PushBack(testFoo);

			Assert::AreEqual(testInt, intVector.Front());
			Assert::AreEqual(testPtr, ptrVector.Front());
			Assert::IsTrue(testFoo == fooVector.Front());

			intVector.PushBack(secondTestInt);
			ptrVector.PushBack(secondTestPtr);
			fooVector.PushBack(secondTestFoo);

			Assert::AreEqual(testInt, intVector.Front());
			Assert::AreEqual(testPtr, ptrVector.Front());
			Assert::IsTrue(testFoo == fooVector.Front());
		}

		TEST_METHOD(VectorBack)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;

			testPtr = &testInt;
			testFoo.Data(testInt);
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);
			thirdTestPtr = &thirdTestInt;
			thirdTestFoo.Data(thirdTestInt);

			intVector.PushBack(testInt);
			ptrVector.PushBack(testPtr);
			fooVector.PushBack(testFoo);

			Assert::AreEqual(testInt, intVector.Back());
			Assert::AreEqual(testPtr, ptrVector.Back());
			Assert::IsTrue(testFoo == fooVector.Back());

			intVector.PushBack(secondTestInt);
			ptrVector.PushBack(secondTestPtr);
			fooVector.PushBack(secondTestFoo);

			Assert::AreEqual(secondTestInt, intVector.Back());
			Assert::AreEqual(secondTestPtr, ptrVector.Back());
			Assert::IsTrue(secondTestFoo == fooVector.Back());

			intVector.PushBack(thirdTestInt);
			ptrVector.PushBack(thirdTestPtr);
			fooVector.PushBack(thirdTestFoo);

			Assert::AreEqual(thirdTestInt, intVector.Back());
			Assert::AreEqual(thirdTestPtr, ptrVector.Back());
			Assert::IsTrue(thirdTestFoo == fooVector.Back());
		}

		TEST_METHOD(VectorPopBack)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;

			testPtr = &testInt;
			testFoo.Data(testInt);
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);
			thirdTestPtr = &thirdTestInt;
			thirdTestFoo.Data(thirdTestInt);

			intVector.PushBack(testInt);
			intVector.PushBack(secondTestInt);
			intVector.PushBack(thirdTestInt);
			ptrVector.PushBack(testPtr);
			ptrVector.PushBack(secondTestPtr);
			ptrVector.PushBack(thirdTestPtr);
			fooVector.PushBack(testFoo);
			fooVector.PushBack(secondTestFoo);
			fooVector.PushBack(thirdTestFoo);

			std::uint32_t size = intVector.Size();
			std::uint32_t capacity = intVector.Capacity();

			intVector.PopBack();
			ptrVector.PopBack();
			fooVector.PopBack();

			Assert::AreEqual(secondTestInt, intVector.Back());
			Assert::AreNotEqual(size, intVector.Size());
			Assert::AreEqual(capacity, intVector.Capacity());
			Assert::AreEqual(secondTestPtr, ptrVector.Back());
			Assert::AreNotEqual(size, ptrVector.Size());
			Assert::AreEqual(capacity, ptrVector.Capacity());
			Assert::IsTrue(secondTestFoo == fooVector.Back());
			Assert::AreNotEqual(size, fooVector.Size());
			Assert::AreEqual(capacity, fooVector.Capacity());

			intVector.PopBack();
			ptrVector.PopBack();
			fooVector.PopBack();

			Assert::AreEqual(testInt, intVector.Back());
			Assert::AreNotEqual(size, intVector.Size());
			Assert::AreEqual(capacity, intVector.Capacity());
			Assert::AreEqual(testPtr, ptrVector.Back());
			Assert::AreNotEqual(size, ptrVector.Size());
			Assert::AreEqual(capacity, ptrVector.Capacity());
			Assert::IsTrue(testFoo == fooVector.Back());
			Assert::AreNotEqual(size, fooVector.Size());
			Assert::AreEqual(capacity, fooVector.Capacity());
		}

		TEST_METHOD(VectorIsEmpty)
		{
			Assert::IsTrue(emptyIntVector.IsEmpty());
			Assert::IsTrue(emptyPtrVector.IsEmpty());
			Assert::IsTrue(emptyFooVector.IsEmpty());
		}

		TEST_METHOD(VectorSize)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;
			std::uint32_t size = 0;

			testPtr = &testInt;
			testFoo.Data(testInt);
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intVector.PushBack(testInt);
			ptrVector.PushBack(testPtr);
			fooVector.PushBack(testFoo);
			++size;
			intVector.PushBack(secondTestInt);
			ptrVector.PushBack(secondTestPtr);
			fooVector.PushBack(secondTestFoo);
			++size;

			Assert::AreEqual(size, intVector.Size());
			Assert::AreEqual(size, ptrVector.Size());
			Assert::AreEqual(size, fooVector.Size());
		}

		TEST_METHOD(VectorCapacity)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;
			std::uint32_t capacity = 10;

			testPtr = &testInt;
			testFoo.Data(testInt);

			intVector.PushBack(testInt);
			ptrVector.PushBack(testPtr);
			fooVector.PushBack(testFoo);

			Assert::AreEqual(capacity, intVector.Capacity());
			Assert::AreEqual(capacity, ptrVector.Capacity());
			Assert::AreEqual(capacity, fooVector.Capacity());

			for (std::uint32_t i = 0; i < 10; ++i)
			{
				intVector.PushBack(testInt);
				ptrVector.PushBack(testPtr);
				fooVector.PushBack(testFoo);
			}

			Assert::AreNotEqual(capacity, intVector.Capacity());
			Assert::AreNotEqual(capacity, ptrVector.Capacity());
			Assert::AreNotEqual(capacity, fooVector.Capacity());
		}

		TEST_METHOD(VectorBegin)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;

			testPtr = &testInt;
			testFoo.Data(testInt);
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intVector.PushBack(testInt);
			ptrVector.PushBack(testPtr);
			fooVector.PushBack(testFoo);

			intVector.PushBack(secondTestInt);
			ptrVector.PushBack(secondTestPtr);
			fooVector.PushBack(secondTestFoo);

			Assert::AreEqual(*intVector.begin(), testInt);
			Assert::AreEqual(*ptrVector.begin(), testPtr);
			Assert::IsTrue(*fooVector.begin() == testFoo);
		}

		TEST_METHOD(VectorEnd)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;

			testPtr = &testInt;
			testFoo.Data(testInt);
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intVector.PushBack(testInt);
			ptrVector.PushBack(testPtr);
			fooVector.PushBack(testFoo);

			intVector.PushBack(secondTestInt);
			ptrVector.PushBack(secondTestPtr);
			fooVector.PushBack(secondTestFoo);

			auto intExpression = [&intVector] {*intVector.end(); };
			Assert::ExpectException<std::exception>(intExpression);

			auto ptrExpression = [&ptrVector] {*ptrVector.end(); };
			Assert::ExpectException<std::exception>(ptrExpression);

			auto fooExpression = [&fooVector] {*fooVector.end(); };
			Assert::ExpectException<std::exception>(fooExpression);
		}

		TEST_METHOD(VectorPushBack)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;
			std::uint32_t capacity = 10;

			testPtr = &testInt;
			testFoo.Data(testInt);
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intVector.PushBack(testInt);
			ptrVector.PushBack(testPtr);
			fooVector.PushBack(testFoo);

			Assert::AreEqual(capacity, intVector.Capacity());
			Assert::AreEqual(capacity, ptrVector.Capacity());
			Assert::AreEqual(capacity, fooVector.Capacity());

			intVector.PushBack(secondTestInt);
			ptrVector.PushBack(secondTestPtr);
			fooVector.PushBack(secondTestFoo);

			Assert::AreEqual(capacity, intVector.Capacity());
			Assert::AreEqual(capacity, ptrVector.Capacity());
			Assert::AreEqual(capacity, fooVector.Capacity());

			Assert::AreNotEqual(intVector.Front(), intVector.Back());
			Assert::AreNotEqual(ptrVector.Front(), ptrVector.Back());
			Assert::IsFalse(fooVector.Front() == fooVector.Back());
		}

		TEST_METHOD(VectorCopyConstructor)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;
			std::uint32_t size = 0;

			testPtr = &testInt;
			testFoo.Data(testInt);
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intVector.PushBack(testInt);
			ptrVector.PushBack(testPtr);
			fooVector.PushBack(testFoo);
			++size;
			intVector.PushBack(secondTestInt);
			ptrVector.PushBack(secondTestPtr);
			fooVector.PushBack(secondTestFoo);
			++size;

			Vector<std::int32_t> secondIntVector(intVector);
			Vector<std::int32_t *> secondPtrVector(ptrVector);
			Vector<Foo> secondFooVector(fooVector);

			Assert::AreEqual(intVector.Size(), secondIntVector.Size());
			Assert::AreEqual(intVector.Capacity(), secondIntVector.Capacity());
			Assert::AreEqual(intVector.Front(), secondIntVector.Front());
			Assert::AreEqual(intVector.Back(), secondIntVector.Back());

			Assert::AreEqual(ptrVector.Size(), secondPtrVector.Size());
			Assert::AreEqual(ptrVector.Capacity(), secondPtrVector.Capacity());
			Assert::AreEqual(ptrVector.Front(), secondPtrVector.Front());
			Assert::AreEqual(ptrVector.Back(), secondPtrVector.Back());

			Assert::AreEqual(fooVector.Size(), secondFooVector.Size());
			Assert::AreEqual(fooVector.Capacity(), secondFooVector.Capacity());
			Assert::IsTrue(intVector.Front() == secondIntVector.Front());
			Assert::IsTrue(intVector.Back() == secondIntVector.Back());
		}

		TEST_METHOD(VectorMoveConstructor)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;
			std::uint32_t size = 0;

			testPtr = &testInt;
			testFoo.Data(testInt);
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intVector.PushBack(testInt);
			ptrVector.PushBack(testPtr);
			fooVector.PushBack(testFoo);
			++size;
			intVector.PushBack(secondTestInt);
			ptrVector.PushBack(secondTestPtr);
			fooVector.PushBack(secondTestFoo);
			++size;

			std::uint32_t rhsIntSize = intVector.Size();
			std::uint32_t rhsPtrSize = ptrVector.Size();
			std::uint32_t rhsFooSize = fooVector.Size();
			std::uint32_t rhsIntCapacity = intVector.Capacity();
			std::uint32_t rhsPtrCapacity = ptrVector.Capacity();
			std::uint32_t rhsFooCapacity = fooVector.Capacity();
			std::int32_t rhsIntFront = intVector.Front();
			std::int32_t* rhsPtrFront = ptrVector.Front();
			std::int32_t rhsIntBack = intVector.Back();
			std::int32_t* rhsPtrBack = ptrVector.Back();

			Vector<std::int32_t> secondIntVector(std::move(intVector));
			Vector<std::int32_t *> secondPtrVector(std::move(ptrVector));
			Vector<Foo> secondFooVector(std::move(fooVector));

			Assert::AreEqual(rhsIntSize, secondIntVector.Size());
			Assert::AreEqual(rhsIntCapacity, secondIntVector.Capacity());
			Assert::AreEqual(rhsIntFront, secondIntVector.Front());
			Assert::AreEqual(rhsIntBack, secondIntVector.Back());

			Assert::AreEqual(rhsPtrSize, secondPtrVector.Size());
			Assert::AreEqual(rhsPtrCapacity, secondPtrVector.Capacity());
			Assert::AreEqual(rhsPtrFront, secondPtrVector.Front());
			Assert::AreEqual(rhsPtrBack, secondPtrVector.Back());

			Assert::AreEqual(rhsFooSize, secondFooVector.Size());
			Assert::AreEqual(rhsFooCapacity, secondFooVector.Capacity());
			Assert::IsTrue(rhsIntFront == secondIntVector.Front());
			Assert::IsTrue(rhsIntBack == secondIntVector.Back());

		}

		TEST_METHOD(VectorAssignmentOperator)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;
			Vector<std::int32_t> secondIntVector;
			Vector<std::int32_t *> secondPtrVector;
			Vector<Foo> secondFooVector;

			testPtr = &testInt;
			testFoo.Data(testInt);
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intVector.PushBack(testInt);
			ptrVector.PushBack(testPtr);
			fooVector.PushBack(testFoo);

			intVector.PushBack(secondTestInt);
			ptrVector.PushBack(secondTestPtr);
			fooVector.PushBack(secondTestFoo);

			secondIntVector = intVector;
			secondPtrVector = ptrVector;
			secondFooVector = fooVector;

			Assert::AreEqual(intVector.Size(), secondIntVector.Size());
			Assert::AreEqual(intVector.Capacity(), secondIntVector.Capacity());
			Assert::AreEqual(intVector.Front(), secondIntVector.Front());
			Assert::AreEqual(intVector.Back(), secondIntVector.Back());

			Assert::AreEqual(ptrVector.Size(), secondPtrVector.Size());
			Assert::AreEqual(ptrVector.Capacity(), secondPtrVector.Capacity());
			Assert::AreEqual(ptrVector.Front(), secondPtrVector.Front());
			Assert::AreEqual(ptrVector.Back(), secondPtrVector.Back());

			Assert::AreEqual(fooVector.Size(), secondFooVector.Size());
			Assert::AreEqual(fooVector.Capacity(), secondFooVector.Capacity());
			Assert::IsTrue(intVector.Front() == secondIntVector.Front());
			Assert::IsTrue(intVector.Back() == secondIntVector.Back());

			intVector.PopBack();
			ptrVector.PopBack();
			fooVector.PopBack();

			secondIntVector = intVector;
			secondPtrVector = ptrVector;
			secondFooVector = fooVector;

			Assert::AreEqual(intVector.Size(), secondIntVector.Size());
			Assert::AreEqual(intVector.Capacity(), secondIntVector.Capacity());
			Assert::AreEqual(intVector.Front(), secondIntVector.Front());
			Assert::AreEqual(intVector.Back(), secondIntVector.Back());

			Assert::AreEqual(ptrVector.Size(), secondPtrVector.Size());
			Assert::AreEqual(ptrVector.Capacity(), secondPtrVector.Capacity());
			Assert::AreEqual(ptrVector.Front(), secondPtrVector.Front());
			Assert::AreEqual(ptrVector.Back(), secondPtrVector.Back());

			Assert::AreEqual(fooVector.Size(), secondFooVector.Size());
			Assert::AreEqual(fooVector.Capacity(), secondFooVector.Capacity());
			Assert::IsTrue(intVector.Front() == secondIntVector.Front());
			Assert::IsTrue(intVector.Back() == secondIntVector.Back());
		}

		TEST_METHOD(VectorMoveAssignmentOperator)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;
			Vector<std::int32_t> secondIntVector;
			Vector<std::int32_t *> secondPtrVector;
			Vector<Foo> secondFooVector;

			testPtr = &testInt;
			testFoo.Data(testInt);
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intVector.PushBack(testInt);
			ptrVector.PushBack(testPtr);
			fooVector.PushBack(testFoo);

			intVector.PushBack(secondTestInt);
			ptrVector.PushBack(secondTestPtr);
			fooVector.PushBack(secondTestFoo);

			std::uint32_t rhsIntSize = intVector.Size();
			std::uint32_t rhsPtrSize = ptrVector.Size();
			std::uint32_t rhsFooSize = fooVector.Size();
			std::uint32_t rhsIntCapacity = intVector.Capacity();
			std::uint32_t rhsPtrCapacity = ptrVector.Capacity();
			std::uint32_t rhsFooCapacity = fooVector.Capacity();
			std::int32_t rhsIntFront = intVector.Front();
			std::int32_t* rhsPtrFront = ptrVector.Front();
			std::int32_t rhsIntBack = intVector.Back();
			std::int32_t* rhsPtrBack = ptrVector.Back();

			secondIntVector.PushBack(testInt);

			secondIntVector = std::move(intVector);
			secondPtrVector = std::move(ptrVector);
			secondFooVector = std::move(fooVector);

			Assert::AreEqual(rhsIntSize, secondIntVector.Size());
			Assert::AreEqual(rhsIntCapacity, secondIntVector.Capacity());
			Assert::AreEqual(rhsIntFront, secondIntVector.Front());
			Assert::AreEqual(rhsIntBack, secondIntVector.Back());

			Assert::AreEqual(rhsPtrSize, secondPtrVector.Size());
			Assert::AreEqual(rhsPtrCapacity, secondPtrVector.Capacity());
			Assert::AreEqual(rhsPtrFront, secondPtrVector.Front());
			Assert::AreEqual(rhsPtrBack, secondPtrVector.Back());

			Assert::AreEqual(rhsFooSize, secondFooVector.Size());
			Assert::AreEqual(rhsFooCapacity, secondFooVector.Capacity());
			Assert::IsTrue(rhsIntFront == secondIntVector.Front());
			Assert::IsTrue(rhsIntBack == secondIntVector.Back());
		}

		TEST_METHOD(VectorReserve)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;
			std::uint32_t capacity = 10;

			intVector.Reserve(capacity);
			ptrVector.Reserve(capacity);
			fooVector.Reserve(capacity);

			Assert::AreEqual(capacity, intVector.Capacity());
			Assert::AreEqual(capacity, ptrVector.Capacity());
			Assert::AreEqual(capacity, fooVector.Capacity());
		}

		TEST_METHOD(VectorFind)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;

			testPtr = &testInt;
			testFoo.Data(testInt);
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intVector.PushBack(testInt);
			ptrVector.PushBack(testPtr);
			fooVector.PushBack(testFoo);

			intVector.PushBack(secondTestInt);
			ptrVector.PushBack(secondTestPtr);
			fooVector.PushBack(secondTestFoo);

			Vector<std::int32_t>::Iterator intIt;
			Vector<std::int32_t *>::Iterator ptrIt;
			Vector<Foo>::Iterator fooIt;
			Vector<std::int32_t>::Iterator secondIntIt;
			Vector<std::int32_t *>::Iterator secondPtrIt;
			Vector<Foo>::Iterator secondFooIt;

			intIt = intVector.Find(testInt);
			ptrIt = ptrVector.Find(testPtr);
			fooIt = fooVector.Find(testFoo);

			secondIntIt = intVector.begin();
			secondPtrIt = ptrVector.begin();
			secondFooIt = fooVector.begin();

			Assert::IsTrue(intIt == secondIntIt);
			Assert::IsTrue(ptrIt == secondPtrIt);
			Assert::IsTrue(fooIt == secondFooIt);

			Vector<std::int32_t> secondIntVector;
			Vector<std::int32_t *> secondPtrVector;
			Vector<Foo> secondFooVector;

			intIt = secondIntVector.Find(testInt);
			ptrIt = secondPtrVector.Find(testPtr);
			fooIt = secondFooVector.Find(testFoo);

			secondIntIt = secondIntVector.end();
			secondPtrIt = secondPtrVector.end();
			secondFooIt = secondFooVector.end();

			Assert::IsTrue(intIt == secondIntIt);
			Assert::IsTrue(ptrIt == secondPtrIt);
			Assert::IsTrue(fooIt == secondFooIt);

			secondIntVector.PushBack(testInt);
			secondPtrVector.PushBack(testPtr);
			secondFooVector.PushBack(testFoo);

			intIt = secondIntVector.Find(secondTestInt);
			ptrIt = secondPtrVector.Find(secondTestPtr);
			fooIt = secondFooVector.Find(secondTestFoo);

			secondIntIt = secondIntVector.end();
			secondPtrIt = secondPtrVector.end();
			secondFooIt = secondFooVector.end();

			Assert::IsTrue(intIt == secondIntIt);
			Assert::IsTrue(ptrIt == secondPtrIt);
			Assert::IsTrue(fooIt == secondFooIt);
		}

		TEST_METHOD(VectorClear)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;

			testPtr = &testInt;
			testFoo.Data(testInt);

			for (std::uint32_t i = 0; i < 5; ++i)
			{
				intVector.PushBack(testInt);
				ptrVector.PushBack(testPtr);
				fooVector.PushBack(testFoo);
			}

			intVector.Clear();
			ptrVector.Clear();
			fooVector.Clear();

			Assert::IsTrue(intVector.IsEmpty());
			Assert::IsTrue(ptrVector.IsEmpty());
			Assert::IsTrue(fooVector.IsEmpty());
		}

		TEST_METHOD(VectorRemove)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;

			testPtr = &testInt;
			testFoo.Data(testInt);

			for (std::uint32_t i = 0; i < 5; ++i)
			{
				intVector.PushBack(testInt);
				ptrVector.PushBack(testPtr);
				fooVector.PushBack(testFoo);
			}

			Vector<std::int32_t>::Iterator intIt = intVector.begin();
			Vector<std::int32_t *>::Iterator ptrIt = ptrVector.begin();
			Vector<Foo>::Iterator fooIt = fooVector.begin();

			std::uint32_t originalSize = intVector.Size();

			intVector.Remove(intIt);
			ptrVector.Remove(ptrIt);
			fooVector.Remove(fooIt);

			Assert::AreNotEqual(originalSize, intVector.Size());
			Assert::AreNotEqual(originalSize, ptrVector.Size());
			Assert::AreNotEqual(originalSize, fooVector.Size());

			intIt = intVector.begin();
			ptrIt = ptrVector.begin();
			fooIt = fooVector.begin();

			++intIt;
			++ptrIt;
			++fooIt;

			originalSize = intVector.Size();

			intVector.Remove(intIt);
			ptrVector.Remove(ptrIt);
			fooVector.Remove(fooIt);

			Assert::AreNotEqual(originalSize, intVector.Size());
			Assert::AreNotEqual(originalSize, ptrVector.Size());
			Assert::AreNotEqual(originalSize, fooVector.Size());

			Vector<std::int32_t> secondIntVector;
			Vector<std::int32_t *> secondPtrVector;
			Vector<Foo> secondFooVector;

			for (std::uint32_t i = 0; i < 5; ++i)
			{
				secondIntVector.PushBack(testInt);
				secondPtrVector.PushBack(testPtr);
				secondFooVector.PushBack(testFoo);
			}

			Vector<std::int32_t>::Iterator startIntIt = secondIntVector.begin();
			Vector<std::int32_t *>::Iterator startPtrIt = secondPtrVector.begin();
			Vector<Foo>::Iterator startFooIt = secondFooVector.begin();
			Vector<std::int32_t>::Iterator endIntIt = startIntIt;
			Vector<std::int32_t *>::Iterator endPtrIt = startPtrIt;
			Vector<Foo>::Iterator endFooIt = startFooIt;

			originalSize = secondIntVector.Size();

			++endIntIt;
			++endPtrIt;
			++endFooIt;

			++endIntIt;
			++endPtrIt;
			++endFooIt;

			secondIntVector.Remove(endIntIt, startIntIt);
			secondPtrVector.Remove(endPtrIt, startPtrIt);
			secondFooVector.Remove(endFooIt, startFooIt);

			Assert::AreEqual(originalSize, secondIntVector.Size());
			Assert::AreEqual(originalSize, secondPtrVector.Size());
			Assert::AreEqual(originalSize, secondFooVector.Size());

			secondIntVector.Remove(startIntIt, endIntIt);
			secondPtrVector.Remove(startPtrIt, endPtrIt);
			secondFooVector.Remove(startFooIt, endFooIt);

			Assert::AreNotEqual(originalSize, secondIntVector.Size());
			Assert::AreNotEqual(originalSize, secondPtrVector.Size());
			Assert::AreNotEqual(originalSize, secondFooVector.Size());
		}

		TEST_METHOD(IteratorComparisonOperators)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;
			Vector<std::int32_t> secondIntVector;
			Vector<std::int32_t *> secondPtrVector;
			Vector<Foo> secondFooVector;

			testPtr = &testInt;
			testFoo.Data(testInt);
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intVector.PushBack(testInt);
			ptrVector.PushBack(testPtr);
			fooVector.PushBack(testFoo);

			intVector.PushBack(secondTestInt);
			ptrVector.PushBack(secondTestPtr);
			fooVector.PushBack(secondTestFoo);

			secondIntVector.PushBack(testInt);
			secondPtrVector.PushBack(testPtr);
			secondFooVector.PushBack(testFoo);

			Vector<std::int32_t>::Iterator intIt = intVector.begin();
			Vector<std::int32_t *>::Iterator ptrIt = ptrVector.begin();
			Vector<Foo>::Iterator fooIt = fooVector.begin();
			Vector<std::int32_t>::Iterator secondIntIt = intVector.begin();
			Vector<std::int32_t *>::Iterator secondPtrIt = ptrVector.begin();
			Vector<Foo>::Iterator secondFooIt = fooVector.begin();

			Assert::IsTrue(intIt == secondIntIt);
			Assert::IsTrue(ptrIt == secondPtrIt);
			Assert::IsTrue(fooIt == secondFooIt);

			Assert::IsFalse(intIt != secondIntIt);
			Assert::IsFalse(ptrIt != secondPtrIt);
			Assert::IsFalse(fooIt != secondFooIt);

			secondIntIt = secondIntVector.begin();
			secondPtrIt = secondPtrVector.begin();
			secondFooIt = secondFooVector.begin();

			Assert::IsFalse(intIt == secondIntIt);
			Assert::IsFalse(ptrIt == secondPtrIt);
			Assert::IsFalse(fooIt == secondFooIt);

			Assert::IsTrue(intIt != secondIntIt);
			Assert::IsTrue(ptrIt != secondPtrIt);
			Assert::IsTrue(fooIt != secondFooIt);
		}

		TEST_METHOD(IteratorIncrementOperators)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;

			testPtr = &testInt;
			testFoo.Data(testInt);
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intVector.PushBack(testInt);
			ptrVector.PushBack(testPtr);
			fooVector.PushBack(testFoo);

			intVector.PushBack(secondTestInt);
			ptrVector.PushBack(secondTestPtr);
			fooVector.PushBack(secondTestFoo);

			Vector<std::int32_t>::Iterator intIt = intVector.begin();
			Vector<std::int32_t *>::Iterator ptrIt = ptrVector.begin();
			Vector<Foo>::Iterator fooIt = fooVector.begin();
			Vector<std::int32_t>::Iterator secondIntIt;
			Vector<std::int32_t *>::Iterator secondPtrIt;
			Vector<Foo>::Iterator secondFooIt;

			secondIntIt = intIt;
			secondPtrIt = ptrIt;
			secondFooIt = fooIt;
			Assert::IsFalse(intIt == ++secondIntIt);
			Assert::IsFalse(ptrIt == ++secondPtrIt);
			Assert::IsFalse(fooIt == ++secondFooIt);

			secondIntIt = intIt;
			secondPtrIt = ptrIt;
			secondFooIt = fooIt;
			Assert::IsTrue(intIt == secondIntIt++);
			Assert::IsTrue(ptrIt == secondPtrIt++);
			Assert::IsTrue(fooIt == secondFooIt++);
		}

		TEST_METHOD(IteratorDereferenceOperator)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;

			testPtr = &testInt;
			testFoo.Data(testInt);
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intVector.PushBack(testInt);
			ptrVector.PushBack(testPtr);
			fooVector.PushBack(testFoo);

			intVector.PushBack(secondTestInt);
			ptrVector.PushBack(secondTestPtr);
			fooVector.PushBack(secondTestFoo);

			Vector<std::int32_t>::Iterator intIt = intVector.begin();
			Vector<std::int32_t *>::Iterator ptrIt = ptrVector.begin();
			Vector<Foo>::Iterator fooIt = fooVector.begin();

			Assert::AreEqual(*intIt, testInt);
			Assert::AreEqual(*ptrIt, testPtr);
			Assert::IsTrue(*fooIt == testFoo);

			const Vector<std::int32_t>::Iterator constIntIt(intIt);
			Assert::AreEqual(*constIntIt, *intIt);

			intIt = intVector.end();
			ptrIt = ptrVector.end();
			fooIt = fooVector.end();

			const Vector<std::int32_t>::Iterator invalidConstIntIt(intIt);

			auto intExpression = [&intIt] {*intIt; };
			Assert::ExpectException<std::exception>(intExpression);

			auto ptrExpression = [&ptrIt] {*ptrIt; };
			Assert::ExpectException<std::exception>(ptrExpression);

			auto fooExpression = [&fooIt] {*fooIt; };
			Assert::ExpectException<std::exception>(fooExpression);

			auto constIntExpression = [&invalidConstIntIt] {*invalidConstIntIt; };
			Assert::ExpectException<std::exception>(constIntExpression);
		}

		TEST_METHOD(IteratorCopyConstructor)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;
			Vector<std::int32_t> secondIntVector;
			Vector<std::int32_t *> secondPtrVector;
			Vector<Foo> secondFooVector;

			testPtr = &testInt;
			testFoo.Data(testInt);
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intVector.PushBack(testInt);
			ptrVector.PushBack(testPtr);
			fooVector.PushBack(testFoo);

			intVector.PushBack(secondTestInt);
			ptrVector.PushBack(secondTestPtr);
			fooVector.PushBack(secondTestFoo);

			secondIntVector.PushBack(testInt);
			secondPtrVector.PushBack(testPtr);
			secondFooVector.PushBack(testFoo);

			Vector<std::int32_t>::Iterator intIt = intVector.begin();
			Vector<std::int32_t *>::Iterator ptrIt = ptrVector.begin();
			Vector<Foo>::Iterator fooIt = fooVector.begin();

			Vector<std::int32_t>::Iterator secondIntIt(intIt);
			Vector<std::int32_t *>::Iterator secondPtrIt(ptrIt);
			Vector<Foo>::Iterator secondFooIt(fooIt);

			Assert::AreEqual(*intIt, *secondIntIt);
			Assert::AreEqual(*ptrIt, *secondPtrIt);
			Assert::IsTrue(*fooIt == *secondFooIt);
		}

		TEST_METHOD(IteratorAssignmentOperator)
		{
			Vector<std::int32_t> intVector;
			Vector<std::int32_t *> ptrVector;
			Vector<Foo> fooVector;

			testPtr = &testInt;
			testFoo.Data(testInt);
			secondTestPtr = &secondTestInt;
			secondTestFoo.Data(secondTestInt);

			intVector.PushBack(testInt);
			ptrVector.PushBack(testPtr);
			fooVector.PushBack(testFoo);

			intVector.PushBack(secondTestInt);
			ptrVector.PushBack(secondTestPtr);
			fooVector.PushBack(secondTestFoo);

			Vector<std::int32_t>::Iterator intIt = intVector.begin();
			Vector<std::int32_t *>::Iterator ptrIt = ptrVector.begin();
			Vector<Foo>::Iterator fooIt = fooVector.begin();

			Assert::AreEqual(*intIt, testInt);
			Assert::AreEqual(*ptrIt, testPtr);
			Assert::IsTrue(*fooIt == testFoo);

			Vector<std::int32_t>::Iterator secondIntIt = intIt;
			Vector<std::int32_t *>::Iterator secondPtrIt = ptrIt;
			Vector<Foo>::Iterator secondFooIt = fooIt;

			Assert::AreEqual(*intIt, *secondIntIt);
			Assert::AreEqual(*ptrIt, *secondPtrIt);
			Assert::IsTrue(*fooIt == *secondFooIt);
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

	_CrtMemState VectorTest::sStartMemState;
}