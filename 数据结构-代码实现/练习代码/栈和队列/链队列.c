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

typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;//链队列结点，链队列指针
typedef struct

{
	QueuePtr front;//队头指针
	QueuePtr rear;//队尾指针
}LinkQueue;//链队列

//函数声明
Status InitLinkQueue(LinkQueue* Q);	//链队列初始化
Status DestoryLinkQueue(LinkQueue* Q);	//链队列销毁
Status EnQueue(LinkQueue* Q, QElemType e);	//链队列入队
Status DeLinkQueue(LinkQueue* Q, QElemType* e);	//链队列出队
Status GetHead(LinkQueue Q, QElemType *e);	//求队头元素
void ShowLinkQueue(LinkQueue Q);	//显示链队列

int main()
{
	int e = 0;
	int a = 0;
	LinkQueue Q;
	InitLinkQueue(&Q);
	a = GetHead(Q, &e);
	if (a == 0)
	{
		printf("此时链表为空\n");
	}
	else
	{
		printf("此时队头元素为：%d \n", e);
	}	
	printf("此时链队列中元素为：");
	ShowLinkQueue(Q);
	printf("\n");

	//依次入队1~5
	for (int i = 1; i <= 5; i++)
	{
		printf("第 %d 个入队的元素是 %d \n", i, i);
		EnQueue(&Q, i);
		a = GetHead(Q, &e);
		if (a == 0)
		{
			printf("此时链表为空\n");
		}
		else
		{
			printf("此时队头元素为：%d \n", e);
		}
		printf("此时链队列中元素为：");
		ShowLinkQueue(Q);
		printf("\n");
	}
	//依次出队1~5个元素
	for (int i = 1; i <= 5; i++)
	{
		DeLinkQueue(&Q, &e);
		printf("第 %d 个出队的元素是 %d \n", i, e);
		a = GetHead(Q, &e);
		if (a == 0)
		{
			printf("此时链表为空\n");
		}
		else
		{
			printf("此时队头元素为：%d \n", e);
		}
		printf("此时链队列中元素为：");
		ShowLinkQueue(Q);
		printf("\n");
	}


	return 0;
}

//链队列初始化
Status InitLinkQueue(LinkQueue* Q)
{
	Q->front = (QNode*)malloc(sizeof(QNode));
	Q->rear = Q->front;
	if (!Q->rear)
		return ERROR;
	Q->rear->next = NULL;
	return OK;
}

//链队列销毁
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

//链队列入队
Status EnQueue(LinkQueue* Q, QElemType e)
{
	QNode* p = (QNode*)malloc(sizeof(QNode));
	p->data = e;
	p->next = Q->rear->next;	//尾指针的next不就是NULL吗，这一步可以直接改成 p->next = NULL; 吗
	Q->rear->next = p;
	Q->rear = p;		//更新队列尾指针
	return OK;
}

//链队列出队
Status DeLinkQueue(LinkQueue* Q, QElemType* e)
{
	QNode* p = Q->front->next;	//指向首元结点，用于暂时保存首元结点，之后释放
	if (Q->front == Q->rear)	//判断队空
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

//求队头元素
Status GetHead(LinkQueue Q, QElemType *e)
{
	if (Q.front == Q.rear)	//判断队空
		return ERROR;
	*e = Q.front->next->data;
	return OK;
}

//显示链队列
void ShowLinkQueue(LinkQueue Q)
{
	if (Q.front == Q.rear)
	{
		printf("链队列为空\n");
		return;
	}
	Q.front = Q.front->next;	//跳过头结点，移动到首元结点
	while (Q.front)
	{
		printf("%d ", Q.front->data);
		Q.front = Q.front->next;
	}
	putchar('\n');
	return OK;
}