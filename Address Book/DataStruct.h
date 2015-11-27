#pragma once

#ifndef DATASTRUCT_CLASS_DEF
#define DATASTRUCT_CLASS_DEF

//�����Ա��Ϣ�ṹ��
typedef struct MemInfo
{
	CString member_sex;				//�Ա�
	CString member_birthday;		//��������
	CString member_Email;				//����
	CString member_phone;			//�绰
	CString member_teleph;			//�ֻ�
	CString member_QQ;				//QQ
}MemInfo;

//�����Ա���ݽṹ��
typedef struct ElemType_Member
{
	int group_id;								//������
	int member_id;							//��Ա���
	CString member_name;			//��Ա����
	MemInfo member_info;			//��Ա��Ϣ
}ElemType_Member;

//�����ŷ����ڵĳ�Ա
typedef struct LNode_Member
{
	ElemType_Member data;			//��Ա�ڵ������
	LNode_Member * next;				//ָ����һ����Ա�ڵ�
}LNode_Member, *LinkList_Member;


//����������ݽṹ��
typedef struct ElemType_Group
{
	int user_id;									//�û����
	int group_id;									//������
	CString group_name;					//��������
	LinkList_Member member_list;		//�÷�����û�����
}ElemType_Group;

//�����ŷ���
typedef struct LNode_Group
{
	ElemType_Group data;					//����ڵ������
	LNode_Group * next;					//ָ����һ������ڵ�
}LNode_Group, *LinkList_Group;


//����"�û���"�ṹ��
typedef struct ElemType_Users
{
	int user_id;							//�û����
	CString user_name;				//�û��˺�
	CString user_password;			//�û�����
}ElemType_Users;


//������"�û���"��Ա
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
	
	//������������
	LinkList_Group CreatList_Group();
	
	//���������в���ڵ�
	void InsertList_Group(LinkList_Group L, ElemType_Group data);
	
	//���ٷ�������ע����øú���ǰ��Ҫ������ÿ������ڵ��еĳ�Ա����
	void Destory_Group(LinkList_Group L);
	
	//������Ա����
	LinkList_Member CreatList_Member();
	
	//��Ա�����в���ڵ�
	void InsertList_Member(LinkList_Member L, ElemType_Member data);

	// ��Ա������ɾ���ڵ�
	BOOL DeleteList_Member(LinkList_Member L, int id);

	//���ٳ�Ա���������ٳ�Ա�����������ٷ�������
	void Destory_Member(LinkList_Member L);
	
	// �ֶ���ճ�Ա��Ϣ
	void ClearMemberInfo(MemInfo& information);
	// ����������ɾ���ڵ�
	void DeleteList_Group(LinkList_Group L, int id);
};

#endif
