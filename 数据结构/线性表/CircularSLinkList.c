#include<stdio.h>
#include<stdlib.h>

/*
	CircularSLinkList（循环单链表）

	函数模块
	initCSList() 初始化创建
	ListLength() 求表长
	InsertElem() 向指定位置插入元素
	DeleteElem() 删除指定位置元素
	*GetElem() 获得指定位置的元素
	LocateElem() 获得指定元素初次出现位置
	PrintList() 输出单循环链表
	DestoryList() 销毁链表
*/

typedef int ElemType;
typedef struct CSLinkList {
	ElemType data;
	struct CSLinkList* next;
}CSlink,*CSLinkList;

CSLinkList head;//定义头指针


//实现循环单链表

/*
	初始化创建循环单链表
*/
CSLinkList initCSList(){
	//初始化
	head = (CSlink*)malloc(sizeof(CSlink));
	head->next = head;


	int x;//输入数据定义
	CSlink* L,* Tail;//新节点指针,尾指针
	Tail = head;
	Tail->next = head;
	while (1) {
		scanf("%d", &x);
		if (x == -1) {
			break;
		}
		L = (CSlink*)malloc(sizeof(CSlink));
		L->data = x;
		L->next = Tail->next;
		Tail->next = L;
		Tail = L;
	}
	return head;
}

/*
	输出循环单链表
*/
void PrintList(CSLinkList head) {
	CSlink* Tail;
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
int ListLength(CSLinkList head) {
	int l;
	CSlink* Tail;
	Tail = head->next;
	for (l = 0; Tail!=head; l++) {
		Tail = Tail->next;
	}
	return l;
}

/*
	查找指定位置的元素
	@param int i 指定位置
	return ElemType e
*/
CSlink* GetElem(CSLinkList head, int i) {
	ElemType e = NULL;
	if (i<0 || i>ListLength(head)) {
		printf("查找位置错误！\n");
		return -1;
	}
	for (int j = 0; j < i; j++) {
		head = head->next;
		e = head;
	}
	return e;
}

/*
	查找指定元素的位置
	@param ElemType e 指定元素
	return int i
*/
int LocateElem(CSLinkList head,ElemType e) {
	int i;
	CSlink* Tail;
	Tail = head->next;
	for (i=0; Tail != head; i++) {
		if (Tail->data == e) {
			return i + 1;
		}
		Tail = Tail->next;
	}
	return -1;
}


/*
	插入数据到循环单链表
	@param int i 指定位置后
	@param ElemType e 指定元素
	return head
*/
CSLinkList InsertElem(CSLinkList head,int i,ElemType e) {
	CSlink* p, * q;
	if (i<0 || i>ListLength(head)) {
		return -1;
	}
	p = GetElem(head, i);
	q = (CSlink*)malloc(sizeof(CSlink));
	q->data = e;
	q->next = p->next;
	p->next = q;
	return head;
}

/*
	删除指定位置元素
	@param int i 指定位置
*/
CSLinkList DeleteElem(CSLinkList head, int i) {
	CSlink* p,* q;
	if (i<0 || i>ListLength(head)) {
		printf("删除位置不存在");
		return -1;
	}
	if (i == 1) {
		q = (CSlink*)malloc(sizeof(CSlink));
		q = head->next;
		head->next = q->next;
	}
	else
	{
		p = GetElem(head, i - 1);
		q = p->next;
		p->next = q->next;
	}
	free(q);
	return head;
}

/*
	销毁循环单链表
*/
void DestroyList(CSLinkList head) {
	CSlink* p,* Tail;
	Tail = head->next;
	while (Tail != head) {
		p = Tail;
		Tail = Tail->next;
		free(p);
	}
	free(head);
	
}

int main() {
	CSlink* head;
	int i;
	ElemType e;
	head = initCSList();
	PrintList(head);
	printf("当前表长为%d",ListLength(head));
	printf("\n=========================\n");
	printf("请输入要查找的位置：");
	scanf("%d",&i);
	printf("\n位于%d的元素是%d", i, *GetElem(head, i));
	printf("\n=========================\n");
	printf("请输入要查找的元素：");
	scanf("%d", &e);
	printf("\n所查找的元素%d位于%d", e, LocateElem(head,e));
	printf("\n=========================\n");
	printf("请输入所要插入的元素：");
	scanf("%d", &e);
	printf("\n请输入所要插入的位置：");
	scanf("%d", &i);
	PrintList(InsertElem(head,i,e));
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