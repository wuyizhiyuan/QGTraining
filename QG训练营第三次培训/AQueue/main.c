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
	puts("\t***����ѭ������ADT����***");
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

void chose(AQueue * Q)
{
	char select;
	A:puts("���������ѡ��:");
	select = getch();
	switch(select)
	{
		case '1':
			DestoryAQueue(Q);
				Exit();
			break;
		case '2':
			if(IsEmptyAQueue(Q))
				puts("�ö���Ϊ�գ�");
			else
				puts("�ö��в�Ϊ�գ�");
			break;
		case '3':
			gethead(Q);
			puts("");
			break;
		case '4':
			printf("���г���Ϊ%d\n",LengthAQueue(Q));
			break;
		case '5':
			enAQueue(Q);
			break;
		case '6':
			if(DeAQueue(Q))
				puts("���ӳɹ���");
			break;
		case '7':
			ClearAQueue(Q);
			puts("�����ѿգ�");
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
	puts("\t\t\t����������ӵ����ͣ�");
	puts("\t\t�ַ��밴 1�������밴 2���������밴 3���ַ����밴 4 ");
	B:type = getch();
	switch(type)
	{
		case '1':
			puts("�������ַ�!");
			a = getchar();
			fflush(stdin);
			if(EnAQueue(Q,&a))
			{
				puts("����ɹ���");
				datatype[(Q->rear-1+Q->length) % Q->length] = type;
			}
			break;
		case '2':
			puts("����������!");
			b = s_get_int();
			if(EnAQueue(Q,&b))
			{
				puts("����ɹ���");
				datatype[(Q->rear-1+Q->length) % Q->length] = type;
			}
			break;
		case '3':
			puts("�����븡����!");
			s_gets_str(x,64);
			M:c = atof(x);
			if(c == 0)
			{
				int i = 0;
				while(x[i++] != '\0')
				{
					if (x[i] != '0' && x[i] != '.')
					{
						puts("�����������������\n");
						s_gets_str(x,64);
						goto M;
					}
				}
			}
			if(EnAQueue(Q,&c))
			{
				puts("����ɹ���");
				datatype[(Q->rear-1+Q->length) % Q->length] = type;
			}
			break;
		case '4':
			puts("�������ַ���(������64���ַ�)!");
			s_gets_str(x,64);
			if(EnAQueue(Q,x))
			{
				puts("����ɹ���");
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
            puts("�Ƿ�����,����������(��ʱ��֧�ָ���)");
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
