#pragma once
#include "World.h"
#include "EntityPre.h"

namespace rac
{
	class Entity
	{
	public:
		Entity(World *world, EntityId entityId);
		Entity(EntityPre &&entity);

		template<typename T>
		void addComponent()
		{
			m_world->addComponent<T>(m_entityId);
		}

		template<typename T>
		void removeComponent()
		{
			m_world->removeComponent<T>(m_entityId);
		}

		template<typename T>
		bool hasComponent()
		{
			m_world->hasComponent<T>(m_entityId);
		}

		bool isDead()
		{
			m_world->isDead(m_entityId);
		}

		operator EntityId() { return m_entityId; }

	private:
		World *m_world;
		EntityId m_entityId;
	};
}