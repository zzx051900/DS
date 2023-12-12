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

typedef struct
{
	SElemType *base;//栈底指针
	SElemType *top;//栈顶指针
	int stacksize;//栈可用最大容量
}SqStack;

//函数声明
Status InitSqStack(SqStack* S);	//顺序栈的初始化
Status IsEmptySqStack(SqStack S);	//判断顺序栈是否为空
Status IsFullSqStack(SqStack S);	//判断顺序栈是否已满
int StackLength(SqStack S);	//求顺序栈长度
Status ClearSqStack(SqStack* S);	//清空栈
Status DestroySqStack(SqStack* S);	//销毁栈
Status Push(SqStack* S, SElemType e);	//顺序栈的入栈
Status Pop(SqStack* S, SElemType* e);	//顺序栈的出栈
void ShowSqStack(SqStack S);	//栈显示函数
void test(SqStack *s);	//测试函数

int main()
{
	SqStack s;
	int e = 0;
	int a = 0;	//用于判断返回值真假
	int length = 0;

	InitSqStack(&s);	//顺序栈的初始化
	test(&s);
	

	//依次入栈1~10，10个元素
	for (int i = 1; i <= 10; i++)
	{
		Push(&s, i);
		test(&s);
	}

	//依次出栈1~10，10个元素
	for (int i = 1; i < 10; i++)
	{
		Pop(&s, &e);
		printf("第 %d 个弹出的元素为 %d \n", i, e);
		test(&s);
	}

	//依次入栈1~10，10个元素
	for (int i = 1; i <= 10; i++)
	{
		Push(&s, i);
	}
	ClearSqStack(&s);
	test(&s);

	return 0;
}

//顺序栈的初始化
Status InitSqStack(SqStack* S)
{
	S->base = (SElemType*)malloc(MAXSIZE * sizeof(SElemType));
	if (!S->base)			//S->base为NULL，开辟空间失败
		exit(OVERFLOW);
	S->top = S->base;
	S->stacksize = MAXSIZE;
	return OK;
}

//判断顺序栈是否为空
Status IsEmptySqStack(SqStack S)
{
	if (S.base == S.top)
		return TRUE;
	else
		return FALSE;
}

//判断顺序栈是否已满
Status IsFullSqStack(SqStack S)
{
	if (!S.base)
		return ERROR;
	if (S.top - S.base == S.stacksize)
		return TRUE;
	else
		return FALSE;
}

//求顺序栈长度
int StackLength(SqStack S)
{
	return (S.top - S.base);//涉及指针减指针这一特殊情况
}

//清空栈
Status ClearSqStack(SqStack* S)
{
	if (S->base)
		S->top = S->base;
	return OK;
}

//销毁栈
Status DestroySqStack(SqStack* S)
{
	if (!S->base)
		return ERROR;
	free(S->base);
	S->top = S->base = NULL;
	S->stacksize = 0;
	return OK;
}

//顺序栈的入栈
Status Push(SqStack* S, SElemType e)
{
	if (!S->base || S->top - S->base == S->stacksize)		//栈为NULL,或者上溢
		return ERROR;
	*(S->top) = e;
	S->top++;
	return OK;
}

//顺序栈的出栈
Status Pop(SqStack* S, SElemType* e)
{
	if (!S->base || S->top == S->base)						//栈为NULL,或者下溢
		return ERROR;
	S->top--;
	*e = *S->top;
	return OK;
}

//栈显示函数
void ShowSqStack(SqStack S)
{
	if (!S.base || S.top == S.base)
		printf("栈空!\n");
	SElemType* p = S.top;
	while (p != S.base)
	{
		p--;
		printf("%d ", *p);
	}
	putchar('\n');
}

//测试函数
void test(SqStack *s)
{
	int a = 0;
	int length = 0;
	SqStack m = *s;

	a = IsEmptySqStack(m);	//判断顺序栈是否为空
	if (a == 1)
	{
		printf("栈空\n");
	}
	else
	{
		printf("栈非空\n");
	}

	a = IsFullSqStack(m);	//判断顺序栈是否已满
	if (a == 1)
	{
		printf("栈满\n");
	}
	else
	{
		printf("栈非满\n");
	}

	length = StackLength(m);	//求顺序栈长度
	printf("栈的长度为 %d\n",length);

	ShowSqStack(m);	//栈显示函数
	printf("\n");
}