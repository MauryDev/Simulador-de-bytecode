#include <Light.h>
#include <string>
#include <iostream>
#include "CPU.h"
#include <fstream>
#include <sstream>

std::string slurp(std::ifstream& in) {
	std::ostringstream sstr;
	sstr << in.rdbuf();
	return sstr.str();
}

Byte toNumber(Light::CommandResult& command)
{
	return command.ToInt();
}
CPU::Register ToRegister(Light::string_view& name)
{
	if (name == "ax")
	{
		return CPU::Register::AX;
	}
	if (name == "bx")
	{
		return CPU::Register::BX;
	}
}
void Intepreter(Light::Token& tk, CPU& cpu)
{
	auto& expression = tk.expression[0];
	auto enumerator = expression.get_Enumerator();
	Byte v = 0;
	while (enumerator.Next())
	{
		auto& commandresult = enumerator.get_Current();
		if (commandresult.resultType == Light::ResultType::Function)
		{
			auto fn = commandresult.fn;
			auto& name = *fn->name.str;
			auto& args = *fn->args.expression;
			auto argslen = args.get_Count();

			if (name == "stop")
			{
				cpu.Write(v++, 0);
				continue;
			}
			if (name == "add")
			{
				auto& args1 = args[0][0];
				auto& args2 = args[1][0];
				if (args1.resultType == Light::ResultType::Label && args2.resultType == Light::ResultType::Label)
				{
					auto reg1 = ToRegister(*args1.str);
					auto reg2 = ToRegister(*args2.str);
					if (reg1 == CPU::Register::AX && reg2 == CPU::Register::AX)
					{
						cpu.Write(v++, 4);
						continue;
					}
					if (reg1 == CPU::Register::BX && reg2 == CPU::Register::BX)
					{
						cpu.Write(v++, 6);
						continue;

					}
					if (reg1 == CPU::Register::AX && reg2 == CPU::Register::BX)
					{
						cpu.Write(v++, 3);
						continue;

					}
					if (reg1 == CPU::Register::BX && reg2 == CPU::Register::AX)
					{
						cpu.Write(v++, 5);
						continue;
					}
				}
			}
			if (name == "addi")
			{
				auto& args1 = args[0][0];
				auto& args2 = args[1][0];
				if (args1.resultType == Light::ResultType::Label && args2.resultType == Light::ResultType::Number)
				{
					auto reg1 = ToRegister(*args1.str);
					auto valueImediato = toNumber(args2);
					if (reg1 == CPU::Register::AX)
					{
						cpu.Write(v++, 1);
						cpu.Write(v++, valueImediato);
						continue;
					}
					if (reg1 == CPU::Register::BX)
					{
						cpu.Write(v++, 2);
						cpu.Write(v++, valueImediato);
						continue;
					}
				}
			}
			if (name == "sub")
			{
				auto& args1 = args[0][0];
				auto& args2 = args[1][0];
				if (args1.resultType == Light::ResultType::Label && args2.resultType == Light::ResultType::Label)
				{
					auto reg1 = ToRegister(*args1.str);
					auto reg2 = ToRegister(*args2.str);
					if (reg1 == CPU::Register::AX && reg2 == CPU::Register::AX)
					{
						cpu.Write(v++, 10);
						continue;
					}
					if (reg1 == CPU::Register::BX && reg2 == CPU::Register::BX)
					{
						cpu.Write(v++, 12);
						continue;

					}
					if (reg1 == CPU::Register::AX && reg2 == CPU::Register::BX)
					{
						cpu.Write(v++, 9);
						continue;

					}
					if (reg1 == CPU::Register::BX && reg2 == CPU::Register::AX)
					{
						cpu.Write(v++, 11);
						continue;
					}
				}
			}
			if (name == "subi")
			{
				auto& args1 = args[0][0];
				auto& args2 = args[1][0];
				if (args1.resultType == Light::ResultType::Label && args2.resultType == Light::ResultType::Number)
				{
					auto reg1 = ToRegister(*args1.str);
					auto valueImediato = toNumber(args2);
					if (reg1 == CPU::Register::AX)
					{
						cpu.Write(v++, 7);
						cpu.Write(v++, valueImediato);
						continue;
					}
					if (reg1 == CPU::Register::BX)
					{
						cpu.Write(v++, 8);
						cpu.Write(v++, valueImediato);
						continue;
					}
				}
			}

			if (name == "mul")
			{
				auto& args1 = args[0][0];
				auto& args2 = args[1][0];
				if (args1.resultType == Light::ResultType::Label && args2.resultType == Light::ResultType::Label)
				{
					auto reg1 = ToRegister(*args1.str);
					auto reg2 = ToRegister(*args2.str);
					if (reg1 == CPU::Register::AX && reg2 == CPU::Register::AX)
					{
						cpu.Write(v++, 16);
						continue;
					}
					if (reg1 == CPU::Register::BX && reg2 == CPU::Register::BX)
					{
						cpu.Write(v++, 18);
						continue;

					}
					if (reg1 == CPU::Register::AX && reg2 == CPU::Register::BX)
					{
						cpu.Write(v++, 15);
						continue;

					}
					if (reg1 == CPU::Register::BX && reg2 == CPU::Register::AX)
					{
						cpu.Write(v++, 17);
						continue;
					}
				}
			}
			if (name == "muli")
			{
				auto& args1 = args[0][0];
				auto& args2 = args[1][0];
				if (args1.resultType == Light::ResultType::Label && args2.resultType == Light::ResultType::Number)
				{
					auto reg1 = ToRegister(*args1.str);
					auto valueImediato = toNumber(args2);
					if (reg1 == CPU::Register::AX)
					{
						cpu.Write(v++, 13);
						cpu.Write(v++, valueImediato);
						continue;
					}
					if (reg1 == CPU::Register::BX)
					{
						cpu.Write(v++, 14);
						cpu.Write(v++, valueImediato);
						continue;
					}
				}
			}

			if (name == "div")
			{
				auto& args1 = args[0][0];
				auto& args2 = args[1][0];
				if (args1.resultType == Light::ResultType::Label && args2.resultType == Light::ResultType::Label)
				{
					auto reg1 = ToRegister(*args1.str);
					auto reg2 = ToRegister(*args2.str);
					if (reg1 == CPU::Register::AX && reg2 == CPU::Register::AX)
					{
						cpu.Write(v++, 22);
						continue;
					}
					if (reg1 == CPU::Register::BX && reg2 == CPU::Register::BX)
					{
						cpu.Write(v++, 24);
						continue;

					}
					if (reg1 == CPU::Register::AX && reg2 == CPU::Register::BX)
					{
						cpu.Write(v++, 21);
						continue;

					}
					if (reg1 == CPU::Register::BX && reg2 == CPU::Register::AX)
					{
						cpu.Write(v++, 23);
						continue;
					}
				}
			}
			if (name == "divi")
			{
				auto& args1 = args[0][0];
				auto& args2 = args[1][0];
				if (args1.resultType == Light::ResultType::Label && args2.resultType == Light::ResultType::Number)
				{
					auto reg1 = ToRegister(*args1.str);
					auto valueImediato = toNumber(args2);
					if (reg1 == CPU::Register::AX)
					{
						cpu.Write(v++, 19);
						cpu.Write(v++, valueImediato);
						continue;
					}
					if (reg1 == CPU::Register::BX)
					{
						cpu.Write(v++, 20);
						cpu.Write(v++, valueImediato);
						continue;
					}
				}
			}

			if (name == "inc")
			{
				auto& args1 = args[0][0];
				if (args1.resultType == Light::ResultType::Label)
				{
					auto reg1 = ToRegister(*args1.str);
					if (reg1 == CPU::Register::AX)
					{
						cpu.Write(v++, 25);
						continue;
					}
					if (reg1 == CPU::Register::BX)
					{
						cpu.Write(v++, 26);
						continue;
					}
				}
			}
			if (name == "dec")
			{
				auto& args1 = args[0][0];
				if (args1.resultType == Light::ResultType::Label)
				{
					auto reg1 = ToRegister(*args1.str);
					if (reg1 == CPU::Register::AX)
					{
						cpu.Write(v++, 27);
						continue;
					}
					if (reg1 == CPU::Register::BX)
					{
						cpu.Write(v++, 28);
						continue;
					}
				}
			}

			if (name == "store")
			{
				auto& args1 = args[0][0];
				auto& args2 = args[1][0];
				if (args1.resultType == Light::ResultType::Label)
				{
					auto type2 = args2.resultType;
					auto reg1 = ToRegister(*args1.str);

					if (type2 == Light::ResultType::Number)
					{
						auto valueImediato = toNumber(args2);
						if (reg1 == CPU::Register::AX)
						{
							cpu.Write(v++, 29);
							cpu.Write(v++, valueImediato);
							continue;
						}
						if (reg1 == CPU::Register::BX)
						{
							cpu.Write(v++, 30);
							cpu.Write(v++, valueImediato);
							continue;
						}
					}
					if (type2 == Light::ResultType::Label)
					{
						auto reg2 = ToRegister(*args2.str);
						if (reg1 == CPU::Register::AX && reg2 == CPU::Register::AX)
						{
							cpu.Write(v++, 31);
							continue;
						}
						if (reg1 == CPU::Register::BX && reg2 == CPU::Register::BX)
						{
							cpu.Write(v++, 34);
							continue;

						}
						if (reg1 == CPU::Register::AX && reg2 == CPU::Register::BX)
						{
							cpu.Write(v++, 33);
							continue;

						}
						if (reg1 == CPU::Register::BX && reg2 == CPU::Register::AX)
						{
							cpu.Write(v++, 32);
							continue;
						}
					}
				}
			}

			if (name == "load")
			{
				auto& args1 = args[0][0];
				auto& args2 = args[1][0];
				if (args1.resultType == Light::ResultType::Label)
				{
					auto type2 = args2.resultType;
					auto reg1 = ToRegister(*args1.str);

					if (type2 == Light::ResultType::Number)
					{
						auto valueImediato = toNumber(args2);
						if (reg1 == CPU::Register::AX)
						{
							cpu.Write(v++, 35);
							cpu.Write(v++, valueImediato);
							continue;
						}
						if (reg1 == CPU::Register::BX)
						{
							cpu.Write(v++, 36);
							cpu.Write(v++, valueImediato);
							continue;
						}
					}
					if (type2 == Light::ResultType::Label)
					{
						auto reg2 = ToRegister(*args2.str);
						if (reg1 == CPU::Register::AX && reg2 == CPU::Register::AX)
						{
							cpu.Write(v++, 37);
							continue;
						}
						if (reg1 == CPU::Register::BX && reg2 == CPU::Register::BX)
						{
							cpu.Write(v++, 40);
							continue;

						}
						if (reg1 == CPU::Register::AX && reg2 == CPU::Register::BX)
						{
							cpu.Write(v++, 39);
							continue;

						}
						if (reg1 == CPU::Register::BX && reg2 == CPU::Register::AX)
						{
							cpu.Write(v++, 38);
							continue;
						}
					}
				}
			}

			if (name == "mov")
			{
				auto& args1 = args[0][0];
				auto& args2 = args[1][0];
				if (args1.resultType == Light::ResultType::Label && args2.resultType == Light::ResultType::Label)
				{
					auto reg1 = ToRegister(*args1.str);
					auto reg2 = ToRegister(*args2.str);
					if (reg1 == CPU::Register::AX && reg2 == CPU::Register::BX)
					{
						cpu.Write(v++, 43);
						continue;

					}
					if (reg1 == CPU::Register::BX && reg2 == CPU::Register::AX)
					{
						cpu.Write(v++, 44);
						continue;
					}
				}
			}
			if (name == "movi")
			{
				auto& args1 = args[0][0];
				auto& args2 = args[1][0];
				if (args1.resultType == Light::ResultType::Label && args2.resultType == Light::ResultType::Number)
				{
					auto reg1 = ToRegister(*args1.str);
					auto valueImediato = toNumber(args2);
					if (reg1 == CPU::Register::AX)
					{
						cpu.Write(v++, 41);
						cpu.Write(v++, valueImediato);
						continue;
					}
					if (reg1 == CPU::Register::BX)
					{
						cpu.Write(v++, 42);
						cpu.Write(v++, valueImediato);
						continue;
					}
				}
			}
			if (name == "jmp")
			{
				auto& args1 = args[0][0];
				auto type1 = args1.resultType;
				if (type1 == Light::ResultType::Label)
				{
					auto reg1 = ToRegister(*args1.str);
					if (reg1 == CPU::Register::AX)
					{
						cpu.Write(v++, 46);
						continue;
					}
					if (reg1 == CPU::Register::BX)
					{
						cpu.Write(v++, 47);
						continue;
					}
				}
				if (type1 == Light::ResultType::Number)
				{
					auto imediato = toNumber(args1);
					cpu.Write(v++, 45);
					cpu.Write(v++, imediato);
					continue;
				}
			}
			if (name == "nop")
			{
				cpu.Write(v++, 48);
			}


		}
	}
}


void Clock(CPU* that)
{
	std::cout << "clock" << std::endl;
}
int main()
{
	std::ifstream is("C:\\Users\\MALRY\\source\\repos\\ConsoleApplication1\\AtividadeIFBA\\Assembly.txt");

	CPU cpu_simulate;
	Light::Token tk;
	std::string str = slurp(is);
	Light::string_view strview(str.c_str());
	tk.ReadSTR(strview);
	Intepreter(tk, cpu_simulate);

	cpu_simulate.Run(Clock);
}