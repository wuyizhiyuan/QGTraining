#include "LQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InitLQueue(LQueue *Q)
{
	Q->front = Q->rear = NULL;
	Q->length = 0;
}

void DestoryLQueue(LQueue *Q)
{
	if(IsEmptyLQueue(Q))
		return;
	ClearLQueue(Q);
	free(Q);
}

Status IsEmptyLQueue(const LQueue *Q)
{
	if(!Q->length)
		return TRUE;
	return FALSE;
}
Status GetHeadLQueue(LQueue *Q, void *e)
{
	size_t temp;
	if(IsEmptyLQueue(Q))
		return FALSE;
	if(type == '1')
		temp = sizeof(char);
	else if(type == '2')
		temp = sizeof(int);
	else if(type == '3')
		temp = sizeof(double);
	else
		temp = 100 * sizeof(char);
	memcpy(e,Q->front->data,temp);
	return TRUE;
}

int LengthLQueue(LQueue *Q)
{
	return Q->length;
}

Status EnLQueue(LQueue *Q, void *data)
{
	size_t temp;
	if(type == '1')
		temp = sizeof(char);
	else if(type == '2')
		temp = sizeof(int);
	else if(type == '3')
		temp = sizeof(double);
	else
		temp = 100 * sizeof(char);
	Node * p;
	p = (Node *)malloc(sizeof(Node));
	if(p == NULL)
	{
		puts("内存不够!");
		return FALSE;
	}
	p->next = NULL;
	p->data = (void*)malloc(temp);
	memcpy(p->data,data,temp);
	if(IsEmptyLQueue(Q))
		Q->front = p;
	else
		Q->rear->next = p;;
	Q->rear = p;
	Q->length++;
	return TRUE;
}

Status DeLQueue(LQueue *Q)
{
	Node * p;
	if(IsEmptyLQueue(Q))
		return FALSE;
	p = Q->front;
	Q->front = Q->front->next;
	free(p->data);
	free(p);
	Q->length--;
	if(!Q->length)
		Q->rear = NULL;
	return TRUE;
}

void ClearLQueue(LQueue *Q)
{
	while(!IsEmptyLQueue(Q))
		DeLQueue(Q);
}

Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
{
	if(IsEmptyLQueue(Q))
	{
		puts("队列为空！");
		return FALSE;
	}
	Node * p;
	p = Q->front;
	while (p)
	{
		LPrint(p->data);
		p = p->next;
	}
	puts("");
	return TRUE;
}

void LPrint(void *q)
{
	if(type == '1')
		printf("<-- %c", *(char*)q);
	else if (type == '2')
		printf("<-- %d ", *(int*)q);
	else if (type == '3')
		printf("<-- %g", *(double*)q);
	else if (type == '4')
		printf("<-- %s ", (char*)q);
}






































