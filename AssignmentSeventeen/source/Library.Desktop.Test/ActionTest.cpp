#include "pch.h"
#include "CppUnitTest.h"
#include "World.h"
#include "Factory.h"
#include "ActionList.h"
#include "ActionIf.h"
#include "ActionCreateAction.h"
#include "ActionDestroyAction.h"
#include "SharedDataTable.h"
#include "TestEntity.h"
#include "XMLParseMaster.h"
#include "XMLParseHelperIf.h"
#include "XMLParseHelperWorld.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	ConcreteFactory(Action, ActionList)
	ConcreteFactory(Action, ActionIf)
	ConcreteFactory(Action, ActionCreateAction)
	ConcreteFactory(Action, ActionDestroyAction)
	ConcreteFactory(Entity, TestEntity)

	TEST_CLASS(ActionTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD(RTTITests)
		{
			ActionListFactory actionListFactory;
			TestEntityFactory entityFactory;

			World world;
			Sector* sectorPtr = world.CreateSector("OPI");
			Entity* entityPtr = sectorPtr->CreateEntity("TestEntity", "Red");
			Action* actionPtr = entityPtr->CreateAction("ActionList", "Paint");

			Assert::IsTrue(nullptr == entityPtr->QueryInterface(5));
			Assert::IsFalse(entityPtr->Is(5));
			Assert::IsFalse(entityPtr->Is("kaitlyn"));
			Assert::IsFalse(nullptr == entityPtr->As<Entity>());
			Assert::IsTrue(entityPtr == entityPtr->As<Entity>());

			Assert::IsTrue(nullptr == actionPtr->QueryInterface(5));
			Assert::IsFalse(actionPtr->Is(5));
			Assert::IsFalse(actionPtr->Is("kaitlyn"));
			Assert::IsFalse(nullptr == actionPtr->As<Action>());
			Assert::IsTrue(actionPtr == actionPtr->As<Action>());
		}

		TEST_METHOD(ParseHelperIfClone)
		{
			XMLParseHelperIf ifHelper;
			XMLParseHelperIf* ifHelperClone;

			ifHelperClone = ifHelper.Clone();
			Assert::IsTrue(ifHelperClone->IsClone());

			delete ifHelperClone;
		}

		TEST_METHOD(ParseHelperWorldClone)
		{
			XMLParseHelperWorld worldHelper;
			XMLParseHelperWorld* worldHelperClone;

			worldHelperClone = worldHelper.Clone();
			Assert::IsTrue(worldHelperClone->IsClone());

			delete worldHelperClone;
		}

		TEST_METHOD(EntityCreateAction)
		{
			ActionListFactory actionListFactory;
			TestEntityFactory entityFactory;

			World world;
			Sector* sectorPtr = world.CreateSector("OPI");
			Entity* entityPtr = sectorPtr->CreateEntity("TestEntity", "Red");
			Action* actionPtrOne = entityPtr->CreateAction("ActionList", "Paint");
			Action* actionPtrTwo = entityPtr->CreateAction("ActionList", "Draw");

			Assert::IsTrue(actionPtrOne->Name() == "Paint");
			Assert::IsTrue(actionPtrTwo->Name() == "Draw");
			Assert::IsTrue(actionPtrOne->GetParent() == entityPtr);
			Assert::IsTrue(actionPtrTwo->GetParent() == entityPtr);
			Assert::IsTrue(actionPtrOne->Is("ActionList"));
			Assert::IsTrue(actionPtrTwo->Is("ActionList"));

			Datum& actions = entityPtr->Actions();

			Assert::IsTrue(actions.Size() == 2);
			Assert::IsTrue(actions.Get<Scope&>().Equals(actionPtrOne));
			Assert::IsTrue(actions.Get<Scope&>(1).Equals(actionPtrTwo));
		}

		TEST_METHOD(ActionSetName)
		{
			ActionListFactory actionListFactory;
			TestEntityFactory entityFactory;

			World world;
			Sector* sectorPtr = world.CreateSector("OPI");
			Entity* entityPtr = sectorPtr->CreateEntity("TestEntity", "Red");
			Action* actionPtrOne = entityPtr->CreateAction("ActionList", "Paint");
			Action* actionPtrTwo = entityPtr->CreateAction("ActionList", "Draw");

			Assert::IsTrue(actionPtrOne->Name() == "Paint");
			Assert::IsTrue(actionPtrTwo->Name() == "Draw");

			actionPtrOne->SetName("One");
			actionPtrTwo->SetName("Two");

			Assert::IsTrue(actionPtrOne->Name() == "One");
			Assert::IsTrue(actionPtrTwo->Name() == "Two");
		}

		TEST_METHOD(ActionListCreateAction)
		{
			ActionListFactory actionListFactory;
			TestEntityFactory entityFactory;
			ActionCreateActionFactory actionCreateFactory;
			ActionDestroyActionFactory actionDestroyFactory;

			World world;
			Sector* sectorPtr = world.CreateSector("OPI");
			Entity* entityPtr = sectorPtr->CreateEntity("TestEntity", "Red");
			ActionList* actionListPtr = static_cast<ActionList*>(entityPtr->CreateAction("ActionList", "Paint"));
			Action* actionCreatePtr = actionListPtr->CreateAction("ActionCreateAction", "CreateAction");
			Action* actionDestroyPtr = actionListPtr->CreateAction("ActionDestroyAction", "DestroyAction");

			Assert::IsTrue(actionCreatePtr->GetParent() == actionListPtr);
			Assert::IsTrue(actionDestroyPtr->GetParent() == actionListPtr);
			Assert::IsTrue(actionCreatePtr->Name() == "CreateAction");
			Assert::IsTrue(actionDestroyPtr->Name() == "DestroyAction");
			Assert::IsTrue(actionCreatePtr->Is("ActionCreateAction"));
			Assert::IsTrue(actionDestroyPtr->Is("ActionDestroyAction"));

			Datum& actions = actionListPtr->Actions();

			Assert::IsTrue(actions.Size() == 2);
			Assert::IsTrue(actions.Get<Scope&>().Equals(actionCreatePtr));
			Assert::IsTrue(actions.Get<Scope&>(1).Equals(actionDestroyPtr));
		}

		TEST_METHOD(ACASetAttributes)
		{
			ActionListFactory actionListFactory;
			TestEntityFactory entityFactory;
			ActionCreateActionFactory actionCreateFactory;

			World world;
			Sector* sectorPtr = world.CreateSector("OPI");
			Entity* entityPtr = sectorPtr->CreateEntity("TestEntity", "Red");
			ActionList* actionListPtr = static_cast<ActionList*>(entityPtr->CreateAction("ActionList", "Paint"));
			ActionCreateAction* actionCreatePtr = static_cast<ActionCreateAction*>(actionListPtr->CreateAction("ActionCreateAction", "CreateAction"));

			Assert::IsTrue(actionCreatePtr->PrototypeClassName() == "");
			Assert::IsTrue(actionCreatePtr->PrototypeInstanceName() == "");

			actionCreatePtr->SetPrototypeClassName("class");
			actionCreatePtr->SetPrototypeInstanceName("instance");

			Assert::IsTrue(actionCreatePtr->PrototypeClassName() == "class");
			Assert::IsTrue(actionCreatePtr->PrototypeInstanceName() == "instance");
		}

		TEST_METHOD(ADASetAttributes)
		{
			ActionListFactory actionListFactory;
			TestEntityFactory entityFactory;
			ActionDestroyActionFactory actionDestroyFactory;

			World world;
			Sector* sectorPtr = world.CreateSector("OPI");
			Entity* entityPtr = sectorPtr->CreateEntity("TestEntity", "Red");
			ActionList* actionListPtr = static_cast<ActionList*>(entityPtr->CreateAction("ActionList", "Paint"));
			ActionDestroyAction* actionDestroyPtr = static_cast<ActionDestroyAction*>(actionListPtr->CreateAction("ActionDestroyAction", "DestroyAction"));

			Assert::IsTrue(actionDestroyPtr->ActionToDestroy() == "");

			actionDestroyPtr->SetActionToDestroy("destroy");

			Assert::IsTrue(actionDestroyPtr->ActionToDestroy() == "destroy");
		}

		TEST_METHOD(ActionUpdate)
		{
			ActionListFactory actionListFactory;
			TestEntityFactory entityFactory;
			ActionCreateActionFactory actionCreateFactory;
			ActionDestroyActionFactory actionDestroyFactory;

			World world;
			WorldState state;
			Sector* sectorPtr = world.CreateSector("OPI");
			Entity* entityPtr = sectorPtr->CreateEntity("TestEntity", "Red");
			ActionList* actionListPtr = static_cast<ActionList*>(entityPtr->CreateAction("ActionList", "Paint"));
			ActionCreateAction* actionCreatePtr = static_cast<ActionCreateAction*>(actionListPtr->CreateAction("ActionCreateAction", "create"));

			Datum& actions = actionListPtr->Actions();

			Assert::IsTrue(actions.Size() == 1);

			actionCreatePtr->SetPrototypeClassName("ActionDestroyAction");
			actionCreatePtr->SetPrototypeInstanceName("destroy");

			world.Update(state);

			Assert::IsTrue(actions.Size() == 2);
			
			ActionDestroyAction* actionDestroyPtr = static_cast<ActionDestroyAction*>(&actions.Get<Scope&>(1));
			actionDestroyPtr->SetActionToDestroy("create");
			actionCreatePtr->SetPrototypeClassName("");
			actionCreatePtr->SetPrototypeInstanceName("");

			world.Update(state);

			Assert::IsTrue(actions.Size() == 1);
			Assert::IsTrue(actions.Get<Scope&>().Equals(actionDestroyPtr));
		}

		TEST_METHOD(ActionListIfConstructor)
		{
			ActionIfFactory actionIfFactory;
			TestEntityFactory entityFactory;

			World world;
			Sector* sectorPtr = world.CreateSector("OPI");
			Entity* entityPtr = sectorPtr->CreateEntity("TestEntity", "Red");
			ActionIf* actionIfPtr = static_cast<ActionIf*>(entityPtr->CreateAction("ActionIf", "if"));

			Assert::IsTrue(actionIfPtr->Name() == "if");
			Assert::IsTrue(actionIfPtr->IsPrescribedAttribute("Condition"));
			Assert::IsTrue(actionIfPtr->IsPrescribedAttribute("Then"));
			Assert::IsTrue(actionIfPtr->IsPrescribedAttribute("Else"));
		}

		TEST_METHOD(ParseActionFromString)
		{
			ActionListFactory actionListFactory;
			TestEntityFactory entityFactory;

			SharedDataTable data;
			XMLParseMaster master(data);
			XMLParseHelperWorld worldHelper;
			const char* xml = "<world name=\"KaitlynWorld\"> <sector name=\"KTown\"> <entity class=\"TestEntity\" name=\"Kaitlyn\"> <action class=\"ActionList\" name=\"ActionTest\"/> </entity> </sector> </world>";

			master.AddHelper(worldHelper);
			master.Parse(xml, static_cast<std::uint32_t>(strlen(xml)), true);

			Assert::IsTrue(data.MaxDepth() == 4);

			Datum& sectors = data.mWorld->Sectors();
			Datum& entities = static_cast<Sector*>(&sectors.Get<Scope&>())->Entities();
			Datum& actions = static_cast<Entity*>(&entities.Get<Scope&>())->Actions();
			
			Entity* entity = static_cast<Entity*>(&entities.Get<Scope&>());
			Action* action = static_cast<Action*>(&actions.Get<Scope&>());

			Assert::IsTrue(entity->Name() == "Kaitlyn");
			Assert::IsTrue(action->Name() == "ActionTest");
		}

		TEST_METHOD(ParseActionFromFile)
		{
			ActionListFactory actionListFactory;
			TestEntityFactory entityFactory;

			SharedDataTable data;
			XMLParseMaster master(data);
			XMLParseHelperWorld worldHelper;
			const char* filename = "..\\..\\..\\actionXML.txt";

			master.AddHelper(worldHelper);
			master.ParseFromFile(filename);

			Assert::IsTrue(data.MaxDepth() == 4);

			Datum& sectors = data.mWorld->Sectors();
			Datum& entities = static_cast<Sector*>(&sectors.Get<Scope&>())->Entities();
			Datum& actions = static_cast<Entity*>(&entities.Get<Scope&>())->Actions();

			Entity* entity = static_cast<Entity*>(&entities.Get<Scope&>());
			Action* action = static_cast<Action*>(&actions.Get<Scope&>());

			Assert::IsTrue(entity->Name() == "Kaitlyn");
			Assert::IsTrue(action->Name() == "ActionTest");
		}

		TEST_METHOD(ParseActionIfFromFile)
		{
			ActionIfFactory actionIfFactory;
			ActionListFactory actionListFactory;
			TestEntityFactory entityFactory;
			ActionCreateActionFactory actionCreateFactory;

			SharedDataTable data;
			XMLParseMaster master(data);
			XMLParseHelperIf ifHelper;
			XMLParseHelperWorld worldHelper;
			const char* filename = "..\\..\\..\\actionIfXML.txt";

			master.AddHelper(ifHelper);
			master.AddHelper(worldHelper);
			master.ParseFromFile(filename);

			Assert::IsTrue(data.MaxDepth() == 6);

			Datum& sectors = data.mWorld->Sectors();
			Datum& entities = static_cast<Sector*>(&sectors.Get<Scope&>())->Entities();
			Datum& actions = static_cast<Entity*>(&entities.Get<Scope&>())->Actions();
			ActionIf* actionIf = static_cast<ActionIf*>(&actions.Get<Scope&>());

			Assert::IsTrue(actionIf->Name() == "if");
			
			Datum& thenDatum = actionIf->Then();
			Datum& elseDatum = actionIf->Else();
			ActionCreateAction* thenAction = static_cast<ActionCreateAction*>(&thenDatum.Get<Scope&>());
			ActionCreateAction* elseAction = static_cast<ActionCreateAction*>(&elseDatum.Get<Scope&>());

			Assert::IsTrue(thenAction->Name() == "ThenTest");
			Assert::IsTrue(elseAction->Name() == "ElseTest");

			thenAction->SetPrototypeClassName("ActionList");
			thenAction->SetPrototypeInstanceName("createdThen");
			elseAction->SetPrototypeClassName("ActionList");
			elseAction->SetPrototypeInstanceName("createdElse");

			data.Update();
			Datum& ifActions = *actionIf->Find("Actions");
			Assert::IsTrue(ifActions.Size() == 1);
			Assert::IsTrue(static_cast<ActionList*>(&ifActions.Get<Scope&>())->Name() == "createdThen");

			actionIf->SetCondition(0);
			data.Update();
			Assert::IsTrue(ifActions.Size() == 2);
			Assert::IsTrue(static_cast<ActionList*>(&ifActions.Get<Scope&>())->Name() == "createdThen");
			Assert::IsTrue(static_cast<ActionList*>(&ifActions.Get<Scope&>(1))->Name() == "createdElse");
		}

		TEST_METHOD(ParseACAFromFile)
		{
			ActionListFactory actionListFactory;
			TestEntityFactory entityFactory;
			ActionCreateActionFactory actionCreateFactory;

			SharedDataTable data;
			XMLParseMaster master(data);
			XMLParseHelperWorld worldHelper;
			const char* filename = "..\\..\\..\\createActionXML.txt";

			master.AddHelper(worldHelper);
			master.ParseFromFile(filename);

			Assert::IsTrue(data.MaxDepth() == 4);

			Datum& sectors = data.mWorld->Sectors();
			Datum& entities = static_cast<Sector*>(&sectors.Get<Scope&>())->Entities();
			Datum& actions = static_cast<Entity*>(&entities.Get<Scope&>())->Actions();

			Assert::IsTrue(actions.Size() == 2);
			Assert::IsTrue(static_cast<Action*>(&actions.Get<Scope&>())->Name() == "Create");
			Assert::IsTrue(static_cast<Action*>(&actions.Get<Scope&>(1))->Name() == "List");
		}

		TEST_METHOD(ParseADAFromFile)
		{
			ActionListFactory actionListFactory;
			TestEntityFactory entityFactory;
			ActionDestroyActionFactory actionDestroyFactory;

			SharedDataTable data;
			XMLParseMaster master(data);
			XMLParseHelperWorld worldHelper;
			const char* filename = "..\\..\\..\\destroyActionXML.txt";

			master.AddHelper(worldHelper);
			master.ParseFromFile(filename);

			Assert::IsTrue(data.MaxDepth() == 4);

			Datum& sectors = data.mWorld->Sectors();
			Datum& entities = static_cast<Sector*>(&sectors.Get<Scope&>())->Entities();
			Datum& actions = static_cast<Entity*>(&entities.Get<Scope&>())->Actions();

			Assert::IsTrue(actions.Size() == 1);
			Assert::IsTrue(static_cast<Action*>(&actions.Get<Scope&>())->Name() == "Destroy");
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

	_CrtMemState ActionTest::sStartMemState;
}