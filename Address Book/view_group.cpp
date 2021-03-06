// view_group.h : Cview_group 类的实现



// Cview_group 实现

// 代码生成在 2015年11月21日, 19:18

#include "stdafx.h"
#include "view_group.h"
IMPLEMENT_DYNAMIC(Cview_group, CRecordset)

Cview_group::Cview_group(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_u_id = 0;
	m_p_id = 0;
	m_p_mode = "";
	m_nFields = 3;
	m_nDefaultType = dynaset;
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString Cview_group::GetDefaultConnect()
{
	return _T("DSN=DataSourceOfAddr;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=DESKTOP-TLIOR44;DATABASE=AddressBook");
}

CString Cview_group::GetDefaultSQL()
{
	return _T("[dbo].[view_group]");
}

void Cview_group::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Int(pFX, _T("[u_id]"), m_u_id);
	RFX_Int(pFX, _T("[p_id]"), m_p_id);
	RFX_Text(pFX, _T("[p_mode]"), m_p_mode);

}
/////////////////////////////////////////////////////////////////////////////
// Cview_group 诊断

#ifdef _DEBUG
void Cview_group::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cview_group::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


