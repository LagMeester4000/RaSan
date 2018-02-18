#pragma once
#include <bitset>

namespace rac
{
	constexpr size_t MaxComponents = 32;
	constexpr size_t MaxSystem = 32;

	using ComponentMask = std::bitset<MaxComponents>;
}