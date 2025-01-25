#include <iostream>
#include "BNode.h"

int main(int argc, char** argv)
{
    // Mock a 256-byte page for testing
    uint8_t mockPage[256];
    std::memset(mockPage, 0, sizeof(mockPage)); // Clear the memory to avoid undefined behavior

    // Initialize the header values
    mockPage[BNode::BNODE_TYPE_OFFSET] = static_cast<uint8_t>(BNodeType::Internal); // Node type
    *reinterpret_cast<uint16_t*>(mockPage + BNode::NUM_CELLS_OFFSET) = 3;           // Number of cells
    *reinterpret_cast<uint16_t*>(mockPage + BNode::FREE_SPACE_PTR_OFFSET) = 100;    // Free space pointer
    *reinterpret_cast<uint32_t*>(mockPage + BNode::RIGHT_MOST_CHILD_OFFSET) = 42;   // Right-most child pointer

    // Initialize the cell pointers
    uint16_t* cellPtrs = reinterpret_cast<uint16_t*>(mockPage + BNode::CELL_PTRS_OFFSET);
    cellPtrs[0] = 120;
    cellPtrs[1] = 140;
    cellPtrs[2] = 160;

    // Create a BNode instance pointing to the mock page
    BNode bNode;
    bNode.dataPtr = mockPage;

    // Run tests
    bool allTestsPass = true;

    // Test 1: GetType
    BNodeType expectedType = BNodeType::Internal;
    if (bNode.GetType() != expectedType) {
        std::cerr << "Test 1 failed: GetType() returned incorrect value\n";
        std::cerr << "Expected: " << static_cast<int>(expectedType) << "\n";
        std::cerr << "Actual: " << static_cast<int>(bNode.GetType()) << "\n";
        allTestsPass = false;
    }

    // Test 2: GetNumCells
    uint16_t expectedNumCells = 3;
    if (bNode.GetNumCells() != expectedNumCells) {
        std::cerr << "Test 2 failed: GetNumCells() returned incorrect value\n";
        std::cerr << "Expected: " << expectedNumCells << "\n";
        std::cerr << "Actual: " << bNode.GetNumCells() << "\n";
        allTestsPass = false;
    }

    // Test 3: GetFreeSpacePtr
    uint16_t expectedFreeSpacePtr = 100;
    if (bNode.GetFreeSpacePtr() != expectedFreeSpacePtr) {
        std::cerr << "Test 3 failed: GetFreeSpacePtr() returned incorrect value\n";
        std::cerr << "Expected: " << expectedFreeSpacePtr << "\n";
        std::cerr << "Actual: " << bNode.GetFreeSpacePtr() << "\n";
        allTestsPass = false;
    }

    // Test 4: GetRightMostChild
    uint32_t expectedRightMostChild = 42;
    if (bNode.GetRightMostChild() != expectedRightMostChild) {
        std::cerr << "Test 4 failed: GetRightMostChild() returned incorrect value\n";
        std::cerr << "Expected: " << expectedRightMostChild << "\n";
        std::cerr << "Actual: " << bNode.GetRightMostChild() << "\n";
        allTestsPass = false;
    }

    // Test 5: GetCellPtrs
    std::vector<uint16_t> expectedPtrs = { 120, 140, 160 };
    std::vector<uint16_t> actualPtrs = bNode.GetCellPtrs();
    if (actualPtrs != expectedPtrs) {
        std::cerr << "Test 5 failed: GetCellPtrs() returned incorrect values\n";
        std::cerr << "Expected: ";
        for (const auto& ptr : expectedPtrs) {
            std::cerr << ptr << " ";
        }
        std::cerr << "\nActual: ";
        for (const auto& ptr : actualPtrs) {
            std::cerr << ptr << " ";
        }
        std::cerr << "\n";
        allTestsPass = false;
    }

    // Final result
    if (allTestsPass) {
        std::cout << "All tests passed successfully!\n";
    }
    else {
        std::cerr << "Some tests failed. Check the logs above.\n";
    }

    return allTestsPass ? 0 : 1;
}