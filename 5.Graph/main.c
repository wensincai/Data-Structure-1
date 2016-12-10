#include "ALGraph.h"

int main()
{
	ALGraph G;
	CreateGraph(&G);
	BFSTraverse(&G);
	DFSTraverse(&G);
	printVex(&G);
	return 0;
}