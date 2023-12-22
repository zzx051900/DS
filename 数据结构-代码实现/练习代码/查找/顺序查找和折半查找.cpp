#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<time.h>
using namespace std;

#define MAXSIZE 10	//��ʼ������
#define OK 1	//�ɹ���־
#define  ERROR 0	//ʧ�ܱ�־

typedef int Status;	//Status �Ǻ��������ͣ���ֵ�Ǻ������״̬����
typedef int KeyType;

typedef struct
{
	KeyType key;	//�ؼ�����
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
	srand((unsigned int)time(NULL));//��ʼ�������������
	for (int i = 1; i <= MAXSIZE; i++)
	{
		a[i] = rand()%100;
	}
	ofstream ofs;//2.����������
	ofs.open("datafile.txt", ios::out);//3.�򿪷�ʽ
	for (int i = 1; i <= MAXSIZE; i++)
	{
		ofs << a[i] << "\t";//4.д����
	}	
	ofs.close();//5.�ر��ļ�

	ifstream ifs;
	ifs.open("datafile.txt", ios::in);
	for (int i = 1; i <= MAXSIZE; i++)
	{
		ifs >> ST.R[i].key;
		ST.length++;
	}
	print_ST(ST);

	cout << "˳�����������Ҫ���ҵ�Ԫ�أ�" << endl;
	KeyType key;
	cin >> key;
	int flag = 0;
	flag = Search_ST(ST, key);
	if (flag == 0)
	{
		cout << "����ʧ��" << endl;
	}
	else
	{
		cout << "��Ԫ���������еĵ� " << flag << " ��" << endl;
	}

	cout << "�����" << endl;
	bubble_sort(ST);
	print_ST(ST);

	cout << "�ǵݹ��۰����������Ҫ���ҵ�Ԫ�أ�" << endl;
	cin >> key;	
	flag = Search_Bin1(ST, key);
	if (flag == 0)
	{
		cout << "����ʧ��" << endl;
	}
	else
	{
		cout << "��Ԫ���������еĵ� " << flag << " ��" << endl;
	}

	cout << "�ݹ��۰����������Ҫ���ҵ�Ԫ�أ�" << endl;
	cin >> key;
	flag = Search_Bin2(ST, key, 1, ST.length);
	if (flag == 0)
	{
		cout << "����ʧ��" << endl;
	}
	else
	{
		cout << "��Ԫ���������еĵ� " << flag << " ��" << endl;
	}


	return 0;
}

//��ʼ��
Status InitList_ST(SSTable& ST)
{
	ST.R = new ElemType[MAXSIZE];	//��̬�����ڴ棬����ͷ���
	if (!ST.R)	//�쳣�������洢�ռ��Ƿ����ɹ�
		return ERROR;
	ST.length = 0;	//����Ԫ��Ϊ0
	return OK;
}

//�������Ԫ��
void print_ST(SSTable ST)
{
	for (int i = 1; i <= ST.length; i++)
	{
		cout << ST.R[i].key << " ";
	}
	cout << endl;
}

//˳�����
//�����ҳɹ����򷵻���λ����Ϣ�����򷵻�0
int Search_ST(SSTable ST, KeyType key)
{
	for (int i = ST.length; i >= 1; --i)
	{
		if (ST.R[i].key == key)
			return i;
	}
	return 0;
}

//����ð������
void bubble_sort(SSTable& ST)
{
	int i, j;
	ElemType x; //����ʱ������ʱ����
	int flag = 1; //flag���ڱ���Ƿ����˽���
	for (i = 1; i <= ST.length - 1 && flag == 1; i++)	//n��Ԫ����Ҫn-1��ð������
	{
		flag = 0;
		for (j = 1; j <= ST.length - i; j++)	//ÿһ����Ҫ�Ƚϵ�Ԫ�ؼ���һ��
		{
			flag = 1;
			if (ST.R[j].key >ST.R[j + 1].key) //���������򽻻�
			{
				x = ST.R[j];
				ST.R[j] = ST.R[j + 1];
				ST.R[j + 1] = x;
			}
		}
	}

}

//�۰���ң��ǵݹ飩
int Search_Bin1(SSTable ST, KeyType key)
{
	int low = 1; 
	int high = ST.length;
	while (low <= high)
	{
		int mid = (low + high) / 2;
		if (key == ST.R[mid].key)
			return mid;	//�ҵ�
		if (key < ST.R[mid].key)
		{
			high = mid - 1;	//key��mid��ߣ���ǰ��������
		}
		else
		{
			low = mid + 1;	//key��mid�ұߣ��ں��������
		}
	}
	return 0;
}

//�۰���ң��ݹ飩
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