#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//码这么多自娱自乐
void PrintMenu(void);			// 打印菜单
void CreateList(LinkedList * L);	// 1.创建链表
void Traverse(LinkedList L);		// 2.遍历操作
void Insert(LinkedList L);		// 3.插入操作
void Delete(LinkedList L);		// 4.删除操作
void Search(LinkedList L);		// 5.查询某数是否在链表中
void Destory(LinkedList L);		// 6.置空链表
void Reverse(LinkedList * L);		// 7.反转链表
void FindMid(LinkedList * L);		// 8.寻找中间节点
void AddCircle(LinkedList L);		// 9.给链表加环
LNode * SearchCircleNode(LinkedList L);	// 找到成环的那个点
// 自己的输入函数
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
					puts("此链表无环！");
				else
					puts("此链表存在环！");
				break;
			case 11:
				if(!IsLoopList(List))
				{
					List = ReverseEvenList(&List);
					if(List)
						puts("奇偶反转成功！");
				}
				else
					puts("此链表存在环,不可奇偶翻转！");
				break;
			default:
				puts("请输入正确的选择序号！");
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

// 打印菜单
void PrintMenu(void)
{
	printf("\t\t****链表ADT测试****");
	printf("\n1.整表创建\n2.遍历操作 \n3.插入操作");
	printf("\n4.删除操作\n5.查询某数是否在链表中\n6.置空链表");
	printf("\n7.链表反转逆序\n8.找到链表的中间结点\n9.给链表加环\n10.判断链表是否有环\n11.奇偶反转");
	printf("\n0.退出\n请选择你的操作\n");
}

// 创建链表
void CreateList(LinkedList * L)
{
	if(NULL != (*L))
	{
		if(NULL != (*L)->next)
		{
			puts("此链表已存在，请先清空再创建！");
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
	printf("请输入链表元素个数：");
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
	puts("创建链表成功！");
}

// 遍历操作
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

// 插入操作
void Insert(LinkedList L)
{
	int num;
	LinkedList node_,p;
	printf("请输入要插入第几个位置的后面：");
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
	printf("请输入你要插入的数据：");
	InputPositiveNum(&num);
	p->data = num;
	if(!InsertList(node_,p))
	{
		puts("此节点不存在！");
		free(p);
	}
	else
	{
		puts("插入成功！");
	}
}

// 删除操作
void Delete(LinkedList L)
{
	int num,e;
	LinkedList p;
	p = L;
	printf("请输入要删除第几个位置的节点：");
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
		puts("要删除的节点不存在");
	}
	else
	{
		printf("删除成功 ！你删除的数据是%d\n",e);
	}

}

// 查询某数是否在链表中
void Search(LinkedList L)
{
	int num;
	printf("请输入你要查找的数据：");
	InputPositiveNum(&num);
	if(SearchList(L,num))
	{
		printf("此链表里存在%d!\n",num);
	}
	else
	{
		printf("该链表无此数据！\n");
	}
}

// 置空链表
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
	puts("置空成功！");
}

// 反转链表
void Reverse(LinkedList * L)
{
	if(IsLoopList(*L))
		puts("该链表有环，无法反转！");
	else
	{
		if(ReverseList(L))
		{
			puts("反转成功！");
		}
		else
		{
			puts("反转失败！");
		}
	}
}

// 寻找中间节点
void FindMid(LinkedList * L)
{
	LNode * p;
	if(IsLoopList(*L))
		puts("该链表有环，没有中间节点！");
	else
	{
		p = FindMidNode(L);
		if(p)
			printf("中间节点为%d\n",p->data);
	}
}

// 给链表加环
void AddCircle(LinkedList L)
{
	if(NULL == L)
	{
		puts("The head is null !");
		return;
	}
	else if(NULL == L->next)
	{
		puts("该链表为空表！");
		return;
	}
	int num;
	LinkedList p,q;
	if(!IsLoopList(L))
	{
		q = p = L;
		printf("请输入末尾链表的下一个指向第链表第几个位置：");
		InputPositiveNum(&num);
		for(int i = 0;i < num;i++)
		{
			if(NULL == p)
			{
				puts("不存在此位置");
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
			puts("加环成功!");
		}
	}
	else
	{
		puts("该链表有环，不可再加环！");
	}
}

// 找到成环的那个点
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

// 自己的输入函数
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
			puts("输入有误！");
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
			puts("输入数据过大");
		continue;
	}
	while((*num) < 1)
	{
		puts("请输入正整数！");
		while(!num_gets(num) || (*num) > 99999999)
		{
			if((*num) > 99999999)
				puts("输入数据过大");
			continue;
		}
	}
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
