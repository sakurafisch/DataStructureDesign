#include "common.h"		// 引入自定义的头文件 common.h

#include <ctime>		//引入时间的头文件
#include <Windows.h>	// 引入标准Windows编程的头文件，Sleep()函数在这个文件里面
#include <stack>	// 引入栈的头文件
#include <queue>	// 引入队列的头文件
#include <string>	// 引入字符串类的头文件

using namespace winnerwinter;		// 使用自定义的命名空间 winnerwinter

int Person::static_number = 0;		// 初始化人数为 0

Person::Person() {		// 构造方法
	this->number = static_number;		// 第 n 个人的序号就是 n - 1
	this->initCoordinate();			// 初始化坐标，即地理位置
	static_number++;		// 人数 + 1
}

int Person::getNumber()		// 获取人的序号
{
	return this->number;	// 返回人的序号
}

void Person::printCoordinate()	//打印地理位置信息
{
	std::cout << number << "的位置信息为：<" << x << ", " << y << ">" << std::endl;		// 打印地理位置信息并换行
	return;		// 返回
}

void Person::initCoordinate() 
{
	Sleep(10);  // 程序延迟10ms
	srand((unsigned int)time(NULL) + number);	// 更新种子
	this->x = (int)rand() % 101;	// 随机生成 x 坐标， 范围在 0 ~ 100
	srand((unsigned int)time(NULL) + x + number);	// 更新种子
	this->y = (int)rand() % 101;	// 随机生成 y 坐标， 范围在 0 ~ 100
	return;		//返回
}

int Person::getx() {	// 获取人的 x 坐标
	return this->x;		// 返回人的 x 坐标
}

int Person::gety() {	// 获取人的 y 坐标
	return this->y;		// 返回人的 y 坐标
}

void Person::initX_Aixs()	//利用随机数为 x 坐标赋值
{
	int tmpX;		// 定义临时变量
	srand((unsigned)time(NULL) + y);	// 更新种子
	tmpX = (rand() % 100);		// 生成随机数并赋值给临时变量
	this->x = tmpX;		// 把临时变量的值赋给人的 x 坐标
}

void Person::initY_Aixs()	//利用随机数为 y 坐标赋值
{
	int tmpY;		// 定义临时变量
	srand((unsigned)time(NULL) + x);	// 更新种子
	tmpY = (rand() % 100);		// 生成随机数并赋值给临时变量
	this->y = tmpY;		// 把临时变量的值赋给人的 y 坐标
}

AdjMatrix::AdjMatrix() {	// 构造方法
	initMatrix();	// 初始化矩阵（的边）
	edgeNum = 0;	// 初始化边的值为 0
	std::fill(visited, visited + maxnum, false);	// 初始化 visited 数组为 false，表示各点均未被访问
	std::fill(path, path + maxnum, infinity);	// 初始化 path 数组为 false， 表示路径的初始距离为无穷远
	std::fill(prePerson, prePerson + maxnum, infinity);		// 初始化前一个人为无穷值
	for (int i = 0; i < maxnum; i++) {	// 一重遍历
		for (int j = 0; j < maxnum; j++) {	// 二重遍历
			adj[i][j] = infinity;	// 初始化边值为无穷值 infinity
		}
	}
}

void AdjMatrix::createMatrix() {	// 创建矩阵
	std::cout << "请输入认识的两个人 personIndex1 personIndex2:" << std::endl;		// 提示输入信息并换行
	int personIndex1, personIndex2;		// 定义变量以存储输入信息
	while (std::cin >> personIndex1 >> personIndex2) {	// 每当输入正确就继续执行循环，直到遇到 Ctrl + Z
		edge[personIndex1][personIndex2] = distance(person[personIndex1].getx(), person[personIndex1].gety(), person[personIndex2].getx(), person[personIndex2].gety());	// 把两人之间的地理位置距离作为边的值
		edge[personIndex2][personIndex1] = edge[personIndex1][personIndex2];	// 无向图，互相指
		edgeNum++;		// 边的数量 + 1
	}
	std::cin.clear();	// 用于清空 Ctrl + Z 的终止输入信息
	// adj 的功能和 edge 是一样的。
	for (int i = 0; i < Person::static_number; i++) {
		for (int j = 0; j < Person::static_number; j++) {
			adj[i][j] = int(edge[i][j]);
			adj[j][i] = int(edge[i][j]);
		}
	}
	// 每个人联系自己的距离为 0
	for (int i = 0; i < Person::static_number; i++){
		adj[i][i] = 0;
	}

	// std::getchar(); // 吃掉最后一个字符
}

void AdjMatrix::initMatrix() {
	for (int i = 0; i < maxnum; i++) {
		for (int j = 0; j < maxnum; j++) {
			edge[i][j] = infinity;
		}
	}
}

int AdjMatrix::getEdgeNum() {	 // 获取边数
	return edgeNum;		// 返回边数
}

double AdjMatrix::distance(int x1, int y1, int x2, int y2) {
	// 勾股定理计算距离
	double x = abs(x1 - x2);
	double y = abs(y1 - y2);
	return sqrt(x * x + y * y);	
}

void AdjMatrix::printAdj() {
	std::cout << "邻接矩阵为：" << std::endl;		// 输出字符串并换行
	// 打印邻接矩阵
	for (int i = 0; i < maxnum; i++) {
		for (int j = 0; j < maxnum; j++) {
			if (edge[i][j] != infinity)
				std::cout << edge[i][j];
			else
				std::cout << "∞";
			if (j != maxnum - 1) {
				std::cout << '\t';			// 输出制表符
			} else {
				std::cout << std::endl;		// 换行
			}
		}
	}
}

void AdjMatrix::shortestPath(){		// 最短路径
	// Dijkstra's algorithm  中文名为迪杰斯特拉算法
	std::fill(path, path + Person::static_number, infinity);
	std::cout << std::endl;		// 换行
	std::cout << "请输入第一个人的序号：" << std::endl;		// 输出提示信息并换行
	int firstPersonIndex;
	std::cin >> firstPersonIndex;
	path[firstPersonIndex] = 0;
	for (int i = 0; i < Person::static_number; i++) {
		int u = -1;
		double min = infinity;
		for (int j = 0; j < Person::static_number; j++) {
			if (visited[j] == false && path[j] < min) {
				u = j;
				min = path[j];
			}
		}
		if (u == -1) break;
		visited[u] = true;
		for (int v = 0; v < Person::static_number; v++) {
			if (visited[v] == false && adj[u][v] != infinity) {
				if (path[u] + adj[u][v] < path[v]) {
					path[v] = path[u] + adj[u][v];
					prePerson[v] = u;
				}
			}
		}
	}
	 for (int i = 0; i < Person::static_number; i++) {
		 if (path[i] == infinity)
			 std::cout << person[firstPersonIndex].getNumber() << "到" << person[i].getNumber() << "的最短距离为：∞" << std::endl;		// 换行
		 else
			std::cout << person[firstPersonIndex].getNumber() << "到" << person[i].getNumber() << "的最短距离为：" << path[i] << std::endl;		// 换行
	 }
	int secondPersonIndex;
	std::cout << "请输入第二个人的序号：" << std::endl;		// 换行
	std::cin >> secondPersonIndex;
	// secondPersonIndex--;      // 所有序号从1开始
	std::stack <int> myStack;
	int tmp = secondPersonIndex;
	myStack.push(secondPersonIndex);
	bool isConnected = true; // 假设图是连通的
	while (firstPersonIndex != tmp) {
		tmp = prePerson[tmp]; 
		if (tmp == infinity) {
			isConnected = false;
			break;
		}
		myStack.push(tmp);
	}
	std::cout << person[firstPersonIndex].getNumber() << "到" << person[secondPersonIndex].getNumber() << "的最短路径为：";
	while (!myStack.empty()) {
		std::cout << person[myStack.top()].getNumber() << " ";
		myStack.pop();
	}
	std::cout << std::endl;		// 换行
}

void AdjMatrix::updateXY()	//更新Person的对象的X、Y坐标
{
	//再次初始化三个数组
	std::fill(visited, visited + maxnum, false);
	std::fill(path, path + maxnum, infinity);
	std::fill(prePerson, prePerson + maxnum, infinity);
	//重新为X、Y坐标赋值
	for (int i = 0; i < Person::static_number; i++)
	{
		person[i].initX_Aixs();
		person[i].initY_Aixs();
	}
	//根据新的X、Y坐标计算两点间距离
	for (int i = 0; i < Person::static_number; i++)
		for (int j = 0; j < Person::static_number; j++)
		{
			if (adj[i][j] != infinity)
				adj[i][j] = distance(person[i].getx(), person[i].gety(), person[j].getx(), person[j].gety());
		}
	std::cout << std::endl;		// 换行
	std::cout << std::endl;		// 换行
	std::cout << std::endl;		// 换行
	std::cout << "所有人的位置已更新！" << std::endl;		// 换行
	std::cout << std::endl;		// 换行
}

void AdjMatrix::relativeConnectable() 
{
	// 利用循环寻找附近范围能够联系到的人
	std::cout << std::endl;		// 换行
	std::cout << "请输入需要查找附近联系人的人的序号：" << std::endl;		// 换行
	int find;
	std::cin >> find;
	std::queue<int> myQueue;
	std::cout << std::endl;		// 换行
	for (int i = 0; i < Person::static_number; i++) {
		if (adj[find][i] < 1000 && ( person[i].getNumber() != person[find].getNumber() )) {
			myQueue.push(person[i].getNumber());
		}
	}
	if (myQueue.empty()) {
		std::cout << "这个人附近没有人。" << std:: endl;		// 换行
	}
	else {
		std::cout << std::endl;		// 换行
		std::cout << "在附近能够找到的人有:";
		while (!myQueue.empty()) {
			std::cout << myQueue.front() << ' ';
			myQueue.pop();
		}
		std::cout << std::endl;		// 换行
	}
}

void AdjMatrix::onceConnectable()
{
	// 利用循环寻找通过一次中间人可以联系到的人
	std::cout << std::endl;		// 换行
	std::cout << "请输入需要查找通过一次中间人可以联系到的人的人的序号：" << std::endl;		// 换行
	int find;		// 起始人的下标
	std::cin >> find;		// 输入起始人的下标
	std::queue<int> myQueue;	// 定义队列
	for (int i = 0; i < Person::static_number; i++) {	// 遍历众人
		if (adj[find][i] != infinity) {		// 当
			for (int m = 0; m < Person::static_number; m++) {
				if (adj[i][m] != infinity && person[m].getNumber() != person[find].getNumber()) {
					myQueue.push(person[m].getNumber());
				}
			}
		}
	}
	if (myQueue.empty()) {		// 如果队空
		std::cout << "通过一次中间人无法联系到其他人" << std::endl;		// 输出字符串
	}
	else {
		std::cout << std::endl;		// 换行
		std::cout << "通过一次中间人能够联系到的人有：";
		while (!myQueue.empty()) {		// 执行循环，直到队空
			std::cout << myQueue.front() << ' ';	// 打印队头信息
			myQueue.pop();		// 出队
		}
		std::cout << std::endl;		// 换行
	}
	std::cout << std::endl;		// 换行
}

void AdjMatrix::printAllPeopleCoordinate()
{
	for (int i = 0; i < Person::static_number; i++) {	// 遍历众人
		person[i].printCoordinate();	// 打印人的坐标
	}
	std::cout << std::endl;		// 换行
}
