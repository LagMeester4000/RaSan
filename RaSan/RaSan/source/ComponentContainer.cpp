#include "../include/RaSan/ComponentContainer.h"

void rac::ComponentContainer::removeComponent(EntityId entity, rac::u32 type)
{

}

void rac::ComponentContainer::removeAllComponents(EntityId entity, ComponentMask components)
{
	for (size_t i = 0; i < components.size(); ++i)
	{
		if (components[i])
		{
			ComponentBagBase *bag = m_componentBags[i];
			bag->remove(entity);
		}
	}
}
