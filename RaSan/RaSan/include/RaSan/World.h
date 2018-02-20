#pragma once
#include "SystemManager.h"
#include "EntityManager.h"
#include "ComponentContainer.h"
#include "RemoveList.h"
#include "EntityPre.h"

namespace rac
{
	//World class that holds the systems and entities
	class World
	{
		friend class RemoveList;
	public:
		//add a system to the world
		template<typename T, typename ... Args>
		void addSystem(Args&& ... args)
		{
			m_systems.addSystem(new T(std::forward(args)...));
		}

		//add a component to an entity
		template<typename T>
		void addComponent(EntityId entity)
		{
			m_entities.addComponent<T>(entity);
			m_components.addComponent<T>(entity);
			m_systems.addEntity(entity, m_entities);
		}

		template<typename T>
		void removeComponent(EntityId entity)
		{
			m_removeList.addComponent(entity, TypeIndex<Component>::get<T>());
		}

		//returns if the entity has component T
		template<typename T>
		bool hasComponent(EntityId entity)
		{
			return m_entities.hasComponent<T>(entity);
		}

		//returns if the entity is dead
		bool isDead(EntityId entity);

		//create a new entity ID
		EntityId createEntityId();

		//create entity
		EntityPre createEntity();

		//destroy entity
		void removeEntity(EntityId entity);

		//update the systems
		void update(float deltaTime);
		
		//get a component bag
		//a component bag holds components and the entities they belong to
		template<typename T>
		ComponentBag<T> &getComponents()
		{
			return *m_components.getBag<T>();
		}

		//get system of type T
		template<typename T>
		T *getSystem()
		{
			m_systems.getSystem<T>();
		}

	private:
		//remove an entity
		void removeEntityActual(EntityId entity);

		//remove a component from an entity
		template<typename T>
		void removeComponentActual(EntityId entity)
		{
			ComponentMask oldMask = m_entities.getComponentMask(entity);
			m_entities.removeComponent<T>(entity);
			ComponentMask newMask = m_entities.getComponentMask(entity);
			m_components.removeComponent<T>(entity);
			m_systems.removeComponent(entity, oldMask, newMask);
		}

		//remove a component from an entity
		void removeComponentActual(EntityId entity, rac::u32 type);

	private:
		SystemManager m_systems;
		EntityManager m_entities;
		ComponentContainer m_components;
		RemoveList m_removeList;
	};
}