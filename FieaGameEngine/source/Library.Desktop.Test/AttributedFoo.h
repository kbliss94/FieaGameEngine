#pragma once
#include "Attributed.h"

namespace FieaGameEngine
{
	class AttributedFoo : public Attributed
	{
		RTTI_DECLARATIONS(AttributedFoo, Attributed);

	public:
		//!Constructor
		AttributedFoo();
		//!Copy constructor
		AttributedFoo(AttributedFoo& rhs);
		//!Assignment operator
		AttributedFoo& operator=(AttributedFoo& rhs);
		//!Move constructor
		AttributedFoo(AttributedFoo&& rhs);
		//!Move assignment operator
		AttributedFoo& operator=(AttributedFoo&& rhs);

		static const std::int32_t mArraySize = 1;
		std::int32_t mExternalIntArray[mArraySize];
		std::float_t mExternalFloatArray[mArraySize];
		std::string mExternalStringArray[mArraySize];
		glm::vec4 mExternalVectorArray[mArraySize];
		glm::mat4 mExternalMatrixArray[mArraySize];

		const std::int32_t mInternalInt;
		const std::float_t mInternalFloat;
		const std::string mInternalString;
		const glm::vec4 mInternalVector;
		const glm::mat4 mInternalMatrix;
		Scope* mScopeToAdopt;

	private:
		//!Adds prescribed attributes & nested scopes
		void Initialize();
		//!Updates the storage pointers of the current AttributedFoo's external attributes to the storage pointers
		//belonging to the AttributedFoo given
		/*!
		\param updateFoo the AttributedFoo that contains the storage pointers that the current storage pointers will be updated to
		*/
		void UpdateExternalAttributes();
	};
}