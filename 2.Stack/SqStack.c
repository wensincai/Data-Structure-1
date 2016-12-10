#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

#define OK 1
#define ERROR 0

typedef int SElemType;
typedef int Status;

//˳��ջ����
typedef struct
{
	SElemType *top; //ջ��ָ��
	SElemType *base; //��ջ����֮ǰ������֮��ΪNULL
	int stacksize; //��ǰ�ѷ����С
}SqStack;

//��ʼ��
Status InitStack(SqStack *S)
{
	S->base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if (!S->base) return ERROR;
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return OK;
}

//�п�
Status StackEmpty(SqStack *S)
{
	if (S->top == S->base)
		return OK;
	return ERROR;
}

//ջ��
Status StackFull(SqStack *S)
{
	if (S->top - S->base >= S->stacksize)
		return OK;
	return ERROR;
}

//ջ��
Status GetTop(SqStack *S, SElemType* e)
{
	if (StackEmpty(S))
		return ERROR;
	(*e) = *(S->top - 1);
	return OK;
}

//ѹջ
Status PushStack(SqStack *S, SElemType e)
{
	if (StackFull(S))
	{
		S->base = (SElemType *)realloc(S->base,
			(S->stacksize + STACKINCREMENT)*sizeof(SElemType));
		if (!S->base) return ERROR;
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}
	*(S->top++) = e;
	return OK;
}

//��ջ
Status PopStack(SqStack *S, SElemType* e)
{
	if (StackEmpty(S)) return ERROR;
	(*e) = *(--S->top);
	return OK;
}

//���
Status ClearStack(SqStack *S)
{
	S->top = S->base;
	S->stacksize = 0;
	return OK;
}

//����
Status DestroyStack(SqStack *S)
{
	free(S->base);
	S->top = NULL;
	S->base = NULL;
	S->stacksize = 0;
	return OK;
}

//����
int Length(SqStack *S)
{
	return S->top - S->base;
}

//����ջ
Status Traverse(SqStack *S)
{
	SElemType *p;
	p = S->top - 1;
	while (p >= S->base)
	{
		printf("%d ", *p);
		p--;
	}
	printf("\n");
	return OK;
}

//���Ժ���
void test()
{
	SqStack S;
	InitStack(&S);
	int n;
	scanf("%d", &n);
	while (n--)
	{
		SElemType e;
		scanf("%d", &e);
		PushStack(&S, e);
	}
	printf("The length of the stack is: %d\n", Length(&S));
	printf("The elem of the stack is following from the top to base:\n");
	Traverse(&S);
}

int main()
{
	test();
	return 0;
}