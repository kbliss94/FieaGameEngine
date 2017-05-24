#pragma once
#include <utility>
#include <string>
#include "Hashmap.h"

//!Templated class that hashes given values using additive hashing

namespace FieaGameEngine
{
	template <typename TKey>		
	class DefaultHash
	{
	public:
		std::uint32_t operator() (TKey key) const
		{
			std::uint8_t* data = reinterpret_cast<std::uint8_t*>(&key);
			std::uint32_t hash = 0;

			for (std::uint32_t i = 0; i < sizeof(TKey); ++i)
			{
				hash += 13 + data[i];
			}

			return hash;
		}
	};

	template <typename TKey>
	class DefaultHash <TKey*>
	{
	public:
		std::uint32_t operator() (const TKey* key) const
		{
			TKey data = *key;
			std::uint8_t* dataArray = reinterpret_cast<std::uint8_t*>(&data);
			std::uint32_t hash = 0;

			for (std::uint32_t i = 0; i < sizeof(TKey); ++i)
			{
				hash += 13 + dataArray[i];
			}

			return hash;
		}
	};

	template <>
	class DefaultHash <char*>
	{
	public:
		std::uint32_t operator() (const char* key) const
		{
			std::uint32_t hash = 0;

			for (std::uint32_t i = 0; i < strlen(key); ++i)
			{
				hash += 13 + key[i];
			}

			return hash;
		}
	};

	template <>
	class DefaultHash <std::string>
	{
	public:
		std::uint32_t operator() (const std::string& key) const
		{
			std::uint32_t hash = 0;

			for (std::uint32_t i = 0; i < size(key); ++i)
			{
				hash += 13 + key[i];
			}

			return hash;
		}
	};
}