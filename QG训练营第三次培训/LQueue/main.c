#include "LQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void setType();
void menu();
void chose(LQueue * Q);
void enLQueue(LQueue * Q);
char * s_gets(char *st,int n);
int s_get_int();
void Exit();

int main()
{
	system("color c");
	LQueue * Q = (LQueue *)malloc(sizeof(LQueue));
	puts("\t***泛型链式队列ADT测试***");
	puts("请先确定队列要存取的数据类型:\nchar型请按1\tint型请按2\tdouble型请按3\tstring型请按4");
	setType();
	InitLQueue(Q);
	menu();
	chose(Q);
	return 0;
}

// 操作
void chose(LQueue * Q)
{
	size_t temp;
	char select;
	void *t;
	A:select = getch();
	switch(select)
	{
		case '1':
			DestoryLQueue(Q);
			Exit();
		case '2':
			if(IsEmptyLQueue(Q))
				puts("队列为空!");
			else
			puts("队列不为空!");
			break;
		case '3':
			if(type == '1')
				temp = sizeof(char);
			else if(type == '2')
				temp = sizeof(int);
			else if(type == '3')
				temp = sizeof(double);
			else
				temp = 100 * sizeof(char);
			t = malloc(temp);
			if(GetHeadLQueue(Q,t))
			{
				printf("队头数据为");
				LPrint(t);
				puts("");
			}
			else
				puts("队列为空!");
			break;
		case '4':
			printf("队列长度为%d！\n",LengthLQueue(Q));
			break;
		case '5':
			enLQueue(Q);
			puts("入队成功！");
			break;
		case '6':
			if(DeLQueue(Q))
				puts("出队成功！");
			else
			 puts("队列为空！");
			break;
		case '7':
			ClearLQueue(Q);
			puts("清空成功！");
			break;
		case '8':
			TraverseLQueue(Q,LPrint);
			break;
		case '9':
			system("cls");
			menu();
			break;
		default:
			goto A;
	}
	chose(Q);
}

// 打印菜单
void menu()
{
	puts("\t***泛型链式队列ADT测试***");
	puts("\t\t1.删除队列并退出系统");
	puts("\t\t2.判断队列是否为空");
	puts("\t\t3.输出头结点数据");
	puts("\t\t4.输出队列现有长度");
	puts("\t\t5.入队操作");
	puts("\t\t6.出队操作");
	puts("\t\t7.清空队列");
	puts("\t\t8.遍历队列");
	puts("\t\t9.清空记录");
}

// 入队处理
void enLQueue(LQueue * Q)
{
	char c[100];
	char x;
	if(type == '2')
	{
		int a = 0;
		puts("请输入整形数据:");
		a = s_get_int();
		EnLQueue(Q,&a);
	}
	else if(type == '1')
	{
		puts("请输入字符");
		x = getchar();
		fflush(stdin);
		EnLQueue(Q,&x);
	}
	else if(type == '3')
	{
		double d;
		puts("请输入浮点数据");
		s_gets(c,100);
		M:d = atof(c);
		if(d == 0)
		{
			int i = 0;
			while(c[i++] != '\0')
			{
				if (c[i] != '0' && c[i] != '.')
				{
				puts("输入错误，请重新输入\n");
				s_gets(c,100);
				goto M;
				}
			}
		}
		EnLQueue(Q,&d);
	}
	else if(type == '4')
	{
		puts("请输入数据");
		s_gets(c,100);
		EnLQueue(Q,&c);
	}
}

// 获取整形变量
int s_get_int()
{
	char in[11];
	int t;
	s_gets(in,11);
	t = atoi(in);
	if (t == 0)
	{
		if (in[1] != 0 || in[2] != '\0')
		{
			printf("输入错误，请重新输入！\n");
			t = s_get_int();
		}
	}
	return t;
}

// 选择泛型
void setType()
{
	B:type = getch();
	switch(type)
	{
		case '1':
			break;
		case '2':
			break;
		case '3':
			break;
		case '4':
			break;
		default:
			goto B;
	}
}

//获取键盘输入
char * s_gets(char *st,int n)
{
    char * ret_val;
    char * find;

    fflush(stdin);
    ret_val = fgets(st,n,stdin);
    if (ret_val)
    {
        find = strchr(st,'\n');
        if (find)
            *find = '\0';
        else
            while (getchar() != '\n')
                    continue;
    }
    return ret_val;
}

void Exit()
{
	system("pause");
	puts("\t\t\t感谢使用！\n\n\n");
	system("pause");
	system("cls");
	for (float y = 1.5; y > -1.5; y -= 0.1)
	{
		for (float x = -1.5; x < 1.5; x += 0.04)
		{
			float a = x * x + y * y - 1;
			putchar(a * a * a - x * x * y * y * y <= 0.0 ? '*' : ' ');
		}
		putchar('\n');
	}
	system("pause");
	exit(0);
}
