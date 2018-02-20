#pragma once
#include <bitset>
#include "detail/Array.h"
#include "detail/EntityID.h"
#include "Component.h"
#include "Settings.h"
#include <deque>
#include "detail/TypeIndex.h"

namespace rac
{
	using EntityIndexType = unsigned int;

	class EntityMetadata
	{
	public:
		void reset();
		
		rac::u8 getVersion();
		rac::u8 updateVersion();
		
		void addComponent(rac::u32 type);
		void removeComponent(rac::u32 type);
		
		bool hasComponents(ComponentMask mask);

		template<typename T>
		bool hasComponent()
		{
			auto type = TypeIndex<Component>::get<T>();
			return m_hasComponents[type];
		}

		ComponentMask getComponentMask();
	private:
		rac::u8 m_version = 0;
		ComponentMask m_hasComponents;
	};

	class EntityManager
	{
	public:
		EntityManager();

		//create unique entity ID
		EntityId create();

		//remove entity ID
		void remove(EntityId entity);

		//returns if the entity is dead
		bool isDead(EntityId entity);

		//register component for entity
		template<typename T>
		void addComponent(EntityId entity);
		void addComponent(EntityId entity, rac::u32 type);

		//unregister component for entity
		template<typename T>
		void removeComponent(EntityId entity);
		void removeComponent(EntityId entity, rac::u32 type);

		//test if an entity has certain components
		bool hasComponents(EntityId entity, ComponentMask mask);

		//test if an entity has a certain component
		template<typename T>
		bool hasComponent(EntityId entity)
		{
			return m_entities[entity.getIndex()].hasComponent<T>();
		}

		//get a copy of the component mask
		ComponentMask getComponentMask(EntityId entity);
	private:
		//create new entity metadata and ID
		EntityId createNewId();
	private:
		//array holding entity metadata (version number and held components)
		Array<EntityMetadata> m_entities;
		EntityIndexType m_top;
		std::deque<EntityIndexType> m_freeList;
	};

	template <typename T>
	void EntityManager::addComponent(EntityId entity)
	{
		auto type = TypeIndex<Component>::get<T>();
		if (!isDead(entity))
			m_entities[entity.getIndex()].addComponent(type);
	}

	template<typename T>
	inline void EntityManager::removeComponent(EntityId entity)
	{
		auto type = TypeIndex<Component>::get<T>();
		m_entities[entity.getIndex()].removeComponent(type);
	}
}
