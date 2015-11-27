// view_group.h : Cview_group ���ʵ��



// Cview_group ʵ��

// ���������� 2015��11��21��, 19:18

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
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Int(pFX, _T("[u_id]"), m_u_id);
	RFX_Int(pFX, _T("[p_id]"), m_p_id);
	RFX_Text(pFX, _T("[p_mode]"), m_p_mode);

}
/////////////////////////////////////////////////////////////////////////////
// Cview_group ���

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


