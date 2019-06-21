#include "common.h"
#include <ctime>
#include <Windows.h>
#include <stack>
#include <queue>
#include <string>
using namespace winnerwinter;

int Person::static_number = 0;

Person::Person() {
	this->number = static_number;
	this->initCoordinate();
	static_number++;
}

int Person::getNumber() {
	return this->number;
}

void Person::printCoordinate(){
	std::cout << number << "的位置信息为：<" << x << ", " << y << ">" << std::endl;
	return;
}

void Person::initCoordinate() {
	Sleep(10);  // 程序延迟10ms
	srand((unsigned int)time(NULL) + number);
	this->x = (int)rand() % 101;
	srand((unsigned int)time(NULL) + x + number);
	this->y = (int)rand() % 101;
	return;
}

int Person::getx() {
	return this->x;
}

int Person::gety() {
	return this->y;
}

void Person::InitX_Aixs()	//利用随机数为X轴坐标赋值
{
	int tempX;
	srand((unsigned)time(NULL) + y);
	tempX = (rand() % 100);
	x = tempX;
}

void Person::InitY_Aixs()	//利用随机数为Y轴坐标赋值
{
	int tempY;
	srand((unsigned)time(NULL) + x);
	tempY = (rand() % 100);
	y = tempY;
}

AdjMatrix::AdjMatrix() {
	initMatrix();
	edgeNum = 0;
	std::fill(visited, visited + maxnum, false);
	std::fill(path, path + maxnum, infinity);
	std::fill(prePerson, prePerson + maxnum, infinity);
	for (int i = 0; i < maxnum; i++) {
		for (int j = 0; j < maxnum; j++) {
			adj[i][j] = infinity;
		}
	}
}

void AdjMatrix::createMatrix() {
	std::cout << "请输入认识的两个人 personIndex1 personIndex2:" << std::endl;
	int personIndex1, personIndex2;
	while (std::cin >> personIndex1 >> personIndex2) {
		edge[personIndex1][personIndex2] = distance(person[personIndex1].getx(), person[personIndex1].gety(), person[personIndex2].getx(), person[personIndex2].gety());
		edge[personIndex2][personIndex1] = edge[personIndex1][personIndex2];
		edgeNum++;
	}
	std::cin.clear();

	for (int i = 0; i < Person::static_number; i++) {
		for (int j = 0; j < Person::static_number; j++) {
			adj[i][j] = int(edge[i][j]);
			adj[j][i] = int(edge[i][j]);
		}
	}
	for (int i = 0; i < Person::static_number; i++)
	{
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

int AdjMatrix::getEdgeNum() {
	return edgeNum;
}

double AdjMatrix::distance(int x1, int y1, int x2, int y2) {
	double x = abs(x1 - x2);
	double y = abs(y1 - y2);
	return sqrt(x * x + y * y);
}

void AdjMatrix::printAdj() {
	std::cout << "邻接矩阵为：" << std::endl;
	for (int i = 0; i < maxnum; i++) {
		for (int j = 0; j < maxnum; j++) {
			if (edge[i][j] != infinity)
				std::cout << edge[i][j];
			else
				std::cout << "∞";
			if (j != maxnum - 1) {
				std::cout << '\t';
			} else {
				std::cout << std::endl;
			}
		}
	}
}

void AdjMatrix::shortestPath(){
	std::fill(path, path + Person::static_number, infinity);
	std::cout << std::endl;
	std::cout << "请输入第一个人的序号：" << std::endl;
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
			 std::cout << person[firstPersonIndex].getNumber() << "到" << person[i].getNumber() << "的最短距离为：∞" << std::endl;
		 else
			std::cout << person[firstPersonIndex].getNumber() << "到" << person[i].getNumber() << "的最短距离为：" << path[i] << std::endl;
	 }
	int secondPersonIndex;
	std::cout << "请输入第二个人的序号：" << std::endl;
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
	std::cout << std::endl;
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
		person[i].InitX_Aixs();
		person[i].InitY_Aixs();
	}
	//根据新的X、Y坐标计算两点间距离
	for (int i = 0; i < Person::static_number; i++)
		for (int j = 0; j < Person::static_number; j++)
		{
			if (adj[i][j] != infinity)
				adj[i][j] = distance(person[i].getx(), person[i].gety(), person[j].getx(), person[j].gety());
		}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "所有人的位置已更新！" << std::endl;
	std::cout << std::endl;
}

void AdjMatrix::relativeConnectable() 
{
	// 利用循环寻找附近范围能够联系到的人
	std::cout << std::endl;
	std::cout << "请输入需要查找附近联系人的人的序号：" << std::endl;
	int find;
	std::cin >> find;
	std::queue<int> myQueue;
	std::cout << std::endl;
	for (int i = 0; i < Person::static_number; i++) {
		if (adj[find][i] < 1000 && ( person[i].getNumber() != person[find].getNumber() )) {
			myQueue.push(person[i].getNumber());
		}
	}
	if (myQueue.empty()) {
		std::cout << "这个人附近没有人。" << std:: endl;
	}
	else {
		std::cout << std::endl;
		std::cout << "在附近能够找到的人有:";
		while (!myQueue.empty()) {
			std::cout << myQueue.front() << ' ';
			myQueue.pop();
		}
		std::cout << std::endl;
	}
}

void AdjMatrix::onceConnectable()
{
	// 利用循环寻找通过一次中间人可以联系到的人
	std::cout << std::endl;
	std::cout << "请输入需要查找通过一次中间人可以联系到的人的人的序号：" << std::endl;
	int find;
	std::cin >> find;
	std::queue<int> myQueue;
	for (int i = 0; i < Person::static_number; i++) {
		if (adj[find][i] != infinity) {
			for (int m = 0; m < Person::static_number; m++) {
				if (adj[i][m] != infinity && person[m].getNumber() != person[find].getNumber()) {
					myQueue.push(person[m].getNumber());
				}
			}
		}
	}
	if (myQueue.empty()) {
		std::cout << "通过一次中间人无法联系到其他人" << std::endl;
	}
	else {
		std::cout << std::endl;
		std::cout << "通过一次中间人能够联系到的人有：";
		while (!myQueue.empty()) {
			std::cout << myQueue.front() << ' ';
			myQueue.pop();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
