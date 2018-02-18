#pragma once
#include <vector>
#include "EntityID.h"

namespace rac
{
	struct HasEntityStruct
	{
		rac::u8 version = 0;
		bool has = false;
	};

	//keeps track of which entities a system has
	class HasEntityChecker
	{
	public:
		HasEntityChecker();
		~HasEntityChecker();

		void add(EntityId index);
		void remove(EntityId index);
		rac::u8 getVersion(EntityId index);
		rac::u8 getVersion(size_t index);
		bool hasEntity(EntityId entity);
	private:
		std::vector<HasEntityStruct> m_hasEntity;
	};
}