#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAXSIZE 5	//线性表初始分配量

void print_Arr(int arr[]);
void merge_sort(int arr[]);
void merge(int arr[], int a[], int left, int mid, int right);
void msort(int arr[], int a[], int left, int right);

int main()
{
	int arr[MAXSIZE + 1];
	clock_t start, finish; // 定义变量
	double t;
	FILE *fp1;
	srand((unsigned int)time(NULL));//初始化随机数发生器

	for (int i = 1; i <= MAXSIZE; i++)
	{
		arr[i] = rand();
	}
	fp1 = fopen("data.dat", "wb");
	fwrite(arr, sizeof(int), MAXSIZE + 1, fp1);
	fclose(fp1);

	fp1 = fopen("data.dat", "rb");
	fread(arr, sizeof(int), MAXSIZE + 1, fp1);
	fclose(fp1);

	start = clock();     //开始

	print_Arr(arr);
	merge_sort(arr);
	print_Arr(arr);

	finish = clock();    //结束
	t = (double)(finish - start);//计算运行时间
	printf("time = %lfms\n\n", t);//输出运行时间

	return 0;
}

void print_Arr(int arr[])
{
	for (int i = 1; i <= MAXSIZE; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

// 归并排序入口
void merge_sort(int arr[])
{
	int* a = (int*)malloc((MAXSIZE + 1)*sizeof(int));	//分配一个同样大小的辅助空间
	
	if (a)	//辅助数组分配成功
	{
		msort(arr, a, 1, MAXSIZE);
		free(a);	//释放辅助空间
	}
	else
	{
		printf("error:分配失败！");
	}
}

//归并排序
void msort(int arr[], int a[], int left, int right)	//原顺序表，辅助数组，左下标，右下标
{
	//如果只有一个元素，那么不需要继续划分
	if (left < right)
	{
		int mid = (left + right) / 2;	//找中间点
		msort(arr, a, left, mid);	//递归继续划分，左半区
		msort(arr, a, mid + 1, right);	//右半区
		merge(arr, a, left, mid, right);	//当只有一个元素的时候开始合并
	}
}

void merge(int arr[], int a[], int left, int mid, int right)
{
	//标记顺序表左半区第一个未排序的元素
	int l_pos = left;
	//标记顺序表右半区第一个未排序的元素
	int r_pos = mid + 1;
	//临时数组的下标
	int pos = left;	//因为一个过程内需要合并的就是left到right这一部分
	//合并
	while (l_pos <= mid && r_pos <= right)	//当左半区和右半区都还有元素时
	{
		if (arr[l_pos] < arr[r_pos])	//如果左半区第一个剩余元素小于右半区第一个元素
		{
			a[pos] = arr[l_pos];	//将左半区元素放到辅助数组
			pos++;
			l_pos++;
		}
		else
		{
			a[pos] = arr[r_pos];	//将右半区元素放到辅助数组
			pos++;
			r_pos++;
		}
	}
	//合并左半区剩余的元素
	while (l_pos <= mid)
	{
		a[pos] = arr[l_pos];	//将左半区元素放到辅助数组
		pos++;
		l_pos++;
	}
	//合并右半区剩余的元素
	while (r_pos <= right)
	{
		a[pos] = arr[r_pos];	//将左半区元素放到辅助数组
		pos++;
		r_pos++;
	}
	//把临时数组中合并后的元素复制回原数组
	while (left <= right)
	{
		arr[left] = a[left];
		left++;
	}
}