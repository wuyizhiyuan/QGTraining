#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "AQueue.h"

void menu();
void chose(AQueue * Q);
void enAQueue(AQueue * Q);
void gethead(AQueue * Q);
int s_get_int();
char * s_gets_str(char * str,int lim);
void Exit();

int main(void)
{
	system("color c");
	AQueue * Q = (AQueue *)malloc(sizeof(AQueue));
	InitAQueue(Q);
	menu();
	chose(Q);
	return 0;
}

void menu()
{
	puts("\t***泛型循环队列ADT测试***");
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

void chose(AQueue * Q)
{
	char select;
	A:puts("请输入操作选项:");
	select = getch();
	switch(select)
	{
		case '1':
			DestoryAQueue(Q);
				Exit();
			break;
		case '2':
			if(IsEmptyAQueue(Q))
				puts("该队列为空！");
			else
				puts("该队列不为空！");
			break;
		case '3':
			gethead(Q);
			puts("");
			break;
		case '4':
			printf("现有长度为%d\n",LengthAQueue(Q));
			break;
		case '5':
			enAQueue(Q);
			break;
		case '6':
			if(DeAQueue(Q))
				puts("出队成功！");
			break;
		case '7':
			ClearAQueue(Q);
			puts("队列已空！");
			break;
		case '8':
			TraverseAQueue(Q,APrint);
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

void enAQueue(AQueue * Q)
{
	char a;
	int b;
	double c;
	char x[64];
	puts("\t\t\t请输入想入队的类型？");
	puts("\t\t字符请按 1，整数请按 2，浮点数请按 3，字符串请按 4 ");
	B:type = getch();
	switch(type)
	{
		case '1':
			puts("请输入字符!");
			a = getchar();
			fflush(stdin);
			if(EnAQueue(Q,&a))
			{
				puts("输入成功！");
				datatype[(Q->rear-1+Q->length) % Q->length] = type;
			}
			break;
		case '2':
			puts("请输入整数!");
			b = s_get_int();
			if(EnAQueue(Q,&b))
			{
				puts("输入成功！");
				datatype[(Q->rear-1+Q->length) % Q->length] = type;
			}
			break;
		case '3':
			puts("请输入浮点数!");
			s_gets_str(x,64);
			M:c = atof(x);
			if(c == 0)
			{
				int i = 0;
				while(x[i++] != '\0')
				{
					if (x[i] != '0' && x[i] != '.')
					{
						puts("输入错误，请重新输入\n");
						s_gets_str(x,64);
						goto M;
					}
				}
			}
			if(EnAQueue(Q,&c))
			{
				puts("输入成功！");
				datatype[(Q->rear-1+Q->length) % Q->length] = type;
			}
			break;
		case '4':
			puts("请输入字符串(不超过64个字符)!");
			s_gets_str(x,64);
			if(EnAQueue(Q,x))
			{
				puts("输入成功！");
				datatype[(Q->rear-1+Q->length) % Q->length] = type;
			}
			break;
		default:
			goto B;
	}

}

void gethead(AQueue * Q)
{
	type = datatype[Q->front];
	if(type == '1')
	{
		char e;
		if(GetHeadAQueue(Q,&e))
			APrint(&e);
	}
	else if(type == '2')
	{
		int e = 0;
		if(GetHeadAQueue(Q,&e))
			APrint(&e);
	}
	else if(type == '3')
	{
		double e;
		if(GetHeadAQueue(Q,&e))
			APrint(&e);
	}
	else
	{
		char e[64];
		if(GetHeadAQueue(Q,e))
			APrint(e);
	}
}

int s_get_int()
{
    char str[9];
    int i = 0;

    fflush(stdin);
    while ((str[i] = getchar()) != '\n' && i <= 9)
    {
        if (str[i]<'0' || str[i]>'9')
        {
            puts("非法输入,请重新输入(暂时不支持负数)");
            fflush(stdin);
            i = 0;
            continue;
        }
        i++;
    }
    str[i] = '\0';
    return atoi(str);
}

char * s_gets_str(char * str,int lim)
{
	char * ret_val;
	char * find;

	ret_val = fgets(str,lim,stdin);
	if(ret_val)
	{
		find = strchr(str,'\n');
		if(find)
		{
			*find = '\0';
		}
		else
		{
			while(getchar() != '\n')
				continue;
		}
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
