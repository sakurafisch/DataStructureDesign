#include "common.h"		// �����Զ����ͷ�ļ� common.h

#include <ctime>		//����ʱ���ͷ�ļ�
#include <Windows.h>	// �����׼Windows��̵�ͷ�ļ���Sleep()����������ļ�����
#include <stack>	// ����ջ��ͷ�ļ�
#include <queue>	// ������е�ͷ�ļ�
#include <string>	// �����ַ������ͷ�ļ�

using namespace winnerwinter;		// ʹ���Զ���������ռ� winnerwinter

int Person::static_number = 0;		// ��ʼ������Ϊ 0

Person::Person() {		// ���췽��
	this->number = static_number;		// �� n ���˵���ž��� n - 1
	this->initCoordinate();			// ��ʼ�����꣬������λ��
	static_number++;		// ���� + 1
}

int Person::getNumber()		// ��ȡ�˵����
{
	return this->number;	// �����˵����
}

void Person::printCoordinate()	//��ӡ����λ����Ϣ
{
	std::cout << number << "��λ����ϢΪ��<" << x << ", " << y << ">" << std::endl;		// ��ӡ����λ����Ϣ������
	return;		// ����
}

void Person::initCoordinate() 
{
	Sleep(10);  // �����ӳ�10ms
	srand((unsigned int)time(NULL) + number);	// ��������
	this->x = (int)rand() % 101;	// ������� x ���꣬ ��Χ�� 0 ~ 100
	srand((unsigned int)time(NULL) + x + number);	// ��������
	this->y = (int)rand() % 101;	// ������� y ���꣬ ��Χ�� 0 ~ 100
	return;		//����
}

int Person::getx() {	// ��ȡ�˵� x ����
	return this->x;		// �����˵� x ����
}

int Person::gety() {	// ��ȡ�˵� y ����
	return this->y;		// �����˵� y ����
}

void Person::initX_Aixs()	//���������Ϊ x ���긳ֵ
{
	int tmpX;		// ������ʱ����
	srand((unsigned)time(NULL) + y);	// ��������
	tmpX = (rand() % 100);		// �������������ֵ����ʱ����
	this->x = tmpX;		// ����ʱ������ֵ�����˵� x ����
}

void Person::initY_Aixs()	//���������Ϊ y ���긳ֵ
{
	int tmpY;		// ������ʱ����
	srand((unsigned)time(NULL) + x);	// ��������
	tmpY = (rand() % 100);		// �������������ֵ����ʱ����
	this->y = tmpY;		// ����ʱ������ֵ�����˵� y ����
}

AdjMatrix::AdjMatrix() {	// ���췽��
	initMatrix();	// ��ʼ�����󣨵ıߣ�
	edgeNum = 0;	// ��ʼ���ߵ�ֵΪ 0
	std::fill(visited, visited + maxnum, false);	// ��ʼ�� visited ����Ϊ false����ʾ�����δ������
	std::fill(path, path + maxnum, infinity);	// ��ʼ�� path ����Ϊ false�� ��ʾ·���ĳ�ʼ����Ϊ����Զ
	std::fill(prePerson, prePerson + maxnum, infinity);		// ��ʼ��ǰһ����Ϊ����ֵ
	for (int i = 0; i < maxnum; i++) {	// һ�ر���
		for (int j = 0; j < maxnum; j++) {	// ���ر���
			adj[i][j] = infinity;	// ��ʼ����ֵΪ����ֵ infinity
		}
	}
}

void AdjMatrix::createMatrix() {	// ��������
	std::cout << "��������ʶ�������� personIndex1 personIndex2:" << std::endl;		// ��ʾ������Ϣ������
	int personIndex1, personIndex2;		// ��������Դ洢������Ϣ
	while (std::cin >> personIndex1 >> personIndex2) {	// ÿ��������ȷ�ͼ���ִ��ѭ����ֱ������ Ctrl + Z
		edge[personIndex1][personIndex2] = distance(person[personIndex1].getx(), person[personIndex1].gety(), person[personIndex2].getx(), person[personIndex2].gety());	// ������֮��ĵ���λ�þ�����Ϊ�ߵ�ֵ
		edge[personIndex2][personIndex1] = edge[personIndex1][personIndex2];	// ����ͼ������ָ
		edgeNum++;		// �ߵ����� + 1
	}
	std::cin.clear();	// ������� Ctrl + Z ����ֹ������Ϣ
	// adj �Ĺ��ܺ� edge ��һ���ġ�
	for (int i = 0; i < Person::static_number; i++) {
		for (int j = 0; j < Person::static_number; j++) {
			adj[i][j] = int(edge[i][j]);
			adj[j][i] = int(edge[i][j]);
		}
	}
	// ÿ������ϵ�Լ��ľ���Ϊ 0
	for (int i = 0; i < Person::static_number; i++){
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

int AdjMatrix::getEdgeNum() {	 // ��ȡ����
	return edgeNum;		// ���ر���
}

double AdjMatrix::distance(int x1, int y1, int x2, int y2) {
	// ���ɶ���������
	double x = abs(x1 - x2);
	double y = abs(y1 - y2);
	return sqrt(x * x + y * y);	
}

void AdjMatrix::printAdj() {
	std::cout << "�ڽӾ���Ϊ��" << std::endl;		// ����ַ���������
	// ��ӡ�ڽӾ���
	for (int i = 0; i < maxnum; i++) {
		for (int j = 0; j < maxnum; j++) {
			if (edge[i][j] != infinity)
				std::cout << edge[i][j];
			else
				std::cout << "��";
			if (j != maxnum - 1) {
				std::cout << '\t';			// ����Ʊ��
			} else {
				std::cout << std::endl;		// ����
			}
		}
	}
}

void AdjMatrix::shortestPath(){		// ���·��
	// Dijkstra's algorithm  ������Ϊ�Ͻ�˹�����㷨
	std::fill(path, path + Person::static_number, infinity);
	std::cout << std::endl;		// ����
	std::cout << "�������һ���˵���ţ�" << std::endl;		// �����ʾ��Ϣ������
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
			 std::cout << person[firstPersonIndex].getNumber() << "��" << person[i].getNumber() << "����̾���Ϊ����" << std::endl;		// ����
		 else
			std::cout << person[firstPersonIndex].getNumber() << "��" << person[i].getNumber() << "����̾���Ϊ��" << path[i] << std::endl;		// ����
	 }
	int secondPersonIndex;
	std::cout << "������ڶ����˵���ţ�" << std::endl;		// ����
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
	std::cout << std::endl;		// ����
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
		person[i].initX_Aixs();
		person[i].initY_Aixs();
	}
	//�����µ�X��Y���������������
	for (int i = 0; i < Person::static_number; i++)
		for (int j = 0; j < Person::static_number; j++)
		{
			if (adj[i][j] != infinity)
				adj[i][j] = distance(person[i].getx(), person[i].gety(), person[j].getx(), person[j].gety());
		}
	std::cout << std::endl;		// ����
	std::cout << std::endl;		// ����
	std::cout << std::endl;		// ����
	std::cout << "�����˵�λ���Ѹ��£�" << std::endl;		// ����
	std::cout << std::endl;		// ����
}

void AdjMatrix::relativeConnectable() 
{
	// ����ѭ��Ѱ�Ҹ�����Χ�ܹ���ϵ������
	std::cout << std::endl;		// ����
	std::cout << "��������Ҫ���Ҹ�����ϵ�˵��˵���ţ�" << std::endl;		// ����
	int find;
	std::cin >> find;
	std::queue<int> myQueue;
	std::cout << std::endl;		// ����
	for (int i = 0; i < Person::static_number; i++) {
		if (adj[find][i] < 1000 && ( person[i].getNumber() != person[find].getNumber() )) {
			myQueue.push(person[i].getNumber());
		}
	}
	if (myQueue.empty()) {
		std::cout << "����˸���û���ˡ�" << std:: endl;		// ����
	}
	else {
		std::cout << std::endl;		// ����
		std::cout << "�ڸ����ܹ��ҵ�������:";
		while (!myQueue.empty()) {
			std::cout << myQueue.front() << ' ';
			myQueue.pop();
		}
		std::cout << std::endl;		// ����
	}
}

void AdjMatrix::onceConnectable()
{
	// ����ѭ��Ѱ��ͨ��һ���м��˿�����ϵ������
	std::cout << std::endl;		// ����
	std::cout << "��������Ҫ����ͨ��һ���м��˿�����ϵ�����˵��˵���ţ�" << std::endl;		// ����
	int find;		// ��ʼ�˵��±�
	std::cin >> find;		// ������ʼ�˵��±�
	std::queue<int> myQueue;	// �������
	for (int i = 0; i < Person::static_number; i++) {	// ��������
		if (adj[find][i] != infinity) {		// ��
			for (int m = 0; m < Person::static_number; m++) {
				if (adj[i][m] != infinity && person[m].getNumber() != person[find].getNumber()) {
					myQueue.push(person[m].getNumber());
				}
			}
		}
	}
	if (myQueue.empty()) {		// ����ӿ�
		std::cout << "ͨ��һ���м����޷���ϵ��������" << std::endl;		// ����ַ���
	}
	else {
		std::cout << std::endl;		// ����
		std::cout << "ͨ��һ���м����ܹ���ϵ�������У�";
		while (!myQueue.empty()) {		// ִ��ѭ����ֱ���ӿ�
			std::cout << myQueue.front() << ' ';	// ��ӡ��ͷ��Ϣ
			myQueue.pop();		// ����
		}
		std::cout << std::endl;		// ����
	}
	std::cout << std::endl;		// ����
}

void AdjMatrix::printAllPeopleCoordinate()
{
	for (int i = 0; i < Person::static_number; i++) {	// ��������
		person[i].printCoordinate();	// ��ӡ�˵�����
	}
	std::cout << std::endl;		// ����
}
