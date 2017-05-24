#include "pch.h"
#include "CppUnitTest.h"
#include "World.h"
#include "Factory.h"
#include "ReactionAttributed.h"
#include "ActionEvent.h"
#include "EventMessage.h"
#include "TestEntity.h"
#include "SharedDataTable.h"
#include "XMLParseMaster.h"
#include "XMLParseHelperWorld.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	ConcreteFactory(Entity, TestEntity)
	ConcreteFactory(Reaction, ReactionAttributed)
	ConcreteFactory(Action, ActionEvent)

	TEST_CLASS(ReactionTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD(RTTITests)
		{
			ActionEventFactory actionEventFactory;
			TestEntityFactory entityFactory;

			World world;
			WorldState state;
			ReactionAttributed reaction;
			Sector* sectorPtr = world.CreateSector("OPI");
			Entity* entityPtr = sectorPtr->CreateEntity("TestEntity", "Red");
			Action* actionPtr = entityPtr->CreateAction("ActionEvent", "Paint");
			ActionEvent* actionEventPtr = static_cast<ActionEvent*>(actionPtr);

			Assert::IsTrue(nullptr == actionEventPtr->QueryInterface(5));
			Assert::IsFalse(actionEventPtr->Is(5));
			Assert::IsFalse(actionEventPtr->Is("kaitlyn"));
			Assert::IsFalse(nullptr == actionEventPtr->As<Action>());
			Assert::IsTrue(actionEventPtr == actionEventPtr->As<Action>());

			EventMessage message;

			Assert::IsTrue(nullptr == message.QueryInterface(5));
			Assert::IsFalse(message.Is(5));
			Assert::IsFalse(message.Is("kaitlyn"));
			Assert::IsFalse(nullptr == message.As<Attributed>());
			Assert::IsTrue(&message == message.As<Attributed>());
		}

		TEST_METHOD(EventMessageVariableAccess)
		{
			EventMessage message;

			Assert::IsTrue(message.GetSubtype() == std::string());
			Assert::IsTrue(message.GetWorld() == nullptr);

			World testWorld;
			message.SetSubtype("TestSubtype");
			message.SetWorld(testWorld);

			Assert::IsTrue(message.GetSubtype() == "TestSubtype");
			Assert::IsTrue(message.GetWorld() == &testWorld);
		}

		TEST_METHOD(EventMessageAuxAttributes)
		{
			EventMessage message;
			Datum* auxOne = &message.AppendAuxiliaryAttribute("auxOne");
			Datum* auxTwo = &message.AppendAuxiliaryAttribute("auxTwo");

			Assert::IsTrue(message.AuxiliaryAttributes()[0].first == "auxOne");
			Assert::IsTrue(message.AuxiliaryAttributes()[1].first == "auxTwo");
			Assert::IsTrue(message.AuxiliaryAttributes()[0].second == auxOne);
			Assert::IsTrue(message.AuxiliaryAttributes()[1].second == auxTwo);
		}

		TEST_METHOD(ReactionAttributedNotify)
		{
			EventMessage message;
			message.SetSubtype("EventMessage");
			Datum* auxOne = &message.AppendAuxiliaryAttribute("auxOne");
			Datum* auxTwo = &message.AppendAuxiliaryAttribute("auxTwo");
			std::int32_t intOne = 1;
			std::int32_t intTwo = 2;
			auxOne->Set(intOne);
			auxTwo->Set(intTwo);
			Event<EventMessage> event(message);

			ReactionAttributed reaction;
			Assert::IsTrue(reaction.AuxiliaryAttributes().IsEmpty());

			event.Deliver();
			Assert::IsTrue(reaction.AuxiliaryAttributes().Size() == 2);
			Assert::IsTrue(*reaction.AuxiliaryAttributes()[0].second == *auxOne);
			Assert::IsTrue(*reaction.AuxiliaryAttributes()[1].second == *auxTwo);
		}

		TEST_METHOD(ActionEventUpdate)
		{
			ActionEventFactory actionEventFactory;
			TestEntityFactory entityFactory;

			World world;
			WorldState state;
			ReactionAttributed reaction;
			Sector* sectorPtr = world.CreateSector("OPI");
			Entity* entityPtr = sectorPtr->CreateEntity("TestEntity", "Red");
			Action* actionPtr = entityPtr->CreateAction("ActionEvent", "Paint");
			ActionEvent* actionEventPtr = static_cast<ActionEvent*>(actionPtr);
			Datum* auxOne = &actionEventPtr->AppendAuxiliaryAttribute("auxOne");
			Datum* auxTwo = &actionEventPtr->AppendAuxiliaryAttribute("auxTwo");
			std::int32_t intOne = 1;
			std::int32_t intTwo = 2;
			auxOne->Set(intOne);
			auxTwo->Set(intTwo);

			actionEventPtr->SetSubtype("EventMessage");
			actionEventPtr->SetDelay(0);
			world.Update(state);

			Assert::IsTrue(reaction.AuxiliaryAttributes().Size() == 2);
			Assert::IsTrue(reaction.IsAuxiliaryAttribute("auxOne"));
			Assert::IsTrue(reaction.IsAuxiliaryAttribute("auxTwo"));

			Assert::IsTrue(*reaction.AuxiliaryAttributes()[0].second == *auxOne);
			Assert::IsTrue(*reaction.AuxiliaryAttributes()[1].second == *auxTwo);
		}

		TEST_METHOD(ParseActionEventFromFile)
		{
			ActionEventFactory actionEventFactory;
			TestEntityFactory entityFactory;

			SharedDataTable data;
			XMLParseMaster master(data);
			XMLParseHelperWorld worldHelper;
			const char* filename = "..\\..\\..\\actionEventXML.txt";

			master.AddHelper(worldHelper);
			master.ParseFromFile(filename);

			Assert::IsTrue(data.MaxDepth() == 4);

			Datum& sectors = data.mWorld->Sectors();
			Datum& entities = static_cast<Sector*>(&sectors.Get<Scope&>())->Entities();
			Datum& actions = static_cast<Entity*>(&entities.Get<Scope&>())->Actions();

			Assert::IsTrue(actions.Size() == 1);
			Assert::IsTrue(static_cast<Action*>(&actions.Get<Scope&>())->Name() == "Reaction");

			master.RemoveAllHelpers();
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

	_CrtMemState ReactionTest::sStartMemState;
}