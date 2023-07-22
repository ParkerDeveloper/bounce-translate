#ifndef CSHORTASM_H
#define CSHORTASM_H

#include <QString>
#include <QMap>
#include "sys/mman.h"

#define CALLHOOK void __stdcall

typedef unsigned char byte;

typedef enum r86{
	EAX = 0,
	ECX,
	EDX,
	EBX,
	ESP,
	EBP,
	ESI,
	EDI
} r86;

template <typename T>
union byteValue{
	T value;
	byte bytes[sizeof( T )];
};

class CShortAsm
{
public:
	CShortAsm(uint pages = 1);
	~CShortAsm();

	void insert(byte* array, uint size);
	void insert(QByteArray array);
	void push(byte value);
	void push(int value);
	void push(r86 r);
	void pushad();
	void pushfd();
	void pop(r86 r);
	void popad();
	void popfd();
	void label(QString label);
	void jmp(int addr);
	void jmp(QString label);
	void jmp(r86 r);
	void ret(int pops = 0);
	void nop();
	void call(int addr);
	void call(QString label);
	void call(r86 r);
	void mov(int &var, r86 r); // mov var, EAX
	void mov(r86 r, int &var); // mov EAX, var
	void mov(r86 r, const int value); // mov EAX, value
	void mov(r86 r1, r86 r2, byte offset); // mov EAX, [EAX + 4]
	void mov(r86 r1, byte offset, r86 r2); // mov [EAX + 4], EAX
	void xchg(r86 r1, r86 r2, byte offset = 0); // swap registers
	void xchg(r86 r, int &var);
	void add(r86 r, byte value);
	void add(r86 r, const int value);
	void add(r86 r, int &var);
	void sub(r86 r, byte value);
	void sub(r86 r, const int value);
	void sub(r86 r, int &var);
	void mul(r86 r);
	void imul(r86 r);
	void imul(r86 r1, r86 r2);
	void imul(r86 r, byte value);
	void imul(r86 r, const int value);
	void imul(r86 r1, r86 r2, byte value);
	void imul(r86 r1, r86 r2, const int value);
	void div(r86 r);
	void idiv(r86 r);
	void cmp(r86 r1, r86 r2);
	void cmp(r86 r, byte value);
	void cmp(r86 r, const int value);
	void XOR(r86 r1, r86 r2);
	void XOR(r86 r, byte value);
	void XOR(r86 r, const int value);
	void je(const int addr);
	void je(QString label);
	void jne(const int addr);
	void jne(QString label);
	void jl(const int addr);
	void jl(QString label);
	void jle(const int addr);
	void jle(QString label);
	void jg(const int addr);
	void jg(QString label);
	void jge(const int addr);
	void jge(QString label);
	void jb(const int addr);
	void jb(QString label);
	void jbe(const int addr);
	void jbe(QString label);
	void ja(const int addr);
	void ja(QString label);
	void jae(const int addr);
	void jae(QString label);

	void resetWriteOffset();
	uint getWriteOffset();
	void setWriteOffset(uint offset);

	const byte* getAddr();
	uint getSize();

	static uint arrayToPages(size_t size_array);
	static const uint PAGE_SIZE = 4096;

protected:
	void resize(uint pages);
	uint getRelativeAddress(uint addr);
	void write(byte v);

	byte* _code = nullptr;
	uint _size = 0;

private:
	uint _offset = 0;
	uint _peak = 0;
	QMap<QString, uint> _labels;
	QMap<QString, uint> _jmps;
	QMap<QString, uint> _jes;
	QMap<QString, uint> _jnes;
	QMap<QString, uint> _jls;
	QMap<QString, uint> _jles;
	QMap<QString, uint> _jgs;
	QMap<QString, uint> _jges;
	QMap<QString, uint> _jbs;
	QMap<QString, uint> _jbes;
	QMap<QString, uint> _jas;
	QMap<QString, uint> _jaes;
};

#endif // CSHORTASM_H
