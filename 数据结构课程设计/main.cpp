#include "common.h"		// 引入自定义的头文件 common.h

using namespace winnerwinter;	// 使用自定义的命名空间 winnerwinter

void test();	// 声明测试方法
bool cycle(AdjMatrix adjMatrix);	// 声明不断循环地执行的方法

int main()		// 主方法
{
	test();		// 测试 
	return 0;	// 程序正常退出
}

void test() 
{
	AdjMatrix adjMatrix;	// 构造邻接矩阵
	adjMatrix.createMatrix();	// I/O 输入人与人之间是否认识
LOOP:
	if (cycle(adjMatrix)) goto LOOP;	// 循环执行
	else return;						// 退出
}

bool cycle(AdjMatrix adjMatrix)		// 这是不断循环的内容
{
	adjMatrix.updateXY();	// 使用随机数更新地理位置信息，在循环中多次调用便可以达到不断更新地理位置的效果
	adjMatrix.printAllPeopleCoordinate();	// 打印所有人的地理位置信息
	adjMatrix.printAdj();		// 打印邻接矩阵
	adjMatrix.shortestPath();		// 最短路径
	adjMatrix.relativeConnectable();	// 附近认识的人
	adjMatrix.onceConnectable();		// 通过一次中间人可以找到的人
	// 以下代码，用于与用户交互，让用户来决定让程序继续运行还是退出程序
	std::cout << "输入\"exit\"退出，输入\"continue\"或其他内容继续" << std::endl;
	std::string str;
	std::cin >> str;
	if (str == "exit" || str == "EXIT") return false;
	else return true;
}
