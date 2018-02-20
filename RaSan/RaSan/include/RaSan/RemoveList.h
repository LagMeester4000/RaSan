#pragma once
#include "detail/EntityID.h"
#include "detail/Types.h"
#include <vector>

namespace rac
{
	struct RemoveEntity
	{
		EntityId entity;
	};

	struct RemoveComponent
	{
		EntityId entity;
		rac::u32 component;
	};

	class RemoveList
	{
	public:
		RemoveList() {}

		void update(class World *world);

		void addEntity(EntityId entity);
		void addComponent(EntityId entity, rac::u32 type);
	private:
		std::vector<RemoveEntity> m_entityRemoveList;
		std::vector<RemoveComponent> m_componentRemoveList;
	};
}