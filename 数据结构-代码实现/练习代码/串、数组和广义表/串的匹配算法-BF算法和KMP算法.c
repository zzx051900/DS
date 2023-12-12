//BF�㷨��KMP�㷨�ļ����
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

int Index_BF(char* a, char* b, int len1, int len2);	//BF�㷨
int Index_KMP(char* a, char* b, int len1, int len2, int* next);	//KMP�㷨
void get_next(char*b, int len, int* next);	//��next����

int main()
{
	char a[] = "aaaabc";
	char b[] = "abc";
	int len_a = strlen(a);
	int len_b = strlen(b);
	int next[4] = { 0 };
	printf("BF�����Ӵ�����������λ���ǣ�%d\n", Index_BF(a, b, len_a, len_b));	
	get_next(b, len_b, next);
	printf("KP�����Ӵ�����������λ���ǣ�%d\n", Index_KMP(a, b, len_a, len_b, next));

	return 0;
}

int Index_BF(char* a, char* b, int len1, int len2)
{
	int i = 1, j = 1;
	while (i <= len1 && j <= len2)
	{
		if (a[i] == b[j]) //�Ƚϳɹ�ʱ���������Ӵ�����ƥ����һ���ַ�
		{
			++i;
			++j;
		}
		else //�������Ӵ�ָ����ݣ����¿�ʼ��һ��ƥ��      
		{
			i = i - j + 2;//i-(j-1)+1	������ j-1 �����ص���������αȽ�ʱ��ʼ��λ�ã�+1��ʾ����һ��λ�ÿ�ʼ��һ�ֵıȽ�
			j = 1;
		}
	}
	if (j >= len2)
		return i - len2;//����ƥ��ĵ�һ���ַ��±�
	return 0;//δƥ��ɹ�
}

int Index_KMP(char* a, char* b, int len1, int len2, int* next)
{
	int i = 1, j = 1;
	while (i <= len1 && j <= len2)
	{
		if (j == 0 || a[i] == b[j]) //�Ƚϳɹ�ʱ���������Ӵ�����ƥ����һ���ַ�
		{
			++i;
			++j;
		}
		else //�������Ӵ�ָ����ݣ����¿�ʼ��һ��ƥ��      
		{
			j = next[j];
		}
	}
	if (j > len2)
		return i - len2;//����ƥ��ĵ�һ���ַ��±�
	return 0;//δƥ��ɹ�
}
void get_next(char* b, int len, int* next)
{
	int i = 1, j = 0;
	next[1] = 0;	
	while (i<len)
	{
		if (j == 0 || b[i] == b[j])
		{
			++i;
			++j;
			next[i] = j;
		}
		else
		{
			j = next[j];
		}		
	}
}