#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "duLinkedList.h"

void PrintMenu(void);			// ��ӡ�˵�
void CreateList(DuLinkedList * L);	// ��������
void InsertBefore(DuLinkedList L);	// ��ѡ�е�Ԫ��֮ǰ����
void InesrtAfter(DuLinkedList L);	// ��ѡ�е�Ԫ��֮�����
void Delete(DuLinkedList L);		// ɾ������
void Destory(DuLinkedList * L);		// �ÿ�����
// �Լ������뺯��
void s_gets(char * str,int lim);
Status num_gets(int * num);
void InputPositiveNum(int * num);

void Exit();


int main(void)
{
	system("color c");
	int choice,i = 0;
	DuLinkedList List = NULL;
	PrintMenu();
	while(!num_gets(&choice))
		continue;
	while(choice != 0)
	{
		switch(choice)
		{
			case 1:
				CreateList(&List);
				break;
			case 2:
				TraverseList_DuL(List,visit);
				break;
			case 3:
				InsertBefore(List);
				break;
			case 4:
				InesrtAfter(List);
				break;
			case 5:
				Delete(List);
				break;
			case 6:
				Destory(&List);
				break;
			default:
				puts("��������ȷ��ѡ����ţ�");
				break;
		}
		if(++i == 8)
		{
			i = 0;
			system("pause");
			system("cls");
			PrintMenu();
		}
		while(!num_gets(&choice))
			continue;
	}
	Exit();
	return 0;

}

// ��ӡ�˵�
void PrintMenu(void)
{
	printf("\t\t****˫������ADT����****");
	printf("\n1.������\n2.�������� \n3.��ѡ�е�Ԫ��֮ǰ����");
	printf("\n4.��ѡ�е�Ԫ��֮�����\n5.ɾ������\n6.�ÿ�����");
	printf("\n0.�˳�\n��ѡ����Ĳ���\n");
}

// ��������
void CreateList(DuLinkedList * L)
{
	if(NULL != (*L))
	{
		if(NULL != (*L)->next)
		{
			puts("�������Ѵ��ڣ���������ٴ�����");
			return;
		}
	}
	else
	{
		if(!InitList_DuL(L))
		{
			exit(0);
		}
	}
	int input;
	DuLinkedList temp,p;
	printf("����������Ԫ�ظ�����");
	InputPositiveNum(&input);
	p = (*L);
	for(int i = 0;i < input;i++)
	{
		if(!InitList_DuL(&temp))
		{
			exit(0);
		}
		temp->data = i+1;
		p->next = temp;
		temp->prior =p;
		p = temp;
		temp->next = NULL;
		temp = NULL;
	}
	puts("��������ɹ���");
}

void InsertBefore(DuLinkedList L)	// ��ѡ�е�Ԫ��֮ǰ����
{
	int num;
	DuLinkedList node_,p;
	printf("������Ҫ����ڼ���λ�õ�ǰ�棺");
	node_ = L;
	InputPositiveNum(&num);
	for(int i = 0;i < num;i++)
	{
		if(NULL == node_)
		{
			break;
		}
		node_ = node_->next;
	}
	if(!InitList_DuL(&p))
	{
		exit(0);
	}
	printf("��������Ҫ��������ݣ�");
	InputPositiveNum(&num);
	p->data = num;
	if(!InsertBeforeList_DuL(node_,p))
	{
		puts("�˽ڵ㲻���ڣ�");
		free(p);
	}
	else
	{
		puts("����ɹ���");
	}
}

void InesrtAfter(DuLinkedList L)	// ��ѡ�е�Ԫ��֮�����
{
	int num;
	DuLinkedList node_,p;
	printf("������Ҫ����ڼ���λ�õĺ��棺");
	node_ = L;
	InputPositiveNum(&num);
	for(int i = 0;i < num;i++)
	{
		if(NULL == node_)
		{
			break;
		}
		node_ = node_->next;
	}
	if(!InitList_DuL(&p))
	{
		exit(0);
	}
	printf("��������Ҫ��������ݣ�");
	InputPositiveNum(&num);
	p->data = num;
	if(!InsertAfterList_DuL(node_,p))
	{
		puts("�˽ڵ㲻���ڣ�");
		free(p);
	}
	else
	{
		puts("����ɹ���");
	}
}

void Delete(DuLinkedList L)		// ɾ������
{
	int num,e;
	DuLinkedList p;
	p = L;
	printf("������Ҫɾ���ڼ���λ�õĽڵ㣺");
	InputPositiveNum(&num);
	for(int i = 0;i < num-1;i++)
	{
		if(NULL == p)
		{
			break;
		}
		p = p->next;
	}
	if(!DeleteList_DuL(p,&e))
	{
		puts("Ҫɾ���Ľڵ㲻����");
	}
	else
	{
		printf("ɾ���ɹ� ����ɾ����������%d\n",e);
	}
}

void Destory(DuLinkedList * L)		// �ÿ�����
{
	if(NULL == (*L) || NULL == (*L)->next)
		puts("����Ϊ��!");
	else
	{
		DestroyList_DuL(L);
		puts("�ÿճɹ���");
	}
}

// �Լ������뺯��
void s_gets(char * str,int lim)
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
}

Status num_gets(int * num)
{
	char temp,str[10],digit[10] ={'\0'};
	int i = 0;
	s_gets(str,10);
	if(str[0] == '\0')
	{
		return ERROR;
	}
	while((temp = str[i++]) != '\0')
	{
		if(isdigit(temp))
		{
			digit[i-1] = temp;
		}
		else
		{
			puts("��������");
			return ERROR;
		}
	}
	digit[i] = '\0';
	(*num) = atoi(digit);
	return SUCCESS;
}

void InputPositiveNum(int * num)
{
	while(!num_gets(num) || (*num) > 99999999)
	{
		if((*num) > 99999999)
			puts("�������ݹ���");
		continue;
	}
	while((*num) < 1)
	{
		puts("��������������");
		while(!num_gets(num) || (*num) > 99999999)
		{
			if((*num) > 99999999)
				puts("�������ݹ���");
			continue;
		}
	}
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
