#pragma warning(disable:4996)
#include <stdio.h>
#include <malloc.h>
#include "LinkQueue.h"

#define MAX_VERTEX_NUM 20
#define OK 1
#define ERROR 0

typedef char VertexType;
//typedef int InfoType;
typedef int Status;

typedef int QElemType;

//�߱�
typedef struct ArcNode
{
	int adjvex; //�ñ���ָ����λ��
	struct ArcNode *nextarc; //ָ����һ������ָ��
	//InfoType *info; //�û������Ϣ��ָ��
} ArcNode;

//�����
typedef struct VerNode
{
	VertexType data; //������Ϣ
	ArcNode *firstarc; //ָ���һ�������ö���Ļ�
} VerNode, AdjList[MAX_VERTEX_NUM];

//ͼ����
typedef struct
{
	AdjList vertices;
	int vexnum, arcnum; //ͼ�ĵ�ǰ�������ͻ���
	//int kind; //ͼ�������־
} ALGraph;

int visit[MAX_VERTEX_NUM];

//�ڵ�Ԫ�ض�λ
int LocateVex(ALGraph *G, VertexType e)
{
	int tmp = -1; int i;
	for (i = 0; i < G->vexnum; i++)
	{
		if (G->vertices[i].data == e)
		{
			tmp = i; break;
		}
	}
	return tmp;
}

//�ڽӱ�ͷ��
Status HeadInsertArc(ALGraph *G, int pos, int adjvex)
{
	ArcNode *e;
	e = (ArcNode *)malloc(sizeof(ArcNode));
	e->adjvex = adjvex;
	e->nextarc = G->vertices[pos].firstarc;
	G->vertices[pos].firstarc = e;
	return OK;
}

//�ڽӱ�β��
Status TailInsertArc(ALGraph *G, int pos, int adjvex)
{
	ArcNode *e, *p;
	e = (ArcNode *)malloc(sizeof(ArcNode));
	e->adjvex = adjvex;
	e->nextarc = NULL;
	if (G->vertices[pos].firstarc == NULL)
		G->vertices[pos].firstarc = e;
	else
	{
		p = G->vertices[pos].firstarc;
		while (p->nextarc)
			p = p->nextarc;
		p->nextarc = e;
	}
	return OK;
}

//����ͼ
Status CreateGraph(ALGraph *G)
{
	int i;
	printf("Please input the vexnum and arcnum:");
	scanf("%d%d", &(G->vexnum), &(G->arcnum));
	getchar();
	for (i = 0; i < G->vexnum; i++)
	{
		G->vertices[i].data = getchar();
		G->vertices[i].firstarc = NULL;
	}
	getchar();
	for (i = 0; i < G->arcnum; i++)
	{
		char arc_s, arc_e;
		arc_s = getchar(); arc_e = getchar();
		int v_s = LocateVex(G, arc_s);
		int v_e = LocateVex(G, arc_e);
		//HeadInsertArc(G, v_s, v_e);
		//HeadInsertArc(G, v_e, v_s);
		TailInsertArc(G, v_s, v_e);
		TailInsertArc(G, v_e, v_s);
	}
	return OK;
}

//��ӡ�ڵ�
Status printVex(ALGraph *G)
{
	ArcNode *p; int i;
	for (i = 0; i < G->vexnum; i++)
	{
		printf("%d | %c", i, G->vertices[i].data);
		if (G->vertices[i].firstarc != NULL)
		{
			p = G->vertices[i].firstarc;
			while (p)
			{
				printf("-->%c", G->vertices[p->adjvex].data);
				p = p->nextarc;
			}
		}
		printf("\n");
	}
	return OK;
}

//������ȱ���
Status BFSTraverse(ALGraph *G)
{
	int i; LinkQueue Q;
	InitQueue(&Q); //��ʼ������
	for (int i = 0; i < G->vexnum; i++) //������Ϊ����Ϊδ����
		visit[i] = 0;
	for (int i = 0; i < G->vexnum; ++i)
	{
		if (0 == visit[i]) //ѡȡδ���ʵĶ���
		{
			visit[i] = 1; //δ����,��(ֻ)����һ��
			printf("%c ", G->vertices[i].data);
			EnQueue(&Q, i); //�ѷ��������
			while (!QueueEmpty(&Q)) //���в�Ϊ��
			{
				DeQueue(&Q, &i); //����
				ArcNode *p = G->vertices[i].firstarc; //ָ����һ���߱���
				while (p)
				{
					if (!visit[p->adjvex]) //δ���ʽ��
					{
						visit[p->adjvex] = 1;
						printf("%c ", G->vertices[p->adjvex].data);
						EnQueue(&Q, p->adjvex);
					}
					p = p->nextarc; //��һ���߱���
				}
			}
		}
	}
	printf("\n");
	return OK;
}

//�ǵݹ�
Status DFS_Non_Recursion(ALGraph *G, int i)
{
	ArcNode *p;
	printf("%c ", G->vertices[i].data);
	visit[i] = 1;
	p = G->vertices[i].firstarc;

	while (p)
	{
		if (!visit[p->adjvex])
		{
			printf("%c ", G->vertices[p->adjvex].data);
			visit[p->adjvex] = 1;
		}
		p = p->nextarc;
	}
	return OK;
}
//�ݹ�
Status DFS_Recursion(ALGraph *G, int i)
{
	ArcNode *p;
	printf("%c ", G->vertices[i].data);
	p = G->vertices[i].firstarc;
	visit[i] = 1;
	while (p)
	{
		if (!visit[p->adjvex])
		{
			DFS_Recursion(G, p->adjvex);
		}
		p = p->nextarc;
	}
	return OK;
}

//������ȱ���
Status DFSTraverse(ALGraph *G)
{
	int i;
	for (i = 0; i < G->vexnum; i++)
		visit[i] = 0;
	for (i = 0; i < G->vexnum; i++)
		if (!visit[i]) DFS_Non_Recursion(G, i);
	printf("\n");
	return OK;
}


