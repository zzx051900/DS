#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<time.h>
using namespace std;

#define MAXSIZE 10	//初始分配量
#define OK 1	//成功标志
#define  ERROR 0	//失败标志

typedef int Status;	//Status 是函数的类型，其值是函数结果状态代码
typedef int KeyType;

typedef struct
{
	KeyType key;	//关键字域
}ElemType;

typedef struct
{
	ElemType *R;
	int length;
}SSTable;

Status InitList_ST(SSTable& ST);
void print_ST(SSTable ST);
int Search_ST(SSTable ST, KeyType key);
void bubble_sort(SSTable& ST);
int Search_Bin1(SSTable ST, KeyType key);
int Search_Bin2(SSTable ST, KeyType key, int low, int high);

int main()
{	
	SSTable ST;
	int a[MAXSIZE+1] = { 0 };

	InitList_ST(ST);
	srand((unsigned int)time(NULL));//初始化随机数发生器
	for (int i = 1; i <= MAXSIZE; i++)
	{
		a[i] = rand()%100;
	}
	ofstream ofs;//2.创建流对象
	ofs.open("datafile.txt", ios::out);//3.打开方式
	for (int i = 1; i <= MAXSIZE; i++)
	{
		ofs << a[i] << "\t";//4.写内容
	}	
	ofs.close();//5.关闭文件

	ifstream ifs;
	ifs.open("datafile.txt", ios::in);
	for (int i = 1; i <= MAXSIZE; i++)
	{
		ifs >> ST.R[i].key;
		ST.length++;
	}
	print_ST(ST);

	cout << "顺序查找请输入要查找的元素：" << endl;
	KeyType key;
	cin >> key;
	int flag = 0;
	flag = Search_ST(ST, key);
	if (flag == 0)
	{
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "该元素在数组中的第 " << flag << " 号" << endl;
	}

	cout << "排序后：" << endl;
	bubble_sort(ST);
	print_ST(ST);

	cout << "非递归折半查找请输入要查找的元素：" << endl;
	cin >> key;	
	flag = Search_Bin1(ST, key);
	if (flag == 0)
	{
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "该元素在数组中的第 " << flag << " 号" << endl;
	}

	cout << "递归折半查找请输入要查找的元素：" << endl;
	cin >> key;
	flag = Search_Bin2(ST, key, 1, ST.length);
	if (flag == 0)
	{
		cout << "查找失败" << endl;
	}
	else
	{
		cout << "该元素在数组中的第 " << flag << " 号" << endl;
	}


	return 0;
}

//初始化
Status InitList_ST(SSTable& ST)
{
	ST.R = new ElemType[MAXSIZE];	//动态分配内存，创建头结点
	if (!ST.R)	//异常处理，检查存储空间是否分配成功
		return ERROR;
	ST.length = 0;	//表中元素为0
	return OK;
}

//输出所有元素
void print_ST(SSTable ST)
{
	for (int i = 1; i <= ST.length; i++)
	{
		cout << ST.R[i].key << " ";
	}
	cout << endl;
}

//顺序查找
//若查找成功，则返回其位置信息；否则返回0
int Search_ST(SSTable ST, KeyType key)
{
	for (int i = ST.length; i >= 1; --i)
	{
		if (ST.R[i].key == key)
			return i;
	}
	return 0;
}

//排序（冒泡排序）
void bubble_sort(SSTable& ST)
{
	int i, j;
	ElemType x; //交换时用于临时储存
	int flag = 1; //flag用于标记是否发生了交换
	for (i = 1; i <= ST.length - 1 && flag == 1; i++)	//n个元素需要n-1趟冒泡排序
	{
		flag = 0;
		for (j = 1; j <= ST.length - i; j++)	//每一趟需要比较的元素减少一个
		{
			flag = 1;
			if (ST.R[j].key >ST.R[j + 1].key) //发生逆序，则交换
			{
				x = ST.R[j];
				ST.R[j] = ST.R[j + 1];
				ST.R[j + 1] = x;
			}
		}
	}

}

//折半查找（非递归）
int Search_Bin1(SSTable ST, KeyType key)
{
	int low = 1; 
	int high = ST.length;
	while (low <= high)
	{
		int mid = (low + high) / 2;
		if (key == ST.R[mid].key)
			return mid;	//找到
		if (key < ST.R[mid].key)
		{
			high = mid - 1;	//key在mid左边，在前半区查找
		}
		else
		{
			low = mid + 1;	//key在mid右边，在后半区查找
		}
	}
	return 0;
}

//折半查找（递归）
int Search_Bin2(SSTable ST, KeyType key, int low, int high)
{
	if (low > high)
		return 0;
	int mid = (low + high) / 2;
	if (key == ST.R[mid].key)
		return mid;
	if (key < ST.R[mid].key)
	{
		high = mid - 1;
		Search_Bin2(ST, key, low, high);
	}
	else
	{
		low = mid + 1;
		Search_Bin2(ST, key, low, high);
	}
}