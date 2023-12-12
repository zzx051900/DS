#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAXQSIZE 50  //���������Ԫ�ص�������
#define OK 1	//�ɹ���־
#define ERROR 0	//ʧ�ܱ�־
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1

typedef int Status;	//Status �Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int QElemType;

typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;//�����н�㣬������ָ��
typedef struct

{
	QueuePtr front;//��ͷָ��
	QueuePtr rear;//��βָ��
}LinkQueue;//������

//��������
Status InitLinkQueue(LinkQueue* Q);	//�����г�ʼ��
Status DestoryLinkQueue(LinkQueue* Q);	//����������
Status EnQueue(LinkQueue* Q, QElemType e);	//���������
Status DeLinkQueue(LinkQueue* Q, QElemType* e);	//�����г���
Status GetHead(LinkQueue Q, QElemType *e);	//���ͷԪ��
void ShowLinkQueue(LinkQueue Q);	//��ʾ������

int main()
{
	int e = 0;
	int a = 0;
	LinkQueue Q;
	InitLinkQueue(&Q);
	a = GetHead(Q, &e);
	if (a == 0)
	{
		printf("��ʱ����Ϊ��\n");
	}
	else
	{
		printf("��ʱ��ͷԪ��Ϊ��%d \n", e);
	}	
	printf("��ʱ��������Ԫ��Ϊ��");
	ShowLinkQueue(Q);
	printf("\n");

	//�������1~5
	for (int i = 1; i <= 5; i++)
	{
		printf("�� %d ����ӵ�Ԫ���� %d \n", i, i);
		EnQueue(&Q, i);
		a = GetHead(Q, &e);
		if (a == 0)
		{
			printf("��ʱ����Ϊ��\n");
		}
		else
		{
			printf("��ʱ��ͷԪ��Ϊ��%d \n", e);
		}
		printf("��ʱ��������Ԫ��Ϊ��");
		ShowLinkQueue(Q);
		printf("\n");
	}
	//���γ���1~5��Ԫ��
	for (int i = 1; i <= 5; i++)
	{
		DeLinkQueue(&Q, &e);
		printf("�� %d �����ӵ�Ԫ���� %d \n", i, e);
		a = GetHead(Q, &e);
		if (a == 0)
		{
			printf("��ʱ����Ϊ��\n");
		}
		else
		{
			printf("��ʱ��ͷԪ��Ϊ��%d \n", e);
		}
		printf("��ʱ��������Ԫ��Ϊ��");
		ShowLinkQueue(Q);
		printf("\n");
	}


	return 0;
}

//�����г�ʼ��
Status InitLinkQueue(LinkQueue* Q)
{
	Q->front = (QNode*)malloc(sizeof(QNode));
	Q->rear = Q->front;
	if (!Q->rear)
		return ERROR;
	Q->rear->next = NULL;
	return OK;
}

//����������
Status DestoryLinkQueue(LinkQueue* Q)
{
	QNode* p;
	while (Q->front)
	{
		p = Q->front->next;
		free(Q->front);
		Q->front = p;
	}
	return OK;
}

//���������
Status EnQueue(LinkQueue* Q, QElemType e)
{
	QNode* p = (QNode*)malloc(sizeof(QNode));
	p->data = e;
	p->next = Q->rear->next;	//βָ���next������NULL����һ������ֱ�Ӹĳ� p->next = NULL; ��
	Q->rear->next = p;
	Q->rear = p;		//���¶���βָ��
	return OK;
}

//�����г���
Status DeLinkQueue(LinkQueue* Q, QElemType* e)
{
	QNode* p = Q->front->next;	//ָ����Ԫ��㣬������ʱ������Ԫ��㣬֮���ͷ�
	if (Q->front == Q->rear)	//�ж϶ӿ�
		return ERROR;	
	*e = p->data;
	Q->front->next = p->next;
	if (Q->rear == p)
	{
		Q->rear = Q->front;	
	}		
	free(p);
	return OK;
}

//���ͷԪ��
Status GetHead(LinkQueue Q, QElemType *e)
{
	if (Q.front == Q.rear)	//�ж϶ӿ�
		return ERROR;
	*e = Q.front->next->data;
	return OK;
}

//��ʾ������
void ShowLinkQueue(LinkQueue Q)
{
	if (Q.front == Q.rear)
	{
		printf("������Ϊ��\n");
		return;
	}
	Q.front = Q.front->next;	//����ͷ��㣬�ƶ�����Ԫ���
	while (Q.front)
	{
		printf("%d ", Q.front->data);
		Q.front = Q.front->next;
	}
	putchar('\n');
	return OK;
}