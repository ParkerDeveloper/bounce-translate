/*
BitStream
@bartekdvd
Feel free to use it.
*/

#ifndef BitStream_H
#define BitStream_H

#define BITS_TO_BYTES(x) (((x)+7)>>3)
#define BYTES_TO_BITS(x) ((x)<<3)
#define BITSTREAM_STACK_ALLOCATION_SIZE 256

class BitStream
{
public:
	BitStream();
	~BitStream();
	//private:
	int numberOfBitsUsed;
	int numberOfBitsAllocated;
	int readOffset;
	unsigned char *data;
	bool copyData;
	unsigned char stackData[BITSTREAM_STACK_ALLOCATION_SIZE];
};

#endif // BitStream_H
