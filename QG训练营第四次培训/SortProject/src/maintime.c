#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "qgsort.h"

void randNum( int* a, int count);
void timeTest(int *a,int size, int count);

int main()
{
	int a[100];
	puts("��10k������100����������ʱ������:");
	timeTest(a,100, 10000);
	printf("\n\n\n");
	puts("��50k������100����������ʱ������:");
	timeTest(a,100, 50000);
	printf("\n\n\n");
	puts("��200k������100����������ʱ������:");
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
	printf("����������ʱ%ld ms\n",finish-start);

	start = clock();
	for(int i =0 ;i < count;i++)
	{
		randNum(a,size);
		MergeSort(a,0,size-1,t);
	}
	finish = clock();
	printf("�鲢������ʱ%ld ms\n",finish-start);

	start = clock();
	for(int i =0 ;i < count;i++)
	{
		randNum(a,size);
		QuickSort_Recursion(a, 0,size-1);
	}
	finish = clock();
	printf("��������(�ݹ��)��ʱ%ld ms\n",finish-start);

	start = clock();
	for(int i =0 ;i < count;i++)
	{
		randNum(a,size);
		QuickSort(a,size);
	}
	finish = clock();
	printf("��������(�ǵݹ��)��ʱ%ld ms\n",finish-start);

	start = clock();
	for(int i =0 ;i < count;i++)
	{
		randNum(a,size);
		RadixCountSort(a,size);
	}
	finish = clock();
	printf("����������ʱ%ld ms\n",finish-start);
}

