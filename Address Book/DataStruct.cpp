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
	p->data.user_id = data.user_id;
	p->next = L->next;									//���ڵ���뵽�ײ�
	L->next = p;
}


//�����û�����
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


//������������
LinkList_Group DataStruct::CreatList_Group()
{
	LinkList_Group L = new LNode_Group;
	L->next = NULL;
	return L;
}


//�����������ڵ�
void DataStruct::InsertList_Group(LinkList_Group L, ElemType_Group data)
{
	LinkList_Group p = new LNode_Group;
	p->data.group_id = data.group_id;
	p->data.group_name = data.group_name;
	p->data.user_id = data.user_id;
	p->data.member_list = new LNode_Member;
	p->data.member_list->next = NULL;
	//ÿ�������ڵĳ�Ա�����Ȳ���
	p->next = L->next;									//���ڵ���뵽�ײ�
	L->next = p;
}


//���ٷ�������ע����øú���ǰ��Ҫ������ÿ������ڵ��еĳ�Ա����
void DataStruct::Destory_Group(LinkList_Group L)
{
	while (L->next)										//�ͷ����ݽڵ�
	{
		LinkList_Group temp_free;
		temp_free = L->next->next;
		delete L->next;
		L->next = temp_free;
	}
	delete L;													//�ͷ�ͷ�ڵ�
}


//������Ա����
LinkList_Member DataStruct::CreatList_Member()
{
	LinkList_Member L = new LNode_Member;
	L->next = NULL;
	return L;
}


//��Ա�����в���ڵ�
void DataStruct::InsertList_Member(LinkList_Member L, ElemType_Member data)
{
	LinkList_Member p = new LNode_Member;
	p->data.group_id = data.group_id;
	p->data.member_id = data.member_id;
	p->data.member_name = data.member_name;
//	p->data.member_info = data.member_info;
	p->next = L->next;									//���ڵ���뵽�ײ�
	L->next = p;
}


//���ٳ�Ա����
void DataStruct::Destory_Member(LinkList_Member L)
{
	while (L->next)										//�ͷ����ݽڵ�
	{
		LinkList_Member temp_free;
		temp_free = L->next->next;
		delete L->next;
		L->next = temp_free;
	}
	delete L;													//�ͷ�ͷ�ڵ�
}
