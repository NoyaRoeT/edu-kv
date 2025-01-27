#include <iostream>
#include <cstring>
#include "BNode.h"  // Assuming BNode class is defined in BNode.h

int main() {
    // Step 1: Allocate a page for dataPtr (simulating the memory for a BNode).
    void* dataPtr = std::malloc(BNode::PAGE_SIZE);
    if (dataPtr == nullptr) {
        std::cerr << "Memory allocation failed." << std::endl;
        return 1;  // Exit with error if memory allocation fails.
    }

    // Step 2: Create a BNode instance and set dataPtr.
    BNode node;
    node.dataPtr = dataPtr;  // Set dataPtr to the allocated memory.

    // Step 3: Set values using setters.
    node.SetType(BNodeType::Internal);  // Set the type.
    node.SetNumCells(42);  // Set the number of cells.
    node.SetFreeSpacePtr(1234);  // Set the free space pointer.
    node.SetRightMostChild(5678);  // Set the rightmost child.
    node.SetCellOffset(0, 9876);  // Set the cell offset for index 0.

    // Step 4: Get values using getters and check them.
    std::cout << "BNode Type: " << static_cast<int>(node.GetType()) << std::endl;
    std::cout << "Number of Cells: " << node.GetNumCells() << std::endl;
    std::cout << "Free Space Ptr: " << node.GetFreeSpacePtr() << std::endl;
    std::cout << "Right Most Child: " << node.GetRightMostChild() << std::endl;
    std::cout << "Cell Offset at Index 0: " << node.GetCellOffset(0) << std::endl;

    // Step 5: Clean up by freeing the allocated memory.
    std::free(dataPtr);

    return 0;
}