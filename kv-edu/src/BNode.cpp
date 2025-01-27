#include "BNode.h"
#include <stdexcept>

BNodeType BNode::GetType()
{
    return ReadTypeAt<BNodeType>(BNODE_TYPE_OFFSET);
}

uint16_t BNode::GetNumCells()
{
    return ReadTypeAt<uint16_t>(NUM_CELLS_OFFSET);
}

uint16_t BNode::GetFreeSpacePtr()
{
    return ReadTypeAt<uint16_t>(FREE_SPACE_PTR_OFFSET);
}

uint32_t BNode::GetRightMostChild()
{
    if (GetType() != BNodeType::Internal)
    {
        throw std::runtime_error("Leaf node does not have a RightMostChild");
    }

    return ReadTypeAt<uint32_t>(RIGHT_MOST_CHILD_OFFSET);
}

uint16_t BNode::GetCellOffset(size_t idx)
{
    return ReadTypeAt<uint16_t>(CELL_PTRS_OFFSET + idx * CELL_PTR_SIZE);
}

void BNode::SetType(BNodeType type)
{
    WriteTypeAt(BNODE_TYPE_OFFSET, type);
}

void BNode::SetNumCells(uint16_t numCells)
{
    WriteTypeAt(NUM_CELLS_OFFSET, numCells);
}

void BNode::SetFreeSpacePtr(uint16_t ptr)
{
    WriteTypeAt(FREE_SPACE_PTR_OFFSET, ptr);
}

void BNode::SetRightMostChild(uint32_t value)
{
    WriteTypeAt(RIGHT_MOST_CHILD_OFFSET, value);
}

void BNode::SetCellOffset(size_t idx, uint16_t value)
{
    uint32_t offset = CELL_PTRS_OFFSET + idx * CELL_PTR_SIZE;
    WriteTypeAt<uint16_t>(offset, value);
}