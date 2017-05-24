#include "pch.h"
#include "CppUnitTest.h"
#include "World.h"
#include "Event.h"
#include "TestFoo.h"
#include "TestSubscriber.h"
#include "GameTime.h"
#include <thread>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTest
{
	TEST_CLASS(EventTest)
	{
		typedef std::chrono::high_resolution_clock::time_point time_point;
		typedef std::chrono::milliseconds milliseconds;

	public:

		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD(PublisherSetTime)
		{
			Foo f;
			Event<Foo> fooEvent(f);

			time_point enqueueDefaultValue = time_point();
			time_point enqueueTime(chrono::seconds(5));
			milliseconds delayDefaultValue = milliseconds();
			milliseconds delayTime(10);

			Assert::IsTrue(fooEvent.TimeEnqueued() == enqueueDefaultValue);
			Assert::IsTrue(fooEvent.Delay() == delayDefaultValue);
			
			fooEvent.SetTime(enqueueTime, delayTime);

			Assert::IsTrue(fooEvent.TimeEnqueued() == enqueueTime);
			Assert::IsTrue(fooEvent.Delay() == delayTime);
		}


		TEST_METHOD(PublisherIsExpired)
		{
			Foo f;
			Event<Foo> fooEvent(f);

			time_point currentTime(chrono::seconds(5));
			
			Assert::IsTrue(fooEvent.IsExpired(currentTime));

			time_point enqueueTime(chrono::seconds(5));
			milliseconds delayTime(10);

			fooEvent.SetTime(enqueueTime, delayTime);

			Assert::IsFalse(fooEvent.IsExpired(currentTime));
		}

		TEST_METHOD(EventMessage)
		{
			const std::int32_t testInt = 22;
			Event<std::int32_t> intEvent(testInt);

			Assert::IsTrue(intEvent.Message() == testInt);

			Foo testFoo;
			testFoo.Data(testInt);
			Event<Foo> fooEvent(testFoo);

			Assert::IsTrue(fooEvent.Message() == testFoo);
		}

		TEST_METHOD(EventSubscribe)
		{
			Event<Foo>::UnsubscribeAll();

			TestSubscriber subscriberOne;
			TestSubscriber subscriberTwo;
			TestSubscriber subscriberThree;
			TestSubscriber subscriberFour;
			TestSubscriber subscriberFive;

			Foo f;
			Event<Foo> intEvent(f);
			std::uint32_t numberOfSubscribers = 5;

			Event<Foo>::Subscribe(subscriberOne);
			Event<Foo>::Subscribe(subscriberTwo);
			Event<Foo>::Subscribe(subscriberThree);
			Event<Foo>::Subscribe(subscriberFour);
			Event<Foo>::Subscribe(subscriberFive);

			Assert::AreEqual(intEvent.SubscriberAmount(), numberOfSubscribers);
			Event<Foo>::UnsubscribeAll();
			numberOfSubscribers = 0;
			Assert::AreEqual(intEvent.SubscriberAmount(), numberOfSubscribers);
		}

		TEST_METHOD(EventUnsubscribe)
		{
			Event<Foo>::UnsubscribeAll();

			TestSubscriber subscriberOne;
			TestSubscriber subscriberTwo;
			TestSubscriber subscriberThree;

			Foo f;
			Event<Foo> fooEvent(f);
			std::uint32_t numberOfSubscribers = 3;

			Event<Foo>::Subscribe(subscriberOne);
			Event<Foo>::Subscribe(subscriberTwo);
			Event<Foo>::Subscribe(subscriberThree);

			Assert::AreEqual(fooEvent.SubscriberAmount(), numberOfSubscribers);

			Event<Foo>::Unsubscribe(subscriberThree);
			--numberOfSubscribers;

			Assert::AreEqual(fooEvent.SubscriberAmount(), numberOfSubscribers);

			Event<Foo>::Unsubscribe(subscriberTwo);
			--numberOfSubscribers;

			Assert::AreEqual(fooEvent.SubscriberAmount(), numberOfSubscribers);

			Event<Foo>::UnsubscribeAll();
			numberOfSubscribers = 0;
			Assert::AreEqual(fooEvent.SubscriberAmount(), numberOfSubscribers);
		}

		TEST_METHOD(EventCopySemantics)
		{
			Event<Foo>::UnsubscribeAll();

			Foo fOne;
			fOne.Data(5);
			Foo fTwo;
			fTwo.Data(10);
			Event<Foo> fooEventOne(fOne);
			Event<Foo> fooEventTwo(fTwo);
			std::uint32_t numberOfSubscribers = 3;

			TestSubscriber subscriberOne;
			TestSubscriber subscriberTwo;
			TestSubscriber subscriberThree;

			Event<Foo>::Subscribe(subscriberOne);
			Event<Foo>::Subscribe(subscriberTwo);
			Event<Foo>::Subscribe(subscriberThree);

			Assert::AreEqual(fooEventOne.SubscriberAmount(), numberOfSubscribers);
			Assert::AreEqual(fooEventTwo.SubscriberAmount(), numberOfSubscribers);
			Assert::IsTrue(fooEventOne.Message() == fOne);
			Assert::IsTrue(fooEventTwo.Message() == fTwo);

			fooEventOne = fooEventTwo;
			Assert::IsFalse(fooEventOne.Message() == fOne);
			Assert::IsTrue(fooEventOne.Message() == fooEventTwo.Message());
			Assert::IsTrue(fooEventTwo.Message() == fTwo);

			Event<Foo> fooEventThree(fooEventTwo);
			Assert::IsTrue(fooEventThree.Message() == fooEventTwo.Message());

			Event<Foo>::UnsubscribeAll();
			numberOfSubscribers = 0;
			Assert::AreEqual(fooEventOne.SubscriberAmount(), numberOfSubscribers);
			Assert::AreEqual(fooEventTwo.SubscriberAmount(), numberOfSubscribers);
		}

		TEST_METHOD(EventMoveSemantics)
		{
			Foo fOne;
			fOne.Data(5);
			Foo fTwo;
			fTwo.Data(10);
			Event<Foo> fooEventOne(fOne);
			Event<Foo> fooEventTwo(fTwo);

			fooEventOne = std::move(fooEventTwo);
			Assert::IsTrue(fooEventOne.Message() == fTwo);
		}

		TEST_METHOD(PublisherDeliver)
		{
			Event<Foo>::UnsubscribeAll();

			Foo f;
			Event<Foo> intEventOne(f);

			TestSubscriber subscriberOne;
			TestSubscriber subscriberTwo;
			TestSubscriber subscriberThree;

			Event<Foo>::Subscribe(subscriberOne);
			Event<Foo>::Subscribe(subscriberTwo);
			Event<Foo>::Subscribe(subscriberThree);

			Assert::IsFalse(subscriberOne.EventReceived());
			Assert::IsFalse(subscriberTwo.EventReceived());
			Assert::IsFalse(subscriberThree.EventReceived());

			intEventOne.Deliver();

			Assert::IsTrue(subscriberOne.EventReceived());
			Assert::IsTrue(subscriberTwo.EventReceived());
			Assert::IsTrue(subscriberThree.EventReceived());

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(EventQueueEnqueue)
		{
			EventQueue queue;
			std::uint32_t queueSize = 3;

			Assert::AreNotEqual(queueSize, queue.Size());

			Foo testFooOne;
			Foo testFooTwo;
			Foo testFooThree;
			shared_ptr<Event<Foo>> eventPtrOne = make_shared<Event<Foo>>(testFooOne);
			shared_ptr<Event<Foo>> eventPtrTwo = make_shared<Event<Foo>>(testFooTwo);
			shared_ptr<Event<Foo>> eventPtrThree = make_shared<Event<Foo>>(testFooThree);

			queue.Enqueue(eventPtrOne);
			queue.Enqueue(eventPtrTwo);
			queue.Enqueue(eventPtrThree);

			Assert::AreEqual(queueSize, queue.Size());
		}

		TEST_METHOD(EventQueueIsEmpty)
		{
			EventQueue queue;

			Assert::IsTrue(queue.IsEmpty());

			Foo testFooOne;
			shared_ptr<Event<Foo>> eventPtrOne = make_shared<Event<Foo>>(testFooOne);
			queue.Enqueue(eventPtrOne);

			Assert::IsFalse(queue.IsEmpty());
		}

		TEST_METHOD(EventQueueClear)
		{
			EventQueue queue;
			std::uint32_t emptyQueueSize = 0;

			Foo testFooOne;
			Foo testFooTwo;
			Foo testFooThree;
			shared_ptr<Event<Foo>> eventPtrOne = make_shared<Event<Foo>>(testFooOne);
			shared_ptr<Event<Foo>> eventPtrTwo = make_shared<Event<Foo>>(testFooTwo);
			shared_ptr<Event<Foo>> eventPtrThree = make_shared<Event<Foo>>(testFooThree);

			queue.Enqueue(eventPtrOne);
			queue.Enqueue(eventPtrTwo);
			queue.Enqueue(eventPtrThree);

			Assert::AreNotEqual(emptyQueueSize, queue.Size());

			queue.Clear();

			Assert::AreEqual(emptyQueueSize, queue.Size());
		}

		TEST_METHOD(EventQueueSend)
		{
			EventQueue queue;
			TestSubscriber subscriberOne;
			TestSubscriber subscriberTwo;
			Foo testFooOne;
			shared_ptr<Event<Foo>> eventPtrOne = make_shared<Event<Foo>>(testFooOne);
			
			eventPtrOne->Subscribe(subscriberOne);
			eventPtrOne->Subscribe(subscriberTwo);

			Assert::IsFalse(subscriberOne.EventReceived());
			Assert::IsFalse(subscriberTwo.EventReceived());

			queue.Send(*eventPtrOne);

			Assert::IsTrue(subscriberOne.EventReceived());
			Assert::IsTrue(subscriberTwo.EventReceived());
		}

		TEST_METHOD(EventQueueUpdate)
		{
			Event<Foo>::UnsubscribeAll();

			Library::GameTime time;
			EventQueue queue;
			TestSubscriber subscriberOne;
			TestSubscriber subscriberTwo;
			TestSubscriber subscriberThree;
			TestSubscriber subscriberFour;
			Foo fooOne;
			Foo fooTwo;
			shared_ptr<Event<Foo>> notDelayedEvent = make_shared<Event<Foo>>(fooOne);
			shared_ptr<Event<Foo>> delayedEvent = make_shared<Event<Foo>>(fooTwo);
			time_point enqueueTime = time_point();
			milliseconds delayTime(10);

			notDelayedEvent->Subscribe(subscriberOne);
			notDelayedEvent->Subscribe(subscriberTwo);

			delayedEvent->SetTime(enqueueTime, delayTime);
			delayedEvent->Subscribe(subscriberThree);
			delayedEvent->Subscribe(subscriberFour);

			queue.Enqueue(notDelayedEvent);
			queue.Enqueue(delayedEvent);

			Assert::IsTrue(notDelayedEvent->IsExpired(enqueueTime));
			Assert::IsFalse(delayedEvent->IsExpired(enqueueTime));

			queue.Update(time);

			std::uint32_t queueSize = 1;

			Assert::IsTrue(subscriberOne.EventReceived());
			Assert::IsTrue(subscriberTwo.EventReceived());
			Assert::IsTrue(subscriberThree.EventReceived());
			Assert::IsTrue(subscriberFour.EventReceived());
			Assert::AreEqual(queueSize, queue.Size());

			time_point delayedEnqueueTime(chrono::milliseconds(10));
			time.SetCurrentTime(delayedEnqueueTime);

			queue.Update(time);

			--queueSize;

			Assert::AreEqual(queueSize, queue.Size());

			queue.Clear();
			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(EventQueueSortQueue)
		{
			Library::GameTime time;
			EventQueue queue;
			std::uint32_t test = 5;
			TestSubscriber subscriber;
			shared_ptr<Event<std::uint32_t>> notDelayedEventOne = make_shared<Event<std::uint32_t>>(test);
			shared_ptr<Event<std::uint32_t>> delayedEventOne = make_shared<Event<std::uint32_t>>(test);
			shared_ptr<Event<std::uint32_t>> delayedEventTwo = make_shared<Event<std::uint32_t>>(test);
			shared_ptr<Event<std::uint32_t>> notDelayedEventTwo = make_shared<Event<std::uint32_t>>(test);
			shared_ptr<Event<std::uint32_t>> notDelayedEventThree = make_shared<Event<std::uint32_t>>(test);
			time_point enqueueTime = time_point();
			time_point delayedEnqueueTime(chrono::milliseconds(10));
			milliseconds delayTime(10);
			std::uint32_t queueSize = 5;

			notDelayedEventOne->Subscribe(subscriber);

			delayedEventOne->SetTime(enqueueTime, delayTime);
			delayedEventTwo->SetTime(enqueueTime, delayTime);

			queue.Enqueue(notDelayedEventOne);
			queue.Enqueue(delayedEventOne);
			queue.Enqueue(delayedEventTwo);
			queue.Enqueue(notDelayedEventTwo);
			queue.Enqueue(notDelayedEventThree);

			Assert::IsTrue(notDelayedEventOne->IsExpired(enqueueTime));
			Assert::IsFalse(delayedEventOne->IsExpired(enqueueTime));
			Assert::IsFalse(delayedEventTwo->IsExpired(enqueueTime));
			Assert::IsTrue(notDelayedEventTwo->IsExpired(enqueueTime));
			Assert::IsTrue(notDelayedEventThree->IsExpired(enqueueTime));
			Assert::IsTrue(queueSize == queue.Size());

			queue.Update(time);

			------queueSize;

			Assert::IsTrue(queueSize == queue.Size());
			queue.Clear();
			Event<std::uint32_t >::UnsubscribeAll();
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

	_CrtMemState EventTest::sStartMemState;
}