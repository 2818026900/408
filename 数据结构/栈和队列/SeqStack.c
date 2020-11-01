#include<stdio.h>
#include<stdlib.h>

/*
	Stack（栈）

	函数模块
	InitStack() 初始化一个空栈
	StackEmpty() 判空
	StackLength() 栈长
	Push() 进栈
	Pop() 出栈
	GetTop() 获取栈顶元素
	ClearStack() 清空栈
*/

/*
	栈原理分析
	栈的实现类似线性表
	但栈的元素只能从头进，从头出，即先进后出
	
	初始设置
		栈顶指针S.top=-1，栈顶元素 S.data[S.top]
	进栈操作
		栈不满，栈顶指针加1，为栈顶元素赋值
	出栈操作
		栈非空，取出栈顶元素，栈顶指针减1
	栈空条件
		S.top = -1
	栈满条件
		S.top = MaxSize-1
	栈长
		s.top + 1
*/

//顺序栈实现

/*
	结构定义
*/
#define MaxSize 50//栈中最大元素数
typedef int ElemType;
typedef struct SeqStack {
	ElemType data[MaxSize];//存放栈中元素
	int top;//栈顶指针
}Sstack;

//定义栈s
Sstack s;

/*
	InitStack() 初始化一个空栈
*/
void InitStack() {
	//初始栈顶指针
	s.top = -1;
	printf("初始化成功\n");
}

/*
	StackEmpty() 判空
*/
void StackEmpty() {
	return s.top == -1 ? 0 : -1;//栈空返回0
}

/*
	StackLength() 栈长
*/
int StackLength() {
	return s.top + 1;
}

/*
	Push() 进栈
*/
void Push(ElemType e) {
	if (s.top == MaxSize - 1) {
		printf("栈满了\n");
		return -1;
	}
	s.data[++s.top] = e;
}

/*
	Pop() 出栈
*/
ElemType Pop() {
	if (s.top == -1) {
		printf("栈空了\n");
		return -1;
	}
	ElemType e;
	e = s.data[s.top--];
	return e;
}

/*
	GetTop() 获取栈顶元素
*/
ElemType GetTop() {
	if (s.top == -1) {
		printf("当前栈为空\n");
		return -1;
	}
	return s.data[s.top];
}

/*
	ClearStack() 清空栈
*/
void ClearStack() {
	s.top = -1;
	printf("已清空\n");
}



int main()
{
	int top;
	ElemType e;
	printf("栈\n");
	printf("\n====================\n");
	InitStack();
	StackEmpty();
	printf("入栈：\n请输入元素：");
	while (1) {
		scanf("%d", &e);
		if (e == -1) {
			break;
		}
		Push(e);
	}
	printf("top:%d\n", GetTop());
	printf("Length:%d\n", StackLength());
	while (s.top != -1) {
		printf("data:%d\t", Pop());
	}
	printf("\n");
	ClearStack();
	return 0;
}