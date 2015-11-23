
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
}

BEGIN_MESSAGE_MAP(CAddressBookDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_AddressBook, &CAddressBookDlg::OnTvnSelchangedTreeAddressbook)
	ON_MESSAGE(WM_RECEV_USER, OnRecevUser)
	ON_EN_CHANGE(IDC_EDIT_SELECTED, &CAddressBookDlg::OnEnChangeEditSelected)
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

	//��ѯ�û��ķ�����Ϣ
	InqView_Group();

	//��ѯÿ�������еĳ�Ա
	InqView_Member();

	//���οؼ���ʼ��
	InitTreeCtrl();

	//��ѯ��Ա��Ϣ
	InqTable_memberinfo();

	//�б���ͼ�ؼ���ʼ��
	InitListCtrl();
	
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
	HTREEITEM hItem = m_AddrbookTree.GetSelectedItem();
	DWORD_PTR hId = m_AddrbookTree.GetItemData(hItem);
	
	//��ȡѡ�нڵ�ı�ǩ�ַ���
	strText = m_AddrbookTree.GetItemText(hItem);
	//���ַ�����ʾ���༭����
	SetDlgItemText(IDC_EDIT_SELECTED, strText);
	
	if (hId != RootId)
	{
		//��ȡ���ڵ�������������
		HTREEITEM hItem_parent = m_AddrbookTree.GetParentItem(hItem);
		DWORD_PTR ParentId = m_AddrbookTree.GetItemData(hItem_parent);

		//����Ľڵ�Ϊ��Ա����ʾ��Ա��Ϣ
		if ((ParentId != RootId) && (hId != RootId))
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

//��ѯ�û�����Ϣ
void CAddressBookDlg::InqTable_Users()
{
	CString sql = _T("SELECT * FROM users");		//sql���Ҫִ�е�SQL���
	L = datastruct.CreatList_Users();
	LinkList_Users L_temp = L;
	TRY
	{
		rs_user.Open(CRecordset::snapshot, sql);			//�򿪲�ѯ��¼
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
		rs_group.Open(CRecordset::snapshot, sql);			//�򿪲�ѯ��¼
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
		rs_member.Open(CRecordset::snapshot, sql);			//�򿪲�ѯ��¼
		rs_member.MoveFirst();												//������һ����¼
		while (!rs_member.IsEOF())										//δ�������һ����¼����ִ��
		{
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


void CAddressBookDlg::OnEnChangeEditSelected()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


//���οؼ���ʼ��
void CAddressBookDlg::InitTreeCtrl()
{
	HICON hIcon[5];						//����ͼ��������
	HTREEITEM hRoot;					//���ڵ���
	HTREEITEM hPacket;					//��ʾ��һ������
	HTREEITEM hMember;				//��ʾ��һ��Ա���

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
		hPacket = m_AddrbookTree.InsertItem(group_name, group_id, group_id, hRoot, TVI_LAST);
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


//����ÿ����Ա����Ϣ
void CAddressBookDlg::InqTable_memberinfo()
{
	
	CString sql = _T("select m_id,m_name,m_sex,CONVERT(varchar(10),m_birthday,23) as m_birthday,\
							m_email,m_phone,m_teleph,m_qq from membership");		//sql���Ҫִ�е�SQL���
	TRY
	{
		rs_memberInfo.Open(CRecordset::snapshot, sql);			//�򿪲�ѯ��¼
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

//����б�
void CAddressBookDlg::FillList()
{
	m_list_info.SetItemText(0, 1, member_information.member_sex);
	m_list_info.SetItemText(1, 1, member_information.member_birthday);
	m_list_info.SetItemText(2, 1, member_information.member_Email);
	m_list_info.SetItemText(3, 1, member_information.member_phone);
	m_list_info.SetItemText(4, 1, member_information.member_teleph);
	m_list_info.SetItemText(5, 1, member_information.member_QQ);
}
