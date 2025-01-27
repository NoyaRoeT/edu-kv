# B+ Tree Pages

## Key-Value
Store arbitrary length key-value pairs.
Do not allow size of a key-value record to exceed the content size of a page.

Format: keyLen, valueLen, key, value


## Page format
Fixed page size = 4096, might change this later on (e.g. make it configurable)

For internal nodes, key-value pairs store keys and the page numbers of the child nodes responsible
for the given range.

Format:
+---------------------+----------------------+-----------------------+---------------------+------------------------------+------------+
| BNODE_TYPE (1 byte) | NUM_CELLS (2 bytes) | FREE_SPACE_PTR (2B)  | RIGHT_MOST_CHILD (4B) | CELL_OFFSETS (2B * NUM_CELLS)| FREE_SPACE |
+---------------------+----------------------+-----------------------+---------------------+------------------------------+------------+

Page offset uses 4 bytes (uint32_t) => max number of pages bounded by this.

NOTE: raw pointers may suffer from byte alignment issues (some architectures do not allow accessing unaligned memory). So use memcpy instead.

## BNode
Encapsulates a node in a B+ tree.

TODO: BNode encapsulates a page in the DB. It will be responsible for interacting with the page manager, i.e. it is responsible for reads and writes to its associated page.

## BTree
Represents a B+ tree.

TODO: BTree will interact with BNodes only and not directly with the page manager.

## Design plan
BTree will request a page from PageManager, PageManager will return a BNode that is used to send R/W requests to PageManager.
PageManager will be a singleton that is globally accessible.


## Current Issues
1. Ownership of data pointer that points to the start of a DB page in memory.
	- In the future, would like to implement a buffer management system.
	- Probably means we will have an object that manages pages in memory and R/W to pages on disk.
	- That object should then have ownership of page.
	- One way is to give the BNode a reference to the page in memory, but if this page is removed from memory the reference is invalidated.
	- Another way is to send page modification requests to the page manager (e.g. write to this byte or retrieve from this byte)
	- Prefer the 2nd centralized approach where page manager is responsible for all access to pages.
	- Since the page manager is implemented after BNode, let BNode handle data for now, but manipulation should be done through well-defined functions that do not have knowledge of the ptr.