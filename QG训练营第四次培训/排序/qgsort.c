#include "qgsort.h"
#include "LinkStack.h"
#include <stdio.h>
#include <stdlib.h>
/*int main()
{
	int array[12] = {3,0,5,6,8,7,4,11,12,9,1,2};
	int b[10] = {0,2,1,0,2,1,2,1,2,1};
	//QuickSort_Recursion(array,0,9);
	//MergeSort(array,0,9,b);
	//insertSort(array,10);
	//RadixCountSort(array,12);
	//ColorSort(b,10);
	//CountSort(array,12,12);
	//QuickSort(array,12);
	int k = 4;
	Search(array,0,11,&k);
	printf("%d",k);
	for(int i=0;i < 12;i++)
	{
		printf("%d",array[i]);
	}
	return 0;
}*/

// 二分插入排序
void insertSort(int *a,int n)
{
	int i,j,low,high,mid,temp;
	for(i=1;i < n;i++)
	{
		temp = a[i];
		low = 0,high = i-1;
		while(low <= high)
		{
			mid = (low + high) / 2;
			if(a[mid] > temp)
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
		}
		for(j=i-1;j >= high;j--)
		{
			a[j+1] = a[j];
		}
		a[high+1] = temp;
	}
}

// 归并排序（合并数组）
void MergeArray(int *a,int begin,int mid,int end,int *temp)
{
	int i,j,k;
	for(k = begin;k <= end;k++)
	{
		temp[k] = a[k];
	}
	for(i=begin,j=mid+1,k=i;i<=mid && j<=end;k++)
	{
		if(temp[i] <= temp[j])
		{
			a[k] = temp[i++];
		}
		else
		{
			a[k] = temp[j++];
		}
	}
	while(i <= mid)
	{
		a[k++] = temp[i++];
	}
	while(j <= end)
	{
		a[k++] = temp[j++];
	}
}

// 归并排序
void MergeSort(int *a,int begin,int end,int *temp)
{
	int mid;
	if(begin < end)
	{
		mid = (begin +end) / 2;
		MergeSort(a,begin,mid,temp);
		MergeSort(a,mid+1,end,temp);
		MergeArray(a,begin,mid,end,temp);
	}
}

// 快速排序（递归版）
void QuickSort_Recursion(int *a, int begin, int end)
{
	int pivotpos;
	if(begin < end)
	{
		pivotpos = Partition(a,begin,end);
		QuickSort_Recursion(a,begin,pivotpos-1);
		QuickSort_Recursion(a,pivotpos+1,end);
	}
}

// 快速排序（非递归版）
void QuickSort(int *a,int size)
{
	LinkStack * stack = (LinkStack *)malloc(sizeof(LinkStack));
	initLStack(stack);
	int mid;
	int left = 0;
	int right = size - 1;
	pushLStack(stack,left);
	pushLStack(stack,right);
	while(!isEmptyLStack(stack))
	{
		popLStack(stack,&right);
		popLStack(stack,&left);
		mid = Partition(a,left,right);
		if(mid - 1 > left)
		{
			pushLStack(stack,left);
			pushLStack(stack,mid-1);
		}
		if(mid + 1 < right)
		{
			pushLStack(stack,mid+1);
			pushLStack(stack,right);
		}
	}
	destroyLStack(stack);
}

// 快速排序（枢轴存放）
int Partition(int *a, int begin, int end)
{
	int pivot = a[begin];
	while(begin < end)
	{
		while(begin < end && a[end] >= pivot)
		{
			end--;
		}
		a[begin] = a[end];
		while(begin < end && a[begin] <= pivot)
		{
			begin++;
		}
		a[end] = a[begin];
	}
	a[begin] = pivot;
	return begin;
}

// 计数排序
void CountSort(int *a, int size , int max)
{
	int b[size];
	int * temp = (int *)malloc(sizeof(int) * (max+1));
	for(int i = 0; i < max+1; i++)
		temp[i] = 0;
	for (int i = 0;i < size;i++)//统计每个元素出现的次数
		temp[a[i]]++;
	for(int i = 1; i < max+1; i++)
		temp[i] += temp[i-1];
	for(int i = size-1;i >= 0 ;i--)
	{
		b[temp[a[i]] - 1] = a[i];
		temp[a[i]] -= 1;
	}
	free(temp);
	for(int i = 0;i < size;i++)
		a[i] = b[i];
}

// 基数计数排序
void RadixCountSort(int *a,int size)
{
	int i,j,k,pos,num,index;
	int * radixArrays[10];
	for(i=0;i<10;i++)
	{
		radixArrays[i] = (int *)malloc(sizeof(int) * (size+1));
		radixArrays[i][0] = 0;
	}
	for(pos=1;pos <= 9;pos++)
	{
		for(i = 0;i < size;i++)
		{
			int temp = 1;
			for(int r = 0;r < pos-1;r++)
			{
				temp *= 10;
			}
			num = (a[i] / temp) % 10;
			index = ++radixArrays[num][0];
			radixArrays[num][index] = a[i];
		}
		for(i=0,j=0;i < 10;i++)
		{
			for(k=1;k <= radixArrays[i][0];k++)
			{
				a[j++] = radixArrays[i][k];
			}
			radixArrays[i][0] = 0;
		}
	}
}

// 颜色排序
void ColorSort(int *a,int size)
{
	int p0,p,p2,temp;
	p = p0 = 0;
	p2 = size - 1;
	while(p != p2)
	{
		if(a[p0] == 0)
		{
			p0++;
			p = p0;
			continue;
		}
		if(a[p2] == 2)
		{
			p2--;
			continue;
		}
		if(a[p] == 1)
		{
			p++;
		}
		if(a[p] == 0)
		{
			temp = a[p0];
			a[p0] = a[p];
			a[p] = temp;
		}
		if(a[p] == 2)
		{
			temp = a[p2];
			a[p2] = a[p];
			a[p] = temp;
		}
	}
	if(a[p] == 0)
	{
		temp = a[p0];
		a[p0] = a[p];
		a[p] = temp;
	}
}

// 在一个无序序列中找到第K大/小的数
void Search(int *a,int begin,int end,int k)
{
	int t = a[begin];
	int i = begin,j = end;
	while (i < j)
	{
		while(i < j && a[j] >= t) j--;
		if(i < j) a[i++] = a[j];
		while(i < j && a[i] <= t) i++;
		if(i < j) a[j--] = a[i];
	}
	a[i] = t;
	if(i == k) printf("第k小的数为:%d",a[i]);
	else if(i > k) Search(a,begin,i-1,k);
	else if(i < k) Search(a,i+1,end,k);
}

Status initLStack(LinkStack *s)
{
	s->top = (LinkStackPtr)malloc(sizeof(StackNode));
	if (!s->top)
		return ERROR;
	s->count = 0;
	return SUCCESS;
}

Status isEmptyLStack(LinkStack *s)
{
	return s->count == 0;
}

Status destroyLStack(LinkStack *s)
{
	LinkStackPtr ptem, p = s->top->next;
	while (s->count != 0)
	{
		ptem = p->next;
		free(p);
		s->top->next = ptem;
		s->count--;
	}
	free(s->top);
	return SUCCESS;
}

Status pushLStack(LinkStack *s,ElemType data)
{
	StackNode *p;
	p = (StackNode*)malloc(sizeof(StackNode));
	p->data = data;
	p->next = s->top->next;
	s->top->next = p;
	s->count++;
	return SUCCESS;
}

Status popLStack(LinkStack *s, ElemType *data)
{
	LinkStackPtr ptem, p = s->top->next;
	*data = p->data;
	ptem = p->next;
	free(p);
	s->top->next = ptem;
	s->count--;
	return SUCCESS;
}
