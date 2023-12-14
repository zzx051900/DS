#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>

#define OK 1	//成功标志
#define  ERROR 0	//失败标志

typedef int Status;	//Status 是函数的类型，其值是函数结果状态代码
typedef int TElemType;

typedef struct BiTNode
{
	TElemType data;
	struct BiTNode *lchild, *rchild;//左右孩子指针
}BiTNode, *BiTree;

//函数声明
Status CreateBiTree(BiTree* T);	//先序遍历建立二叉树
Status PreOrderTraverse(BiTree T);	//先序遍历二叉树
Status InOrderTraverse(BiTree T);	//中序遍历二叉树
Status PostOrderTraverse(BiTree T);	//后序遍历二叉树
int Copy(BiTree T, BiTree* NewT);	//复制二叉树
int Depth(BiTree T);	//计算二叉树深度
int NodeCount(BiTree T);	//计算二叉树结点总数
int LeafCount(BiTree T);	//计算二叉树叶子结点总数

int main()
{
	BiTree T;
	BiTree NewT;
	int a = 0;

	CreateBiTree(&T);

	printf("先序遍历序列：");
	PreOrderTraverse(T);
	printf("\n");
	printf("中序遍历序列：");
	InOrderTraverse(T);
	printf("\n");
	printf("后序遍历序列：");
	PostOrderTraverse(T);
	printf("\n");

	a = Depth(T);
	printf("二叉树的深度：%d\n", a);
	a = NodeCount(T);
	printf("二叉树的结点总数：%d\n", a);
	a = LeafCount(T);
	printf("二叉树叶子结点总数：%d\n", a);

	Copy(T, &NewT);
	printf("复制二叉树的先序遍历序列：");
	PreOrderTraverse(NewT);
	printf("\n");

	return 0;
}

//先序遍历建立二叉树
/*
这里二级指针也没问题，也可以使用C++中的引用，也可以使用将返回值设置为一级指针的方式
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
	CreateBiTree(&(*T)->lchild); //创建左子树
	CreateBiTree(&(*T)->rchild); //创建右子树

	return OK;
}

//先序遍历二叉树
Status PreOrderTraverse(BiTree T)
{
	if (T == NULL)	//空二叉树
		return OK;
	printf("%d ", T->data);
	PreOrderTraverse(T->lchild);//递归遍历左子树
	PreOrderTraverse(T->rchild);//递归遍历右子树
	return OK;
}

//中序遍历二叉树
Status InOrderTraverse(BiTree T)
{
	if (T == NULL)
		return OK;//空二叉树
	InOrderTraverse(T->lchild);//递归遍历左子树
	printf("%d ", T->data);
	InOrderTraverse(T->rchild);//递归遍历右子树
	return OK;
}

//后序遍历二叉树
Status PostOrderTraverse(BiTree T)
{
	if (T == NULL)
		return OK;//空二叉树
	PostOrderTraverse(T->lchild);//递归遍历左子树
	PostOrderTraverse(T->rchild);//递归遍历右子树
	printf("%d ", T->data);
	return OK;
}

//复制二叉树
int Copy(BiTree T, BiTree* NewT)
{
	if (T == NULL)	//如果是空树，递归结束
	{
		*NewT = NULL;
		return 0;
	}
	else
	{
		*NewT = (BiTNode*)malloc(sizeof(BiTNode));	//申请新结点空间
		(*NewT)->data = T->data;	//复制根结点
		Copy(T->lchild, &((*NewT)->lchild));	//递归复制左子树
		Copy(T->rchild, &((*NewT)->rchild));	//递归复制右子树
	}
	return OK;
}

//计算二叉树深度
int Depth(BiTree T)
{
	int m = 0, n = 0;
	if (T == NULL)
		return 0;
	m = Depth(T->lchild);	//遍历左子树
	n = Depth(T->rchild);	//遍历右子树
	if (m>n)
		return m + 1;
	return n + 1;
}

//计算二叉树结点总数
int NodeCount(BiTree T)
{
	if (T == NULL)
		return 0;
	return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;//加一加的是当前作为根结点的结点本身
}

//计算二叉树叶子结点总数
int LeafCount(BiTree T)
{
	if (T == NULL)
		return 0;
	if (T->lchild == NULL && T->rchild == NULL)
		return 1;//是叶子节点
	return LeafCount(T->lchild) + LeafCount(T->rchild);	//不是叶子节点，则分别统计左右子树叶子结点个数
}