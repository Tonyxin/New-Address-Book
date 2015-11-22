
// Address BookDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "LoginDlg.h"




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
	LinkList_Users L;							//用户链表
	LinkList_Group L_Group;				//分组链表
	int id_user;									//当前用户id
	CLoginDlg m_loginDlg;
	CTreeCtrl m_AddrbookTree;
	CImageList m_ImageList;
	afx_msg void OnTvnSelchangedTreeAddressbook(NMHDR *pNMHDR, LRESULT *pResult);
	void ConnectDataSource();
	void InqTable_Users();
	void InqView_Group();
	void InqView_Member();
	afx_msg void OnEnChangeEditSelected();
};
