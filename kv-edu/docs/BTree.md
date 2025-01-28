# B+ Tree

## Data format
Fixed page size = 4KB.

Page format:
+---------------------+----------------------+-----------------------+---------------------+------------------------------+------------+-------+
| BNODE_TYPE (1 byte) | NUM_CELLS (2 bytes) | FREE_SPACE_PTR (2B)  | RIGHT_MOST_CHILD (4B) | CELL_OFFSETS (2B * NUM_CELLS)| Free space | Cells |
+---------------------+----------------------+-----------------------+---------------------+------------------------------+------------+-------+

For non-variable sized nodes which we are using here, maximum key and value sizes should be chosen such that each page contains at least 2 keys,
else the data structure will be inefficient.
- Explained here: https://stackoverflow.com/questions/74284080/should-btrees-with-variable-length-keys-and-values-be-split-based-on-size-byte

Cell format (key-value pair):
+-------------+-------------+-----+-----+
| keyLen (2b) | varLen (2b) | key | val |
+-------------+-------------+-----+-----+

Given that page header size = 1 + 2 + 2 + 4 = 9B and a cell offset is 2B, each cell occupies (keySize + valSize + 6)B.
We want cellSize < (4KB - 9B) / 2= 4087B / 2.

So we arbitrarily set:
- Max key size = 512
- Max val size = 1024

## BNode
Responsible for making sense of B+ tree page data.

Cells are added from the back of the page towards the front, to give way for cell offsets to grow as new cells are added.
The order of cells does not matter, instead we use cell offsets to maintain a sorted order for keys.
This also means that we need a ptr to keep track of where to insert new cells, which is what the free space ptr is for.

Inserting into a BNode:
1. Find the idx position to insert the new cell.
2. Determine if there is enough space to insert the cell.
3. If there is enough space, add the cell to the cell region and insert the offset in sorted order.
4. If there is not enough space, split the cell:
	- Can either split the cell into even sized cells.
	- Or just use the middle key.
	- Smallest cell of right node is inserted into parent.



## Some implementation details
1. raw pointers may suffer from byte alignment issues (some architectures do not allow accessing unaligned memory). So use memcpy instead, which treats everything as bytes.

## TODO
1. Go revise B+ tree :l
2. Implement B+ tree T.T