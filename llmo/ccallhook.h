#ifndef CCALLHOOK_H
#define CCALLHOOK_H

#include "cshortasm.h"
#include "memsafe.h"

enum eCodePos{
	cp_skip = 0,
	cp_before,
	cp_after
};

enum eSafeCall{
	sc_not = 0,
	sc_registers,
	sc_flags
};

enum eEntry{
	e_jmp = 0,
	e_call
};

class CCallHook
{
public:
	CCallHook(void* addr, uint size = 5, eCodePos pos = cp_after, eSafeCall save = eSafeCall(sc_registers | sc_flags), eEntry entry = e_call);
	~CCallHook();

	void setFunc(void(__stdcall*func)());
	void enable(void(__stdcall*func)());
	void enable();
	void disable();

protected:
	byte* orig_bytes;
	uint _size;
	uint hook_offset;
	void* hook_addr;
	eCodePos hook_pos;
	void(__stdcall*_func)();

	template<typename T>
	bool checkFlag(T value, T flag );

private:
	CShortAsm *_asm;

	void setNops();
	void ModOriginalBytesStart(uint offset);
	void ModOriginalBytesEnd(uint offset);
};

#endif // CCALLHOOK_H
