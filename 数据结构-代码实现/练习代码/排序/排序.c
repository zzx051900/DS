#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAXSIZE 10000	//线性表初始分配量
#define OK 1	//成功标志
#define  ERROR 0	//失败标志

typedef int Status;	//Status 是函数的类型，其值是函数结果状态代码
typedef int ElemType;	//ElemType的类型根据实际情况而定，这里假定为int
typedef int KeyType; //设关键字为整型

int q_a = 0;	//快速排序比较次数
int q_b = 0;	//快速排序移动次数
int h_a = 0;	//堆排序比较次数
int h_b = 0;	//堆排序移动次数
int m_a = 0;	//归并排序比较次数
int m_b = 0;	//归并排序移动次数

typedef struct //定义每个记录（数据元素）的结构
{
	KeyType key; //关键字
}RedType;

//顺序表数据结构
typedef struct
{
	RedType r[MAXSIZE+1];
	int length;
}SqList;

//函数声明
Status InitList_Sq(SqList *L);	//顺序表的初始化
Status S_ChangeList_Sq(SqList* L);
Status N_ChangeList_Sq(SqList* L);
void bubble_sort(SqList* L);	//冒泡排序
void SelectSort(SqList* L);		//简单选择排序
void InserSort(SqList* L);		//直接插入排序
void QSort(SqList* L, int low, int high);//快速排序（递归）
int Partition(SqList* L, int low, int high);
void HeapSort(SqList* L);	//堆排序
void HeapAdjust(SqList* L, int s, int m);	//堆调整
void merge_sort(SqList* L);
void merge(SqList* L, RedType a[], int left, int mid, int right);
void msort(SqList* L, RedType a[], int left, int right);

void print_Sq(SqList L);	//输出顺序表


int main()
{
	SqList L;
	clock_t start, finish; // 定义变量
	double t;
	FILE *fp1;
	srand((unsigned int)time(NULL));//初始化随机数发生器

	InitList_Sq(&L);

	//写入文件
	fp1 = fopen("data1.dat", "wb");
	fwrite(L.r, sizeof(RedType), MAXSIZE+1, fp1);
	fclose(fp1);
	for (int i = 1; i <= MAXSIZE; i++)
	{
		L.r[i].key = 0;
	}
	//测试冒泡排序
	fp1 = fopen("data1.dat", "rb");
	fread(L.r, sizeof(RedType), MAXSIZE+1, fp1);
	fclose(fp1);

	start = clock();     //开始
	//printf("冒泡排序前：\n");
	//print_Sq(L);  //打印结果

	bubble_sort(&L);
	//printf("冒泡排序后：\n");
	//print_Sq(L);  //打印结果

	finish = clock();    //结束
	t = (double)(finish - start);//计算运行时间
	printf("time = %lfms\n\n", t);//输出运行时间

	//测试简单选择排序
	fp1 = fopen("data1.dat", "rb");
	fread(L.r, sizeof(RedType), MAXSIZE + 1, fp1);
	fclose(fp1);

	start = clock();     //开始
	//printf("简单选择排序前：\n");
	//print_Sq(L);  //打印结果

	SelectSort(&L);
	//printf("简单选择排序后：\n");
	//print_Sq(L);  //打印结果

	finish = clock();    //结束
	t = (double)(finish - start);//计算运行时间
	printf("time = %lfms\n\n", t);//输出运行时间

	//测试直接插入排序
	fp1 = fopen("data1.dat", "rb");
	fread(L.r, sizeof(RedType), MAXSIZE + 1, fp1);
	fclose(fp1);

	start = clock();     //开始
	//printf("直接插入排序前：\n");
	//print_Sq(L);  //打印结果

	InserSort(&L);
	//printf("直接插入排序后：\n");
	//print_Sq(L);  //打印结果

	finish = clock();    //结束
	t = (double)(finish - start);//计算运行时间
	printf("time = %lfms\n\n", t);//输出运行时间

	//测试快速排序（随机）
	fp1 = fopen("data1.dat", "rb");
	fread(L.r, sizeof(RedType), MAXSIZE + 1, fp1);
	fclose(fp1);

	start = clock();     //开始
	//printf("随机快速排序前：\n");
	//print_Sq(L);  //打印结果

	QSort(&L, 1, L.length);	
	printf("随机快速排序比较次数为：%d\n", q_a);
	printf("随机快速排序移动次数为：%d\n", q_b);
	//printf("随机快速排序后：\n");
	//print_Sq(L);  //打印结果

	finish = clock();    //结束
	t = (double)(finish - start);//计算运行时间
	printf("time = %lfms\n\n", t);//输出运行时间

	
	//测试堆排序
	fp1 = fopen("data1.dat", "rb");
	fread(L.r, sizeof(RedType), MAXSIZE + 1, fp1);
	fclose(fp1);

	start = clock();     //开始
	//printf("堆排序前：\n");
	//print_Sq(L);  //打印结果

	HeapSort(&L);
	printf("堆排序比较次数为：%d\n", h_a);
	printf("堆排序移动次数为：%d\n", h_b);
	//printf("堆排序后：\n");
	//print_Sq(L);  //打印结果

	finish = clock();    //结束
	t = (double)(finish - start);//计算运行时间
	printf("time = %lfms\n\n", t);//输出运行时间
	
	//测试归并排序
	fp1 = fopen("data1.dat", "rb");
	fread(L.r, sizeof(RedType), MAXSIZE + 1, fp1);
	fclose(fp1);

	start = clock();     //开始
	//printf("归并排序前：\n");
	//print_Sq(L);  //打印结果

	merge_sort(&L);
	printf("归并排序比较次数：%d\n", m_a);
	printf("归并排序移动次数：%d\n", m_b);
	//printf("归并排序后：\n");
	//print_Sq(L);  //打印结果

	finish = clock();    //结束
	t = (double)(finish - start);//计算运行时间
	printf("time = %lfms\n\n", t);//输出运行时间
	return 0;
}

//顺序表的初始化
Status InitList_Sq(SqList* L)
{
	L->length = MAXSIZE;	

	for (int i = 1; i <= MAXSIZE; i++)
	{
		L->r[i].key = rand();
	}
	return OK;
}

//冒泡排序
void bubble_sort(SqList* L)
{
	int i, j;
	int a = 0;	//比较次数
	int b = 0;	//交换次数
	RedType x; //交换时用于临时储存
	for (i = 1; i <= L->length -1; i++)	//n个元素需要n-1趟冒泡排序
	{
		for (j = 1; j <= L->length - i; j++)	//第一趟需要比较n-1次，每一趟需要比较的元素减少一个
		{
			if (++a && L->r[j].key >L->r[j + 1].key) //发生逆序，则交换
			{
				x = L->r[j];
				L->r[j] = L->r[j + 1];
				L->r[j + 1] = x;
				b++;
			}
		}
	}
	printf("冒泡排序比较次数为：%d\n", a);
	printf("冒泡排序交换次数为：%d\n", b);
	printf("冒泡排序移动次数为：%d\n", 3*b);
}

//简单选择排序
void SelectSort(SqList* L)
{
	int i, k, j;
	RedType x; //交换时用于临时储存
	int a = 0;	//比较次数
	int b = 0;	//交换次数
	for (i = 1; i <= L->length - 1; i++)
	{
		k = i;	//开始时默认每趟的第一个为最小
		for (j = i + 1; j <= L->length; j++)	//从默认位置之后的元素开始寻找最小的元素
		{
			if (++a && L->r[j].key < L->r[k].key)
			{
				k = j; //记录最小值位置
			}				
		}
		//一趟执行完以后，交换L.r[i]与L.r[k]
		if (k != i)	//如果最小的位置不是默认位置，则需要交换
		{
			x = L->r[i];
			L->r[i] = L->r[k];
			L->r[k] = x;
			b++;
		}
	}
	printf("简单选择排序比较次数为：%d\n", a);
	printf("简单选择排序交换次数为：%d\n", b);
	printf("简单选择排序移动次数为：%d\n",3*b);
}

//直接插入排序（使用哨兵）
void InserSort(SqList* L)
{
	int i, j;
	int a = 0;	//比较次数
	int b = 0;	//移动次数
	for (i = 2; i <= L->length; i++)	//从第二个元素开始插入到有序序列
	{
		if (++a && L->r[i].key < L->r[i - 1].key)	//判断新插入的元素是否比已排序的最后一个元素大，如果大则不需要移动元素
		{
			L->r[0] = L->r[i];//复制为哨兵
			for (j = i - 1;++a && L->r[0].key < L->r[j].key; j--)	//从已排好序的序列的最后一个从后往前比较，如果大于哨兵，则后移
			{
				L->r[j + 1] = L->r[j];
				b++;
			}	//循环结束时代表第j位元素小于新插入元素，j+1位为要插入的位置
			L->r[j + 1] = L->r[0]; //插入到正确位置
			b++;
		}		
	}
	printf("直接插入排序比较次数为：%d\n", a);
	printf("直接插入排序移动次数为：%d\n", b);
}

//对顺序表L快速排序（递归）
void QSort(SqList* L, int low, int high) 
{
	if (low < high) //长度大于1
	{
		//找中心点元素位置
		int pivotloc;
		pivotloc = Partition(L, low, high); //将L.r[low...high]一分为二，pivotloc为枢轴元素排好序的位置
		QSort(L, low, pivotloc - 1); 	//对低子表递归排序
		QSort(L, pivotloc + 1, high); //对高子表递归排序
	}
}

int Partition(SqList* L, int low, int high)
{
	L->r[0] = L->r[low];
	while (low < high)
	{
		while (low < high && ++q_a && L->r[high].key >= L->r[0].key)
			high--;
		L->r[low] = L->r[high];
		q_b++;
		while (low < high && ++q_a && L->r[low].key <= L->r[0].key)
			low++;
		L->r[high] = L->r[low];
		q_b++;
	}	//结束时，low和high都指向中心点元素应该在的位置
	L->r[low] = L->r[0];
	return low;	//返回中心点位置
}

//输出顺序表
void print_Sq(SqList L)
{
	for (int i = 1; i <= L.length; i++)
	{
		printf("%d ", L.r[i]);
	}
	printf("\n");
}

//堆排序
void HeapSort(SqList* L) 
{
	int i, n;
	RedType tmp;
	n = L->length;

	for (i = n / 2; i >= 1; i--)	//i = n/2 找到最后一个非叶子结点
	{
		HeapAdjust(L, i, n); //建初始堆
	}
	for (i = n; i > 1; i--) //进行n-1趟排序
	{
		//根与最后一个元素交换
		tmp = L->r[1];
		L->r[1] = L->r[i];
		L->r[i] = tmp;
		h_b += 3;
		HeapAdjust(L, 1, i - 1); //对R[1]到R[i-1]重新建堆
	}
}

//堆调整（大根堆）
void HeapAdjust(SqList* L, int s, int m)	//s为堆顶所在位置，m为最后一个元素所在位置
{
	//建大根堆，将最大的元素放在最后面，即完成了从小到大排序
	int j;
	RedType rc = L->r[s];	//保存堆顶元素
	for (j = 2 * s; j <= m; j *= 2) //沿key较大的孩子向下筛选
	{
		if (j < m && ++h_a && (L->r[j].key < L->r[j + 1].key))
		{
			j++; //j为key较大的记录的下标
		}
		if (++h_a && rc.key >= L->r[j].key)	
			break;
		L->r[s] = L->r[j];
		++h_b;
		s = j; //rc应插入在位置s上
	}
	L->r[s] = rc; //插入
	++h_b;
}

// 归并排序入口
void merge_sort(SqList* L)
{
	RedType* a = (RedType*)malloc((MAXSIZE + 1)*sizeof(RedType));	//分配一个同样大小的辅助空间
	if (a)	//辅助数组分配成功
	{
		msort(L, a, 1, L->length);
		free(a);	//释放辅助空间
	}
	else
	{
		printf("error:分配失败！");
	}
}

//归并排序
void msort(SqList* L, RedType a[], int left, int right)	//原顺序表，辅助数组，左下标，右下标
{
	//如果只有一个元素，那么不需要继续划分
	if (left < right)
	{
		int mid = (left + right) / 2;	//找中间点
		msort(L, a, left, mid);	//递归继续划分，左半区
		msort(L, a, mid + 1, right);	//右半区
		merge(L, a, left, mid, right);	//当只有一个元素的时候开始合并
	}
}

//合并
void merge(SqList* L, RedType a[], int left, int mid, int right)
{
	//标记顺序表左半区第一个未排序的元素
	int l_pos = left;
	//标记顺序表左半区第一个未排序的元素
	int r_pos = mid + 1;
	//临时数组的下标
	int pos = left;	//因为一个过程内需要合并的就是left到right这一部分
	//合并
	while (++m_a && l_pos <= mid && ++m_a && r_pos <= right)	//当左半区和右半区都还有元素时
	{
		if (++m_a && L->r[l_pos].key < L->r[r_pos].key)	//如果左半区第一个剩余元素小于右半区第一个元素
		{
			a[pos] = L->r[l_pos];	//将左半区元素放到辅助数组
			pos++;
			l_pos++;
			++m_b;
		}
		else
		{
			a[pos] = L->r[r_pos];	//将右半区元素放到辅助数组
			pos++;
			r_pos++;
			++m_b;
		}
	}
	//合并左半区剩余的元素
	while (++m_a && l_pos <= mid)
	{
		a[pos] = L->r[l_pos];	//将左半区元素放到辅助数组
		pos++;
		l_pos++;
		++m_b;
	}
	//合并右半区剩余的元素
	while (++m_a && r_pos <= right)
	{
		a[pos] = L->r[r_pos];	//将左半区元素放到辅助数组
		pos++;
		r_pos++;
		++m_b;
	}
	//把临时数组中合并后的元素复制回原数组
	while (left <= right)
	{
		L->r[left] = a[left];
		left++;
		++m_b;
	}
}