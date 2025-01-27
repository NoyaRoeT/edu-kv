#pragma once
#include <stdint.h>

bool IsLittleEndian()
{
	uint32_t n = 1;
	return (*(reinterpret_cast<uint8_t*>(&n)) == 1);
}

uint32_t HostToLittleEndian(uint32_t n)
{
    if (!IsLittleEndian()) {
        return ((n & 0xFF000000) >> 24) |
            ((n & 0x00FF0000) >> 8) |
            ((n & 0x0000FF00) << 8) |
            ((n & 0x000000FF) << 24);
    }
    return n;
}

uint16_t HostToLittleEndian(uint16_t n)
{
    if (!IsLittleEndian()) 
    {
        return (n >> 8) | (n << 8);
    }
    return n;
}

uint32_t LittleEndianToHost(uint32_t n)
{
    if (IsLittleEndian()) return n;

    return ((n & 0xFF000000) >> 24) |
        ((n & 0x00FF0000) >> 8) |
        ((n & 0x0000FF00) << 8) |
        ((n & 0x000000FF) << 24);
}

uint16_t LittleEndianToHost(uint16_t n)
{
    if (IsLittleEndian()) return n;

    return (n >> 8) | (n << 8);
}