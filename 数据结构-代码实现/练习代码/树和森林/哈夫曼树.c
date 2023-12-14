#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define OK 1	//成功标志
#define  ERROR 0	//失败标志

typedef int Status;	//Status 是函数的类型，其值是函数结果状态代码
typedef int TElemType;

typedef struct
{
	int weight;//权重
	int parent, lch, rch;//双亲、左孩子、右孩子结点下标
}HTNode, *HuffmanTree;

typedef char** HuffmanCode; //指针数组中存储的元素类型

void CreatHuffmanTree(HuffmanTree* HT, int n);
void Select(HuffmanTree HT, int n, int* s1, int* s2);
void HuffCoding(HuffmanTree* HT, HuffmanCode* HC, int n);

int main()
{
	HuffmanTree HT;
	int n = 0;
	HuffmanCode HC;
	printf("请输入给定的权值数量：");
	scanf("%d", &n);
	CreatHuffmanTree(&HT, n);

	
	HuffCoding(&HT, &HC, n); //构建哈夫曼编码
	for (int i = 1; i <= n; i++) //打印哈夫曼编码
	{
		printf("数据 %d 的编码为:%s\n", HT[i].weight, HC[i]);
	}

	return 0;
}

void CreatHuffmanTree(HuffmanTree* HT, int n)
{
	int m = 0;
	if (n <= 1)
		return;
	m = 2 * n - 1;	//数组共2n-1个元素
	*HT = (HuffmanTree)malloc((m + 1)*sizeof(HTNode));	//0号元素不用
	for (int i = 1; i <= m; ++i)	//初始化
	{
		(*HT)[i].lch = 0;
		(*HT)[i].rch = 0;
		(*HT)[i].parent = 0;
	}
	printf("请输入所有结点的权值大小：");
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &(*HT)[i].weight);	//输入前n个元素的weight值，HT[i].weight
	}
	for (int i = n + 1; i <= m; i++)
	{
		int s1 = 0, s2 = 0;
		//写一个函数，实现：在HT[k](1 <= k <= i-1)中选择两个其双亲域为0，且权值最小的结点，并返回它们在HT中的序号s1和s2
		//为什么是 i-1 ，因为一开始 n = i-1，并且每循环一次，都多一个需要比较的结点
		Select(*HT, i - 1, &s1, &s2);
		(*HT)[s1].parent = i;
		(*HT)[s2].parent = i;//表示从F中删除s1和s2，其双亲域不为0了
		(*HT)[i].lch = s1; 
		(*HT)[i].rch = s2;//s1和s2分别作为i的左右孩子
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;//i的权值为左右孩子权值之和  
	}
	printf("哈夫曼树为:\n");
	printf("下标\t权值\t父结点\t左孩子\t右孩子\n");
	for (int i = 1; i <= m; i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\n", i, (*HT)[i].weight, (*HT)[i].parent, (*HT)[i].lch, (*HT)[i].rch);
	}
	printf("\n");
	
}

void Select(HuffmanTree HT, int n, int* s1, int* s2)
{
	int min;
	//找第一个最小值
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0)
		{
			min = i;
			break;
		}
	}
	for (int i = min + 1; i <= n; i++)
	{
		if (HT[i].parent == 0 && HT[i].weight < HT[min].weight)
			min = i;
	}
	*s1 = min; //第一个最小值给s1
	//找第二个最小值
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0 && i != *s1)
		{
			min = i;
			break;
		}
	}
	for (int i = min + 1; i <= n; i++)
	{
		if (HT[i].parent == 0 && HT[i].weight < HT[min].weight&&i != *s1)
			min = i;
	}
	*s2 = min; //第二个最小值给s2
}

//生成哈夫曼编码
void HuffCoding(HuffmanTree* HT, HuffmanCode* HC, int n)
{
	*HC = (HuffmanCode)malloc(sizeof(char*)*(n + 1)); //开n+1个空间，因为下标为0的空间不用
	char* code = (char*)malloc(sizeof(char)*n); //辅助空间，编码最长为n(最长时，前n-1个用于存储数据，最后1个用于存放'\0')
	code[n - 1] = '\0'; //辅助空间最后一个位置为'\0'
	for (int i = 1; i <= n; i++)
	{
		int start = n - 1; //每次生成数据的哈夫曼编码之前，先将start指针指向'\0'
		int c = i; //正在进行的第i个数据的编码
		int p = (*HT)[c].parent; //找到该数据的父结点
		while (p) //直到父结点为0，即父结点为根结点时，停止
		{
			if ((*HT)[p].lch == c) //如果该结点是其父结点的左孩子，则编码为0，否则为1
				code[--start] = '0';
			else
				code[--start] = '1';
			c = p; //继续往上进行编码
			p = (*HT)[c].parent; //c的父结点
		}
		(*HC)[i] = (char*)malloc(sizeof(char)*(n - start)); //开辟用于存储编码的内存空间
		strcpy((*HC)[i], &code[start]); //将编码拷贝到字符指针数组中的相应位置
	}
	free(code); //释放辅助空间
}