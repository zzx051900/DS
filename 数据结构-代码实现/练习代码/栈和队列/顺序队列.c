#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAXQSIZE 50  //定义队列中元素的最大个数
#define OK 1	//成功标志
#define ERROR 0	//失败标志
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1

typedef int Status;	//Status 是函数的类型，其值是函数结果状态代码
typedef int QElemType;

typedef struct
{
	QElemType *base;//初始化动态分配存储空间
	int front;//头指针（实际是队头元素下标）
	int rear;//尾指针（实际是队尾元素下标）
}SqQueue;

//函数声明
Status InitSqQueue(SqQueue* Q);	//队列初始化
int QueueLength(SqQueue Q);	//求队列长度
Status EnQueue(SqQueue* Q, QElemType e);	//循环队列入队
Status DeQueue(SqQueue* Q, QElemType* e);	//循环队列出队
QElemType GetHead(SqQueue Q);	//取队头元素（不出队）
Status DestoryQueue(SqQueue* Q);	//销毁队列
void ShowSqQueue(SqQueue Q);	//显示队列

int main()
{
	int e = 0;
	SqQueue Q;
	InitSqQueue(&Q);
	printf("此时队头元素是 %d \n", GetHead(Q));
	printf("此时列长度为 %d \n", QueueLength(Q));
	printf("此时队列中的元素为：");
	ShowSqQueue(Q);
	printf("\n");

	//依次入队1~5
	for (int i = 1; i <= 5; i++)
	{
		printf("第 %d 个入队的元素是 %d \n", i, i);
		EnQueue(&Q, i);
		printf("此时队头元素是 %d \n", GetHead(Q));
		printf("此时列长度为 %d \n", QueueLength(Q));
		printf("此时队列中的元素为：");
		ShowSqQueue(Q);
		printf("\n");
	}
	//依次出队1~5个元素
	for (int i = 1; i <= 5; i++)
	{
		DeQueue(&Q, &e);
		printf("第 %d 个出队的元素是 %d \n", i, e);
		printf("此时队头元素是 %d \n", GetHead(Q));
		printf("此时列长度为 %d \n", QueueLength(Q));
		printf("此时队列中的元素为：");
		ShowSqQueue(Q);
		printf("\n");
	}

	return 0;
}

//队列初始化
Status InitSqQueue(SqQueue* Q)
{
	Q->base = (QElemType*)malloc(MAXQSIZE * sizeof(QElemType));
	if (!Q->base)
		return ERROR;
	Q->front = 0;
	Q->rear = 0;
	return OK;
}

//求队列长度
int QueueLength(SqQueue Q)
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

//循环队列入队
Status EnQueue(SqQueue* Q, QElemType e)
{
	if ((Q->rear + 1) % MAXQSIZE == Q->front)		//判断是否出现上溢
		return ERROR;
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
	return OK;
}

//循环队列出队
Status DeQueue(SqQueue* Q, QElemType* e)
{
	if (Q->front == Q->rear)	//判断是否出现下溢（队空）
		return ERROR;
	*e = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXQSIZE;
	return OK;
}

//取队头元素（不出队）
QElemType GetHead(SqQueue Q)
{
	if (Q.front == Q.rear)
		return ERROR;
	return Q.base[Q.front];
}

//销毁队列
Status DestoryQueue(SqQueue* Q)
{
	if (!(Q->base))
		return ERROR;
	free(Q->base);
	Q->base = NULL;
	Q->front = Q->rear = 0;
	return OK;
}

//显示队列
void ShowSqQueue(SqQueue Q)
{
	if (Q.front == Q.rear)
	{
		printf("队列为空\n");
		return;
	}
	while (Q.rear != Q.front)
	{
		printf("%d ", Q.base[Q.front]);
		Q.front = (Q.front + 1) % MAXQSIZE;	//可以直接使用队头指针移动，因为这是值传递，不会改变原队列中的队头指针
	}
	putchar('\n');
}