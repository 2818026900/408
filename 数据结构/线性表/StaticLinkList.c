#include<stdio.h>
#include<stdlib.h>

/*
	所引用的函数要位于引用的地方的前面，不然报错
		函数重定义
*/

/*
	静态链表与动态链表的区别
		静态链表限制了存储空间范围为一个数组空间
		动态链表储存空间为整个内存空间
	静态链表由于限制了储存空间范围所以需要自行实现malloc与free函数
*/

/*
	静态链表实现原理
		将数组所有空间初始化为一个备用链表，每个数组节点代表一个数据域
		存储静态链表时将备用链表第一个数据域作为备用链表头，第二个数据域名作为数据链表头
		每次动态申请一个数据域作为数据节点插入到数据链表，直到数组最后一个数据域为止
		即备用链表用完时表长为2.
*/

/*
	StaticLinkList(静态链表)

	函数模块
	initList() 初始化创建
	ListLength() 求表长
	InsertElem() 向指定位置插入元素
	DeleteElem() 删除指定位置元素
	GetElem() 获得指定位置的元素
	LocateElem() 获得指定元素初次出现位置
	PrintList() 输出单循环链表
	reserve() 初始化数组为备用链表
	MallocList() 申请空间
	FreeLisst() 释放空间
*/

#define MaxSize 100//数组空间
typedef int ElemType;
typedef struct SList {
	ElemType data;//数据域
	int next;//游标（相当于其他链表的指针域）
}S;//别名S

//静态链表的实现

/*
	将数组变为备用链表
*/
void reserve(S *array) {
	for (int i = 0; i < MaxSize; i++) {
		array[i].next = i + 1;
	}
	array[MaxSize - 1].next = 0;//设置备用链表的最后一个节点的下一个节点为0
}

/*
	实现malloc函数,即从备用链表上取下一个空闲节点
	return 所取下的节点的地址
*/
int MallocList(S* array) {
	int i;//所取下的节点地址
	i = array[0].next;//从备用链表的头节点的下一个依次取下空闲节点
	//移动头节点
	if (array[0].next) {
		array[0].next = array[i].next;
	}
	return i;
}

/*
	创建静态链表（初始化）
	return 返回数据链表头指针
*/
int InitList(S *array) {
	//初始化数组空间为备用链表
	reserve(array);
	//为头节点申请空间
	int head = MallocList(array);//array[1]为数据链表的头节点
	//头节点的下一个指针指向空
	array[head].next = 0;

	//定义输入数据元素类型
	int x;
	while (1) {
		scanf("%d", &x);
		if (x == -1) {
			break;
		}
		//申请新的节点空间
		int L = MallocList(array);
		array[L].data = x;
		//头插法
		array[L].next = array[head].next;
		array[head].next = L;
	}
	return head;
}

/*
	遍历静态链表
*/
void PrintList(S *array,int head) {
	head = array[head].next;
	while (head) {
		printf("data:%d\tnext:%d\n", array[head].data,array[head].next);
		head = array[head].next;
	}
	printf("\n");
}

/*
	求表长
*/
int ListLength(S* array, int head) {
	int l = 0;
	head = array[head].next;
	while (head) {
		head = array[head].next;
		l++;
	}
	return l;
}

/*
	查找指定位置的元素
	@param int i 指定位置
*/
ElemType GetElem(S* array, int head, int i) {
	ElemType e = NULL;
	if (i<0 || i>ListLength(array, head)) {
		printf("查找位置有误！\n");
		return -1;
	}
	for (int j = 0; j < i; j++) {
		head = array[head].next;
		e = array[head].data;
	}
	return e;
}

/*
	查找指定元素的位置
	@param ElemType e 指定元素
*/
int LocateElem(S* array, int head, ElemType e) {
	int i=0;
	head = array[head].next;
	while (head)
	{
		if (array[head].data == e)
			return i + 1;
		head = array[head].next;
		i++;
	}
	return i;
}

/*
	插入元素到指定位置
	@param int i 指定元素位置
	@param ElemType e 所要插入的元素
*/
int InsertElem(S* array, int head, int i, ElemType e) {
	if (i<0 || i>ListLength(array, head))
	{
		printf("插入位置不对！\n");
		return -1;
	}
	int p, q;//p表示待插入元素上一节点的位置，q表示新的节点
	if (i == 1) {
		p = head;
	}
	else
	{
		p = GetElem(array, head, i - 1);
	}
	q = MallocList(array);
	array[q].data = e;
	array[q].next = array[p].next;
	array[p].next = q;
	return head;
}

/*
	释放元素空间，即将需要释放的元素连接到备用链表
*/
void FreeList(S* array, int i) {
	array[i].next = array[0].next;
	array[0].next = i;
}

/*
	删除指定位置的元素
	@param int i 指定位置
*/
int DeleteElem(S* array, int head, int i) {
	if (i<0 || i>ListLength(array, head))
	{
		printf("删除位置不存在！\n");
		return -1;
	}
	int p, q;//p表示待插入元素上一节点的位置，q表示需要删除的节点
	if (i == 1) {
		q = array[head].next;
		array[head].next = array[q].next;
	}
	else 
	{
		p = GetElem(array, head, i - 1);
		q = array[p].next;
		array[p].next = array[q].next;
	}
	FreeList(array, q);
	return head;
}


int main()
{
	S array[MaxSize];
	int i;
	ElemType e;
	reserve(array);
	int head = InitList(array);
	PrintList(array, head);
	printf("当前链表的长度为%d\n", ListLength(array, head));
	printf("\n=========================\n");
	printf("请输入要查找的位置：");
	scanf("%d", &i);
	printf("\n位于%d的元素是%d", i, GetElem(array, head, i));
	printf("\n=========================\n");
	printf("请输入要查找的元素：");
	scanf("%d", &e);
	printf("\n所查找的元素%d位于%d", e, LocateElem(array, head, e));
	printf("\n=========================\n");
	printf("请输入所要插入的元素：");
	scanf("%d", &e);
	printf("\n请输入所要插入的位置：");
	scanf("%d", &i);
	head = InsertElem(array, head, i, e);
	PrintList(array, head);
	printf("\n=========================\n");
	printf("请输入要删除的元素位置:");
	scanf("%d", &i);
	printf("\n删除成功：\n");
	PrintList(array, DeleteElem(array, head, i));
	return 0;
}