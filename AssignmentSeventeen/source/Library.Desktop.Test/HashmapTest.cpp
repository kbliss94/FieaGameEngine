#include <utility>
#include "pch.h"
#include "CppUnitTest.h"
#include "Hashmap.h"
#include "TestFoo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

template <>
class FieaGameEngine::DefaultHash <Foo>
{
public:
	std::uint32_t operator() (const Foo & key) const
	{
		std::uint32_t data = key.getData();
		std::uint8_t * dataArray = reinterpret_cast<std::uint8_t*>(&data);
		std::uint32_t hash = 0;

		for (std::uint32_t i = 0; i < sizeof(key); ++i)
		{
			hash += 13 + dataArray[i];
		}

		return hash;
	}
};

namespace LibraryDesktopTest
{
	TEST_CLASS(HashmapTest)
	{
	public:
		std::int32_t testInt = 10;
		std::int32_t secondTestInt = 20;
		std::int32_t thirdTestInt = 30;
		std::int32_t *testPtr = &testInt;
		std::int32_t *secondTestPtr = &secondTestInt;
		std::int32_t *thirdTestPtr = &thirdTestInt;
		Foo testFoo;
		Foo secondTestFoo;
		Foo thirdTestFoo;
		char* testCharPtr = { "hi" };
		char* secondTestCharPtr = { "hey" };
		std::string testString = "hi";
		std::string secondTestString = "hey";

		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD(HashmapConstructor)
		{
			Hashmap<std::int32_t, std::int32_t> intHashmap;
			Hashmap<std::int32_t*, std::int32_t> ptrHashmap;
			Hashmap<Foo, std::int32_t> fooHashmap;
			Hashmap<std::string, std::int32_t> stringHashmap;
			Hashmap<char, std::int32_t> charPtrHashmap;

			std::uint32_t size = 0;

			Assert::AreEqual(size, intHashmap.Size());
			Assert::AreEqual(size, ptrHashmap.Size());
			Assert::AreEqual(size, fooHashmap.Size());
			Assert::AreEqual(size, stringHashmap.Size());
			Assert::AreEqual(size, charPtrHashmap.Size());
		}

		TEST_METHOD(HashmapMoveConstructor)
		{
			testFoo.Data(testInt);
			secondTestFoo.Data(secondTestInt);

			Hashmap<std::int32_t, std::int32_t> intHashmap;
			Hashmap<std::int32_t*, std::int32_t> ptrHashmap;
			Hashmap<Foo, std::int32_t> fooHashmap;
			Hashmap<std::string, std::int32_t> stringHashmap;
			Hashmap<char*, std::int32_t> charPtrHashmap;

			std::pair <std::int32_t, std::int32_t> intPair(testInt, testInt);
			std::pair <std::int32_t*, std::int32_t> ptrPair(testPtr, testInt);
			std::pair <Foo, std::int32_t> fooPair(testFoo, testInt);
			std::pair <std::string, std::int32_t> stringPair(testString, testInt);
			std::pair <char*, std::int32_t> charPtrPair(testCharPtr, testInt);

			std::pair <std::int32_t, std::int32_t> secondIntPair(secondTestInt, secondTestInt);
			std::pair <std::int32_t*, std::int32_t> secondPtrPair(secondTestPtr, secondTestInt);
			std::pair <Foo, std::int32_t> secondFooPair(secondTestFoo, secondTestInt);
			std::pair <std::string, std::int32_t> secondStringPair(secondTestString, secondTestInt);
			std::pair <char*, std::int32_t> secondCharPtrPair(secondTestCharPtr, secondTestInt);

			intHashmap.Insert(intPair);
			ptrHashmap.Insert(ptrPair);
			fooHashmap.Insert(fooPair);
			stringHashmap.Insert(stringPair);
			charPtrHashmap.Insert(charPtrPair);

			intHashmap.Insert(secondIntPair);
			ptrHashmap.Insert(secondPtrPair);
			fooHashmap.Insert(secondFooPair);
			stringHashmap.Insert(secondStringPair);
			charPtrHashmap.Insert(secondCharPtrPair);

			std::uint32_t intSize = intHashmap.Size();
			std::uint32_t ptrSize = ptrHashmap.Size();
			std::uint32_t fooSize = fooHashmap.Size();
			std::uint32_t stringSize = stringHashmap.Size();
			std::uint32_t charPtrSize = charPtrHashmap.Size();

			std::int32_t beginInt = intHashmap.begin()->first;
			std::int32_t* beginPtr = ptrHashmap.begin()->first;
			Foo beginFoo = fooHashmap.begin()->first;
			std::string beginString = stringHashmap.begin()->first;
			char* beginCharPtr = charPtrHashmap.begin()->first;

			Hashmap<std::int32_t, std::int32_t> secondIntHashmap(std::move(intHashmap));
			Hashmap<std::int32_t*, std::int32_t> secondPtrHashmap(std::move(ptrHashmap));
			Hashmap<Foo, std::int32_t> secondFooHashmap(std::move(fooHashmap));
			Hashmap<std::string, std::int32_t> secondStringHashmap(std::move(stringHashmap));
			Hashmap<char*, std::int32_t> secondCharPtrHashmap(std::move(charPtrHashmap));

			Assert::IsTrue(intSize == secondIntHashmap.Size());
			Assert::IsTrue(ptrSize == secondPtrHashmap.Size());
			Assert::IsTrue(fooSize == secondFooHashmap.Size());
			Assert::IsTrue(stringSize == secondStringHashmap.Size());
			Assert::IsTrue(charPtrSize == secondCharPtrHashmap.Size());

			Assert::IsTrue(beginInt == secondIntHashmap.begin()->first);
			Assert::IsTrue(beginPtr == secondPtrHashmap.begin()->first);
			Assert::IsTrue(beginFoo.getData() == secondFooHashmap.begin()->first.getData());
			Assert::IsTrue(beginString == secondStringHashmap.begin()->first);
			Assert::IsTrue(beginCharPtr == secondCharPtrHashmap.begin()->first);
		}

		TEST_METHOD(HashmapMoveAssignmentOperator)
		{
			testFoo.Data(testInt);
			secondTestFoo.Data(secondTestInt);

			Hashmap<std::int32_t, std::int32_t> intHashmap;
			Hashmap<std::int32_t*, std::int32_t> ptrHashmap;
			Hashmap<Foo, std::int32_t> fooHashmap;
			Hashmap<std::string, std::int32_t> stringHashmap;
			Hashmap<char*, std::int32_t> charPtrHashmap;

			std::pair <std::int32_t, std::int32_t> intPair(testInt, testInt);
			std::pair <std::int32_t*, std::int32_t> ptrPair(testPtr, testInt);
			std::pair <Foo, std::int32_t> fooPair(testFoo, testInt);
			std::pair <std::string, std::int32_t> stringPair(testString, testInt);
			std::pair <char*, std::int32_t> charPtrPair(testCharPtr, testInt);

			std::pair <std::int32_t, std::int32_t> secondIntPair(secondTestInt, secondTestInt);
			std::pair <std::int32_t*, std::int32_t> secondPtrPair(secondTestPtr, secondTestInt);
			std::pair <Foo, std::int32_t> secondFooPair(secondTestFoo, secondTestInt);
			std::pair <std::string, std::int32_t> secondStringPair(secondTestString, secondTestInt);
			std::pair <char*, std::int32_t> secondCharPtrPair(secondTestCharPtr, secondTestInt);

			intHashmap.Insert(intPair);
			ptrHashmap.Insert(ptrPair);
			fooHashmap.Insert(fooPair);
			stringHashmap.Insert(stringPair);
			charPtrHashmap.Insert(charPtrPair);

			intHashmap.Insert(secondIntPair);
			ptrHashmap.Insert(secondPtrPair);
			fooHashmap.Insert(secondFooPair);
			stringHashmap.Insert(secondStringPair);
			charPtrHashmap.Insert(secondCharPtrPair);

			std::uint32_t intSize = intHashmap.Size();
			std::uint32_t ptrSize = ptrHashmap.Size();
			std::uint32_t fooSize = fooHashmap.Size();
			std::uint32_t stringSize = stringHashmap.Size();
			std::uint32_t charPtrSize = charPtrHashmap.Size();

			std::int32_t beginInt = intHashmap.begin()->first;
			std::int32_t* beginPtr = ptrHashmap.begin()->first;
			Foo beginFoo = fooHashmap.begin()->first;
			std::string beginString = stringHashmap.begin()->first;
			char* beginCharPtr = charPtrHashmap.begin()->first;

			Hashmap<std::int32_t, std::int32_t> secondIntHashmap;
			Hashmap<std::int32_t*, std::int32_t> secondPtrHashmap;
			Hashmap<Foo, std::int32_t> secondFooHashmap;
			Hashmap<std::string, std::int32_t> secondStringHashmap;
			Hashmap<char*, std::int32_t> secondCharPtrHashmap;

			secondIntHashmap = std::move(intHashmap);
			secondPtrHashmap = std::move(ptrHashmap);
			secondFooHashmap = std::move(fooHashmap);
			secondStringHashmap = std::move(stringHashmap);
			secondCharPtrHashmap = std::move(charPtrHashmap);

			Assert::IsTrue(intSize == secondIntHashmap.Size());
			Assert::IsTrue(ptrSize == secondPtrHashmap.Size());
			Assert::IsTrue(fooSize == secondFooHashmap.Size());
			Assert::IsTrue(stringSize == secondStringHashmap.Size());
			Assert::IsTrue(charPtrSize == secondCharPtrHashmap.Size());

			Assert::IsTrue(beginInt == secondIntHashmap.begin()->first);
			Assert::IsTrue(beginPtr == secondPtrHashmap.begin()->first);
			Assert::IsTrue(beginFoo.getData() == secondFooHashmap.begin()->first.getData());
			Assert::IsTrue(beginString == secondStringHashmap.begin()->first);
			Assert::IsTrue(beginCharPtr == secondCharPtrHashmap.begin()->first);
		}

		TEST_METHOD(HashmapFind)
		{
			testFoo.Data(testInt);
			secondTestFoo.Data(secondTestInt);

			Hashmap<std::int32_t, std::int32_t> intHashmap;
			Hashmap<std::int32_t*, std::int32_t> ptrHashmap;
			Hashmap<Foo, std::int32_t> fooHashmap;
			Hashmap<std::string, std::int32_t> stringHashmap;
			Hashmap<char*, std::int32_t> charPtrHashmap;

			std::pair <std::int32_t, std::int32_t> intPair(testInt, testInt);
			std::pair <std::int32_t*, std::int32_t> ptrPair(testPtr, testInt);
			std::pair <Foo, std::int32_t> fooPair(testFoo, 1);
			std::pair <std::string, std::int32_t> stringPair(testString, 1);
			std::pair <char*, std::int32_t> charPtrPair(testCharPtr, 1);

			std::pair <std::int32_t, std::int32_t> secondIntPair(secondTestInt, secondTestInt);
			std::pair <std::int32_t*, std::int32_t> secondPtrPair(secondTestPtr, secondTestInt);
			std::pair <Foo, std::int32_t> secondFooPair(secondTestFoo, 1);
			std::pair <std::string, std::int32_t> secondStringPair(secondTestString, 1);
			std::pair <char*, std::int32_t> secondCharPtrPair(secondTestCharPtr, 1);

			Hashmap<std::int32_t, std::int32_t>::Iterator intIt;
			Hashmap<std::int32_t*, std::int32_t>::Iterator ptrIt;
			Hashmap<Foo, std::int32_t>::Iterator fooIt;
			Hashmap<std::string, std::int32_t>::Iterator stringIt;
			Hashmap<char*, std::int32_t>::Iterator charPtrIt;

			Hashmap<std::int32_t, std::int32_t>::Iterator secondIntIt;
			Hashmap<std::int32_t*, std::int32_t>::Iterator secondPtrIt;
			Hashmap<Foo, std::int32_t>::Iterator secondFooIt;
			Hashmap<std::string, std::int32_t>::Iterator secondStringIt;
			Hashmap<char*, std::int32_t>::Iterator secondCharPtrIt;

			intIt = intHashmap.Insert(intPair);
			ptrIt = ptrHashmap.Insert(ptrPair);
			fooIt = fooHashmap.Insert(fooPair);
			stringIt = stringHashmap.Insert(stringPair);
			charPtrIt = charPtrHashmap.Insert(charPtrPair);

			secondIntIt = intHashmap.Find(intPair.first);
			secondPtrIt = ptrHashmap.Find(ptrPair.first);
			secondFooIt = fooHashmap.Find(fooPair.first);
			secondStringIt = stringHashmap.Find(stringPair.first);
			secondCharPtrIt = charPtrHashmap.Find(charPtrPair.first);

			Assert::AreEqual((*intIt).first, (*secondIntIt).first);
			Assert::AreEqual((*ptrIt).first, (*secondPtrIt).first);
			Assert::IsTrue((*fooIt).first == (*secondFooIt).first);
			Assert::AreEqual((*stringIt).first, (*secondStringIt).first);
			Assert::AreEqual((*charPtrIt).first, (*secondCharPtrIt).first);

			secondIntIt = intHashmap.Find(secondIntPair.first);
			secondPtrIt = ptrHashmap.Find(secondPtrPair.first);
			secondFooIt = fooHashmap.Find(secondFooPair.first);
			secondStringIt = stringHashmap.Find(secondStringPair.first);
			secondCharPtrIt = charPtrHashmap.Find(secondCharPtrPair.first);

			Assert::IsTrue(secondIntIt == intHashmap.end());
			Assert::IsTrue(secondPtrIt == ptrHashmap.end());
			Assert::IsTrue(secondFooIt == fooHashmap.end());
			Assert::IsTrue(secondStringIt == stringHashmap.end());
			Assert::IsTrue(secondCharPtrIt == charPtrHashmap.end());
		}

		TEST_METHOD(HashmapInsert)
		{
			testFoo.Data(testInt);
			secondTestFoo.Data(secondTestInt);

			Hashmap<std::int32_t, std::int32_t> intHashmap;
			Hashmap<std::int32_t*, std::int32_t> ptrHashmap;
			Hashmap<Foo, std::int32_t> fooHashmap;
			Hashmap<std::string, std::int32_t> stringHashmap;
			Hashmap<char*, std::int32_t> charPtrHashmap;
			std::uint32_t size = 0;

			std::pair <std::int32_t, std::int32_t> intPair(testInt, testInt);
			std::pair <std::int32_t*, std::int32_t> ptrPair(testPtr, testInt);
			std::pair <Foo, std::int32_t> fooPair(testFoo, testInt);
			std::pair <std::string, std::int32_t> stringPair(testString, testInt);
			std::pair <char*, std::int32_t> charPtrPair(testCharPtr, testInt);

			std::pair <std::int32_t, std::int32_t> secondIntPair(secondTestInt, secondTestInt);
			std::pair <std::int32_t*, std::int32_t> secondPtrPair(secondTestPtr, secondTestInt);
			std::pair <Foo, std::int32_t> secondFooPair(secondTestFoo, secondTestInt);
			std::pair <std::string, std::int32_t> secondStringPair(secondTestString, secondTestInt);
			std::pair <char*, std::int32_t> secondCharPtrPair(secondTestCharPtr, secondTestInt);

			Hashmap<std::int32_t, std::int32_t>::Iterator intIt;
			Hashmap<std::int32_t*, std::int32_t>::Iterator ptrIt;
			Hashmap<Foo, std::int32_t>::Iterator fooIt;
			Hashmap<std::string, std::int32_t>::Iterator stringIt;
			Hashmap<char*, std::int32_t>::Iterator charPtrIt;

			intIt = intHashmap.Insert(intPair);
			ptrIt = ptrHashmap.Insert(ptrPair);
			fooIt = fooHashmap.Insert(fooPair);
			stringIt = stringHashmap.Insert(stringPair);
			charPtrIt = charPtrHashmap.Insert(charPtrPair);
			++size;

			Assert::AreEqual(testInt, (*intIt).first);
			Assert::AreEqual(testPtr, (*ptrIt).first);
			Assert::IsTrue(testFoo == (*fooIt).first);
			Assert::AreEqual(testString, (*stringIt).first);
			Assert::AreEqual(testCharPtr, (*charPtrIt).first);

			Assert::AreEqual(size, intHashmap.Size());
			Assert::AreEqual(size, ptrHashmap.Size());
			Assert::AreEqual(size, fooHashmap.Size());
			Assert::AreEqual(size, stringHashmap.Size());
			Assert::AreEqual(size, charPtrHashmap.Size());

			intHashmap.Insert(secondIntPair);
			ptrHashmap.Insert(secondPtrPair);
			fooHashmap.Insert(secondFooPair);
			stringHashmap.Insert(secondStringPair);
			charPtrHashmap.Insert(secondCharPtrPair);
			++size;

			Assert::AreEqual(size, intHashmap.Size());
			Assert::AreEqual(size, ptrHashmap.Size());
			Assert::AreEqual(size, fooHashmap.Size());
			Assert::AreEqual(size, stringHashmap.Size());
			Assert::AreEqual(size, charPtrHashmap.Size());

			intHashmap.Insert(intPair);
			ptrHashmap.Insert(ptrPair);
			fooHashmap.Insert(fooPair);
			stringHashmap.Insert(stringPair);
			charPtrHashmap.Insert(charPtrPair);

			Assert::AreEqual(size, intHashmap.Size());
			Assert::AreEqual(size, ptrHashmap.Size());
			Assert::AreEqual(size, fooHashmap.Size());
			Assert::AreEqual(size, stringHashmap.Size());
			Assert::AreEqual(size, charPtrHashmap.Size());
		}

		TEST_METHOD(HashmapBracketOperator)
		{
			testFoo.Data(testInt);
			secondTestFoo.Data(secondTestInt);

			Hashmap<std::int32_t, std::int32_t> intHashmap;
			Hashmap<std::int32_t*, std::int32_t> ptrHashmap;
			Hashmap<Foo, std::int32_t> fooHashmap;
			Hashmap<std::string, std::int32_t> stringHashmap;
			Hashmap<char*, std::int32_t> charPtrHashmap;

			std::pair <std::int32_t, std::int32_t> intPair(testInt, testInt);
			std::pair <std::int32_t*, std::int32_t> ptrPair(testPtr, testInt);
			std::pair <Foo, std::int32_t> fooPair(testFoo, testInt);
			std::pair <std::string, std::int32_t> stringPair(testString, testInt);
			std::pair <char*, std::int32_t> charPtrPair(testCharPtr, testInt);

			std::pair <std::int32_t, std::int32_t> secondIntPair(secondTestInt, secondTestInt);
			std::pair <std::int32_t*, std::int32_t> secondPtrPair(secondTestPtr, secondTestInt);
			std::pair <Foo, std::int32_t> secondFooPair(secondTestFoo, secondTestInt);
			std::pair <std::string, std::int32_t> secondStringPair(secondTestString, secondTestInt);
			std::pair <char*, std::int32_t> secondCharPtrPair(secondTestCharPtr, secondTestInt);

			Hashmap<std::int32_t, std::int32_t>::Iterator intIt;
			Hashmap<std::int32_t*, std::int32_t>::Iterator ptrIt;
			Hashmap<Foo, std::int32_t>::Iterator fooIt;
			Hashmap<std::string, std::int32_t>::Iterator stringIt;
			Hashmap<char*, std::int32_t>::Iterator charPtrIt;

			intIt = intHashmap.Insert(intPair);
			ptrIt = ptrHashmap.Insert(ptrPair);
			fooIt = fooHashmap.Insert(fooPair);
			stringIt = stringHashmap.Insert(stringPair);
			charPtrIt = charPtrHashmap.Insert(charPtrPair);

			const Hashmap<std::int32_t, std::int32_t> secondIntHashmap(intHashmap);
			const Hashmap<std::int32_t*, std::int32_t> secondPtrHashmap(ptrHashmap);
			const Hashmap<Foo, std::int32_t> secondFooHashmap(fooHashmap);
			const Hashmap<std::string, std::int32_t> secondStringHashmap(stringHashmap);
			const Hashmap<char*, std::int32_t> secondCharPtrHashmap(charPtrHashmap);

			Assert::AreEqual((*intIt).second, intHashmap[(*intIt).first]);
			Assert::AreEqual((*ptrIt).second, ptrHashmap[(*ptrIt).first]);
			Assert::IsTrue((*fooIt).second == fooHashmap[(*fooIt).first]);
			Assert::AreEqual((*stringIt).second, stringHashmap[(*stringIt).first]);
			Assert::AreEqual((*charPtrIt).second, charPtrHashmap[(*charPtrIt).first]);

			std::uint32_t size = 2;

			intHashmap[secondIntPair.first];
			ptrHashmap[secondPtrPair.first];
			fooHashmap[secondFooPair.first];
			stringHashmap[secondStringPair.first];
			charPtrHashmap[secondCharPtrPair.first];

			Assert::AreEqual(size, intHashmap.Size());
			Assert::AreEqual(size, ptrHashmap.Size());
			Assert::AreEqual(size, fooHashmap.Size());
			Assert::AreEqual(size, stringHashmap.Size());
			Assert::AreEqual(size, charPtrHashmap.Size());

			auto intExpression = [&secondIntHashmap, &secondIntPair] {secondIntHashmap[secondIntPair.first]; };
			Assert::ExpectException<std::exception>(intExpression);

			auto ptrExpression = [&secondPtrHashmap, &secondPtrPair] {secondPtrHashmap[secondPtrPair.first]; };
			Assert::ExpectException<std::exception>(ptrExpression);

			auto fooExpression = [&secondFooHashmap, &secondFooPair] {secondFooHashmap[secondFooPair.first]; };
			Assert::ExpectException<std::exception>(fooExpression);

			auto stringExpression = [&secondStringHashmap, &secondStringPair] {secondStringHashmap[secondStringPair.first]; };
			Assert::ExpectException<std::exception>(stringExpression);

			auto charPtrExpression = [&secondCharPtrHashmap, &secondCharPtrPair] {secondCharPtrHashmap[secondCharPtrPair.first]; };
			Assert::ExpectException<std::exception>(charPtrExpression);
		}

		TEST_METHOD(HashmapRemove)
		{
			testFoo.Data(testInt);
			secondTestFoo.Data(secondTestInt);

			Hashmap<std::int32_t, std::int32_t> intHashmap;
			Hashmap<std::int32_t*, std::int32_t> ptrHashmap;
			Hashmap<Foo, std::int32_t> fooHashmap;
			Hashmap<std::string, std::int32_t> stringHashmap;
			Hashmap<char*, std::int32_t> charPtrHashmap;
			std::uint32_t size = 0;

			std::pair <std::int32_t, std::int32_t> intPair(testInt, testInt);
			std::pair <std::int32_t*, std::int32_t> ptrPair(testPtr, testInt);
			std::pair <Foo, std::int32_t> fooPair(testFoo, testInt);
			std::pair <std::string, std::int32_t> stringPair(testString, testInt);
			std::pair <char*, std::int32_t> charPtrPair(testCharPtr, testInt);

			std::pair <std::int32_t, std::int32_t> secondIntPair(secondTestInt, secondTestInt);
			std::pair <std::int32_t*, std::int32_t> secondPtrPair(secondTestPtr, secondTestInt);
			std::pair <Foo, std::int32_t> secondFooPair(secondTestFoo, secondTestInt);
			std::pair <std::string, std::int32_t> secondStringPair(secondTestString, secondTestInt);
			std::pair <char*, std::int32_t> secondCharPtrPair(secondTestCharPtr, secondTestInt);

			intHashmap.Insert(intPair);
			ptrHashmap.Insert(ptrPair);
			fooHashmap.Insert(fooPair);
			stringHashmap.Insert(stringPair);
			charPtrHashmap.Insert(charPtrPair);
			++size;

			intHashmap.Insert(secondIntPair);
			ptrHashmap.Insert(secondPtrPair);
			fooHashmap.Insert(secondFooPair);
			stringHashmap.Insert(secondStringPair);
			charPtrHashmap.Insert(secondCharPtrPair);
			++size;

			intHashmap.Remove(intPair.first);
			ptrHashmap.Remove(ptrPair.first);
			fooHashmap.Remove(fooPair.first);
			stringHashmap.Remove(stringPair.first);
			charPtrHashmap.Remove(charPtrPair.first);
			--size;

			Assert::AreEqual(size, intHashmap.Size());
			Assert::AreEqual(size, ptrHashmap.Size());
			Assert::AreEqual(size, fooHashmap.Size());
			Assert::AreEqual(size, stringHashmap.Size());
			Assert::AreEqual(size, charPtrHashmap.Size());

			intHashmap.Remove(intPair.first);
			ptrHashmap.Remove(ptrPair.first);
			fooHashmap.Remove(fooPair.first);
			stringHashmap.Remove(stringPair.first);
			charPtrHashmap.Remove(charPtrPair.first);

			Assert::AreEqual(size, intHashmap.Size());
			Assert::AreEqual(size, ptrHashmap.Size());
			Assert::AreEqual(size, fooHashmap.Size());
			Assert::AreEqual(size, stringHashmap.Size());
			Assert::AreEqual(size, charPtrHashmap.Size());
		}

		TEST_METHOD(HashmapClear)
		{
			testFoo.Data(testInt);
			secondTestFoo.Data(secondTestInt);

			Hashmap<std::int32_t, std::int32_t> intHashmap;
			Hashmap<std::int32_t*, std::int32_t> ptrHashmap;
			Hashmap<Foo, std::int32_t> fooHashmap;
			Hashmap<std::string, std::int32_t> stringHashmap;
			Hashmap<char*, std::int32_t> charPtrHashmap;

			std::pair <std::int32_t, std::int32_t> intPair(testInt, testInt);
			std::pair <std::int32_t*, std::int32_t> ptrPair(testPtr, testInt);
			std::pair <Foo, std::int32_t> fooPair(testFoo, testInt);
			std::pair <std::string, std::int32_t> stringPair(testString, testInt);
			std::pair <char*, std::int32_t> charPtrPair(testCharPtr, testInt);

			std::pair <std::int32_t, std::int32_t> secondIntPair(secondTestInt, secondTestInt);
			std::pair <std::int32_t*, std::int32_t> secondPtrPair(secondTestPtr, secondTestInt);
			std::pair <Foo, std::int32_t> secondFooPair(secondTestFoo, secondTestInt);
			std::pair <std::string, std::int32_t> secondStringPair(secondTestString, secondTestInt);
			std::pair <char*, std::int32_t> secondCharPtrPair(secondTestCharPtr, secondTestInt);

			intHashmap.Insert(intPair);
			ptrHashmap.Insert(ptrPair);
			fooHashmap.Insert(fooPair);
			stringHashmap.Insert(stringPair);
			charPtrHashmap.Insert(charPtrPair);

			intHashmap.Insert(secondIntPair);
			ptrHashmap.Insert(secondPtrPair);
			fooHashmap.Insert(secondFooPair);
			stringHashmap.Insert(secondStringPair);
			charPtrHashmap.Insert(secondCharPtrPair);

			intHashmap.Clear();
			ptrHashmap.Clear();
			fooHashmap.Clear();
			stringHashmap.Clear();
			charPtrHashmap.Clear();

			std::uint32_t size = 0;
			Assert::AreEqual(size, intHashmap.Size());
			Assert::AreEqual(size, ptrHashmap.Size());
			Assert::AreEqual(size, fooHashmap.Size());
			Assert::AreEqual(size, stringHashmap.Size());
			Assert::AreEqual(size, charPtrHashmap.Size());
		}
		
		TEST_METHOD(HashmapSize)
		{
			testFoo.Data(testInt);
			secondTestFoo.Data(secondTestInt);

			Hashmap<std::int32_t, std::int32_t> intHashmap;
			Hashmap<std::int32_t*, std::int32_t> ptrHashmap;
			Hashmap<Foo, std::int32_t> fooHashmap;
			Hashmap<std::string, std::int32_t> stringHashmap;
			Hashmap<char*, std::int32_t> charPtrHashmap;
			std::uint32_t size = 0;

			std::pair <std::int32_t, std::int32_t> intPair(testInt, testInt);
			std::pair <std::int32_t*, std::int32_t> ptrPair(testPtr, testInt);
			std::pair <Foo, std::int32_t> fooPair(testFoo, testInt);
			std::pair <std::string, std::int32_t> stringPair(testString, testInt);
			std::pair <char*, std::int32_t> charPtrPair(testCharPtr, testInt);

			std::pair <std::int32_t, std::int32_t> secondIntPair(secondTestInt, secondTestInt);
			std::pair <std::int32_t*, std::int32_t> secondPtrPair(secondTestPtr, secondTestInt);
			std::pair <Foo, std::int32_t> secondFooPair(secondTestFoo, secondTestInt);
			std::pair <std::string, std::int32_t> secondStringPair(secondTestString, secondTestInt);
			std::pair <char*, std::int32_t> secondCharPtrPair(secondTestCharPtr, secondTestInt);

			intHashmap.Insert(intPair);
			ptrHashmap.Insert(ptrPair);
			fooHashmap.Insert(fooPair);
			stringHashmap.Insert(stringPair);
			charPtrHashmap.Insert(charPtrPair);
			++size;

			intHashmap.Insert(secondIntPair);
			ptrHashmap.Insert(secondPtrPair);
			fooHashmap.Insert(secondFooPair);
			stringHashmap.Insert(secondStringPair);
			charPtrHashmap.Insert(secondCharPtrPair);
			++size;

			const Hashmap<std::int32_t, std::int32_t> secondIntHashmap(intHashmap);
			const Hashmap<std::int32_t*, std::int32_t> secondPtrHashmap(ptrHashmap);
			const Hashmap<Foo, std::int32_t> secondFooHashmap(fooHashmap);
			const Hashmap<std::string, std::int32_t> secondStringHashmap(stringHashmap);
			const Hashmap<char*, std::int32_t> secondCharPtrHashmap(charPtrHashmap);

			Assert::AreEqual(size, intHashmap.Size());
			Assert::AreEqual(size, ptrHashmap.Size());
			Assert::AreEqual(size, fooHashmap.Size());
			Assert::AreEqual(size, stringHashmap.Size());
			Assert::AreEqual(size, charPtrHashmap.Size());

			Assert::AreEqual(size, secondIntHashmap.Size());
			Assert::AreEqual(size, secondPtrHashmap.Size());
			Assert::AreEqual(size, secondFooHashmap.Size());
			Assert::AreEqual(size, secondStringHashmap.Size());
			Assert::AreEqual(size, secondCharPtrHashmap.Size());
		}

		TEST_METHOD(HashmapContainsKey)
		{
			testFoo.Data(testInt);
			secondTestFoo.Data(secondTestInt);

			Hashmap<std::int32_t, std::int32_t> intHashmap;
			Hashmap<std::int32_t*, std::int32_t> ptrHashmap;
			Hashmap<Foo, std::int32_t> fooHashmap;
			Hashmap<std::string, std::int32_t> stringHashmap;
			Hashmap<char*, std::int32_t> charPtrHashmap;

			std::pair <std::int32_t, std::int32_t> intPair(testInt, testInt);
			std::pair <std::int32_t*, std::int32_t> ptrPair(testPtr, testInt);
			std::pair <Foo, std::int32_t> fooPair(testFoo, testInt);
			std::pair <std::string, std::int32_t> stringPair(testString, testInt);
			std::pair <char*, std::int32_t> charPtrPair(testCharPtr, testInt);

			std::pair <std::int32_t, std::int32_t> secondIntPair(secondTestInt, secondTestInt);
			std::pair <std::int32_t*, std::int32_t> secondPtrPair(secondTestPtr, secondTestInt);
			std::pair <Foo, std::int32_t> secondFooPair(secondTestFoo, secondTestInt);
			std::pair <std::string, std::int32_t> secondStringPair(secondTestString, secondTestInt);
			std::pair <char*, std::int32_t> secondCharPtrPair(secondTestCharPtr, secondTestInt);

			intHashmap.Insert(intPair);
			ptrHashmap.Insert(ptrPair);
			fooHashmap.Insert(fooPair);
			stringHashmap.Insert(stringPair);
			charPtrHashmap.Insert(charPtrPair);

			Assert::IsTrue(intHashmap.ContainsKey(intPair.first));
			Assert::IsTrue(ptrHashmap.ContainsKey(ptrPair.first));
			Assert::IsTrue(fooHashmap.ContainsKey(fooPair.first));
			Assert::IsTrue(stringHashmap.ContainsKey(stringPair.first));
			Assert::IsTrue(charPtrHashmap.ContainsKey(charPtrPair.first));

			Assert::IsFalse(intHashmap.ContainsKey(secondIntPair.first));
			Assert::IsFalse(ptrHashmap.ContainsKey(secondPtrPair.first));
			Assert::IsFalse(fooHashmap.ContainsKey(secondFooPair.first));
			Assert::IsFalse(stringHashmap.ContainsKey(secondCharPtrPair.first));
			Assert::IsFalse(charPtrHashmap.ContainsKey(secondCharPtrPair.first));
		}

		TEST_METHOD(HashmapBegin)
		{
			testFoo.Data(testInt);

			Hashmap<std::int32_t, std::int32_t> intHashmap;
			Hashmap<std::int32_t*, std::int32_t> ptrHashmap;
			Hashmap<Foo, std::int32_t> fooHashmap;
			Hashmap<std::string, std::int32_t> stringHashmap;
			Hashmap<char*, std::int32_t> charPtrHashmap;

			std::pair <std::int32_t, std::int32_t> intPair(testInt, testInt);
			std::pair <std::int32_t*, std::int32_t> ptrPair(testPtr, testInt);
			std::pair <Foo, std::int32_t> fooPair(testFoo, testInt);
			std::pair <std::string, std::int32_t> stringPair(testString, testInt);
			std::pair <char*, std::int32_t> charPtrPair(testCharPtr, testInt);

			Hashmap<std::int32_t, std::int32_t>::Iterator intIt;
			Hashmap<std::int32_t*, std::int32_t>::Iterator ptrIt;
			Hashmap<Foo, std::int32_t>::Iterator fooIt;
			Hashmap<std::string, std::int32_t>::Iterator stringIt;
			Hashmap<char*, std::int32_t>::Iterator charPtrIt;

			intHashmap.Insert(intPair);
			ptrHashmap.Insert(ptrPair);
			fooHashmap.Insert(fooPair);
			stringHashmap.Insert(stringPair);
			charPtrHashmap.Insert(charPtrPair);

			const Hashmap<std::int32_t, std::int32_t> secondIntHashmap(intHashmap);
			const Hashmap<std::int32_t*, std::int32_t> secondPtrHashmap(ptrHashmap);
			const Hashmap<Foo, std::int32_t> secondFooHashmap(fooHashmap);
			const Hashmap<std::string, std::int32_t> secondStringHashmap(stringHashmap);
			const Hashmap<char*, std::int32_t> secondCharPtrHashmap(charPtrHashmap);

			intIt = intHashmap.begin();
			ptrIt = ptrHashmap.begin();
			fooIt = fooHashmap.begin();
			stringIt = stringHashmap.begin();
			charPtrIt = charPtrHashmap.begin();

			Assert::AreEqual((*intIt).first, intPair.first);
			Assert::AreEqual((*ptrIt).first, ptrPair.first);
			Assert::IsTrue((*fooIt).first == fooPair.first);
			Assert::AreEqual((*stringIt).first, stringPair.first);
			Assert::AreEqual((*charPtrIt).first, charPtrPair.first);

			intIt = secondIntHashmap.begin();
			ptrIt = secondPtrHashmap.begin();
			fooIt = secondFooHashmap.begin();
			stringIt = secondStringHashmap.begin();
			charPtrIt = secondCharPtrHashmap.begin();

			Assert::AreEqual((*intIt).first, intPair.first);
			Assert::AreEqual((*ptrIt).first, ptrPair.first);
			Assert::IsTrue((*fooIt).first == fooPair.first);
			Assert::AreEqual((*stringIt).first, stringPair.first);
			Assert::AreEqual((*charPtrIt).first, charPtrPair.first);
		}

		TEST_METHOD(HashmapEnd)
		{
			testFoo.Data(testInt);

			Hashmap<std::int32_t, std::int32_t> intHashmap;
			Hashmap<std::int32_t*, std::int32_t> ptrHashmap;
			Hashmap<Foo, std::int32_t> fooHashmap;
			Hashmap<std::string, std::int32_t> stringHashmap;
			Hashmap<char*, std::int32_t> charPtrHashmap;

			std::pair <std::int32_t, std::int32_t> intPair(testInt, testInt);
			std::pair <std::int32_t*, std::int32_t> ptrPair(testPtr, testInt);
			std::pair <Foo, std::int32_t> fooPair(testFoo, testInt);
			std::pair <std::string, std::int32_t> stringPair(testString, testInt);
			std::pair <char*, std::int32_t> charPtrPair(testCharPtr, testInt);

			Hashmap<std::int32_t, std::int32_t>::Iterator intIt;
			Hashmap<std::int32_t*, std::int32_t>::Iterator ptrIt;
			Hashmap<Foo, std::int32_t>::Iterator fooIt;
			Hashmap<std::string, std::int32_t>::Iterator stringIt;
			Hashmap<char*, std::int32_t>::Iterator charPtrIt;

			Hashmap<std::int32_t, std::int32_t>::Iterator secondIntIt;
			Hashmap<std::int32_t*, std::int32_t>::Iterator secondPtrIt;
			Hashmap<Foo, std::int32_t>::Iterator secondFooIt;
			Hashmap<std::string, std::int32_t>::Iterator secondStringIt;
			Hashmap<char*, std::int32_t>::Iterator secondCharPtrIt;

			intHashmap.Insert(intPair);
			ptrHashmap.Insert(ptrPair);
			fooHashmap.Insert(fooPair);
			stringHashmap.Insert(stringPair);
			charPtrHashmap.Insert(charPtrPair);

			const Hashmap<std::int32_t, std::int32_t> secondIntHashmap(intHashmap);
			const Hashmap<std::int32_t*, std::int32_t> secondPtrHashmap(ptrHashmap);
			const Hashmap<Foo, std::int32_t> secondFooHashmap(fooHashmap);
			const Hashmap<std::string, std::int32_t> secondStringHashmap(stringHashmap);
			const Hashmap<char*, std::int32_t> secondCharPtrHashmap(charPtrHashmap);

			intIt = intHashmap.begin();
			ptrIt = ptrHashmap.begin();
			fooIt = fooHashmap.begin();
			stringIt = stringHashmap.begin();
			charPtrIt = charPtrHashmap.begin();

			secondIntIt = intHashmap.end();
			secondPtrIt = ptrHashmap.end();
			secondFooIt = fooHashmap.end();
			secondStringIt = stringHashmap.end();
			secondCharPtrIt = charPtrHashmap.end();

			Assert::IsTrue(intIt != secondIntIt);
			Assert::IsTrue(ptrIt != secondPtrIt);
			Assert::IsTrue(fooIt != secondFooIt);
			Assert::IsTrue(stringIt != secondStringIt);
			Assert::IsTrue(charPtrIt != secondCharPtrIt);

			intIt = secondIntHashmap.begin();
			ptrIt = secondPtrHashmap.begin();
			fooIt = secondFooHashmap.begin();
			stringIt = secondStringHashmap.begin();
			charPtrIt = secondCharPtrHashmap.begin();

			secondIntIt = secondIntHashmap.end();
			secondPtrIt = secondPtrHashmap.end();
			secondFooIt = secondFooHashmap.end();
			secondStringIt = secondStringHashmap.end();
			secondCharPtrIt = secondCharPtrHashmap.end();

			Assert::IsTrue(intIt != secondIntIt);
			Assert::IsTrue(ptrIt != secondPtrIt);
			Assert::IsTrue(fooIt != secondFooIt);
			Assert::IsTrue(stringIt != secondStringIt);
			Assert::IsTrue(charPtrIt != secondCharPtrIt);
		}

		TEST_METHOD(HashmapComparisonOperators)
		{
			testFoo.Data(testInt);
			secondTestFoo.Data(secondTestInt);

			Hashmap<std::int32_t, std::int32_t> intHashmap;
			Hashmap<std::int32_t*, std::int32_t> ptrHashmap;
			Hashmap<Foo, std::int32_t> fooHashmap;
			Hashmap<std::string, std::int32_t> stringHashmap;
			Hashmap<char*, std::int32_t> charPtrHashmap;

			Hashmap<std::int32_t, std::int32_t> secondIntHashmap;
			Hashmap<std::int32_t*, std::int32_t> secondPtrHashmap;
			Hashmap<Foo, std::int32_t> secondFooHashmap;
			Hashmap<std::string, std::int32_t> secondStringHashmap;
			Hashmap<char*, std::int32_t> secondCharPtrHashmap;

			std::pair <std::int32_t, std::int32_t> intPair(testInt, testInt);
			std::pair <std::int32_t*, std::int32_t> ptrPair(testPtr, testInt);
			std::pair <Foo, std::int32_t> fooPair(testFoo, testInt);
			std::pair <std::string, std::int32_t> stringPair(testString, testInt);
			std::pair <char*, std::int32_t> charPtrPair(testCharPtr, testInt);

			std::pair <std::int32_t, std::int32_t> secondIntPair(secondTestInt, secondTestInt);
			std::pair <std::int32_t*, std::int32_t> secondPtrPair(secondTestPtr, secondTestInt);
			std::pair <Foo, std::int32_t> secondFooPair(secondTestFoo, secondTestInt);
			std::pair <std::string, std::int32_t> secondStringPair(secondTestString, secondTestInt);
			std::pair <char*, std::int32_t> secondCharPtrPair(secondTestCharPtr, secondTestInt);

			intHashmap.Insert(intPair);
			ptrHashmap.Insert(ptrPair);
			fooHashmap.Insert(fooPair);
			stringHashmap.Insert(stringPair);
			charPtrHashmap.Insert(charPtrPair);

			intHashmap.Insert(secondIntPair);
			ptrHashmap.Insert(secondPtrPair);
			fooHashmap.Insert(secondFooPair);
			stringHashmap.Insert(secondStringPair);
			charPtrHashmap.Insert(secondCharPtrPair);

			secondIntHashmap.Insert(intPair);
			secondPtrHashmap.Insert(ptrPair);
			secondFooHashmap.Insert(fooPair);
			secondStringHashmap.Insert(stringPair);
			secondCharPtrHashmap.Insert(charPtrPair);

			secondIntHashmap.Insert(secondIntPair);
			secondPtrHashmap.Insert(secondPtrPair);
			secondFooHashmap.Insert(secondFooPair);
			secondStringHashmap.Insert(secondStringPair);
			secondCharPtrHashmap.Insert(secondCharPtrPair);

			Assert::IsTrue(intHashmap == secondIntHashmap);
			Assert::IsTrue(ptrHashmap == secondPtrHashmap);
			Assert::IsTrue(fooHashmap == secondFooHashmap);
			Assert::IsTrue(stringHashmap == secondStringHashmap);
			Assert::IsTrue(charPtrHashmap == secondCharPtrHashmap);
		}

		TEST_METHOD(IteratorCopyConstructor)
		{
			testFoo.Data(testInt);

			Hashmap<std::int32_t, std::int32_t> intHashmap;
			Hashmap<std::int32_t*, std::int32_t> ptrHashmap;
			Hashmap<Foo, std::int32_t> fooHashmap;
			Hashmap<std::string, std::int32_t> stringHashmap;
			Hashmap<char*, std::int32_t> charPtrHashmap;

			std::pair <std::int32_t, std::int32_t> intPair(testInt, testInt);
			std::pair <std::int32_t*, std::int32_t> ptrPair(testPtr, testInt);
			std::pair <Foo, std::int32_t> fooPair(testFoo, testInt);
			std::pair <std::string, std::int32_t> stringPair(testString, testInt);
			std::pair <char*, std::int32_t> charPtrPair(testCharPtr, testInt);

			Hashmap<std::int32_t, std::int32_t>::Iterator intIt;
			Hashmap<std::int32_t*, std::int32_t>::Iterator ptrIt;
			Hashmap<Foo, std::int32_t>::Iterator fooIt;
			Hashmap<std::string, std::int32_t>::Iterator stringIt;
			Hashmap<char*, std::int32_t>::Iterator charPtrIt;

			intHashmap.Insert(intPair);
			ptrHashmap.Insert(ptrPair);
			fooHashmap.Insert(fooPair);
			stringHashmap.Insert(stringPair);
			charPtrHashmap.Insert(charPtrPair);

			intIt = intHashmap.begin();
			ptrIt = ptrHashmap.begin();
			fooIt = fooHashmap.begin();
			stringIt = stringHashmap.begin();
			charPtrIt = charPtrHashmap.begin();

			Hashmap<std::int32_t, std::int32_t>::Iterator secondIntIt(intIt);
			Hashmap<std::int32_t*, std::int32_t>::Iterator secondPtrIt(ptrIt);
			Hashmap<Foo, std::int32_t>::Iterator secondFooIt(fooIt);
			Hashmap<std::string, std::int32_t>::Iterator secondStringIt(stringIt);
			Hashmap<char*, std::int32_t>::Iterator secondCharPtrIt(charPtrIt);

			Assert::IsTrue(intIt == secondIntIt);
			Assert::IsTrue(ptrIt == secondPtrIt);
			Assert::IsTrue(fooIt == secondFooIt);
			Assert::IsTrue(stringIt == secondStringIt);
			Assert::IsTrue(charPtrIt == secondCharPtrIt);
		}

		TEST_METHOD(IteratorIncrementOperators)
		{
			testFoo.Data(testInt);
			secondTestFoo.Data(secondTestInt);

			Hashmap<std::int32_t, std::int32_t> intHashmap;
			Hashmap<std::int32_t*, std::int32_t> ptrHashmap;
			Hashmap<Foo, std::int32_t> fooHashmap;
			Hashmap<std::string, std::int32_t> stringHashmap;
			Hashmap<char*, std::int32_t> charPtrHashmap;

			std::pair <std::int32_t, std::int32_t> intPair(testInt, testInt);
			std::pair <std::int32_t*, std::int32_t> ptrPair(testPtr, testInt);
			std::pair <Foo, std::int32_t> fooPair(testFoo, testInt);
			std::pair <std::string, std::int32_t> stringPair(testString, testInt);
			std::pair <char*, std::int32_t> charPtrPair(testCharPtr, testInt);

			std::pair <std::int32_t, std::int32_t> secondIntPair(secondTestInt, secondTestInt);
			std::pair <std::int32_t*, std::int32_t> secondPtrPair(secondTestPtr, secondTestInt);
			std::pair <Foo, std::int32_t> secondFooPair(secondTestFoo, secondTestInt);
			std::pair <std::string, std::int32_t> secondStringPair(secondTestString, secondTestInt);
			std::pair <char*, std::int32_t> secondCharPtrPair(secondTestCharPtr, secondTestInt);

			intHashmap.Insert(intPair);
			ptrHashmap.Insert(ptrPair);
			fooHashmap.Insert(fooPair);
			stringHashmap.Insert(stringPair);
			charPtrHashmap.Insert(charPtrPair);

			intHashmap.Insert(secondIntPair);
			ptrHashmap.Insert(secondPtrPair);
			fooHashmap.Insert(secondFooPair);
			stringHashmap.Insert(secondStringPair);
			charPtrHashmap.Insert(secondCharPtrPair);

			Hashmap<std::int32_t, std::int32_t>::Iterator intIt;
			Hashmap<std::int32_t*, std::int32_t>::Iterator ptrIt;
			Hashmap<Foo, std::int32_t>::Iterator fooIt;
			Hashmap<std::string, std::int32_t>::Iterator stringIt;
			Hashmap<char*, std::int32_t>::Iterator charPtrIt;

			auto intExpression = [&intIt] {++intIt; };
			Assert::ExpectException<std::exception>(intExpression);
			
			auto ptrExpression = [&ptrIt] {++ptrIt; };
			Assert::ExpectException<std::exception>(ptrExpression);

			auto fooExpression = [&fooIt] {++fooIt; };
			Assert::ExpectException<std::exception>(fooExpression);

			auto stringExpression = [&stringIt] {++stringIt; };
			Assert::ExpectException<std::exception>(stringExpression);

			auto charPtrExpression = [&charPtrIt] {++charPtrIt; };
			Assert::ExpectException<std::exception>(charPtrExpression);

			auto secondIntExpression = [&intIt] {intIt++; };
			Assert::ExpectException<std::exception>(secondIntExpression);

			auto secondPtrExpression = [&ptrIt] {ptrIt++; };
			Assert::ExpectException<std::exception>(secondPtrExpression);

			auto secondFooExpression = [&fooIt] {fooIt++; };
			Assert::ExpectException<std::exception>(secondFooExpression);

			auto secondStringExpression = [&stringIt] {stringIt++; };
			Assert::ExpectException<std::exception>(secondStringExpression);

			auto secondCharPtrExpression = [&charPtrIt] {charPtrIt++; };
			Assert::ExpectException<std::exception>(secondCharPtrExpression);

			intIt = intHashmap.begin();
			ptrIt = ptrHashmap.begin();
			fooIt = fooHashmap.begin();
			stringIt = stringHashmap.begin();
			charPtrIt = charPtrHashmap.begin();

			Hashmap<std::int32_t, std::int32_t>::Iterator secondIntIt(intIt);
			Hashmap<std::int32_t*, std::int32_t>::Iterator secondPtrIt(ptrIt);
			Hashmap<Foo, std::int32_t>::Iterator secondFooIt(fooIt);
			Hashmap<std::string, std::int32_t>::Iterator secondStringIt(stringIt);
			Hashmap<char*, std::int32_t>::Iterator secondCharPtrIt(charPtrIt);

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

		TEST_METHOD(IteratorDereferenceOperators)
		{
			testFoo.Data(testInt);

			Hashmap<std::int32_t, std::int32_t> intHashmap;
			Hashmap<std::int32_t*, std::int32_t> ptrHashmap;
			Hashmap<Foo, std::int32_t> fooHashmap;
			Hashmap<std::string, std::int32_t> stringHashmap;
			Hashmap<char*, std::int32_t> charPtrHashmap;

			std::pair <std::int32_t, std::int32_t> intPair(testInt, testInt);
			std::pair <std::int32_t*, std::int32_t> ptrPair(testPtr, testInt);
			std::pair <Foo, std::int32_t> fooPair(testFoo, testInt);
			std::pair <std::string, std::int32_t> stringPair(testString, testInt);
			std::pair <char*, std::int32_t> charPtrPair(testCharPtr, testInt);

			intHashmap.Insert(intPair);
			ptrHashmap.Insert(ptrPair);
			fooHashmap.Insert(fooPair);
			stringHashmap.Insert(stringPair);
			charPtrHashmap.Insert(charPtrPair);

			Hashmap<std::int32_t, std::int32_t>::Iterator intIt;
			Hashmap<std::int32_t*, std::int32_t>::Iterator ptrIt;
			Hashmap<Foo, std::int32_t>::Iterator fooIt;
			Hashmap<std::string, std::int32_t>::Iterator stringIt;
			Hashmap<char*, std::int32_t>::Iterator charPtrIt;

			auto intExpression = [&intIt] {*intIt; };
			Assert::ExpectException<std::exception>(intExpression);

			auto ptrExpression = [&ptrIt] {*ptrIt; };
			Assert::ExpectException<std::exception>(ptrExpression);

			auto fooExpression = [&fooIt] {*fooIt; };
			Assert::ExpectException<std::exception>(fooExpression);

			auto stringExpression = [&stringIt] {*stringIt; };
			Assert::ExpectException<std::exception>(stringExpression);

			auto charPtrExpression = [&charPtrIt] {*charPtrIt; };
			Assert::ExpectException<std::exception>(charPtrExpression);

			auto secondIntExpression = [&intIt] {intIt->first; };
			Assert::ExpectException<std::exception>(secondIntExpression);

			auto secondPtrExpression = [&ptrIt] {ptrIt->first; };
			Assert::ExpectException<std::exception>(secondPtrExpression);

			auto secondFooExpression = [&fooIt] {fooIt->first; };
			Assert::ExpectException<std::exception>(secondFooExpression);

			auto secondStringExpression = [&stringIt] {stringIt->first; };
			Assert::ExpectException<std::exception>(secondStringExpression);

			auto secondCharPtrExpression = [&charPtrIt] {charPtrIt->first; };
			Assert::ExpectException<std::exception>(secondCharPtrExpression);

			intIt = intHashmap.begin();
			ptrIt = ptrHashmap.begin();
			fooIt = fooHashmap.begin();
			stringIt = stringHashmap.begin();
			charPtrIt = charPtrHashmap.begin();

			const Hashmap<std::int32_t, std::int32_t>::Iterator secondIntIt(intIt);
			const Hashmap<std::int32_t*, std::int32_t>::Iterator secondPtrIt(ptrIt);
			const Hashmap<Foo, std::int32_t>::Iterator secondFooIt(fooIt);
			const Hashmap<std::string, std::int32_t>::Iterator secondStringIt(stringIt);
			const Hashmap<char*, std::int32_t>::Iterator secondCharPtrIt(charPtrIt);

			Assert::IsTrue((*intIt).first == intPair.first);
			Assert::IsTrue((*ptrIt).first == ptrPair.first);
			Assert::IsTrue((*fooIt).first == fooPair.first);
			Assert::IsTrue((*stringIt).first == stringPair.first);
			Assert::IsTrue((*charPtrIt).first == charPtrPair.first);

			Assert::IsTrue(intIt->first == intPair.first);
			Assert::IsTrue(ptrIt->first == ptrPair.first);
			Assert::IsTrue(fooIt->first == fooPair.first);
			Assert::IsTrue(stringIt->first == stringPair.first);
			Assert::IsTrue(charPtrIt->first == charPtrPair.first);

			Assert::IsTrue((*secondIntIt).first == intPair.first);
			Assert::IsTrue((*secondPtrIt).first == ptrPair.first);
			Assert::IsTrue((*secondFooIt).first == fooPair.first);
			Assert::IsTrue((*secondStringIt).first == stringPair.first);
			Assert::IsTrue((*secondCharPtrIt).first == charPtrPair.first);

			Assert::IsTrue(secondIntIt->first == intPair.first);
			Assert::IsTrue(secondPtrIt->first == ptrPair.first);
			Assert::IsTrue(secondFooIt->first == fooPair.first);
			Assert::IsTrue(secondStringIt->first == stringPair.first);
			Assert::IsTrue(secondCharPtrIt->first == charPtrPair.first);

			const Hashmap<std::int32_t, std::int32_t>::Iterator thirdIntIt;
			const Hashmap<std::int32_t*, std::int32_t>::Iterator thirdPtrIt;
			const Hashmap<Foo, std::int32_t>::Iterator thirdFooIt;
			const Hashmap<std::string, std::int32_t>::Iterator thirdStringIt;
			const Hashmap<char*, std::int32_t>::Iterator thirdCharPtrIt;

			auto thirdIntExpression = [&thirdIntIt] {*thirdIntIt; };
			Assert::ExpectException<std::exception>(thirdIntExpression);

			auto thirdPtrExpression = [&thirdPtrIt] {*thirdPtrIt; };
			Assert::ExpectException<std::exception>(thirdPtrExpression);

			auto thirdFooExpression = [&thirdFooIt] {*thirdFooIt; };
			Assert::ExpectException<std::exception>(thirdFooExpression);

			auto thirdStringExpression = [&thirdStringIt] {*thirdStringIt; };
			Assert::ExpectException<std::exception>(thirdStringExpression);

			auto thirdCharPtrExpression = [&thirdCharPtrIt] {*thirdCharPtrIt; };
			Assert::ExpectException<std::exception>(thirdCharPtrExpression);

			auto fourthIntExpression = [&thirdIntIt] {thirdIntIt->first; };
			Assert::ExpectException<std::exception>(fourthIntExpression);

			auto fourthPtrExpression = [&thirdPtrIt] {thirdPtrIt->first; };
			Assert::ExpectException<std::exception>(fourthPtrExpression);

			auto fourthFooExpression = [&thirdFooIt] {thirdFooIt->first; };
			Assert::ExpectException<std::exception>(fourthFooExpression);

			auto fourthStringExpression = [&thirdStringIt] {thirdStringIt->first; };
			Assert::ExpectException<std::exception>(fourthStringExpression);

			auto fourthCharPtrExpression = [&thirdCharPtrIt] {thirdCharPtrIt->first; };
			Assert::ExpectException<std::exception>(fourthCharPtrExpression);
		}

		TEST_METHOD(IncrementComparisonOperators)
		{
			testFoo.Data(testInt);

			Hashmap<std::int32_t, std::int32_t> intHashmap;
			Hashmap<std::int32_t*, std::int32_t> ptrHashmap;
			Hashmap<Foo, std::int32_t> fooHashmap;
			Hashmap<std::string, std::int32_t> stringHashmap;
			Hashmap<char*, std::int32_t> charPtrHashmap;

			std::pair <std::int32_t, std::int32_t> intPair(testInt, testInt);
			std::pair <std::int32_t*, std::int32_t> ptrPair(testPtr, testInt);
			std::pair <Foo, std::int32_t> fooPair(testFoo, testInt);
			std::pair <std::string, std::int32_t> stringPair(testString, testInt);
			std::pair <char*, std::int32_t> charPtrPair(testCharPtr, testInt);

			intHashmap.Insert(intPair);
			ptrHashmap.Insert(ptrPair);
			fooHashmap.Insert(fooPair);
			stringHashmap.Insert(stringPair);
			charPtrHashmap.Insert(charPtrPair);

			Hashmap<std::int32_t, std::int32_t>::Iterator intIt;
			Hashmap<std::int32_t*, std::int32_t>::Iterator ptrIt;
			Hashmap<Foo, std::int32_t>::Iterator fooIt;
			Hashmap<std::string, std::int32_t>::Iterator stringIt;
			Hashmap<char*, std::int32_t>::Iterator charPtrIt;

			intIt = intHashmap.begin();
			ptrIt = ptrHashmap.begin();
			fooIt = fooHashmap.begin();
			stringIt = stringHashmap.begin();
			charPtrIt = charPtrHashmap.begin();

			Hashmap<std::int32_t, std::int32_t>::Iterator secondIntIt(intIt);
			Hashmap<std::int32_t*, std::int32_t>::Iterator secondPtrIt(ptrIt);
			Hashmap<Foo, std::int32_t>::Iterator secondFooIt(fooIt);
			Hashmap<std::string, std::int32_t>::Iterator secondStringIt(stringIt);
			Hashmap<char*, std::int32_t>::Iterator secondCharPtrIt(charPtrIt);

			Assert::IsTrue(intIt == secondIntIt);
			Assert::IsTrue(ptrIt == secondPtrIt);
			Assert::IsTrue(fooIt == secondFooIt);
			Assert::IsTrue(stringIt == secondStringIt);
			Assert::IsTrue(charPtrIt == secondCharPtrIt);

			Assert::IsFalse(intIt != secondIntIt);
			Assert::IsFalse(ptrIt != secondPtrIt);
			Assert::IsFalse(fooIt != secondFooIt);
			Assert::IsFalse(stringIt != secondStringIt);
			Assert::IsFalse(charPtrIt != secondCharPtrIt);
		}

		TEST_METHOD(IteratorAssignmentOperator)
		{
			testFoo.Data(testInt);

			Hashmap<std::int32_t, std::int32_t> intHashmap;
			Hashmap<std::int32_t*, std::int32_t> ptrHashmap;
			Hashmap<Foo, std::int32_t> fooHashmap;
			Hashmap<std::string, std::int32_t> stringHashmap;
			Hashmap<char*, std::int32_t> charPtrHashmap;

			std::pair <std::int32_t, std::int32_t> intPair(testInt, testInt);
			std::pair <std::int32_t*, std::int32_t> ptrPair(testPtr, testInt);
			std::pair <Foo, std::int32_t> fooPair(testFoo, testInt);
			std::pair <std::string, std::int32_t> stringPair(testString, testInt);
			std::pair <char*, std::int32_t> charPtrPair(testCharPtr, testInt);

			intHashmap.Insert(intPair);
			ptrHashmap.Insert(ptrPair);
			fooHashmap.Insert(fooPair);
			stringHashmap.Insert(stringPair);
			charPtrHashmap.Insert(charPtrPair);

			Hashmap<std::int32_t, std::int32_t>::Iterator intIt;
			Hashmap<std::int32_t*, std::int32_t>::Iterator ptrIt;
			Hashmap<Foo, std::int32_t>::Iterator fooIt;
			Hashmap<std::string, std::int32_t>::Iterator stringIt;
			Hashmap<char*, std::int32_t>::Iterator charPtrIt;

			intIt = intHashmap.begin();
			ptrIt = ptrHashmap.begin();
			fooIt = fooHashmap.begin();
			stringIt = stringHashmap.begin();
			charPtrIt = charPtrHashmap.begin();

			Hashmap<std::int32_t, std::int32_t>::Iterator secondIntIt;
			Hashmap<std::int32_t*, std::int32_t>::Iterator secondPtrIt;
			Hashmap<Foo, std::int32_t>::Iterator secondFooIt;
			Hashmap<std::string, std::int32_t>::Iterator secondStringIt;
			Hashmap<char*, std::int32_t>::Iterator secondCharPtrIt;

			intIt = secondIntIt;
			ptrIt = secondPtrIt;
			fooIt = secondFooIt;
			stringIt = secondStringIt;
			charPtrIt = secondCharPtrIt;

			Assert::IsTrue(intIt == secondIntIt);
			Assert::IsTrue(ptrIt == secondPtrIt);
			Assert::IsTrue(fooIt == secondFooIt);
			Assert::IsTrue(stringIt == secondStringIt);
			Assert::IsTrue(charPtrIt == secondCharPtrIt);
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

	_CrtMemState HashmapTest::sStartMemState;
}