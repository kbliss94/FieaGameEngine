#pragma once
#include <cstdint>

//!A templated vector class
/*!
Creates and allows manipulation of a vector. The items
within the list are templated data types.
*/

namespace FieaGameEngine
{
	template <typename T>
	class Vector final
	{
	public:
		//!Iterator class that allows the user to access the data within the vector
		class Iterator final
		{
		public:
			friend class Vector;

			//!Default constructor
			Iterator();

			//!Copy constructor that copies the iterator given into a newly created iterator
			/*!
			\param rhs the original iterator that will be copied into the new iterator
			*/
			Iterator(const Iterator& rhs);

			//!Assignment operator that copies the iterator given into an existing iterator
			/*!
			Will clear 'this' iterator and copy the given iterator into the cleared one.
			\param rhs the original iterator that will be copied into the iterator given
			*/
			Iterator& operator=(const Iterator& rhs);

			//!Destructor
			~Iterator() = default;

			//!Comparison operator
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
			\return returns the iterator pointing to the next element in the vector
			\exception "This iterator is not associated with a vector." thrown if the owner of the iterator is null
			\exception "At the end of the vector." thrown when the iterator equals the end of the vector
			*/
			Iterator& operator++();

			//!Postfix increment operator
			/*!
			\return returns the iterator pointing to the next element in the vector
			*/
			Iterator operator++(int);

			//!Dereference operator
			/*!
			\return returns a reference to the data the iterator is pointing at
			\exception "This item doesn't exist." thrown when the iterator is pointing at a nonexistent item
			*/
			T& operator*();
			const T& operator*() const;
			
		private:
			std::uint32_t mIndex;
			const Vector *mOwner;

			//!Constructor
			Iterator(std::uint32_t index, const Vector* vector);
		};

		//!Default constructor
		/*!
		Initializes an empty vector.
		*/
		Vector();		

		//!Copy constructor that deep-copies the vector given
		/*!
		\param rhs the original vector that will be copied into the new vector
		*/
		Vector(const Vector& rhs);

		//!Assignment operator that copies the vector given 
		/*!
		Will clear 'this' vector and copy the given vector into the cleared one.
		\param rhs the original vector that will be copied into the vector given
		*/
		Vector& operator= (const Vector& rhs);

		//!Move constructor
		Vector(Vector&& rhs);

		//!Move assignment operator
		Vector& operator=(Vector&& rhs);

		//!Destructor
		virtual ~Vector();

		//!Returns a reference to the item at the given index
		/*!
		\param index the index where the item is located that the user wants to access
		\return a T reference to the item at the index provided by the user
		\exception "Index is invalid." thrown if the index specified is not between 0 and (size - 1)
		*/
		T& operator [](std::uint32_t index);
		const T& operator [](std::uint32_t index) const;

		//!Removes the last item in the list
		void PopBack();

		//!Returns a boolean value indicating whether or not the list contains any items
		/*!
		\return true if list if empty, false otherwise
		*/
		bool IsEmpty() const;

		//!Returns the first item in the list
		/*!
		\return const or non-const reference to the first item in the list
		\exception "List is empty." thrown if list is empty
		*/
		T& Front();
		const T& Front() const;

		//!Returns the last item in the list
		/*!
		\return const or non-const reference to the last item in the list
		\exception "List is empty." thrown if list is empty
		*/
		T& Back();
		const T& Back() const;

		//!Returns the number of items in the list
		/*!
		\return the number of items in the list as an unsigned integer
		*/
		std::uint32_t Size() const;

		//!Returns the number of items allocated within the list
		/*!
		\return the number of items allocated within the list as an unsigned integer
		*/
		std::uint32_t Capacity() const;

		//!Returns an iterator pointing to the first element in the vector
		/*!
		\return iterator pointing to first element in list
		*/
		Iterator begin() const;

		//!Returns an iterator indicating "not in the container"
		/*!
		\return iterator indicating "not in the container"
		*/
		Iterator end() const;

		//!Appends the given item after the end of the list
		/*!
		\param item is the data item given that will be added to the end of the list
		*/
		void PushBack(const T& item);

		//!Creates an array with the capacity provided by the user
		/*!
		\param capacity the capacity to reserve for the array
		*/
		void Reserve(std::uint32_t capacity);

		//!Finds the value specified by the user within the vector
		/*!
		\param value is the value the user wants to find within the vector
		\return iterator pointing to the first item in the vector that matches the value given
		*/
		Iterator Find(const T& value) const;

		//!Empties the container
		void Clear();

		//!Destroys the vector by clearing it & freeing the allocated memory
		void Destroy();

		//!Removes the element specified by the user from the Vector
		/*!
		\param value the element chosen for removal by the user
		\exception "This iterator does not belong to this vector." thrown if the owner of the iterator is not 'this'
		*/
		void Remove(Iterator& it);

		//!Removes a range of contiguous elements from the vector
		/*
		\param start the beginning of the range to be removed (included in removal)
		\param end the end of the range to be removed (not included in removal)
		\exception "This iterator does not belong to this vector." thrown if the owner of the iterator is not 'this'
		*/
		void Remove(Iterator& start, Iterator& end);

	private:
		T* mData;
		std::uint32_t mSize;
		std::uint32_t mCapacity;
	};
}

#include "Vector.inl"