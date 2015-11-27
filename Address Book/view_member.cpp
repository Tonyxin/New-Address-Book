// view_member.h : Cview_member 类的实现



// Cview_member 实现

// 代码生成在 2015年11月21日, 20:55

#include "stdafx.h"
#include "view_member.h"
IMPLEMENT_DYNAMIC(Cview_member, CRecordset)

Cview_member::Cview_member(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_u_id = 0;
	m_p_id = 0;
	m_m_id = 0;
	m_m_name = "";
	m_nFields = 4;
	m_nDefaultType = dynaset;
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString Cview_member::GetDefaultConnect()
{
	return _T("DSN=DataSourceOfAddr;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=DESKTOP-TLIOR44;DATABASE=AddressBook");
}

CString Cview_member::GetDefaultSQL()
{
	return _T("[dbo].[member]");
}

void Cview_member::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Int(pFX, _T("[u_id]"), m_u_id);
	RFX_Int(pFX, _T("[p_id]"), m_p_id);
	RFX_Int(pFX, _T("[m_id]"), m_m_id);
	RFX_Text(pFX, _T("[m_name]"), m_m_name);

}
/////////////////////////////////////////////////////////////////////////////
// Cview_member 诊断

#ifdef _DEBUG
void Cview_member::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cview_member::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


