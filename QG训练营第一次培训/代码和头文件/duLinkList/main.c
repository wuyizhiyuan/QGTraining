#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../head/duLinkedList.h"

void PrintMenu(void);			// 打印菜单
void CreateList(DuLinkedList * L);	// 创建链表
void InsertBefore(DuLinkedList L);	// 在选中的元素之前插入
void InesrtAfter(DuLinkedList L);	// 在选中的元素之后插入
void Delete(DuLinkedList L);		// 删除操作
void Destory(DuLinkedList * L);		// 置空链表
// 自己的输入函数
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
	printf("\t\t****双向链表ADT测试****");
	printf("\n1.整表创建\n2.遍历操作 \n3.在选中的元素之前插入");
	printf("\n4.在选中的元素之后插入\n5.删除操作\n6.置空链表");
	printf("\n0.退出\n请选择你的操作\n");
}

// 创建链表
void CreateList(DuLinkedList * L)
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
		if(!InitList_DuL(L))
		{
			exit(0);
		}
	}
	int input;
	DuLinkedList temp,p;
	printf("请输入链表元素个数：");
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
	puts("创建链表成功！");
}

void InsertBefore(DuLinkedList L)	// 在选中的元素之前插入
{
	int num;
	DuLinkedList node_,p;
	printf("请输入要插入第几个位置的前面：");
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
	printf("请输入你要插入的数据：");
	InputPositiveNum(&num);
	p->data = num;
	if(!InsertBeforeList_DuL(node_,p))
	{
		puts("此节点不存在！");
		free(p);
	}
	else
	{
		puts("插入成功！");
	}
}

void InesrtAfter(DuLinkedList L)	// 在选中的元素之后插入
{
	int num;
	DuLinkedList node_,p;
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
	if(!InitList_DuL(&p))
	{
		exit(0);
	}
	printf("请输入你要插入的数据：");
	InputPositiveNum(&num);
	p->data = num;
	if(!InsertAfterList_DuL(node_,p))
	{
		puts("此节点不存在！");
		free(p);
	}
	else
	{
		puts("插入成功！");
	}
}

void Delete(DuLinkedList L)		// 删除操作
{
	int num,e;
	DuLinkedList p;
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
	if(!DeleteList_DuL(p,&e))
	{
		puts("要删除的节点不存在");
	}
	else
	{
		printf("删除成功 ！你删除的数据是%d\n",e);
	}
}

void Destory(DuLinkedList * L)		// 置空链表
{
	if(NULL == (*L) || NULL == (*L)->next)
		puts("链表为空!");
	else
	{
		DestroyList_DuL(L);
		puts("置空成功！");
	}
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
