#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0

typedef int QElemType;
typedef int Status;

typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front; //队头指针
	QueuePtr rear; //队尾指针
	int length;
}LinkQueue;

//初始化
Status InitQueue(LinkQueue *Q)
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front) return ERROR;
	Q->front->next = NULL;
	Q->length = 0;
	return OK;
}

//入队
Status EnQueue(LinkQueue *Q, QElemType e)
{
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) return ERROR;
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	Q->length++;
	return OK;
}

//队空
Status QueueEmpty(LinkQueue *Q)
{
	if (Q->front == Q->rear) return OK;
	return ERROR;
}

//出队
Status DeQueue(LinkQueue *Q, QElemType *e)
{
	QueuePtr p;
	if (QueueEmpty(Q)) return ERROR;
	p = Q->front->next;
	*e = p->data;
	Q->front->next = p->next;
	if (p == Q->rear) Q->front = Q->rear;
	free(p);
	Q->length--;
	return OK;
}

//销毁
Status Destroy(LinkQueue *Q)
{
	while (Q->front)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	return OK;
}
