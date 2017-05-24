#pragma once
#include "SList.h"

namespace FieaGameEngine
{
	template <typename T>
	SList<T>::SList() :
		mFront(nullptr), mBack(nullptr), mSize(0)
	{

	}

	template <typename T>
	SList<T>::SList(const SList& rhs) :
		mFront(nullptr), mBack(nullptr), mSize(0)				
	{
		if (!rhs.IsEmpty())
		{
			DeepCopy(rhs);
		}
	}

	template <typename T>
	SList<T> &SList<T>::operator= (const SList& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			DeepCopy(rhs);
		}

		return *this;
	}

	template <typename T>
	SList<T>::SList(SList&& rhs):
		mSize(rhs.mSize), mFront(rhs.mFront), mBack(rhs.mBack)
	{
		rhs.mSize = 0;
		rhs.mFront = nullptr;
		rhs.mBack = nullptr;
	}

	template <typename T>
	SList<T>& SList<T>::operator=(SList&& rhs)
	{
		if (this != &rhs)
		{
			Clear();

			mSize = rhs.mSize;
			mFront = rhs.mFront;
			mBack = rhs.mBack;

			rhs.mSize = 0;
			rhs.mFront = nullptr;
			rhs.mBack = nullptr;
		}

		return *this;
	}

	template <typename T>
	SList<T>::~SList()
	{
		Clear();
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::PushFront(const T& item)
	{
		mFront = new Node(item, mFront);
		if (mBack == nullptr)
		{
			mBack = mFront;
		}

		++mSize;
		return Iterator(this, mFront);
	}

	template <typename T>
	void SList<T>::PopFront()
	{
		if (!IsEmpty())
		{
			Node *nodeToDelete = mFront;
			mFront = nodeToDelete->Next;
			delete nodeToDelete;
			--mSize;
		}
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::PushBack(const T& item)
	{
		struct Node* newNode = new struct Node;
		newNode->Data = item;
		newNode->Next = nullptr;

		if (IsEmpty())
		{
			mFront = newNode;
		}
		else
		{
			struct Node* temp = mBack;
			temp->Next = newNode;
		}

		mBack = newNode;
		++mSize;

		return Iterator(this, mBack);
	}

	template <typename T>
	bool SList<T>::IsEmpty() const
	{
		return (mSize == 0 && mFront == nullptr);
	}

	template <typename T>
	T &SList<T>::Front()
	{
		if (IsEmpty())
		{
			throw std::exception("List is empty.");
		}

		return mFront->Data;
	}

	template <typename T>
	const T& SList<T>::Front() const
	{
		if (IsEmpty())
		{
			throw std::exception("List is empty.");
		}

		return mFront->Data;
	}

	template <typename T>
	T& SList<T>::Back()
	{
		if (IsEmpty())
		{
			throw std::exception("List is empty.");
		}

		return mBack->Data;
	}

	template <typename T>
	const T& SList<T>::Back() const
	{
		if (IsEmpty())
		{
			throw std::exception("List is empty.");
		}

		return mBack->Data;
	}

	template <typename T>
	std::uint32_t SList<T>::Size() const
	{
		return mSize;
	}

	template<typename T>
	void SList<T>::DeepCopy(const SList& rhs)
	{
		Node *current;
		current = rhs.mFront;

		while (current != nullptr)
		{
			PushBack(current->Data);
			current = current->Next;
		}
	}

	template <typename T>
	void SList<T>::Clear()
	{
		while (mSize > 0)
		{
			PopFront();
		}
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::begin() const
	{
		return Iterator(this, mFront);
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::end() const
	{
		return Iterator(this, nullptr);
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::InsertAfter(const T& item, const Iterator& it)
	{
		if (it.mOwner != this)
		{
			throw std::exception("This iterator doesn't belong to this list.");
		}

		if (Size() == 0)
		{
			PushBack(item);
		}
		else
		{
			Node* newNode = new Node(item, it.mNode->Next);
			it.mNode->Next = newNode;
			++mSize;
		}

		return it;
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::Find(const T& value) const
	{
		Iterator it(this, nullptr);
		Node *current = mFront;

		while (current != nullptr)
		{
			if (current->Data == value)
			{
				it.mNode = current;
			}

			current = current->Next;
		}

		return it;
	}

	template<typename T>
	void SList<T>::Remove(const T& item)
	{
		Iterator itPrevious(this, nullptr);
		Iterator itCurrent(this, nullptr);
		
		if (mFront->Data == item)
		{
			PopFront();
		}
		else
		{
			itPrevious.mNode = mFront;
			itCurrent.mNode = mFront->Next;

			while (!(itCurrent.mNode->Data == item))
			{
				itPrevious.mNode = itCurrent.mNode;
				itCurrent.mNode = itCurrent.mNode->Next;
			}

			if (itCurrent.mNode->Data == item)
			{
				Node *nodeToDelete = itCurrent.mNode;
				itPrevious.mNode->Next = itCurrent.mNode->Next;
				delete nodeToDelete;
				--mSize;
			}
		}
	}

	//**************************//
	//	        Node      		//
	//**************************//

	template <typename T>
	SList<T>::Node::Node()
	{

	}


	template <typename T>
	SList<T>::Node::Node(const T& data, Node* next) :
		Data(data), Next(next)
	{

	}

	//**************************//
	//	       Iterator			//
	//**************************//

	template <typename T>
	SList<T>::Iterator::Iterator() :
		mOwner(nullptr), mNode(nullptr)
	{

	}

	template <typename T>
	SList<T>::Iterator::Iterator(const SList* list, Node* node = nullptr) :
		mOwner(list), mNode(node)
	{

	}

	template<typename T>
	bool SList<T>::Iterator::operator==(const Iterator& rhs) const
	{
		return (this->mNode == rhs.mNode && this->mOwner == rhs.mOwner);
	}

	template<typename T>
	bool SList<T>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(operator==(rhs));
	}

	template<typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator++()
	{
		if (mNode != nullptr)
		{
			mNode = mNode->Next;
		}

		return *this;
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::Iterator::operator++(int)
	{
		Iterator temp;
		operator++();

		return temp;
	}

	template<typename T>
	T & SList<T>::Iterator::operator*()
	{
		if (mOwner == nullptr || *this == mOwner->end())
		{
			throw std::exception("This node doesn't exist.");
		}

		return mNode->Data;
	}

	template<typename T>
	const T & SList<T>::Iterator::operator*() const
	{
		if (mOwner == nullptr || *this == mOwner->end())
		{
			throw std::exception("This node doesn't exist.");
		}

		return mNode->Data;
	}
}