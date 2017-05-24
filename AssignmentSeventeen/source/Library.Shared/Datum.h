#pragma once
#define CLM_FORCE_CXX98
#pragma warning(push)
#pragma warning(disable:4201)
#include "glm/glm.hpp"
#include <glm/gtx/string_cast.hpp>
#pragma warning(pop)
#include "RTTI.h"
#pragma warning( disable : 4996 )

#include <string>
#include "Hashmap.h"

//!A class that stores an array of values
/*!
Each Datum object represents an array where all of the elements have the same primitive or user-defined type.
This type is defined at run time.
*/

namespace FieaGameEngine
{
	class Scope;

	enum class DatumType
	{
		Unknown,
		Integer,
		Float,
		Vector,
		Matrix,
		Table,
		String,
		Pointer
	};

	union DatumValues
	{
		std::int32_t* i;
		std::float_t* f;
		std::string* s;
		glm::vec4* v;
		glm::mat4* m;
		Library::RTTI** r;
		Scope** sc;
	};

	class Datum final
	{
	public:
		//!Default constructor
		/*!
		Initializes Datum to be empty & does not allocate any memory
		*/
		Datum();

		//!Copy constructor
		Datum(const Datum& rhs);

		//!Assignment operator that deep-copies the contents of a given Datum into this one
		/*!
		\exception "Cannot switch datum type." thrown if the rhs datum is not the same type as the current
			datum, or if the current datum's type is not Unknown
		\exception "Cannot delete internal data." thrown if the current datum's data is internal & the capacity > 0
		*/
		Datum& operator=(const Datum& rhs);

		//!Move constructor
		Datum(Datum&& rhs);

		//!Move assignment operator
		Datum& operator=(Datum&& rhs);

		//!Destructor
		~Datum();

		//!Bracket operator that allows syntactically simplified access to nested Scopes
		Scope& operator[](const std::uint32_t index);

		//!Removes the scope pointer specified by the user
		/*!
		\return returns true if pointer was found & removed, returns false if pointer was not found
		\exception "Datum type does not comply with argument." thrown if the current datum's type is not Table
		*/
		bool Remove(const Scope* ptrToRemove);

		//!Assignment operator overloads for each DatumType
		/*!
		Treats the datum as if it were a scalar & sets the datum's type if the
		type is Unknown.
		\param rhs the user specified value that the datum will be set to
		*/
		Datum& operator=(const std::int32_t& rhs);
		Datum& operator=(const std::float_t& rhs);
		Datum& operator=(const std::string& rhs);
		Datum& operator=(const glm::vec4& rhs);
		Datum& operator=(const glm::mat4& rhs);
		Datum& operator=(Library::RTTI*& rhs);
		Datum& operator=(Scope& rhs);

		//!Returns type enum associated with this object
		DatumType Type() const;

		//!Assigns the type of data this datum stores
		/*!
		\param type the user specified type of data that this datum will store
		\exception "Not permitted to change the datum type." thrown if the datum type is not Unknown
			or equal to the given type
		*/
		void SetType(const DatumType type);

		//!Returns unsigned integer number of values
		std::uint32_t Size() const;

		//!Sets the number of values & reserves memory if needed. Does not modify capacity
		/*!
		\param size number of values specified by the user
		\exception "Cannot modify external data." thrown if the datum does not contain internal data
		*/
		void SetSize(const std::uint32_t size);

		//!Clears the array without shrinking the capacity
		void Clear();

		//!Assigns the internal values array to the given array
		/*!
		\param sourceArray the given array to copy into the internal array
		\param sourceSize the given size to copy into the internal data
		*/
		void SetStorage(std::int32_t* sourceArray, const std::uint32_t sourceSize);
		void SetStorage(std::float_t* sourceArray, const std::uint32_t sourceSize);
		void SetStorage(std::string* sourceArray, const std::uint32_t sourceSize);
		void SetStorage(glm::vec4* sourceArray, const std::uint32_t sourceSize);
		void SetStorage(glm::mat4* sourceArray, const std::uint32_t sourceSize);
		void SetStorage(Library::RTTI** sourceArray, const std::uint32_t sourceSize);

		//!Equal comparison operator
		/*!
		\param rhs the user specified value that 'this' is being compared to
		\return true if the datums are equal & false otherwise
		*/
		bool operator==(const Datum& rhs) const;

		//!Equal comparison operator overloads
		/*!
		Treats the datum as a scalar value & compares it to the scalar value passed in by the user
		\param rhs the user specified value that 'this' is being compared to
		\return true if the datum & the scalar value are equal & false otherwise
		*/
		bool operator==(const std::int32_t& rhs) const;
		bool operator==(const std::float_t& rhs) const;
		bool operator==(const std::string& rhs) const;
		bool operator==(const glm::vec4& rhs) const;
		bool operator==(const glm::mat4& rhs) const;
		bool operator==(Library::RTTI*& rhs) const;
		bool operator==(const Scope*& rhs) const;

		//!Not equal comparison operator
		/*!
		\param rhs the user specified value that 'this' is being compared to
		\return true if the datums are not equal & false otherwise
		*/
		bool operator!=(const Datum& rhs) const;

		//!Not equal comparison operator overloads
		/*!
		Treats the datum as a scalar value & compares it to the scalar value passed in by the user
		\param rhs the user specified value that 'this' is being compared to
		\return true if the datums are not equal & false otherwise
		*/
		bool operator!=(const std::int32_t& rhs) const;
		bool operator!=(const std::float_t& rhs) const;
		bool operator!=(const std::string& rhs) const;
		bool operator!=(const glm::vec4& rhs) const;
		bool operator!=(const glm::mat4& rhs) const;
		bool operator!=(Library::RTTI*& rhs) const;
		bool operator!=(const Scope*& rhs) const;

		//!Assigns the given item to the index provided
		/*!
		Increases capacity if needed; assigns type if current type is Unknown
		\param item the value assigned into datum
		\param index the spot in the datum where the item is assigned (defaulted to 0)
		\exception "The parameter does not match the datum type." thrown if the given item is not
			the same type as the current datum or if the current datum's type is not Unknown
		*/
		void Set(const std::int32_t& item, const std::uint32_t index = 0);
		void Set(const std::float_t& item, const std::uint32_t index = 0);
		void Set(const std::string& item, const std::uint32_t index = 0);
		void Set(const glm::vec4& item, const std::uint32_t index = 0);
		void Set(const glm::mat4& item, const std::uint32_t index = 0);
		void Set(Library::RTTI* item, const std::uint32_t index = 0);
		void Set(Scope& item, const std::uint32_t index = 0);

		//!Returns the value at the given index
		/*!
		\param index specifies the index at which the return value is located (defaulted to 0)
		\return returns a reference to the item located at the user specified index
		\exception "The return type does not match the datum type." thrown if the user is 
			attempting to get a data type from a datum that does not match the datum's type
		\exception "The index is invalid." thrown if the given index is < 0 or >= capacity 
		*/
		template <typename T> T Get(const std::uint32_t index = 0);
		template <typename T> const T Get(const std::uint32_t index = 0) const;

		//!Parses the string given & assigns the element from the string to the index given
		/*!
		\param string contains the value to be assigned into the datum
		\param index specifies where the value should be placed in the datum
		\exception "The datum has an invalid type." thrown if the current datum's type 
			is Unknown, Pointer or Table
		*/
		void SetFromString(const std::string& string, const std::uint32_t index = 0);

		//!Returns the element at the indicated index as a string
		/*!
		\param index user-specified index where the data is located
		\return string that represents the specified element in the datum
		\exception "Cannot convert pointer to string." thrown when ToString is called on a datum of type Pointer or Table
		*/
		std::string ToString(const std::uint32_t index = 0) const;

		//!Appends the given item after the end of the list
		/*!
		\param item is the data item given that will be added to the end of the list
		\exception "Cannot modify external data." thrown if the current datum's data is not internal
		*/
		void PushBack(const std::int32_t& item);
		void PushBack(const std::float_t& item);
		void PushBack(const std::string& item);
		void PushBack(const glm::vec4& item);
		void PushBack(const glm::mat4& item);
		void PushBack(Library::RTTI*& item);
		void PushBack(Scope& item);

		//!Creates an array with the capacity provided by the user
		/*!
		\param capacity the capacity to reserve for the array
		\exception "Cannot modify external data." thrown if the current datum's data is not internal
		*/
		void Reserve(const std::uint32_t capacity);

	private:
		DatumType mType;
		DatumValues mData;
		bool mDataIsInternal;
		std::uint32_t mSize;
		std::uint32_t mCapacity;

	public:
		//!Static hashmap tables that contain DatumType & function pointer pairs and type-specific functions

		//!Used within assignment operator to deep-copy the elements from the given datum into the current one
		typedef void(Datum::*AssignElementFunction)(const Datum& rhs, const std::uint32_t index);
		static const Hashmap<DatumType, AssignElementFunction> AssignElementFunctions;

		void AssignIntFunction(const Datum& rhs, const std::uint32_t index);
		void AssignFloatFunction(const Datum& rhs, const std::uint32_t index);
		void AssignVec4Function(const Datum& rhs, const std::uint32_t index);
		void AssignMat4Function(const Datum& rhs, const std::uint32_t index);
		void AssignStringFunction(const Datum& rhs, const std::uint32_t index);
		void AssignRTTIFunction(const Datum& rhs, const std::uint32_t index);
		void AssignTableFunction(const Datum& rhs, const std::uint32_t index);

		//!Used within Reserve to realloc memory to obtain the user-specified capacity
		typedef void(Datum::*ReserveElementFunction)(const std::uint32_t capacity);
		static const Hashmap<DatumType, ReserveElementFunction> ReserveElementFunctions;

		void ReserveIntFunction(const std::uint32_t capacity);
		void ReserveFloatFunction(const std::uint32_t capacity);
		void ReserveVec4Function(const std::uint32_t capacity);
		void ReserveMat4Function(const std::uint32_t capacity);
		void ReserveStringFunction(const std::uint32_t capacity);
		void ReserveRTTIFunction(const std::uint32_t capacity);
		void ReserveTableFunction(const std::uint32_t capacity);

		//!Used within SetSize to set the size of the current datum to the user-specified size
		typedef void (Datum::*SetSizeElementFunction)(const std::uint32_t size);
		static const Hashmap<DatumType, SetSizeElementFunction> SetSizeElementFunctions;

		void SetSizeIntFunction(const std::uint32_t size);
		void SetSizeFloatFunction(const std::uint32_t size);
		void SetSizeVec4Function(const std::uint32_t size);
		void SetSizeMat4Function(const std::uint32_t size);
		void SetSizeStringFunction(const std::uint32_t size);
		void SetSizeRTTIFunction(const std::uint32_t size);
		void SetSizeTableFunction(const std::uint32_t size);

		//!Used within the comparison operator to compare each element in this datum to each element in the user-specified datum
		typedef void (Datum::*EqualsElementFunction)(const Datum& rhs, bool& equal) const;
		static const Hashmap<DatumType, EqualsElementFunction> EqualsElementFunctions;

		void EqualsIntFunction(const Datum& rhs, bool& equal) const;
		void EqualsFloatFunction(const Datum& rhs, bool& equal) const;
		void EqualsVec4Function(const Datum& rhs, bool& equal) const;
		void EqualsMat4Function(const Datum& rhs, bool& equal) const;
		void EqualsStringFunction(const Datum& rhs, bool& equal) const;
		void EqualsRTTIFunction(const Datum& rhs, bool& equal) const;
		void EqualsTableFunction(const Datum& rhs, bool& equal) const;

		//!Used within SetFromString to set the element at the specified index to the equivalent value of the provided string
		typedef void (Datum::*SetFromStringFunction)(const std::string& string, const std::uint32_t index);
		static const Hashmap<DatumType, SetFromStringFunction> SetFromStringFunctions;

		void SetIntFromString(const std::string& string, const std::uint32_t index);
		void SetFloatFromString(const std::string& string, const std::uint32_t index);
		void SetVec4FromString(const std::string& string, const std::uint32_t index);
		void SetMat4FromString(const std::string& string, const std::uint32_t index);
		void SetStringFromString(const std::string& string, const std::uint32_t index);

		//!Used within ToString to convert the element at the given index to a string
		/*!
		\exception "Cannot convert pointer to string." thrown when ToString is called on a datum of type Pointer or Table
		*/
		typedef std::string(Datum::*ToStringFunction)(const std::uint32_t index) const;
		static const Hashmap<DatumType, ToStringFunction> ToStringFunctions;

		std::string IntToString(const std::uint32_t index) const;
		std::string FloatToString(const std::uint32_t index) const;
		std::string Vec4ToString(const std::uint32_t index) const;
		std::string Mat4ToString(const std::uint32_t index) const;
		std::string StringToString(const std::uint32_t index) const;
		std::string RTTIToString(const std::uint32_t index) const;
		std::string TableToString(const std::uint32_t index) const;

		//!Contains a table of the datum types and the sizes of the types
		static const Hashmap<DatumType, size_t> DatumTypeSizes;
	};

	template<> Scope& Datum::Get<Scope&>(const std::uint32_t index);
	template<> std::int32_t& Datum::Get<std::int32_t&>(const std::uint32_t index);
	template<> std::float_t& Datum::Get<std::float_t&>(const std::uint32_t index);
	template<> std::string& Datum::Get<std::string&>(const std::uint32_t index);
	template<> glm::vec4& Datum::Get<glm::vec4&>(const std::uint32_t index);
	template<> glm::mat4& Datum::Get<glm::mat4&>(const std::uint32_t index);
	template<> Library::RTTI*& Datum::Get<Library::RTTI*&>(const std::uint32_t index);
	template<> const std::int32_t& Datum::Get<const std::int32_t&>(const std::uint32_t index) const;
	template<> const std::float_t& Datum::Get<const std::float_t&>(const std::uint32_t index) const;
	template<> const std::string& Datum::Get<const std::string&>(const std::uint32_t index) const;
	template<> const glm::vec4& Datum::Get<const glm::vec4&>(const std::uint32_t index) const;
	template<> const glm::mat4& Datum::Get<const glm::mat4&>(const std::uint32_t index) const;
	template<> const Library::RTTI*& Datum::Get<const Library::RTTI*&>(const std::uint32_t index) const;
	template<> const Scope& Datum::Get<const Scope&>(const std::uint32_t index) const;
}