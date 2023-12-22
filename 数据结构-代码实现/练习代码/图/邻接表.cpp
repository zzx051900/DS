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
int visited[MVNum];

//顺序队列
typedef struct
{
	QElemType *base;//初始化动态分配存储空间
	int front;//头指针（实际是队头元素下标）
	int rear;//尾指针（实际是队尾元素下标）
}SqQueue;


typedef struct ArcNode	//边（弧）结点的结构类型
{
	int adjvex;	//该边所指向的顶点的位置
	struct ArcNode* nextarc;	//指向下一条边的指针

}ArcNode;

typedef struct VNode	//顶点的结构类型
{
	VerTexType data;	//顶点信息
	ArcNode* firstarc;	//指向第一条依附该结点的边的指针
}VNode, AdjList[MVNum];	//AdjList表示邻接表类型	 AdjList v; 相当于 VNode v[MVNum];

typedef struct
{
	AdjList vertices;	//顶点数组
	int vexnum, arcnum;	//顶点数和边（弧）数
}ALGraph;

//函数声明
void CreateUDG(ALGraph &G);	//创建邻接表
int LocateVex(ALGraph G, VerTexType v);	//查找顶点下标
void DFS(ALGraph G, int v);	//深度优先递归遍历
void BFS(ALGraph G, int v);	//广度优先非递归遍历
Status InitQueue(SqQueue& Q);	//队列初始化
Status EnQueue(SqQueue& Q, QElemType e);	//循环队列入队
Status DeQueue(SqQueue& Q, QElemType& e);	//循环队列出队

int main()
{
	ALGraph G;
	CreateUDG(G);

	for (int i = 0; i < G.vexnum; i++)
	{
		visited[i] = 0;
	}
	cout << "邻接表深度优先遍历序列：";
	DFS(G, 0);
	cout << endl;
	
	for (int i = 0; i < G.vexnum; i++)
	{
		visited[i] = 0;
	}
	cout << "邻接表广度优先遍历序列：";
	BFS(G, 0);
	cout << endl;

	system("pause");
	return 0;
}

void CreateUDG(ALGraph &G)
{
	cout << "输入总顶点数和总边数：";
	cin >> G.vexnum >> G.arcnum;	//输入总顶点数、总边数
	cout << "输入各顶点值：";
	for (int i = 0; i < G.vexnum; i++)
	{
		cin >> G.vertices[i].data;	//输入顶点值
		G.vertices[i].firstarc = NULL;	//初始化表头结点的指针域
	}
	cout << "输入一条边所依附的两个顶点：" << endl;
	for (int k = 0; k < G.arcnum; k++)
	{
		char v1, v2;
		cin >> v1 >> v2;	//输入一条边依附的两个顶点
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		ArcNode* p1 = new ArcNode;	//生成一个新的边结点
		p1->adjvex = j;	//邻接点序号为j
		p1->nextarc = G.vertices[i].firstarc;	//头插法插入结点
		G.vertices[i].firstarc = p1;	//将新结点p1插入顶点 vi 的边表头部
		//反过来还有一条边
		ArcNode* p2 = new ArcNode;	//生成一个新的边结点
		p2->adjvex = i;	//邻接点序号为i
		p2->nextarc = G.vertices[j].firstarc;	//头插法插入结点
		G.vertices[j].firstarc = p2;	//将新结点p2插入顶点 vj 的边表头部
	}
}

//查找顶点下标
int LocateVex(ALGraph G, VerTexType v)
{
	int i;
	for (i = 0; i < G.vexnum; i++)
	{
		if (v == G.vertices[i].data)
		{
			return i;
		}
	}
	return -1;
}

//深度优先递归遍历
void DFS(ALGraph G, int v)
{
	cout << G.vertices[v].data << " ";
	visited[v] = 1;	//记录他改为已被访问

	ArcNode *p = G.vertices[v].firstarc;	//定义一个指针指向顶点
	while (p != NULL)	//顶点有邻接顶点时
	{
		int j = p->adjvex;	//顶点的第一个邻接顶点
		if (visited[j] == 0)
		{
			DFS(G, j);
		}
		p = p->nextarc;	
	}
}

//广度优先遍历
void BFS(ALGraph G, int v)
{
	cout << G.vertices[v].data << " ";
	visited[v] = 1;
	SqQueue Q;
	InitQueue(Q);
	EnQueue(Q, v);

	while (Q.front != Q.rear)
	{
		int u = 0;
		DeQueue(Q, u);	//队头元素出队并置为u
		
		ArcNode *p = G.vertices[u].firstarc;
		while (p != NULL)
		{
			int j = p->adjvex;
			if (!visited[j])
			{
				cout << G.vertices[j].data << " ";
				visited[j] = 1;
				EnQueue(Q, j);	//j入队

			}
			p = p->nextarc;
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
