#pragma once
#include <utility>
#include "SList.h"
#include "Vector.h"
#include "DefaultHash.h"

//!A templated hashmap class
/*!
A chaining implementation of a hashmap. Consists of a vector of singly-linked lists.
*/

namespace FieaGameEngine
{
	template <typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	class Hashmap final
	{
		typedef std::pair<TKey, TData> PairType;
		typedef SList<PairType> ChainType;
		typedef Vector<ChainType> BucketType;
		typedef typename ChainType::Iterator ChainIterator;

	public:
		//!Iterator class that allows the user to access the data within the hashmap
		class Iterator final
		{
		public:
			friend class Hashmap;

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

			//!Prefix increment operator
			/*!
			\return returns the iterator pointing to the next valid slist node in the vector
			\exception "This iterator is not associated with a hashmap." thrown if the iterator does not have an owner
			*/
			Iterator& operator++();

			//!Postfix increment operator
			/*!
			\return returns the iterator pointing to the next valid slist node in the vector
			\exception "This iterator is not associated with a hashmap." thrown if the iterator does not have an owner
			*/
			Iterator operator++(int);

			//!Star dereference operator
			/*!
			\return returns a reference to the pair type that the iterator is pointing at
			\exception "This iterator is not associated with a hashmap." thrown if the iterator does not have an owner or
			\			if the owner is empty
			*/
			PairType& operator*();
			const PairType& operator*() const;

			//!Arrow dereference operator
			/*!
			\return returns a pointer to the pair type that the iterator is pointing at
			\exception "This iterator is not associated with a hashmap." thrown if the iterator does not have an owner or
			\			if the owner is empty
			*/
			PairType* operator->();
			const PairType* operator->() const;

			//!Equal comparison operator
			/*!
			\param rhs the iterator the current iterator is being compared to
			\return returns true if the lhs and rhs are equal
			*/
			bool operator== (const Iterator& rhs) const;

			//!Not equal comparison operator
			/*!
			\param rhs the iterator the current iterator is being compared to
			\return returns true if the lhs and rhs are not equal
			*/
			bool operator!= (const Iterator& rhs) const;

		private:
			std::uint32_t mIndex;
			const Hashmap *mOwner;
			ChainIterator mChainIt;
			Iterator(std::uint32_t index, const Hashmap* hashmap, ChainIterator chainit);
		};

		//!Constructor
		/*!
		\param size specifies the size of the hash table array (the # of buckets)
		*/
		explicit Hashmap(std::uint32_t size = mDefaultTableSize);

		//!List constructor
		/*!
		Allows the user to initialize the values of the hashmap using an initializer list
		*/
		Hashmap(std::initializer_list<PairType> list);

		//!Copy constructor
		Hashmap(const Hashmap& rhs) = default;

		//!Assignment operator
		Hashmap& operator=(const Hashmap& rhs) = default;

		//!Move constructor
		Hashmap(Hashmap&& rhs);

		//!Move assignment operator
		Hashmap& operator=(Hashmap&& rhs);

		//!Destructor
		~Hashmap() = default;

		//!Finds the element corresponding with the key passed in by the user
		/*!
		\param key is the user specified key that they want to find
		\return a hashmap iterator is returned, pointing to the key found or pointing to null if not found
		*/
		Iterator Find(const TKey& key) const;

		//!Inserts the data given into the hashmap
		/*!
		Enters TKey from the PairType into the hash functor to get the index of the entry & inserts the TData from
		the PairType into the SList at that index.
		\param pair the PairType provided by the user that contains a TKey & TData
		\return a hashmap iterator pointing to the added or found key
		*/
		Iterator Insert(const PairType& pair);

		//!Returns a reference to the TData at the given TKey
		/*!
		\param index the index where the item is located that the user wants to access
		\return a T reference to the item at the index provided by the user
		\exception "Element not found." thrown in the const operator[] when an item associated with the key given is not found
		*/
		TData& operator[](const TKey& key);
		const TData& operator[](const TKey& key) const;

		//!Removes the entry that corresponds with the key provided by the user
		/*!
		\param key identifier for the element the user has chosen to delete
		*/
		void Remove(const TKey& key);

		//!Empties the table & deletes any memory that was allocated
		void Clear();

		//!Returns the number of items in the list
		/*!
		\return the number of items in the list as an unsigned integer
		*/
		std::uint32_t Size() const;

		//!Indicates the presence of a key within the hashmap
		/*!
		\return boolean indicating presence of key within hashmap
		*/
		bool ContainsKey(const TKey& key) const;

		//!Returns an iterator pointing to the first element in the hashmap
		/*!
		\return iterator pointing to first valid element in the hashmap
		*/
		Iterator begin() const;

		//!Returns an iterator which can be used to determine when a loop is done
		/*!
		\return iterator
		*/
		Iterator end() const;

		//!Compares two hashmaps to see if they are equal
		/*!
		\return true if hashmaps are equal & false otherwise
		*/
		bool operator==(const Hashmap& rhs) const;

		//!Compares two hashmaps to see if they are not equal
		/*!
		\return false if hashmaps are equal & true otherwise
		*/
		bool operator!=(const Hashmap& rhs) const;

	private:
		HashFunctor mHashFunction;
		BucketType mHashmap;
		std::uint32_t mSize;
		const static std::uint32_t mDefaultTableSize = 13;
	};
}

#include "Hashmap.inl"