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

typedef struct StackNode
{
	SElemType data;	//������
	struct StackNode *next;	//next��
}StackNode, *LinkStack;

//��������
void InitStack(LinkStack* S);	//��ջ��ʼ��������ͷ��㣩
Status stackEmpty(LinkStack S);	//�ж���ջ�Ƿ�Ϊ��
Status Push(LinkStack* S, SElemType e);	//��ջ����ջ
Status Pop(LinkStack* S, SElemType* e);	//��ջ�ĳ�ջ
SElemType GetTop(LinkStack S);	//ȡջ��Ԫ��
void ShowLinkStack(LinkStack S);	//��ʾ��ջ

int main()
{
	int a = 0;
	int e = 0;
	LinkStack S;
	InitStack(&S);
	a = stackEmpty(S);
	if (a == 1)
	{
		printf("��ջΪ��\n");
	}
	else
	{
		printf("��ջ�ǿ�\n");
	}
	ShowLinkStack(S);
	//������ջ1~10
	for (int i = 1; i <= 10; i++)
	{
		Push(&S, i);
		printf("�� %d ����ջ��Ԫ���� %d \n", i, i);
		a = stackEmpty(S);
		if (a == 1)
		{
			printf("ջ��\n");
		}
		else
		{
			printf("ջ�ǿ�\n");
		}
		printf("ջ��Ԫ��Ϊ��");
		ShowLinkStack(S);
	}
	//���γ�ջ
	for (int i = 1; i <= 10; i++)
	{
		Pop(&S, &e);
		printf("�� %d ����ջ��Ԫ���� %d \n", i, e);
		a = stackEmpty(S);
		if (a == 1)
		{
			printf("ջ��\n");
		}
		else
		{
			printf("ջ�ǿ�\n");
		}
		ShowLinkStack(S);
	}

	return 0;
}

//��ջ��ʼ��������ͷ��㣩
void InitStack(LinkStack* S)
{
	*S = NULL;//����Ҫͷ���
}

//�ж���ջ�Ƿ�Ϊ��
Status stackEmpty(LinkStack S)
{
	if (S == NULL)
		return TRUE;
	return FALSE;
}

//��ջ����ջ
Status Push(LinkStack* S, SElemType e)
{
	StackNode* new = (StackNode*)malloc(sizeof(StackNode));
	new->data = e;
	new->next = *S;
	(*S) = new;
	return OK;
}

//��ջ�ĳ�ջ
Status Pop(LinkStack* S, SElemType* e)
{
	StackNode* p = *S;
	if ((*S) == NULL)			//�ж���ջ����
		return ERROR;
	*e = p->data;
	*S = p->next;
	free(p);					//�ͷ�ջ���ռ�
}

//ȡջ��Ԫ��
SElemType GetTop(LinkStack S)
{
	if (S)
		return S->data;
}

//��ʾ��ջ
void ShowLinkStack(LinkStack S)
{
	if (S == NULL)
	{
		printf("��ջΪ��\n");
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