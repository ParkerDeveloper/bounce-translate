/*
BitStream
@bartekdvd
Feel free to use it
*/

#include "../loader.h"
#include "BitStream.h"

BitStream::BitStream()
{
	numberOfBitsUsed = 0;
	numberOfBitsAllocated = BITSTREAM_STACK_ALLOCATION_SIZE * 8;
	readOffset = 0;
	data = ( unsigned char* ) stackData;
	copyData = true;
}

BitStream::~BitStream()
{
	if (copyData) free(data);
}
