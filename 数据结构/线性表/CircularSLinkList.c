#include<stdio.h>
#include<stdlib.h>

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
	head = NULL;
	head = (CSlink*)malloc(sizeof(CSlink));


	int x;//输入数据定义
	CSlink* L,* Tail;//新建节点指针L,尾指针Tail
	Tail = head;
	scanf("%d", &x);

	while (x != -1) {
		L = (CSlink*)malloc(sizeof(CSlink));
		L->data = x;
		Tail->next = L;
		L->next = head;
		Tail = L;
		scanf("%d", &x);
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

int main() {
	CSlink* head;
	head = initCSList();
	PrintList(head);
	return 0;
}