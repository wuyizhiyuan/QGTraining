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
	puts("\t***������ʽ����ADT����***");
	puts("����ȷ������Ҫ��ȡ����������:\nchar���밴1\tint���밴2\tdouble���밴3\tstring���밴4");
	setType();
	InitLQueue(Q);
	menu();
	chose(Q);
	return 0;
}

// ����
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
				puts("����Ϊ��!");
			else
			puts("���в�Ϊ��!");
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
				printf("��ͷ����Ϊ");
				LPrint(t);
				puts("");
			}
			else
				puts("����Ϊ��!");
			break;
		case '4':
			printf("���г���Ϊ%d��\n",LengthLQueue(Q));
			break;
		case '5':
			enLQueue(Q);
			puts("��ӳɹ���");
			break;
		case '6':
			if(DeLQueue(Q))
				puts("���ӳɹ���");
			else
			 puts("����Ϊ�գ�");
			break;
		case '7':
			ClearLQueue(Q);
			puts("��ճɹ���");
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

// ��ӡ�˵�
void menu()
{
	puts("\t***������ʽ����ADT����***");
	puts("\t\t1.ɾ�����в��˳�ϵͳ");
	puts("\t\t2.�ж϶����Ƿ�Ϊ��");
	puts("\t\t3.���ͷ�������");
	puts("\t\t4.����������г���");
	puts("\t\t5.��Ӳ���");
	puts("\t\t6.���Ӳ���");
	puts("\t\t7.��ն���");
	puts("\t\t8.��������");
	puts("\t\t9.��ռ�¼");
}

// ��Ӵ���
void enLQueue(LQueue * Q)
{
	char c[100];
	char x;
	if(type == '2')
	{
		int a = 0;
		puts("��������������:");
		a = s_get_int();
		EnLQueue(Q,&a);
	}
	else if(type == '1')
	{
		puts("�������ַ�");
		x = getchar();
		fflush(stdin);
		EnLQueue(Q,&x);
	}
	else if(type == '3')
	{
		double d;
		puts("�����븡������");
		s_gets(c,100);
		M:d = atof(c);
		if(d == 0)
		{
			int i = 0;
			while(c[i++] != '\0')
			{
				if (c[i] != '0' && c[i] != '.')
				{
				puts("�����������������\n");
				s_gets(c,100);
				goto M;
				}
			}
		}
		EnLQueue(Q,&d);
	}
	else if(type == '4')
	{
		puts("����������");
		s_gets(c,100);
		EnLQueue(Q,&c);
	}
}

// ��ȡ���α���
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
			printf("����������������룡\n");
			t = s_get_int();
		}
	}
	return t;
}

// ѡ����
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

//��ȡ��������
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
	puts("\t\t\t��лʹ�ã�\n\n\n");
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
