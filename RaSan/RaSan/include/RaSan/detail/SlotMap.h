#pragma once
#include <vector>
#include "Array.h"
#include "EntityID.h"

namespace rac
{
	template<typename T, typename IndexType = unsigned int>
	class SlotInsertMap
	{
	public:
		SlotInsertMap() 
		{
			m_top = 0;
		}

		void insert(T value, IndexType index)
		{
			//get new index
			IndexType top = m_top;
			m_top++;

			//grow arrays if needed
			m_indices.reallocate(index + 1);
			m_array.reallocate(m_top + 1);
			m_indexBack.reallocate(m_top + 1);

			//insert into data array
			m_array[top] = value;
			m_indexBack[top] = index;

			//insert into indices
			m_indices[index] = top;
		}

		void remove(IndexType index)
		{
			//get actual index
			IndexType acIndex = m_indices[index];

			//get top to swap
			m_top--;
			IndexType top = m_top;

			//swap array data
			m_array[acIndex] = m_array[top];
			m_indices[m_indexBack[top]] = index;
			m_indexBack[acIndex] = index;
		}

		T &get(IndexType index)
		{
			return m_array[m_indices[index]];
		}

		T &operator[](IndexType index)
		{
			return get(index);
		}

		IndexType sizeIndices()
		{
			return m_indices.size();
		}

		IndexType size()
		{
			return m_array.size();
		}
	private:
		//redirection array
		Array<IndexType> m_indices;

		//data array
		Array<T> m_array;
		Array<IndexType> m_indexBack;

		//index of top
		IndexType m_top = 0;
	};

	template<typename T, typename IndexType = unsigned int>
	class ComponentSlotMap
	{
		using EntityIndex = EntityId;
	public:
		void insert(T t, EntityIndex entity)
		{
			//get index of entity
			auto index = entity.getIndex();

			//get new index
			IndexType newLocation = m_top;
			m_top++;

			//insert index into indices
			m_indices.reallocate(index);
			m_indices[index] = newLocation;
			m_componentData.reallocate(newLocation + 1);
			m_componentEntIndex.reallocate(newLocation + 1);
			m_componentData[newLocation] = t;
			m_componentEntIndex[newLocation] = entity;
		}

		void remove(EntityIndex entity)
		{
			//get index of entity
			auto index = entity.getIndex();

			//get index into component array
			IndexType acIndex = m_indices[index];

			//call component destructor
			m_componentData[acIndex].~T();

			//get top index
			m_top--;
			IndexType topIndex = m_top;

			//swap top
			m_componentData[acIndex] = m_componentData[topIndex];
			m_componentEntIndex[acIndex] = m_componentEntIndex[topIndex];

			//update indices
			IndexType indicesIndex = m_componentEntIndex[topIndex].getIndex();
			m_indices[indicesIndex] = acIndex;
		}

		T &get(EntityIndex entity)
		{
			return m_componentData[m_indices[entity.getIndex()]];
		}

		T &operator[](EntityIndex entity)
		{
			return get(entity);
		}

		IndexType size()
		{
			return m_top;
		}

		//returns the array with all the components
		//PLEASE DO NOT CHANGE CONTENTS OF ARRAY IF POSSIBLE
		Array<T> &getComponentArray()
		{
			return m_componentData;
		}

	private:
		//redirection array
		Array<IndexType> m_indices;

		//component data arrays
		Array<EntityIndex> m_componentEntIndex;
		Array<T> m_componentData;

		//index of top
		IndexType m_top = 0;
	};
}