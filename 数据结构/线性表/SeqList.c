#include <stdio.h>
#include <stdlib.h>

//顺序表的实现
/**
*initList(&L)初始化顺序表
*ListLength(L):求表长，返回线性表长度，即线性表元素个数。
*LocateElem(L,e):按值查找，查找表中具有给定关键字值的元素。
*GetElem(L,i):按位查找，获取表中第i个位置的元素的值。
*ListInsert(&L,i,e):插入操作，在表中第i个位置插入元素。
*ListDelete(&L,i):删除i位置的元素并返回删除值。
*PrintList(L):输出线性表
*Empty(L):判空
*DestroyList(&L):销毁表，并释放空间。
*
*/

//顺序表实现
#define MaxSize  100 //定义顺序表最大长度
typedef int ElemType;//定义顺序表中元素的ElemType，此处假设为int类型
typedef struct SeqList
{
	ElemType* base;//顺序表储存基地址
	int length;//当前顺序表长度
	int lengthMax;//线性表最大长度
}SeqList;

//初始化线性表
SeqList initList(SeqList* seq) {
	seq->lengthMax = MaxSize;//设置顺序表最大长度
	seq->base = (ElemType*)malloc(sizeof(ElemType)*seq->lengthMax);//初始化申请空间，大小为lengthMax*类型长度
	seq->length = 0;//设置初始顺序表为空
	return *seq;
}

//求表长
int ListLength(SeqList *seq) {
	if (seq->length >= 0 && seq->length <= seq->lengthMax) {
		return seq->length;
	}
	return -1;
}

//判断顺序表为空
int Empty(SeqList* seq) {
	return seq->length == 0;
}

//遍历顺序表
void PrintList(SeqList* seq) {
	int i;
	for (i = 0; i < seq->length; i++) {
		printf("%d\t", seq->base[i]);
	}
	printf("\n");
}

int ListInsert(SeqList* seq, int i, ElemType e) {
	//i是一个从1开始的值
	
	//判断空间是否满了
	if (seq->length == seq->lengthMax) {
		printf("空间不足，无法插入！");
		return -1;
	}

	//判断插入位置是否符合规范
	if (i - 1 < 0 || i - 1 > seq->length) {
		printf("插入位置不合法");
		return -1;
	}

	//插入操作
	for (int j = seq->length; j > i-1; j--) {
		*(seq->base + j + 1) = *(seq->base + j);
	}
	*(seq->base + i - 1) = e;
	seq->length = seq->length + 1;
	return 0;
}

//删除一个指定位置元素操作
ElemType DeleteList(SeqList* seq,int i) {
	ElemType e;
	//表为空删除失败
	if (seq->length == 0) {
		printf("该表为空，请插入元素再试！");
		return -1;
	}
	//删除位置不对，删除失败
	if (i<1 || i>seq->length) {
		printf("请输入正确删除位置后，再试！");
		return -1;
	}
	e = seq->base[i - 1];//存储删除值
	//向前移动元素位置
	for (int j = i; j < seq->length; j++) {
		seq->base[j - 1] = seq->base[j];
	}
	seq->length--;
	return e;
}

//得到指定位置值
ElemType GetElem(SeqList* seq, int i) {
	if (i<1 || i>seq->length) {
		printf("当前位置不对，请重新输入！");
		return -1;
	}
	return seq->base[i-1];
}

//查找指定值第一次出现位置
int LocateElem(SeqList* seq, ElemType e) {
	int i;
	for (i = 0; i < seq->length; i++) {
		if (seq->base[i] == e) {
			return i+1;
		}
	}
	return -1;//返回查找值第一次找到位置
}

//销毁顺序表
int DestroyList(SeqList* seq) {
	//清空线性表
	if (seq->length > 0 && seq->length < seq->lengthMax) {
		seq->length = 0;
		//线性表总长归0
		seq->lengthMax = 0;
		//释放空间
		free(seq->base);
		//检查是否成功
		printf("销毁成功\n");
		return 0;
	}
	printf("销毁失败\n");
	return -1;
}

int main() {
	SeqList seq;//声明顺序表
	initList(&seq);//创建顺序表
	if (Empty(&seq)) {
		printf("当前表为空\n");
	}
	ListInsert(&seq,1,500);
	printf("第1个位置的值为%d\n", GetElem(&seq, 1));
	ListInsert(&seq, 2, 500);
	printf("第2个位置的值为%d\n", GetElem(&seq, 2));
	printf("查找值为500的位置为：%d\n",LocateElem(&seq,500));
	int l = ListLength(&seq);
	printf("当前表长为%d\n", l);
	PrintList(&seq);
	printf("删除元素为%d\n",DeleteList(&seq, 1));
	ListInsert(&seq, 1, 1000);
	printf("第1个位置的值为%d\n", GetElem(&seq, 1));
	DestroyList(&seq);
	return 0;
}
