#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"

Status initLStack(LinkStack *s)
{
	s->top = (LinkStackPtr)malloc(sizeof(StackNode));
	if (!s->top)
		return ERROR;
	s->count = 0;
	return SUCCESS;
}

Status isEmptyLStack(LinkStack *s)
{
	return s->count == 0;
}

Status getTopLStack(LinkStack *s,ElemType *e)
{
	if(s->count == 0 || !s->top)
	{
		puts("Õ»Îª¿Õ£¡");
		return ERROR;
	}
	*e = s->top->next->data;
	return SUCCESS;
}

Status clearLStack(LinkStack *s)
{
	if(isEmptyLStack(s))
		return SUCCESS;
	LinkStackPtr ptem, p;
	p = s->top->next;
	if (!s->top)
		return ERROR;
	while (p)
	{
		ptem = p->next;
		free(p);
		p = ptem;
	}
	s->count = 0;
	return SUCCESS;
}

Status destroyLStack(LinkStack *s)
{
	LinkStackPtr ptem, p = s->top->next;
	if (!s->top)
		return ERROR;
	while (s->count != 0){
		ptem = p->next;
		free(p);
		s->top->next = ptem;
		s->count--;
	}
	free(s->top);
	return SUCCESS;
}

Status LStackLength(LinkStack *s,int *length)
{
	if (!s->top)
		return ERROR;
	*length = s->count;
	return SUCCESS;
}

Status pushLStack(LinkStack *s,ElemType data)
{
	StackNode *p;
	if(!s->top)
		return ERROR;
	p = (StackNode*)malloc(sizeof(StackNode));
	p->data = data;
	p->next = s->top->next;
	s->top->next = p;
	s->count++;
	return SUCCESS;
}

Status popLStack(LinkStack *s, ElemType *data)
{
	LinkStackPtr ptem, p = s->top->next;
	if(!s->top || s->count == 0)
	{
		puts("Õ»Îª¿Õ!");
		return ERROR;
	}
	*data = p->data;
	ptem = p->next;
	free(p);
	s->top->next = ptem;
	s->count--;
	return SUCCESS;
}
