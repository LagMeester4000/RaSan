#include "../include/RaSan/EntityManager.h"

void rac::EntityMetadata::reset()
{
	m_hasComponents.reset();
}

rac::u8 rac::EntityMetadata::getVersion()
{
	return m_version;
}

rac::u8 rac::EntityMetadata::updateVersion()
{
	m_version++;
	return m_version;
}

void rac::EntityMetadata::addComponent(rac::u32 type)
{
	m_hasComponents[type] = true;
}

void rac::EntityMetadata::removeComponent(rac::u32 type)
{
	m_hasComponents[type] = false;
}

bool rac::EntityMetadata::hasComponents(ComponentMask mask)
{
	ComponentMask testMask = mask & m_hasComponents;
	return testMask == mask;
}

rac::ComponentMask rac::EntityMetadata::getComponentMask()
{
	return m_hasComponents;
}

rac::EntityManager::EntityManager()
{
}

rac::EntityId rac::EntityManager::create()
{
	if (m_freeList.size())
	{
		EntityIndexType reUsed = m_freeList.front(); 
		m_freeList.pop_front();
		m_entities[reUsed].reset();
		return __EntityCreator::createEntityId(reUsed, m_entities[reUsed].getVersion());
	}
	return createNewId();
}

void rac::EntityManager::remove(EntityId entity)
{
	m_entities[entity.getIndex()].updateVersion();
}

bool rac::EntityManager::isDead(EntityId entity)
{
	return m_entities[entity.getIndex()].getVersion() != entity.getVersion();
}

void rac::EntityManager::addComponent(EntityId entity, rac::u32 type)
{
	if (!isDead(entity))
		m_entities[entity.getIndex()].addComponent(type);
}

void rac::EntityManager::removeComponent(EntityId entity, rac::u32 type)
{
	m_entities[entity.getIndex()].removeComponent(type);
}

bool rac::EntityManager::hasComponents(EntityId entity, ComponentMask mask)
{
	return m_entities[entity.getIndex()].hasComponents(mask);
}

rac::ComponentMask rac::EntityManager::getComponentMask(EntityId entity)
{
	return m_entities[entity.getIndex()].getComponentMask();
}

rac::EntityId rac::EntityManager::createNewId()
{
	EntityIndexType newIndex = m_top;
	m_top++;
	m_entities.reallocate(m_top);
	m_entities[newIndex].reset();
	return __EntityCreator::createEntityId(m_top, 0);
}
