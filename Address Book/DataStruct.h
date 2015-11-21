#pragma once

#ifndef DATASTRUCT_CLASS_DEF
#define DATASTRUCT_CLASS_DEF


//����"��Ա��"��Ա�ṹ��
typedef struct ElemType_Users
{
	//���ｫ�ṹ�������ΪCString�ڸ�ֵʱ�����Ī�������⡣����
	CString user_name;
	CString user_password;
}ElemType_Users;

//������"��Ա��"��Ա
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
	//�����û�����
	LinkList_Users CreatList_Users();
	//�û��������ڵ�
	void InsertList_Users(LinkList_Users L, ElemType_Users data);
	//�����û�����
	void Destory_Users(LinkList_Users L);
};

#endif
