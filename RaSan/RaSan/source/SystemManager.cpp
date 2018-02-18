#include "../include/RaSan/SystemManager.h"
#include "../include/RaSan/EntityManager.h"
#include <cstddef>

rac::SystemManager::SystemManager()
{
}

rac::SystemManager::~SystemManager()
{
}

void rac::SystemManager::addEntity(EntityId entity, EntityManager & entityManager)
{
	ComponentMask entMask = entityManager.getComponentMask(entity);
	
	for (size_t i = 0; i < m_systemMetadata.size(); ++i)
	{
		if ((m_systemMetadata[i].mask & entMask) == m_systemMetadata[i].mask)
		{
			m_systems[i]->addEntity(entity);
		}
	}
}

void rac::SystemManager::removeComponent(EntityId entity, ComponentMask & oldMask, ComponentMask & newMask)
{
	for (size_t i = 0; i < m_systemMetadata.size(); ++i)
	{
		if (m_systems[i])
		{
			if ((m_systemMetadata[i].mask & oldMask) == m_systemMetadata[i].mask)
			{
				//contains entity
				//test to see if should remove it
				if ((m_systemMetadata[i].mask & newMask) != m_systemMetadata[i].mask)
				{
					//entity should be removed
					m_systems[i]->removeEntity(entity);
				}
			}
		}
	}
}

void rac::SystemManager::update(float deltaTime, World * world)
{
	for (size_t i = 0; i < m_systems.size(); ++i)
	{
		m_systems[i]->update(deltaTime, world);
	}
}
