#include "../include/RaSan/World.h"

bool rac::World::isDead(EntityId entity)
{
	return m_entities.isDead(entity);
}

rac::EntityId rac::World::createEntityId()
{
	return m_entities.create();
}

rac::EntityPre rac::World::createEntity()
{
	return EntityPre{this, createEntityId()};
}

void rac::World::removeEntity(EntityId entity)
{
	m_removeList.addEntity(entity);
}

void rac::World::removeEntityActual(EntityId entity)
{
	//remove entity from register
	m_entities.remove(entity);

	//remove all components
	m_components.removeAllComponents(entity, m_entities.getComponentMask(entity));

	//remove entity from all systems
	m_systems.removeEntity(entity);
}

void rac::World::update(float deltaTime)
{
	//update all systems
	m_systems.update(deltaTime, this);
	
	//remove entities that were marked this update
	m_removeList.update(this);
}

void rac::World::removeComponentActual(EntityId entity, rac::u32 type)
{
	ComponentMask oldMask = m_entities.getComponentMask(entity);
	m_entities.removeComponent(entity, type);
	ComponentMask newMask = m_entities.getComponentMask(entity);
	m_components.removeComponent(entity, type);
	m_systems.removeComponent(entity, oldMask, newMask);
}
