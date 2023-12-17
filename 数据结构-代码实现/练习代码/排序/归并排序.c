#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAXSIZE 5	//���Ա��ʼ������

void print_Arr(int arr[]);
void merge_sort(int arr[]);
void merge(int arr[], int a[], int left, int mid, int right);
void msort(int arr[], int a[], int left, int right);

int main()
{
	int arr[MAXSIZE + 1];
	clock_t start, finish; // �������
	double t;
	FILE *fp1;
	srand((unsigned int)time(NULL));//��ʼ�������������

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

	start = clock();     //��ʼ

	print_Arr(arr);
	merge_sort(arr);
	print_Arr(arr);

	finish = clock();    //����
	t = (double)(finish - start);//��������ʱ��
	printf("time = %lfms\n\n", t);//�������ʱ��

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

// �鲢�������
void merge_sort(int arr[])
{
	int* a = (int*)malloc((MAXSIZE + 1)*sizeof(int));	//����һ��ͬ����С�ĸ����ռ�
	
	if (a)	//�����������ɹ�
	{
		msort(arr, a, 1, MAXSIZE);
		free(a);	//�ͷŸ����ռ�
	}
	else
	{
		printf("error:����ʧ�ܣ�");
	}
}

//�鲢����
void msort(int arr[], int a[], int left, int right)	//ԭ˳����������飬���±꣬���±�
{
	//���ֻ��һ��Ԫ�أ���ô����Ҫ��������
	if (left < right)
	{
		int mid = (left + right) / 2;	//���м��
		msort(arr, a, left, mid);	//�ݹ�������֣������
		msort(arr, a, mid + 1, right);	//�Ұ���
		merge(arr, a, left, mid, right);	//��ֻ��һ��Ԫ�ص�ʱ��ʼ�ϲ�
	}
}

void merge(int arr[], int a[], int left, int mid, int right)
{
	//���˳����������һ��δ�����Ԫ��
	int l_pos = left;
	//���˳����Ұ�����һ��δ�����Ԫ��
	int r_pos = mid + 1;
	//��ʱ������±�
	int pos = left;	//��Ϊһ����������Ҫ�ϲ��ľ���left��right��һ����
	//�ϲ�
	while (l_pos <= mid && r_pos <= right)	//����������Ұ���������Ԫ��ʱ
	{
		if (arr[l_pos] < arr[r_pos])	//����������һ��ʣ��Ԫ��С���Ұ�����һ��Ԫ��
		{
			a[pos] = arr[l_pos];	//�������Ԫ�طŵ���������
			pos++;
			l_pos++;
		}
		else
		{
			a[pos] = arr[r_pos];	//���Ұ���Ԫ�طŵ���������
			pos++;
			r_pos++;
		}
	}
	//�ϲ������ʣ���Ԫ��
	while (l_pos <= mid)
	{
		a[pos] = arr[l_pos];	//�������Ԫ�طŵ���������
		pos++;
		l_pos++;
	}
	//�ϲ��Ұ���ʣ���Ԫ��
	while (r_pos <= right)
	{
		a[pos] = arr[r_pos];	//�������Ԫ�طŵ���������
		pos++;
		r_pos++;
	}
	//����ʱ�����кϲ����Ԫ�ظ��ƻ�ԭ����
	while (left <= right)
	{
		arr[left] = a[left];
		left++;
	}
}