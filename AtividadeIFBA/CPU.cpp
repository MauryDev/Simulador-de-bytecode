#include "CPU.h"

CPU::CPU()
{
	
	Memory = new Byte[256];
	PC = IR = 0;
	EXIT = false;
	BX = AX = 0;
}

void CPU::Run(CPUClock cpulock)
{
	while (!EXIT)
	{
		Decoder();
		cpulock(this);
	}
}

void CPU::Write(Byte pos, Byte value)
{
	Memory[pos] = value;
}

void CPU::Write(Byte pos, Byte* buff, Byte size)
{
	for (size_t i = 0; i < size; i++)
	{
		Write(pos + i, buff[i]);
	}
}

void CPU::Decoder()
{
	IR = Memory[PC];
	Execute();
}

void CPU::Execute()
{
#pragma region Stop
	if (IR == 0)
	{
		EXIT = true;
		++PC;
		return;
	}
#pragma endregion
#pragma region Add
	if (IR == 1)
	{
		AX = AX + Memory[PC + 1];
		PC += 2;
		return;
	}
	if (IR == 2)
	{
		BX = BX + Memory[PC + 1];
		PC += 2;
		return;
	}
	if (IR == 3)
	{
		AX = AX + BX;
		PC += 1;
		return;
	}
	if (IR == 4)
	{
		AX = AX + AX;
		PC += 1;
		return;
	}
	if (IR == 5)
	{
		BX = BX + AX;
		PC += 1;
		return;
	}
	if (IR == 6)
	{
		BX = BX + BX;
		PC += 1;
		return;
	}
#pragma endregion
#pragma region Sub
	if (IR == 7)
	{
		AX = AX - Memory[PC + 1];
		PC += 2;
		return;
	}
	if (IR == 8)
	{
		BX = BX - Memory[PC + 1];
		PC += 2;
		return;
	}
	if (IR == 9)
	{
		AX = AX - BX;
		PC += 1;
		return;
	}
	if (IR == 10)
	{
		AX = AX - AX;
		PC += 1;
		return;
	}
	if (IR == 11)
	{
		BX = BX - AX;
		PC += 1;
		return;
	}
	if (IR == 12)
	{
		BX = BX - BX;
		PC += 1;
		return;
	}
#pragma endregion
#pragma region Mul
	if (IR == 13)
	{
		AX = AX * Memory[PC + 1];
		PC += 2;
		return;
	}
	if (IR == 14)
	{
		BX = BX * Memory[PC + 1];
		PC += 2;
		return;
	}
	if (IR == 15)
	{
		AX = AX * BX;
		PC += 1;
		return;
	}
	if (IR == 16)
	{
		AX = AX * AX;
		PC += 1;
		return;
	}
	if (IR == 17)
	{
		BX = BX * AX;
		PC += 1;
		return;
	}
	if (IR == 18)
	{
		BX = BX * BX;
		PC += 1;
		return;
	}
#pragma endregion
#pragma region Div
	if (IR == 19)
	{
		AX = AX / Memory[PC + 1];
		PC += 2;
		return;
	}
	if (IR == 20)
	{
		BX = BX / Memory[PC + 1];
		PC += 2;
		return;
	}
	if (IR == 21)
	{
		AX = AX / BX;
		PC += 1;
		return;
	}
	if (IR == 22)
	{
		AX = AX / AX;
		PC += 1;
		return;
	}
	if (IR == 23)
	{
		BX = BX / AX;
		PC += 1;
		return;
	}
	if (IR == 24)
	{
		BX = BX / BX;
		PC += 1;
		return;
	}
#pragma endregion
#pragma region INC
	if (IR == 25)
	{
		AX = AX + 1;
		PC += 1;
		return;
	}
	if (IR == 26)
	{
		BX = BX + 1;
		PC += 2;
		return;
	}
#pragma endregion
#pragma region DEC
	if (IR == 27)
	{
		AX = AX - 1;
		PC += 1;
		return;
	}
	if (IR == 28)
	{
		BX = BX - 1;
		PC += 2;
		return;
	}
#pragma endregion
#pragma region Store
	if (IR == 29)
	{
		auto op1 = Memory[PC + 1];
		Memory[op1] = AX;
		PC += 2;
		return;
	}
	if (IR == 30)
	{
		auto op1 = Memory[PC + 1];
		Memory[op1] = BX;
		PC += 2;
		return;
	}
	if (IR == 31)
	{
		auto op1 = Memory[AX];
		Memory[op1] = AX;
		PC += 1;
		return;
	}
	if (IR == 32)
	{
		auto op1 = Memory[AX];
		Memory[op1] = BX;
		PC += 1;
		return;
	}
	if (IR == 33)
	{
		auto op1 = Memory[BX];
		Memory[op1] = AX;
		PC += 1;
		return;
	}
	if (IR == 34)
	{
		auto op1 = Memory[BX];
		Memory[op1] = BX;
		PC += 1;
		return;
	}
#pragma endregion
#pragma region Load
	if (IR == 35)
	{
		auto op1 = Memory[PC + 1];
		AX = Memory[op1];
		PC += 2;
		return;
	}
	if (IR == 36)
	{
		auto op1 = Memory[PC + 1];
		BX = Memory[op1];
		PC += 2;
		return;
	}
	if (IR == 37)
	{
		auto op1 = Memory[AX];
		AX = Memory[op1];
		PC += 1;
		return;
	}
	if (IR == 38)
	{
		auto op1 = Memory[AX];
		BX = Memory[op1];
		PC += 1;
		return;
	}
	if (IR == 39)
	{
		auto op1 = Memory[BX];
		AX = Memory[op1];
		PC += 1;
		return;
	}
	if (IR == 40)
	{
		auto op1 = Memory[BX];
		BX = Memory[op1];
		PC += 1;
		return;
	}
#pragma endregion
#pragma region Mov
	if (IR == 41)
	{
		AX = Memory[PC + 1];
		PC += 2;
		return;
	}
	if (IR == 42)
	{
		BX = Memory[PC + 1];
		PC += 2;
		return;
	}
	if (IR == 43)
	{
		AX = BX;
		PC += 1;
		return;
	}
	if (IR == 44)
	{
		BX = AX;
		PC += 1;
		return;
	}
#pragma endregion
#pragma region JMP
	if (IR == 45)
	{
		PC += Memory[PC + 1] + 2;
		return;
	}
	if (IR == 46)
	{
		PC = AX;
		return;
	}
	if (IR == 47)
	{
		PC = BX;
		return;
	}
#pragma endregion
#pragma region NOP
	if (IR == 48)
	{
		PC += 1;
		return;
	}
#pragma endregion
#pragma region OUT
	if (IR == 49)
	{
		R1 = AX;
		PC += 1;
		return;
	}
	if (IR == 50)
	{
		R2 = AX;
		PC += 1;
		return;
	}
	if (IR == 51)
	{
		R3 = AX;
		PC += 1;
		return;
	}
	if (IR == 52)
	{
		R4 = AX;
		PC += 1;
		return;
	}

#pragma endregion
#pragma region INP
	if (IR == 53)
	{
		AX = R1;
		PC += 1;
		return;
	}
	if (IR == 54)
	{
		AX = R2;
		PC += 1;
		return;
	}
	if (IR == 55)
	{
		AX = R3;
		PC += 1;
		return;
	}
	if (IR == 56)
	{
		AX = R4;
		PC += 1;
		return;
	}
#pragma endregion
}

