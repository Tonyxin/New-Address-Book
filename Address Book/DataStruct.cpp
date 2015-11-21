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
	p->next = L->next;									//将节点插入到首部
	L->next = p;
}

//删除用户链表
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
