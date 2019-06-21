#include "common.h"
using namespace winnerwinter;

int main()
{
	AdjMatrix adjMatrix;
	adjMatrix.createMatrix();
	while (true) {
		adjMatrix.showAdj(); 
		adjMatrix.shortestPath();
		adjMatrix.relativeConnectable();
		adjMatrix.onceConnectable();
		adjMatrix.updateXY();
	}
	system("pause");
	return 0;
}
