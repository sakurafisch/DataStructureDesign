#pragma once
#include<iostream>


namespace winnerwinter
{
	const int maxnum = 10;
	const int infinity = 10000;//用10000表示无穷值
	class Person
	{
	public:
		static int static_number;
	public:
		Person();
		int getNumber();
		void initCoordinate();
		void printCoordinate();
		int getx();
		int gety();
		void InitX_Aixs();
		void InitY_Aixs();
	private:
		int number;
		int x;
		int y;
	};

	class AdjMatrix 
	{
	public:
		AdjMatrix();
		void createMatrix();
		int getEdgeNum();
		void printAdj();
		void shortestPath();
		void updateXY();
		void relativeConnectable();
		void onceConnectable();
		void printAllPeopleCoordinate();
	private:
		Person person[maxnum];
		double edge[maxnum][maxnum];
		int edgeNum;
		bool visited[maxnum];
		int path[maxnum];
		int prePerson[maxnum];
		int adj[maxnum][maxnum];
		void initMatrix();
		double distance(int, int, int, int);
	};
}
