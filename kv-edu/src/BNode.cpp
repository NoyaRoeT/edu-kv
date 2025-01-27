#include <stdexcept>
#include "BNode.h"
#include "utils.h"

BNodeType BNode::GetType()
{
    return ReadTypeAt<BNodeType>(dataPtr, BNODE_TYPE_OFFSET);
}

uint16_t BNode::GetNumCells()
{
    return ReadUint16At(dataPtr, NUM_CELLS_OFFSET);
}

uint16_t BNode::GetFreeSpacePtr()
{
    return ReadTypeAt<uint16_t>(dataPtr, FREE_SPACE_PTR_OFFSET);
}

uint32_t BNode::GetRightMostChild()
{
    if (GetType() != BNodeType::Internal)
    {
        throw std::runtime_error("Leaf node does not have a RightMostChild");
    }

    return ReadUint32At(dataPtr, RIGHT_MOST_CHILD_OFFSET);
}

uint16_t BNode::GetCellOffset(size_t idx)
{
    if (idx >= GetNumCells())
    {
        throw std::runtime_error("No cell with index=" + idx);
    }
    return ReadUint16At(dataPtr, CELL_PTRS_OFFSET + idx * CELL_PTR_SIZE);
}

std::pair<std::string, std::string> BNode::GetCell(size_t idx)
{
    uint16_t cellPos = GetCellOffset(idx);

    uint16_t keyLen = GetKeyLen(cellPos);
    uint16_t valLen = GetValueLen(cellPos);

    uint16_t baseOffset = cellPos + KEY_LEN_SIZE + VAL_LEN_SIZE;

    std::string key(keyLen, '\0');
    std::memcpy(&key[0], reinterpret_cast<uint8_t*>(dataPtr) + baseOffset, keyLen);

    std::string value(valLen, '\0');
    std::memcpy(&value[0], reinterpret_cast<uint8_t*>(dataPtr) + baseOffset + keyLen, valLen);

    return { key, value };
}

uint16_t BNode::GetKeyLen(uint16_t cellOffset)
{
    return ReadUint16At(dataPtr, cellOffset);
}

uint16_t BNode::GetValueLen(uint16_t cellOffset)
{
    return ReadUint16At(dataPtr, cellOffset + KEY_LEN_SIZE);
}

void BNode::SetType(BNodeType type)
{
    WriteTypeAt<BNodeType>(dataPtr, BNODE_TYPE_OFFSET, type);
}

void BNode::SetNumCells(uint16_t numCells)
{
    WriteUint16At(dataPtr, NUM_CELLS_OFFSET, numCells);
}

void BNode::SetFreeSpacePtr(uint16_t ptr)
{
    WriteUint16At(dataPtr, FREE_SPACE_PTR_OFFSET, ptr);
}

void BNode::SetRightMostChild(uint32_t value)
{
    WriteUint32At(dataPtr, RIGHT_MOST_CHILD_OFFSET, value);
}

void BNode::SetCellOffset(size_t idx, uint16_t value)
{
    uint32_t offset = CELL_PTRS_OFFSET + idx * CELL_PTR_SIZE;
    WriteUint16At(dataPtr, offset, value);
}