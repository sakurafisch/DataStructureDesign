#include "common.h"
using namespace winnerwinter;

void test();
bool cycle(AdjMatrix adjMatrix);

int main()
{
	test();
	return 0;
}


void test() 
{
	AdjMatrix adjMatrix;
	adjMatrix.createMatrix();
LOOP:
	if (cycle(adjMatrix)) goto LOOP;
	else return;
}

bool cycle(AdjMatrix adjMatrix) 
{
	adjMatrix.updateXY();
	adjMatrix.printAdj();
	adjMatrix.shortestPath();
	adjMatrix.relativeConnectable();
	adjMatrix.onceConnectable();
	std::cout << "输入\"exit\"退出，输入\"continue\"或其他内容继续" << std::endl;
	std::string str;
	std::cin >> str;
	if (str == "exit" || str == "EXIT") return false;
	else return true;
}
