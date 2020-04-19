#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "qgsort.h"

void randNum( int* a, int count);
void timeTest(int *a,int size, int count);

int main()
{
	int a[100];
	puts("在10k次数下100给数据排序时间如下:");
	timeTest(a,100, 10000);
	printf("\n\n\n");
	puts("在50k次数下100给数据排序时间如下:");
	timeTest(a,100, 50000);
	printf("\n\n\n");
	puts("在200k次数下100给数据排序时间如下:");
	timeTest(a,100, 200000);
}

void randNum( int* a, int count )
{

	int i = 0;

	while( i < count )
	{
		a[i++] = rand() % (count+1);

	}

}

void timeTest(int *a,int size,int count)
{
	int t[200000];
	clock_t start, finish;

	start = clock();
	for(int i =0 ;i < count;i++)
	{
		randNum(a,size);
		insertSort(a,size);
	}
	finish = clock();
	printf("插入排序用时%ld ms\n",finish-start);

	start = clock();
	for(int i =0 ;i < count;i++)
	{
		randNum(a,size);
		MergeSort(a,0,size-1,t);
	}
	finish = clock();
	printf("归并排序用时%ld ms\n",finish-start);

	start = clock();
	for(int i =0 ;i < count;i++)
	{
		randNum(a,size);
		QuickSort_Recursion(a, 0,size-1);
	}
	finish = clock();
	printf("快速排序(递归版)用时%ld ms\n",finish-start);

	start = clock();
	for(int i =0 ;i < count;i++)
	{
		randNum(a,size);
		QuickSort(a,size);
	}
	finish = clock();
	printf("快速排序(非递归版)用时%ld ms\n",finish-start);

	start = clock();
	for(int i =0 ;i < count;i++)
	{
		randNum(a,size);
		RadixCountSort(a,size);
	}
	finish = clock();
	printf("基数排序用时%ld ms\n",finish-start);
}

