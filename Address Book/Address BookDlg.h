
// Address BookDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "LoginDlg.h"
#include "afxwin.h"




// CAddressBookDlg 对话框
class CAddressBookDlg : public CDialog
{
// 构造
public:
	
	CAddressBookDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ADDRESSBOOK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	Cusers rs_user;							//和用户表绑定的对象
	Cview_group rs_group;				//和分组视图绑定的对象
	Cview_member rs_member;		//和成员视图绑定的对象
	Cmemberinfo rs_memberInfo;	//和成员信息绑定的对象
	Crelations rs_relation;				//和关系表绑定的对象
	Cgroup rs_packetmode;			//和分组类型表绑定的对象
	CDatabase m_db;						
	DataStruct datastruct;				
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnRecevUser(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP();

public:
	CLoginDlg m_loginDlg;
	CEdit edit_name;
	CButton button_add;
	CButton button_update;
	CButton button_cancel;
	afx_msg void OnEnChangeEditSelected();
	BOOL PreTranslateMessage(MSG* pMsg);		// 屏蔽回车和ESC按键
	afx_msg void OnModifyMember();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnDeleteMember();
	afx_msg void OnAddMember();

	afx_msg void OnDeleteGroup();
	afx_msg void OnAddGroup();
	
	
//连接数据库相关变量和函数
public:
	int id_user;									//当前用户id
	void ConnectDataSource();			//连接数据源
	void InqTable_Users();					//查询"users表"
	void InqTable_memberinfo();			//查询"membership表"
	void InqTable_Relation();				//查询"relations表"
	void InqView_Group();					//查询"view_group视图"
	void InqView_Member();				//查询"member视图"

//数据存储相关的变脸和函数
public:
	LinkList_Users L;							//用户链表
	LinkList_Group L_Group;				//分组链表
	MemInfo member_information;	//所点击用户信息

//树形控件相关的变量和函数
public:
	CTreeCtrl m_AddrbookTree;		//树形控件控制变量
	CImageList m_ImageList;			//图标序列
	HICON hIcon[5];						//设置图标句柄数组
	HTREEITEM hRoot;					//根节点句柄
	HTREEITEM hPacket;					//表示任一分组句柄
	HTREEITEM hMember;				//表示任一成员句柄
	HTREEITEM hItem;					//当前选中节点句柄
	DWORD_PTR ParentId;				//存放父节点id
	DWORD_PTR hId;						//存放当前节点id
	//因为表设计的有问题，这里包含了所有用户的分组和成员，I'm so sad;
	int max_group_id;						//最大的分组id
	int max_member_id;					//最大的成员id

	void InitTreeCtrl();						//初始化树形控件的图标信息
	void LoadOtherNode();				//加载树形控件节点
	//左键点击树形控件
	afx_msg void OnTvnSelchangedTreeAddressbook(NMHDR *pNMHDR, LRESULT *pResult);
	//右键点击树形控件
	afx_msg void OnNMRClickTreeAddressbook(NMHDR *pNMHDR, LRESULT *pResult);

//列表视图控件相关的变脸和函数
public:
	CListCtrl m_list_info;						//列表视图控件变量
	int m_Row;									//存放列表框中的行  
	int m_Col;										//存放列表框中的列
	BOOL button_upd_is_down;			//用于表示列表框是否可以修改
	CEdit m_edit_temp;						//用于修改列表框
	void InitListCtrl();							//初始化列表视图控件
	void ClearList();								//清空列表
	void FillList();									//填充列表
	//双击列表单元
	afx_msg void OnNMDblclkListInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEditTemp();
	

	CButton button_add_group;
	afx_msg void OnBnClickedButtonAddgroup();
	// 加载packetmode表
	void InqTable_Packetmode();
};
