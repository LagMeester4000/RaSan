#pragma once
#include <memory>
#include <math.h>

namespace rac
{
	template<typename T>
	class Array
	{
	public:
		Array() : m_array(nullptr), m_size(0)
		{}

		~Array()
		{
			if (m_array)
			{
				deleteData(m_array);
			}
			m_array = nullptr;
			m_size = 0;
		}

		Array(size_t size) : m_size(size)
		{
			allocateRaw(size);
		}

		//copy constructor
		Array(const Array<T> &other)
		{
			copy(other);
		}

		Array<T> &operator=(const Array<T> &other)
		{
			copy(other);
			return *this;
		}

		//move constructor
		Array(Array<T> &&other)
		{
			move(other);
		}

		Array<T> &operator=(Array<T> &&other)
		{
			move(other);
			return *this;
		}

		//get size of the array
		size_t size()
		{
			return m_size;
		}

		//get if the array is initialized
		bool isInitialized()
		{
			return (m_array && m_size);
		}
		
		void reallocate(size_t size)
		{
			//calculate actual next size
			size = calculateNewIndex(size);

			if (size > m_size)
			{
				if (m_array)
				{
					T *newArray = allocateData(size);
					std::memcpy(newArray, m_array, m_size * sizeof(T));
					deleteData(m_array);
					m_array = newArray;
					return;
				}
				//else
				m_array = allocateData(size);
				m_size = size;
			}
		}

		//access
		T &operator[](size_t index)
		{
			return m_array[index];
		}

	private:
		//allocate array with a nullptr check on the array
		void allocateSafe(size_t size)
		{
			if (!m_array)
			{
				allocateRaw(size);
			}
		}

		//allocate the array
		void allocateRaw(size_t size)
		{
			m_array = allocateData(size);
		}

		void copy(const Array<T> &other)
		{

		}
		
		void move(Array<T> &&other)
		{
			m_array = other.m_array;
			m_size = other.m_size;
			other.m_array = nullptr;
			other.m_size = 0;
		}

		T *allocateData(size_t size)
		{
			return new T[size]();
		}
		void deleteData(T *data)
		{
			delete[] data;
		}

		size_t calculateNewIndex(size_t input)
		{
			float inF = (float)input;
			inF = std::sqrt(inF);
			inF = std::floorf(inF) + 1.f;
			return (size_t)(inF * inF);
		}
	private:
		T *m_array = nullptr;
		size_t m_size = 0;
	};
}