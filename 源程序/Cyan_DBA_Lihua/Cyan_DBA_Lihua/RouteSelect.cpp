// RouteSelect.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Cyan_DBA_Lihua.h"
#include "RouteSelect.h"
#include "afxdialogex.h"


// RouteSelect �Ի���

IMPLEMENT_DYNAMIC(RouteSelect, CDialogEx)

RouteSelect::RouteSelect(CWnd* pParent /*=NULL*/)
	: CDialogEx(RouteSelect::IDD, pParent)
	, m_index(_T(""))
{
}

RouteSelect::~RouteSelect()
{
}

void RouteSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITSelect, m_index);
}


BEGIN_MESSAGE_MAP(RouteSelect, CDialogEx)
	
END_MESSAGE_MAP()


// RouteSelect ��Ϣ�������


