#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <stdbool.h>
#include "function.h"

void FixedWindow()			// ����cmd����
{
	system("mode con cols=70 lines=40");
	SetWindowLongPtrA(GetConsoleWindow(),GWL_STYLE,GetWindowLongPtrA(GetConsoleWindow(),GWL_STYLE)& ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
	system("color 34");
}

void gotoxy(int x,int y) 	 	//����ƶ���(x,y)λ��
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void DrawBoundary()			// ���Ʊ߿�
{
	for(int i = 1;i <= WINDOWHIGH;i++)
	{
		if(i == 1 || i == WINDOWHIGH)
		{
			for (int k = 1;k <= WINDOWWIDTH / 2;k++)
			{
				printf("��");
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
				printf("��");
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
	printf("��ӭʹ�ü�������");
	gotoxy(28,20);
	system("pause");
	system("cls");
	for(int i = 0;i < 171;i++)
	{
		if(i == 85)
		{
			printf("��ӭʹ�ã�");
		}
		else
		{
			if(i < 35 || i > 135)
			{
				printf("��");
			}
			else
			{
				printf("**");
			}
		}
	}
	printf("\n\n\n");
}

//������ջ
void push1(Stack1 * stack,double e)
{
	Node1 * p;
	p = (Node1 *)malloc(sizeof(Node1));
	p->data = e;
	p->next = stack->top;
	stack->quantity++;
	stack->top = p;
}

//������ջ
void push2(Stack2 * stack,char e)
{
	Node2 * p;
	p = (Node2 *)malloc(sizeof(Node2));
	p->data = e;
	p->next = stack->top;
	stack->quantity++;
	stack->top = p;
}

//������ջ
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

//������ջ
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

//�ж����ȼ�
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

//����ջ��ʼ��
void InitStack(Stack1 * num,Stack2 * sign)
{
	num->quantity = 0;
	sign->quantity = 0;
	num->top = NULL;
	sign->top = NULL;

}

char * s_gets(char * str)		// ���뺯��
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
	remove_blank(ret_val);	// �޳��ո�
	return ret_val;
}

// ����������
void calculate()
{
	Stack1 num;		// ����һ������ջ
	Stack2 sign;		// ����һ������ջ
	char temp,posture[MAX],digit[MAXBIT];
	int i,j;
	double a;
	InitStack(&num,&sign);	// ��ʼ��ջ
	i = j = 0;

	A:s_gets(posture);	//�Ǻ�A
	if(!judge(posture))
		goto A;
	if(posture[0] == '\0' || (posture[0] == '=' && posture[1] == '\0'))	// �� �س� ������ �Ⱥ� �Ļ���������
		goto A;

	while((temp = posture[i]) != '\0')
	{

		if(i >= MAX)
		{
			puts("ʽ�ӹ�����");
			return;
		}
		if(isdigit(temp) || temp == '.')	// ��������
		{
			i++;
			digit[j++] = temp;
			digit[j] = '\0';
			if(j >= MAXBIT)
			{
				puts("���ݹ���");
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
		if(sign.quantity == 0 || priority(temp) > priority(sign.top->data) || (sign.top->data == '(' && temp != ')'))	// �ж��Ƿ��ջ
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
						printf("��������Ϊ�㣡\n");
						return;
					}
					push1(&num,pop1(&num) / a);
					break;
			}
		}
	}
	printf("%s\t\t%g\n\n",posture,pop1(&num));
}


bool egal(char ch) 	// ����+-*/.()=֮��������Ϊ�Ƿ�
{
	if(ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '.' && ch != '(' && ch != ')' && ch!= '=')
		return false;
	return true;
}

// ����Ƿ��зǷ�����
bool judge(char * ch)
{
	space_blank_bracket(ch);	// �޳���������
	int l,r; // ���ڼ��������������Լ�����������
	l = r = 0;
	for(int j = 0;ch[j] !='\0';j++)
	{
		if(ch[j] == '(')
			l++;
		if(ch[j] == ')')		// ����������������Ƿ���ͬ,���������Ƿ���ǰ���������ȳ���
			r++;
		if(r > l)
		{
			puts("ʹ�����Ŵ���");
			return false;
		}
	}
	if(r != l)
	{
		puts("���������������������ȣ�");
		return false;
	}
	int i,t; // i���ڱ����ַ�����t���ڼ��С�����Ƿ��ʹ�ô���
	for(i = 0;ch[i] != '\0';i++)
	{
		if(!isdigit(ch[i]) && !egal(ch[i]))		// �������֣�С���㣬+-*/() ֮�⣬������Ϊ�Ƿ�����
		{
			puts("�Ƿ����룡��������룡");
			return false;
		}
		if(ch[i] == '.')			// С�����ֻ�������֣��Ҹ��������ٳ���С���㣬���򱨴�
		{
			if(!isdigit(ch[i-1]) || !isdigit(ch[i+1]))
			{
				puts("ʹ��С������ִ�����������룡");
				return false;
			}
			t = i;
			while(isdigit(ch[++t]))
				continue;
			if(ch[t] == '.')
			{
				puts("ʹ��С������ִ�����������룡");
				return false;
			}
		}
		if(ch[i] == '+' || ch[i] == '-' || ch[i] == '*' || ch[i] == '/')	// +-*/ ��ֻ�������ֻ� (
		{
			if(!isdigit(ch[i+1]) && ch[i+1] != '(')
			{
				puts("ʹ�÷��ų��ִ�����������룡");
				return false;
			}

		}
		if(ch[i] == '=')			// �Ⱥź��治���ٳ����κζ������Ⱥ�ǰ���ܳ��� +-*/�����򱨴�
		{
			if(ch[i+1] != '\0')
			{
				puts("ʹ�õȺŴ�������������룡");
				return false;
			}
			if(ch[i-1] == '+' || ch[i-1] == '-' || ch[i-1] == '*' || ch[i-1] == '/')
			{
				puts("�Ⱥ�ǰһλ������������ţ�");
				return false;
			}
		}
		if( (isdigit(ch[i]) && ch[i+1] == '(') || (ch[i+1] == ')' && isdigit(ch[i+1])) )	// ���ֺ���Ϊ�����ţ������ź���Ϊ����
		{
			puts("ʹ�����Ŵ���");
			return false;
		}
		if(ch[i] == '-')		// ������ʽ�ӿ�ͷ �� ����ǰΪ ( ������Ҫ��ǰ���0
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
	if(ch[0] == '+' || ch[0] == '*' || ch[0] == '/')	// ����ַ�����һλΪ����������ŵĻ�Ҳ����
	{
		puts("ʹ�÷��ų��ִ�����������룡");
		return false;
	}
	if(ch[i-1] != '=')			// ����û������Ⱥţ����Զ�����
	{
		ch[i] = '=';
		ch[i+1] = '\0';
	}
	return true;
}

// �޳��ո�
void remove_blank(char * ch)
{
	char * c;//ָ���ַ������ַ���
	while (*ch != ' ')
	{
		if (*ch == '\0')
		{
			//�ַ�����û�пո�,ֱ�ӷ���
			return;
		}
		ch++;
	}//��blankָ��ָ���һ���ո�λ��
	//��cָ��ָ����ֿո��ĵ�һ���ַ���
	c = ch + 1;
	while(*c == ' ')
	{
		c++;
	}
	while (*c != '\0')
	{
		if (*c != ' ')
		{
			//���ո�Ϊ������ֵ��ַ�������ȥ���ַ���Ϊ�ո�
			*ch = *c;
			*c = ' ';
			ch++;
		}
		c++;
	}
	*ch = '\0';
	return;
}

// �޳�������
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

// ���ɺ���
bool transit()
{
	char ch[MAXBIT];
	puts("��ѡ����Ĳ������� y/Y �������ü��������� n/N ���� �� q/Q �˳���");
        s_gets(ch);
        if((ch[0] == 'q' || ch[0] == 'Q') && ch[1] == '\0')
	{
		Exit();
	}
        if((ch[0] == 'y' || ch[0] == 'Y') && ch[1] == '\0')
		return true;
	puts("�������");
	return false;
}

void Exit()
{
	system("pause");
	system("cls");
	puts("\n\n\n\t\t\t��лʹ�ã�\n\n\n");
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

