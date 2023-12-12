#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 10  //����ջ��Ԫ�ص�������
#define OK 1	//�ɹ���־
#define ERROR 0	//ʧ�ܱ�־
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1

typedef int Status;	//Status �Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int SElemType;	

typedef struct
{
	SElemType *base;//ջ��ָ��
	SElemType *top;//ջ��ָ��
	int stacksize;//ջ�����������
}SqStack;

//��������
Status InitSqStack(SqStack* S);	//˳��ջ�ĳ�ʼ��
Status IsEmptySqStack(SqStack S);	//�ж�˳��ջ�Ƿ�Ϊ��
Status IsFullSqStack(SqStack S);	//�ж�˳��ջ�Ƿ�����
int StackLength(SqStack S);	//��˳��ջ����
Status ClearSqStack(SqStack* S);	//���ջ
Status DestroySqStack(SqStack* S);	//����ջ
Status Push(SqStack* S, SElemType e);	//˳��ջ����ջ
Status Pop(SqStack* S, SElemType* e);	//˳��ջ�ĳ�ջ
void ShowSqStack(SqStack S);	//ջ��ʾ����
void test(SqStack *s);	//���Ժ���

int main()
{
	SqStack s;
	int e = 0;
	int a = 0;	//�����жϷ���ֵ���
	int length = 0;

	InitSqStack(&s);	//˳��ջ�ĳ�ʼ��
	test(&s);
	

	//������ջ1~10��10��Ԫ��
	for (int i = 1; i <= 10; i++)
	{
		Push(&s, i);
		test(&s);
	}

	//���γ�ջ1~10��10��Ԫ��
	for (int i = 1; i < 10; i++)
	{
		Pop(&s, &e);
		printf("�� %d ��������Ԫ��Ϊ %d \n", i, e);
		test(&s);
	}

	//������ջ1~10��10��Ԫ��
	for (int i = 1; i <= 10; i++)
	{
		Push(&s, i);
	}
	ClearSqStack(&s);
	test(&s);

	return 0;
}

//˳��ջ�ĳ�ʼ��
Status InitSqStack(SqStack* S)
{
	S->base = (SElemType*)malloc(MAXSIZE * sizeof(SElemType));
	if (!S->base)			//S->baseΪNULL�����ٿռ�ʧ��
		exit(OVERFLOW);
	S->top = S->base;
	S->stacksize = MAXSIZE;
	return OK;
}

//�ж�˳��ջ�Ƿ�Ϊ��
Status IsEmptySqStack(SqStack S)
{
	if (S.base == S.top)
		return TRUE;
	else
		return FALSE;
}

//�ж�˳��ջ�Ƿ�����
Status IsFullSqStack(SqStack S)
{
	if (!S.base)
		return ERROR;
	if (S.top - S.base == S.stacksize)
		return TRUE;
	else
		return FALSE;
}

//��˳��ջ����
int StackLength(SqStack S)
{
	return (S.top - S.base);//�漰ָ���ָ����һ�������
}

//���ջ
Status ClearSqStack(SqStack* S)
{
	if (S->base)
		S->top = S->base;
	return OK;
}

//����ջ
Status DestroySqStack(SqStack* S)
{
	if (!S->base)
		return ERROR;
	free(S->base);
	S->top = S->base = NULL;
	S->stacksize = 0;
	return OK;
}

//˳��ջ����ջ
Status Push(SqStack* S, SElemType e)
{
	if (!S->base || S->top - S->base == S->stacksize)		//ջΪNULL,��������
		return ERROR;
	*(S->top) = e;
	S->top++;
	return OK;
}

//˳��ջ�ĳ�ջ
Status Pop(SqStack* S, SElemType* e)
{
	if (!S->base || S->top == S->base)						//ջΪNULL,��������
		return ERROR;
	S->top--;
	*e = *S->top;
	return OK;
}

//ջ��ʾ����
void ShowSqStack(SqStack S)
{
	if (!S.base || S.top == S.base)
		printf("ջ��!\n");
	SElemType* p = S.top;
	while (p != S.base)
	{
		p--;
		printf("%d ", *p);
	}
	putchar('\n');
}

//���Ժ���
void test(SqStack *s)
{
	int a = 0;
	int length = 0;
	SqStack m = *s;

	a = IsEmptySqStack(m);	//�ж�˳��ջ�Ƿ�Ϊ��
	if (a == 1)
	{
		printf("ջ��\n");
	}
	else
	{
		printf("ջ�ǿ�\n");
	}

	a = IsFullSqStack(m);	//�ж�˳��ջ�Ƿ�����
	if (a == 1)
	{
		printf("ջ��\n");
	}
	else
	{
		printf("ջ����\n");
	}

	length = StackLength(m);	//��˳��ջ����
	printf("ջ�ĳ���Ϊ %d\n",length);

	ShowSqStack(m);	//ջ��ʾ����
	printf("\n");
}