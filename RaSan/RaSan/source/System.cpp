#include "../include/RaSan/System.h"

void rac::SystemBase::addEntity(EntityId entity)
{
	if (!m_entityMetadata.hasEntity(entity))
	{
		auto newIndex = m_entities.size();
		m_entities.push_back(entity);
		m_entityMetadata.add(entity);

		//update indices
		m_entityIndices.resize(entity.getIndex() + 1);
		m_entityIndices[entity.getIndex()] = newIndex;
	}
}

void rac::SystemBase::removeEntity(size_t index)
{
	if (index < m_entities.size())
	{
		EntityId entity = m_entities[index];
		m_entityMetadata.remove(entity);

		auto top = m_entities.size() - 1;
		//EntityId oldEnt = m_entities[index];
		EntityId newEnt = m_entities[top];
		m_entities.pop_back();
		m_entityIndices[newEnt.getIndex()] = index;
	}
}

void rac::SystemBase::removeEntity(EntityId entity)
{
	if (m_entityMetadata.hasEntity(entity))
	{
		auto top = m_entities.size() - 1;
		auto entIndex = m_entityIndices[entity.getIndex()];
		auto newIndex = m_entityIndices[m_entities[top]];
		EntityId newEntity = m_entities[newIndex];
		m_entities[entIndex] = m_entities[newIndex];
		m_entityIndices[newEntity.getIndex()] = newIndex;
	}
}

