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

//˳�����
typedef struct
{
	QElemType *base;//��ʼ����̬����洢�ռ�
	int front;//ͷָ�루ʵ���Ƕ�ͷԪ���±꣩
	int rear;//βָ�루ʵ���Ƕ�βԪ���±꣩
}SqQueue;

//ͼ
typedef struct
{
	VerTexType vexs[MVNum];	//�����
	ArcType arcs[MVNum][MVNum];	//�ڽӾ���
	int vexnum, arcnum;	//ͼ�ĵ�ǰ�������ͱ���
}AMGraph;	//Adjacency Matrix Graph

//��������
int LocateVex(AMGraph G, VerTexType v);	//���Ҷ����±�
void CreateUDN(AMGraph &G);	//�����ڽӾ���
void DFS(AMGraph G, int v);	//������ȵݹ����
void BFS(AMGraph G, int v);	//������ȷǵݹ����
Status InitQueue(SqQueue& Q);	//���г�ʼ��
Status EnQueue(SqQueue& Q, QElemType e);	//ѭ���������
Status DeQueue(SqQueue& Q, QElemType& e);	//ѭ�����г���


int visited[MVNum];

int main()
{
	AMGraph G;
	CreateUDN(G);

	cout << "�ڽӾ���" << endl;
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j < G.vexnum; j++)
		{
			cout << G.arcs[i][j] << " ";
		}
		cout << endl;
	}
	cout << "�ڽӾ���������ȱ������У�";
	DFS(G, 0);
	cout << endl;

	for (int i = 0; i < G.vexnum; i++)	//����־������0
	{
		visited[i] = 0;	
	}
	cout << "�ڽӾ��������ȱ������У�";
	BFS(G, 0);
	cout << endl;
	
	system("pause");
	return 0;
}


//���Ҷ����±�
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
	cout << "�����ܶ��������ܱ�����";
	cin >> G.vexnum >> G.arcnum;	//�����ܶ��������ܱ���
	cout << "�������붥�����Ϣ��";
	for (int i = 0; i < G.vexnum; i++)
	{
		cin >> G.vexs[i];	//������������Ϣ
		visited[i] = 0;	//��ʼ����־����Ϊ0
	}
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j] = 0;	//��ʼ��ÿ����ȨֵΪ0
		}
	}
	cout << "����һ�������������������㼰�ߵ�Ȩֵ��";
	for (int k = 0; k < G.arcnum; k++)
	{
		VerTexType v1, v2;
		int w;
		cin >> v1 >> v2 >> w;	//����һ�����������Ķ��㼰�ߵ�Ȩֵ
		int i = LocateVex(G, v1);
		int j = LocateVex(G, v2);	//ȷ��v1��v2��G�е�λ��
		G.arcs[i][j] = w;	//��<v1,v2>��Ȩ��Ϊw
		G.arcs[j][i] = w;	//����ԳƱߵ�ȨֵҲ��Ϊw
	}

}

//������ȵݹ����
void DFS(AMGraph G, int v)
{
	cout << G.vexs[v] << " ";
	visited[v] = 1;	//��¼����Ϊ�ѱ�����
	for (int w = 0; w < G.vexnum; w++)
	{
		if ((G.arcs[v][w] != 0) && (visited[w] == 0))	//�����ڣ���δ�����ʵ��ڽӶ���
		{
			DFS(G, w);	//w��v���ڽӶ��㣬��wδ�����ʣ���ݹ����DFS
		}
	}
}

//������ȷǵݹ����
void BFS(AMGraph G, int v)
{
	cout << G.vexs[v] << " ";	//�����һ����������
	visited[v] = 1;	//��¼����Ϊ�ѱ�����
	SqQueue Q;
	InitQueue(Q);	//��������Q��ʼ�����ÿ�
	EnQueue(Q, v);	//v���

	while (Q.front != Q.rear)	//���зǿ�
	{
		int u = 0;
		DeQueue(Q, u);	//��ͷԪ�س��Ӳ���Ϊu

		int w = 0;
		for (int i = 0; i < G.vexnum; i++)
		{
			if ((G.arcs[u][i] != 0) && (visited[i] == 0))
			{
				w = i;	//�ҵ�u�ĵ�һ��δ�����ʵ��ڽӶ��㣬Ȼ��ֱ������
				break;
			}
		}
		for (; w < G.vexnum; w++)
		{
			if ((G.arcs[u][w] != 0) && (visited[w] == 0))	//��u��ȫ��δ���ʵ��ڽӶ������
			{
				cout << G.vexs[w] << " ";
				visited[w] = 1;
				EnQueue(Q, w);	//w���
			}
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
