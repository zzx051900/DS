//BF算法和KMP算法的简单理解
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

int Index_BF(char* a, char* b, int len1, int len2);	//BF算法
int Index_KMP(char* a, char* b, int len1, int len2, int* next);	//KMP算法
void get_next(char*b, int len, int* next);	//求next数组

int main()
{
	char a[] = "aaaabc";
	char b[] = "abc";
	int len_a = strlen(a);
	int len_b = strlen(b);
	int next[4] = { 0 };
	printf("BF求解出子串在主串中是位置是：%d\n", Index_BF(a, b, len_a, len_b));	
	get_next(b, len_b, next);
	printf("KP求解出子串在主串中是位置是：%d\n", Index_KMP(a, b, len_a, len_b, next));

	return 0;
}

int Index_BF(char* a, char* b, int len1, int len2)
{
	int i = 1, j = 1;
	while (i <= len1 && j <= len2)
	{
		if (a[i] == b[j]) //比较成功时，主串和子串依次匹配下一个字符
		{
			++i;
			++j;
		}
		else //主串、子串指针回溯，重新开始下一次匹配      
		{
			i = i - j + 2;//i-(j-1)+1	，回退 j-1 个，回到主串中这次比较时开始的位置，+1表示从下一个位置开始下一轮的比较
			j = 1;
		}
	}
	if (j >= len2)
		return i - len2;//返回匹配的第一个字符下标
	return 0;//未匹配成功
}

int Index_KMP(char* a, char* b, int len1, int len2, int* next)
{
	int i = 1, j = 1;
	while (i <= len1 && j <= len2)
	{
		if (j == 0 || a[i] == b[j]) //比较成功时，主串和子串依次匹配下一个字符
		{
			++i;
			++j;
		}
		else //主串、子串指针回溯，重新开始下一次匹配      
		{
			j = next[j];
		}
	}
	if (j > len2)
		return i - len2;//返回匹配的第一个字符下标
	return 0;//未匹配成功
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