// view_member.h : Cview_member ���ʵ��



// Cview_member ʵ��

// ���������� 2015��11��21��, 20:55

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
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Int(pFX, _T("[u_id]"), m_u_id);
	RFX_Int(pFX, _T("[p_id]"), m_p_id);
	RFX_Int(pFX, _T("[m_id]"), m_m_id);
	RFX_Text(pFX, _T("[m_name]"), m_m_name);

}
/////////////////////////////////////////////////////////////////////////////
// Cview_member ���

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


