#pragma once
#include <stdint.h>
#include <vector>
#include <stdexcept>

enum class BNodeType : uint8_t
{
	Internal = 0x05,
	Leaf = 0x0D
};

class BNode
{
public:
	// Getters
	BNodeType GetType();
	uint16_t GetNumCells();
	uint16_t GetFreeSpacePtr();
	uint32_t GetRightMostChild();
	uint16_t GetCellOffset(size_t idx);

	// Setters
	void SetType(BNodeType type);
	void SetNumCells(uint16_t numCells);
	void SetFreeSpacePtr(uint16_t ptr);
	void SetRightMostChild(uint32_t offset);
	void SetCellOffset(size_t idx, uint16_t value);

	void* dataPtr; // Move to private after testing
	static const uint32_t PAGE_SIZE = 4096;

private:

	// Utilities
	template<typename T>
	T ReadTypeAt(uint32_t offset) const
	{
		if (offset >= PAGE_SIZE)
		{
			throw std::runtime_error("Cannot read beyond page limits, tried to read offset=" + offset);
		}

		T value;
		std::memcpy(&value, reinterpret_cast<uint8_t*>(dataPtr) + offset, sizeof(T));
		return value;
	}

	template<typename T>
	void WriteTypeAt(uint32_t offset, const T& value)
	{
		if (offset >= PAGE_SIZE)
		{
			throw std::runtime_error("Cannot write beyond page limits, tried to write offset=" + offset);
		}
		std::memcpy(reinterpret_cast<uint8_t*>(dataPtr) + offset, &value, sizeof(T));
	}

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
}; 