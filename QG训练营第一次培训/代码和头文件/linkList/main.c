#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//����ô����������
void PrintMenu(void);			// ��ӡ�˵�
void CreateList(LinkedList * L);	// 1.��������
void Traverse(LinkedList L);		// 2.��������
void Insert(LinkedList L);		// 3.�������
void Delete(LinkedList L);		// 4.ɾ������
void Search(LinkedList L);		// 5.��ѯĳ���Ƿ���������
void Destory(LinkedList L);		// 6.�ÿ�����
void Reverse(LinkedList * L);		// 7.��ת����
void FindMid(LinkedList * L);		// 8.Ѱ���м�ڵ�
void AddCircle(LinkedList L);		// 9.������ӻ�
LNode * SearchCircleNode(LinkedList L);	// �ҵ��ɻ����Ǹ���
// �Լ������뺯��
void s_gets(char * str,int lim);
Status num_gets(int * num);
void InputPositiveNum(int * num);

void Exit();

int main(void)
{
	system("color c");
	int choice,i = 0;
	LinkedList List = NULL;
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
				Traverse(List);
				break;
			case 3:
				Insert(List);
				break;
			case 4:
				Delete(List);
				break;
			case 5:
				Search(List);
				break;
			case 6:
				Destory(List);
				break;
			case 7:
				Reverse(&List);
				break;
			case 8:
				FindMid(&List);
				break;
			case 9:
				AddCircle(List);
				break;
			case 10:
				if(!IsLoopList(List))
					puts("�������޻���");
				else
					puts("��������ڻ���");
				break;
			case 11:
				if(!IsLoopList(List))
				{
					List = ReverseEvenList(&List);
					if(List)
						puts("��ż��ת�ɹ���");
				}
				else
					puts("��������ڻ�,������ż��ת��");
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
	printf("\t\t****����ADT����****");
	printf("\n1.������\n2.�������� \n3.�������");
	printf("\n4.ɾ������\n5.��ѯĳ���Ƿ���������\n6.�ÿ�����");
	printf("\n7.����ת����\n8.�ҵ�������м���\n9.������ӻ�\n10.�ж������Ƿ��л�\n11.��ż��ת");
	printf("\n0.�˳�\n��ѡ����Ĳ���\n");
}

// ��������
void CreateList(LinkedList * L)
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
		if(!InitList(L))
		{
			exit(0);
		}
	}
	int input;
	LinkedList temp;
	printf("����������Ԫ�ظ�����");
	InputPositiveNum(&input);
	LinkedList p;
	p = (*L);
	for(int i = 0;i < input;i++)
	{
		if(!InitList(&temp))
		{
			exit(0);
		}
		temp->data = i+1;
		p->next = temp;
		p = temp;
		temp = NULL;
	}
	puts("��������ɹ���");
}

// ��������
void Traverse(LinkedList L)
{
	if(IsLoopList(L))
	{
		LinkedList p,q;
		p = SearchCircleNode(L);
		q =L->next;
		while(q != p)
		{
			printf("%d-> ",q->data);
			q = q->next;
		}
		q = p->next;
		printf("%d-> ",p->data);
		while(q != p)
		{
			printf("%d-> ",q->data);
			q = q->next;
		}
		printf("*%d\n",p->data);
	}
	else
	{
		TraverseList(L,visit);
	}
}

// �������
void Insert(LinkedList L)
{
	int num;
	LinkedList node_,p;
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
	if(!InitList(&p))
	{
		exit(0);
	}
	printf("��������Ҫ��������ݣ�");
	InputPositiveNum(&num);
	p->data = num;
	if(!InsertList(node_,p))
	{
		puts("�˽ڵ㲻���ڣ�");
		free(p);
	}
	else
	{
		puts("����ɹ���");
	}
}

// ɾ������
void Delete(LinkedList L)
{
	int num,e;
	LinkedList p;
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
	if(!DeleteList(p,&e))
	{
		puts("Ҫɾ���Ľڵ㲻����");
	}
	else
	{
		printf("ɾ���ɹ� ����ɾ����������%d\n",e);
	}

}

// ��ѯĳ���Ƿ���������
void Search(LinkedList L)
{
	int num;
	printf("��������Ҫ���ҵ����ݣ�");
	InputPositiveNum(&num);
	if(SearchList(L,num))
	{
		printf("�����������%d!\n",num);
	}
	else
	{
		printf("�������޴����ݣ�\n");
	}
}

// �ÿ�����
void Destory(LinkedList L)
{
	if(IsLoopList(L))
	{
		LinkedList p,q,r;
		p = SearchCircleNode(L);
		q =L->next;
		while(q != p)
		{
			r = q;
			q = q->next;
			free(r);
		}
		q = p->next;
		while(q != p)
		{
			r = q;
			q = q->next;
			free(r);
		}
		free(p);
		L->next = NULL;
	}
	else
	{
		DestroyList(&L);
	}
	puts("�ÿճɹ���");
}

// ��ת����
void Reverse(LinkedList * L)
{
	if(IsLoopList(*L))
		puts("�������л����޷���ת��");
	else
	{
		if(ReverseList(L))
		{
			puts("��ת�ɹ���");
		}
		else
		{
			puts("��תʧ�ܣ�");
		}
	}
}

// Ѱ���м�ڵ�
void FindMid(LinkedList * L)
{
	LNode * p;
	if(IsLoopList(*L))
		puts("�������л���û���м�ڵ㣡");
	else
	{
		p = FindMidNode(L);
		if(p)
			printf("�м�ڵ�Ϊ%d\n",p->data);
	}
}

// ������ӻ�
void AddCircle(LinkedList L)
{
	if(NULL == L)
	{
		puts("The head is null !");
		return;
	}
	else if(NULL == L->next)
	{
		puts("������Ϊ�ձ�");
		return;
	}
	int num;
	LinkedList p,q;
	if(!IsLoopList(L))
	{
		q = p = L;
		printf("������ĩβ�������һ��ָ�������ڼ���λ�ã�");
		InputPositiveNum(&num);
		for(int i = 0;i < num;i++)
		{
			if(NULL == p)
			{
				puts("�����ڴ�λ��");
			}
			p = p->next;
		}
		if(p)
		{
			while(q->next)
			{
				q = q->next;
			}
			q->next = p;
			puts("�ӻ��ɹ�!");
		}
	}
	else
	{
		puts("�������л��������ټӻ���");
	}
}

// �ҵ��ɻ����Ǹ���
LNode * SearchCircleNode(LinkedList L)
{
	LinkedList quick,slow;
	quick = slow = L->next;
	while(1)
	{
		quick = quick->next->next;
		slow = slow->next;
		if(quick == slow)
		{
			break;
		}
	}
	quick = L->next;
	while(quick != slow)
	{
		quick = quick->next;
		slow = slow->next;
	}
	return quick;
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
