#include "../head/linkedList.h"
#include <stdio.h>
#include <stdlib.h>

/**
 *  @name        : Status InitList(LinkList *L);
 *	@description : initialize an empty linked list with only the head node without value
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList(LinkedList *L) {
	*L = (LinkedList)malloc(sizeof(LNode));
	if(NULL == (*L))
	{
		puts("Out of space !");
		return ERROR;
	}
	(*L)->next = NULL;
	return SUCCESS;
}

/**
 *  @name        : void DestroyList(LinkedList *L)
 *	@description : destroy a linked list, free all the nodes
 *	@param		 : L(the head node)
 *	@return		 : None
 *  @notice      : None
 */
void DestroyList(LinkedList *L) {
	if(NULL == (*L))
		return;
	LinkedList p,q;
	p = (*L)->next;
	while(NULL != p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;
}

/**
 *  @name        : Status InsertList(LNode *p, LNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : Status
 *  @notice      : None
 */
Status InsertList(LNode *p, LNode *q) {
	if(NULL == p)
	{
		return ERROR;
	}
	LinkedList r;
	r = p->next;
	p->next = q;
	q->next = r;
	return SUCCESS;
}

/**
 *  @name        : Status DeleteList(LNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : Status
 *  @notice      : None
 */
Status DeleteList(LNode *p, ElemType *e) {
	if(NULL == p || NULL == p->next)
	{
		return ERROR;
	}
	LinkedList q;
	q = p->next;
	(*e) = q->data;
	p->next = q->next;
	free(q);
	return SUCCESS;
}

/**
 *  @name        : void TraverseList(LinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : None
 *  @notice      : None
 */
void TraverseList(LinkedList L, void (*visit)(ElemType e)) {
	if(NULL != L)
	{
		LNode *p;
		p = L;
		while(p->next)
		{
			visit(p->next->data);
			p = p->next;
		}
	}
	puts("NULL");
}

/**
 *  @name        : Status SearchList(LinkedList L, ElemType e)
 *	@description : find the first node in the linked list according to e
 *	@param		 : L(the head node), e
 *	@return		 : Status
 *  @notice      : None
 */
Status SearchList(LinkedList L, ElemType e) {
	if(NULL != L)
	{
		LinkedList p;
		p = L->next;
		while(p)
		{
			if(e == p->data)
			{
				return SUCCESS;
			}
		p = p->next;
		}
	}
	return ERROR;
}

/**
 *  @name        : Status ReverseList(LinkedList *L)
 *	@description : reverse the linked list
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status ReverseList(LinkedList *L) {
	if(NULL == (*L))
	{
		puts("The head is null !");
		return ERROR;
	}
	if(NULL == (*L)->next)
	{
		puts("The list is empty !");
		return ERROR;
	}
	LinkedList p,q,r;
	r = NULL;
	p = (*L)->next;		// p�ǵ�һ�����
	q = p->next;		// q�ǵڶ������
	while(q)
	{
		p->next = r;	// ָ��ת�� pӦ��ָ�����һλ
		r = p;          // ��r����´ε���Ӧ��ָ����һλ
		p = q;
		q = q->next;
	}
	p->next = r;
	(*L)->next = p;
	return SUCCESS;
}

/**
 *  @name        : Status IsLoopList(LinkedList L)
 *	@description : judge whether the linked list is looped
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status IsLoopList(LinkedList L) {
	if(NULL == L || NULL == L->next)
	{
		return ERROR;
	}
	LinkedList quick,slow;
	quick = slow = L->next;
	//����޻���quick���ߵ��յ�
	//��������Ϊ����ʱ��quick->nextΪ��
	//��������Ϊż��ʱ��quickΪ��
	while(NULL != quick && NULL != quick->next)
	{
		quick = quick->next->next;
		slow = slow->next;
		if(quick == slow)
		{
			break;
		}
	}
	if(NULL == quick || NULL == quick->next)
		return ERROR;
	else
		return SUCCESS;
}

/**
 *  @name        : LNode* ReverseEvenList(LinkedList *L)
 *	@description : reverse the nodes which value is an even number in the linked list, input: 1 -> 2 -> 3 -> 4  output: 2 -> 1 -> 4 -> 3
 *	@param		 : L(the head node)
 *	@return		 : LNode(the new head node)
 *  @notice      : choose to finish
 */
LNode* ReverseEvenList(LinkedList *L) {
	if(NULL == (*L))
	{
		puts("The head  is null !");
		return (*L);
	}
	LinkedList p0,p1,p2;
	p0 = (*L);	// ÿ�ε�����ʼʱ p0��ԶΪ�ôθı��������� ǰ��Ľ�㣨����ı�3��4����ôp0����2��
	p1 = p0->next;	// ÿ�ε�����ʼʱ p1��Զָ���������Ľ�㣨1 ��3�� 5 ������ͬ��p2ָ��ż��
	while(NULL != p1 && NULL != p1->next) // ÿ�ε���ֻ��������ż�������ڲ���Ҫ����
	{
		p2 = p1->next;

		p0->next = p2;
		p1->next = p2->next;
		p2->next = p1;

		p0 = p1;
		p1 = p1->next;
	}
	return (*L);
}

/**
 *  @name        : LNode* FindMidNode(LinkedList *L)
 *	@description : find the middle node in the linked list
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : choose to finish
 */
LNode* FindMidNode(LinkedList *L) {
	// ����������м��㣬�򷵻صڶ����м���
	if(NULL == (*L))
	{
		puts("The head is null !");
		return NULL;
	}
	if(NULL == (*L)->next)
	{
		puts("The list is empty !");
	}
	LinkedList slow,quick;
	slow = quick = (*L)->next;
	while(quick && quick->next)
	{
		quick = quick->next->next;
		slow = slow->next;
	}
	return slow;
}

/**
 *  @name        : void visit(ElemType e)
 *	@description : print e
 *	@param		 : e
 *	@return		 : None
 *  @notice      : None
 */
void visit(ElemType e)
{
	printf("%d-> ",e);
}

