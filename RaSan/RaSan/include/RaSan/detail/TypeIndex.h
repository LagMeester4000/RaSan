#pragma once
#include <type_traits>
#include "Types.h"

namespace rac
{
	template<typename Base>
	struct TypeIndex
	{
		template<typename T, typename = typename std::enable_if<std::is_base_of<Base, T>::value>::type>
		static rac::u32 get()
		{
			const static rac::u32 ret = m_typeIndex++;
			return ret;
		}

	private:
		static rac::u32 m_typeIndex;
	};
	template<typename Base>
	rac::u32 TypeIndex<Base>::m_typeIndex = 0;
}