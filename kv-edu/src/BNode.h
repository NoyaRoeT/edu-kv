#pragma once
#include <stdint.h>
#include <vector>
#include <string>

enum class BNodeType : uint8_t
{
	Internal = 0x05,
	Leaf = 0x0D
};

struct BNode
{
	// Getters
	BNodeType GetType();
	uint16_t GetNumCells();
	uint16_t GetFreeSpacePtr();
	uint32_t GetRightMostChild();
	uint16_t GetCellOffset(size_t idx);

	std::pair<std::string, std::string> GetCell(size_t idx);
	uint16_t GetKeyLen(uint16_t cellOffset);
	uint16_t GetValueLen(uint16_t cellOffset);

	// Setters
	void SetType(BNodeType type);
	void SetNumCells(uint16_t numCells);
	void SetFreeSpacePtr(uint16_t ptr);
	void SetRightMostChild(uint32_t offset);
	void SetCellOffset(size_t idx, uint16_t value);

	// Lookup

	
	void* dataPtr;

	// Constants
	static const uint32_t BNODE_TYPE_SIZE = sizeof(BNodeType);
	static const uint32_t BNODE_TYPE_OFFSET = 0;
	static const uint32_t NUM_CELLS_SIZE = sizeof(uint16_t);
	static const uint32_t NUM_CELLS_OFFSET = BNODE_TYPE_SIZE;
	static const uint32_t FREE_SPACE_PTR_SIZE = sizeof(uint16_t);
	static const uint32_t FREE_SPACE_PTR_OFFSET = NUM_CELLS_OFFSET + NUM_CELLS_SIZE;
	static const uint32_t RIGHT_MOST_CHILD_SIZE = sizeof(uint32_t);
	static const uint32_t RIGHT_MOST_CHILD_OFFSET = FREE_SPACE_PTR_OFFSET + FREE_SPACE_PTR_SIZE;
	static const uint32_t HEADER_SIZE = BNODE_TYPE_SIZE + NUM_CELLS_SIZE + FREE_SPACE_PTR_SIZE + RIGHT_MOST_CHILD_SIZE;

	static const uint32_t CELL_PTR_SIZE = sizeof(uint16_t);
	static const uint32_t CELL_PTRS_OFFSET = HEADER_SIZE;

	static const uint32_t KEY_LEN_SIZE = sizeof(uint16_t);
	static const uint32_t VAL_LEN_SIZE = sizeof(uint16_t);
	static const uint32_t KEY_OFFSET = KEY_LEN_SIZE + VAL_LEN_SIZE;

	static const uint32_t PAGE_SIZE = 4096;
	static const uint32_t MAX_KEY_SIZE = 256;
	static const uint32_t MAX_VALUE_SIZE = 256;
}; 