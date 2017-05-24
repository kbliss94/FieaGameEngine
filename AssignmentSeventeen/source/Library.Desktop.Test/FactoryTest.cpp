#include "pch.h"
#include "TestFoo.h"
#include "CppUnitTest.h"
#include "Factory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	ConcreteFactory(Library::RTTI, Foo)

	TEST_CLASS(FactoryTest)
	{
	public:

		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD(FooFactoryMacro)
		{
			FooFactory f;
			
			Assert::IsTrue(f.ClassName() == "Foo");
			Assert::IsTrue(f.Find(f.ClassName()) == &f);
			Assert::IsTrue(f.begin()->first == "Foo");
			Assert::IsTrue(f.begin() != f.end());

			Library::RTTI* testPtr = Factory<Library::RTTI>::Create(f.ClassName());
			Library::RTTI* testPtrTwo = Factory<Library::RTTI>::Create("Bar");

			Assert::IsNull(testPtrTwo);

			delete testPtr;
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

	_CrtMemState FactoryTest::sStartMemState;
}