#include "pch.h"
#include "Datum.h"
#include "Scope.h"

using namespace std;

namespace FieaGameEngine
{
	Datum::Datum() :
		mType(DatumType::Unknown), mSize(0), mCapacity(0), mDataIsInternal(true)
	{
		mData.i = nullptr;
	}

	Datum::Datum(const Datum& rhs) :
		mType(DatumType::Unknown), mSize(0), mCapacity(0), mDataIsInternal(true)
	{
		mData.i = nullptr;
		*this = rhs;
	}

	Datum& Datum::operator=(const Datum& rhs)
	{
		if (mType != rhs.mType && mType != DatumType::Unknown)
		{
			throw std::exception("Cannot switch datum type.");
		}

		if (this != &rhs)
		{
			if (mType == DatumType::Unknown)
			{
				mType = rhs.mType;
			}

			Clear();

			if (rhs.mDataIsInternal)
			{
				if (!mDataIsInternal)
				{
					mCapacity = 0;
				}

				mDataIsInternal = true;

				for (std::uint32_t i = 0; i < rhs.mSize; ++i)
				{
					(this->*AssignElementFunctions[mType])(rhs, i);
				}
			}
			else
			{
				if (mDataIsInternal && mCapacity > 0)
				{
					throw std::exception("Cannot delete internal data.");
				}

				mData = rhs.mData;
				mDataIsInternal = false;
				mSize = rhs.mSize;
				mCapacity = rhs.mCapacity;
			}
		}

		return *this;
	}

	Datum::Datum(Datum&& rhs) :
		mType(rhs.mType), mData(rhs.mData), mDataIsInternal(rhs.mDataIsInternal), mSize(rhs.mSize), mCapacity(rhs.mCapacity)
	{
		rhs.mType = DatumType::Unknown;
		rhs.mData.i = nullptr;
		rhs.mDataIsInternal = true;
		rhs.mSize = 0;
		rhs.mCapacity = 0;
	}

	Datum& Datum::operator=(Datum&& rhs)
	{
		if (this != &rhs)
		{
			Clear();

			mType = rhs.mType;
			mData = rhs.mData;
			mDataIsInternal = rhs.mDataIsInternal;
			mSize = rhs.mSize;
			mCapacity = rhs.mCapacity;

			rhs.mType = DatumType::Unknown;
			rhs.mData.i = nullptr;
			rhs.mDataIsInternal = true;
			rhs.mSize = 0;
			rhs.mCapacity = 0;
		}

		return *this;
	}

	Datum::~Datum()
	{
		Clear();

		if (mDataIsInternal && mCapacity > 0)
		{
			free(mData.i);
		}
	}

	Scope& Datum::operator[](const std::uint32_t index)
	{
		return Get<Scope&>(index);
	}

	bool Datum::Remove(const Scope* ptrToRemove)
	{
		if (mType != DatumType::Table)
		{
			throw std::exception("Datum type does not comply with argument.");
		}

		bool removed = false;

		for (std::uint32_t i = 0; i < mSize; ++i)
		{
			if (&Get<Scope&>(i) == ptrToRemove)
			{
				auto size = (mCapacity - i - 1) * sizeof(Scope*);
				memmove_s((mData.sc + i), size, (mData.sc + i + 1), size);
				--mSize;
				removed = true;
			}
		}

		return removed;
	}

	Datum& Datum::operator=(const std::int32_t& rhs)
	{
		Clear();
		Set(rhs);

		return *this;
	}

	Datum& Datum::operator=(const std::float_t& rhs)
	{
		Clear();
		Set(rhs);

		return *this;
	}

	Datum& Datum::operator=(const std::string& rhs)
	{
		Clear();
		Set(rhs);

		return *this;
	}

	Datum& Datum::operator=(const glm::vec4& rhs)
	{
		Clear();
		Set(rhs);

		return *this;
	}

	Datum& Datum::operator=(const glm::mat4& rhs)
	{
		Clear();
		Set(rhs);

		return *this;
	}

	Datum& Datum::operator=(Library::RTTI*& rhs)
	{
		Clear();
		Set(rhs);

		return *this;
	}

	Datum& Datum::operator=(Scope& rhs)
	{
		Clear();
		Set(rhs);

		return *this;
	}

	DatumType Datum::Type() const
	{
		return mType;
	}

	void Datum::SetType(const DatumType type)
	{
		if (mType != DatumType::Unknown && mType != type)
		{
			throw std::exception("Not permitted to change the datum type.");
		}

		mType = type;
	}

	std::uint32_t Datum::Size() const
	{
		return mSize;
	}

	void Datum::SetSize(const std::uint32_t size)
	{
		if (!mDataIsInternal)
		{
			throw std::exception("Cannot modify external data.");
		}

		if (size >= mCapacity)
		{
			Reserve(size);
		}

		if (size > mSize && mType != DatumType::Unknown)
		{
			(this->*SetSizeElementFunctions[mType])(size);
		}

		mSize = size;
	}

	void Datum::Clear()
	{
		if (mDataIsInternal)
		{
			if (mType == DatumType::String)
			{
				for (std::uint32_t i = 0; i < mSize; ++i)
				{
					mData.s[i].string::~string();
				}
			}

			if (mType == DatumType::Pointer)
			{
				for (std::uint32_t i = 0; i < mSize; ++i)
				{
					mData.r[i] = nullptr;
				}
			}

			if (mType == DatumType::Table)
			{
				for (std::uint32_t i = 0; i < mSize; ++i)
				{
					mData.sc[i] = nullptr;
				}
			}
		}

		mSize = 0;
	}

	void Datum::SetStorage(std::int32_t* sourceArray, const std::uint32_t sourceSize)
	{
		mDataIsInternal = false;
		mType = DatumType::Integer;
		mData.i = sourceArray;
		mSize = sourceSize;
		mCapacity = sourceSize;
	}

	void Datum::SetStorage(std::float_t* sourceArray, const std::uint32_t sourceSize)
	{
		mDataIsInternal = false;
		mType = DatumType::Float;
		mData.f = sourceArray;
		mSize = sourceSize;
		mCapacity = sourceSize;
	}

	void Datum::SetStorage(std::string* sourceArray, const std::uint32_t sourceSize)
	{
		mDataIsInternal = false;
		mType = DatumType::String;
		mData.s = sourceArray;
		mSize = sourceSize;
		mCapacity = sourceSize;
	}

	void Datum::SetStorage(glm::vec4* sourceArray, const std::uint32_t sourceSize)
	{
		mDataIsInternal = false;
		mType = DatumType::Vector;
		mData.v = sourceArray;
		mSize = sourceSize;
		mCapacity = sourceSize;
	}

	void Datum::SetStorage(glm::mat4* sourceArray, const std::uint32_t sourceSize)
	{
		mDataIsInternal = false;
		mType = DatumType::Matrix;
		mData.m = sourceArray;
		mSize = sourceSize;
		mCapacity = sourceSize;
	}

	void Datum::SetStorage(Library::RTTI** sourceArray, const std::uint32_t sourceSize)
	{
		mDataIsInternal = false;
		mType = DatumType::Pointer;
		mData.r = sourceArray;
		mSize = sourceSize;
		mCapacity = sourceSize;
	}

	bool Datum::operator==(const Datum& rhs) const
	{
		bool equal = true;

		if (mType == rhs.mType && mSize == rhs.mSize)
		{
			if (mType != DatumType::Unknown)
			{
				(this->*EqualsElementFunctions[mType])(rhs, equal);
			}
		}
		else
		{
			equal = false;
		}

		return equal;
	}

	bool Datum::operator==(const std::int32_t& rhs) const
	{
		return (mType == DatumType::Integer && mSize == 1 && *mData.i == rhs);
	}

	bool Datum::operator==(const std::float_t& rhs) const
	{
		return (mType == DatumType::Float && mSize == 1 && *mData.f == rhs);
	}

	bool Datum::operator==(const std::string& rhs) const
	{
		return (mType == DatumType::String && mSize == 1 && *mData.s == rhs);
	}

	bool Datum::operator==(const glm::vec4& rhs) const
	{
		return (mType == DatumType::Vector && mSize == 1 && *mData.v == rhs);
	}

	bool Datum::operator==(const glm::mat4& rhs) const
	{
		return (mType == DatumType::Matrix && mSize == 1 && *mData.m == rhs);
	}

	bool Datum::operator==(Library::RTTI*& rhs) const
	{
		return (mType == DatumType::Pointer && mSize == 1 && *mData.r == rhs);
	}

	bool Datum::operator==(const Scope*& rhs) const
	{
		return (mType == DatumType::Table && mSize == 1 && *mData.sc == rhs);
	}

	bool Datum::operator!=(const Datum& rhs) const
	{
		return !operator==(rhs);
	}

	bool Datum::operator!=(const std::int32_t& rhs) const
	{
		return !operator==(rhs);
	}

	bool Datum::operator!=(const std::float_t& rhs) const
	{
		return !operator==(rhs);
	}

	bool Datum::operator!=(const std::string& rhs) const
	{
		return !operator==(rhs);
	}

	bool Datum::operator!=(const glm::vec4& rhs) const
	{
		return !operator==(rhs);
	}

	bool Datum::operator!=(const glm::mat4& rhs) const
	{
		return !operator==(rhs);
	}

	bool Datum::operator!=(Library::RTTI*& rhs) const
	{
		return !operator==(rhs);
	}

	bool Datum::operator!=(const Scope*& rhs) const
	{
		return !operator==(rhs);
	}

	void Datum::Set(const std::int32_t& item, const std::uint32_t index)
	{
		if (mType != DatumType::Unknown && mType != DatumType::Integer)
		{
			throw std::exception("The parameter does not match the datum type.");
		}

		if (mType == DatumType::Unknown)
		{
			mType = DatumType::Integer;
		}

		if (index >= mSize)
		{
			SetSize(index + 1);
		}

		*(mData.i + index) = item;
	}

	void Datum::Set(const std::float_t& item, const std::uint32_t index)
	{
		if (mType != DatumType::Unknown && mType != DatumType::Float)
		{
			throw std::exception("The parameter does not match the datum type.");
		}

		if (mType == DatumType::Unknown)
		{
			mType = DatumType::Float;
		}

		if (index >= mSize)
		{
			SetSize(index + 1);
		}

		*(mData.f + index) = item;
	}

	void Datum::Set(const std::string& item, const std::uint32_t index)
	{
		if (mType != DatumType::Unknown && mType != DatumType::String)
		{
			throw std::exception("The parameter does not match the datum type.");
		}

		if (mType == DatumType::Unknown)
		{
			mType = DatumType::String;
		}

		if (index >= mSize)
		{
			SetSize(index + 1);
		}

		*(mData.s + index) = item;
	}

	void Datum::Set(const glm::vec4& item, const std::uint32_t index)
	{
		if (mType != DatumType::Unknown && mType != DatumType::Vector)
		{
			throw std::exception("The parameter does not match the datum type.");
		}

		if (mType == DatumType::Unknown)
		{
			mType = DatumType::Vector;
		}

		if (index >= mSize)
		{
			SetSize(index + 1);
		}

		*(mData.v + index) = item;
	}

	void Datum::Set(const glm::mat4& item, const std::uint32_t index)
	{
		if (mType != DatumType::Unknown && mType != DatumType::Matrix)
		{
			throw std::exception("The parameter does not match the datum type.");
		}

		if (mType == DatumType::Unknown)
		{
			mType = DatumType::Matrix;
		}

		if (index >= mSize)
		{
			SetSize(index + 1);
		}

		*(mData.m + index) = item;
	}

	void Datum::Set(Library::RTTI* item, const std::uint32_t index)
	{
		if (mType != DatumType::Unknown && mType != DatumType::Pointer)
		{
			throw std::exception("The parameter does not match the datum type.");
		}

		if (mType == DatumType::Unknown)
		{
			mType = DatumType::Pointer;
		}

		if (index >= mSize)
		{
			SetSize(index + 1);
		}

		*(mData.r + index) = item;
	}

	void Datum::Set(Scope& item, const std::uint32_t index)
	{
		if (mType != DatumType::Unknown && mType != DatumType::Table)
		{
			throw std::exception("The parameter does not match the datum type.");
		}

		if (mType == DatumType::Unknown)
		{
			mType = DatumType::Table;
		}

		if (index >= mSize)
		{
			SetSize(index + 1);
		}

		*(mData.sc + index) = &item;
	}

	void Datum::SetFromString(const std::string& string, const std::uint32_t index)
	{
		if (mType == DatumType::Unknown || mType == DatumType::Pointer || mType == DatumType::Table)
		{
			throw std::exception("The datum has an invalid type.");
		}

		(this->*SetFromStringFunctions[mType])(string, index);
	}

	std::string Datum::ToString(const std::uint32_t index) const
	{
		return (this->*ToStringFunctions[mType])(index);
	}

	void Datum::PushBack(const std::int32_t& item)
	{
		if (!mDataIsInternal)
		{
			throw std::exception("Cannot modify external data.");
		}

		++mSize;

		if (mCapacity < mSize)
		{
			if (mCapacity == 0)
			{
				mData.i = nullptr;
				Reserve(mCapacity + 10);
			}
			else
			{
				Reserve(mCapacity * 2);
			}
		}

		new (mData.i + (mSize - 1))std::int32_t(item);
	}

	void Datum::PushBack(const std::float_t& item)
	{
		if (!mDataIsInternal)
		{
			throw std::exception("Cannot modify external data.");
		}

		++mSize;

		if (mCapacity < mSize)
		{
			if (mCapacity == 0)
			{
				mData.f = nullptr;
				Reserve(mCapacity + 10);
			}
			else
			{
				Reserve(mCapacity * 2);
			}
		}

		new (mData.f + (mSize - 1))std::float_t(item);
	}

	void Datum::PushBack(const std::string& item)
	{
		if (!mDataIsInternal)
		{
			throw std::exception("Cannot modify external data.");
		}

		++mSize;

		if (mCapacity < mSize)
		{
			if (mCapacity == 0)
			{
				mData.s = nullptr;
				Reserve(mCapacity + 10);
			}
			else
			{
				Reserve(mCapacity * 2);
			}
		}

		new (mData.s + (mSize - 1))std::string(item);
	}

	void Datum::PushBack(const glm::vec4& item)
	{
		if (!mDataIsInternal)
		{
			throw std::exception("Cannot modify external data.");
		}

		++mSize;

		if (mCapacity < mSize)
		{
			if (mCapacity == 0)
			{
				mData.v = nullptr;
				Reserve(mCapacity + 10);
			}
			else
			{
				Reserve(mCapacity * 2);
			}
		}

		new (mData.v + (mSize - 1))glm::vec4(item);
	}

	void Datum::PushBack(const glm::mat4& item)
	{
		if (!mDataIsInternal)
		{
			throw std::exception("Cannot modify external data.");
		}

		++mSize;

		if (mCapacity < mSize)
		{
			if (mCapacity == 0)
			{
				mData.m = nullptr;
				Reserve(mCapacity + 10);
			}
			else
			{
				Reserve(mCapacity * 2);
			}
		}

		new (mData.m + (mSize - 1))glm::mat4(item);
	}

	void Datum::PushBack(Library::RTTI*& item)
	{
		if (!mDataIsInternal)
		{
			throw std::exception("Cannot modify external data.");
		}

		++mSize;

		if (mCapacity < mSize)
		{
			if (mCapacity == 0)
			{
				mData.r = nullptr;
				Reserve(mCapacity + 10);
			}
			else
			{
				Reserve(mCapacity * 2);
			}
		}

		new (mData.r + (mSize - 1))Library::RTTI*(item);
	}

	void Datum::PushBack(Scope& item)
	{
		if (!mDataIsInternal)
		{
			throw std::exception("Cannot modify external data.");
		}

		++mSize;

		if (mCapacity < mSize)
		{
			if (mCapacity == 0)
			{
				mData.sc = nullptr;
				Reserve(mCapacity + 10);
			}
			else
			{
				Reserve(mCapacity * 2);
			}
		}

		new (mData.sc + (mSize - 1))Scope*(&item);
	}

	void Datum::Reserve(const std::uint32_t capacity)
	{
		if (!mDataIsInternal)
		{
			throw std::exception("Cannot modify external data.");
		}

		if (capacity > mCapacity && mType != DatumType::Unknown)
		{
			(this->*ReserveElementFunctions[mType])(capacity);
		}

		mCapacity = capacity;
	}

	template<>
	std::int32_t& Datum::Get<std::int32_t&>(const std::uint32_t index)
	{
		if (mType != DatumType::Integer)
		{
			throw std::exception("The return type does not match the datum type.");
		}

		if (0 <= index && index < mCapacity)
		{
			return *(mData.i + index);
		}
		else
		{
			throw std::exception("The index is invalid.");
		}
	}

	template<>
	std::float_t& Datum::Get<std::float_t&>(const std::uint32_t index)
	{
		if (mType != DatumType::Float)
		{
			throw std::exception("The return type does not match the datum type.");
		}

		if (0 <= index && index < mCapacity)
		{
			return *(mData.f + index);
		}
		else
		{
			throw std::exception("The index is invalid.");
		}
	}

	template<>
	std::string& Datum::Get<std::string&>(const std::uint32_t index)
	{
		if (mType != DatumType::String)
		{
			throw std::exception("The return type does not match the datum type.");
		}

		if (0 <= index && index < mCapacity)
		{
			return *(mData.s + index);
		}
		else
		{
			throw std::exception("The index is invalid.");
		}
	}

	template<>
	glm::vec4& Datum::Get<glm::vec4&>(const std::uint32_t index)
	{
		if (mType != DatumType::Vector)
		{
			throw std::exception("The return type does not match the datum type.");
		}

		if (0 <= index && index < mCapacity)
		{
			return *(mData.v + index);
		}
		else
		{
			throw std::exception("The index is invalid.");
		}
	}

	template<>
	glm::mat4& Datum::Get<glm::mat4&>(const std::uint32_t index)
	{
		if (mType != DatumType::Matrix)
		{
			throw std::exception("The return type does not match the datum type.");
		}

		if (0 <= index && index < mCapacity)
		{
			return *(mData.m + index);
		}
		else
		{
			throw std::exception("The index is invalid.");
		}
	}

	template<>
	Library::RTTI*& Datum::Get<Library::RTTI*&>(const std::uint32_t index)
	{
		if (mType != DatumType::Pointer)
		{
			throw std::exception("The return type does not match the datum type.");
		}

		if (0 <= index && index < mCapacity)
		{
			return *(mData.r + index);
		}
		else
		{
			throw std::exception("The index is invalid.");
		}
	}

	template<>
	const std::int32_t& Datum::Get<const std::int32_t&>(const std::uint32_t index) const
	{
		if (mType != DatumType::Integer)
		{
			throw std::exception("The return type does not match the datum type.");
		}

		if (0 <= index && index < mCapacity)
		{
			return *(mData.i + index);
		}
		else
		{
			throw std::exception("The index is invalid.");
		}
	}

	template<>
	const std::float_t& Datum::Get<const std::float_t&>(const std::uint32_t index) const
	{
		if (mType != DatumType::Float)
		{
			throw std::exception("The return type does not match the datum type.");
		}

		if (0 <= index && index < mCapacity)
		{
			return *(mData.f + index);
		}
		else
		{
			throw std::exception("The index is invalid.");
		}
	}

	template<>
	const std::string& Datum::Get<const std::string&>(const std::uint32_t index) const
	{
		if (mType != DatumType::String)
		{
			throw std::exception("The return type does not match the datum type.");
		}

		if (0 <= index && index < mCapacity)
		{
			return *(mData.s + index);
		}
		else
		{
			throw std::exception("The index is invalid.");
		}
	}

	template<>
	const glm::vec4& Datum::Get<const glm::vec4&>(const std::uint32_t index) const
	{
		if (mType != DatumType::Vector)
		{
			throw std::exception("The return type does not match the datum type.");
		}

		if (0 <= index && index < mCapacity)
		{
			return *(mData.v + index);
		}
		else
		{
			throw std::exception("The index is invalid.");
		}
	}

	template<>
	const glm::mat4& Datum::Get<const glm::mat4&>(const std::uint32_t index) const
	{
		if (mType != DatumType::Matrix)
		{
			throw std::exception("The return type does not match the datum type.");
		}

		if (0 <= index && index < mCapacity)
		{
			return *(mData.m + index);
		}
		else
		{
			throw std::exception("The index is invalid.");
		}
	}

	template<>
	const Library::RTTI*& Datum::Get<const Library::RTTI*&>(const std::uint32_t index) const
	{
		if (mType != DatumType::Pointer)
		{
			throw std::exception("The return type does not match the datum type.");
		}

		if (0 <= index && index < mSize)
		{
			return const_cast<const Library::RTTI*&>(*(mData.r + index));
		}
		else
		{
			throw std::exception("The index is invalid.");
		}
	}

	template<>
	const Scope& Datum::Get<const Scope&>(const std::uint32_t index) const
	{
		if (mType != DatumType::Table)
		{
			throw std::exception("The return type does not match the datum type.");
		}

		if (0 <= index && index < mSize)
		{
			return const_cast<const Scope&>(*(mData.sc[index]));
		}
		else
		{
			throw std::exception("The index is invalid.");
		}
	}

	template<>
	Scope& Datum::Get<Scope&>(const std::uint32_t index)
	{
		if (mType != DatumType::Table)
		{
			throw std::exception("The return type does not match the datum type.");
		}

		if (0 <= index && index < mCapacity)
		{
			return **(mData.sc + index);
		}
		else
		{
			throw std::exception("The index is invalid.");
		}
	}




	//**************************************//
	//	       Functions for Tables			//
	//**************************************//

#pragma region

	void Datum::AssignIntFunction(const Datum& rhs, const std::uint32_t index)
	{
		PushBack(*(rhs.mData.i + index));
	}

	void Datum::AssignFloatFunction(const Datum& rhs, const std::uint32_t index)
	{
		PushBack(*(rhs.mData.f + index));
	}

	void Datum::AssignVec4Function(const Datum& rhs, const std::uint32_t index)
	{
		PushBack(*(rhs.mData.v + index));
	}

	void Datum::AssignMat4Function(const Datum& rhs, const std::uint32_t index)
	{
		PushBack(*(rhs.mData.m + index));
	}

	void Datum::AssignStringFunction(const Datum& rhs, const std::uint32_t index)
	{
		PushBack(*(rhs.mData.s + index));
	}

	void Datum::AssignRTTIFunction(const Datum& rhs, const std::uint32_t index)
	{
		PushBack(*(rhs.mData.r + index));
	}

	void Datum::AssignTableFunction(const Datum& rhs, const std::uint32_t index)
	{
		PushBack(**(rhs.mData.sc + index));
	}

#pragma endregion AssignElementFunctions

#pragma region

	void Datum::ReserveIntFunction(const std::uint32_t capacity)
	{
		mData.i = static_cast<std::int32_t*>(realloc(mData.i, DatumTypeSizes[mType] * capacity));
	}

	void Datum::ReserveFloatFunction(const std::uint32_t capacity)
	{
		mData.f = static_cast<std::float_t*>(realloc(mData.f, DatumTypeSizes[mType] * capacity));
	}

	void Datum::ReserveVec4Function(const std::uint32_t capacity)
	{
		mData.v = static_cast<glm::vec4*>(realloc(mData.v, DatumTypeSizes[mType] * capacity));
	}

	void Datum::ReserveMat4Function(const std::uint32_t capacity)
	{
		mData.m = static_cast<glm::mat4*>(realloc(mData.m, DatumTypeSizes[mType] * capacity));
	}

	void Datum::ReserveStringFunction(const std::uint32_t capacity)
	{
		mData.s = static_cast<std::string*>(realloc(mData.s, DatumTypeSizes[mType] * capacity));
	}

	void Datum::ReserveRTTIFunction(const std::uint32_t capacity)
	{
		mData.r = static_cast<Library::RTTI**>(realloc(mData.r, DatumTypeSizes[mType] * capacity));
	}

	void Datum::ReserveTableFunction(const std::uint32_t capacity)
	{
		mData.sc = static_cast<Scope**>(realloc(mData.sc, DatumTypeSizes[mType] * capacity));
	}

#pragma endregion ReserveElementFunctions

#pragma region

	void Datum::SetSizeIntFunction(const std::uint32_t size)
	{
		for (std::uint32_t i = mSize; i < size; ++i)
		{
			new (mData.i + i)std::int32_t(0);
		}
	}

	void Datum::SetSizeFloatFunction(const std::uint32_t size)
	{
		for (std::uint32_t i = mSize; i < size; ++i)
		{
			new (mData.f + i)std::float_t(0);
		}
	}

	void Datum::SetSizeVec4Function(const std::uint32_t size)
	{
		for (std::uint32_t i = mSize; i < size; ++i)
		{
			new (mData.v + i)glm::vec4(0);
		}
	}

	void Datum::SetSizeMat4Function(const std::uint32_t size)
	{
		for (std::uint32_t i = mSize; i < size; ++i)
		{
			new (mData.m + i)glm::mat4(0);
		}
	}

	void Datum::SetSizeStringFunction(const std::uint32_t size)
	{
		for (std::uint32_t i = mSize; i < size; ++i)
		{
			new (mData.s + i)std::string("");
		}
	}

	void Datum::SetSizeRTTIFunction(const std::uint32_t size)
	{
		for (std::uint32_t i = mSize; i < size; ++i)
		{
			new (mData.r + i)Library::RTTI*(nullptr);
		}
	}

	void Datum::SetSizeTableFunction(const std::uint32_t size)
	{
		for (std::uint32_t i = mSize; i < size; ++i)
		{
			new (mData.r + i)Scope*(nullptr);
		}
	}

#pragma endregion SetSizeElementFunctions

#pragma region

	void Datum::EqualsIntFunction(const Datum& rhs, bool& equal) const
	{
		for (std::uint32_t i = 0; i < mSize; ++i)
		{
			if (*(mData.i + i) != *(rhs.mData.i + i))
			{
				equal = false;
				break;
			}
		}
	}

	void Datum::EqualsFloatFunction(const Datum& rhs, bool& equal) const
	{
		for (std::uint32_t i = 0; i < mSize; ++i)
		{
			if (*(mData.f + i) != *(rhs.mData.f + i))
			{
				equal = false;
				break;
			}
		}
	}

	void Datum::EqualsVec4Function(const Datum& rhs, bool& equal) const
	{
		for (std::uint32_t i = 0; i < mSize; ++i)
		{
			if (*(mData.v + i) != *(rhs.mData.v + i))
			{
				equal = false;
				break;
			}
		}
	}

	void Datum::EqualsMat4Function(const Datum& rhs, bool& equal) const
	{
		for (std::uint32_t i = 0; i < mSize; ++i)
		{
			if (*(mData.m + i) != *(rhs.mData.m + i))
			{
				equal = false;
				break;
			}
		}
	}

	void Datum::EqualsStringFunction(const Datum& rhs, bool& equal) const
	{
		for (std::uint32_t i = 0; i < mSize; ++i)
		{
			if (*(mData.s + i) != *(rhs.mData.s + i))
			{
				equal = false;
				break;
			}
		}
	}

	void Datum::EqualsRTTIFunction(const Datum& rhs, bool& equal) const
	{
		for (std::uint32_t i = 0; i < mSize; ++i)
		{
			if (mData.r[i] != nullptr)
			{
				if (!(mData.r[i]->Equals(rhs.mData.r[i])))
				{
					equal = false;
					break;
				}
			}
		}
	}

	void Datum::EqualsTableFunction(const Datum& rhs, bool& equal) const
	{
		for (std::uint32_t i = 0; i < mSize; ++i)
		{
			if (mData.sc[i] != nullptr)
			{
				if (mData.sc[i] == rhs.mData.sc[i])
				{
					equal = false;
					break;
				}
			}
		}
	}

#pragma endregion EqualsElementFunctions

#pragma region

	void Datum::SetIntFromString(const std::string& string, const std::uint32_t index)
	{
		Set(std::stoi(string), index);
	}

	void Datum::SetFloatFromString(const std::string& string, const std::uint32_t index)
	{
		Set(std::stof(string), index);
	}

	void Datum::SetVec4FromString(const std::string& string, const std::uint32_t index)
	{
		char vectorStringOne[8];
		char vectorStringTwo[8];
		char vectorStringThree[8];
		char vectorStringFour[8];

		string.copy(vectorStringOne, 4, 5);
		string.copy(vectorStringTwo, 4, 11);
		string.copy(vectorStringThree, 4, 17);
		string.copy(vectorStringFour, 4, 23);

		Set(glm::vec4(std::stof(vectorStringOne), std::stof(vectorStringTwo), std::stof(vectorStringThree), std::stof(vectorStringFour)), index);
	}

	void Datum::SetMat4FromString(const std::string& string, const std::uint32_t index)
	{
		char vectorStringOne[8];
		char vectorStringTwo[8];
		char vectorStringThree[8];
		char vectorStringFour[8];

		glm::vec4 vectorOne;
		glm::vec4 vectorTwo;
		glm::vec4 vectorThree;
		glm::vec4 vectorFour;

		string.copy(vectorStringOne, 4, 8);
		string.copy(vectorStringTwo, 4, 14);
		string.copy(vectorStringThree, 4, 20);
		string.copy(vectorStringFour, 4, 26);

		vectorOne = glm::vec4(std::stof(vectorStringOne), std::stof(vectorStringTwo), std::stof(vectorStringThree), std::stof(vectorStringFour));

		string.copy(vectorStringOne, 4, 34);
		string.copy(vectorStringTwo, 4, 40);
		string.copy(vectorStringThree, 4, 46);
		string.copy(vectorStringFour, 4, 52);

		vectorTwo = glm::vec4(std::stof(vectorStringOne), std::stof(vectorStringTwo), std::stof(vectorStringThree), std::stof(vectorStringFour));

		string.copy(vectorStringOne, 4, 60);
		string.copy(vectorStringTwo, 4, 66);
		string.copy(vectorStringThree, 4, 72);
		string.copy(vectorStringFour, 4, 78);

		vectorThree = glm::vec4(std::stof(vectorStringOne), std::stof(vectorStringTwo), std::stof(vectorStringThree), std::stof(vectorStringFour));

		string.copy(vectorStringOne, 4, 86);
		string.copy(vectorStringTwo, 4, 92);
		string.copy(vectorStringThree, 4, 98);
		string.copy(vectorStringFour, 4, 104);

		vectorFour = glm::vec4(std::stof(vectorStringOne), std::stof(vectorStringTwo), std::stof(vectorStringThree), std::stof(vectorStringFour));

		Set(glm::mat4(vectorOne, vectorTwo, vectorThree, vectorFour), index);
	}

	void Datum::SetStringFromString(const std::string& string, const std::uint32_t index)
	{
		Set(string, index);
	}

#pragma endregion SetFromStringFunctions

#pragma region

	std::string Datum::IntToString(const std::uint32_t index) const
	{
		return std::to_string(Get<const std::int32_t&>(index));
	}

	std::string Datum::FloatToString(const std::uint32_t index) const
	{
		return std::to_string(Get<const std::float_t&>(index));
	}

	std::string Datum::Vec4ToString(const std::uint32_t index) const
	{
		return glm::to_string(Get<const glm::vec4&>(index));
	}

	std::string Datum::Mat4ToString(const std::uint32_t index) const
	{
		return glm::to_string(Get<const glm::mat4&>(index));
	}

	std::string Datum::StringToString(const std::uint32_t index) const
	{
		return Get<const std::string&>(index);
	}

	std::string Datum::RTTIToString(const std::uint32_t index) const
	{
		index;
		throw std::exception("Cannot convert pointer to string.");
	}

	std::string Datum::TableToString(const std::uint32_t index) const
	{
		index;
		throw std::exception("Cannot convert pointer to string.");
	}

#pragma endregion ToStringFunctions

	//**********************************************//
	//	       DatumType/Function Ptr Tables		//
	//**********************************************//

	const Hashmap<DatumType, Datum::AssignElementFunction> Datum::AssignElementFunctions =
	{
		{ DatumType::Integer, &Datum::AssignIntFunction },
		{ DatumType::Float, &Datum::AssignFloatFunction },
		{ DatumType::Vector, &Datum::AssignVec4Function },
		{ DatumType::Matrix, &Datum::AssignMat4Function },
		{ DatumType::String, &Datum::AssignStringFunction },
		{ DatumType::Pointer, &Datum::AssignRTTIFunction },
		{ DatumType::Table, &Datum::AssignTableFunction }
	};

	const Hashmap<DatumType, Datum::ReserveElementFunction> Datum::ReserveElementFunctions = 
	{
		{ DatumType::Integer, &Datum::ReserveIntFunction },
		{ DatumType::Float, &Datum::ReserveFloatFunction },
		{ DatumType::Vector, &Datum::ReserveVec4Function },
		{ DatumType::Matrix, &Datum::ReserveMat4Function },
		{ DatumType::String, &Datum::ReserveStringFunction },
		{ DatumType::Pointer, &Datum::ReserveRTTIFunction },
		{ DatumType::Table, &Datum::ReserveTableFunction }
	};

	const Hashmap<DatumType, Datum::SetSizeElementFunction> Datum::SetSizeElementFunctions = 
	{
		{ DatumType::Integer, &Datum::SetSizeIntFunction },
		{ DatumType::Float, &Datum::SetSizeFloatFunction },
		{ DatumType::Vector, &Datum::SetSizeVec4Function },
		{ DatumType::Matrix, &Datum::SetSizeMat4Function },
		{ DatumType::String, &Datum::SetSizeStringFunction },
		{ DatumType::Pointer, &Datum::SetSizeRTTIFunction },
		{ DatumType::Table, &Datum::SetSizeTableFunction }
	};

	const Hashmap<DatumType, Datum::EqualsElementFunction> Datum::EqualsElementFunctions = 
	{
		{ DatumType::Integer, &Datum::EqualsIntFunction },
		{ DatumType::Float, &Datum::EqualsFloatFunction },
		{ DatumType::Vector, &Datum::EqualsVec4Function },
		{ DatumType::Matrix, &Datum::EqualsMat4Function },
		{ DatumType::String, &Datum::EqualsStringFunction },
		{ DatumType::Pointer, &Datum::EqualsRTTIFunction },
		{ DatumType::Table, &Datum::EqualsTableFunction }
	};

	const Hashmap<DatumType, Datum::SetFromStringFunction> Datum::SetFromStringFunctions = 
	{
		{ DatumType::Integer, &Datum::SetIntFromString },
		{ DatumType::Float, &Datum::SetFloatFromString },
		{ DatumType::Vector, &Datum::SetVec4FromString },
		{ DatumType::Matrix, &Datum::SetMat4FromString },
		{ DatumType::String, &Datum::SetStringFromString }
	};

	const Hashmap<DatumType, Datum::ToStringFunction> Datum::ToStringFunctions =
	{
		{ DatumType::Integer, &Datum::IntToString },
		{ DatumType::Float, &Datum::FloatToString },
		{ DatumType::Vector, &Datum::Vec4ToString },
		{ DatumType::Matrix, &Datum::Mat4ToString },
		{ DatumType::String, &Datum::StringToString },
		{ DatumType::Pointer, &Datum::RTTIToString },
		{ DatumType::Table, &Datum::TableToString }
	};

	const Hashmap<DatumType, size_t> Datum::DatumTypeSizes = 
	{
		{ DatumType::Integer, sizeof(std::int32_t) },
		{ DatumType::Float, sizeof(std::float_t) },
		{ DatumType::Vector, sizeof(glm::vec4) },
		{ DatumType::Matrix, sizeof(glm::mat4) },
		{ DatumType::String, sizeof(std::string) },
		{ DatumType::Pointer, sizeof(Library::RTTI*) },
		{ DatumType::Table, sizeof(Scope*) }
	};
}