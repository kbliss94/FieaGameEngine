#include "pch.h"
#include "Scope.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Scope)

	Scope::Scope():
		mParent(nullptr), mOrderVector(), mTable(mDefaultScopeSize*3)
	{

	}

	Scope::Scope(const Scope& rhs):
		mParent(nullptr), mOrderVector(), mTable(rhs.mTable)
	{
		if (this != &rhs)
		{
			operator=(rhs);
		}
	}

	Scope& Scope::operator=(const Scope& rhs)
	{
		if (this != &rhs)
		{
			for (auto& it : rhs.mOrderVector)
			{
				Datum foundDatum = it->second;
				std::string foundDatumName = it->first;

				if (foundDatum.Type() != DatumType::Table)
				{
					Append(foundDatumName) = foundDatum;
				}
				else
				{
					for (std::uint32_t i = 0; i < foundDatum.Size(); ++i)
					{
						AppendScope(foundDatumName) = foundDatum[i];
					}
				}
			}
		}

		return *this;
	}

	Scope::Scope(Scope&& rhs):
		mParent(rhs.mParent), mOrderVector(std::move(rhs.mOrderVector)), mTable(std::move(rhs.mTable))
	{
		if (mParent != nullptr)
		{
			std::string rhsName = rhs.mParent->FindName(&rhs);
			rhs.Orphan();
			mParent->Adopt(*this, rhsName);
		}

		for (auto& it : mOrderVector)
		{
			Datum foundDatum = it->second;

			//if (it->second.Type() == DatumType::Table)
			if (foundDatum.Type() == DatumType::Table)
			{
				for (std::uint32_t i = 0; i < it->second.Size(); ++i)
				{
					//it->second[i].mParent = this;
					foundDatum[i].mParent = this;
				}
			}
		}
	}

	Scope& Scope::operator=(Scope&& rhs)
	{
		if (this != &rhs)
		{
			Clear();

			mOrderVector = std::move(rhs.mOrderVector);
			mTable = std::move(rhs.mTable);
			mParent = rhs.mParent;

			if (mParent != nullptr)
			{
				std::string rhsName = rhs.mParent->FindName(&rhs);
				rhs.Orphan();
				mParent->Adopt(*this, rhsName);
			}

			for (auto& it : mOrderVector)
			{
				Datum foundDatum = it->second;

				//if (it->second.Type() == DatumType::Table)
				if (foundDatum.Type() == DatumType::Table)
				{
					for (std::uint32_t i = 0; i < it->second.Size(); ++i)
					{
						//it->second[i].mParent = this;
						foundDatum[i].mParent = this;
					}
				}
			}
		}

		return *this;
	}

	Scope::~Scope()
	{
		Clear();
	}

	Datum* Scope::Find(const std::string& name) const
	{
		Datum* foundDatumPtr = nullptr;
		HashmapType::Iterator tableIt = mTable.Find(name);

		if (tableIt != mTable.end())
		{
			foundDatumPtr = &(*tableIt).second;
		}

		return foundDatumPtr;
	}

	Datum* Scope::Search(const std::string& name, Scope** objectAddress) 
	{
		Datum* foundDatum = nullptr;

		foundDatum = Find(name);

		if (foundDatum == nullptr && mParent != nullptr)
		{
			foundDatum = mParent->Search(name);
		}
		else
		{
			if (objectAddress != nullptr)
			{
				*objectAddress = this;
			}
		}

		return foundDatum;
	}

	Datum& Scope::Append(const std::string& name)
	{
		HashmapType::Iterator it = mTable.Insert(PairType(name, Datum()));

		if (mOrderVector.Find(&*it) == mOrderVector.end())
		{
			mOrderVector.PushBack(&*it);
		}

		return it->second;
	}

	Scope& Scope::AppendScope(const std::string& name)
	{
		Datum& returnedDatum = Append(name);
		returnedDatum.SetType(DatumType::Table);

		Scope* newScope = new Scope();
		newScope->mParent = this;
		returnedDatum.PushBack(*newScope);

		return *newScope;
	}

	void Scope::Orphan()
	{
		if (mParent != nullptr)
		{
			for (auto& it : mParent->mOrderVector)
			{
				Datum foundDatum = it->second;

				//if (it->second.Type() == DatumType::Table)
				if (foundDatum.Type() == DatumType::Table)
				{
					//if (it->second.Remove(this))
					if (foundDatum.Remove(this))
					{
						mParent = nullptr;
						break;
					}
				}
			}
		}
	}

	void Scope::Adopt(Scope& scopeToAdopt, const std::string& name)
	{
		Datum& datum = Append(name);
		datum.SetType(DatumType::Table);
		scopeToAdopt.Orphan();
		scopeToAdopt.mParent = this;
		datum.PushBack(scopeToAdopt);
	}

	Scope* Scope::GetParent() const
	{
		return mParent;
	}

	Datum& Scope::operator[](const std::string& name)
	{
		return Append(name);
	}

	Datum& Scope::operator[](const std::uint32_t index)
	{
		return mOrderVector[index]->second;
	}

	const Datum& Scope::operator[](const std::uint32_t index) const
	{
		return mOrderVector[index]->second;
	}

	bool Scope::operator==(const Scope& rhs) const
	{
		bool isEqual = false;

		if (mOrderVector.Size() == rhs.mOrderVector.Size())
		{
			isEqual = true;

			for (std::uint32_t i = 0; i < mOrderVector.Size(); ++i)
			{
				if (*mOrderVector[i] != *rhs.mOrderVector[i])
				{
					isEqual = false;
					break;
				}
			}
		}

		return isEqual;
	}

	bool Scope::operator!=(const Scope& rhs) const
	{
		return !operator==(rhs);
	}

	std::string Scope::FindName(const Scope* scopeToFind) const
	{
		std::string name = nullptr;

		for (auto& it : mOrderVector)
		{
			if (it->second == scopeToFind)
			{
				name = it->first;
			}
		}

		return name;
	}

	void Scope::Clear()
	{
		for (std::uint32_t i = 0; i < mOrderVector.Size(); ++i)
		{
			if (mOrderVector[i]->second.Type() == DatumType::Table)
			{
				for (std::uint32_t j = 0; j < mOrderVector[i]->second.Size(); ++j)
				{
					if (&mOrderVector[i]->second.Get<Scope&>(j) != nullptr)
					{
						delete &mOrderVector[i]->second.Get<Scope&>(j);
					}
				}
			}
		}

		mOrderVector.Clear();
		mTable.Clear();
	}
}

