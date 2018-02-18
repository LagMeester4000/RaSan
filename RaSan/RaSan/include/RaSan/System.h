#pragma once
#include <vector>
#include <cstddef>
#include "../Unen/TList.h"
#include "detail/TypeIndex.h"
#include "detail/EntityID.h"
#include "detail/HasEntityChecker.h"
#include "Settings.h"
#include "Component.h"

namespace rac
{
	class World;

	//base class for the system (non-template)
	class SystemBase
	{
		friend class World;
		friend class SystemManager;

		using IndexType = unsigned int;
	public:
		SystemBase() {}

		virtual void update(float deltaTime, World *world) {}

	private:
		void addEntity(EntityId entity);
		void removeEntity(size_t index);
		void removeEntity(EntityId entity);

	private:
		//the entities currently in the system
		std::vector<EntityId> m_entities;

		//put in an entity and get an index in the array
		std::vector<IndexType> m_entityIndices;

		//metadata for entities in the system, to check if the entity is in the system
		HasEntityChecker m_entityMetadata;
	};

	//System class that holds entities with certain components
	//template arguments should be the components that an entity needs to be placed in the system
	template<typename ... Components>
	class System : public SystemBase
	{
		friend class World;
	public:
		using RequiredComponents = unen::TList<Components...>;
	};


	//struct impl to fill a component mask
	template<typename First, typename ... Other>
	struct GetComponentMask
	{
		static void func(ComponentMask &current)
		{
			auto type = TypeIndex<Component>::get<First>();
			current[type] = true;
			GetComponentMask<Other...>::func(current);
		}
	};

	template<typename First>
	struct GetComponentMask<First>
	{
		static void func(ComponentMask &current)
		{
			auto type = TypeIndex<Component>::get<First>();
			current[type] = true;
		}
	};

	template<typename ... Types>
	void __back_getComponentMask(ComponentMask &mask, unen::TList<Types...>)
	{
		GetComponentMask<Types...>::func(mask);
	}

	//function to get the component mask of a system
	template<typename T>
	ComponentMask getComponentMask()
	{
		ComponentMask c = ComponentMask();
		__back_getComponentMask(c, T::RequiredComponents{});
		return c;
	}
}