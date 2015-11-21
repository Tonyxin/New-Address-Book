#include "stdafx.h"
#include "DataStruct.h"


DataStruct::DataStruct()
{
}


DataStruct::~DataStruct()
{
}

//创建用户链表
LinkList_Users DataStruct::CreatList_Users()
{
	LinkList_Users L = new LNode_Users;		//构造头节点，头节点中数据没有意义
	L->next=NULL;
	return L;
}


//插入用户节点
void DataStruct::InsertList_Users(LinkList_Users L, ElemType_Users data)
{
	LinkList_Users p = new LNode_Users;		//创建节点，记得用完了要删除
	p->data.user_name = data.user_name;
	p->data.user_password = data.user_password;
	p->data.user_id = data.user_id;
	p->next = L->next;									//将节点插入到首部
	L->next = p;
}


//销毁用户链表
void DataStruct::Destory_Users(LinkList_Users L)
{
	while (L->next)										//释放数据节点
	{
		LinkList_Users temp_free;
		temp_free = L->next->next;
		delete L->next;
		L->next = temp_free;
	}
	delete L;													//释放头节点
}


//创建分组链表
LinkList_Group DataStruct::CreatList_Group()
{
	LinkList_Group L = new LNode_Group;
	L->next = NULL;
	return L;
}


//分组链表插入节点
void DataStruct::InsertList_Group(LinkList_Group L, ElemType_Group data)
{
	LinkList_Group p = new LNode_Group;
	p->data.group_id = data.group_id;
	p->data.group_name = data.group_name;
	p->data.user_id = data.user_id;
	p->data.member_list = new LNode_Member;
	p->data.member_list->next = NULL;
	//每个分组内的成员链表先不管
	p->next = L->next;									//将节点插入到首部
	L->next = p;
}


//销毁分组链表，注意调用该函数前，要先销毁每个分组节点中的成员链表
void DataStruct::Destory_Group(LinkList_Group L)
{
	while (L->next)										//释放数据节点
	{
		LinkList_Group temp_free;
		temp_free = L->next->next;
		delete L->next;
		L->next = temp_free;
	}
	delete L;													//释放头节点
}


//创建成员链表
LinkList_Member DataStruct::CreatList_Member()
{
	LinkList_Member L = new LNode_Member;
	L->next = NULL;
	return L;
}


//成员链表中插入节点
void DataStruct::InsertList_Member(LinkList_Member L, ElemType_Member data)
{
	LinkList_Member p = new LNode_Member;
	p->data.group_id = data.group_id;
	p->data.member_id = data.member_id;
	p->data.member_name = data.member_name;
//	p->data.member_info = data.member_info;
	p->next = L->next;									//将节点插入到首部
	L->next = p;
}


//销毁成员链表
void DataStruct::Destory_Member(LinkList_Member L)
{
	while (L->next)										//释放数据节点
	{
		LinkList_Member temp_free;
		temp_free = L->next->next;
		delete L->next;
		L->next = temp_free;
	}
	delete L;													//释放头节点
}
