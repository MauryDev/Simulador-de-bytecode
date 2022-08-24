#pragma once

typedef unsigned char Byte;
class CPU
{
public:
	enum class Register
	{
		None,
		IR,
		PC,
		AX,
		BX,
		R1,
		R2,
		R3,
		R4
	};
	typedef void (*CPUClock) (CPU* that);
	CPU();
	void Run(CPUClock clock);
	void Write(Byte pos, Byte value);
	void Write(Byte pos, Byte* buff, Byte size);
	// ES
	Byte R1, R2, R3, R4;
private:

	// UC
	void Decoder();
	void Execute();
	// RAM
	Byte* Memory;
	// Registradores
	Byte IR;
	Byte PC;
	Byte AX, BX;
	bool EXIT;
};

