// Position.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Cyan_DBA_Lihua.h"
#include "Position.h"
#include "afxdialogex.h"


// Position �Ի���

IMPLEMENT_DYNAMIC(Position, CDialogEx)

Position::Position(CWnd* pParent /*=NULL*/)
	: CDialogEx(Position::IDD, pParent)
	, longitude(_T(""))
	, latitude(_T(""))
{

}

Position::~Position()
{
}

void Position::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, longitude);
	DDX_Text(pDX, IDC_EDIT2, latitude);
}


BEGIN_MESSAGE_MAP(Position, CDialogEx)
END_MESSAGE_MAP()


// Position ��Ϣ�������
