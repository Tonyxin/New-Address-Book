
// Address BookDlg.cpp : ʵ���ļ�
//


#include "stdafx.h"
#include "Address Book.h"
#include "Address BookDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnModifyMember();
	afx_msg void OnAddGroup();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()


// CAddressBookDlg �Ի���



CAddressBookDlg::CAddressBookDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddressBookDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAddressBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_AddressBook, m_AddrbookTree);
	DDX_Control(pDX, IDC_LIST_INFO, m_list_info);
	DDX_Control(pDX, IDC_BUTTON_ADD, button_add);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, button_update);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, button_cancel);
	DDX_Control(pDX, IDC_EDIT_TEMP, m_edit_temp);
	DDX_Control(pDX, IDC_EDIT_SELECTED, edit_name);
	DDX_Control(pDX, IDC_BUTTON_ADDGROUP, button_add_group);
}

BEGIN_MESSAGE_MAP(CAddressBookDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_AddressBook, &CAddressBookDlg::OnTvnSelchangedTreeAddressbook)
	ON_MESSAGE(WM_RECEV_USER, OnRecevUser)
	ON_EN_CHANGE(IDC_EDIT_SELECTED, &CAddressBookDlg::OnEnChangeEditSelected)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_AddressBook, &CAddressBookDlg::OnNMRClickTreeAddressbook)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_INFO, &CAddressBookDlg::OnNMDblclkListInfo)
	ON_EN_KILLFOCUS(IDC_EDIT_TEMP, &CAddressBookDlg::OnEnKillfocusEditTemp)
	ON_COMMAND(ID_MODIFY_MEMBER, &CAddressBookDlg::OnModifyMember)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CAddressBookDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CAddressBookDlg::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CAddressBookDlg::OnBnClickedButtonCancel)
	ON_COMMAND(ID_DELETE_MEMBER, &CAddressBookDlg::OnDeleteMember)
	ON_COMMAND(ID_ADD_MEMBER, &CAddressBookDlg::OnAddMember)
	ON_COMMAND(ID_DELETE_GROUP, &CAddressBookDlg::OnDeleteGroup)
	ON_COMMAND(ID_ADD_GROUP, &CAddressBookDlg::OnAddGroup)
	ON_BN_CLICKED(IDC_BUTTON_ADDGROUP, &CAddressBookDlg::OnBnClickedButtonAddgroup)
END_MESSAGE_MAP()


// CAddressBookDlg ��Ϣ�������

BOOL CAddressBookDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	//��������Դ
	ConnectDataSource();		
	
	//��ѯ�û�����Ϣ��������֤�˺�����
	InqTable_Users();				

	//������½�Ի���
	m_loginDlg.L_login = L;						//���ó�Ա���ʵķ�ʽ���û�����L�������½�Ի���
	if (m_loginDlg.DoModal() != IDOK)	//��������½�Ի���ʱִ��OnOk();		
	{														
		OnOK();										//�������ڵĶԻ���
	}
	//�����û�����
	datastruct.Destory_Users(L);          
	
	max_member_id = 0;
	max_group_id = 0;

	//��ѯ�û��ķ�����Ϣ
	InqView_Group();

	//��ѯÿ�������еĳ�Ա
	InqView_Member();

	//���οؼ���ʼ�������ؽڵ���Ϣ
	InitTreeCtrl();
	LoadOtherNode();					//���ؽڵ���Ϣ

	//��ѯ��Ա��Ϣ
	InqTable_memberinfo();

	//�б���ͼ�ؼ���ʼ��
	InitListCtrl();
	
	//����relations���˴���Ϊ�˶Գ�Ա����ɾ�������
	InqTable_Relation();

	//����packetmode���˴���Ϊ�˶Է���������
	InqTable_Packetmode();

	//���������޸��б���EDIT�ؼ�
	m_edit_temp.ShowWindow(SW_HIDE);
	button_upd_is_down = 0;						//�б���ֹ�޸�
	edit_name.EnableWindow(FALSE);

	//�����޸Ŀؼ�
	button_add.ShowWindow(SW_HIDE);
	button_update.ShowWindow(SW_HIDE);
	button_cancel.ShowWindow(SW_HIDE);
	button_add_group.ShowWindow(SW_HIDE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CAddressBookDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAddressBookDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAddressBookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//----------------------------------------------------------------------------
//-----------------------��ʼ������------------------------------------------
//----------------------------------------------------------------------------
//��������Դ
void CAddressBookDlg::ConnectDataSource()
{
	//��������Դ
	TRY
	{
	m_db.OpenEx(_T("DSN=DataSourceOfAddr;"), CDatabase::noOdbcDialog);	//���ӵ�һ����ΪDataSourceOfAddr������Դ
	rs_user.m_pDatabase = &m_db;
	rs_group.m_pDatabase = &m_db;
	rs_member.m_pDatabase = &m_db;
	rs_memberInfo.m_pDatabase = &m_db;
	rs_relation.m_pDatabase = &m_db;
	rs_packetmode.m_pDatabase = &m_db;
	}

	//��ʾ�����Ƿ�ɹ�
	if (!m_db.IsOpen())		AfxMessageBox(_T("��������Դʧ��"));

	//�����쳣��Ϣ
	CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CMemoryException, pex)
	{
		pex->ReportError();
		AfxMessageBox(_T("memory exception"));
	}
	AND_CATCH(CException, ex)
	{
		TCHAR szError[100];
		ex->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
	END_CATCH;
}

//��ѯ�û���Ϣ
void CAddressBookDlg::InqTable_Users()
{
	CString sql = _T("SELECT * FROM users");		//sql���Ҫִ�е�SQL���
	L = datastruct.CreatList_Users();
	LinkList_Users L_temp = L;
	TRY
	{
		rs_user.Open(CRecordset::none, sql);			//�򿪲�ѯ��¼
		rs_user.MoveFirst();											//������һ����¼
		while (!rs_user.IsEOF())										//δ�������һ����¼����ִ��
		{
			ElemType_Users data_user;
			data_user.user_name = rs_user.m_u_name;					//��Ϊ�Ѿ�����Cusers�󶨵���users��
			data_user.user_password = rs_user.m_u_password;		//��ʵʱ����
			data_user.user_id = rs_user.m_u_id;
			datastruct.InsertList_Users(L, data_user);						//�����û�����
			rs_user.MoveNext();														//������һ����¼
		}
	}
	CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CMemoryException, pex)
	{
		pex->ReportError();
		AfxMessageBox(_T("memory exception"));
	}
	END_CATCH;
}

//�Ե�½�Ի������Ϣ��Ӧ�������洢��ǰ�û�id
LRESULT CAddressBookDlg::OnRecevUser(WPARAM wParam, LPARAM lParam)
{
	id_user = *((int*)lParam);			//���浱ǰ�û�id
	return TRUE;
}

//��ѯ������ͼ��Ϣ
void CAddressBookDlg::InqView_Group()
{
	CString sql = _T("SELECT * FROM view_group");		//sql���Ҫִ�е�SQL���
	L_Group = datastruct.CreatList_Group();
	LinkList_Group L_temp = L_Group;
	TRY
	{
		rs_group.Open(CRecordset::none, sql);			//�򿪲�ѯ��¼
		rs_group.MoveFirst();											//������һ����¼
		while (!rs_group.IsEOF())										//δ�������һ����¼����ִ��
		{
			if (rs_group.m_u_id == id_user)							//ֻΪ��ǰ�û���������
			{
				ElemType_Group data_group;
				data_group.group_id = rs_group.m_p_id;
				data_group.group_name = rs_group.m_p_mode;
				data_group.user_id = rs_group.m_u_id;
				datastruct.InsertList_Group(L_Group, data_group);		//�����������
			}
			rs_group.MoveNext();														//������һ����¼
		}
	}
	CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CMemoryException, pex)
	{
		pex->ReportError();
		AfxMessageBox(_T("memory exception"));
	}
	END_CATCH;
}

//��ѯ�������г�Ա��ֻ�г�Ա�����ƣ���ϸ��Ϣ�ڱ�ĺ����У�
void CAddressBookDlg::InqView_Member()
{
	CString sql = _T("SELECT * FROM member");		//sql���Ҫִ�е�SQL���
	TRY
	{
		rs_member.Open(CRecordset::none, sql);			//�򿪲�ѯ��¼
		rs_member.MoveFirst();												//������һ����¼
		while (!rs_member.IsEOF())										//δ�������һ����¼����ִ��
		{
			//���浱ǰ���ĳ�Աid������֮����ӳ�Ա
			if (rs_member.m_u_id == id_user)							//���ڵ�ǰ�û�
			{
				LinkList_Group L_temp = L_Group;
				while (L_temp->next)
				{
					L_temp = L_temp->next;
					if (L_temp->data.group_id == rs_member.m_p_id)	//���ڵ�ǰ����
					{
						ElemType_Member data_member;
						data_member.group_id = rs_member.m_p_id;
						data_member.member_id = rs_member.m_m_id;
						data_member.member_name = rs_member.m_m_name;
						datastruct.InsertList_Member(L_temp->data.member_list, data_member);
						break;
					}//if
				}//while
			}//if
			rs_member.MoveNext();
		}//while
	}//TRY

	CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CMemoryException, pex)
	{
		pex->ReportError();
		AfxMessageBox(_T("memory exception"));
	}
	END_CATCH;
}

//����ÿ����Ա����Ϣ
void CAddressBookDlg::InqTable_memberinfo()
{

	CString sql = _T("select * from membership");		//sql���Ҫִ�е�SQL���
	TRY
	{
		rs_memberInfo.Open(CRecordset::none, sql);			//�򿪲�ѯ��¼
	}
	LinkList_Group L_Group_temp = L_Group;
	while (L_Group_temp->next)
	{
		L_Group_temp = L_Group_temp->next;
		LinkList_Member L_Member_temp = L_Group_temp->data.member_list;
		while (L_Member_temp->next)
		{
			L_Member_temp = L_Member_temp->next;
			TRY
			{
				rs_memberInfo.MoveFirst();											//������һ����¼
				while (!rs_memberInfo.IsEOF())										//δ�������һ����¼����ִ��
				{
					if (L_Member_temp->data.member_id == rs_memberInfo.m_m_id)
					{
						L_Member_temp->data.member_info.member_sex = rs_memberInfo.m_m_sex;
						L_Member_temp->data.member_info.member_birthday = rs_memberInfo.m_m_birthday;
						L_Member_temp->data.member_info.member_Email = rs_memberInfo.m_m_email;
						L_Member_temp->data.member_info.member_phone = rs_memberInfo.m_m_phone;
						L_Member_temp->data.member_info.member_teleph = rs_memberInfo.m_m_teleph;
						L_Member_temp->data.member_info.member_QQ = rs_memberInfo.m_m_qq;
						break;
					}
					else    rs_memberInfo.MoveNext();
				}
			}
			CATCH(CDBException, ex)
			{
				AfxMessageBox(ex->m_strError);
				AfxMessageBox(ex->m_strStateNativeOrigin);
			}
			AND_CATCH(CMemoryException, pex)
			{
				pex->ReportError();
				AfxMessageBox(_T("memory exception"));
			}
			END_CATCH;
		}
	}
	CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CMemoryException, pex)
	{
		pex->ReportError();
		AfxMessageBox(_T("memory exception"));
	}
	END_CATCH;
}

//����relations��
void CAddressBookDlg::InqTable_Relation()
{
	CString sql = _T("select * from relations");
	TRY
	{
		rs_relation.Open(CRecordset::none, sql);			//�򿪲�ѯ��¼
	}
	CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CMemoryException, pex)
	{
		pex->ReportError();
		AfxMessageBox(_T("memory exception"));
	}
	END_CATCH;
}

// ����packetmode��
void CAddressBookDlg::InqTable_Packetmode()
{
	CString sql = _T("select * from packetmode");
	TRY
	{
		rs_packetmode.Open(CRecordset::none, sql);			//�򿪲�ѯ��¼
	}
	CATCH(CDBException, ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CMemoryException, pex)
	{
		pex->ReportError();
		AfxMessageBox(_T("memory exception"));
	}
	END_CATCH;
}

//���οؼ���ʼ��
void CAddressBookDlg::InitTreeCtrl()
{
	//����ͼ�꣬�����ǵľ�����浽����
	hIcon[0] = theApp.LoadIcon(IDI_ICON_addrbook);
	hIcon[1] = theApp.LoadIcon(IDI_ICON_family);
	hIcon[2] = theApp.LoadIcon(IDI_ICON_classmate);
	hIcon[3] = theApp.LoadIcon(IDI_ICON_friend);
	hIcon[4] = theApp.LoadIcon(IDI_ICON_people);

	//����ͼ������CImageList����
	m_ImageList.Create(32, 32, ILC_COLOR32, 5, 5);
	//��ͼ����ӵ�����
	for (int i = 0; i < 5; i++)		m_ImageList.Add(hIcon[i]);

	//Ϊ���οؼ�����ͼ������
	m_AddrbookTree.SetImageList(&m_ImageList, TVSIL_NORMAL);

}

// ���ظ��ڵ�֮��Ľڵ���Ϣ�����οؼ�
void CAddressBookDlg::LoadOtherNode()
{
	//�������Ա��Ϣ��ʾ�����οؼ���
	//������ڵ�
	hRoot = m_AddrbookTree.InsertItem(_T("ͨѶ¼"), 0, 0);
	m_AddrbookTree.SetItemData(hRoot, 0);			//���ø��ڵ�ĸ�������Ϊ0
	LinkList_Group L_Group_temp = L_Group;
	//���ڵ��²������ڵ�
	while (L_Group_temp->next)
	{
		L_Group_temp = L_Group_temp->next;
		CString group_name = L_Group_temp->data.group_name;
		int group_id = L_Group_temp->data.group_id;
		if (group_id<4)		hPacket = m_AddrbookTree.InsertItem(group_name, group_id, group_id, hRoot, TVI_LAST);
		else    hPacket = m_AddrbookTree.InsertItem(group_name, 2, 2, hRoot, TVI_LAST);
		m_AddrbookTree.SetItemData(hPacket, group_id);		//����ڵ�ĸ�������Ϊ������
		//����ڵ��²�����ڵ�
		LinkList_Member L_Member_temp = L_Group_temp->data.member_list;
		while (L_Member_temp->next)
		{
			L_Member_temp = L_Member_temp->next;
			CString member_name = L_Member_temp->data.member_name;
			hMember = m_AddrbookTree.InsertItem(member_name, 4, 4, hPacket, TVI_LAST);
			m_AddrbookTree.SetItemData(hMember, L_Member_temp->data.member_id);
			//��Ա�ڵ�ĸ�������Ϊ��Ա���
		}
	}
}



//---------------------------------------------------------------------------------
//---------------���οؼ������������ʾ�ڵ���Ϣ---------------------------------
//---------------------------------------------------------------------------------
//�����οؼ�����������ʾ��Ա��Ϣ
void CAddressBookDlg::OnTvnSelchangedTreeAddressbook(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CString strText;				//������ڵ�ı�ǩ�ı��ַ���

	ClearList();		//��ձ�

	//��ȡ���ڵ�������������
	HTREEITEM hItem_root = m_AddrbookTree.GetRootItem();
	DWORD_PTR RootId = m_AddrbookTree.GetItemData(hItem_root);

	//��ȡ��ǰѡ�еľ������������
	hItem = m_AddrbookTree.GetSelectedItem();
	hId = m_AddrbookTree.GetItemData(hItem);

	//��ȡѡ�нڵ�ı�ǩ�ַ���
	strText = m_AddrbookTree.GetItemText(hItem);
	//���ַ�����ʾ���༭����
	SetDlgItemText(IDC_EDIT_SELECTED, strText);

	if (hId != RootId)
	{
		//��ȡ���ڵ�������������
		HTREEITEM hItem_parent = m_AddrbookTree.GetParentItem(hItem);
		ParentId = m_AddrbookTree.GetItemData(hItem_parent);

		//����Ľڵ�Ϊ��Ա����ʾ��Ա��Ϣ
		if (ParentId != RootId)
		{
			DWORD_PTR GroupId = ParentId;	//��ȡ������
			DWORD_PTR MemberId = hId;			//��ȡ��Ա���
			//��������Ѱ�ҵ�ǰ���еĳ�Ա�ڵ���Ϣ��������member_information��
			LinkList_Group L_Group_temp = L_Group;
			while (L_Group_temp->next)
			{
				L_Group_temp = L_Group_temp->next;
				if (L_Group_temp->data.group_id == GroupId)
				{
					LinkList_Member L_Member_temp = L_Group_temp->data.member_list;
					while (L_Member_temp->next)
					{
						L_Member_temp = L_Member_temp->next;
						if (L_Member_temp->data.member_id == MemberId)
						{
							member_information = L_Member_temp->data.member_info;
							break;
						}
					}//while
					break;
				}//if
			}//while
			//�˴���ӽڵ���Ϣ����ʾ����
			FillList();		//��ѡ�г�Ա��Ϣ��ʾ������
		}//if
	}
}


void CAddressBookDlg::OnEnChangeEditSelected()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

// ���λس���ESC����
BOOL CAddressBookDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}


//--------------------------------------------------------------------
//------------------���б���ͼ�ؼ��Ĳ���----------------------------
//--------------------------------------------------------------------
//��ʼ���б���ͼ�ؼ�
void CAddressBookDlg::InitListCtrl()
{
	CRect rect;

	//��ȡ�б���ͼ�ؼ���λ�úʹ�С
	m_list_info.GetClientRect(&rect);

	//Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����
	m_list_info.SetExtendedStyle(m_list_info.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//Ϊ�б���ͼ�ؼ��������
	m_list_info.InsertColumn(0, _T("��Ա��Ϣ"), LVCFMT_CENTER, rect.Width() / 2, 0);
	m_list_info.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width() / 2, 1);

	//�����Ӧ����
	m_list_info.InsertItem(0, _T("�Ա�"));
	m_list_info.InsertItem(1, _T("��������"));
	m_list_info.InsertItem(2, _T("����"));
	m_list_info.InsertItem(3, _T("�绰"));
	m_list_info.InsertItem(4, _T("�ֻ�"));
	m_list_info.InsertItem(5, _T("QQ"));
}

//����б�
void CAddressBookDlg::ClearList()
{
	m_list_info.SetItemText(0, 1, _T(""));
	m_list_info.SetItemText(1, 1, _T(""));
	m_list_info.SetItemText(2, 1, _T(""));
	m_list_info.SetItemText(3, 1, _T(""));
	m_list_info.SetItemText(4, 1, _T(""));
	m_list_info.SetItemText(5, 1, _T(""));
}

//����ǰmember_information��Ϣ����䵽�б�
void CAddressBookDlg::FillList()
{
	m_list_info.SetItemText(0, 1, member_information.member_sex);
	m_list_info.SetItemText(1, 1, member_information.member_birthday);
	m_list_info.SetItemText(2, 1, member_information.member_Email);
	m_list_info.SetItemText(3, 1, member_information.member_phone);
	m_list_info.SetItemText(4, 1, member_information.member_teleph);
	m_list_info.SetItemText(5, 1, member_information.member_QQ);
}

//OnNMDblclkListInfo()��OnEnKillfocusEditTemp()��������޸��б�����ʾ�ı�
void CAddressBookDlg::OnNMDblclkListInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (button_upd_is_down)
	{
		NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
		CRect rc;
		m_Row = pNMListView->iItem;//���ѡ�е���  
		m_Col = pNMListView->iSubItem;//���ѡ����  

		if (pNMListView->iSubItem != 0) //���ѡ���������;  
		{
			m_list_info.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);//��������RECT��  
			m_edit_temp.SetParent(&m_list_info);//ת������Ϊ�б���е�����  
			m_edit_temp.MoveWindow(rc);//�ƶ�Edit��RECT���ڵ�λ��;  
			m_edit_temp.SetWindowText(m_list_info.GetItemText(m_Row, m_Col));//���������е�ֵ����Edit�ؼ��У�  
			m_edit_temp.ShowWindow(SW_SHOW);//��ʾEdit�ؼ���  
			m_edit_temp.SetFocus();//����Edit����  
			m_edit_temp.ShowCaret();//��ʾ���  
			m_edit_temp.SetSel(-1);//������ƶ������  
		}
	}
	*pResult = 0;
}
//�༭��ʧȥ����ʱ����Ϣ�����������ڽ��༭���е�ֵ���뵽�б���
void CAddressBookDlg::OnEnKillfocusEditTemp()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (button_upd_is_down)
	{
		CString tem;
		m_edit_temp.GetWindowText(tem);					//�õ��û�������µ�����  
		m_list_info.SetItemText(m_Row, m_Col, tem);   //���ñ༭���������  
		m_edit_temp.ShowWindow(SW_HIDE);             //Ӧ�ر༭��
	}
}


//------------------------------------------------------------------------
//---------------------�����ݿ������ɾ�Ĳ���---------------------------
//------------------------------------------------------------------------
//���οؼ����Ҽ����������沢��ʾ�˵�ǰ�����Ϣ
void CAddressBookDlg::OnNMRClickTreeAddressbook(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	//��ȡ��Ļλ��
	CPoint ScreenPt;
	GetCursorPos(&ScreenPt);
	CPoint pt(ScreenPt);

	//	�����Ļ���굽�ͻ��������ת��
	m_AddrbookTree.ScreenToClient(&ScreenPt);

	hItem = m_AddrbookTree.HitTest(ScreenPt);
	if (hItem)
	{
		//��ȡѡ�нڵ�ı�ǩ�ַ���
		CString strText = m_AddrbookTree.GetItemText(hItem);
		//���ַ�����ʾ���༭����
		SetDlgItemText(IDC_EDIT_SELECTED, strText);

		//��ȡ���ڵ�������������
		HTREEITEM hItem_root = m_AddrbookTree.GetRootItem();
		DWORD_PTR RootId = m_AddrbookTree.GetItemData(hItem_root);

		hId = m_AddrbookTree.GetItemData(hItem);
		CMenu menu;			//�˵�����

		//���нڵ�Ϊ���ڵ�
		if (hId == RootId)
		{
			menu.LoadMenuW(IDR_MENU3);
			datastruct.ClearMemberInfo(member_information);
			FillList();
		}
		else
		{
			//��ȡ���ڵ�������������
			HTREEITEM hItem_parent = m_AddrbookTree.GetParentItem(hItem);
			ParentId = m_AddrbookTree.GetItemData(hItem_parent);
			//���нڵ�Ϊ����ڵ�
			if (ParentId == RootId)
			{
				datastruct.ClearMemberInfo(member_information);
				menu.LoadMenuW(IDR_MENU2);
			}	
			//���нڵ�Ϊ��Ա�ڵ�
			else
			{
				//���浱ǰ��ڵ���Ϣ
				LinkList_Group L_Group_temp = L_Group;
				while (L_Group_temp->next)
				{
					L_Group_temp = L_Group_temp->next;
					if (L_Group_temp->data.group_id == ParentId)					//��ʱParentIdΪ��Ӧ����ڵ�id
					{
						LinkList_Member L_Member_temp = L_Group_temp->data.member_list;
						while (L_Member_temp->next)
						{
							L_Member_temp = L_Member_temp->next;
							if (hId == L_Member_temp->data.member_id)				//��ʱhIdΪ��Ӧ��Ա�ڵ�id
							{
								member_information = L_Member_temp->data.member_info;
								break;
							}
						}//while
						break;
					}
				}//while
				menu.LoadMenuW(IDR_MENU1);
			}//else
			FillList();
		}
		
		CMenu* pPopup = menu.GetSubMenu(0);//װ�ص�һ���Ӳ˵��������ǲ˵��ĵ�һ��
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, pt.x, pt.y, this);	//�����˵�
		menu.DestroyMenu();
		*pResult = 0;
	}
}

//��Ա�ڵ������"�޸�"�˵�
void CAddressBookDlg::OnModifyMember()
{
	// TODO:  �ڴ���������������
	m_AddrbookTree.EnableWindow(FALSE);					//���οؼ�����
	button_update.ShowWindow(SW_SHOW);						//�޸İ�ťʹ��
	button_cancel.ShowWindow(SW_SHOW);							//ȡ����ťʹ��
	button_upd_is_down = 1;											//�༭�б��ʹ��
}

//��Ա�ڵ��µ��"ɾ��"�˵���ʵ����ֻ�ǽ���˳�Ա���û��Ĺ�ϵ
void CAddressBookDlg::OnDeleteMember()
{
	// TODO:  �ڴ���������������
	//����ͬ�����洢��������
	LinkList_Group L_Group_temp = L_Group;
	while (L_Group_temp->next)
	{
		L_Group_temp = L_Group_temp->next;
		if (L_Group_temp->data.group_id == ParentId)					//��ʱParentIdΪ��Ӧ����ڵ�id
		{
			LinkList_Member L_Member_temp = L_Group_temp->data.member_list;
			if (!datastruct.DeleteList_Member(L_Member_temp, hId))	AfxMessageBox(_T("ɾ����Աʧ��"));
			break;
		}//if
	}//while

	//����ͬ�������ݿ���
	rs_relation.MoveFirst();
	while (!rs_relation.IsEOF())										//δ�������һ����¼����ִ��
	{
		if ((hId == rs_relation.m_m_id) && (id_user == rs_relation.m_u_id))
		{
			rs_relation.Delete();
			break;
		}
		rs_relation.MoveNext();
	}

	//���༭���ÿ�
	SetDlgItemText(IDC_EDIT_SELECTED, _T(""));
	//����б�
	ClearList();
	//ɾ����ǰ�ڵ�
	m_AddrbookTree.DeleteItem(hItem);
}

//����ڵ���"��ӳ�Ա"�˵�
void CAddressBookDlg::OnAddMember()
{
	// TODO:  �ڴ���������������
	m_AddrbookTree.EnableWindow(FALSE);					//���οؼ�����
	button_add.ShowWindow(SW_SHOW);						//��Ӱ�ťʹ��
	button_cancel.ShowWindow(SW_SHOW);					//ȡ����ťʹ��
	button_upd_is_down = 1;											//�༭�б��ʹ��
	edit_name.EnableWindow(TRUE);								//�༭��ʹ��
	FillList();
	SetDlgItemText(IDC_EDIT_SELECTED, _T(""));				//��༭��Ϊ��
	//��ť��ʾ��ָ��λ��
	CRect rect;
	button_update.GetWindowRect(&rect);
	ScreenToClient(&rect);
	button_add.MoveWindow(rect);
}

//����ڵ���"ɾ������"�˵���ֱ��ɾ��relations���������
void CAddressBookDlg::OnDeleteGroup()
{
	// TODO:  �ڴ���������������
	//����ͬ�����洢��������
	LinkList_Group L_Group_temp = L_Group;
	while (L_Group_temp->next)
	{
		L_Group_temp = L_Group_temp->next;
		if (L_Group_temp->data.group_id == hId)							//��ʱhIdΪ��Ӧ����ڵ�id
		{
			datastruct.DeleteList_Group(L_Group_temp, hId);
			break;
		}
	}

	//����ͬ�������ݿ���
	rs_relation.MoveFirst();
	while (!rs_relation.IsEOF())										//δ�������һ����¼����ִ��
	{
		if ((hId == rs_relation.m_p_id) && (id_user == rs_relation.m_u_id))
		{
			rs_relation.Delete();
		}
		rs_relation.MoveNext();
	}

	//���༭���ÿ�
	SetDlgItemText(IDC_EDIT_SELECTED, _T(""));
	//����б�
	ClearList();
	//ɾ����ǰ�ڵ�
	m_AddrbookTree.DeleteItem(hItem);
}

//ͨѶ¼���ڵ��µ��"��ӷ���"
void CAddressBookDlg::OnAddGroup()
{
	// TODO:  �ڴ���������������
	m_AddrbookTree.EnableWindow(FALSE);					//���οؼ�����
	button_add_group.ShowWindow(SW_SHOW);			//��Ӱ�ťʹ��
	button_cancel.ShowWindow(SW_SHOW);					//ȡ����ťʹ��
	edit_name.EnableWindow(TRUE);								//�༭��ʹ��
	SetDlgItemText(IDC_EDIT_SELECTED, _T(""));				//��༭��Ϊ��
	
	//��ť��ʾ��ָ��λ��
	CRect rect;
	button_update.GetWindowRect(&rect);
	ScreenToClient(&rect);												
	button_add_group.MoveWindow(rect);

}

//�����"ȷ����ӳ�Ա"��ť
void CAddressBookDlg::OnBnClickedButtonAdd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	button_add.ShowWindow(SW_HIDE);							//��Ӱ�ť����
	button_cancel.ShowWindow(SW_HIDE);						//ȡ����ť����
	m_AddrbookTree.EnableWindow(TRUE);						//���οؼ�ʹ��
	button_upd_is_down = 0;												//�༭�б�����
	
	CString m_name;		//�¼����Ա����
	GetDlgItemText(IDC_EDIT_SELECTED, m_name);			//�༭������д��Ա��
	if (!m_name)
	{
		AfxMessageBox(_T("��������Ϊ�գ�"));
		edit_name.SetFocus();				//����Edit����  
		edit_name.ShowCaret();			//��ʾ���  
		edit_name.SetSel(-1);				//������ƶ������  
		FillList();									//����б�
	}
	else
	{
		edit_name.EnableWindow(FALSE);				//�༭�����
		member_information.member_sex = m_list_info.GetItemText(0, 1);
		member_information.member_birthday = m_list_info.GetItemText(1, 1);
		member_information.member_Email = m_list_info.GetItemText(2, 1);
		member_information.member_phone = m_list_info.GetItemText(3, 1);
		member_information.member_teleph = m_list_info.GetItemText(4, 1);
		member_information.member_QQ = m_list_info.GetItemText(5, 1);


		//�����ĺ�Ľ�����浽���ݿ�
		//����membership��
		rs_memberInfo.AddNew();
		rs_memberInfo.m_m_birthday = member_information.member_birthday;
		rs_memberInfo.m_m_email = member_information.member_Email;
		rs_memberInfo.m_m_name = m_name;
		rs_memberInfo.m_m_phone = member_information.member_phone;
		rs_memberInfo.m_m_qq = member_information.member_QQ;
		rs_memberInfo.m_m_sex = member_information.member_sex;
		rs_memberInfo.m_m_teleph = member_information.member_teleph;
		rs_memberInfo.Update();
		rs_memberInfo.Requery();
		
		//������Ϊmembership��m_id��������˲����Ҫ����m_idֵ
		rs_memberInfo.MoveLast();
		max_member_id = rs_memberInfo.m_m_id;
		
		//�����ĺ������ͬ�����洢��������
		LinkList_Group L_Group_temp = L_Group;
		while (L_Group_temp->next)
		{
			L_Group_temp = L_Group_temp->next;
			if (L_Group_temp->data.group_id == hId)					//��ʱhIdΪ��ǰ����id
			{
				ElemType_Member NewMember;
				NewMember.group_id = hId;
				NewMember.member_id = max_member_id;
				NewMember.member_name = m_name;
				NewMember.member_info = member_information;
				datastruct.InsertList_Member(L_Group_temp->data.member_list, NewMember);
				break;
			}
		}//while

		//��������浽���ݿ���
		//����"relations"��
		rs_relation.AddNew();
		rs_relation.m_u_id = id_user;
		rs_relation.m_p_id = hId;
		rs_relation.m_m_id = max_member_id;
		rs_relation.Update();
		rs_relation.Requery();

		//�����οؼ��м����½ڵ�
		hMember = m_AddrbookTree.InsertItem(m_name, 4, 4, hItem, TVI_LAST);
		m_AddrbookTree.SetItemData(hMember, max_member_id);
	}//else
}

//�����"ȷ���޸�"��ť
void CAddressBookDlg::OnBnClickedButtonUpdate()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	button_update.ShowWindow(SW_HIDE);						//�޸İ�ť����
	button_cancel.ShowWindow(SW_HIDE);						//ȡ����ť����
	m_AddrbookTree.EnableWindow(TRUE);						//���οռ�ʹ��
	button_upd_is_down = 0;												//�༭�б�����

	member_information.member_sex = m_list_info.GetItemText(0, 1);
	member_information.member_birthday = m_list_info.GetItemText(1, 1);
	member_information.member_Email = m_list_info.GetItemText(2, 1);
	member_information.member_phone = m_list_info.GetItemText(3, 1);
	member_information.member_teleph = m_list_info.GetItemText(4, 1);
	member_information.member_QQ = m_list_info.GetItemText(5, 1);

	//�����ĺ������ͬ�����洢��������
	LinkList_Group L_Group_temp = L_Group;
	while (L_Group_temp->next)
	{
		L_Group_temp = L_Group_temp->next;
		if (L_Group_temp->data.group_id == ParentId)					//��ʱParentIdΪ��Ӧ����ڵ�id
		{
			LinkList_Member L_Member_temp = L_Group_temp->data.member_list;
			while (L_Member_temp->next)
			{
				L_Member_temp = L_Member_temp->next;
				if (hId == L_Member_temp->data.member_id)				//��ʱhIdΪ��Ӧ��Ա�ڵ�id
				{
					L_Member_temp->data.member_info = member_information;
					break;
				}
			}//while
			break;
		}//if
	}//while

	//�����ĺ������ͬ�������ݿ�
	rs_memberInfo.MoveFirst();											//��������һ����¼
	while (!rs_memberInfo.IsEOF())										//δ�������һ����¼����ִ��
	{
		if (hId == rs_memberInfo.m_m_id)
		{
			rs_memberInfo.Edit();
			rs_memberInfo.m_m_sex = member_information.member_sex;
			rs_memberInfo.m_m_birthday = member_information.member_birthday;
			rs_memberInfo.m_m_email = member_information.member_Email;
			rs_memberInfo.m_m_phone = member_information.member_phone;
			rs_memberInfo.m_m_teleph = member_information.member_teleph;
			rs_memberInfo.m_m_qq = member_information.member_QQ;
			rs_memberInfo.Update();
			rs_memberInfo.Requery();
			break;
		}
		else    rs_memberInfo.MoveNext();
	}
}

//���"ȷ����ӷ���"��ť
void CAddressBookDlg::OnBnClickedButtonAddgroup()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	button_add_group.ShowWindow(SW_HIDE);					//��Ӱ�ť����
	button_cancel.ShowWindow(SW_HIDE);						//ȡ����ť����
	m_AddrbookTree.EnableWindow(TRUE);						//���οؼ�ʹ��

	CString m_name;		//�¼����Ա����
	GetDlgItemText(IDC_EDIT_SELECTED, m_name);			//�༭������д��Ա��
	if (!m_name)
	{
		AfxMessageBox(_T("�������Ʋ���Ϊ�գ�"));
		edit_name.SetFocus();				//����Edit����  
		edit_name.ShowCaret();			//��ʾ���  
		edit_name.SetSel(-1);				//������ƶ������  
		FillList();									//����б�
	}
	else
	{
		//�����ݱ��浽���ݿ�
		//���浽packetmode��
		rs_packetmode.AddNew();
		rs_packetmode.m_p_mode = m_name;
		rs_packetmode.Update();
		rs_packetmode.Requery();

		rs_packetmode.MoveLast();
		max_group_id = rs_packetmode.m_p_id;

		//���浽relation��
		rs_relation.AddNew();
		rs_relation.m_u_id = id_user;
		rs_relation.m_p_id = max_group_id;
		rs_relation.Update();
		rs_relation.Requery();

		//���浽�洢��������
		ElemType_Group data_group;
		data_group.group_id = max_group_id;
		data_group.group_name = m_name;
		data_group.user_id = id_user;
		datastruct.InsertList_Group(L_Group, data_group);		//�����������

		hPacket = m_AddrbookTree.InsertItem(m_name, 2, 2, hItem, TVI_LAST);
		m_AddrbookTree.SetItemData(hPacket, max_group_id);
	}
}

//���"ȡ��"��ť
void CAddressBookDlg::OnBnClickedButtonCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�༭��ʹ�ܣ�������ʾԭ���ݣ������༭�����
	if (edit_name.IsWindowEnabled())
	{
		CString strText = m_AddrbookTree.GetItemText(hItem);
		SetDlgItemText(IDC_EDIT_SELECTED, strText);
		edit_name.EnableWindow(FALSE);
	}
	button_update.ShowWindow(SW_HIDE);						//�޸İ�ť����
	button_cancel.ShowWindow(SW_HIDE);						//ȡ����ť����
	button_add_group.ShowWindow(SW_HIDE);					//��ӷ��鰴ť����
	button_add.ShowWindow(SW_HIDE);							//��ӳ�Ա��ť����
	m_AddrbookTree.EnableWindow(TRUE);						//���οռ�ʹ��
	button_upd_is_down = 0;												//�༭�б�����
	FillList();
}





