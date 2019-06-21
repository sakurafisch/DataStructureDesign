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
	std::cout << number << "��λ����ϢΪ��<" << x << ", " << y << ">" << std::endl;
	return;
}

void Person::initCoordinate() {
	Sleep(10);  // �����ӳ�10ms
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

void Person::InitX_Aixs()	//���������ΪX�����긳ֵ
{
	int tempX;
	srand((unsigned)time(NULL) + y);
	tempX = (rand() % 100);
	x = tempX;
}

void Person::InitY_Aixs()	//���������ΪY�����긳ֵ
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
	std::cout << "��������ʶ�������� personIndex1 personIndex2:" << std::endl;
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

	// std::getchar(); // �Ե����һ���ַ�
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
	std::cout << "�ڽӾ���Ϊ��" << std::endl;
	for (int i = 0; i < maxnum; i++) {
		for (int j = 0; j < maxnum; j++) {
			if (edge[i][j] != infinity)
				std::cout << edge[i][j];
			else
				std::cout << "��";
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
	std::cout << "�������һ���˵���ţ�" << std::endl;
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
			 std::cout << person[firstPersonIndex].getNumber() << "��" << person[i].getNumber() << "����̾���Ϊ����" << std::endl;
		 else
			std::cout << person[firstPersonIndex].getNumber() << "��" << person[i].getNumber() << "����̾���Ϊ��" << path[i] << std::endl;
	 }
	int secondPersonIndex;
	std::cout << "������ڶ����˵���ţ�" << std::endl;
	std::cin >> secondPersonIndex;
	// secondPersonIndex--;      // ������Ŵ�1��ʼ
	std::stack <int> myStack;
	int tmp = secondPersonIndex;
	myStack.push(secondPersonIndex);
	bool isConnected = true; // ����ͼ����ͨ��
	while (firstPersonIndex != tmp) {
		tmp = prePerson[tmp]; 
		if (tmp == infinity) {
			isConnected = false;
			break;
		}
		myStack.push(tmp);
	}
	std::cout << person[firstPersonIndex].getNumber() << "��" << person[secondPersonIndex].getNumber() << "�����·��Ϊ��";
	while (!myStack.empty()) {
		std::cout << person[myStack.top()].getNumber() << " ";
		myStack.pop();
	}
	std::cout << std::endl;
}

void AdjMatrix::updateXY()	//����Person�Ķ����X��Y����
{
	//�ٴγ�ʼ����������
	std::fill(visited, visited + maxnum, false);
	std::fill(path, path + maxnum, infinity);
	std::fill(prePerson, prePerson + maxnum, infinity);
	//����ΪX��Y���긳ֵ
	for (int i = 0; i < Person::static_number; i++)
	{
		person[i].InitX_Aixs();
		person[i].InitY_Aixs();
	}
	//�����µ�X��Y���������������
	for (int i = 0; i < Person::static_number; i++)
		for (int j = 0; j < Person::static_number; j++)
		{
			if (adj[i][j] != infinity)
				adj[i][j] = distance(person[i].getx(), person[i].gety(), person[j].getx(), person[j].gety());
		}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "�����˵�λ���Ѹ��£�" << std::endl;
	std::cout << std::endl;
}

void AdjMatrix::relativeConnectable() 
{
	// ����ѭ��Ѱ�Ҹ�����Χ�ܹ���ϵ������
	std::cout << std::endl;
	std::cout << "��������Ҫ���Ҹ�����ϵ�˵��˵���ţ�" << std::endl;
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
		std::cout << "����˸���û���ˡ�" << std:: endl;
	}
	else {
		std::cout << std::endl;
		std::cout << "�ڸ����ܹ��ҵ�������:";
		while (!myQueue.empty()) {
			std::cout << myQueue.front() << ' ';
			myQueue.pop();
		}
		std::cout << std::endl;
	}
}

void AdjMatrix::onceConnectable()
{
	// ����ѭ��Ѱ��ͨ��һ���м��˿�����ϵ������
	std::cout << std::endl;
	std::cout << "��������Ҫ����ͨ��һ���м��˿�����ϵ�����˵��˵���ţ�" << std::endl;
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
		std::cout << "ͨ��һ���м����޷���ϵ��������" << std::endl;
	}
	else {
		std::cout << std::endl;
		std::cout << "ͨ��һ���м����ܹ���ϵ�������У�";
		while (!myQueue.empty()) {
			std::cout << myQueue.front() << ' ';
			myQueue.pop();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
