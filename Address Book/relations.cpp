// relations.h : Crelations ���ʵ��



// Crelations ʵ��

// ���������� 2015��11��26��, 14:24

#include "stdafx.h"
#include "relations.h"
IMPLEMENT_DYNAMIC(Crelations, CRecordset)

Crelations::Crelations(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_u_id = 0;
	m_p_id = 0;
	m_m_id = 0;
	m_nFields = 3;
	m_nDefaultType = dynaset;
}

//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString Crelations::GetDefaultConnect()
{
	return _T("DSN=DataSourceOfAddr;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=DESKTOP-TLIOR44;DATABASE=AddressBook");
}

CString Crelations::GetDefaultSQL()
{
	return _T("[dbo].[relations]");
}

void Crelations::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Int(pFX, _T("[u_id]"), m_u_id);
	RFX_Int(pFX, _T("[p_id]"), m_p_id);
	RFX_Int(pFX, _T("[m_id]"), m_m_id);

}
/////////////////////////////////////////////////////////////////////////////
// Crelations ���

#ifdef _DEBUG
void Crelations::AssertValid() const
{
	CRecordset::AssertValid();
}

void Crelations::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


