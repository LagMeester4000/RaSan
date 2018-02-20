#pragma once
#include <vector>
#include "System.h"
#include "Settings.h"

namespace rac
{
	class EntityManager;

	struct SystemMetadata
	{
		ComponentMask mask;
	};

	class SystemManager
	{
	public:
		SystemManager();
		~SystemManager();

		//add system
		template<typename T>
		void addSystem(T *system);

		//add entity to systems that need it
		void addEntity(EntityId entity, EntityManager &entityManager);

		//remove entity from all systems
		void removeEntity(EntityId entity);

		//remove component from entity, update systems to remove entity if no longer needed
		void removeComponent(EntityId entity, ComponentMask &oldMask, ComponentMask &newMask);

		//update all the systems
		void update(float deltaTime, World *world);

		//get a system
		template<typename T>
		T *getSystem()
		{
			for (size_t i = 0; i < m_systems.size(); ++i)
			{
				T *ret = dynamic_cast<T*>(m_systems[i]);
				if (ret)
				{
					return ret;
				}
			}
			return nullptr;
		}
	private:
		std::vector<SystemBase*> m_systems;
		std::vector<SystemMetadata> m_systemMetadata;
	};

	template<typename T>
	inline void SystemManager::addSystem(T *system)
	{
		//create component mask
		SystemMetadata pushMeta;
		pushMeta.mask = getComponentMask<T>();
		
		//add component mask and system to arrays
		m_systems.push_back(system);
		m_systemMetadata.push_back(pushMeta);
	}
}