#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <stdbool.h>
#include "function.h"

void FixedWindow()			// 设置cmd窗口
{
	system("mode con cols=70 lines=40");
	SetWindowLongPtrA(GetConsoleWindow(),GWL_STYLE,GetWindowLongPtrA(GetConsoleWindow(),GWL_STYLE)& ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
	system("color 34");
}

void gotoxy(int x,int y) 	 	//光标移动到(x,y)位置
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void DrawBoundary()			// 绘制边框
{
	for(int i = 1;i <= WINDOWHIGH;i++)
	{
		if(i == 1 || i == WINDOWHIGH)
		{
			for (int k = 1;k <= WINDOWWIDTH / 2;k++)
			{
				printf("█");
				Sleep(10);
			}
			if(i == 1)
			{
				printf("\n");
			}
			continue;
		}
		for(int j = 1;j <= WINDOWWIDTH - 1;j++)
		{
			if(j == 1 || j == WINDOWWIDTH - 1)
			{
				printf("█");
			}
			else if(j == 2)
			{
				continue;
			}
			else
			{
				putchar(' ');
			}
		}
		printf("\n");
	}
	gotoxy(28,15);
	printf("欢迎使用计算器！");
	gotoxy(28,20);
	system("pause");
	system("cls");
	for(int i = 0;i < 171;i++)
	{
		if(i == 85)
		{
			printf("欢迎使用！");
		}
		else
		{
			if(i < 35 || i > 135)
			{
				printf("█");
			}
			else
			{
				printf("**");
			}
		}
	}
	printf("\n\n\n");
}

//进数字栈
void push1(Stack1 * stack,double e)
{
	Node1 * p;
	p = (Node1 *)malloc(sizeof(Node1));
	p->data = e;
	p->next = stack->top;
	stack->quantity++;
	stack->top = p;
}

//进符号栈
void push2(Stack2 * stack,char e)
{
	Node2 * p;
	p = (Node2 *)malloc(sizeof(Node2));
	p->data = e;
	p->next = stack->top;
	stack->quantity++;
	stack->top = p;
}

//出数字栈
double pop1(Stack1 * stack)
{
	double e;
	e = stack->top->data;
	Node1 * p;
	p = stack->top;
	stack->top = p->next;
	stack->quantity--;
	free(p);
	return e;
}

//出符号栈
char pop2(Stack2 * stack)
{
	char e;
	e = stack->top->data;
	Node2 * p;
	p = stack->top;
	stack->top = p->next;
	stack->quantity--;
	free(p);
	return e;
}

//判断优先级
Status priority(char c)
{
	switch(c)
	{
		case'+':
		case'-':
			return 1;
		case'*':
		case'/':
			return 2;
		case'(':
			return 3;
		case')':
		case'=':
			return -1;
		default:
			return 0;
	}
}

//两个栈初始化
void InitStack(Stack1 * num,Stack2 * sign)
{
	num->quantity = 0;
	sign->quantity = 0;
	num->top = NULL;
	sign->top = NULL;

}

char * s_gets(char * str)		// 输入函数
{
	char * ret_val;
	char * find;

	ret_val = fgets(str,MAX,stdin);
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
	remove_blank(ret_val);	// 剔除空格
	return ret_val;
}

// 计算主函数
void calculate()
{
	Stack1 num;		// 定义一个数字栈
	Stack2 sign;		// 定义一个符号栈
	char temp,posture[MAX],digit[MAXBIT];
	int i,j;
	double a;
	InitStack(&num,&sign);	// 初始化栈
	i = j = 0;

	A:s_gets(posture);	//记号A
	if(!judge(posture))
		goto A;
	if(posture[0] == '\0' || (posture[0] == '=' && posture[1] == '\0'))	// 按 回车 和输入 等号 的话继续输入
		goto A;

	while((temp = posture[i]) != '\0')
	{

		if(i >= MAX)
		{
			puts("式子过长！");
			return;
		}
		if(isdigit(temp) || temp == '.')	// 处理数字
		{
			i++;
			digit[j++] = temp;
			digit[j] = '\0';
			if(j >= MAXBIT)
			{
				puts("数据过大！");
				return;
			}
			if(!isdigit(posture[i]) &&  posture[i] != '.')
			{
				a = atof(digit);
				push1(&num,a);
				j = 0;
			}
			continue;
		}
		if(sign.quantity == 0 || priority(temp) > priority(sign.top->data) || (sign.top->data == '(' && temp != ')'))	// 判断是否进栈
		{
			i++;
			push2(&sign,temp);
			continue;
		}
		if(sign.top->data == '(' && temp == ')')
		{
			i++;
			pop2(&sign);
			continue;
		}
		if(sign.quantity != 0)
		{
			a = 0;
			switch(pop2(&sign))
			{
				case'+':
					a = pop1(&num) + pop1(&num);
					push1(&num,a);
					break;
				case'-':
					a = pop1(&num);
					push1(&num,pop1(&num) - a);
					break;
				case'*':
					a = pop1(&num) * pop1(&num);
					push1(&num,a);
					break;
				case'/':
					a = pop1(&num);
					if(a == 0)
					{
						printf("除数不能为零！\n");
						return;
					}
					push1(&num,pop1(&num) / a);
					break;
			}
		}
	}
	printf("%s\t\t%g\n\n",posture,pop1(&num));
}


bool egal(char ch) 	// 除了+-*/.()=之外的输入皆为非法
{
	if(ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '.' && ch != '(' && ch != ')' && ch!= '=')
		return false;
	return true;
}

// 检测是否有非法输入
bool judge(char * ch)
{
	space_blank_bracket(ch);	// 剔除空括号先
	int l,r; // 用于计算左括号数量以及右括号数量
	l = r = 0;
	for(int j = 0;ch[j] !='\0';j++)
	{
		if(ch[j] == '(')
			l++;
		if(ch[j] == ')')		// 检查左右括号数量是否相同,或右括号是否提前比左括号先出现
			r++;
		if(r > l)
		{
			puts("使用括号错误！");
			return false;
		}
	}
	if(r != l)
	{
		puts("左括号与右括号数量不等！");
		return false;
	}
	int i,t; // i用于遍历字符串，t用于检查小数点是否错使用错误
	for(i = 0;ch[i] != '\0';i++)
	{
		if(!isdigit(ch[i]) && !egal(ch[i]))		// 除了数字，小数点，+-*/() 之外，其他皆为非法输入
		{
			puts("非法输入！请继续输入！");
			return false;
		}
		if(ch[i] == '.')			// 小数点后只能是数字，且该数不能再出现小数点，否则报错
		{
			if(!isdigit(ch[i-1]) || !isdigit(ch[i+1]))
			{
				puts("使用小数点出现错误！请继续输入！");
				return false;
			}
			t = i;
			while(isdigit(ch[++t]))
				continue;
			if(ch[t] == '.')
			{
				puts("使用小数点出现错误！请继续输入！");
				return false;
			}
		}
		if(ch[i] == '+' || ch[i] == '-' || ch[i] == '*' || ch[i] == '/')	// +-*/ 后只能是数字或 (
		{
			if(!isdigit(ch[i+1]) && ch[i+1] != '(')
			{
				puts("使用符号出现错误！请继续输入！");
				return false;
			}

		}
		if(ch[i] == '=')			// 等号后面不能再出现任何东西，等号前不能出现 +-*/，否则报错
		{
			if(ch[i+1] != '\0')
			{
				puts("使用等号处错误！请继续输入！");
				return false;
			}
			if(ch[i-1] == '+' || ch[i-1] == '-' || ch[i-1] == '*' || ch[i-1] == '/')
			{
				puts("等号前一位不能是运算符号！");
				return false;
			}
		}
		if( (isdigit(ch[i]) && ch[i+1] == '(') || (ch[i+1] == ')' && isdigit(ch[i+1])) )	// 数字后不能为左括号，右括号后不能为数字
		{
			puts("使用括号错误！");
			return false;
		}
		if(ch[i] == '-')		// 负号在式子开头 或 负号前为 ( ，则需要在前面加0
		{
			if(i == 0 || ch[i-1] == '(')
			{
				int j;
				char temp2  = '0';
				char temp1;
				for(j = i;ch[j] != '\0';j++)
				{
					temp1 = ch[j];
					ch[j] = temp2;
					temp2 = temp1;;
				}
				ch[j] = temp2;
				ch[j+1] = '\0';
			}
		}
	}
	if(ch[0] == '+' || ch[0] == '*' || ch[0] == '/')	// 如果字符串第一位为四则运算符号的话也报错
	{
		puts("使用符号出现错误！请继续输入！");
		return false;
	}
	if(ch[i-1] != '=')			// 假如没有输入等号，则自动补上
	{
		ch[i] = '=';
		ch[i+1] = '\0';
	}
	return true;
}

// 剔除空格
void remove_blank(char * ch)
{
	char * c;//指向字符串的字符处
	while (*ch != ' ')
	{
		if (*ch == '\0')
		{
			//字符串中没有空格,直接返回
			return;
		}
		ch++;
	}//将blank指针指向第一个空格位置
	//让c指针指向出现空格后的第一个字符串
	c = ch + 1;
	while(*c == ' ')
	{
		c++;
	}
	while (*c != '\0')
	{
		if (*c != ' ')
		{
			//将空格换为后面出现的字符，换过去的字符置为空格
			*ch = *c;
			*c = ' ';
			ch++;
		}
		c++;
	}
	*ch = '\0';
	return;
}

// 剔除空括号
void space_blank_bracket(char * ch)
{
	for(int i = 0;ch[i] != '\0';i++)
	{
		if(ch[i] == '(' && ch[i+1] == ')')
		{
			int j;
			for(j = i+2;ch[j] != '\0';j++)
			{
				ch[j-2] = ch[j];
			}
			ch[j-2] = '\0';
			i = -1;
		}
	}
}

// 过渡函数
bool transit()
{
	char ch[MAXBIT];
	puts("请选择你的操作：按 y/Y 可以重置计算器！按 n/N 继续 按 q/Q 退出！");
        s_gets(ch);
        if((ch[0] == 'q' || ch[0] == 'Q') && ch[1] == '\0')
	{
		Exit();
	}
        if((ch[0] == 'y' || ch[0] == 'Y') && ch[1] == '\0')
		return true;
	puts("请继续！");
	return false;
}

void Exit()
{
	system("pause");
	system("cls");
	puts("\n\n\n\t\t\t感谢使用！\n\n\n");
	system("pause");
	system("cls");
	float x,y,a;
	for(y=1.5f;y>-1.5f;y-=0.1f)
	{
		for(x=-1.5f;x<1.5f;x+=0.05f)
		{
			a=x*x+y*y-1;
			putchar(a*a*a-x*x*y*y*y<=0.0f?'*':' ');
		}
		putchar('\n');
	}
	system("pause");
	exit(0);
}

