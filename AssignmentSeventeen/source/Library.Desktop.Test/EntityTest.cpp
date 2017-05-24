#include "pch.h"
#include "CppUnitTest.h"
#include "Entity.h"
#include "Sector.h"
#include "World.h"
#include "WorldState.h"
#include "TestEntity.h"
#include "XMLParseMaster.h"
#include "SharedDataTable.h"
#include "XMLParseHelperWorld.h"
#include "XMLParseHelperInteger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	ConcreteFactory(Entity, TestEntity)

	TEST_CLASS(EntityTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD(RTTITests)
		{
			TestEntityFactory entityFactory;

			World world;
			Library::RTTI* worldPtr = &world;

			Assert::IsTrue(nullptr == worldPtr->QueryInterface(5));
			Assert::IsFalse(worldPtr->Is(5));
			Assert::IsFalse(worldPtr->Is("kaitlyn"));
			Assert::IsFalse(nullptr == worldPtr->As<World>());
			Assert::IsTrue(&world == worldPtr->As<World>());

			Sector* sector = world.CreateSector("testSector");
			Library::RTTI* sectorPtr = sector;

			Assert::IsTrue(nullptr == sectorPtr->QueryInterface(5));
			Assert::IsFalse(sectorPtr->Is(5));
			Assert::IsFalse(sectorPtr->Is("kaitlyn"));
			Assert::IsFalse(nullptr == sectorPtr->As<Sector>());
			Assert::IsTrue(sector == sectorPtr->As<Sector>());
		}

		TEST_METHOD(WorldName)
		{
			World world;

			Assert::IsTrue(world.Name() == "");
		}

		TEST_METHOD(WorldSetName)
		{
			World worldstar;
			worldstar.SetName("hiphop");

			Assert::IsTrue("hiphop" == worldstar.Name());
			Assert::IsTrue(worldstar.IsPrescribedAttribute("Name"));
			Assert::IsTrue(worldstar.IsPrescribedAttribute("Sectors"));
			Assert::IsFalse(worldstar.IsPrescribedAttribute("hey"));
		}

		TEST_METHOD(WorldCreateSector)
		{
			World world;
			Sector* sectorPtrOne = world.CreateSector("OPI");
			Sector* sectorPtrTwo = world.CreateSector("Essie");
			Datum& sectors = world.Sectors();

			Assert::IsTrue(sectors.Type() == DatumType::Table);
			Assert::IsTrue(sectors.Size() == 2);

			Sector* scopeOne;
			scopeOne = static_cast<Sector*>(&(sectors.Get<Scope&>()));

			Sector* scopeTwo;
			scopeTwo = static_cast<Sector*>(&(sectors.Get<Scope&>(1)));

			Assert::IsTrue(sectorPtrOne->Equals(scopeOne));
			Assert::IsTrue(sectorPtrTwo->Equals(scopeTwo));
			Assert::IsTrue(scopeOne->Name() == "OPI");
			Assert::IsTrue(scopeTwo->Name() == "Essie");
		}

		TEST_METHOD(WorldUpdate)
		{
			TestEntityFactory entityFactory;

			WorldState state;
			World world;
			Sector* sectorPtrOne = world.CreateSector("OPI");
			Sector* sectorPtrTwo = world.CreateSector("Essie");
			Entity* entityPtrOne = sectorPtrOne->CreateEntity("TestEntity", "Red");
			Entity* entityPtrTwo = sectorPtrTwo->CreateEntity("TestEntity", "Blue");

			world.Update(state);

			Assert::IsTrue(state.mWorld == &world);
			Assert::IsTrue(state.mSector == sectorPtrTwo);
			Assert::IsFalse(state.mSector == sectorPtrOne);
			Assert::IsFalse(state.mEntity == entityPtrOne);
			Assert::IsTrue(state.mEntity == entityPtrTwo);
		}

		TEST_METHOD(SectorSetName)
		{
			World world;
			Sector* sectorPtrOne = world.CreateSector("OPI");
			Sector* sectorPtrTwo = world.CreateSector("Essie");

			sectorPtrOne->SetName("One");
			sectorPtrTwo->SetName("Two");

			Assert::IsTrue("One" == sectorPtrOne->Name());
			Assert::IsTrue("Two" == sectorPtrTwo->Name());
		}

		TEST_METHOD(SectorCreateEntity)
		{
			TestEntityFactory entityFactory;

			World world;
			Sector* sectorPtrOne = world.CreateSector("OPI");
			Sector* sectorPtrTwo = world.CreateSector("Essie");
			Entity* entityPtrOne = sectorPtrOne->CreateEntity("TestEntity", "Red");
			Entity* entityPtrTwo = sectorPtrTwo->CreateEntity("TestEntity", "Blue");

			Assert::IsTrue(entityPtrOne->Name() == "Red");
			Assert::IsTrue(entityPtrTwo->Name() == "Blue");
			
			Datum& entitiesOne = sectorPtrOne->Entities();
			Datum& entitiesTwo = sectorPtrTwo->Entities();

			Assert::IsTrue(entitiesOne.Size() == 1);
			Assert::IsTrue(entitiesTwo.Size() == 1);
		}

		TEST_METHOD(SectorGetWorld)
		{
			World world;
			Sector* sectorPtrOne = world.CreateSector("OPI");

			Assert::IsTrue(&world == sectorPtrOne->GetWorld());
		}

		TEST_METHOD(EntitySetName)
		{
			TestEntityFactory entityFactory;

			World world;
			Sector* sectorPtrOne = world.CreateSector("OPI");
			Sector* sectorPtrTwo = world.CreateSector("Essie");
			Entity* entityPtrOne = sectorPtrOne->CreateEntity("TestEntity", "Red");
			Entity* entityPtrTwo = sectorPtrTwo->CreateEntity("TestEntity", "Blue");

			entityPtrOne->SetName("One");
			entityPtrTwo->SetName("Two");

			Assert::IsTrue(entityPtrOne->Name() == "One");
			Assert::IsTrue(entityPtrTwo->Name() == "Two");
		}

		TEST_METHOD(EntityGetSector)
		{
			TestEntityFactory entityFactory;

			World world;
			Sector* sectorPtrOne = world.CreateSector("OPI");
			Sector* sectorPtrTwo = world.CreateSector("Essie");
			Entity* entityPtrOne = sectorPtrOne->CreateEntity("TestEntity", "Red");
			Entity* entityPtrTwo = sectorPtrTwo->CreateEntity("TestEntity", "Blue");

			Assert::IsTrue(sectorPtrOne == entityPtrOne->GetSector());
			Assert::IsTrue(sectorPtrTwo == entityPtrTwo->GetSector());
		}

		TEST_METHOD(ParseHelperWorldParse)
		{
			TestEntityFactory entityFactory;

			SharedDataTable data;
			XMLParseMaster master(data);
			XMLParseHelperWorld worldHelper;
			XMLParseHelperInteger integerHelper;
			const char* xml = "<world name=\"KaitlynWorld\"> <sector name=\"KTown\"> <entity class=\"TestEntity\" name=\"Kaitlyn\"> <entry type=\"Integer\" name=\"Health\" value=\"10\"/> </entity> </sector> </world>";

			master.AddHelper(worldHelper);
			master.AddHelper(integerHelper);
			master.Parse(xml, static_cast<std::uint32_t>(strlen(xml)), true);

			Assert::IsTrue(data.MaxDepth() == 4);
		}

		TEST_METHOD(ParseFromFile)
		{
			TestEntityFactory entityFactory;

			SharedDataTable data;
			XMLParseMaster master(data);
			XMLParseHelperWorld worldHelper;
			XMLParseHelperInteger integerHelper;
			const char* filename = "..\\..\\..\\worldXML.txt";

			master.AddHelper(worldHelper);
			master.AddHelper(integerHelper);
			master.ParseFromFile(filename);

			Assert::IsTrue(data.MaxDepth() == 4);
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

	_CrtMemState EntityTest::sStartMemState;
}