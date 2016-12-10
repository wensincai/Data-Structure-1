#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

#define MAXQSIZE 100 //队列最大长度

typedef char TElemType;
typedef int Status;

//定义树节点
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

//为栈/队列定义栈内元素类型
typedef BiTree SElemType; //栈元素为BiTree类型
typedef BiTree QElemType; //队列元素为BiTree类型


//************************************************************************

void test();
int main()
{
	test();
	return 0;
}


//************************************************************************

//定义栈
typedef struct
{
	SElemType *top; //栈顶指针
	SElemType *base; //在栈构造之前和销毁之后为NULL
	int stacksize; //当前已分配大小
}SqStack;

//初始化
Status InitStack(SqStack *S)
{
	S->base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if (!S->base) return ERROR;
	S->top = S->base;
	S->stacksize = STACK_INIT_SIZE;
	return OK;
}

//栈满
Status StackFull(SqStack *S)
{
	if (S->top - S->base >= S->stacksize)
		return OK;
	return ERROR;
}

//判空
Status StackEmpty(SqStack *S)
{
	if (S->top == S->base)
		return OK;
	return ERROR;
}

//压栈
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

//弹栈
Status PopStack(SqStack *S, SElemType* e)
{
	if (StackEmpty(S)) return ERROR;
	(*e) = *(--S->top);
	return OK;
}

//栈顶
Status GetTop(SqStack *S, SElemType* e)
{
	if (StackEmpty(S))
		return ERROR;
	(*e) = *(S->top - 1);
	return OK;
}

//************************************************************************

//队列定义
typedef struct
{
	QElemType *base;
	int front;
	int rear;
}SqQueue;

//初始化空队列
Status InitQueue(SqQueue *Q)
{
	Q->base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
	if (!Q->base) return ERROR;
	Q->front = Q->rear = 0;
	return OK;
}

//队满
Status QueueFull(SqQueue *Q)
{
	if ((Q->rear + 1) % MAXQSIZE == Q->front)
		return OK;
	return ERROR;
}

//队空
Status QueueEmpty(SqQueue *Q)
{
	if (Q->front == Q->rear)
		return OK;
	return ERROR;
}

//入队
Status EnQueue(SqQueue *Q, QElemType e)
{
	if (QueueFull(Q))
		return ERROR;
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
	return OK;
}

//出队
Status DeQueue(SqQueue *Q, QElemType *e)
{
	if (QueueEmpty(Q))
		return ERROR;
	(*e) = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXQSIZE;
	return OK;
}

//************************************************************************

//创建二叉树
Status CreateBiTree(BiTree *T)
{
	TElemType e;
	scanf("%c", &e);
	if (e == '#') *T = NULL;
	else
	{
		*T = (BiTNode *)malloc(sizeof(BiTNode));
		if (!(*T)) return ERROR;
		(*T)->data = e;
		CreateBiTree(&((*T)->lchild));
		CreateBiTree(&((*T)->rchild));
	}
	return OK;
}

Status visit(BiTNode *e)
{
	if (e)
	{
		printf("%c ", e->data);
		return OK;
	}
	return ERROR;
}

//前序递归
Status PreOrderTraverse_Recursion(BiTree T)
{
	if (visit(T))
	{
		PreOrderTraverse_Recursion(T->lchild);
		PreOrderTraverse_Recursion(T->rchild);
	}
	return OK;
}

//前序非递归
Status PreOrderTraverse_Non_Recursion(BiTree T)
{
	SqStack S; InitStack(&S);
	BiTNode *p; p = T;
	while (p || !StackEmpty(&S))
	{
		if (visit(p))
		{
			PushStack(&S, p);
			p = p->lchild;
		}
		else
		{
			PopStack(&S, &p);
			p = p->rchild;
		}
	}
	printf("\n");
	return OK;
}

//中序递归
Status InOrderTraverse_Recursion(BiTree T)
{
	if (T)
	{
		InOrderTraverse_Recursion(T->lchild);
		visit(T);
		InOrderTraverse_Recursion(T->rchild);
	}
	return OK;
}

//中序非递归
Status InOrderTraverse_Non_Recursion(BiTree T)
{
	SqStack S; InitStack(&S);
	BiTNode *p; p = T;
	while (p || !StackEmpty(&S))
	{
		if (p)
		{
			PushStack(&S, p);
			p = p->lchild;
		}
		else
		{
			PopStack(&S, &p);
			visit(p);
			p = p->rchild;
		}
	}
	printf("\n");
	return OK;
}

//中序非递归思路二
Status InOrderTraverse_Non_Recursion_2(BiTree T)
{
	SqStack S; InitStack(&S);
	BiTNode *p; PushStack(&S, T);
	while (!StackEmpty(&S))
	{
		while (GetTop(&S, &p) && p)
			PushStack(&S, p->lchild); //向左走到尽头
		PopStack(&S, &p); //回退空指针
		if (!StackEmpty(&S))
		{
			PopStack(&S, &p);
			visit(p);
			PushStack(&S, p->rchild);
		}
	}
	printf("\n");
	return OK;
}

//后序递归
Status PostOrderTraverse_Recursion(BiTree T)
{
	if (T)
	{
		PostOrderTraverse_Recursion(T->lchild);
		PostOrderTraverse_Recursion(T->rchild);
		visit(T);
	}
	return OK;
}

/**
*后序非递归
*/
/*Status PostOrderTraverse_Non_Recursion(BiTree T)
{
SqStack S; InitStack(&S);
BiTNode *p,*pre;
p = T; pre = NULL;
while(p || !StackEmpty(&S))
{
if(p)
{
PushStack(&S,p);
p = p->lchild;
}
else
{
PopStack(&S,&p);
if(p->rchild != NULL && )
p = p->rchild;
else
{
visit(p);
p = NULL; //将p置为NULL，为了将当前栈顶元素弹出，防止已输出元素再次压栈
}
}
}
return OK;
}*/

//层序非递归
Status LevelOrderTraverse_Non_Recursion(BiTree T)
{
	SqQueue Q; InitQueue(&Q);
	BiTNode *p; p = T;
	if (visit(p)) //访问根节点
	{
		EnQueue(&Q, p); //根节点入队
		while (!QueueEmpty(&Q))
		{

			DeQueue(&Q, &p); //出队
			if (visit(p->lchild))
				EnQueue(&Q, p->lchild);
			if (visit(p->rchild))
				EnQueue(&Q, p->rchild);
		}
		printf("\n");
	}
	return OK;
}

//深度
int Depth(BiTree T)
{
	int h, hl, hr;
	if (T == NULL)
		h = 0;
	else
	{
		hl = Depth(T->lchild);
		hr = Depth(T->rchild);
		if (hl >= hr) h = hl + 1;
		else h = hr + 1;
	}
	return h;
}

//递归计算叶子结点数
int CountLeaf_Recursion(BiTree T)
{
	int leaf;
	if (T == NULL)
		leaf = 0;
	else if (T->lchild == NULL && T->rchild == NULL)
		leaf = 1;
	else
		leaf = CountLeaf_Recursion(T->lchild) + CountLeaf_Recursion(T->rchild);
	return leaf;
}

//非递归计算叶子结点数
int CountLeaf_Non_Recursion(BiTree T)
{
	int leaf = 0;
	SqStack S; InitStack(&S);
	BiTNode *p; p = T;
	while (p || !StackEmpty(&S))
	{
		if (p)
		{
			PushStack(&S, p);
			if (p->lchild == NULL && p->rchild == NULL)
				leaf++;
			p = p->lchild;
		}
		else
		{
			PopStack(&S, &p);
			p = p->rchild;
		}
	}
	return leaf;
}

//层序输出叶子结点
Status LevelOrderTraverse_Leaf(BiTree T)
{
	SqQueue Q; InitQueue(&Q);
	BiTNode *p; p = T;
	if (p) //访问根节点
	{
		EnQueue(&Q, p); //根节点入队
		while (!QueueEmpty(&Q))
		{
			DeQueue(&Q, &p); //出队
			if (p->lchild == NULL && p->rchild == NULL)
				visit(p);
			else
			{
				if (p->lchild)
					EnQueue(&Q, p->lchild);
				if (p->rchild)
					EnQueue(&Q, p->rchild);
			}
		}
		printf("\n");
	}
	return OK;
}

//先序输出叶子结点
Status PreOrderTraverse_Leaf(BiTree T)
{
	if (T)
	{
		if (T->lchild == NULL && T->rchild == NULL)
			visit(T);
		PreOrderTraverse_Leaf(T->lchild);
		PreOrderTraverse_Leaf(T->rchild);
	}
	return OK;
}

//节点总个数
int CountNode_Recursion(BiTree T)
{
	int node;
	if (T == NULL)
		node = 0;
	else
		node = CountNode_Recursion(T->lchild) + CountNode_Recursion(T->rchild) + 1;
	return node;
}

//判断两株二叉树是否相等
Status IsEqual(BiTree T1, BiTree T2)
{
	int flag = 0;
	if (!T1 && !T2)
		flag = 1;
	else if (T1 && T2)
	{
		if (T1->data == T2->data)
		{
			if (IsEqual(T1->lchild, T2->lchild))
				flag = IsEqual(T1->rchild, T2->rchild);
		}
	}
	return flag;
}

// 复制二叉树
BiTNode* CopyTree(BiTree T)
{
	BiTNode *p, *lchild, *rchild;
	if (T == NULL)
		return ERROR;
	lchild = CopyTree(T->lchild);
	rchild = CopyTree(T->rchild);
	p = (BiTNode*)malloc(sizeof(BiTNode));
	p->data = T->data;
	p->lchild = lchild;
	p->rchild = rchild;
	return p;
}

/**
* 交换函数
*/
/*void swap(BiTNode **p,BiTNode **q)
{
BiTNode *tmp = NULL;
tmp = *p;
*p = *q;
*q = tmp;
}*/

//递归交换二叉树左右孩子
Status ExchangeChild_Recursion(BiTree T)
{
	BiTNode *tmp = NULL;
	if (T)
	{
		ExchangeChild_Recursion(T->lchild);
		ExchangeChild_Recursion(T->rchild);
		tmp = T->lchild;
		T->lchild = T->rchild;
		T->rchild = tmp;
		//swap(T->lchild,T->rchild);
		return OK;
	}
	return ERROR;
}

//非递归交换左右孩子
Status ExchangeChild_Non_Recursion(BiTree T)
{
	SqStack S; InitStack(&S);
	BiTNode *p; p = T;
	BiTNode *tmp = NULL;
	while (p || !StackEmpty(&S))
	{
		if (p)
		{
			PushStack(&S, p);
			tmp = p->lchild;
			p->lchild = p->rchild;
			p->rchild = tmp;
			//swap(p->lchild,p->rchild);
			p = p->lchild;
		}
		else
		{
			PopStack(&S, &p);
			p = p->rchild;
		}
	}
	return OK;
}

//根节点左插入
Status Insert_Root_LeftNode(BiTree T, TElemType e)
{
	BiTNode *p, *q;
	if (T == NULL)
		return ERROR;
	p = T->lchild;
	q = (BiTNode *)malloc(sizeof(BiTNode));
	q->data = e;
	q->lchild = p;
	q->rchild = NULL;
	T->lchild = q;
	return OK;
}

//查找某个信息是否在树中
BiTNode* FindNode(BiTree T, TElemType e)
{
	BiTNode *p; p = T;
	if (p == NULL)
		return NULL;
	else
	{
		if (p->data == e)
			return p;
		else
		{
			p = FindNode(p->lchild, e);
			if (p == NULL)
				p = FindNode(p->rchild, e);
			return p;
		}
	}
}

// 查找父亲节点
BiTNode* FindFather(BiTree T, TElemType e)
{
	if (T == NULL || T->data == e)
		return NULL;
	if ((T->lchild && T->lchild->data == e) ||
		(T->rchild && T->rchild->data == e))
		return T;
	BiTNode *p = FindFather(T->lchild, e);
	if (p == NULL)
		p = FindFather(T->rchild, e);
	return p;
}

//任意节点左插入(右节点类似，不再赘述)
Status InsertLeftNode(BiTree T, TElemType s, TElemType e)
{
	BiTNode *p = (BiTNode *)malloc(sizeof(BiTNode));
	p = FindNode(T, s);
	if (p == NULL)
		return ERROR;
	BiTNode *q = (BiTNode *)malloc(sizeof(BiTNode));
	q->data = e;
	q->lchild = p->lchild;
	q->rchild = NULL;
	p->lchild = q;
	return OK;
}

//根节点右插入
Status Insert_Root_RightNode(BiTree T, TElemType e)
{
	BiTNode *p, *q;
	if (T == NULL)
		return ERROR;
	p = T->rchild;
	q = (BiTNode *)malloc(sizeof(BiTNode));
	q->data = e;
	q->rchild = p;
	q->lchild = NULL;
	T->rchild = q;
	return OK;
}

/**
* 删除节点
*/
/*Status DeleteNode(BiTree T,TElemType e)
{
BiTNode *p = (BiTNode *)malloc(sizeof(BiTNode));
p = FindFather(T,s);
if(p == NULL)
return ERROR;
}*/

Status ChangeValue(BiTree T, TElemType s, TElemType e)
{
	BiTNode *p = NULL;
	p = FindNode(T, s);
	if (p == NULL)
		return ERROR;
	p->data = e;
	return OK;
}

// 销毁二叉树
Status Destroy(BiTree T)
{
	if (T == NULL)
		return ERROR;
	Destroy(T->lchild);
	Destroy(T->rchild);
	free(T);
	return OK;
}

//删除左子树
Status DestroyLeftTree(BiTree T)
{
	if (T == NULL)
		return ERROR;
	DestroyLeftTree(T->lchild);
	T->lchild = NULL;
	return OK;
}

//删除右子树
Status DestroyRightTree(BiTree T)
{
	if (T == NULL)
		return ERROR;
	DestroyLeftTree(T->rchild);
	T->rchild = NULL;
	return OK;
}

//最大值与最小值
BiTNode* MaxNode(BiTree T)
{
	if (T == NULL)
		return NULL;
	BiTNode *pMax = T, *tmp;
	tmp = MaxNode(T->lchild);
	if (tmp)
	{
		if (tmp->data > pMax->data)
			pMax = tmp;
	}
	tmp = MaxNode(T->rchild);
	if (tmp)
	{
		if (tmp->data > pMax->data)
			pMax = tmp;
	}
	return pMax;
}

//************************************************************************

// 测试函数(示例:ABC##DE#G##F###,leaf:3,depth:5)
void test()
{
	BiTree T;
	printf("Create bitree in preorder:\n");
	CreateBiTree(&T);

	printf("Traverse bitree in preorder:\n");
	PreOrderTraverse_Recursion(T); printf("\n");
	PreOrderTraverse_Non_Recursion(T);

	printf("Traverse bitree in inorder:\n");
	InOrderTraverse_Recursion(T); printf("\n");
	InOrderTraverse_Non_Recursion(T);
	InOrderTraverse_Non_Recursion_2(T);

	printf("Traverse bitree in postorder:\n");
	PostOrderTraverse_Recursion(T); printf("\n");

	printf("Traverse bitree in levelorder:\n");
	LevelOrderTraverse_Non_Recursion(T);

	printf("The count of node is: %d\n", CountNode_Recursion(T));
	printf("The depth of the tree is: %d\n", Depth(T));
	printf("The count of leaves is: %d\n", CountLeaf_Non_Recursion(T));
	printf("The count of leaves is: %d\n", CountLeaf_Recursion(T));
	printf("These leaves are following(in level):\n");
	LevelOrderTraverse_Leaf(T);
	printf("These leaves are following(in pre_order):\n");
	PreOrderTraverse_Leaf(T); printf("\n");

	/*printf("Insert Left:\n");
	TElemType s1,e1;
	printf("Please input the node and the insert node:");
	scanf("%c%c",&s1,&e1);
	InsertLeftNode(T,s1,e1);
	LevelOrderTraverse_Non_Recursion(T);*/

	/*printf("Change Value:\n");
	TElemType s2,e2;
	printf("Please input the node and the change node:");
	scanf("%c%c",&s2,&e2);
	ChangeValue(T,s2,e2);
	LevelOrderTraverse_Non_Recursion(T);*/

	printf("Find father:\n");
	TElemType e3;
	getchar();
	printf("Please input the node:");
	e3 = getchar();
	BiTNode *p = FindFather(T, e3);
	if (p)
		printf("The father node is %c: \n", p->data);
	else
		printf("No father node!\n");

	//************************************************************************
	printf("Exchange left and right:\n");
	ExchangeChild_Non_Recursion(T);
	printf("Traverse bitree in preorder:\n");
	PreOrderTraverse_Recursion(T); printf("\n");
	PreOrderTraverse_Non_Recursion(T);

	printf("Traverse bitree in inorder:\n");
	InOrderTraverse_Recursion(T); printf("\n");
	InOrderTraverse_Non_Recursion(T);
	InOrderTraverse_Non_Recursion_2(T);

	printf("Traverse bitree in postorder:\n");
	PostOrderTraverse_Recursion(T); printf("\n");

	printf("Traverse bitree in levelorder:\n");
	LevelOrderTraverse_Non_Recursion(T);
}
