#pragma once
#include "Factory.h"

namespace FieaGameEngine
{
	template <typename T>
	Factory<T>* Factory<T>::Find(std::string className)
	{
		return mFactoryTable.Find(className)->second;
	}

	template <typename T>
	T* Factory<T>::Create(std::string className)
	{
		if (mFactoryTable.Find(className) == mFactoryTable.end())
		{
			return nullptr;
		}

		return Find(className)->Create();
	}

	template <typename T>
	typename Hashmap <std::string, Factory<T>*>::Iterator Factory<T>::begin()
	{
		return mFactoryTable.begin();
	}

	template <typename T>
	typename Hashmap <std::string, Factory<T>*>::Iterator Factory<T>::end()
	{
		return mFactoryTable.end();
	}

	template <typename T>
	typename void Factory<T>::Add(Factory<T>* pFactory)
	{
		mFactoryTable[pFactory->ClassName()] = pFactory;
	}

	template <typename T>
	typename void Factory<T>::Remove(std::string name)
	{
		mFactoryTable.Remove(name);
	}

	template <typename T>
	Hashmap <std::string, Factory<T>*> Factory<T>::mFactoryTable;
}
