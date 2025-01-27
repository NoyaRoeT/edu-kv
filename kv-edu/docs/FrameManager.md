## Frame Manager
Responsible for ownership and lifetimes of Frame objects, where each Frame object represents a page.

{
	framesMap -> maps page numbers to shared_ptrs that references a Frame object
	GetFrame(pageNum) -> returns a weak_ptr that references a Frame object
}

Issues:
1. Shared and weak pointers are thread-safe
	- May contain unnecessary concurrency control mechanisms where not required => overhead
	- The ownership semantics are good though.
2. Currently no cache eviction
	- Buffer size grows infinitely, which is not great.


## Frame
Encapsulates all the data of a frame.

{
	data -> points to the actual page data
	pinnedCount
}

Important that the Frame is never copied, else a copied object that runs out of scope will invalid the data pointer.

TODO: Add concurrency control to Frame access (if we ever get to introducing concurrent read/writes)

## BNode, Frame and FrameManager Interaction
Frame:
- Encapsulates all the data in a frame.
- Provides thread-safe access to page data.

BNode:
- A logical representation of a node in a B+ tree.
- While the frame contains the page data, the BNode can make sense of the page data.

FrameManager:
- Manages the lifetime and ownership of frames.

## TODO
1. Implement in-memory B+ tree that modifies memory via frames
	- Setter and getter methods for BNode header
	- Getter for BNode cell
	- Inserting into BNode
2. FrameManager
	- Ability to create new frames
	- Load frame with data after retreiving


Finish in-memory B+tree first, so we have data that we can test.