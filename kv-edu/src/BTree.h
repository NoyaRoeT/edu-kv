#include "BNode.h"

struct BTree
{
	BNode GetBNode(uint32_t pageNum);
	BNode AddBNode();
	void DelBNode();

	int32_t root;
};