// MapMessage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Cyan_DBA_Lihua.h"
#include "MapMessage.h"
#include "afxdialogex.h"


// MapMessage �Ի���

IMPLEMENT_DYNAMIC(MapMessage, CDialogEx)

MapMessage::MapMessage(CWnd* pParent /*=NULL*/)
	: CDialogEx(MapMessage::IDD, pParent)
	, message(_T(""))
{

}

MapMessage::~MapMessage()
{
}

void MapMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITText, message);
}


BEGIN_MESSAGE_MAP(MapMessage, CDialogEx)
	
END_MESSAGE_MAP()


// MapMessage ��Ϣ�������


