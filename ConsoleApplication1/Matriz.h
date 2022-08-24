#pragma once
#include <initializer_list>
template <typename T>
class Matriz
{
public:
	struct Index
	{
		int L;
		int C;
		Index(int l, int c);
	};
	Matriz();
	Matriz(int L,int C);
	Matriz(int L, int C,T* arr);
	Matriz(int L, int C, std::initializer_list<T> arr);

	~Matriz();
	static int GetValueByRange(int v, int ma);
	T Det();
	T Cofator(Index index);
	T& operator [](Index i);
	T& at(Index i);
private:
	int L, C;
	T* value;
};

template<typename T>
inline Matriz<T>::Matriz()
{
	value = nullptr;
	L = C = 0;

}

template<typename T>
inline Matriz<T>::Matriz(int L, int C)
{
	value = new T[L * C];
	this->L = L;
	this->C = C;
}

template<typename T>
inline Matriz<T>::Matriz(int L, int C, T* arr)
{
	auto len = L * C;
	value = new T[len];

	for (size_t i = 0; i < len; i++)
	{
		value[i] = arr[i];
	}
	this->L = L;
	this->C = C;
}

template<typename T>
inline Matriz<T>::Matriz(int L, int C, std::initializer_list<T> arr)
{
	auto len = L * C;
	value = new T[len];
	auto start = arr.begin();
	for (size_t i = 0; i < len; i++)
	{
		value[i] = start[i];
	}
	this->L = L;
	this->C = C;
}

template<typename T>
inline Matriz<T>::~Matriz()
{
	if (value != nullptr)
	{
		L = C = 0;
		delete[] value;
		value = nullptr;
	}
}

template<typename T>
inline int Matriz<T>::GetValueByRange(int v,int max)
{
	auto rest = v % max;
	return v < 0 ? (rest == 0 ? 0 : max + rest) : rest;
}

template<typename T>
inline T Matriz<T>::Det()
{
	if (L == C)
	{
		if (L <= 0)
		{
			return 0;
		}
		if (L == 1)
		{
			return this->at(Index(0, 0));
		}
		if (L == 2)
		{
			return this->at(Index(0, 0)) * this->at(Index(1, 1)) - this->at(Index(0, 1)) * this->at(Index(1, 0));
		}
		if (L == 3)
		{
			T DP = T(), DS = T();
			for (size_t i = 0; i < 3; i++)
			{
				DP += this->at(Index(0, i)) * this->at(Index(1, GetValueByRange(i + 1, 3))) * this->at(Index(2, GetValueByRange(i + 2, 3)));
				DS += this->at(Index(0, i)) * this->at(Index(1, GetValueByRange(i - 1, 3))) * this->at(Index(2, GetValueByRange(i - 2, 3)));

			}
			return DP - DS;
		}
		if (L >= 4)
		{
			T D = T();
			for (size_t i = 0; i < C; i++)
			{
				T a1j = this->at(Index(0, i));
				T A1j = this->Cofator(Index(0, i));

				D += a1j * A1j;
			}
			return D;
		}
	}
	else
	{
		return 0;
	}
}

template<typename T>
inline T Matriz<T>::Cofator(Index index)
{
	int soma = index.C + index.L % 2 == 0 ? 1 : -1;
	Matriz<T> matriz(L - 1, C - 1);
	int i3 = 0;
	for (size_t i = 0; i < L; i++)
	{
		int i4 = 0;
		if (i != index.L)
		{
			for (size_t i2 = 0; i2 < C; i2++)
			{
				if (i2 != index.C)
				{
					matriz[Index(i3, i4)] = this->at(Index(i, i2));
					++i4;
				}
			}
			i3++;
		}
	}
	return soma * matriz.Det();
}

template<typename T>
inline T& Matriz<T>::operator[](Matriz<T>::Index i)
{
	
	return at(i);
}

template<typename T>
inline T& Matriz<T>::at(Index i)
{
	return value[i.L * L + i.C];
}

template<typename T>
inline Matriz<T>::Index::Index(int l, int c)
{
	L = l;
	C = c;
}
