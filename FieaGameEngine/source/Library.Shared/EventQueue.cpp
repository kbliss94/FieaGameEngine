#include "pch.h"
#include "EventQueue.h"

namespace FieaGameEngine
{
	EventQueue::EventQueue():
		mQueue()
	{

	}

	void EventQueue::Enqueue(const shared_ptr<EventPublisher>& event)
	{
		lock_guard<mutex> lock(mMutex);
		mQueue.PushBack(event);
	}

	void EventQueue::Send(EventPublisher& event) const
	{
		event.Deliver();
	}

	void EventQueue::Update(const Library::GameTime& time)
	{
		if (!mQueue.IsEmpty())
		{
			std::uint32_t expiredIndex;
			vector<shared_ptr<EventPublisher>> expiredEvents;
			vector<future<void>> futures;

			{
				lock_guard<mutex> lock(mMutex);

				expiredIndex = SortQueue(time);

				for (std::uint32_t i = expiredIndex; i < mQueue.Size(); ++i)
				{
					expiredEvents.push_back(mQueue[i]);
				}

				IteratorType beginExpiredIt = mQueue.Find(mQueue[expiredIndex]);
				IteratorType endExpiredIt = mQueue.end();
				mQueue.Remove(beginExpiredIt, endExpiredIt);
			}

			for (auto& event : expiredEvents)
			{
				futures.emplace_back(async([&]()
				{
					event->Deliver();
				}));
			}

			for (auto& f : futures)
			{
				f.get();
			}
		}
	}

	void EventQueue::Clear()
	{
		mQueue.Clear();
	}

	bool EventQueue::IsEmpty() const
	{
		return (mQueue.Size() == 0);
	}

	std::uint32_t EventQueue::Size() const
	{
		return mQueue.Size();
	}

	std::uint32_t EventQueue::SortQueue(const Library::GameTime& time)
	{
		std::chrono::high_resolution_clock::time_point currentTime = time.CurrentTime();
		std::uint32_t expiredStartIndex = 0;

		for (std::uint32_t i = 0; i < mQueue.Size(); ++i)
		{
			if (mQueue[i]->IsExpired(currentTime))
			{
				for (std::uint32_t j = (mQueue.Size() - 1); j > i; --j)
				{
					if (!mQueue[j]->IsExpired(currentTime))
					{
						shared_ptr<EventPublisher> temp = mQueue[i];
						mQueue[i] = mQueue[j];
						mQueue[j] = temp;
						expiredStartIndex = j;
						break;
					}
				}
			}

			if (expiredStartIndex == i + 1)
			{
				break;
			}
		}

		return expiredStartIndex;
	}
}