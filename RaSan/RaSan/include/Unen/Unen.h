#pragma once
#include "TList.h"

namespace unen
{

}


class TestClass
{
public:
	float x, y;
	int health;

	template<typename T>
	auto serialize(T t)
	{
		return t(x, y, health);
	}
};