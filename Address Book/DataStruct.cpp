#include "stdafx.h"
#include "DataStruct.h"


DataStruct::DataStruct()
{
}


DataStruct::~DataStruct()
{
}

//�����û�����
LinkList_Users DataStruct::CreatList_Users()
{
	LinkList_Users L = new LNode_Users;		//����ͷ�ڵ㣬ͷ�ڵ�������û������
	L->next=NULL;
	return L;
}

//�����û��ڵ�
void DataStruct::InsertList_Users(LinkList_Users L, ElemType_Users data)
{
	LinkList_Users p = new LNode_Users;		//�����ڵ㣬�ǵ�������Ҫɾ��
	p->data.user_name = data.user_name;
	p->data.user_password = data.user_password;
	p->next = L->next;									//���ڵ���뵽�ײ�
	L->next = p;
}

//ɾ���û�����
void DataStruct::Destory_Users(LinkList_Users L)
{
	while (L->next)										//�ͷ����ݽڵ�
	{
		LinkList_Users temp_free;
		temp_free = L->next->next;
		delete L->next;
		L->next = temp_free;
	}
	delete L;													//�ͷ�ͷ�ڵ�
}
