#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AQueue.h"

void InitAQueue(AQueue *Q)
{
	int i;
	Q->length = MAXQUEUE;
	for(i = 0; i < MAXQUEUE; i++)
		Q->data[i] = (void *)malloc(65);
	Q->front = Q->rear = 0;
}

void DestoryAQueue(AQueue *Q)
{
	if(NULL == Q->data[0])
	{
		puts("队列未初始化！请先初始化队列！");
		return;
	}
	for(int i = 0; i < MAXQUEUE; i++)
		free(Q->data[i]);
	Q->data[0] = NULL;
}

Status IsFullAQueue(const AQueue *Q)
{
	if(NULL == Q->data[0])
	{
		puts("队列未初始化！请先初始化队列！");
		return FALSE;
	}
	if(IsEmptyAQueue(Q))
		return FALSE;
	if(LengthAQueue(Q) == MAXQUEUE - 1)		// 牺牲一个空间
	{
		return TRUE;
	}
	else
		return FALSE;
}

Status IsEmptyAQueue(const AQueue *Q)
{
	if(NULL == Q->data[0])
	{
		puts("队列未初始化！请先初始化队列！");
		return FALSE;
	}
	return (LengthAQueue(Q) == 0 ? TRUE : FALSE);
}

Status GetHeadAQueue(AQueue *Q, void *e)
{
	if (IsEmptyAQueue(Q))
	{
		puts("没有队头！");
		return FALSE;
	}
	int temp;
	if(type == '4')
		temp = 64;
	else if(type == '3')
		temp =8;
	else if(type == '2')
		temp = 4;
	else
		temp = sizeof(*e);
	memcpy(e,Q->data[Q->front],temp);
	return TRUE;
}

int LengthAQueue(const AQueue *Q)
{
        return (Q->rear-Q->front+Q->length) % Q->length;
}

Status EnAQueue(AQueue *Q, void *data)
{
	if(IsFullAQueue(Q))
	{
		puts("队列已满！");
		return FALSE;
	}
	if(IsEmptyAQueue(Q))
	{
		memcpy(Q->data[Q->front],data,64);
		Q->rear = (Q->rear + 1) % Q->length;
		return TRUE;
	}
	memcpy(Q->data[Q->rear], data, 64);
	Q->rear = (Q->rear + 1) % Q->length;
    return TRUE;
}

Status DeAQueue(AQueue *Q)
{
	if(IsEmptyAQueue(Q))
    	{
    		puts("队列为空！");
    		return FALSE;
    	}
        Q->front = (Q->front + 1) % Q->length;
        return TRUE;
}

void ClearAQueue(AQueue *Q)
{
	if(IsEmptyAQueue(Q))
	{
		return;
	}
	Q->front = Q->rear = 0;
}

Status TraverseAQueue(const AQueue *Q, void (*foo)(void *q))
{
        if(NULL == Q->data[0])
        {
            puts("队列未初始化！");
            return FALSE;
        }
    	if(IsEmptyAQueue(Q))
    	{
    		puts("队列为空!");
    		return FALSE;
    	}
    	for(int i = 0;i < (MAXQUEUE - Q->front + Q->rear) % MAXQUEUE;i++)
	{
		type = datatype[(Q->front+i) % MAXQUEUE];
    		foo(Q->data[(Q->front+i) % MAXQUEUE]);
    	}
    	puts("");
        return TRUE;
}

void APrint(void *q)
{
	if(type == '1')
            printf("<-- %c",*(char*)q);
	if(type == '2')
            printf("<-- %d ",*(int*)q);
        if(type == '3')
            printf("<-- %g",*(double*)q);
        if(type == '4')
            printf("<-- %s ",(char*)q);
}


