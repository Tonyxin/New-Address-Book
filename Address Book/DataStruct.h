#pragma once

#ifndef DATASTRUCT_CLASS_DEF
#define DATASTRUCT_CLASS_DEF


//定义"成员表"成员结构体
typedef struct ElemType_Users
{
	//这里将结构体变量置为CString在赋值时会出现莫名的问题。。。
	CString user_name;
	CString user_password;
}ElemType_Users;

//链表存放"成员表"成员
typedef struct LNode_Users
{
	ElemType_Users data;
	struct LNode_Users * next;
}LNode_Users, *LinkList_Users;

class DataStruct
{
public:
	DataStruct();
	~DataStruct();

protected:

public:
	//创建用户链表
	LinkList_Users CreatList_Users();
	//用户链表插入节点
	void InsertList_Users(LinkList_Users L, ElemType_Users data);
	//销毁用户链表
	void Destory_Users(LinkList_Users L);
};

#endif
