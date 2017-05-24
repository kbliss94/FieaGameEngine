#pragma once
#include "Vector.h"
#include "Datum.h"
#include "Hashmap.h"

//!Creates a dictionary of name-value pairs, where Datum objects are the values
/*!
Scopes are the tables of Datum, so a Scope can contain a Scope. The Datum & Scope classes
form a recursive pair, leading to the formation of a dynamic hierarchical database.
*/

namespace FieaGameEngine
{
	class Scope : public Library::RTTI
	{
		RTTI_DECLARATIONS(Scope, Library::RTTI);
		typedef std::pair<std::string, Datum> PairType;
		typedef Hashmap<std::string, Datum> HashmapType;
		typedef Vector<PairType*> VectorType;

	public:
		//!Constructor
		Scope();

		//!Copy constructor
		Scope(const Scope& rhs);

		//!Assignment operator
		Scope& operator=(const Scope& rhs);

		//!Move constructor
		Scope(Scope&& rhs);

		//!Move assignment operator
		Scope& operator=(Scope&& rhs);

		//!Destructor
		virtual ~Scope();

		//!Returns the address of the Datum associated with the given name 
		/*!
		\param name the key that is associated with the datum the user is trying to find
		\return returns the address of the datum if found & nullptr otherwise
		*/
		Datum* Find(const std::string& name) const;

		//!Returns the address of the most-closely nested Datum associated with the given name in this Scope
		/*!
		\param name the key that is associated with the datum the user is trying to find
		\param objectAddress contains the address of the scope object which contains the match (default is nullptr)
		\return returns the address of the Datum if found & nullptr otherwise
		*/
		Datum* Search(const std::string& name, Scope** objectAddress = nullptr);

		//!Returns a reference to the datum found or created that is associated with the given name
		/*!
		This also updates the order vector if a datum is not found & subsequently created.
		\param name the name associated with the datum to find or create
		\return reference to datum found or created
		*/
		Datum& Append(const std::string& name);

		//!Returns a reference to the scope added that is associated with the given name
		/*!
		\param name the name associated with the scope to create
		\return reference to the scope added
		*/
		Scope& AppendScope(const std::string& name);

		//!Removes this scope pointer from its parent pointer & sets this scope's parent to nullptr
		void Orphan();

		//!Places the given child scope into the current parent scope
		/*!
		\param scopeToAdopt reference to the scope to be adopted by the current scope
		\param name the name of the scope to be adopted
		\param index the index at which the child scope should be placed at within its datum
		*/
		void Adopt(Scope& scopeToAdopt, const std::string& name);

		//!Returns the address of the scope which contains the current scope
		Scope* GetParent() const;

		//!Wraps Append for syntactic convenience
		Datum& operator[](const std::string& name);

		//!Finds the datum value at the given index
		/*!
		\param index the spot containing the datum the user wants to find
		\return reference to datum at the index location
		*/
		Datum& operator[](const std::uint32_t index);
		const Datum& operator[](const std::uint32_t index) const;

		//!Comparison operator
		/*!
		\param rhs the scope the current scope is being compared to
		\return returns true if the lhs and rhs are equal
		*/
		bool operator==(const Scope& rhs) const;

		//!Comparison operator
		/*!
		\param rhs the scope the current scope is being compared to
		\return returns false if the lhs and rhs are equal
		*/
		bool operator!=(const Scope& rhs) const;

		//!Finds the name of a table within this table
		/*!
		\param scopeToFind is the address of the scope to search for within the current scope
		*/
		std::string FindName(const Scope* scopeToFind) const;

		//!Deletes all memory allocated by this object
		void Clear();

	private:
		const static std::uint32_t mDefaultScopeSize = 13;
		Scope* mParent;
		VectorType mOrderVector;
		HashmapType mTable;
	};
}
