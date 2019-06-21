#pragma once

#include<iostream>		// 引入标准输入输出流的头文件

namespace winnerwinter		// 定义命名空间
{
	const int maxnum = 10;	// 人数的最大值
	const int infinity = 10000;//用10000表示无穷值
	class Person		// 表示人类
	{
	public:
		static int static_number;		// 静态成员变量，表示人数
	public:
		Person();	// 构造方法
		int getNumber();	// 获取人的序号
		void printCoordinate();
		int getx();				// 获取人的 x 坐标
		int gety();				// 获取人的 y 坐标
		void initX_Aixs();		// 更新 x 坐标
		void initY_Aixs();		// 更新 y 坐标
	private:
		void initCoordinate();	//初始化人的位置
	private:
		int number;		// 人的序号，作为主码
		int x;			// 人的 x 坐标
		int y;			// 人的 y 坐标
	};

	class AdjMatrix 
	{
	public:
		AdjMatrix();	// 构造方法，初始化一系列变量
		void createMatrix();	// 创建矩阵，I/O输入人与人之间的关系
		int getEdgeNum();	// 获取边数
		void printAdj();	// 打印矩阵
		void shortestPath();	// 最短路径
		void updateXY();	// 更新X、Y坐标，即地理位置更新
		void relativeConnectable();		// 附近认识的人
		void onceConnectable();		// 通过一个中间人能找到的人
		void printAllPeopleCoordinate();		// 打印所有人的坐标
	private:
		double distance(int, int, int, int);	// 计算人与人之间的距离
		void initMatrix();	// 初始化矩阵，把边初始化为无穷值infinity，该方法只在内部调用
	private:
		Person person[maxnum];		// 节点，在社交关系图中，人是节点
		double edge[maxnum][maxnum];	// 边，表示人与人是否认识以及他们的直接距离
		int edgeNum;	// 边数
		bool visited[maxnum];	// 是否已遍历，在最短路径中用到
		int path[maxnum];		// 用于存储最短路径
		int prePerson[maxnum];		// 前一个人
		int adj[maxnum][maxnum];	// 这个也是边
	};
}
