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
	uint16_t GetFreeSpacePtr();
	uint32_t GetRightMostChild();
	std::vector<uint16_t> GetCellPtrs();

	void* dataPtr;

	// Node header format
	static const uint32_t BNODE_TYPE_SIZE = sizeof(BNodeType);
	static const uint32_t BNODE_TYPE_OFFSET = 0;
	static const uint32_t NUM_CELLS_SIZE = sizeof(uint16_t);
	static const uint32_t NUM_CELLS_OFFSET = BNODE_TYPE_SIZE;
	static const uint32_t FREE_SPACE_PTR_SIZE = sizeof(uint16_t);
	static const uint32_t FREE_SPACE_PTR_OFFSET = NUM_CELLS_OFFSET + NUM_CELLS_SIZE;
	static const uint32_t RIGHT_MOST_CHILD_SIZE = sizeof(uint32_t);
	static const uint32_t RIGHT_MOST_CHILD_OFFSET = FREE_SPACE_PTR_OFFSET + FREE_SPACE_PTR_SIZE;

	static const uint32_t CELL_PTRS_OFFSET = RIGHT_MOST_CHILD_OFFSET + RIGHT_MOST_CHILD_SIZE;
}; 