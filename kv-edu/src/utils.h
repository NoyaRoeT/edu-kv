#pragma once
#include <stdint.h>

inline bool IsLittleEndian()
{
	uint32_t n = 1;
    static bool result = (reinterpret_cast<uint8_t*>(&n)[0] == 1);
    return result;
}

inline uint32_t HostToLittleEndian(uint32_t n)
{
    if (!IsLittleEndian()) {
        return ((n & 0xFF000000) >> 24) |
            ((n & 0x00FF0000) >> 8) |
            ((n & 0x0000FF00) << 8) |
            ((n & 0x000000FF) << 24);
    }
    return n;
}

inline uint16_t HostToLittleEndian(uint16_t n)
{
    if (!IsLittleEndian()) 
    {
        return (n >> 8) | (n << 8);
    }
    return n;
}

inline uint32_t LittleEndianToHost(uint32_t n)
{
    if (IsLittleEndian()) return n;

    return ((n & 0xFF000000) >> 24) |
        ((n & 0x00FF0000) >> 8) |
        ((n & 0x0000FF00) << 8) |
        ((n & 0x000000FF) << 24);
}

inline uint16_t LittleEndianToHost(uint16_t n)
{
    if (IsLittleEndian()) return n;

    return (n >> 8) | (n << 8);
}

// Utilities
template<typename T>
T ReadTypeAt(void* src, uint32_t offset)
{
	T value;
	std::memcpy(&value, reinterpret_cast<uint8_t*>(src) + offset, sizeof(T));
	return value;
}

template<typename T>
void WriteTypeAt(void* dest, uint32_t offset, const T& value)
{
	std::memcpy(reinterpret_cast<uint8_t*>(dest) + offset, &value, sizeof(T));
}

uint16_t ReadUint16At(void* src, uint32_t offset)
{
    uint16_t value = ReadTypeAt<uint16_t>(src, offset);
    return LittleEndianToHost(value);
}

uint16_t ReadUint32At(void* src, const uint32_t offset)
{
    uint32_t value = ReadTypeAt<uint32_t>(src, offset);
    return LittleEndianToHost(value);
}

void WriteUint16At(void* dest, uint32_t offset, uint16_t value)
{
    uint16_t valEndian = HostToLittleEndian(value);
    WriteTypeAt<uint16_t>(dest, offset, valEndian);
}

void WriteUint32At(void* dest, uint32_t offset, uint32_t value)
{
    uint32_t valEndian = HostToLittleEndian(value);
    WriteTypeAt<uint16_t>(dest, offset, valEndian);
}