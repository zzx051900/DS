#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAXSIZE 10	//���Ա��ʼ������
#define OK 1	//�ɹ���־
#define  ERROR 0	//ʧ�ܱ�־

typedef int Status;	//Status �Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int ElemType;	//ElemType�����͸���ʵ���������������ٶ�Ϊint
typedef int KeyType; //��ؼ���Ϊ����

typedef struct //����ÿ����¼������Ԫ�أ��Ľṹ
{
	KeyType key; //�ؼ���
}RedType;

//˳������ݽṹ
typedef struct
{
	RedType r[MAXSIZE+1];
	int length;
}SqList;

//��������
Status InitList_Sq(SqList *L);	//˳���ĳ�ʼ��
void bubble_sort(SqList* L);	//ð������
void SelectSort(SqList* L);		//��ѡ������
void InserSort(SqList* L);		//ֱ�Ӳ�������
void QSort(SqList* L, int low, int high);//�������򣨵ݹ飩
int Partition(SqList* L, int low, int high);
void HeapSort(SqList* L);	//������
void HeapAdjust(SqList* L, int s, int m);	//�ѵ���
int min_(int x, int y);
void merge_sort(SqList* L);
void print_Sq(SqList L);	//���˳���


int main()
{
	SqList L;
	clock_t start, finish; // �������
	double t;
	FILE *fp1;
	srand((unsigned int)time(NULL));//��ʼ�������������

	InitList_Sq(&L);

	// ���ļ���д������
	fp1 = fopen("data1.dat", "wb");
	fwrite(L.r, sizeof(RedType), MAXSIZE, fp1);
	fclose(fp1);

	//����ð������
	fp1 = fopen("data1.dat", "rb");
	fread(L.r, sizeof(RedType), MAXSIZE, fp1);
	fclose(fp1);

	start = clock();     //��ʼ
	printf("ð������ǰ��\n");
	print_Sq(L);  //��ӡ���

	bubble_sort(&L);
	printf("ð�������\n");
	print_Sq(L);  //��ӡ���

	finish = clock();    //����
	t = (double)(finish - start) / CLOCKS_PER_SEC;//��������ʱ��
	printf("time = %lfms\n\n", t * 1000);//�������ʱ��

	//���Լ�ѡ������
	fp1 = fopen("data1.dat", "rb");
	fread(L.r, sizeof(RedType), MAXSIZE, fp1);
	fclose(fp1);

	start = clock();     //��ʼ
	printf("��ѡ������ǰ��\n");
	print_Sq(L);  //��ӡ���

	SelectSort(&L);
	printf("��ѡ�������\n");
	print_Sq(L);  //��ӡ���

	finish = clock();    //����
	t = (double)(finish - start) / CLOCKS_PER_SEC;//��������ʱ��
	printf("time = %lfms\n\n", t * 1000);//�������ʱ��

	//����ֱ�Ӳ�������
	fp1 = fopen("data1.dat", "rb");
	fread(L.r, sizeof(RedType), MAXSIZE, fp1);
	fclose(fp1);

	start = clock();     //��ʼ
	printf("ֱ�Ӳ�������ǰ��\n");
	print_Sq(L);  //��ӡ���

	InserSort(&L);
	printf("ֱ�Ӳ��������\n");
	print_Sq(L);  //��ӡ���

	finish = clock();    //����
	t = (double)(finish - start) / CLOCKS_PER_SEC;//��������ʱ��
	printf("time = %lfms\n\n", t * 1000);//�������ʱ��

	//���Կ�������
	fp1 = fopen("data1.dat", "rb");
	fread(L.r, sizeof(RedType), MAXSIZE, fp1);
	fclose(fp1);

	start = clock();     //��ʼ
	printf("��������ǰ��\n");
	print_Sq(L);  //��ӡ���

	QSort(&L, 1, L.length);	
	printf("���������\n");
	//print_Sq(L);  //��ӡ���

	finish = clock();    //����
	t = (double)(finish - start) / CLOCKS_PER_SEC;//��������ʱ��
	printf("time = %lfms\n\n", t * 1000);//�������ʱ��

	//���Զ�����
	fp1 = fopen("data1.dat", "rb");
	fread(L.r, sizeof(RedType), MAXSIZE, fp1);
	fclose(fp1);

	start = clock();     //��ʼ
	printf("������ǰ��\n");
	print_Sq(L);  //��ӡ���

	HeapSort(&L);
	printf("�������\n");
	print_Sq(L);  //��ӡ���

	finish = clock();    //����
	t = (double)(finish - start) / CLOCKS_PER_SEC;//��������ʱ��
	printf("time = %lfms\n\n", t * 1000);//�������ʱ��
	
	//���Զ�����
	fp1 = fopen("data1.dat", "rb");
	fread(L.r, sizeof(RedType), MAXSIZE, fp1);
	fclose(fp1);

	start = clock();     //��ʼ
	printf("�鲢����ǰ��\n");
	print_Sq(L);  //��ӡ���

	merge_sort(&L);
	printf("�鲢�����\n");
	print_Sq(L);  //��ӡ���

	finish = clock();    //����
	t = (double)(finish - start) / CLOCKS_PER_SEC;//��������ʱ��
	printf("time = %lfms\n\n", t * 1000);//�������ʱ��


	return 0;
}

//˳���ĳ�ʼ��
Status InitList_Sq(SqList* L)
{
	L->length = MAXSIZE;	

	for (int i = 1; i <= MAXSIZE; i++)
	{
		L->r[i].key = rand();
	}
	return OK;
}

//ð������
void bubble_sort(SqList* L)
{
	int i, j;
	int a = 0;	//�Ƚϴ���
	int b = 0;	//��������
	RedType x; //����ʱ������ʱ����
	for (i = 1; i <= L->length -1; i++)	//n��Ԫ����Ҫn-1��ð������
	{
		for (j = 1; j <= L->length - i; j++)	//��һ����Ҫ�Ƚ�n-1�Σ�ÿһ����Ҫ�Ƚϵ�Ԫ�ؼ���һ��
		{
			if (++a && L->r[j].key >L->r[j + 1].key) //���������򽻻�
			{
				x = L->r[j];
				L->r[j] = L->r[j + 1];
				L->r[j + 1] = x;
				b++;
			}
		}
	}
	printf("ð������Ƚϴ���Ϊ��%d\n", a);
	printf("ð�����򽻻�����Ϊ��%d\n", b);
	printf("ð�������ƶ�����Ϊ��%d\n", 3*b);
}

//��ѡ������
void SelectSort(SqList* L)
{
	int i, k, j;
	RedType x; //����ʱ������ʱ����
	int a = 0;	//�Ƚϴ���
	int b = 0;	//��������
	for (i = 1; i <= L->length - 1; i++)
	{
		k = i;	//��ʼʱĬ��ÿ�˵ĵ�һ��Ϊ��С
		for (j = i + 1; j <= L->length; j++)	//��Ĭ��λ��֮���Ԫ�ؿ�ʼѰ����С��Ԫ��
		{
			if (++a && L->r[j].key < L->r[k].key)
			{
				k = j; //��¼��Сֵλ��
			}				
		}
		//һ��ִ�����Ժ󣬽���L.r[i]��L.r[k]
		if (k != i)	//�����С��λ�ò���Ĭ��λ�ã�����Ҫ����
		{
			x = L->r[i];
			L->r[i] = L->r[k];
			L->r[k] = x;
			b++;
		}
	}
	printf("��ѡ������Ƚϴ���Ϊ��%d\n", a);
	printf("��ѡ�����򽻻�����Ϊ��%d\n", b);
	printf("��ѡ�������ƶ�����Ϊ��%d\n",3*b);
}

//ֱ�Ӳ�������ʹ���ڱ���
void InserSort(SqList* L)
{
	int i, j;
	int a = 0;	//�Ƚϴ���
	int b = 0;	//�ƶ�����
	for (i = 2; i <= L->length; i++)	//�ӵڶ���Ԫ�ؿ�ʼ���뵽��������
	{
		if (++a && L->r[i].key < L->r[i - 1].key)	//�ж��²����Ԫ���Ƿ������������һ��Ԫ�ش����������Ҫ�ƶ�Ԫ��
		{
			L->r[0] = L->r[i];//����Ϊ�ڱ�
			for (j = i - 1;++a && L->r[0].key < L->r[j].key; j--)	//�����ź�������е����һ���Ӻ���ǰ�Ƚϣ���������ڱ��������
			{
				L->r[j + 1] = L->r[j];
				b++;
			}	//ѭ������ʱ�����jλԪ��С���²���Ԫ�أ�j+1λΪҪ�����λ��
			L->r[j + 1] = L->r[0]; //���뵽��ȷλ��
			b++;
		}		
	}
	printf("ֱ�Ӳ�������Ƚϴ���Ϊ��%d\n", a);
	printf("ֱ�Ӳ��������ƶ�����Ϊ��%d\n", b);
}

//��˳���L�������򣨵ݹ飩
void QSort(SqList* L, int low, int high) 
{
	if (low < high) //���ȴ���1
	{
		//�����ĵ�Ԫ��λ��
		int pivotloc;
		pivotloc = Partition(L, low, high); //��L.r[low...high]һ��Ϊ����pivotlocΪ����Ԫ���ź����λ��
		QSort(L, low, pivotloc - 1); 	//�Ե��ӱ�ݹ�����
		QSort(L, pivotloc + 1, high); //�Ը��ӱ�ݹ�����
	}
}


int Partition(SqList* L, int low, int high)
{
	KeyType pivotkey;
	L->r[0] = L->r[low];
	pivotkey = L->r[low].key;
	while (low < high)
	{
		while (low < high && L->r[high].key >= pivotkey)
			high--;
		L->r[low] = L->r[high];
		while (low < high && L->r[low].key <= pivotkey)
			low++;
		L->r[high] = L->r[low];
	}	//����ʱ��low��high��ָ�����ĵ�Ԫ��Ӧ���ڵ�λ��
	L->r[low] = L->r[0];
	return low;	//�������ĵ�λ��
}

//���˳���
void print_Sq(SqList L)
{
	for (int i = 1; i <= L.length; i++)
	{
		printf("%d ", L.r[i]);
	}
	printf("\n");
}

//������
void HeapSort(SqList* L) 
{
	int i, n;
	RedType tmp;
	n = L->length;

	for (i = n / 2; i >= 1; i--)	//i = n/2 �ҵ����һ����Ҷ�ӽ��
	{
		HeapAdjust(L, i, n); //����ʼ��
	}
	for (i = n; i > 1; i--) //����n-1������
	{
		//�������һ��Ԫ�ؽ���
		tmp = L->r[1];
		L->r[1] = L->r[i];
		L->r[i] = tmp;
		HeapAdjust(L, 1, i - 1); //��R[1]��R[i-1]���½���
	}
}

//�ѵ���������ѣ�
void HeapAdjust(SqList* L, int s, int m)	//sΪ�Ѷ�����λ�ã�mΪ���һ��Ԫ������λ��
{
	//������ѣ�������Ԫ�ط�������棬������˴�С��������
	int j;
	RedType rc = L->r[s];	//����Ѷ�Ԫ��
	for (j = 2 * s; j <= m; j *= 2) //��key�ϴ�ĺ�������ɸѡ
	{
		if (j < m && (L->r[j].key < L->r[j + 1].key))
		{
			j++; //jΪkey�ϴ�ļ�¼���±�
		}
		if (rc.key >= L->r[j].key)	
			break;
		L->r[s] = L->r[j];
		s = j; //rcӦ������λ��s��
	}
	L->r[s] = rc; //����
}

// �鲢����C-�����棩
int min_(int x, int y) 
{
	return x < y ? x : y;
}
void merge_sort(SqList* L) {
	RedType* a = L->r;
	RedType* b = (RedType*)malloc(L->length * sizeof(RedType));
	int seg, start;
	for (seg = 1; seg < L->length; seg += seg) {
		for (start = 0; start < L->length; start += seg + seg) 
		{
			int low = start, mid = min_(start + seg, L->length), high = min_(start + seg + seg, L->length);
			int k = low;
			int start1 = low, end1 = mid;
			int start2 = mid, end2 = high;
			while (start1 < end1 && start2 < end2)
				b[k++] = a[start1].key < a[start2].key ? a[start1++] : a[start2++];
			while (start1 < end1)
				b[k++] = a[start1++];
			while (start2 < end2)
				b[k++] = a[start2++];
		}
		RedType* temp = a;
		a = b;
		b = temp;
	}
	if (a != L->r) {
		int i;
		for (i = 0; i < L->length; i++)
			b[i] = a[i];
		b = a;
	}
	free(b);
}
