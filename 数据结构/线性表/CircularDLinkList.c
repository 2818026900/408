#include<stdio.h>
#include<stdlib.h>

/*
	CircularDLinkList（循环双链表）

	函数模块
	initCDList() 初始化创建
	ListLength() 求表长
	InsertElem() 向指定位置插入元素
	DeleteElem() 删除指定位置元素
	*GetElem() 获得指定位置的元素
	LocateElem() 获得指定元素初次出现位置
	PrintList() 输出单循环链表
	DestoryList() 销毁链表
*/

typedef int ElemType;
typedef struct CDLinkList {
	ElemType data;//数据域
	struct CDLinkList* prior,* next;//前驱，后继指针
}CDlink,*CDLinkList;

CDLinkList head;//头节点

//实现循环双链表

/*
	初始化创建循环双链表
*/
CDLinkList initCDList() {
	//初始化
	head = (CDlink*)malloc(sizeof(CDlink));
	head->next = head;

	int x;//定义输入数据
	CDlink* L,* Tail;//新节点指针,尾节点指针

	Tail = head;
	Tail->next = head;
	Tail->prior = head;
	while (1) {
		scanf("%d", &x);
		if (x == -1) {
			break;
		}
		L = (CDlink*)malloc(sizeof(CDlink));
		L->data = x;
		L->next = Tail->next;
		Tail->next = L;
		L->prior = Tail;
		Tail = L;
	}

	return head;
}

/*
	输出循环双链表
*/
void PrintList(CDLinkList head) {
	CDlink* Tail;
	Tail = head->next;
	while (Tail != head) {
		printf("data:%d\t", Tail->data);
		Tail = Tail->next;
	}
	printf("\n");
}

/*
	求表长
*/
int ListLength(CDLinkList head) {
	int l = 0;
	CDlink* Tail;
	Tail = head->next;
	while (Tail != head) {
		l++;
		Tail = Tail->next;
	}
	return l;
}

/*
	查找指定位置元素
	@param int i 指定位置
*/
CDlink* GetElem(CDLinkList head,int i) {
	ElemType e = NULL;
	if (i<0 || i>ListLength(head)) {
		printf("查找指定位置错误！\n");
		return -1;
	}
	for (int j = 0; j < i; j++) {
		head = head->next;
		e = head;
	}
	return e;
}

/*
	查找指定元素位置
	@param ElemType e 指定元素
*/
int LocateElem(CDLinkList head, ElemType e) {
	int i;
	CDlink* Tail;
	Tail = head->next;
	for (i = 0; Tail != head ; i++) {
		if (Tail->data == e)
			return i+1;
		Tail = Tail->next;
	}
	return -1;
}

/*
	指定位置插入元素
	@param int i 指定位置
	@param ElemType e 待插入元素
*/
CDLinkList InsertElem(CDLinkList head, int i, ElemType e) {
	CDlink* p, * q;
	if (i<0 || i>ListLength(head)) {
		return -1;
	}
	p = GetElem(head, i);
	q = (CDlink*)malloc(sizeof(CDlink));
	q->data = e;
	q->next = p->next;
	p->next->prior = q;
	q->prior = p;
	p->next = q;
	return head;
}

/*
	删除指定位置元素
	@param int i 指定位置
*/
CDLinkList DeleteElem(CDLinkList head, int i) {
	CDlink* p, * q;
	if (i<0 || i>ListLength(head)) {
		printf("删除位置不存在!\n");
		return -1;
	}
	if (i == 1) {
		q = (CDlink*)malloc(sizeof(CDlink));
		q = head->next;
		head->next = q->next;
		q->next->prior = head;
	}
	else {
		p = GetElem(head, i - 1);
		q = p->next;
		p->next = q->next;
		q->next->prior = p;
	}
	free(q);
	return  head;
}

/*
	销毁双循环链表
*/
void DestroyList(CDLinkList head) {
	CDlink* p, * Tail;
	Tail = head->next;
	while (Tail != head) {
		p = Tail;
		Tail = Tail->next;
		free(p);
	}
	free(head);
}

int main() {
	CDlink* head;
	int i;
	ElemType e;
	head = initCDList();
	PrintList(head);
	printf("当前表长为%d\n",ListLength(head));
	printf("\n=========================\n");
	printf("请输入要查找的位置：");
	scanf("%d", &i);
	printf("\n位于%d的元素是%d", i, *GetElem(head, i));
	printf("\n=========================\n");
	printf("请输入要查找的元素：");
	scanf("%d", &e);
	printf("\n所查找的元素%d位于%d", e, LocateElem(head, e));
	printf("\n=========================\n");
	printf("请输入所要插入的元素：");
	scanf("%d", &e);
	printf("\n请输入所要插入的位置：");
	scanf("%d", &i);
	PrintList(InsertElem(head, i, e));
	printf("\n=========================\n");
	printf("请输入要删除的元素位置:");
	scanf("%d", &i);
	printf("\n删除成功：");
	PrintList(DeleteElem(head, i));
	printf("\n=========================\n");
	DestroyList(head);
	printf("销毁成功");
	return 0;
}