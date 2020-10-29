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
	@param i 所要查找的值所处位值
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
	按值查找
	@param ElemType e 所要查找元素
	return int i 所查找元素位置
	LocateElem()
*/
int LocateElem(LinkList head,ElemType e) {
	int i;
	head = head->next;
	for (i = 0; head != NULL; i++) {
		if (head->data == e) {
			return i + 1;
		}
		head = head->next;//移动指针位置
	}
	return -1;
}

/*
	插入节点（前插）
	@param ElemType e 所要插入的值
	@param int i 所要插入节点的当前位置
	return head 返回插入成功后的头指针
	BeforeInstert()
*/
LinkList BefortInstert(LinkList head,ElemType e ,int i) {
	//找到插入节点的前驱位置p,L为新节点
	link* p,*L;
	p = GetElem(head,i-1);
	//插入节点，移动元素
	L = (link*)malloc(sizeof(link));
	L->data = e;
	L->next = p->next;
	p->next = L;
	return head;
}

/*
	插入节点（后插）
	@param ElemType e 所要插入的值
	@param int i 所要插入节点的当前位置
	return head 返回插入成功后的头指针
	BeforeInstert()
*/
LinkList AfterInstert(LinkList head, ElemType e, int i) {
	link* p, * L;//找到插入节点的当前位置p,L为新节点
	p = GetElem(head , i);
	//插入节点移动位置
	L = (link*)malloc(sizeof(link));
	L->data = e;
	L->next = p->next;
	p->next = L;
	return head;
}

/*
	删除指定位置节点
	@param int i 待删除元素的位置
	DeleteElem();
*/
LinkList DeleteElem(LinkList head, int i) {
	link* p, * q;//找到待删除节点的前驱p,当前节点q
	p = GetElem(head , i-1);
	q = p->next;
	p->next = q->next;
	free(q);
	 
	/*
		free(q)时出现断点错误是因为在BeforeInsert/AfterInsert中申请内存空间时使用
			(ElemType*)malloc(ElemType);
		这句话只为指针申请了空间而没有为结构体申请空间，所以释放后空间不足以放下结构题引发断点
		正确写法：
			(link*)malloc(link);
		参考文章URL:https://blog.csdn.net/linzi_1988/article/details/79564440?utm_medium=distribute.pc_relevant_ask_down.none-task-blog-baidujs-1.nonecase&depth_1-utm_source=distribute.pc_relevant_ask_down.none-task-blog-baidujs-1.nonecase
	*/

	return head;
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


/*
	求表长（不带头节点）
*/
int ListLength(LinkList head) {
	int l=0;
	while (head->next)
	{
		l++;
		head = head->next;//切记移动头指针
	}
	return l;
}


int main() {
	link* head;
	ElemType e;
	head = HeadInsert();
	printf("头插法：\n");
	PrintList(head);
	printf("第2个值是%d\n", *GetElem(head, 2));
	head = TailInsert();
	printf("尾插法：\n");
	PrintList(head);
	printf("请输入要查找的值：");
	scanf("%d", &e);
	printf("\n值%d的位置是%d\n", e,LocateElem(head,e));
	head = BefortInstert(head,10,2);
	PrintList(head);
	head = AfterInstert(head, 50, 2);
	PrintList(head);
	head = DeleteElem(head,3);
	PrintList(head);
	printf("当前表长为%d\n",ListLength(head));
	return 0;
}