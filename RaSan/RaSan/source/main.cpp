#include <iostream>
#include "../include/RaSan/World.h"
#include "../include/RaSan/Entity.h"

class Position : public rac::Component
{
public:
	float x, y, z;
};

class Velocity : public rac::Component
{
public:
	float xv, yv, zv;
};

class Speed : public rac::Component
{
public:
	float speed;
};

class MovementSystem : public rac::System<Velocity>
{
public:
	void update(float deltaTime, rac::World *world)
	{
		int i = 0;
	}
};

class PositionSystem : public rac::System<Position>
{
public:
	void update(float deltaTime, rac::World *world)
	{
		int i = 0;
	}
};

class PosMovSystem : public rac::System<Velocity, Position>
{
public:
	void update(float deltaTime, rac::World *world)
	{
		int i = 0;
	}
};

int main()
{
	std::bitset<32> bt1, bt2;
	bt1[1] = 1;
	std::bitset<32> r1 = bt1 & bt2;


	//init world
	rac::World w = rac::World();

	//add systems
	w.addSystem<MovementSystem>();
	w.addSystem<PositionSystem>();
	w.addSystem<PosMovSystem>();

	
	rac::Entity e = w.createEntity();
	e.addComponent<Position>();

	//some entities
	rac::EntityId ent1, ent2, ent3;

	{//1
		ent1 = w.createEntity();
		w.addComponent<Position>(ent1);
	}

	{//2
		ent2 = w.createEntity();
		w.addComponent<Velocity>(ent2);
	}

	{//3
		ent3 = w.createEntity();
		w.addComponent<Position>(ent3);
		w.addComponent<Velocity>(ent3);
	}

	//update world
	w.update(0.5f);

	system("pause");
	return 0;
}


//#include <iostream>
//
//template<size_t N> 
//constexpr char getCharacter(const char(&arr)[N], size_t i)
//{
//	return arr[i];
//}
//
//template<char C, size_t I>
//struct StringLength
//{
//	template<size_t N>
//	constexpr static size_t func(const char(&arr)[N])
//	{
//		return StringLength<getCharacter(arr, I + 1), I + 1>::func(arr);
//	}
//};
//
//template<size_t I>
//struct StringLength<'\n',I>
//{
//	template<size_t N>
//	constexpr static size_t func(const char(&arr)[N])
//	{
//		return I;
//	}
//};
//
//template<size_t N>
//constexpr size_t stringLength(const char(&arr)[N])
//{
//	return StringLength<getCharacter(arr, 0), 0>::func(arr);
//}
//
//
//void main()
//{
//	std::cout << stringLength("klaa") << std::endl;
//
//	system("pause");
//}