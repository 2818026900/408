#include<stdio.h>
#include<stdlib.h>

//0表示成功，-1表示失败

typedef int ElemType;//定义ElemType类型为int
typedef struct LinkList {
	ElemType data;//数据域
	struct LinkList *next;//指针域
}link, *LinkList;//link是节点类型，LinkList是指向link节点的指针类型。

LinkList head;//定义头指针


//单链表的实现

/*
	头插法建立单链表
	插入顺序与输入顺序恰好相反，每次将输入节点插入在最前端
	HeadInsert();
*/
LinkList HeadInsert() {
	head = NULL;//初始化头指针
	int x;//定义数据元素为int型
	link* L;//定义一个新节点的指针

	//创建头节点，申请空间
	head = (link*)malloc(sizeof(link));
	//初始化链表为空
	head->next = NULL;
	//输入数据
	scanf("%d", &x);
	//如果输入为-1，退出
	while (x != -1) {
		//创建新节点
		L = (link*)malloc(sizeof(link));
		//将x赋值给新节点数据域
		L->data = x;

		//将新节点插入到表中

		//替换头节点的下一个指针为新节点的下一个指针
		L->next = head->next;
		//头节点的下一个指针指向新节点
		head->next = L;


		scanf("%d",&x);
	}
	//返回头指针
	return head;
}


/*
	尾插法建立单链表
	插入顺序与输入顺序相同，每次将输入节点插入在最尾端
	Tailnsert();
*/
LinkList TailInsert() {
	head = NULL;//初始化头指针
	int x;//定义数据元素为int型
	link* L, * Tail;//定义一个新节点的指针L,尾部元素指针Tail

	/*
		不能在还没有初始化申请空间时进行相互赋值
		即在这里写
			Tail = head; 
		为错误写法。
	*/

	head = (link*)malloc(sizeof(link));//创建头结点，申请空间
	head->next = NULL;//初始化链表
	Tail = head;//尾指针指向头节点
	scanf("%d", &x);//输入数据
	while (x != -1) {
		L = (link*)malloc(sizeof(link));//为新节点申请空间
		L->data = x;//将x赋值给新节点数据域
		Tail->next = L;//尾节点的下一个指针指向新节点
		Tail = L;//替换新节点为链表尾节点
		scanf("%d", &x);
	}
	Tail->next = NULL;//尾节点的下一节点指向空
	return head;
}

/*
	按位查找
	@peram i 所要查找的值所处位值
	GetElem()
*/
link* GetElem(LinkList head, int i) {
	int j = 0;
	link* p=head;//头节点赋值给p
	while (j < i && p->next != NULL) {
		p = p->next;
		j++;
	}
	if (j == i) {
		return p;
	}
	else
	{
		printf("查找位置出错，请重新输入\n");
		return NULL;
	}
}

/*
	遍历链表
*/
void PrintList(LinkList head) {
	head = head->next;
	while (head) {
		printf("data:%d\t", head->data);
		head = head->next;
	}
	printf("\n");
}

int main() {
	link* head;
	head = HeadInsert();
	printf("头插法：\n");
	PrintList(head);
	printf("第2个值是%d\n", *GetElem(head, 2));
	head = TailInsert();
	printf("尾插法：\n");
	PrintList(head);
	printf("第2个值是%d\n",*GetElem(head,2));
	return 0;
}