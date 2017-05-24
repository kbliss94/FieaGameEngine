#pragma once
#include "Vector.h"

namespace FieaGameEngine
{
	template <typename T>
	Vector<T>::Vector() :
		mData(nullptr), mSize(0), mCapacity(0)
	{
		Reserve(10);
	}

	template <typename T>
	Vector<T>::Vector(const Vector& rhs) :
		mData(nullptr), mSize(0), mCapacity(0)
	{
		if (!(rhs.IsEmpty()))
		{
			*this = rhs;
		}
	}

	template <typename T>
	Vector<T>& Vector<T>::operator= (const Vector& rhs)
	{
		if (this != &rhs)
		{
			Clear();

			for (std::uint32_t i = 0; i < rhs.mSize; ++i)
			{
				PushBack(rhs.mData[i]);
			}
		}

		return *this;
	}

	template <typename T>
	Vector<T>::Vector(Vector&& rhs):
		mData(rhs.mData), mSize(rhs.mSize), mCapacity(rhs.mCapacity)
	{
		rhs.mData = nullptr;
		rhs.mSize = 0;
		rhs.mCapacity = 0;
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(Vector&& rhs)
	{
		if (this != &rhs)
		{
			Destroy();

			mData = rhs.mData;
			mSize = rhs.mSize;
			mCapacity = rhs.mCapacity;

			rhs.mData = nullptr;
			rhs.mSize = 0;
			rhs.mCapacity = 0;
		}

		return *this;
	}

	template <typename T>
	Vector<T>::~Vector()
	{
		Clear();
		free(mData);
	}

	template <typename T>
	T& Vector<T>::operator [](std::uint32_t index)
	{
		if (mSize <= index)
		{
			throw std::exception("Index is invalid.");
		}

		return *(mData + index);
	}

	template <typename T>
	const T& Vector<T>::operator [](std::uint32_t index) const
	{
		if (mSize < index)
		{
			throw std::exception("Index is invalid.");
		}

		return *(mData + index);
	}

	template <typename T>
	void Vector<T>::PopBack()
	{
		if (!IsEmpty())
		{
			mData[--mSize].~T();
		}
	}

	template <typename T>
	bool Vector<T>::IsEmpty() const
	{
		return (mSize == 0);
	}

	template <typename T>
	T& Vector<T>::Front()
	{
		if (IsEmpty())
		{
			throw std::exception("List is empty.");
		}

		return mData[0];
	}

	template <typename T>
	const T& Vector<T>::Front() const
	{
		if (IsEmpty())
		{
			throw std::exception("List is empty.");
		}

		return mData[0];
	}

	template <typename T>
	T& Vector<T>::Back()
	{
		if (IsEmpty())
		{
			throw std::exception("List is empty.");
		}

		return mData[mSize - 1];
	}

	template <typename T>
	const T& Vector<T>::Back() const
	{
		if (IsEmpty())
		{
			throw std::exception("List is empty.");
		}

		return mData[mSize - 1];
	}

	template <typename T>
	std::uint32_t Vector<T>::Size() const
	{
		return mSize;
	}

	template <typename T>
	std::uint32_t Vector<T>::Capacity() const
	{
		return mCapacity;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::begin() const
	{
		return Iterator (0, this);
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::end() const
	{
		return Iterator(mSize, this);
	}

	template <typename T>
	void Vector<T>::PushBack(const T& item)
	{
		++mSize;

		if (mCapacity < mSize)
		{
			if (mCapacity == 0)
			{
				Reserve(mCapacity + 10);
			}
			else
			{
				Reserve(mCapacity * 2);
			}
		}

		new(mData + (mSize - 1))T(item);
	}

	template <typename T>
	void Vector<T>::Reserve(std::uint32_t capacity)
	{
		if (capacity > mCapacity)
		{
			mData = static_cast<T*>(realloc(mData, sizeof(T)*capacity));
			mCapacity = capacity;
		}
		else if (capacity < mCapacity)
		{
			while (capacity != mCapacity)
			{
				PopBack();
				--mCapacity;
			}

			mData = static_cast<T*>(realloc(mData, sizeof(T)*capacity));
		}
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Find(const T& value) const
	{
		Iterator it = begin();

		for (; it != end(); ++it)
		{
			if (*it == value)
			{
				break;
			}
		}

		return it;
	}

	template <typename T>
	void Vector<T>::Clear()
	{
		if (!IsEmpty())
		{
			while (mSize != 0)
			{
				PopBack();
			}
		}
	}

	template <typename T>
	void Vector<T>::Destroy()
	{
		Clear();
		free(mData);
	}

	template <typename T>
	void Vector<T>::Remove(Iterator& it)
	{
		if (this != it.mOwner)
		{
			throw std::exception("This iterator does not belong to this vector.");
		}

		mData[it.mIndex].~T();
		auto size = (mCapacity - it.mIndex - 1) * sizeof(T);

		if (size > 0)
		{
			memmove_s((mData + it.mIndex), size, (mData + it.mIndex + 1), size);
		}

		--mSize;
	}

	template <typename T>
	void Vector<T>::Remove(Iterator& start, Iterator& end)
	{
		if (this != start.mOwner && this != end.mOwner)
		{
			throw std::exception("This iterator does not belong to this vector.");
		}

		if (start == end)
		{
			Remove(start);
		}

		if (start.mIndex < end.mIndex)
		{
			if (0 <= start.mIndex && start.mIndex < mSize && 0 <= end.mIndex && end.mIndex <= mSize)
			{
				for (Iterator it = start; it != end; ++it)
				{
					mData[it.mIndex].~T();
				}

				if (end.mIndex != mSize)
				{
					auto size = (mCapacity - (end.mIndex - start.mIndex)) * sizeof(T);
					memmove_s((mData + start.mIndex), size, (mData + end.mIndex), size);
				}

				mSize = mSize - (end.mIndex - start.mIndex);
			}
		}
	}

	//**************************//
	//	       Iterator			//
	//**************************//

	template <typename T>
	Vector<T>::Iterator::Iterator() :
		mIndex(0), mOwner(nullptr)
	{

	}

	template<typename T>
	Vector<T>::Iterator::Iterator(const Iterator & rhs) :
		mIndex(rhs.mIndex), mOwner(rhs.mOwner)
	{

	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator& rhs)
	{
		if (this != &rhs)
		{
			mIndex = rhs.mIndex;
			mOwner = rhs.mOwner;
		}

		return *this;
	}

	template <typename T>
	bool Vector<T>::Iterator::operator== (const Iterator& rhs) const
	{
		return (mIndex == rhs.mIndex && mOwner == rhs.mOwner);
	}

	template <typename T>
	bool Vector<T>::Iterator::operator!= (const Iterator& rhs) const
	{
		return !(operator==(rhs));
	}

	template <typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
	{
		if (mOwner == nullptr)
		{
			throw std::exception("This iterator is not associated with a vector.");
		}

		if (mIndex == mOwner->Size())
		{
			throw std::exception("At the end of the vector.");
		}

		++mIndex;
		return *this;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
	{
		Iterator temp = *this;
		operator++();

		return temp;
	}

	template <typename T>
	T& Vector<T>::Iterator::operator*()
	{
		if (mOwner->Size() <= mIndex || mOwner == nullptr)
		{
			throw std::exception("This item doesn't exist.");
		}

		return *(mOwner->mData + mIndex);
	}

	template <typename T>
	const T& Vector<T>::Iterator::operator*() const
	{
		if (mOwner->Size() <= mIndex || mOwner == nullptr)
		{
			throw std::exception("This item doesn't exist.");
		}

		return *(mOwner->mData + mIndex);
	}

	template <typename T>
	Vector<T>::Iterator::Iterator(std::uint32_t index, const Vector* vector) :
		mIndex(index), mOwner(vector)
	{

	}
}