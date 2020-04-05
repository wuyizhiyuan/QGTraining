#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SqStack.h"

Status initStack(SqStack *s,int sizes)
{
	s->elem = (ElemType*)malloc(sizes * sizeof(ElemType));
	if(!s->elem)
	{
		puts("Out of sqace !");
		return ERROR;
	}
	s->top = -1;
	s->size = sizes;
	return SUCCESS;
}

Status isEmptyStack(SqStack *s)
{
	return s->top == -1;
}

Status getTopStack(SqStack *s,ElemType *e)
{
	if(s->top == -1)
	{
		puts("栈为空！");
		return ERROR;
	}
	*e = s->elem[s->top];
	return SUCCESS;
}

Status clearStack(SqStack *s)
{
	if(!s)
		return ERROR;
	s->top = -1;
	return SUCCESS;
}

Status destroyStack(SqStack *s)
{
	if(!s)
		return ERROR;
	free(s->elem);
	return SUCCESS;
}

Status stackLength(SqStack *s,int *length)
{
	if(!s)
		return ERROR;
	*length = s->top + 1;
	return SUCCESS;
}

Status pushStack(SqStack *s,ElemType data)
{
	if(!s || s->top == s->size - 1)
	{
		puts("栈已满，无法入栈");
		return ERROR;
	}
	s->top++;
	s->elem[s->top] = data;
	return SUCCESS;
}

Status popStack(SqStack *s, ElemType *data)
{
	if(!s || s->top == -1)
	{
		puts("栈为空！");
		return ERROR;
	}
	s->top--;
	*data = s->top;
	return SUCCESS;
}




