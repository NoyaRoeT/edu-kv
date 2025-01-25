#include "BNode.h"
#include <stdexcept>

BNodeType BNode::GetType()
{
	return static_cast<BNodeType>(*reinterpret_cast<uint8_t*>(dataPtr));
}

uint16_t BNode::GetNumCells()
{
	return *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(dataPtr) + NUM_CELLS_OFFSET);
}

uint16_t BNode::GetFreeSpacePtr()
{
	return *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(dataPtr) + FREE_SPACE_PTR_OFFSET);
}

uint32_t BNode::GetRightMostChild()
{
	if (GetType() != BNodeType::Internal)
	{
		throw std::runtime_error("Leaf node does not have a RightMostChild");
	}

	return *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(dataPtr) + RIGHT_MOST_CHILD_OFFSET);
}

std::vector<uint16_t> BNode::GetCellPtrs()
{
	size_t numCells = GetNumCells();

	std::vector<uint16_t> cellPtrs;
	cellPtrs.reserve(numCells);

	uint16_t* ptr = reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(dataPtr) + CELL_PTRS_OFFSET);
	for (size_t i = 0; i != numCells; ++i)
	{
		cellPtrs.push_back(*ptr);
		++ptr;
	}

	return cellPtrs;
}