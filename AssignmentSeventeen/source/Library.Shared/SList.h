#pragma once
#include <cstdint>

//!A templated singly-linked list class
/*!
Creates and allows manipulation of a singly-linked list. The
nodes making up the list contain templated data types.
*/

namespace FieaGameEngine
{
	template <typename T>
	class SList final
	{
	private:
		//!Private node structure that makes up the list of nodes
		struct Node
		{
			Node();
			Node(const T& data, Node* next);
			T Data;
			Node* Next;
		};

	public:
		//!Iterator class that allows the user to access nodes within the linked list
		class Iterator final
		{
		public:
			friend class SList;

			//!Default constructor
			Iterator();

			//!Destructor
			~Iterator() = default;

			//!Const equal comparison operator
			/*!
			\param rhs the iterator the current iterator is being compared to
			\return returns true if the lhs and rhs are equal
			*/
			bool operator== (const Iterator& rhs) const;

			//!Compares the current iterator to the one passed in to see if they are equal
			/*!
			\param rhs the iterator the current iterator is being compared to
			\return returns true if the lhs and rhs are not equal
			*/
			bool operator!= (const Iterator& rhs) const;

			//!Prefix increment operator
			/*!
			\return returns the iterator pointing to the next node in the list
			*/
			Iterator& operator++();

			//!Postfix increment operator
			/*!
			\return returns the iterator pointing to the next node in the list
			*/
			Iterator operator++(int);
			
			//!Dereference operators
			/*!
			\return returns a reference to the item contained by the node the iterator points to
			\exception "This node doesn't exist." thrown if the iterator being dereferenced isn't pointing to anything
			*/
			T& operator*();
			const T& operator*() const;

		private:
			Node* mNode;
			const SList* mOwner;

			//!Constructor
			Iterator(const SList* list, Node* node);
		};

	public:
		//!Initializes the list to be empty
		SList();	

		//!Copy constructor that deep-copies the list given
		/*!
		\param rhs the original list that will be copied into the new list
		*/
		SList(const SList& rhs);

		//!Assignment operator that copies the list given 
		/*!
		Will clear 'this' list and copy the given list into the cleared one.
		\param rhs the original list that will be copied into the list given
		*/
		SList& operator= (const SList& rhs);

		//!Move constructor
		/*!
		Moves the rhs values into the lhs values and erases the rhs.
		*/
		SList(SList&& rhs);

		//!Move assignment operator
		/*!
		Moves the rhs values into the lhs values and erases the rhs.
		*/
		SList& operator=(SList&& rhs);

		//!Destructor 
		virtual ~SList();

		//!Inserts given item before the front of the list
		/*!
		\param item a template data type argument
		\return iterator pointing to the node that was just pushed to the front of the list
		*/
		Iterator PushFront(const T& item);

		//!Removes first item from the list
		/*!
		If the list is empty, nothing is done and the method ends
		*/
		void PopFront();

		//!Adds given item to the end of the list
		/*!
		\param item a template data type argument
		\return iterator pointing to the node that was just pushed at the back of the list
		*/
		Iterator PushBack(const T& item);

		//!Checks if the list is empty
		/*!
		\return true if list is empty, false if not
		*/
		bool IsEmpty() const;	

		//!Returns a reference to the first item in the list
		/*!
		\return a const or non-const reference to the first item in the list
		\exception "List is empty" is thrown if method is called on an empty list
		*/
		T& Front();
		const T& Front() const;

		//!Returns a reference to the last item in the list
		/*!
		\return a const or non-const reference to the last item in the list
		\exception "List is empty" is thrown if method is called on an empty list
		*/
		T& Back();
		const T& Back() const;

		//!Returns the size of the list
		/*!
		\return an unsigned integer for the size of the list
		*/
		std::uint32_t Size() const;	

		//!Creates a deep copy of the list passed in
		/*!
		\param rhs the original list that will be copied into the new list
		*/
		void DeepCopy(const SList& rhs);

		//!Clears & resets the list
		void Clear();

		//!Returns an iterator pointing to the head of the list
		/*!
		\return returns an iterator pointing to the beginning of the list
		*/
		Iterator begin() const;

		//!Returns an iterator pointing past the end of the list
		/*!
		\return returns an iterator pointing past the end of the list
		*/
		Iterator end() const;

		//!Appends the given item after the item the given iterator points to 
		/*!
		\param item is the data value that the user wants to enter into the list
		\param it refers to the node that the user wants to append the given data value to
		\return returns an iterator pointing to the new node inserted into the list
		\exception "This iterator doesn't belong to this list." if the owner of the iterator provided isn't 'this'
		*/
		Iterator InsertAfter(const T& item, const Iterator& it);

		//!Returns an iterator pointing to a node that has the same data value given
		/*!
		\param value is the value that the user wants to find within the list
		\return returns an iterator pointing to the node that has the same data value given
		*/
		Iterator Find(const T& value) const;

		//!Removes the item associated with the given data & maintains list integrity
		/*!
		\param item is a templated data type
		*/
		void Remove(const T& item);

	private:
		Node* mFront;
		Node* mBack;
		std::uint32_t mSize;
	};
}

#include "SList.inl"