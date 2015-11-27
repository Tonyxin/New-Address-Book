#pragma once

#ifndef DATASTRUCT_CLASS_DEF
#define DATASTRUCT_CLASS_DEF

//定义成员信息结构体
typedef struct MemInfo
{
	CString member_sex;				//性别
	CString member_birthday;		//出生日期
	CString member_Email;				//邮箱
	CString member_phone;			//电话
	CString member_teleph;			//手机
	CString member_QQ;				//QQ
}MemInfo;

//定义成员数据结构体
typedef struct ElemType_Member
{
	int group_id;								//分组编号
	int member_id;							//成员编号
	CString member_name;			//成员姓名
	MemInfo member_info;			//成员信息
}ElemType_Member;

//链表存放分组内的成员
typedef struct LNode_Member
{
	ElemType_Member data;			//成员节点的数据
	LNode_Member * next;				//指向下一个成员节点
}LNode_Member, *LinkList_Member;


//定义分组数据结构体
typedef struct ElemType_Group
{
	int user_id;									//用户编号
	int group_id;									//分组编号
	CString group_name;					//分组名称
	LinkList_Member member_list;		//该分组的用户链表
}ElemType_Group;

//链表存放分组
typedef struct LNode_Group
{
	ElemType_Group data;					//分组节点的数据
	LNode_Group * next;					//指向下一个分组节点
}LNode_Group, *LinkList_Group;


//定义"用户表"结构体
typedef struct ElemType_Users
{
	int user_id;							//用户编号
	CString user_name;				//用户账号
	CString user_password;			//用户密码
}ElemType_Users;


//链表存放"用户表"成员
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
	
	//创建分组链表
	LinkList_Group CreatList_Group();
	
	//分组链表中插入节点
	void InsertList_Group(LinkList_Group L, ElemType_Group data);
	
	//销毁分组链表，注意调用该函数前，要先销毁每个分组节点中的成员链表
	void Destory_Group(LinkList_Group L);
	
	//创建成员链表
	LinkList_Member CreatList_Member();
	
	//成员链表中插入节点
	void InsertList_Member(LinkList_Member L, ElemType_Member data);

	// 成员链表中删除节点
	BOOL DeleteList_Member(LinkList_Member L, int id);

	//销毁成员链表（先销毁成员链表，才能销毁分组链表）
	void Destory_Member(LinkList_Member L);
	
	// 手动清空成员信息
	void ClearMemberInfo(MemInfo& information);
	// 分组链表中删除节点
	void DeleteList_Group(LinkList_Group L, int id);
};

#endif
