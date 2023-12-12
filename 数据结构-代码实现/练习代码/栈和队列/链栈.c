#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 10  //定义栈中元素的最大个数
#define OK 1	//成功标志
#define ERROR 0	//失败标志
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1

typedef int Status;	//Status 是函数的类型，其值是函数结果状态代码
typedef int SElemType;

typedef struct StackNode
{
	SElemType data;	//数据域
	struct StackNode *next;	//next域
}StackNode, *LinkStack;

//函数声明
void InitStack(LinkStack* S);	//链栈初始化（不带头结点）
Status stackEmpty(LinkStack S);	//判断链栈是否为空
Status Push(LinkStack* S, SElemType e);	//链栈的入栈
Status Pop(LinkStack* S, SElemType* e);	//链栈的出栈
SElemType GetTop(LinkStack S);	//取栈顶元素
void ShowLinkStack(LinkStack S);	//显示链栈

int main()
{
	int a = 0;
	int e = 0;
	LinkStack S;
	InitStack(&S);
	a = stackEmpty(S);
	if (a == 1)
	{
		printf("链栈为空\n");
	}
	else
	{
		printf("链栈非空\n");
	}
	ShowLinkStack(S);
	//依次入栈1~10
	for (int i = 1; i <= 10; i++)
	{
		Push(&S, i);
		printf("第 %d 个入栈的元素是 %d \n", i, i);
		a = stackEmpty(S);
		if (a == 1)
		{
			printf("栈空\n");
		}
		else
		{
			printf("栈非空\n");
		}
		printf("栈中元素为：");
		ShowLinkStack(S);
	}
	//依次出栈
	for (int i = 1; i <= 10; i++)
	{
		Pop(&S, &e);
		printf("第 %d 个出栈的元素是 %d \n", i, e);
		a = stackEmpty(S);
		if (a == 1)
		{
			printf("栈空\n");
		}
		else
		{
			printf("栈非空\n");
		}
		ShowLinkStack(S);
	}

	return 0;
}

//链栈初始化（不带头结点）
void InitStack(LinkStack* S)
{
	*S = NULL;//不需要头结点
}

//判断链栈是否为空
Status stackEmpty(LinkStack S)
{
	if (S == NULL)
		return TRUE;
	return FALSE;
}

//链栈的入栈
Status Push(LinkStack* S, SElemType e)
{
	StackNode* new = (StackNode*)malloc(sizeof(StackNode));
	new->data = e;
	new->next = *S;
	(*S) = new;
	return OK;
}

//链栈的出栈
Status Pop(LinkStack* S, SElemType* e)
{
	StackNode* p = *S;
	if ((*S) == NULL)			//判断链栈下溢
		return ERROR;
	*e = p->data;
	*S = p->next;
	free(p);					//释放栈顶空间
}

//取栈顶元素
SElemType GetTop(LinkStack S)
{
	if (S)
		return S->data;
}

//显示链栈
void ShowLinkStack(LinkStack S)
{
	if (S == NULL)
	{
		printf("链栈为空\n");
		return;
	}
	StackNode* p;
	p = S;
	while (p)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	putchar('\n');
	putchar('\n');
}