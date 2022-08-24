#include <iostream>
#include <locale>
#include <string>
#include <Light.h>
#include "Matriz.h"
#include "Equation.h"
#include <sstream>
#include <fstream>
#include <windows.h>

template<typename T>
Light::Array<T> Cramer(Light::Array<Equation<T>>& equations, SLType& type)
{
	size_t len = equations.get_Count();
	Light::Array<T> ret(len);

	Matriz<T> D(len, len);

	for (size_t i = 0; i < len; i++)
	{
		Equation<T>& current = equations[i];
		for (size_t i2 = 0; i2 < len; i2++)
		{
			D[Matriz<T>::Index(i, i2)] = current[i2];
		}
	}
	T detD = D.Det();
	int zero = 0;
	if (detD != 0)
	{
		type = SLType::SPD;
	}
	for (size_t i = 0; i < len; i++)
	{
		for (size_t i2 = 0; i2 < len; i2++)
		{
			Equation<T>& current = equations[i2];
			D[Matriz<T>::Index(i2, i)] = current.Result();
		}
		T detDi = D.Det();
		if (detD != 0)
		{
			ret.Add(detDi / detD);
		}
		else
		{
			if (detDi == 0)
			{
				++zero;
			}
		}
		for (size_t i2 = 0; i2 < len; i2++)
		{
			Equation<T>& current = equations[i2];

			D[Matriz<T>::Index(i2, i)] = current[i];
		}
	}
	if (zero == len)
	{
		type = SLType::SPI;
	}
	else if (detD == 0)
	{
		type = SLType::SI;
	}
	return ret;
}

void Evaluate(Light::Token& token)
{
	using T = double;
	auto expression1 = token.expression[0];
	auto len = expression1.get_Count();

	Light::Array<Equation<T>> equations(len);
	auto enumerator = expression1.get_Enumerator();
	while (enumerator.Next())
	{
		auto current = enumerator.get_Current().list;
		auto lst = current->at(0).list;
		auto val2 = current->at(1);
		auto result = val2.ToDouble();
		auto lenarray = lst->get_Count();
		Equation<T> eq(len);
		auto enumerator2 = lst->get_Enumerator();
		int i = 0;
		while (enumerator2.Next())
		{
			auto current2 = enumerator2.get_Current();
			auto value = current2.ToDouble();
			eq[i++] = value;
		}
		(eq.Result()) = result;
		equations.Add(eq);
	}
	SLType sltype;
	auto results = Cramer(equations, sltype);
	auto enumerator3 = equations.get_Enumerator();
	while (enumerator3.Next())
	{
		enumerator3.get_Current().Free();
	}
	equations.Free();
	switch (sltype)
	{
	case SLType::SPI:
		std::cout << "Sistema Linear: S.P.I." << std::endl;
		break;
	case SLType::SI:
		std::cout << "Sistema Linear: S.I." << std::endl;
		break;
	case SLType::SPD:
		std::cout << "Sistema Linear: S.P.D." << std::endl;
		break;
	}
	std::cout << "S = {( ";

	for (size_t i = 0; i < len; i++)
	{
		if (i == 0)
		{
			std::cout << results[i];
		}
		else
		{
			std::cout << "," << results[i];
		}
	}
	std::cout << " )}" << std::endl;
	results.Free();
}

std::string slurp(std::ifstream& in) {
	std::ostringstream sstr;
	sstr << in.rdbuf();
	return sstr.str();
}

int main()
{
	std::ifstream is("C:\\Users\\MALRY\\source\\repos\\ConsoleApplication1\\Release\\expression.txt");
	Light::Token c;
	std::string str = slurp(is);
	std::cout << str << std::endl;
	Light::string_view strview(str.c_str());
	c.ReadSTR(strview);
	Evaluate(c);
	c.Free();
	system("pause");
}