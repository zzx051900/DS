#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>

#define OK 1	//�ɹ���־
#define  ERROR 0	//ʧ�ܱ�־

typedef int Status;	//Status �Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int TElemType;

typedef struct BiTNode
{
	TElemType data;
	struct BiTNode *lchild, *rchild;//���Һ���ָ��
}BiTNode, *BiTree;

//��������
Status CreateBiTree(BiTree* T);	//�����������������
Status PreOrderTraverse(BiTree T);	//�������������
Status InOrderTraverse(BiTree T);	//�������������
Status PostOrderTraverse(BiTree T);	//�������������
int Copy(BiTree T, BiTree* NewT);	//���ƶ�����
int Depth(BiTree T);	//������������
int NodeCount(BiTree T);	//����������������
int LeafCount(BiTree T);	//���������Ҷ�ӽ������

int main()
{
	BiTree T;
	BiTree NewT;
	int a = 0;

	CreateBiTree(&T);

	printf("����������У�");
	PreOrderTraverse(T);
	printf("\n");
	printf("����������У�");
	InOrderTraverse(T);
	printf("\n");
	printf("����������У�");
	PostOrderTraverse(T);
	printf("\n");

	a = Depth(T);
	printf("����������ȣ�%d\n", a);
	a = NodeCount(T);
	printf("�������Ľ��������%d\n", a);
	a = LeafCount(T);
	printf("������Ҷ�ӽ��������%d\n", a);

	Copy(T, &NewT);
	printf("���ƶ�����������������У�");
	PreOrderTraverse(NewT);
	printf("\n");

	return 0;
}

//�����������������
/*
�������ָ��Ҳû���⣬Ҳ����ʹ��C++�е����ã�Ҳ����ʹ�ý�����ֵ����Ϊһ��ָ��ķ�ʽ
*/
Status CreateBiTree(BiTree* T)
{
	int a;
	scanf("%d", &a);
	if (a == -1)
	{
		(*T) = NULL;
		return OK;
	}
	(*T) = (BiTNode*)malloc(sizeof(BiTNode));
	(*T)->data = a;
	CreateBiTree(&(*T)->lchild); //����������
	CreateBiTree(&(*T)->rchild); //����������

	return OK;
}

//�������������
Status PreOrderTraverse(BiTree T)
{
	if (T == NULL)	//�ն�����
		return OK;
	printf("%d ", T->data);
	PreOrderTraverse(T->lchild);//�ݹ����������
	PreOrderTraverse(T->rchild);//�ݹ����������
	return OK;
}

//�������������
Status InOrderTraverse(BiTree T)
{
	if (T == NULL)
		return OK;//�ն�����
	InOrderTraverse(T->lchild);//�ݹ����������
	printf("%d ", T->data);
	InOrderTraverse(T->rchild);//�ݹ����������
	return OK;
}

//�������������
Status PostOrderTraverse(BiTree T)
{
	if (T == NULL)
		return OK;//�ն�����
	PostOrderTraverse(T->lchild);//�ݹ����������
	PostOrderTraverse(T->rchild);//�ݹ����������
	printf("%d ", T->data);
	return OK;
}

//���ƶ�����
int Copy(BiTree T, BiTree* NewT)
{
	if (T == NULL)	//����ǿ������ݹ����
	{
		*NewT = NULL;
		return 0;
	}
	else
	{
		*NewT = (BiTNode*)malloc(sizeof(BiTNode));	//�����½��ռ�
		(*NewT)->data = T->data;	//���Ƹ����
		Copy(T->lchild, &((*NewT)->lchild));	//�ݹ鸴��������
		Copy(T->rchild, &((*NewT)->rchild));	//�ݹ鸴��������
	}
	return OK;
}

//������������
int Depth(BiTree T)
{
	int m = 0, n = 0;
	if (T == NULL)
		return 0;
	m = Depth(T->lchild);	//����������
	n = Depth(T->rchild);	//����������
	if (m>n)
		return m + 1;
	return n + 1;
}

//����������������
int NodeCount(BiTree T)
{
	if (T == NULL)
		return 0;
	return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;//��һ�ӵ��ǵ�ǰ��Ϊ�����Ľ�㱾��
}

//���������Ҷ�ӽ������
int LeafCount(BiTree T)
{
	if (T == NULL)
		return 0;
	if (T->lchild == NULL && T->rchild == NULL)
		return 1;//��Ҷ�ӽڵ�
	return LeafCount(T->lchild) + LeafCount(T->rchild);	//����Ҷ�ӽڵ㣬��ֱ�ͳ����������Ҷ�ӽ�����
}