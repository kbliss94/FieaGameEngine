#include "pch.h"
#include "Action.h"
#include "Entity.h"

namespace FieaGameEngine
{
	std::string Action::Name() const
	{
		return Find("Name")->Get<std::string&>();
	}

	void Action::SetName(const std::string& name)
	{
		mName = name;
		Find("Name")->SetStorage(&mName, mName.length());
	}

	void Action::Initialize()
	{
		AddExternalAttribute("Name", &mName, sizeof(mName));
	}
}