
// Address BookDlg.cpp : 实现文件
//


#include "stdafx.h"
#include "Address Book.h"
#include "Address BookDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CAddressBookDlg 对话框



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


// CAddressBookDlg 消息处理程序

BOOL CAddressBookDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	//连接数据源
	ConnectDataSource();		
	
	//查询用户表信息，用于验证账号密码
	InqTable_Users();				

	//弹出登陆对话框
	m_loginDlg.L_login = L;						//利用成员访问的方式将用户链表L存入给登陆对话框
	if (m_loginDlg.DoModal() != IDOK)	//当×掉登陆对话框时执行OnOk();		
	{														
		OnOK();										//结束所在的对话框
	}
	//销毁用户链表
	datastruct.Destory_Users(L);          
	
	max_member_id = 0;
	max_group_id = 0;

	//查询用户的分组信息
	InqView_Group();

	//查询每个分组中的成员
	InqView_Member();

	//树形控件初始化并加载节点信息
	InitTreeCtrl();
	LoadOtherNode();					//加载节点信息

	//查询成员信息
	InqTable_memberinfo();

	//列表视图控件初始化
	InitListCtrl();
	
	//加载relations表，此处是为了对成员进行删除和添加
	InqTable_Relation();

	//加载packetmode表，此处是为了对分组进行添加
	InqTable_Packetmode();

	//隐藏用于修改列表框的EDIT控件
	m_edit_temp.ShowWindow(SW_HIDE);
	button_upd_is_down = 0;						//列表框禁止修改
	edit_name.EnableWindow(FALSE);

	//隐藏修改控件
	button_add.ShowWindow(SW_HIDE);
	button_update.ShowWindow(SW_HIDE);
	button_cancel.ShowWindow(SW_HIDE);
	button_add_group.ShowWindow(SW_HIDE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAddressBookDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAddressBookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//----------------------------------------------------------------------------
//-----------------------初始化操作------------------------------------------
//----------------------------------------------------------------------------
//连接数据源
void CAddressBookDlg::ConnectDataSource()
{
	//连接数据源
	TRY
	{
	m_db.OpenEx(_T("DSN=DataSourceOfAddr;"), CDatabase::noOdbcDialog);	//连接到一个名为DataSourceOfAddr的数据源
	rs_user.m_pDatabase = &m_db;
	rs_group.m_pDatabase = &m_db;
	rs_member.m_pDatabase = &m_db;
	rs_memberInfo.m_pDatabase = &m_db;
	rs_relation.m_pDatabase = &m_db;
	rs_packetmode.m_pDatabase = &m_db;
	}

	//显示连接是否成功
	if (!m_db.IsOpen())		AfxMessageBox(_T("连接数据源失败"));

	//处理异常消息
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

//查询用户信息
void CAddressBookDlg::InqTable_Users()
{
	CString sql = _T("SELECT * FROM users");		//sql存放要执行的SQL语句
	L = datastruct.CreatList_Users();
	LinkList_Users L_temp = L;
	TRY
	{
		rs_user.Open(CRecordset::none, sql);			//打开查询记录
		rs_user.MoveFirst();											//滚到第一条记录
		while (!rs_user.IsEOF())										//未滚过最后一条记录，则执行
		{
			ElemType_Users data_user;
			data_user.user_name = rs_user.m_u_name;					//因为已经将类Cusers绑定到表users中
			data_user.user_password = rs_user.m_u_password;		//会实时更新
			data_user.user_id = rs_user.m_u_id;
			datastruct.InsertList_Users(L, data_user);						//插入用户链表
			rs_user.MoveNext();														//滚向下一条记录
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

//对登陆对话框的消息响应函数，存储当前用户id
LRESULT CAddressBookDlg::OnRecevUser(WPARAM wParam, LPARAM lParam)
{
	id_user = *((int*)lParam);			//保存当前用户id
	return TRUE;
}

//查询分组视图信息
void CAddressBookDlg::InqView_Group()
{
	CString sql = _T("SELECT * FROM view_group");		//sql存放要执行的SQL语句
	L_Group = datastruct.CreatList_Group();
	LinkList_Group L_temp = L_Group;
	TRY
	{
		rs_group.Open(CRecordset::none, sql);			//打开查询记录
		rs_group.MoveFirst();											//滚到第一条记录
		while (!rs_group.IsEOF())										//未滚过最后一条记录，则执行
		{
			if (rs_group.m_u_id == id_user)							//只为当前用户建立链表
			{
				ElemType_Group data_group;
				data_group.group_id = rs_group.m_p_id;
				data_group.group_name = rs_group.m_p_mode;
				data_group.user_id = rs_group.m_u_id;
				datastruct.InsertList_Group(L_Group, data_group);		//插入分组链表
			}
			rs_group.MoveNext();														//滚向下一条记录
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

//查询个分组中成员（只有成员的名称，详细信息在别的函数中）
void CAddressBookDlg::InqView_Member()
{
	CString sql = _T("SELECT * FROM member");		//sql存放要执行的SQL语句
	TRY
	{
		rs_member.Open(CRecordset::none, sql);			//打开查询记录
		rs_member.MoveFirst();												//滚到第一条记录
		while (!rs_member.IsEOF())										//未滚过最后一条记录，则执行
		{
			//保存当前最大的成员id，便于之后添加成员
			if (rs_member.m_u_id == id_user)							//属于当前用户
			{
				LinkList_Group L_temp = L_Group;
				while (L_temp->next)
				{
					L_temp = L_temp->next;
					if (L_temp->data.group_id == rs_member.m_p_id)	//属于当前分组
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

//加载每个成员的信息
void CAddressBookDlg::InqTable_memberinfo()
{

	CString sql = _T("select * from membership");		//sql存放要执行的SQL语句
	TRY
	{
		rs_memberInfo.Open(CRecordset::none, sql);			//打开查询记录
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
				rs_memberInfo.MoveFirst();											//滚到第一条记录
				while (!rs_memberInfo.IsEOF())										//未滚过最后一条记录，则执行
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

//加载relations表
void CAddressBookDlg::InqTable_Relation()
{
	CString sql = _T("select * from relations");
	TRY
	{
		rs_relation.Open(CRecordset::none, sql);			//打开查询记录
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

// 加载packetmode表
void CAddressBookDlg::InqTable_Packetmode()
{
	CString sql = _T("select * from packetmode");
	TRY
	{
		rs_packetmode.Open(CRecordset::none, sql);			//打开查询记录
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

//树形控件初始化
void CAddressBookDlg::InitTreeCtrl()
{
	//加载图标，将他们的句柄保存到数组
	hIcon[0] = theApp.LoadIcon(IDI_ICON_addrbook);
	hIcon[1] = theApp.LoadIcon(IDI_ICON_family);
	hIcon[2] = theApp.LoadIcon(IDI_ICON_classmate);
	hIcon[3] = theApp.LoadIcon(IDI_ICON_friend);
	hIcon[4] = theApp.LoadIcon(IDI_ICON_people);

	//创建图像序列CImageList对象
	m_ImageList.Create(32, 32, ILC_COLOR32, 5, 5);
	//将图标添加到序列
	for (int i = 0; i < 5; i++)		m_ImageList.Add(hIcon[i]);

	//为树形控件设置图像序列
	m_AddrbookTree.SetImageList(&m_ImageList, TVSIL_NORMAL);

}

// 加载根节点之外的节点信息到树形控件
void CAddressBookDlg::LoadOtherNode()
{
	//将分组成员信息显示到树形控件中
	//插入根节点
	hRoot = m_AddrbookTree.InsertItem(_T("通讯录"), 0, 0);
	m_AddrbookTree.SetItemData(hRoot, 0);			//设置跟节点的附加数据为0
	LinkList_Group L_Group_temp = L_Group;
	//根节点下插入分组节点
	while (L_Group_temp->next)
	{
		L_Group_temp = L_Group_temp->next;
		CString group_name = L_Group_temp->data.group_name;
		int group_id = L_Group_temp->data.group_id;
		if (group_id<4)		hPacket = m_AddrbookTree.InsertItem(group_name, group_id, group_id, hRoot, TVI_LAST);
		else    hPacket = m_AddrbookTree.InsertItem(group_name, 2, 2, hRoot, TVI_LAST);
		m_AddrbookTree.SetItemData(hPacket, group_id);		//分组节点的附加数据为分组编号
		//分组节点下插入根节点
		LinkList_Member L_Member_temp = L_Group_temp->data.member_list;
		while (L_Member_temp->next)
		{
			L_Member_temp = L_Member_temp->next;
			CString member_name = L_Member_temp->data.member_name;
			hMember = m_AddrbookTree.InsertItem(member_name, 4, 4, hPacket, TVI_LAST);
			m_AddrbookTree.SetItemData(hMember, L_Member_temp->data.member_id);
			//成员节点的附加数据为成员编号
		}
	}
}



//---------------------------------------------------------------------------------
//---------------树形控件左键单击，显示节点信息---------------------------------
//---------------------------------------------------------------------------------
//对树形控件左键点击，显示成员信息
void CAddressBookDlg::OnTvnSelchangedTreeAddressbook(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	CString strText;				//存放树节点的标签文本字符串

	ClearList();		//清空表

	//获取根节点句柄及附加数据
	HTREEITEM hItem_root = m_AddrbookTree.GetRootItem();
	DWORD_PTR RootId = m_AddrbookTree.GetItemData(hItem_root);

	//获取当前选中的句柄及附加数据
	hItem = m_AddrbookTree.GetSelectedItem();
	hId = m_AddrbookTree.GetItemData(hItem);

	//获取选中节点的标签字符串
	strText = m_AddrbookTree.GetItemText(hItem);
	//将字符串显示到编辑框中
	SetDlgItemText(IDC_EDIT_SELECTED, strText);

	if (hId != RootId)
	{
		//获取父节点句柄及附加数据
		HTREEITEM hItem_parent = m_AddrbookTree.GetParentItem(hItem);
		ParentId = m_AddrbookTree.GetItemData(hItem_parent);

		//点击的节点为成员，显示成员信息
		if (ParentId != RootId)
		{
			DWORD_PTR GroupId = ParentId;	//获取分组编号
			DWORD_PTR MemberId = hId;			//获取成员编号
			//在链表中寻找当前点中的成员节点信息，保存在member_information中
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
			//此处添加节点信息的显示操作
			FillList();		//将选中成员信息显示到表中
		}//if
	}
}


void CAddressBookDlg::OnEnChangeEditSelected()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

// 屏蔽回车和ESC按键
BOOL CAddressBookDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_RETURN)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}


//--------------------------------------------------------------------
//------------------对列表视图控件的操作----------------------------
//--------------------------------------------------------------------
//初始化列表视图控件
void CAddressBookDlg::InitListCtrl()
{
	CRect rect;

	//获取列表视图控件的位置和大小
	m_list_info.GetClientRect(&rect);

	//为列表视图控件添加全行选中和栅格风格
	m_list_info.SetExtendedStyle(m_list_info.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//为列表视图控件添加两列
	m_list_info.InsertColumn(0, _T("成员信息"), LVCFMT_CENTER, rect.Width() / 2, 0);
	m_list_info.InsertColumn(1, _T("数据"), LVCFMT_CENTER, rect.Width() / 2, 1);

	//添加相应的行
	m_list_info.InsertItem(0, _T("性别"));
	m_list_info.InsertItem(1, _T("出生日期"));
	m_list_info.InsertItem(2, _T("邮箱"));
	m_list_info.InsertItem(3, _T("电话"));
	m_list_info.InsertItem(4, _T("手机"));
	m_list_info.InsertItem(5, _T("QQ"));
}

//清空列表
void CAddressBookDlg::ClearList()
{
	m_list_info.SetItemText(0, 1, _T(""));
	m_list_info.SetItemText(1, 1, _T(""));
	m_list_info.SetItemText(2, 1, _T(""));
	m_list_info.SetItemText(3, 1, _T(""));
	m_list_info.SetItemText(4, 1, _T(""));
	m_list_info.SetItemText(5, 1, _T(""));
}

//将当前member_information信息的填充到列表
void CAddressBookDlg::FillList()
{
	m_list_info.SetItemText(0, 1, member_information.member_sex);
	m_list_info.SetItemText(1, 1, member_information.member_birthday);
	m_list_info.SetItemText(2, 1, member_information.member_Email);
	m_list_info.SetItemText(3, 1, member_information.member_phone);
	m_list_info.SetItemText(4, 1, member_information.member_teleph);
	m_list_info.SetItemText(5, 1, member_information.member_QQ);
}

//OnNMDblclkListInfo()与OnEnKillfocusEditTemp()组合用于修改列表框的显示文本
void CAddressBookDlg::OnNMDblclkListInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	if (button_upd_is_down)
	{
		NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
		CRect rc;
		m_Row = pNMListView->iItem;//获得选中的行  
		m_Col = pNMListView->iSubItem;//获得选中列  

		if (pNMListView->iSubItem != 0) //如果选择的是子项;  
		{
			m_list_info.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);//获得子项的RECT；  
			m_edit_temp.SetParent(&m_list_info);//转换坐标为列表框中的坐标  
			m_edit_temp.MoveWindow(rc);//移动Edit到RECT坐在的位置;  
			m_edit_temp.SetWindowText(m_list_info.GetItemText(m_Row, m_Col));//将该子项中的值放在Edit控件中；  
			m_edit_temp.ShowWindow(SW_SHOW);//显示Edit控件；  
			m_edit_temp.SetFocus();//设置Edit焦点  
			m_edit_temp.ShowCaret();//显示光标  
			m_edit_temp.SetSel(-1);//将光标移动到最后  
		}
	}
	*pResult = 0;
}
//编辑框失去焦点时的消息处理函数，用于将编辑框中的值传入到列表中
void CAddressBookDlg::OnEnKillfocusEditTemp()
{
	// TODO:  在此添加控件通知处理程序代码
	if (button_upd_is_down)
	{
		CString tem;
		m_edit_temp.GetWindowText(tem);					//得到用户输入的新的内容  
		m_list_info.SetItemText(m_Row, m_Col, tem);   //设置编辑框的新内容  
		m_edit_temp.ShowWindow(SW_HIDE);             //应藏编辑框
	}
}


//------------------------------------------------------------------------
//---------------------对数据库进行增删改操作---------------------------
//------------------------------------------------------------------------
//树形控件的右键操作，保存并显示了当前结点信息
void CAddressBookDlg::OnNMRClickTreeAddressbook(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码

	//获取屏幕位置
	CPoint ScreenPt;
	GetCursorPos(&ScreenPt);
	CPoint pt(ScreenPt);

	//	完成屏幕坐标到客户区坐标的转换
	m_AddrbookTree.ScreenToClient(&ScreenPt);

	hItem = m_AddrbookTree.HitTest(ScreenPt);
	if (hItem)
	{
		//获取选中节点的标签字符串
		CString strText = m_AddrbookTree.GetItemText(hItem);
		//将字符串显示到编辑框中
		SetDlgItemText(IDC_EDIT_SELECTED, strText);

		//获取根节点句柄及附加数据
		HTREEITEM hItem_root = m_AddrbookTree.GetRootItem();
		DWORD_PTR RootId = m_AddrbookTree.GetItemData(hItem_root);

		hId = m_AddrbookTree.GetItemData(hItem);
		CMenu menu;			//菜单对象

		//点中节点为根节点
		if (hId == RootId)
		{
			menu.LoadMenuW(IDR_MENU3);
			datastruct.ClearMemberInfo(member_information);
			FillList();
		}
		else
		{
			//获取父节点句柄及附加数据
			HTREEITEM hItem_parent = m_AddrbookTree.GetParentItem(hItem);
			ParentId = m_AddrbookTree.GetItemData(hItem_parent);
			//点中节点为分组节点
			if (ParentId == RootId)
			{
				datastruct.ClearMemberInfo(member_information);
				menu.LoadMenuW(IDR_MENU2);
			}	
			//点中节点为成员节点
			else
			{
				//保存当前点节点信息
				LinkList_Group L_Group_temp = L_Group;
				while (L_Group_temp->next)
				{
					L_Group_temp = L_Group_temp->next;
					if (L_Group_temp->data.group_id == ParentId)					//此时ParentId为相应分组节点id
					{
						LinkList_Member L_Member_temp = L_Group_temp->data.member_list;
						while (L_Member_temp->next)
						{
							L_Member_temp = L_Member_temp->next;
							if (hId == L_Member_temp->data.member_id)				//此时hId为相应成员节点id
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
		
		CMenu* pPopup = menu.GetSubMenu(0);//装载第一个子菜单，即我们菜单的第一列
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, pt.x, pt.y, this);	//弹出菜单
		menu.DestroyMenu();
		*pResult = 0;
	}
}

//成员节点点下了"修改"菜单
void CAddressBookDlg::OnModifyMember()
{
	// TODO:  在此添加命令处理程序代码
	m_AddrbookTree.EnableWindow(FALSE);					//树形控件禁用
	button_update.ShowWindow(SW_SHOW);						//修改按钮使能
	button_cancel.ShowWindow(SW_SHOW);							//取消按钮使能
	button_upd_is_down = 1;											//编辑列表框使能
}

//成员节点下点击"删除"菜单，实际上只是解除了成员和用户的关系
void CAddressBookDlg::OnDeleteMember()
{
	// TODO:  在此添加命令处理程序代码
	//数据同步到存储的链表中
	LinkList_Group L_Group_temp = L_Group;
	while (L_Group_temp->next)
	{
		L_Group_temp = L_Group_temp->next;
		if (L_Group_temp->data.group_id == ParentId)					//此时ParentId为相应分组节点id
		{
			LinkList_Member L_Member_temp = L_Group_temp->data.member_list;
			if (!datastruct.DeleteList_Member(L_Member_temp, hId))	AfxMessageBox(_T("删除成员失败"));
			break;
		}//if
	}//while

	//数据同步到数据库中
	rs_relation.MoveFirst();
	while (!rs_relation.IsEOF())										//未滚过最后一条记录，则执行
	{
		if ((hId == rs_relation.m_m_id) && (id_user == rs_relation.m_u_id))
		{
			rs_relation.Delete();
			break;
		}
		rs_relation.MoveNext();
	}

	//将编辑框置空
	SetDlgItemText(IDC_EDIT_SELECTED, _T(""));
	//清空列表
	ClearList();
	//删除当前节点
	m_AddrbookTree.DeleteItem(hItem);
}

//分组节点点击"添加成员"菜单
void CAddressBookDlg::OnAddMember()
{
	// TODO:  在此添加命令处理程序代码
	m_AddrbookTree.EnableWindow(FALSE);					//树形控件禁用
	button_add.ShowWindow(SW_SHOW);						//添加按钮使能
	button_cancel.ShowWindow(SW_SHOW);					//取消按钮使能
	button_upd_is_down = 1;											//编辑列表框使能
	edit_name.EnableWindow(TRUE);								//编辑框使能
	FillList();
	SetDlgItemText(IDC_EDIT_SELECTED, _T(""));				//令编辑框为空
	//按钮显示到指定位置
	CRect rect;
	button_update.GetWindowRect(&rect);
	ScreenToClient(&rect);
	button_add.MoveWindow(rect);
}

//分组节点点击"删除分组"菜单，直接删掉relations表中相关行
void CAddressBookDlg::OnDeleteGroup()
{
	// TODO:  在此添加命令处理程序代码
	//数据同步到存储的链表中
	LinkList_Group L_Group_temp = L_Group;
	while (L_Group_temp->next)
	{
		L_Group_temp = L_Group_temp->next;
		if (L_Group_temp->data.group_id == hId)							//此时hId为相应分组节点id
		{
			datastruct.DeleteList_Group(L_Group_temp, hId);
			break;
		}
	}

	//数据同步到数据库中
	rs_relation.MoveFirst();
	while (!rs_relation.IsEOF())										//未滚过最后一条记录，则执行
	{
		if ((hId == rs_relation.m_p_id) && (id_user == rs_relation.m_u_id))
		{
			rs_relation.Delete();
		}
		rs_relation.MoveNext();
	}

	//将编辑框置空
	SetDlgItemText(IDC_EDIT_SELECTED, _T(""));
	//清空列表
	ClearList();
	//删除当前节点
	m_AddrbookTree.DeleteItem(hItem);
}

//通讯录根节点下点击"添加分组"
void CAddressBookDlg::OnAddGroup()
{
	// TODO:  在此添加命令处理程序代码
	m_AddrbookTree.EnableWindow(FALSE);					//树形控件禁用
	button_add_group.ShowWindow(SW_SHOW);			//添加按钮使能
	button_cancel.ShowWindow(SW_SHOW);					//取消按钮使能
	edit_name.EnableWindow(TRUE);								//编辑框使能
	SetDlgItemText(IDC_EDIT_SELECTED, _T(""));				//令编辑框为空
	
	//按钮显示到指定位置
	CRect rect;
	button_update.GetWindowRect(&rect);
	ScreenToClient(&rect);												
	button_add_group.MoveWindow(rect);

}

//点击了"确认添加成员"按钮
void CAddressBookDlg::OnBnClickedButtonAdd()
{
	// TODO:  在此添加控件通知处理程序代码
	button_add.ShowWindow(SW_HIDE);							//添加按钮隐藏
	button_cancel.ShowWindow(SW_HIDE);						//取消按钮隐藏
	m_AddrbookTree.EnableWindow(TRUE);						//树形控件使能
	button_upd_is_down = 0;												//编辑列表框禁用
	
	CString m_name;		//新加入成员姓名
	GetDlgItemText(IDC_EDIT_SELECTED, m_name);			//编辑框中填写成员名
	if (!m_name)
	{
		AfxMessageBox(_T("姓名不能为空！"));
		edit_name.SetFocus();				//设置Edit焦点  
		edit_name.ShowCaret();			//显示光标  
		edit_name.SetSel(-1);				//将光标移动到最后  
		FillList();									//清空列表
	}
	else
	{
		edit_name.EnableWindow(FALSE);				//编辑框禁用
		member_information.member_sex = m_list_info.GetItemText(0, 1);
		member_information.member_birthday = m_list_info.GetItemText(1, 1);
		member_information.member_Email = m_list_info.GetItemText(2, 1);
		member_information.member_phone = m_list_info.GetItemText(3, 1);
		member_information.member_teleph = m_list_info.GetItemText(4, 1);
		member_information.member_QQ = m_list_info.GetItemText(5, 1);


		//将更改后的结果保存到数据库
		//更改membership表
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
		
		//这里因为membership中m_id自增，因此插入后还要返回m_id值
		rs_memberInfo.MoveLast();
		max_member_id = rs_memberInfo.m_m_id;
		
		//将更改后的数据同步到存储的链表中
		LinkList_Group L_Group_temp = L_Group;
		while (L_Group_temp->next)
		{
			L_Group_temp = L_Group_temp->next;
			if (L_Group_temp->data.group_id == hId)					//此时hId为当前分组id
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

		//将结果保存到数据库中
		//更改"relations"表
		rs_relation.AddNew();
		rs_relation.m_u_id = id_user;
		rs_relation.m_p_id = hId;
		rs_relation.m_m_id = max_member_id;
		rs_relation.Update();
		rs_relation.Requery();

		//在树形控件中加入新节点
		hMember = m_AddrbookTree.InsertItem(m_name, 4, 4, hItem, TVI_LAST);
		m_AddrbookTree.SetItemData(hMember, max_member_id);
	}//else
}

//点击了"确认修改"按钮
void CAddressBookDlg::OnBnClickedButtonUpdate()
{
	// TODO:  在此添加控件通知处理程序代码
	button_update.ShowWindow(SW_HIDE);						//修改按钮禁用
	button_cancel.ShowWindow(SW_HIDE);						//取消按钮禁用
	m_AddrbookTree.EnableWindow(TRUE);						//树形空间使能
	button_upd_is_down = 0;												//编辑列表框禁用

	member_information.member_sex = m_list_info.GetItemText(0, 1);
	member_information.member_birthday = m_list_info.GetItemText(1, 1);
	member_information.member_Email = m_list_info.GetItemText(2, 1);
	member_information.member_phone = m_list_info.GetItemText(3, 1);
	member_information.member_teleph = m_list_info.GetItemText(4, 1);
	member_information.member_QQ = m_list_info.GetItemText(5, 1);

	//将更改后的数据同步到存储的链表中
	LinkList_Group L_Group_temp = L_Group;
	while (L_Group_temp->next)
	{
		L_Group_temp = L_Group_temp->next;
		if (L_Group_temp->data.group_id == ParentId)					//此时ParentId为相应分组节点id
		{
			LinkList_Member L_Member_temp = L_Group_temp->data.member_list;
			while (L_Member_temp->next)
			{
				L_Member_temp = L_Member_temp->next;
				if (hId == L_Member_temp->data.member_id)				//此时hId为相应成员节点id
				{
					L_Member_temp->data.member_info = member_information;
					break;
				}
			}//while
			break;
		}//if
	}//while

	//将更改后的数据同步到数据库
	rs_memberInfo.MoveFirst();											//滚动到第一条记录
	while (!rs_memberInfo.IsEOF())										//未滚过最后一条记录，则执行
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

//点击"确认添加分组"按钮
void CAddressBookDlg::OnBnClickedButtonAddgroup()
{
	// TODO:  在此添加控件通知处理程序代码
	button_add_group.ShowWindow(SW_HIDE);					//添加按钮隐藏
	button_cancel.ShowWindow(SW_HIDE);						//取消按钮隐藏
	m_AddrbookTree.EnableWindow(TRUE);						//树形控件使能

	CString m_name;		//新加入成员姓名
	GetDlgItemText(IDC_EDIT_SELECTED, m_name);			//编辑框中填写成员名
	if (!m_name)
	{
		AfxMessageBox(_T("分组名称不能为空！"));
		edit_name.SetFocus();				//设置Edit焦点  
		edit_name.ShowCaret();			//显示光标  
		edit_name.SetSel(-1);				//将光标移动到最后  
		FillList();									//清空列表
	}
	else
	{
		//将数据保存到数据库
		//保存到packetmode表
		rs_packetmode.AddNew();
		rs_packetmode.m_p_mode = m_name;
		rs_packetmode.Update();
		rs_packetmode.Requery();

		rs_packetmode.MoveLast();
		max_group_id = rs_packetmode.m_p_id;

		//保存到relation表
		rs_relation.AddNew();
		rs_relation.m_u_id = id_user;
		rs_relation.m_p_id = max_group_id;
		rs_relation.Update();
		rs_relation.Requery();

		//保存到存储的链表中
		ElemType_Group data_group;
		data_group.group_id = max_group_id;
		data_group.group_name = m_name;
		data_group.user_id = id_user;
		datastruct.InsertList_Group(L_Group, data_group);		//插入分组链表

		hPacket = m_AddrbookTree.InsertItem(m_name, 2, 2, hItem, TVI_LAST);
		m_AddrbookTree.SetItemData(hPacket, max_group_id);
	}
}

//点击"取消"按钮
void CAddressBookDlg::OnBnClickedButtonCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	//编辑框被使能，重新显示原内容，并将编辑框禁用
	if (edit_name.IsWindowEnabled())
	{
		CString strText = m_AddrbookTree.GetItemText(hItem);
		SetDlgItemText(IDC_EDIT_SELECTED, strText);
		edit_name.EnableWindow(FALSE);
	}
	button_update.ShowWindow(SW_HIDE);						//修改按钮禁用
	button_cancel.ShowWindow(SW_HIDE);						//取消按钮禁用
	button_add_group.ShowWindow(SW_HIDE);					//添加分组按钮禁用
	button_add.ShowWindow(SW_HIDE);							//添加成员按钮禁用
	m_AddrbookTree.EnableWindow(TRUE);						//树形空间使能
	button_upd_is_down = 0;												//编辑列表框禁用
	FillList();
}





