#pragma once
#include "Scope.h"

using namespace std;

namespace FieaGameEngine
{
	class Attributed abstract: public Scope
	{
		RTTI_DECLARATIONS(Attributed, Scope);

	public:
		//!Constructor
		Attributed();
		//!Destructor
		virtual ~Attributed() {};
		//!Copy constructor
		Attributed(const Attributed& rhs);
		//!Assignment operator
		Attributed& operator=(const Attributed& rhs);
		//!Move constructor
		Attributed(Attributed&& rhs);
		//!Move assignment operator
		Attributed& operator=(Attributed&& rhs);
		//!Determines whether the given name refers to an attribute for this object
		/*!
		\param name the string associated with the attribute that the user wants to know about
		\return true if the param is the name of an attribute & false otherwise
		*/
		bool IsAttribute(const std::string& name) const;
		//!Determines whether the given name refers to a prescribed attribute for this class
		/*!
		\param name the string associated with the attribute that the user wants to know about
		\return true if the param is the name of a prescribed attribute & false otherwise
		*/
		bool IsPrescribedAttribute(const std::string& name) const;
		//!Determines whether the given name refers to an auxiliary attribute for this object
		/*!
		\param name the string associated with the attribute that the user wants to know about
		\return true if the param is the name of an auxiliary attribute & false otherwise
		*/
		bool IsAuxiliaryAttribute(const std::string& name) const;
		//!Appends a Datum with the given name to this Scope if the name isn't already associated with a prescribed attribute
		/*!
		\param name the name of the auxiliary datum to be appended to the Scope
		\return a reference to the datum that has been appended
		*/
		Datum& AppendAuxiliaryAttribute(const std::string& name);
		//!Returns the index of the first auxiliary attribute
		/*!
		\return unsigned integer that is the index of the first auxiliary attribute
		*/
		std::uint32_t AuxiliaryBegin() const;

		//!Returns a constant vector of pointers to pairs of string datum attributes
		const Vector<std::pair<std::string, Datum*>> AuxiliaryAttributes() const;

	protected:
		void AddInternalAttribute(const std::string& name, const std::int32_t initialValue, const std::uint32_t size);
		void AddInternalAttribute(const std::string& name, const std::float_t initialValue, const std::uint32_t size);
		void AddInternalAttribute(const std::string& name, const std::string& initialValue, const std::uint32_t size);
		void AddInternalAttribute(const std::string& name, const glm::mat4& initialValue, const std::uint32_t size);
		void AddInternalAttribute(const std::string& name, const glm::vec4& initialValue, const std::uint32_t size);

		void AddExternalAttribute(const std::string& name, std::int32_t* externalArray, const std::uint32_t size);
		void AddExternalAttribute(const std::string& name, std::float_t* externalArray, const std::uint32_t size);
		void AddExternalAttribute(const std::string& name, std::string* externalArray, const std::uint32_t size);
		void AddExternalAttribute(const std::string& name, glm::mat4* externalArray, const std::uint32_t size);
		void AddExternalAttribute(const std::string& name, glm::vec4* externalArray, const std::uint32_t size);

		void AddNestedScope(const std::string& name, Scope& scopeToAdd);
		Scope& AddNestedScope(const std::string& name);

	private:
		Vector<std::string> mPrescribedAttributes;
		Vector<std::pair<std::string, Datum*>> mAuxiliaryAttributes;
	};
}
