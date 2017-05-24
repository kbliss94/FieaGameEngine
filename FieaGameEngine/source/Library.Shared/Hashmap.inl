#pragma once
#include "Hashmap.h"

namespace FieaGameEngine
{
	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	Hashmap<TKey, TData, HashFunctor>::Hashmap(std::uint32_t size = mDefaultTableSize):
		mHashFunction(), mHashmap(), mSize(0)
	{
		mHashmap.Reserve(size);

		for (std::uint32_t i = 0; i < size; ++i)
		{
			mHashmap.PushBack(ChainType());
		}
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	Hashmap<TKey, TData, HashFunctor>::Hashmap(std::initializer_list<PairType> list) :
		Hashmap()
	{
		for (PairType pair : list)
		{
			Insert(pair);
		}
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	Hashmap<TKey, TData, HashFunctor>::Hashmap(Hashmap&& rhs):
		mHashFunction(rhs.mHashFunction), mSize(rhs.mSize), mHashmap(std::move(rhs.mHashmap))
	{
		rhs.mSize = 0;
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	Hashmap<TKey, TData, HashFunctor>& Hashmap<TKey, TData, HashFunctor>::operator=(Hashmap&& rhs)
	{
		if (this != &rhs)
		{
			Clear();

			mSize = rhs.mSize;
			mHashmap = std::move(rhs.mHashmap);
			
			rhs.mSize = 0;
		}

		return *this;
	}

	template <typename TKey, typename TData, typename HashFunctor>
	typename Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::Find(const TKey& key) const
	{
		std::uint32_t hashIndex = (mHashFunction(key)) % mHashmap.Capacity();
		ChainIterator slistIt = mHashmap[hashIndex].begin();

		for (std::uint32_t i = 0; i < mHashmap[hashIndex].Size(); ++i)
		{
			if ((*slistIt).first == key)
			{
				break;
			}

			++slistIt;
		}

		if (slistIt == mHashmap[hashIndex].end())
		{
			return end();
		}

		return Iterator(hashIndex, this, slistIt);
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	typename Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::Insert(const PairType& pair)
	{
		Iterator it = Find(pair.first);
		std::uint32_t hashIndex = (mHashFunction(pair.first)) % mHashmap.Capacity();
		ChainType* chain = &(mHashmap[hashIndex]);

		if (chain->IsEmpty() || it == end())
		{
			chain->PushFront(pair);
			++mSize;
			it = Iterator(hashIndex, this, chain->begin());
		}

		return it;
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	TData& Hashmap<TKey, TData, HashFunctor>::operator[](const TKey& key) 
	{
		Iterator hashmapIt = Insert(PairType(key, TData()));

		return (*hashmapIt).second;
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	const TData& Hashmap<TKey, TData, HashFunctor>::operator[](const TKey& key) const
	{
		Iterator hashmapIt = Find(key);

		if (hashmapIt == end())
		{
			throw std::exception("Element not found.");
		}

		return (*hashmapIt).second;
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	void Hashmap<TKey, TData, HashFunctor>::Remove(const TKey& key)
	{
		Iterator it = Find(key);

		if (it != end())
		{
			mHashmap[it.mIndex].Remove(*it);
			--mSize;
		}
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	void Hashmap<TKey, TData, HashFunctor>::Clear()
	{
		if (mSize != 0)
		{
			Iterator it = begin();
			std::uint32_t index = it.mIndex;

			for (std::uint32_t i = it.mIndex; i < mHashmap.Size(); ++i)
			{
				mHashmap[index].Clear();
				++index;
			}

			mSize = 0;
		}
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	std::uint32_t Hashmap<TKey, TData, HashFunctor>::Size() const
	{
		return mSize;
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	bool Hashmap<TKey, TData, HashFunctor>::ContainsKey(const TKey& key) const
	{
		return !(Find(key) == end());
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	typename Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::begin() const
	{
		Iterator it(0, this, mHashmap[0].begin());
		if (it.mChainIt == mHashmap[0].end())
		{
			++it;
		}

		return it;
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	typename Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::end() const
	{
		return Iterator(mHashmap.Size(), this, ChainIterator());
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	bool Hashmap<TKey, TData, HashFunctor>::operator==(const Hashmap& rhs) const
	{
		bool equal = false;

		if (mSize == rhs.mSize)
		{
			Iterator itLHS = begin();
			Iterator itRHS = rhs.begin();

			for (std::uint32_t i = 0; i < mSize; ++i)
			{
				if (*itLHS != *itRHS)
				{
					break;
				}

				++itLHS;
				++itRHS;
			}

			equal = true;
		}

		return equal;
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	bool Hashmap<TKey, TData, HashFunctor>::operator!=(const Hashmap& rhs) const
	{
		return !operator==(rhs);
	}

	//**************************//
	//	       Iterator			//
	//**************************//

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	Hashmap<TKey, TData, HashFunctor>::Iterator::Iterator() :
		mIndex(0), mOwner(nullptr), mChainIt()
	{

	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	Hashmap<TKey, TData, HashFunctor>::Iterator::Iterator(const Iterator& rhs):
		mIndex(rhs.mIndex), mOwner(rhs.mOwner), mChainIt(rhs.mChainIt)
	{

	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	typename Hashmap<TKey, TData, HashFunctor>::Iterator& Hashmap<TKey, TData, HashFunctor>::Iterator::operator= (const Iterator& rhs)
	{
		if (this != &rhs)
		{
			mIndex = rhs.mIndex;
			mOwner = rhs.mOwner;
			mChainIt = rhs.mChainIt;
		}

		return *this;
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	typename Hashmap<TKey, TData, HashFunctor>::Iterator& Hashmap<TKey, TData, HashFunctor>::Iterator::operator ++()
	{
		if (mOwner == nullptr) 
		{
			throw std::exception("This iterator is not associated with a hashmap.");
		}

		++mChainIt;


		if (mChainIt == mOwner->mHashmap[mIndex].end())
		{
			++mIndex;

			while (mOwner->mHashmap[mIndex].IsEmpty() && mIndex < (mOwner->mHashmap.Capacity() - 1))
			{
				++mIndex;
			}

			mChainIt = mOwner->mHashmap[mIndex].begin();
		}

		return *this;
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	typename Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::Iterator::operator ++(int)
	{
		if (mOwner == nullptr)
		{
			throw std::exception("This iterator is not associated with a hashmap.");
		}

		Iterator temp = *this;
		operator++();

		return temp;
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	typename Hashmap<TKey, TData, HashFunctor>::PairType& Hashmap<TKey, TData, HashFunctor>::Iterator::operator*()
	{
		if (mOwner == nullptr || mOwner->Size() == 0)
		{
			throw std::exception("This iterator is not associated with a hashmap.");
		}

		return *mChainIt;
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	typename const Hashmap<TKey, TData, HashFunctor>::PairType& Hashmap<TKey, TData, HashFunctor>::Iterator::operator*() const
	{
		if (mOwner == nullptr || mOwner->Size() == 0)
		{
			throw std::exception("This iterator is not associated with a hashmap.");
		}

		return *mChainIt;
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	typename Hashmap<TKey, TData, HashFunctor>::PairType* Hashmap<TKey, TData, HashFunctor>::Iterator::operator->()
	{
		if (mOwner == nullptr || mOwner->Size() == 0)
		{
			throw std::exception("This iterator is not associated with a hashmap.");
		}

		return &(*mChainIt);
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	typename const Hashmap<TKey, TData, HashFunctor>::PairType* Hashmap<TKey, TData, HashFunctor>::Iterator::operator->() const
	{
		if (mOwner == nullptr || mOwner->Size() == 0)
		{
			throw std::exception("This iterator is not associated with a hashmap.");
		}

		return &(*mChainIt);
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	bool Hashmap<TKey, TData, HashFunctor>::Iterator::operator == (const Iterator& rhs) const
	{
		return (mIndex == rhs.mIndex && mOwner == rhs.mOwner && mChainIt == rhs.mChainIt);
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	bool Hashmap<TKey, TData, HashFunctor>::Iterator::operator != (const Iterator& rhs) const
	{
		return !(operator==(rhs));
	}

	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	Hashmap<TKey, TData, HashFunctor>::Iterator::Iterator(std::uint32_t index, const Hashmap* hashmap, ChainIterator chainit):
		mIndex(index), mOwner(hashmap), mChainIt(chainit)
	{

	}
}