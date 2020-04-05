#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SqStack.h"

int s_get_int();
void select(SqStack *s);
void menu();
void Exit();

int main(void)
{
	system("color c");
	SqStack *s ;
	int size = 0;
	s = (SqStack *)malloc(sizeof(SqStack));
	while(size <= 0 || size > 99999999)
	{
		puts("输入即将创建栈的大小(1-99999999):");
		size = s_get_int();
	}
	initStack(s,size);
	system("cls");
	menu();
	puts("请输入操作选项");
	select(s);
	return 0;
}

void menu()
{
    puts("\t**顺序栈测试**");
    puts("\t1.判断栈是否为空");
    puts("\t2.输出栈顶元素");
    puts("\t3.清空栈内元素");
    puts("\t4.测试栈的实际长度");
    puts("\t5.入栈操作");
    puts("\t6.出栈操作");
    puts("\t7.销毁栈并退出系统");
    puts("\t8.清空操作记录");
}

void select(SqStack *s)
{
	ElemType e;

	switch(s_get_int())
	{
		case 1:
			if(isEmptyStack(s))
				puts("栈内为空");
			else
				puts("栈不为空");
			break;
		case 2:
			if(getTopStack(s,&e))
				printf("栈顶元素为%d\n",e);
			else
				puts("栈为空，操作失败");
			break;
		case 3:
			clearStack(s);
			puts("操作成功");
			break;
		case 4:
			stackLength(s,&e);
			printf("栈的实际长度为%d\n",e);
			break;
		case 5:
			puts("请输入入栈数据：");
			if(pushStack(s,s_get_int()))
				puts("操作成功");
			else
				puts("操作失败");
			break;
		case 6:
			if(popStack(s,&e))
				puts("操作成功");
			else
				puts("操作失败");
			break;
		case 7:
			destroyStack(s);
			Exit();
			exit(0);
		case 8:
			system("cls");
			menu();
			break;
		default :
			puts("请在范围内输入：");
	}
	puts("请输入操作选项");
	select(s);
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
}
