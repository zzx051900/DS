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

typedef struct
{
	QElemType *base;//��ʼ����̬����洢�ռ�
	int front;//ͷָ�루ʵ���Ƕ�ͷԪ���±꣩
	int rear;//βָ�루ʵ���Ƕ�βԪ���±꣩
}SqQueue;

//��������
Status InitSqQueue(SqQueue* Q);	//���г�ʼ��
int QueueLength(SqQueue Q);	//����г���
Status EnQueue(SqQueue* Q, QElemType e);	//ѭ���������
Status DeQueue(SqQueue* Q, QElemType* e);	//ѭ�����г���
QElemType GetHead(SqQueue Q);	//ȡ��ͷԪ�أ������ӣ�
Status DestoryQueue(SqQueue* Q);	//���ٶ���
void ShowSqQueue(SqQueue Q);	//��ʾ����

int main()
{
	int e = 0;
	SqQueue Q;
	InitSqQueue(&Q);
	printf("��ʱ��ͷԪ���� %d \n", GetHead(Q));
	printf("��ʱ�г���Ϊ %d \n", QueueLength(Q));
	printf("��ʱ�����е�Ԫ��Ϊ��");
	ShowSqQueue(Q);
	printf("\n");

	//�������1~5
	for (int i = 1; i <= 5; i++)
	{
		printf("�� %d ����ӵ�Ԫ���� %d \n", i, i);
		EnQueue(&Q, i);
		printf("��ʱ��ͷԪ���� %d \n", GetHead(Q));
		printf("��ʱ�г���Ϊ %d \n", QueueLength(Q));
		printf("��ʱ�����е�Ԫ��Ϊ��");
		ShowSqQueue(Q);
		printf("\n");
	}
	//���γ���1~5��Ԫ��
	for (int i = 1; i <= 5; i++)
	{
		DeQueue(&Q, &e);
		printf("�� %d �����ӵ�Ԫ���� %d \n", i, e);
		printf("��ʱ��ͷԪ���� %d \n", GetHead(Q));
		printf("��ʱ�г���Ϊ %d \n", QueueLength(Q));
		printf("��ʱ�����е�Ԫ��Ϊ��");
		ShowSqQueue(Q);
		printf("\n");
	}

	return 0;
}

//���г�ʼ��
Status InitSqQueue(SqQueue* Q)
{
	Q->base = (QElemType*)malloc(MAXQSIZE * sizeof(QElemType));
	if (!Q->base)
		return ERROR;
	Q->front = 0;
	Q->rear = 0;
	return OK;
}

//����г���
int QueueLength(SqQueue Q)
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

//ѭ���������
Status EnQueue(SqQueue* Q, QElemType e)
{
	if ((Q->rear + 1) % MAXQSIZE == Q->front)		//�ж��Ƿ��������
		return ERROR;
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
	return OK;
}

//ѭ�����г���
Status DeQueue(SqQueue* Q, QElemType* e)
{
	if (Q->front == Q->rear)	//�ж��Ƿ�������磨�ӿգ�
		return ERROR;
	*e = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXQSIZE;
	return OK;
}

//ȡ��ͷԪ�أ������ӣ�
QElemType GetHead(SqQueue Q)
{
	if (Q.front == Q.rear)
		return ERROR;
	return Q.base[Q.front];
}

//���ٶ���
Status DestoryQueue(SqQueue* Q)
{
	if (!(Q->base))
		return ERROR;
	free(Q->base);
	Q->base = NULL;
	Q->front = Q->rear = 0;
	return OK;
}

//��ʾ����
void ShowSqQueue(SqQueue Q)
{
	if (Q.front == Q.rear)
	{
		printf("����Ϊ��\n");
		return;
	}
	while (Q.rear != Q.front)
	{
		printf("%d ", Q.base[Q.front]);
		Q.front = (Q.front + 1) % MAXQSIZE;	//����ֱ��ʹ�ö�ͷָ���ƶ�����Ϊ����ֵ���ݣ�����ı�ԭ�����еĶ�ͷָ��
	}
	putchar('\n');
}