#include "../include/RaSan/detail/HasEntityChecker.h"

rac::HasEntityChecker::HasEntityChecker()
{
}

rac::HasEntityChecker::~HasEntityChecker()
{
}

void rac::HasEntityChecker::add(EntityId index)
{
	if (index.getIndex() >= m_hasEntity.size())
	{
		m_hasEntity.resize(index.getIndex() + 1);
	}

	//set to current entity
	m_hasEntity[index.getIndex()].has = true;
	m_hasEntity[index.getIndex()].version = index.getVersion();
}

void rac::HasEntityChecker::remove(EntityId index)
{
	if (index.getIndex() < m_hasEntity.size())
		m_hasEntity[index].has = false;
}

rac::u8 rac::HasEntityChecker::getVersion(EntityId index)
{
	if (index.getIndex() < m_hasEntity.size())
		return m_hasEntity[index.getIndex()].version;
	return 0;
}

rac::u8 rac::HasEntityChecker::getVersion(size_t index)
{
	if (index < m_hasEntity.size())
		return m_hasEntity[index].version;
	return 0;
}

bool rac::HasEntityChecker::hasEntity(EntityId entity)
{
	auto version = entity.getVersion();
	if (entity.getIndex() < m_hasEntity.size())
	{
		auto &obj = m_hasEntity[entity.getIndex()];
		return (version == obj.version) && obj.has;
	}
	return false;
}
