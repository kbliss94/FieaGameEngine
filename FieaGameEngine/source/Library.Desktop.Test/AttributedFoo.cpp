#include "pch.h"
#include "AttributedFoo.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(AttributedFoo)
	AttributedFoo::AttributedFoo():
		mExternalIntArray(), mExternalFloatArray(), mExternalStringArray(), mExternalVectorArray(), mExternalMatrixArray(), mInternalInt(0),
		mInternalFloat(0.0f), mInternalString(""), mInternalVector(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), mInternalMatrix(glm::mat4(1.0f)), mScopeToAdopt()
	{
		mScopeToAdopt = new Scope();
		Initialize();
	}

	AttributedFoo::AttributedFoo(AttributedFoo& rhs):
		mExternalIntArray(), mExternalFloatArray(), mExternalStringArray(), mExternalVectorArray(), mExternalMatrixArray(), mInternalInt(0),
		mInternalFloat(0.0f), mInternalString(""), mInternalVector(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), mInternalMatrix(glm::mat4(1.0f)), mScopeToAdopt()
	{
		*this = rhs;
	}

	AttributedFoo& AttributedFoo::operator=(AttributedFoo& rhs)
	{
		if (this != &rhs)
		{
			Attributed::operator=(rhs);
			UpdateExternalAttributes();
			*Find("external int") = *(rhs.Find("external int"));
			*Find("external float") = *(rhs.Find("external float"));
			*Find("external string") = *(rhs.Find("external string"));
			*Find("external vector") = *(rhs.Find("external vector"));
			*Find("external matrix") = *(rhs.Find("external matrix"));
		}

		return *this;
	}

	AttributedFoo::AttributedFoo(AttributedFoo&& rhs):
		mExternalIntArray(), mExternalFloatArray(), mExternalStringArray(), mExternalVectorArray(), mExternalMatrixArray(), mInternalInt(0),
		mInternalFloat(0.0f), mInternalString(""), mInternalVector(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), mInternalMatrix(glm::mat4(1.0f)), mScopeToAdopt()
	{
		mScopeToAdopt = new Scope();
		Initialize();
		*this = std::move(rhs);
	}

	AttributedFoo& AttributedFoo::operator=(AttributedFoo&& rhs)
	{
		if (this != &rhs)
		{
			UpdateExternalAttributes();
			*Find("external int") = *(rhs.Find("external int"));
			*Find("external float") = *(rhs.Find("external float"));
			*Find("external string") = *(rhs.Find("external string"));
			*Find("external vector") = *(rhs.Find("external vector"));
			*Find("external matrix") = *(rhs.Find("external matrix"));
			Attributed::operator=(std::move(rhs));
		}

		return *this;
	}

	void AttributedFoo::Initialize()
	{
		AddInternalAttribute("int", mInternalInt, 1);
		AddInternalAttribute("float", mInternalFloat, 1);
		AddInternalAttribute("string", mInternalString, 1);
		AddInternalAttribute("vector", mInternalVector, 1);
		AddInternalAttribute("matrix", mInternalMatrix, 1);

		AddExternalAttribute("external int", mExternalIntArray, mArraySize);
		AddExternalAttribute("external float", mExternalFloatArray, mArraySize);
		AddExternalAttribute("external string", mExternalStringArray, mArraySize);
		AddExternalAttribute("external vector", mExternalVectorArray, mArraySize);
		AddExternalAttribute("external matrix", mExternalMatrixArray, mArraySize);

		AddNestedScope("scope");
		AddNestedScope("adopted scope", *mScopeToAdopt);
	}

	void AttributedFoo::UpdateExternalAttributes()
	{
		Find("external int")->SetStorage(mExternalIntArray, mArraySize);
		Find("external float")->SetStorage(mExternalFloatArray, mArraySize);
		Find("external string")->SetStorage(mExternalStringArray, mArraySize);
		Find("external vector")->SetStorage(mExternalVectorArray, mArraySize);
		Find("external matrix")->SetStorage(mExternalMatrixArray, mArraySize);
	}
}