#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct DoubleLink {
	ElemType data;//数据域
	struct DoubleLink* prior, * next;//前驱，后继指针
}DLink, * DLinkList;

DLinkList head;//定义头指针

/*
	DoubleLinkList(双链表的实现)

	函数模块
	HeadInsert() 头插法创建链表
	TailInsert() 尾插法创建链表
	GetElem() 获取指定位置的元素值
	LocateElem() 获取指定元素首个位置
	BefortInstert() 向指定位置前插入值
	AfterInstert() 向指定位置后插入值
	DeleteElem() 删除指定位置元素
	ListLength() 获取当前链表长度（不带头）
	PrintList() 打印当前链表
*/

//双链表的实现

/*
	头插法创建链表
	HeadInsert()
*/
DLinkList HeadInsert() {
	//初始化头指针
	head = NULL;
	//定义数据元素X
	int x;
	//定义新的节点的指针L
	DLink* L;
	
	//为头节点申请空间
	head = (DLink*)malloc(sizeof(DLink));
	//初始化链表为空
	head->next = NULL;
	head->prior = NULL;
	//输入数据
	scanf("%d", &x);
	//判断添加节点
	while (x != -1) {
		//创建新的节点
		L = (DLink*)malloc(sizeof(DLink));
		L->data = x;
		L->next = head->next;
		//插入第一个节点时不需要下面操作
		if (L->next != NULL) {
			head->next->prior = L;
		}
		head->next = L;
		L->prior = head;
		scanf("%d", &x);
	}
	return head;
}

/*
	尾插法
	TailInsert()
*/
DLinkList TailInsert() {
	head = NULL;
	head = (DLink*)malloc(sizeof(DLink));
	head->next = NULL;
	head->prior = NULL;

	int x;
	DLink* L,*Tail;
	Tail = head;
	scanf("%d", &x);
	while (x != -1) {
		L = (DLink*)malloc(sizeof(DLink));
		L->data = x;
		Tail->next = L;
		L->prior = Tail;
		Tail = L;
		scanf("%d",&x);
	}
	Tail->next = NULL;
	return head;
}

/*
	按位查找
	@param int i 所要查找的位置
	return 查找位置的元素值
*/
DLink *GetElem(DLinkList head, int i) {
	int j;
	for (j = 0; j < i; j++) {
		head = head->next;
	}
	if (j == i) {
		return head;
	}
	else
	{
		return NULL;
	}
}

/*
	按值查找
	@param ElemType e 所要查找的元素
	return 所查找元素第一次出现的位置
*/
int LocateElem(DLinkList head, ElemType e) {
	int i;
	DLink* p = head->next;
	for (i = 0; p != NULL; i++) {
		if (p->data == e) {
			return i + 1;
		}
		p = p->next;//移动指针位置
	}
	return -1;
}

/*
	前插
	@param ElemType e 所要插入的元素
	@param int i 所要插入的位置
	retrun head
*/
DLinkList BeforeInsert(DLinkList head, int i,ElemType e) {
	DLink* p, * L;
	p = GetElem(head, i - 1);
	L = (DLink*)malloc(sizeof(DLink));
	L->data = e;
	L->next = p->next;
	p->next->prior = L;
	L->prior = p;
	p->next = L;
	return head;
}

/*
	后插
	@param ElemType e 所要插入的元素
	@param int i 所要插入的位置
	retrun head
*/
DLinkList AfterInsert(DLinkList head, int i, ElemType e) {
	DLink* p, * L;
	p = GetElem(head, i);
	L = (DLink*)malloc(sizeof(DLink));
	L->data = e;
	L->next = p->next;
	p->next->prior = L;
	L->prior = p;
	p->next = L;
	return head;
}

/*
		删除指定位置元素
		@param int i 指定位置
		return head
*/
DLinkList DeleteElem(DLinkList head, int i) {
	DLink* p, * q;
	p = GetElem(head, i - 1);
	q = p->next;
	q->next->prior = p;
	p->next = q->next;
	free(q);
	return head;
}

/*
	求表长
*/
int ListLength(DLinkList head) {
	int j;
	for (j = 0; head->next != NULL; j++) {
		head = head->next;
	}
	return j;
}

/*
	遍历双链表
*/
void PrintList(DLinkList head) {
	head = head->next;
	while (head	!=NULL) {
		printf("Data:%d\t",head->data);
		head = head->next;//切记移动头节点位置
	}
	printf("\n");
}

int main() {
	DLink* head;
	int i;
	ElemType e;
	printf("头插法\n");
	head = HeadInsert();
	PrintList(head);
	printf("尾插法\n");
	head = TailInsert();
	PrintList(head);
	printf("请输入所要查找的元素位置:");
	scanf("%d", &i);
	printf("\n您查找的位于%d的元素是%d\n",i,*GetElem(head,i));
	printf("请输入所要查找的元素:");
	scanf("%d", &e);
	printf("\n您查找的元素%d位于%d\n", e, LocateElem(head,e));
	printf("=====================\n");
	printf("前插\n请输入要插入的元素:");
	scanf("%d",&e);
	printf("\n请输入要插入元素的位置：");
	scanf("%d",&i);
	head = BeforeInsert(head, i, e);
	PrintList(head);
	printf("=====================\n");
	printf("后插\n请输入要插入的元素:");
	scanf("%d", &e);
	printf("\n请输入要插入元素的位置：");
	scanf("%d", &i);
	head = AfterInsert(head, i, e);
	PrintList(head);
	printf("=====================\n");
	printf("请输入想要删除的元素位置：");
	scanf("%d",&i);
	head = DeleteElem(head, i);
	PrintList(head);
	printf("当前表长为%d",ListLength(head));
	return 0;
}