#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

#define MaxInt 32767	//表示极大值∞
#define MVNum 100	//最大顶点数
#define MAXQSIZE 50  //定义队列中元素的最大个数
#define OK 1	//成功标志
#define ERROR 0	//失败标志
#define TRUE 1
#define FALSE 0
typedef char VerTexType;	//设顶点的数据类型为字符型
typedef int ArcType;	//假设边的权值类型为整型
typedef int Status;	//Status 是函数的类型，其值是函数结果状态代码
typedef int QElemType;

//顺序队列
typedef struct
{
	QElemType *base;//初始化动态分配存储空间
	int front;//头指针（实际是队头元素下标）
	int rear;//尾指针（实际是队尾元素下标）
}SqQueue;

//图
typedef struct
{
	VerTexType vexs[MVNum];	//顶点表
	ArcType arcs[MVNum][MVNum];	//邻接矩阵
	int vexnum, arcnum;	//图的当前顶点数和边数
}AMGraph;	//Adjacency Matrix Graph

//函数声明
int LocateVex(AMGraph G, VerTexType v);	//查找顶点下标
void CreateUDN(AMGraph &G);	//创建邻接矩阵
void DFS(AMGraph G, int v);	//深度优先递归遍历
void BFS(AMGraph G, int v);	//广度优先非递归遍历
Status InitQueue(SqQueue& Q);	//队列初始化
Status EnQueue(SqQueue& Q, QElemType e);	//循环队列入队
Status DeQueue(SqQueue& Q, QElemType& e);	//循环队列出队


int visited[MVNum];

int main()
{
	AMGraph G;
	CreateUDN(G);

	cout << "邻接矩阵：" << endl;
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j < G.vexnum; j++)
		{
			cout << G.arcs[i][j] << " ";
		}
		cout << endl;
	}
	cout << "邻接矩阵深度优先遍历序列：";
	DFS(G, 0);
	cout << endl;

	for (int i = 0; i < G.vexnum; i++)	//将标志数组置0
	{
		visited[i] = 0;	
	}
	cout << "邻接矩阵广度优先遍历序列：";
	BFS(G, 0);
	cout << endl;
	
	system("pause");
	return 0;
}


//查找顶点下标
int LocateVex(AMGraph G, VerTexType v)
{
	int i;
	for (i = 0; i < G.vexnum; i++)
	{
		if (v == G.vexs[i])
		{
			return i;
		}
	}
	return -1;
}

void CreateUDN(AMGraph &G)
{
	cout << "输入总顶点数和总边数：";
	cin >> G.vexnum >> G.arcnum;	//输入总顶点数、总边数
	cout << "依次输入顶点的信息：";
	for (int i = 0; i < G.vexnum; i++)
	{
		cin >> G.vexs[i];	//依次输入点的信息
		visited[i] = 0;	//初始化标志数组为0
	}
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = 0;	//初始化每条边权值为0
		}
	}
	cout << "输入一条边所依附的两个顶点及边的权值：";
	for (int k = 0; k < G.arcnum; k++)
	{
		VerTexType v1, v2;
		int w;
		cin >> v1 >> v2 >> w;	//输入一条边所依附的顶点及边的权值
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);	//确定v1、v2在G中的位置
		G.arcs[i][j] = w;	//边<v1,v2>的权置为w
		G.arcs[j][i] = w;	//将其对称边的权值也置为w
	}

}

//深度优先递归遍历
void DFS(AMGraph G, int v)
{
	cout << G.vexs[v] << " ";
	visited[v] = 1;	//记录他改为已被访问
	for (int w = 0; w < G.vexnum; w++)
	{
		if ((G.arcs[v][w] != 0) && (visited[w] == 0))	//弧存在，且未被访问的邻接顶点
		{
			DFS(G, w);	//w是v的邻接顶点，若w未被访问，则递归调用DFS
		}
	}
}

//广度优先非递归遍历
void BFS(AMGraph G, int v)
{
	cout << G.vexs[v] << " ";	//输出第一个遍历顶点
	visited[v] = 1;	//记录他改为已被访问
	SqQueue Q;
	InitQueue(Q);	//辅助队列Q初始化，置空
	EnQueue(Q, v);	//v入队

	while (Q.front != Q.rear)	//队列非空
	{
		int u = 0;
		DeQueue(Q, u);	//队头元素出队并置为u

		int w = 0;
		for (int i = 0; i < G.vexnum; i++)
		{
			if ((G.arcs[u][i] != 0) && (visited[i] == 0))
			{
				w = i;	//找到u的第一个未被访问的邻接顶点，然后直接跳出
				break;
			}
		}
		for (; w < G.vexnum; w++)
		{
			if ((G.arcs[u][w] != 0) && (visited[w] == 0))	//将u的全部未访问的邻接顶点入队
			{
				cout << G.vexs[w] << " ";
				visited[w] = 1;
				EnQueue(Q, w);	//w入队
			}
		}
	}
}


//队列初始化
Status InitQueue(SqQueue& Q)
{
	Q.base = new QElemType[MAXQSIZE];
	if (!Q.base)
		return ERROR;
	Q.front = 0;
	Q.rear = 0;
	return OK;
}

//循环队列入队
Status EnQueue(SqQueue& Q, QElemType e)
{
	if ((Q.rear + 1) % MAXQSIZE == Q.front)		//判断是否出现上溢
		return ERROR;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	return OK;
}

//循环队列出队
Status DeQueue(SqQueue& Q, QElemType& e)
{
	if (Q.front == Q.rear)	//判断是否出现下溢（队空）
		return ERROR;
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
	return OK;
}
