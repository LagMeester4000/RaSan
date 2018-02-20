#include "../include/RaSan/Entity.h"

rac::Entity::Entity(World * world, EntityId entityId)
{
	m_world = world;
	m_entityId = entityId;
}

rac::Entity::Entity(EntityPre && entity)
{
	m_world = entity.world;
	m_entityId = entity.entity;
}
