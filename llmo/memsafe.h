#ifndef MEMSAFE_H
#define MEMSAFE_H

#include <stdint.h>
#include <windows.h>

namespace memsafe
{
	void *copy(void *dest, const void *src, size_t stLen);
	int compare(const void *_s1, const void *_s2, uint32_t len);
	int set(void *_dest, int c, DWORD len);

	void Unprotect(DWORD address, size_t size);

	template<typename T> void write(void* address, T value){
		DWORD oldVP;
		size_t len = sizeof(T);

		VirtualProtect((void*)address, len, PAGE_EXECUTE_READWRITE, &oldVP);
		*(T*)address = value;
		VirtualProtect((void*)address, len, oldVP, nullptr);
	}
	template<typename T> T read(void* address){
		DWORD oldVP;
		size_t len = sizeof(T);

		VirtualProtect((void*)address, len, PAGE_EXECUTE_READWRITE, &oldVP);
		T value = *(T*)address;
		VirtualProtect((void*)address, len, oldVP, nullptr);

		return value;
	}
};

#endif // MEMSAFE_H
