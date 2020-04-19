#include <stdio.h>
#include <stdlib.h>
#include "qgsort.h"

void menu();
int s_get_int();
void randNum( int* a, int count ,int max);
void reandTxt(int *a,int size,int max);
void printArr(int *a,int size);

int main()
{
	int select = 0,temp = 0,*a;
	int size,max;
	menu();
	while(1)
	{
		puts("请输入正确的指令");
		select = s_get_int();
		if(select == 10)
			exit(0);
		if(select == 9)
		{
			system("cls");
			menu();
			puts("请输入正确的指令");
			select = s_get_int();
		}
		//数组赋值部分
		puts("请输入数组长度");
		size = s_get_int();
		a = (int *)malloc(sizeof(int) * size);
		puts("请输入数组允许的最大值");
		max = s_get_int();
		puts("1.随机生成一个数组。2.从txt读取一个符合条件的数组");
		temp = s_get_int();
		do{
			if (temp == 1) randNum(a,size,max);
			else if (temp == 2) reandTxt(a,size,max);
			else puts("输入错误！请重新输入");
		}while(temp != 1 && temp != 2);
		//具体操作部分
		switch(select)
		{
			case 1:
				puts("排序前数组");
				printArr(a,size);
				insertSort(a,size);
				puts("排序后数组");
				printArr(a,size);
				break;

			case 2:{
				int *temp;
				temp = (int *)malloc(sizeof(int) * (size + 1));
				puts("排序前数组");
				printArr(a,size);
				MergeSort(a,0,size-1,temp);
				puts("排序后数组");
				printArr(a,size);
				free(temp);
				break;
			}
			case 3:
				puts("排序前数组");
				printArr(a,size);
				QuickSort_Recursion(a,0,size-1);
				puts("排序后数组");
				printArr(a,size);
				break;
			case 4:
				puts("排序前数组");
				printArr(a,size);
				QuickSort(a,size);
				puts("排序后数组");
				printArr(a,size);
				break;

			case 5:
				puts("排序前数组");
				printArr(a,size);
				CountSort(a, size ,max);
				puts("排序后数组");
				printArr(a,size);
				break;
			case 6:
				puts("排序前数组");
				printArr(a,size);
				RadixCountSort(a,size);
				puts("排序后数组");
				printArr(a,size);
				break;
			case 7:
				if(max > 2)
				{
					puts("颜色排序只能排序0,1,2！");
					break;
				}
				puts("排序前数组");
				printArr(a,size);
				ColorSort(a,size);
				puts("排序后数组");
				printArr(a,size);
				break;
			case 8:{
				puts("你要找第几小的数？");
				int k = s_get_int();
				if(k == 0 || k > size)
				{
					puts("k的输入不合法！");
					break;
				}
				puts("数组为");
				printArr(a,size);
				k--;
				Search(a,0,size-1,k);
				//printf("第k小的数为:%d",k);
				break;
			}
			default:puts("输入错误！");
		}
	}
	return 0;
}

void reandTxt(int *a,int size,int max)
{
	FILE *fp = fopen("arr.txt","r");
	int s = 0,m = 0,flag = 0;

	while(!feof(fp))
	{
		fscanf(fp,"%d %d",&s,&m);
		if(s == size && m == max)
		{
			for(int i = 0;i < size;i++)
			{
				fscanf(fp,"%d",&a[i]);
			}
			flag = 1;
			break;
		}
	}
	fclose(fp);
	if(flag == 0)
	{
		puts("未能从txt文件中找到符合条件的数组");
		puts("现随机创建一个符合条件的数组并存入txt");
		randNum(a,size,max);
	}
}

void menu()
{
	puts("\t\t欢迎来到排序测试程序");
	puts("\t\t1.测试插入程序");
	puts("\t\t2.测试归并排序");
	puts("\t\t3.测试快速排序（递归版）");
	puts("\t\t4.测试快速排序（非递归版）");
	puts("\t\t5.测试计数排序");
	puts("\t\t6.测试基数计数排序");
	puts("\t\t7.测试颜色排序");
	puts("\t\t8.在一个无序序列中找到第K小的数");
	puts("\t\t9.请空操作记录");
	puts("\t\t10.退出测试系统");

}

void printArr(int *a,int size)
{
	for(int i = 0;i < size;i++)
		printf("%d ",a[i]);
	puts("");
}

int s_get_int()
{
    char str[100];
    int i = 0;

    fflush(stdin);
    while ( (str[i] = getchar()) != '\n')
    {
        if (str[i]<'0' || str[i]>'9')
        {
            puts("非法输入,请重新输入(数字)");
            fflush(stdin);
            i = 0;
            continue;
        }
        i++;
    }
    str[i] = '\0';
    return atoi(str);
}

// 生成随机数
void randNum(int* a,int size,int max)
{
	int i = 0;
	FILE *fp = fopen("arr.txt","a+");
	fprintf(fp,"%d %d ",size,max);
	while( i < size )
	{
		a[i] = rand() % (max + 1);
		fprintf(fp,"%d ",a[i]);
		i++;
	}
	fprintf(fp,"\n");
	fclose(fp);
}
