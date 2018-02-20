#pragma once
#include "detail/EntityID.h"

namespace rac
{
	class World;

	class EntityPre
	{
	public:
		World *world;
		EntityId entity;
	public://conversion
		operator EntityId() { return entity; }
	};
}