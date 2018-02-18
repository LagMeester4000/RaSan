#pragma once
#include "SystemManager.h"
#include "EntityManager.h"
#include "ComponentContainer.h"

namespace rac
{
	//World class that holds the systems and entities
	class World
	{
	public:
		template<typename T, typename ... Args>
		void addSystem(Args&& ... args)
		{
			m_systems.addSystem(new T(std::forward(args)...));
		}

		template<typename T>
		void addComponent(EntityId entity)
		{
			m_entities.addComponent<T>(entity);
			m_components.addComponent<T>(entity);
			m_systems.addEntity(entity, m_entities);
		}

		//PLS FIX
		template<typename T>
		void removeComponent(EntityId entity)
		{
			ComponentMask oldMask = m_entities.getComponentMask(entity);
			m_entities.removeComponent<T>(entity);
			m_components.removeComponent<T>(entity);
			//UNFINISHED
			//m_systems.removeComponent<T>(entity); 
		}

		EntityId createEntity();
		void removeEntity(EntityId entity);

		void update(float deltaTime);
		
		template<typename T>
		ComponentBag<T> &getComponents()
		{
			return *m_components.getBag<T>();
		}
	private:
		SystemManager m_systems;
		EntityManager m_entities;
		ComponentContainer m_components;
	};
}