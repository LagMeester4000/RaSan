#pragma once
#include "TypeIndex.h"

namespace rac
{
	template<typename Base>
	class OpaquePointer
	{
	public:
		template<typename T>
		OpaquePointer(T *ref) : m_ref((Base*)ref), m_type(TypeIndex<Base>::get<T>())
		{}

		template<typename T>
		T *get()
		{
			if (TypeIndex<Base>::get<T>() == m_type)
			{
				return (T*)m_ref;
			}
			return nullptr;
		}

	private:
		Base *m_ref;
		rac::u32 m_type;
	};
}