#include "../include/RaSan/RemoveList.h"
#include "../include/RaSan/World.h"

void rac::RemoveList::update(World * world)
{
	//remove components
	for (size_t i = 0; i < m_componentRemoveList.size(); ++i)
	{
		world->removeComponentActual(m_componentRemoveList[i].entity, m_componentRemoveList[i].component);
	}
	//clear list
	m_componentRemoveList.clear();

	//remove entities
	for (size_t i = 0; i < m_entityRemoveList.size(); ++i)
	{
		world->removeEntityActual(m_entityRemoveList[i].entity);
	}
	//clear list
	m_entityRemoveList.clear();
}

void rac::RemoveList::addEntity(EntityId entity)
{
	m_entityRemoveList.push_back(RemoveEntity{ entity });
}

void rac::RemoveList::addComponent(EntityId entity, rac::u32 type)
{
	m_componentRemoveList.push_back(RemoveComponent{ entity, type });
}
