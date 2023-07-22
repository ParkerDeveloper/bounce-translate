#include "ccallhook.h"

CCallHook::CCallHook(void *addr, uint size, eCodePos pos, eSafeCall save, eEntry entry)
{
	hook_addr = addr;
	_size = size;
	hook_pos = pos;
	_asm = new CShortAsm();
	_func = nullptr;

	orig_bytes = new byte[size + 1];
	memsafe::copy(orig_bytes, addr, size);

	if (pos == cp_before){
		if (orig_bytes[0] == 0xE9)
			pos = cp_after;
		else{
			ModOriginalBytesStart(reinterpret_cast<uint>(_asm->getAddr()) + _asm->getWriteOffset());
			_asm->insert(orig_bytes, size);
		}
	}
	if (checkFlag(save, sc_registers))
		_asm->pushad();
	if (checkFlag(save, sc_flags))
		_asm->pushfd();

	hook_offset = _asm->getWriteOffset();
	if (pos == cp_skip)
		ModOriginalBytesStart(reinterpret_cast<uint>(_asm->getAddr()) + _asm->getWriteOffset());
	disable();

	if (checkFlag(save, sc_flags))
		_asm->popfd();
	if (checkFlag(save, sc_registers))
		_asm->popad();
	if (pos == cp_after){
		ModOriginalBytesStart(reinterpret_cast<uint>(_asm->getAddr()) + _asm->getWriteOffset());
		_asm->insert(orig_bytes, size);
	}

	if (entry == e_call)
		_asm->ret();
	else _asm->jmp(reinterpret_cast<int>(addr) + static_cast<int>(size));

	memsafe::set(addr, 0x90, size);
	byteValue<uint> v;
	v.value = reinterpret_cast<uint>(_asm->getAddr()) - (reinterpret_cast<uint>(addr) + 5);
	if (entry == e_call)
		memsafe::set(addr, 0xE8, 1);
	else memsafe::set(addr, 0xE9, 1);
	memsafe::set(reinterpret_cast<void*>(reinterpret_cast<uint>(addr) + 1), v.bytes[0], 1);
	memsafe::set(reinterpret_cast<void*>(reinterpret_cast<uint>(addr) + 2), v.bytes[1], 1);
	memsafe::set(reinterpret_cast<void*>(reinterpret_cast<uint>(addr) + 3), v.bytes[2], 1);
	memsafe::set(reinterpret_cast<void*>(reinterpret_cast<uint>(addr) + 4), v.bytes[3], 1);
}

CCallHook::~CCallHook()
{
	disable();
	//delete _asm;
}

void CCallHook::setFunc(void(__stdcall*func)())
{
	_func = func;
}

void CCallHook::enable(void(__stdcall*func)())
{
	setNops();
	if (func == nullptr){
		if (hook_pos == cp_skip){
			_asm->setWriteOffset(hook_offset);
			_asm->insert(orig_bytes, _size);
		}
		return;
	}
	_asm->setWriteOffset(hook_offset);
	_asm->call(reinterpret_cast<int>(func));
	_func = func;
}

void CCallHook::enable()
{
	return enable(_func);
}

void CCallHook::disable()
{
	_asm->setWriteOffset(hook_offset);
	if (hook_pos == cp_skip)
		_asm->insert(orig_bytes, _size);
	else setNops();
}

template<typename T> inline
bool CCallHook::checkFlag(T value, T flag )
{
	return (value & flag);
}

void CCallHook::setNops()
{
	_asm->setWriteOffset(hook_offset);
	for (int i = 0; i < /*static_cast<int>(_size)*/5; ++i)
		_asm->nop();
}

void CCallHook::ModOriginalBytesStart(uint offset)
{
	// call and jmp (long)
	if (orig_bytes[0] == 0xE9 || orig_bytes[0] == 0xE8){
		byteValue<uint> v;
		v.bytes[0] = orig_bytes[1];
		v.bytes[1] = orig_bytes[2];
		v.bytes[2] = orig_bytes[3];
		v.bytes[3] = orig_bytes[4];
		uint o_addr = v.value + (reinterpret_cast<uint>(hook_addr) + 5);
		v.value = o_addr - (offset + 5);
		orig_bytes[1] = v.bytes[0];
		orig_bytes[2] = v.bytes[1];
		orig_bytes[3] = v.bytes[2];
		orig_bytes[4] = v.bytes[3];
	}
	// conditionals jmp's (long)
	else if (orig_bytes[0] == 0x0F) {
		if (orig_bytes[1] >= 0x81 && orig_bytes[1] <= 0x8F){
			byteValue<uint> v;
			v.bytes[0] = orig_bytes[2];
			v.bytes[1] = orig_bytes[3];
			v.bytes[2] = orig_bytes[4];
			v.bytes[3] = orig_bytes[5];
			uint o_addr = v.value + (reinterpret_cast<uint>(hook_addr) + 6);
			v.value = o_addr - (offset + 6);
			orig_bytes[2] = v.bytes[0];
			orig_bytes[3] = v.bytes[1];
			orig_bytes[4] = v.bytes[2];
			orig_bytes[5] = v.bytes[3];
		}
	}
}

void CCallHook::ModOriginalBytesEnd(uint offset)
{
	// call and jmp (long)
	if (orig_bytes[_size - 5] == 0xE9 || orig_bytes[_size - 5] == 0xE8){
		byteValue<uint> v;
		v.bytes[0] = orig_bytes[_size - 4];
		v.bytes[1] = orig_bytes[_size - 3];
		v.bytes[2] = orig_bytes[_size - 2];
		v.bytes[3] = orig_bytes[_size - 1];
		uint o_addr = v.value + (reinterpret_cast<uint>(hook_addr) + 5);
		v.value = offset - (o_addr + 5);
		orig_bytes[_size - 4] = v.bytes[0];
		orig_bytes[_size - 3] = v.bytes[1];
		orig_bytes[_size - 2] = v.bytes[2];
		orig_bytes[_size - 1] = v.bytes[3];
	}
	// conditionals jmp's (long)
	else if (orig_bytes[_size - 6] == 0x0F) {
		if (orig_bytes[_size - 5] >= 0x81 && orig_bytes[_size - 5] <= 0x8F){
			byteValue<uint> v;
			v.bytes[0] = orig_bytes[_size - 4];
			v.bytes[1] = orig_bytes[_size - 3];
			v.bytes[2] = orig_bytes[_size - 2];
			v.bytes[3] = orig_bytes[_size - 1];
			uint o_addr = v.value + (reinterpret_cast<uint>(hook_addr) + 6);
			v.value = offset - (o_addr + 6);
			orig_bytes[_size - 4] = v.bytes[0];
			orig_bytes[_size - 3] = v.bytes[1];
			orig_bytes[_size - 2] = v.bytes[2];
			orig_bytes[_size - 1] = v.bytes[3];
		}
	}
}
