#include "pch.h"
#include "CppUnitTest.h"
#include "World.h"
#include "Event.h"
#include "TestFoo.h"
#include "AsyncTestSubscribers.h"
#include "GameTime.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(AsyncTest)
	{
	public:

		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD(AsyncControlSubscriber)
		{
			Library::GameTime time;
			EventQueue queue;
			std::uint32_t queueSize = 400;
			std::uint32_t subscriberAmount = 400;
			Foo f;

			for (std::uint32_t i = 0; i < queueSize; ++i)
			{
				queue.Enqueue(make_shared<Event<Foo>>(f));
			}

			Assert::AreEqual(queueSize, queue.Size());

			vector<ControlSubscriber> controlSubscribers;
			for (std::uint32_t i = 0; i < subscriberAmount; ++i)
			{
				controlSubscribers.push_back(ControlSubscriber());
			}

			for (std::uint32_t i = 0; i < subscriberAmount; ++i)
			{
				Event<Foo>::Subscribe(controlSubscribers[i]);
			}

			queue.Update(time);

			for (std::uint32_t i = 0; i < subscriberAmount; ++i)
			{
				Assert::IsTrue(queueSize == controlSubscribers[i].TimesNotified());
			}

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(AsyncSubscribeSubscriber)
		{
			Library::GameTime time;
			EventQueue queue;
			std::uint32_t subscriberAmount = 30;
			std::uint32_t finalSubscriberAmount = 480;
			std::uint32_t eventAmount = 10;

			Foo f;
			for (std::uint32_t i = 0; i < eventAmount; ++i)
			{
				queue.Enqueue(make_shared<Event<Foo>>(f));
			}

			Assert::AreEqual(eventAmount, queue.Size());

			vector<SubscribeSubscriber> subscribers;

			for (std::uint32_t i = 0; i < subscriberAmount; ++i)
			{
				subscribers.push_back(SubscribeSubscriber());
			}

			//subscribing subscribers that create a new subscriber & subscribe it to Event<Foo> in Notify
			for (std::uint32_t i = 0; i < subscribers.size(); ++i)
			{
				Event<Foo>::Subscribe(subscribers[i]);
			}

			Event<Foo> test(f);
			test;

			Assert::AreEqual(subscriberAmount, Event<Foo>::SubscriberAmount());

			queue.Update(time);
			subscriberAmount = 330;
			Assert::AreEqual(subscriberAmount, Event<Foo>::SubscriberAmount());

			//going through the original subscribers & asserting that they have created the same amount of 
			//subscribers as the amount of times they have been notified
			for (std::uint32_t i = 0; i < subscribers.size(); ++i)
			{
				Assert::AreEqual(subscribers[i].TimesNotified(), subscribers[i].mCreatedSubscribers.size());
			}

			//enqueueing 5 more events and updating again
			eventAmount = 5;

			for (std::uint32_t i = 0; i < eventAmount; ++i)
			{
				queue.Enqueue(make_shared<Event<Foo>>(f));
			}
			queue.Update(time);

			//asserting that the original subscribers have created the same amount of subscribers as the
			//amount of times they have been notified
			for (std::uint32_t i = 0; i < subscribers.size(); ++i)
			{
				Assert::AreEqual(subscribers[i].TimesNotified(), subscribers[i].mCreatedSubscribers.size());
			}

			Assert::AreEqual(Event<Foo>::SubscriberAmount(), finalSubscriberAmount);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(AsyncUnsubscribeSubscriber)
		{
			Library::GameTime time;
			EventQueue queue;
			std::uint32_t subscriberAmount = 200;
			std::uint32_t eventAmount = 1;

			Foo f;
			queue.Enqueue(make_shared<Event<Foo>>(f));
			Assert::AreEqual(eventAmount, queue.Size());

			vector<UnsubscribeSubscriber> unsubscribeSubscribers;

			for (std::uint32_t i = 0; i < subscriberAmount; ++i)
			{
				unsubscribeSubscribers.push_back(UnsubscribeSubscriber());
			}

			//subscribing subscribers that do nothing in their notify & subscribers that unsubscribe themselves
			for (std::uint32_t i = 0; i < unsubscribeSubscribers.size(); ++i)
			{
				Event<Foo>::Subscribe(unsubscribeSubscribers[i]);
			}

			Event<Foo> test(f);
			test;

			Assert::AreEqual(Event<Foo>::SubscriberAmount(), subscriberAmount);

			queue.Update(time);

			//asserting that all of the subscribers unsubscribed themselves
			subscriberAmount = 0;
			Assert::AreEqual(Event<Foo>::SubscriberAmount(), subscriberAmount);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(AsyncAddEventSubscriber)
		{
			Library::GameTime time;
			EventQueue queue;
			std::uint32_t subscriberAmount = 200;
			std::uint32_t eventAmount = 20;

			Foo f;
			for (std::uint32_t i = 0; i < eventAmount; ++i)
			{
				queue.Enqueue(make_shared<Event<Foo>>(f));
			}

			Assert::AreEqual(eventAmount, queue.Size());

			vector<AddEventSubscriber> addEventSubscribers;

			for (std::uint32_t i = 0; i < subscriberAmount; ++i)
			{
				addEventSubscribers.push_back(AddEventSubscriber(queue));
			}

			//subscribing subscribers that enqueue an event in their Notify
			for (std::uint32_t i = 0; i < addEventSubscribers.size(); ++i)
			{
				Event<Foo>::Subscribe(addEventSubscribers[i]);
			}

			Assert::AreEqual(Event<Foo>::SubscriberAmount(), subscriberAmount);

			queue.Update(time);

			Assert::AreEqual(queue.Size(), subscriberAmount * eventAmount);
			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(AsyncExceptionSubscriber)
		{
			Library::GameTime time;
			EventQueue queue;

			ExceptionSubscriber test;
			Event<Foo>::Subscribe(test);
			Event<Foo>::Subscribe(test);
			std::uint32_t eventAmount = 2;
			std::uint32_t controlAmount = 200;

			Foo f;
			for (std::uint32_t i = 0; i < eventAmount; ++i)
			{
				queue.Enqueue(make_shared<Event<Foo>>(f));
			}

			vector<ControlSubscriber> controlSubscribers;
			
			for (std::uint32_t i = 0; i < controlAmount; ++i)
			{
				controlSubscribers.push_back(ControlSubscriber());
			}

			for (std::uint32_t i = 0; i < controlAmount; ++i)
			{
				Event<Foo>::Subscribe(controlSubscribers[i]);
			}

			string exceptionOne;

			try
			{
				queue.Update(time);
			}
			catch (exception ex1)
			{
				exceptionOne = ex1.what();
			}

			queue.Enqueue(make_shared<Event<Foo>>(f));

			string exceptionTwo;

			try
			{
				queue.Update(time);
			}
			catch (exception ex2)
			{
				exceptionTwo = ex2.what();
			}

			Assert::IsTrue("exception thrown from subscriber" == exceptionOne);
			Assert::IsTrue("exception thrown from subscriber" == exceptionTwo);

			Event<Foo>::UnsubscribeAll();
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

	_CrtMemState AsyncTest::sStartMemState;
}