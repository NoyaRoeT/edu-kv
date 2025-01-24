#pragma once
#include <stdint.h>
#include <vector>

enum class BNodeType : uint8_t
{
	Internal = 0x05,
	Leaf = 0x0D
};

struct BNode
{
	BNodeType GetType();
	uint16_t GetNumCells();
	std::vector<uint16_t> GetCellOffsets();
	uint16_t GetFreeSpace();
	uint32_t GetRightMostChild();

	void* dataPtr;
}; 