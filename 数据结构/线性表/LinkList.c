#include<stdio.h>
#include<stdlib.h>

//0��ʾ�ɹ���-1��ʾʧ��

typedef int ElemType;//����ElemType����Ϊint
typedef struct LinkList {
	ElemType data;//������
	struct LinkList *next;//ָ����
}link, *LinkList;//link�ǽڵ����ͣ�LinkList��ָ��link�ڵ��ָ�����͡�

LinkList head;//����ͷָ��


//�������ʵ��

/*
	ͷ�巨����������
	����˳��������˳��ǡ���෴��ÿ�ν�����ڵ��������ǰ��
	HeadInsert();
*/
LinkList HeadInsert() {
	head = NULL;//��ʼ��ͷָ��
	int x;//��������Ԫ��Ϊint��
	link* L;//����һ���½ڵ��ָ��

	//����ͷ�ڵ㣬����ռ�
	head = (link*)malloc(sizeof(link));
	//��ʼ������Ϊ��
	head->next = NULL;
	//��������
	scanf("%d", &x);
	//�������Ϊ-1���˳�
	while (x != -1) {
		//�����½ڵ�
		L = (link*)malloc(sizeof(link));
		//��x��ֵ���½ڵ�������
		L->data = x;

		//���½ڵ���뵽����

		//�滻ͷ�ڵ����һ��ָ��Ϊ�½ڵ����һ��ָ��
		L->next = head->next;
		//ͷ�ڵ����һ��ָ��ָ���½ڵ�
		head->next = L;


		scanf("%d",&x);
	}
	//����ͷָ��
	return head;
}


/*
	β�巨����������
	����˳��������˳����ͬ��ÿ�ν�����ڵ��������β��
	Tailnsert();
*/
LinkList TailInsert() {
	head = NULL;//��ʼ��ͷָ��
	int x;//��������Ԫ��Ϊint��
	link* L, * Tail;//����һ���½ڵ��ָ��L,β��Ԫ��ָ��Tail

	/*
		�����ڻ�û�г�ʼ������ռ�ʱ�����໥��ֵ
		��������д
			Tail = head; 
		Ϊ����д����
	*/

	head = (link*)malloc(sizeof(link));//����ͷ��㣬����ռ�
	head->next = NULL;//��ʼ������
	Tail = head;//βָ��ָ��ͷ�ڵ�
	scanf("%d", &x);//��������
	while (x != -1) {
		L = (link*)malloc(sizeof(link));//Ϊ�½ڵ�����ռ�
		L->data = x;//��x��ֵ���½ڵ�������
		Tail->next = L;//β�ڵ����һ��ָ��ָ���½ڵ�
		Tail = L;//�滻�½ڵ�Ϊ����β�ڵ�
		scanf("%d", &x);
	}
	Tail->next = NULL;//β�ڵ����һ�ڵ�ָ���
	return head;
}

/*
	��λ����
	@peram i ��Ҫ���ҵ�ֵ����λֵ
	GetElem()
*/
link* GetElem(LinkList head, int i) {
	int j = 0;
	link* p=head;//ͷ�ڵ㸳ֵ��p
	while (j < i && p->next != NULL) {
		p = p->next;
		j++;
	}
	if (j == i) {
		return p;
	}
	else
	{
		printf("����λ�ó�������������\n");
		return NULL;
	}
}

/*
	��������
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
	printf("ͷ�巨��\n");
	PrintList(head);
	printf("��2��ֵ��%d\n", *GetElem(head, 2));
	head = TailInsert();
	printf("β�巨��\n");
	PrintList(head);
	printf("��2��ֵ��%d\n",*GetElem(head,2));
	return 0;
}