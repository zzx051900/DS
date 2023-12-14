#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define OK 1	//�ɹ���־
#define  ERROR 0	//ʧ�ܱ�־

typedef int Status;	//Status �Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int TElemType;

typedef struct
{
	int weight;//Ȩ��
	int parent, lch, rch;//˫�ס����ӡ��Һ��ӽ���±�
}HTNode, *HuffmanTree;

typedef char** HuffmanCode; //ָ�������д洢��Ԫ������

void CreatHuffmanTree(HuffmanTree* HT, int n);
void Select(HuffmanTree HT, int n, int* s1, int* s2);
void HuffCoding(HuffmanTree* HT, HuffmanCode* HC, int n);

int main()
{
	HuffmanTree HT;
	int n = 0;
	HuffmanCode HC;
	printf("�����������Ȩֵ������");
	scanf("%d", &n);
	CreatHuffmanTree(&HT, n);

	
	HuffCoding(&HT, &HC, n); //��������������
	for (int i = 1; i <= n; i++) //��ӡ����������
	{
		printf("���� %d �ı���Ϊ:%s\n", HT[i].weight, HC[i]);
	}

	return 0;
}

void CreatHuffmanTree(HuffmanTree* HT, int n)
{
	int m = 0;
	if (n <= 1)
		return;
	m = 2 * n - 1;	//���鹲2n-1��Ԫ��
	*HT = (HuffmanTree)malloc((m + 1)*sizeof(HTNode));	//0��Ԫ�ز���
	for (int i = 1; i <= m; ++i)	//��ʼ��
	{
		(*HT)[i].lch = 0;
		(*HT)[i].rch = 0;
		(*HT)[i].parent = 0;
	}
	printf("���������н���Ȩֵ��С��");
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &(*HT)[i].weight);	//����ǰn��Ԫ�ص�weightֵ��HT[i].weight
	}
	for (int i = n + 1; i <= m; i++)
	{
		int s1 = 0, s2 = 0;
		//дһ��������ʵ�֣���HT[k](1 <= k <= i-1)��ѡ��������˫����Ϊ0����Ȩֵ��С�Ľ�㣬������������HT�е����s1��s2
		//Ϊʲô�� i-1 ����Ϊһ��ʼ n = i-1������ÿѭ��һ�Σ�����һ����Ҫ�ȽϵĽ��
		Select(*HT, i - 1, &s1, &s2);
		(*HT)[s1].parent = i;
		(*HT)[s2].parent = i;//��ʾ��F��ɾ��s1��s2����˫����Ϊ0��
		(*HT)[i].lch = s1; 
		(*HT)[i].rch = s2;//s1��s2�ֱ���Ϊi�����Һ���
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;//i��ȨֵΪ���Һ���Ȩֵ֮��  
	}
	printf("��������Ϊ:\n");
	printf("�±�\tȨֵ\t�����\t����\t�Һ���\n");
	for (int i = 1; i <= m; i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\n", i, (*HT)[i].weight, (*HT)[i].parent, (*HT)[i].lch, (*HT)[i].rch);
	}
	printf("\n");
	
}

void Select(HuffmanTree HT, int n, int* s1, int* s2)
{
	int min;
	//�ҵ�һ����Сֵ
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
	*s1 = min; //��һ����Сֵ��s1
	//�ҵڶ�����Сֵ
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
	*s2 = min; //�ڶ�����Сֵ��s2
}

//���ɹ���������
void HuffCoding(HuffmanTree* HT, HuffmanCode* HC, int n)
{
	*HC = (HuffmanCode)malloc(sizeof(char*)*(n + 1)); //��n+1���ռ䣬��Ϊ�±�Ϊ0�Ŀռ䲻��
	char* code = (char*)malloc(sizeof(char)*n); //�����ռ䣬�����Ϊn(�ʱ��ǰn-1�����ڴ洢���ݣ����1�����ڴ��'\0')
	code[n - 1] = '\0'; //�����ռ����һ��λ��Ϊ'\0'
	for (int i = 1; i <= n; i++)
	{
		int start = n - 1; //ÿ���������ݵĹ���������֮ǰ���Ƚ�startָ��ָ��'\0'
		int c = i; //���ڽ��еĵ�i�����ݵı���
		int p = (*HT)[c].parent; //�ҵ������ݵĸ����
		while (p) //ֱ�������Ϊ0���������Ϊ�����ʱ��ֹͣ
		{
			if ((*HT)[p].lch == c) //����ý�����丸�������ӣ������Ϊ0������Ϊ1
				code[--start] = '0';
			else
				code[--start] = '1';
			c = p; //�������Ͻ��б���
			p = (*HT)[c].parent; //c�ĸ����
		}
		(*HC)[i] = (char*)malloc(sizeof(char)*(n - start)); //�������ڴ洢������ڴ�ռ�
		strcpy((*HC)[i], &code[start]); //�����뿽�����ַ�ָ�������е���Ӧλ��
	}
	free(code); //�ͷŸ����ռ�
}