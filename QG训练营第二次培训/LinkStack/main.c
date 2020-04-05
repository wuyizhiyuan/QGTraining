#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"

int s_get_int();
void menu();
void select(LinkStack *s);
void Exit();

int main()
{
	system("color c");
	LinkStack * s = (LinkStack *)malloc(sizeof(LinkStack));
	initLStack(s);
	menu();
	puts("���������ѡ��:");
	select(s);
	return 0;
}

void menu()
{
    puts("\t***����ջ����***");
    puts("\t1.�ж�ջ�Ƿ�Ϊ��");
    puts("\t2.���ջ��Ԫ��");
    puts("\t3.���ջ");
    puts("\t4.����ջ��ʵ�ʳ���");
    puts("\t5.��ջ����");
    puts("\t6.��ջ����");
    puts("\t7.����ջ���˳�ϵͳ");
    puts("\t8.��ղ�����¼");
}

void select(LinkStack *s)
{
	ElemType e;

	switch(s_get_int())
	{
		case 1:
			if(isEmptyLStack(s))
				puts("ջ��Ϊ��");
			else
				puts("ջ��Ϊ��");
			break;
		case 2:
			if(getTopLStack(s,&e))
				printf("ջ��Ԫ��Ϊ%d\n",e);
			else
				puts("ջΪ�գ�����ʧ��");
			break;
		case 3:
			clearLStack(s);
			puts("�����ɹ�");
			break;
		case 4:
			LStackLength(s,&e);
			printf("ջ��ʵ�ʳ���Ϊ%d\n",e);
			break;
		case 5:
			puts("��������ջ���ݣ�");
			if(pushLStack(s,s_get_int()))
				puts("�����ɹ�");
			else
				puts("����ʧ��");
			break;
		case 6:
			if(popLStack(s,&e))
				puts("�����ɹ�");
			else
				puts("����ʧ��");
			break;
		case 7:
			destroyLStack(s);
			Exit();
			exit(0);
		case 8:
			system("cls");
			menu();
			break;
		default :
			puts("���ڷ�Χ�����룺");
	}
	puts("���������ѡ��");
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
            puts("�Ƿ�����,����������(����)");
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
}
