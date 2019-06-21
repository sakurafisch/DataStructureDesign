#pragma once

#include<iostream>		// �����׼�����������ͷ�ļ�

namespace winnerwinter		// ���������ռ�
{
	const int maxnum = 10;	// ���������ֵ
	const int infinity = 10000;//��10000��ʾ����ֵ
	class Person		// ��ʾ����
	{
	public:
		static int static_number;		// ��̬��Ա��������ʾ����
	public:
		Person();	// ���췽��
		int getNumber();	// ��ȡ�˵����
		void printCoordinate();
		int getx();				// ��ȡ�˵� x ����
		int gety();				// ��ȡ�˵� y ����
		void initX_Aixs();		// ���� x ����
		void initY_Aixs();		// ���� y ����
	private:
		void initCoordinate();	//��ʼ���˵�λ��
	private:
		int number;		// �˵���ţ���Ϊ����
		int x;			// �˵� x ����
		int y;			// �˵� y ����
	};

	class AdjMatrix 
	{
	public:
		AdjMatrix();	// ���췽������ʼ��һϵ�б���
		void createMatrix();	// ��������I/O����������֮��Ĺ�ϵ
		int getEdgeNum();	// ��ȡ����
		void printAdj();	// ��ӡ����
		void shortestPath();	// ���·��
		void updateXY();	// ����X��Y���꣬������λ�ø���
		void relativeConnectable();		// ������ʶ����
		void onceConnectable();		// ͨ��һ���м������ҵ�����
		void printAllPeopleCoordinate();		// ��ӡ�����˵�����
	private:
		double distance(int, int, int, int);	// ����������֮��ľ���
		void initMatrix();	// ��ʼ�����󣬰ѱ߳�ʼ��Ϊ����ֵinfinity���÷���ֻ���ڲ�����
	private:
		Person person[maxnum];		// �ڵ㣬���罻��ϵͼ�У����ǽڵ�
		double edge[maxnum][maxnum];	// �ߣ���ʾ�������Ƿ���ʶ�Լ����ǵ�ֱ�Ӿ���
		int edgeNum;	// ����
		bool visited[maxnum];	// �Ƿ��ѱ����������·�����õ�
		int path[maxnum];		// ���ڴ洢���·��
		int prePerson[maxnum];		// ǰһ����
		int adj[maxnum][maxnum];	// ���Ҳ�Ǳ�
	};
}
