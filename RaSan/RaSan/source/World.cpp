#include "../include/RaSan/World.h"

rac::EntityId rac::World::createEntity()
{
	return m_entities.create();
}

void rac::World::removeEntity(EntityId entity)
{
	m_entities.remove(entity);

	//remove all components
	m_components.removeAllComponents(entity, m_entities.getComponentMask(entity));
}

void rac::World::update(float deltaTime)
{
	m_systems.update(deltaTime, this);
}
