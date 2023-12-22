#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

#define MaxInt 32767	//��ʾ����ֵ��
#define MVNum 100	//��󶥵���
#define MAXQSIZE 50  //���������Ԫ�ص�������
#define OK 1	//�ɹ���־
#define ERROR 0	//ʧ�ܱ�־
#define TRUE 1
#define FALSE 0
typedef char VerTexType;	//�趥�����������Ϊ�ַ���
typedef int ArcType;	//����ߵ�Ȩֵ����Ϊ����
typedef int Status;	//Status �Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int QElemType;
int visited[MVNum];

//˳�����
typedef struct
{
	QElemType *base;//��ʼ����̬����洢�ռ�
	int front;//ͷָ�루ʵ���Ƕ�ͷԪ���±꣩
	int rear;//βָ�루ʵ���Ƕ�βԪ���±꣩
}SqQueue;


typedef struct ArcNode	//�ߣ��������Ľṹ����
{
	int adjvex;	//�ñ���ָ��Ķ����λ��
	struct ArcNode* nextarc;	//ָ����һ���ߵ�ָ��

}ArcNode;

typedef struct VNode	//����Ľṹ����
{
	VerTexType data;	//������Ϣ
	ArcNode* firstarc;	//ָ���һ�������ý��ıߵ�ָ��
}VNode, AdjList[MVNum];	//AdjList��ʾ�ڽӱ�����	 AdjList v; �൱�� VNode v[MVNum];

typedef struct
{
	AdjList vertices;	//��������
	int vexnum, arcnum;	//�������ͱߣ�������
}ALGraph;

//��������
void CreateUDG(ALGraph &G);	//�����ڽӱ�
int LocateVex(ALGraph G, VerTexType v);	//���Ҷ����±�
void DFS(ALGraph G, int v);	//������ȵݹ����
void BFS(ALGraph G, int v);	//������ȷǵݹ����
Status InitQueue(SqQueue& Q);	//���г�ʼ��
Status EnQueue(SqQueue& Q, QElemType e);	//ѭ���������
Status DeQueue(SqQueue& Q, QElemType& e);	//ѭ�����г���

int main()
{
	ALGraph G;
	CreateUDG(G);

	for (int i = 0; i < G.vexnum; i++)
	{
		visited[i] = 0;
	}
	cout << "�ڽӱ�������ȱ������У�";
	DFS(G, 0);
	cout << endl;
	
	for (int i = 0; i < G.vexnum; i++)
	{
		visited[i] = 0;
	}
	cout << "�ڽӱ������ȱ������У�";
	BFS(G, 0);
	cout << endl;

	system("pause");
	return 0;
}

void CreateUDG(ALGraph &G)
{
	cout << "�����ܶ��������ܱ�����";
	cin >> G.vexnum >> G.arcnum;	//�����ܶ��������ܱ���
	cout << "���������ֵ��";
	for (int i = 0; i < G.vexnum; i++)
	{
		cin >> G.vertices[i].data;	//���붥��ֵ
		G.vertices[i].firstarc = NULL;	//��ʼ����ͷ����ָ����
	}
	cout << "����һ�������������������㣺" << endl;
	for (int k = 0; k < G.arcnum; k++)
	{
		char v1, v2;
		cin >> v1 >> v2;	//����һ������������������
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);
		ArcNode* p1 = new ArcNode;	//����һ���µı߽��
		p1->adjvex = j;	//�ڽӵ����Ϊj
		p1->nextarc = G.vertices[i].firstarc;	//ͷ�巨������
		G.vertices[i].firstarc = p1;	//���½��p1���붥�� vi �ı߱�ͷ��
		//����������һ����
		ArcNode* p2 = new ArcNode;	//����һ���µı߽��
		p2->adjvex = i;	//�ڽӵ����Ϊi
		p2->nextarc = G.vertices[j].firstarc;	//ͷ�巨������
		G.vertices[j].firstarc = p2;	//���½��p2���붥�� vj �ı߱�ͷ��
	}
}

//���Ҷ����±�
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

//������ȵݹ����
void DFS(ALGraph G, int v)
{
	cout << G.vertices[v].data << " ";
	visited[v] = 1;	//��¼����Ϊ�ѱ�����

	ArcNode *p = G.vertices[v].firstarc;	//����һ��ָ��ָ�򶥵�
	while (p != NULL)	//�������ڽӶ���ʱ
	{
		int j = p->adjvex;	//����ĵ�һ���ڽӶ���
		if (visited[j] == 0)
		{
			DFS(G, j);
		}
		p = p->nextarc;	
	}
}

//������ȱ���
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
		DeQueue(Q, u);	//��ͷԪ�س��Ӳ���Ϊu
		
		ArcNode *p = G.vertices[u].firstarc;
		while (p != NULL)
		{
			int j = p->adjvex;
			if (!visited[j])
			{
				cout << G.vertices[j].data << " ";
				visited[j] = 1;
				EnQueue(Q, j);	//j���

			}
			p = p->nextarc;
		}
	}
}

//���г�ʼ��
Status InitQueue(SqQueue& Q)
{
	Q.base = new QElemType[MAXQSIZE];
	if (!Q.base)
		return ERROR;
	Q.front = 0;
	Q.rear = 0;
	return OK;
}

//ѭ���������
Status EnQueue(SqQueue& Q, QElemType e)
{
	if ((Q.rear + 1) % MAXQSIZE == Q.front)		//�ж��Ƿ��������
		return ERROR;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	return OK;
}

//ѭ�����г���
Status DeQueue(SqQueue& Q, QElemType& e)
{
	if (Q.front == Q.rear)	//�ж��Ƿ�������磨�ӿգ�
		return ERROR;
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
	return OK;
}
