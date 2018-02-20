#pragma once
#include "detail/SlotMap.h"
#include "detail/TypeIndex.h"
#include "Component.h"
#include "Settings.h"

namespace rac
{
	//call update SFINAE
	template<typename T, typename = int>
	struct __call_update
	{
		static void func(T &object, float deltaTime)
		{}
	};

	template<typename T>
	struct __call_update<T, decltype(&T::update, 0)>
	{
		static void func(T &object, float deltaTime)
		{
			object.update(deltaTime);
		}
	};

	template<typename T>
	void callUpdate(T &object, float deltaTime)
	{
		__call_update<T>::func(object, deltaTime);
	}

	//call init SFINAE
	template<typename T, typename = int>
	struct __call_init
	{
		static void func(T &object)
		{}
	};

	template<typename T>
	struct __call_init<T, decltype(&T::init, 0)>
	{
		static void func(T &object)
		{
			object.init();
		}
	};

	template<typename T>
	void callInit(T &object)
	{
		__call_init<T>::func(object);
	}


	class ComponentBagBase
	{
	public:
		virtual ~ComponentBagBase() {}
		virtual void add(EntityId entity) = 0;
		virtual void remove(EntityId entity) = 0;
		virtual void reset(EntityId entity) = 0;
		virtual void update(float deltaTime) = 0;
	};

	template<typename T>
	class ComponentBag : public ComponentBagBase
	{
	public:
		void add(EntityId entity) final
		{
			m_components.insert(T(), entity);
			callInit(m_components[entity]);
		}

		void remove(EntityId entity) final
		{
			m_components.remove(entity);
		}

		void reset(EntityId entity) final
		{
			//nope
		}

		void update(float deltaTime) final
		{
			auto &compArray = m_components.getComponentArray();
			
			for (unsigned int i = 0; i < m_components.size(); i++)
			{
				callUpdate(compArray[i], deltaTime);
			}
		}

		T &get(EntityId entity)
		{
			return m_components[entity];
		}

	private:
		ComponentSlotMap<T> m_components;
	};

	class ComponentContainer
	{
	public:
		ComponentContainer()
		{}

		~ComponentContainer()
		{
			//ADD: loop through slotmap and delete bags
			//for (size_t i = 0; i < m_componentBags.)
		}

		template<typename T>
		void addComponent(EntityId entity)
		{
			//get type index
			auto componentType = TypeIndex<Component>::get<T>();

			//get bag
			ComponentBagBase *bag = nullptr;
			if (componentType < m_componentBags.sizeIndices())
			{
				bag = m_componentBags[componentType];
			}

			//check if bag exists
			if (!bag)
			{
				//create new component bag
				ComponentBagBase *push = new ComponentBag<T>();
				m_componentBags.insert(push, componentType);
			}

			//add component to bag
			m_componentBags.get(componentType)->add(entity);
		}

		template<typename T>
		void removeComponent(EntityId entity)
		{
			//get type index
			auto componentType = TypeIndex<Component>::get<T>();

			//get bag
			ComponentBagBase *bag = nullptr;
			if (componentType < m_componentBags.sizeIndices())
			{
				bag = m_componentBags[componentType];
			}

			//check if bag doesnt exist
			if (!bag)
			{
				return;
			}

			//add component to bag
			m_componentBags.get(componentType)->remove(entity);
		}

		void removeComponent(EntityId entity, rac::u32 type);

		template<typename T>
		ComponentBag<T> *getBag()
		{
			//get type index
			auto componentType = TypeIndex<Component>::get<T>();

			//get bag
			ComponentBagBase *bag = nullptr;
			if (componentType < m_componentBags.sizeIndices())
			{
				bag = m_componentBags[componentType];
			}

			//check if bag exists
			if (!bag)
			{
				//create new component bag
				ComponentBagBase *push = new ComponentBag<T>();
				m_componentBags.insert(push, componentType);
				return push;
			}
			return dynamic_cast<ComponentBag<T>*>(bag);
		}
		
		void removeAllComponents(EntityId entity, ComponentMask components);

	private:
		SlotInsertMap<ComponentBagBase*> m_componentBags;
	};
}