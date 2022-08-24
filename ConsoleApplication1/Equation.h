#pragma once
#include <initializer_list>

enum class SLType
{
	None,
	SPI,
	SI,
	SPD
};
template <typename T>
class Equation
{
public:
	Equation();
	Equation(int size);
	Equation(int size,T* _values,T result);
	Equation(int size, std::initializer_list<T> _values, T result);

	void Free();
	T& operator[] (int index);
	T& Result();
private:
	T* values;
	T result;
	int size;
};

template<typename T>
inline Equation<T>::Equation()
{
	size = 0;
	values = NULL;
	result = T();
}

template<typename T>
inline Equation<T>::Equation(int size)
{
	values = new T[size];
	result = T();
	this->size = size;
}

template<typename T>
inline Equation<T>::Equation(int size, T* _values, T result)
{
	this->size = size;
	values = new T[size];
	for (size_t i = 0; i < size; i++)
	{
		values[i] = _values[i];
	}
	this->result = result;
}

template<typename T>
inline Equation<T>::Equation(int size, std::initializer_list<T> _values, T result)
{
	this->size = size;
	values = new T[size];
	auto begin = _values.begin();
	for (size_t i = 0; i < size; i++)
	{
		values[i] = begin[i];
	}
	this->result = result;
}



template<typename T>
inline void Equation<T>::Free()
{
	delete[] values;
}

template<typename T>
inline T& Equation<T>::operator[](int index)
{
	return values[index];
}

template<typename T>
inline T& Equation<T>::Result()
{
	return result;
}
