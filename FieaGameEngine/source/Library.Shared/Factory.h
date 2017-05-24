#pragma once
#include <cassert>
#include "RTTI.h"
#include "Hashmap.h"

namespace FieaGameEngine
{
	template <class T>
	class Factory
	{
		typedef Hashmap <std::string, Factory<T>*> HashmapType;

	public:
		//!Returns a string representing the name of the class the factory instantiates
		virtual std::string ClassName() = 0;
		//!Returns the concrete factory associated with the given class name
		/*!
		\param className the name of the class that the user wants to find
		\return pointer to the concrete factory that is associated w/the given className
		*/
		static Factory<T>* Find(std::string className);
		//!Returns a new object of the type associated with the given class name
		/*!
		\param className name associated with the object type that the user wants to create
		\return pointer to the new object created
		*/
		static T* Create(std::string className);
		//!Returns an iterator pointing to the beginning of the hashmap that contains the concrete factory types
		static typename HashmapType::Iterator begin();
		//!Returns an iterator pointing to one past the end of the hashmap that contains the concrete factory types
		static typename HashmapType::Iterator end();

	protected:
		//!Adds the concrete factory provided to the hashmap of concrete factories
		/*!
		\param pFactory reference to the concrete factory to be added to the hashmap
		*/
		static void Add(Factory<T>* pFactory);
		//!Removes the concrete factory provided from the hashmap of concrete factories
		/*!
		\param pFactory reference to the concrete factory to be added to the hashmap
		*/
		static void Remove(std::string name);

	private:
		//!Returns the address of a concrete product associated w/this concrete factory class
		virtual T* Create() = 0;
		static HashmapType mFactoryTable;
	};



}

#include "Factory.inl"

#define ConcreteFactory(AbstractProductT, ConcreteProductT)								\
	class ConcreteProductT##Factory : public FieaGameEngine::Factory<AbstractProductT>	\
	{																					\
	public:																				\
		ConcreteProductT##Factory() { Add(this); }										\
		~ConcreteProductT##Factory() { Remove(ClassName()); }							\
		std::string ClassName() { return #ConcreteProductT; }							\
		AbstractProductT* Create()														\
		{																				\
			AbstractProductT* createdObj = new ConcreteProductT();						\
			assert(createdObj != nullptr);												\
			return createdObj;															\
		}																				\
	};	