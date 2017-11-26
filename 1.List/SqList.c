#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define INCREMENT 10

#define OK 1
#define ERROR 0

 typedef int Status;
 typedef int ElemType;

 typedef struct
 {
 	ElemType *data; //节点数据
 	int length; //顺序表长度
 	int size; //顺序表大小
 }SqList;

//初始化
Status InitList(SqList *L)
{
	L->data = (ElemType *)malloc(MAXSIZE*sizeof(ElemType));
	if(!L->data) return ERROR;
	L->length = 0;
	L->size = MAXSIZE;
	return OK;
}

//清空
Status Clear(SqList *L)
{
	if(!L->data) return ERROR;
	L->length = 0;
	return OK;
}

//销毁
 Status Destroy(SqList *L)
 {
 	if(L->data)
 	{
 		free(L->data);
 		L = NULL;
 		return OK;
 	}
 	return ERROR;
 }

//根据位置返回元素
Status GetElem(SqList *L,int pos,ElemType* e)
{
	if(pos<1||pos>L->length) return ERROR;
	(*e) = L->data[pos-1];
	return OK;
}

//根据元素返回位置
Status GetPos(SqList *L,ElemType e,int* pos)
{
	int i = 0;
	if(!L->data) return ERROR;
	while(i < L->length)
	{
		if(e == L->data[i])
		{
			(*pos) = i+1;
			return OK;
		}
		i++;
	}
	(*pos) = -1;
	return ERROR;
}

//表空
Status ListEmpty(SqList *L)
{
	return L->length == 0?1:0;
}

//根据位置插入元素
Status Insert(SqList *L,int pos,ElemType e)
{
	ElemType* newBase;
	int i = 0;
	if(pos < 1||pos > L->length+1)
		return ERROR;
	if(L->length >= L->size)
	{
		newBase = (ElemType *)realloc(L->data,(L->size+INCREMENT)*sizeof(ElemType));
		L->data = newBase;
		L->size+=INCREMENT;
	}
	for(i=L->length-1;i>=pos-1;i--)
		L->data[i+1] = L->data[i]; //后移
	L->data[pos-1] = e;
	L->length++;
	return OK;
}

//创建
Status Create(SqList *L,int n)
{
    ElemType e;
	int i = 0;
	while(i < n)
	{
	    scanf("%d",&e);
		Insert(L,i+1,e);
		i++;
	}
	return OK;
}

//根据位置删除元素
Status DeleteAccordToPos(SqList *L,int pos,ElemType* e)
{
	int i = 0;
	if(!L->data) return ERROR;
	if(pos < 1||pos > L->length)
		return ERROR;
	(*e) = L->data[pos-1];
	for(i = pos-1;i < L->length;++i)
		L->data[i] = L->data[i+1];
	L->length--;
	return OK;
}

//根据值删除元素
Status DeleteAccordToElem(SqList *L,ElemType e,int* pos)
{
    int i = 0;
	if(!L->data) return ERROR;
	while(i < L->length)
	{
		if(e == L->data[i])
		{
			(*pos) = i+1;
			while(i < L->length)
            {
                L->data[i] = L->data[i+1];
                i++;
            }
            L->length--;
			return OK;
		}
		i++;
	}
	(*pos) = -1;
	return ERROR;
}

// 合并
/*Status Merge(SqList *L_1,SqList L_2,SqList L)
{

}*/

//遍历
Status Traverse(SqList *L)
{
	int i = 0;
	while(i < L->length)
	{
		printf("%d ",L->data[i]);
		i++;
	}
	printf("\n");
	return OK;
}

//测试
void test()
{
	SqList L;
	ElemType e;
	//初始化
	InitList(&L);

	//创建
	printf("=============================================\n");
	int n;
	printf("Please input the number of elem:");
	scanf("%d",&n);
	Create(&L,n);
	Traverse(&L);

	//判空
	printf("=============================================\n");
	printf("Is it empty ? %d\n",ListEmpty(&L));

	//指定位置检查元素
	printf("=============================================\n");
	ElemType e2;
	int pos2;
	printf("Please input the pos of elem to be checked:");
	scanf("%d",&pos2);
	GetElem(&L,pos2,&e2);
	printf("NO.%d is: %d\n",pos2,e2);

	//指定元素检查位置
	printf("=============================================\n");
	ElemType e3;
	int pos3;
	printf("Please input the elem to be checked:");
	scanf("%d",&e3);
	GetPos(&L,e3,&pos3);
	printf("%d is: NO.%d\n",e3,pos3);

	//指定位置删除
	printf("=============================================\n");
	ElemType e4;
	int pos4;
	printf("Please input the pos of elem to be deleted:");
	scanf("%d",&pos4);
	DeleteAccordToPos(&L,pos4,&e4);
	printf("The deleted number is: %d\n",e4);
	Traverse(&L);

	//指定元素删除
	printf("=============================================\n");
	ElemType e5;
	int pos5;
	printf("Please input the elem to be deleted:");
	scanf("%d",&e5);
	DeleteAccordToElem(&L,e5,&pos5);
	printf("The pos of the deleted number is: %d\n",pos5);
	Traverse(&L);

	//ָ指定位置插入
	printf("=============================================\n");
	ElemType e6;
	int pos6;
	printf("Please input the pos of elem to be inserted:");
	scanf("%d",&pos6);
	printf("Please input the elem to be inserted:");
	scanf("%d",&e6);
	Insert(&L,pos6,e6);
	Traverse(&L);
}

int main()
{
	test();
	return 0;
}