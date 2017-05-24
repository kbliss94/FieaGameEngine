#include "pch.h"
#include "Attributed.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Attributed)

	Attributed::Attributed():
		Scope(), mPrescribedAttributes(), mAuxiliaryAttributes()
	{
		(*this)["this"].Set(this);
	}

	Attributed::Attributed(const Attributed& rhs):
		Scope(rhs), mPrescribedAttributes(rhs.mPrescribedAttributes), mAuxiliaryAttributes(rhs.mAuxiliaryAttributes)
	{
		(*this)["this"].Set(this);
	}

	Attributed& Attributed::operator=(const Attributed& rhs)
	{
		if (this != &rhs)
		{
			Scope::operator=(rhs);
			mPrescribedAttributes = rhs.mPrescribedAttributes;
			mAuxiliaryAttributes = rhs.mAuxiliaryAttributes;
			(*this)["this"].Set(this);
		}

		return *this;
	}

	Attributed::Attributed(Attributed&& rhs):
		Scope(std::move(rhs)), mPrescribedAttributes(std::move(rhs.mPrescribedAttributes)), mAuxiliaryAttributes(std::move(rhs.mAuxiliaryAttributes))
	{
		(*this)["this"].Set(this);
	}

	Attributed& Attributed::operator=(Attributed&& rhs)
	{
		if (this != &rhs)
		{
			Scope::operator=(std::move(rhs));
			mPrescribedAttributes = std::move(rhs.mPrescribedAttributes);
			mAuxiliaryAttributes = std::move(rhs.mAuxiliaryAttributes);
			(*this)["this"].Set(this);
		}

		return *this;
	}

	bool Attributed::IsAttribute(const std::string& name) const
	{
		return (Find(name) != nullptr);
	}

	bool Attributed::IsPrescribedAttribute(const std::string& name) const
	{
		return (IsAttribute(name) && mPrescribedAttributes.Find(name) != mPrescribedAttributes.end());
	}
	
	bool Attributed::IsAuxiliaryAttribute(const std::string& name) const
	{
		return (IsAttribute(name) && !IsPrescribedAttribute(name));
	}

	Datum& Attributed::AppendAuxiliaryAttribute(const std::string& name)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::exception("This is already a prescribed attribute.");
		}

		Append(name);
		mAuxiliaryAttributes.PushBack(std::pair<std::string, Datum*>(name, Find(name)));

		return *(mAuxiliaryAttributes[mAuxiliaryAttributes.Size() - 1].second);
	}

	std::uint32_t Attributed::AuxiliaryBegin() const
	{
		return (mPrescribedAttributes.Size() + 1);
	}

	const Vector<std::pair<std::string, Datum*>> Attributed::AuxiliaryAttributes() const
	{
		return mAuxiliaryAttributes;
	}

	void Attributed::AddInternalAttribute(const std::string& name, const std::int32_t initialValue, const std::uint32_t size)
	{
		mPrescribedAttributes.PushBack(name);

		(*this)[name].SetType(DatumType::Integer);
		(*this)[name].SetSize(size);

		for (std::uint32_t i = 0; i < size; ++i)
		{
			(*this)[name].Set(initialValue, i);
		}
	}

	void Attributed::AddInternalAttribute(const std::string& name, const std::float_t initialValue, const std::uint32_t size)
	{
		mPrescribedAttributes.PushBack(name);

		(*this)[name].SetType(DatumType::Float);
		(*this)[name].SetSize(size);

		for (std::uint32_t i = 0; i < size; ++i)
		{
			(*this)[name].Set(initialValue, i);
		}
	}

	void Attributed::AddInternalAttribute(const std::string& name, const std::string& initialValue, const std::uint32_t size)
	{
		mPrescribedAttributes.PushBack(name);

		(*this)[name].SetType(DatumType::String);
		(*this)[name].SetSize(size);

		for (std::uint32_t i = 0; i < size; ++i)
		{
			(*this)[name].Set(initialValue, i);
		}
	}

	void Attributed::AddInternalAttribute(const std::string& name, const glm::vec4& initialValue, const std::uint32_t size)
	{
		mPrescribedAttributes.PushBack(name);

		(*this)[name].SetType(DatumType::Vector);
		(*this)[name].SetSize(size);

		for (std::uint32_t i = 0; i < size; ++i)
		{
			(*this)[name].Set(initialValue, i);
		}
	}

	void Attributed::AddInternalAttribute(const std::string& name, const glm::mat4& initialValue, const std::uint32_t size)
	{
		mPrescribedAttributes.PushBack(name);

		(*this)[name].SetType(DatumType::Matrix);
		(*this)[name].SetSize(size);

		for (std::uint32_t i = 0; i < size; ++i)
		{
			(*this)[name].Set(initialValue, i);
		}
	}

	void Attributed::AddExternalAttribute(const std::string& name, std::int32_t* externalArray, const std::uint32_t size)
	{
		mPrescribedAttributes.PushBack(name);
		(*this)[name].SetStorage(externalArray, size);
	}

	void Attributed::AddExternalAttribute(const std::string& name, std::float_t* externalArray, const std::uint32_t size)
	{
		mPrescribedAttributes.PushBack(name);
		(*this)[name].SetStorage(externalArray, size);
	}

	void Attributed::AddExternalAttribute(const std::string& name, std::string* externalArray, const std::uint32_t size)
	{
		mPrescribedAttributes.PushBack(name);
		(*this)[name].SetStorage(externalArray, size);
	}

	void Attributed::AddExternalAttribute(const std::string& name, glm::mat4* externalArray, const std::uint32_t size)
	{
		mPrescribedAttributes.PushBack(name);
		(*this)[name].SetStorage(externalArray, size);
	}

	void Attributed::AddExternalAttribute(const std::string& name, glm::vec4* externalArray, const std::uint32_t size)
	{
		mPrescribedAttributes.PushBack(name);
		(*this)[name].SetStorage(externalArray, size);
	}

	void Attributed::AddNestedScope(const std::string& name, Scope& scopeToAdd)
	{
		mPrescribedAttributes.PushBack(name);
		(*this).Adopt(scopeToAdd, name);
	}

	Scope& Attributed::AddNestedScope(const std::string& name)
	{
		mPrescribedAttributes.PushBack(name);
		return (*this).AppendScope(name);
	}
}