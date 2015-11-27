
// Address BookDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "LoginDlg.h"
#include "afxwin.h"




// CAddressBookDlg �Ի���
class CAddressBookDlg : public CDialog
{
// ����
public:
	
	CAddressBookDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ADDRESSBOOK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	Cusers rs_user;							//���û���󶨵Ķ���
	Cview_group rs_group;				//�ͷ�����ͼ�󶨵Ķ���
	Cview_member rs_member;		//�ͳ�Ա��ͼ�󶨵Ķ���
	Cmemberinfo rs_memberInfo;	//�ͳ�Ա��Ϣ�󶨵Ķ���
	Crelations rs_relation;				//�͹�ϵ��󶨵Ķ���
	Cgroup rs_packetmode;			//�ͷ������ͱ�󶨵Ķ���
	CDatabase m_db;						
	DataStruct datastruct;				
	// ���ɵ���Ϣӳ�亯��
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
	BOOL PreTranslateMessage(MSG* pMsg);		// ���λس���ESC����
	afx_msg void OnModifyMember();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnDeleteMember();
	afx_msg void OnAddMember();

	afx_msg void OnDeleteGroup();
	afx_msg void OnAddGroup();
	
	
//�������ݿ���ر����ͺ���
public:
	int id_user;									//��ǰ�û�id
	void ConnectDataSource();			//��������Դ
	void InqTable_Users();					//��ѯ"users��"
	void InqTable_memberinfo();			//��ѯ"membership��"
	void InqTable_Relation();				//��ѯ"relations��"
	void InqView_Group();					//��ѯ"view_group��ͼ"
	void InqView_Member();				//��ѯ"member��ͼ"

//���ݴ洢��صı����ͺ���
public:
	LinkList_Users L;							//�û�����
	LinkList_Group L_Group;				//��������
	MemInfo member_information;	//������û���Ϣ

//���οؼ���صı����ͺ���
public:
	CTreeCtrl m_AddrbookTree;		//���οؼ����Ʊ���
	CImageList m_ImageList;			//ͼ������
	HICON hIcon[5];						//����ͼ��������
	HTREEITEM hRoot;					//���ڵ���
	HTREEITEM hPacket;					//��ʾ��һ������
	HTREEITEM hMember;				//��ʾ��һ��Ա���
	HTREEITEM hItem;					//��ǰѡ�нڵ���
	DWORD_PTR ParentId;				//��Ÿ��ڵ�id
	DWORD_PTR hId;						//��ŵ�ǰ�ڵ�id
	//��Ϊ����Ƶ������⣬��������������û��ķ���ͳ�Ա��I'm so sad;
	int max_group_id;						//���ķ���id
	int max_member_id;					//���ĳ�Աid

	void InitTreeCtrl();						//��ʼ�����οؼ���ͼ����Ϣ
	void LoadOtherNode();				//�������οؼ��ڵ�
	//���������οؼ�
	afx_msg void OnTvnSelchangedTreeAddressbook(NMHDR *pNMHDR, LRESULT *pResult);
	//�Ҽ�������οؼ�
	afx_msg void OnNMRClickTreeAddressbook(NMHDR *pNMHDR, LRESULT *pResult);

//�б���ͼ�ؼ���صı����ͺ���
public:
	CListCtrl m_list_info;						//�б���ͼ�ؼ�����
	int m_Row;									//����б���е���  
	int m_Col;										//����б���е���
	BOOL button_upd_is_down;			//���ڱ�ʾ�б���Ƿ�����޸�
	CEdit m_edit_temp;						//�����޸��б��
	void InitListCtrl();							//��ʼ���б���ͼ�ؼ�
	void ClearList();								//����б�
	void FillList();									//����б�
	//˫���б�Ԫ
	afx_msg void OnNMDblclkListInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEditTemp();
	

	CButton button_add_group;
	afx_msg void OnBnClickedButtonAddgroup();
	// ����packetmode��
	void InqTable_Packetmode();
};
