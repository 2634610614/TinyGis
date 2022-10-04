// LoginInterface.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Cyan_DBA_Lihua.h"
#include "LoginInterface.h"
#include "afxdialogex.h"


// LoginInterface �Ի���

IMPLEMENT_DYNAMIC(LoginInterface, CDialogEx)

LoginInterface::LoginInterface(CWnd* pParent /*=NULL*/)
	: CDialogEx(LoginInterface::IDD, pParent)
	, account(_T(""))
	, password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

LoginInterface::~LoginInterface()
{
}

void LoginInterface::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, account);
	DDX_Text(pDX, IDC_EDIT2, password);
}


BEGIN_MESSAGE_MAP(LoginInterface, CDialogEx)
	ON_BN_CLICKED(IDOK, &LoginInterface::OnBnClickedOk)
END_MESSAGE_MAP()


// LoginInterface ��Ϣ�������


void LoginInterface::OnBnClickedOk()
{
	this->UpdateData();
	if(this->password==("2333")&&this->account==("9527"))
	{
		MessageBox(_T("�û�9527"),_T("��¼�ɹ�"),MB_OK);
		CDialogEx::OnOK();

	}
	else if(this->password==("lihua666")&&this->account==("26346"))
	{
		MessageBox(_T("�û�:Lihua"),_T("��¼�ɹ�"),MB_OK);
		CDialogEx::OnOK();
	}
	else if(this->password==("06010127")&&this->account==("15039"))
	{
		MessageBox(_T("�û�:������"),_T("��¼�ɹ�"),MB_OK);
		CDialogEx::OnOK();
	}
	else if(this->password==("258080")&&this->account==("258080"))
	{
		MessageBox(_T("�û�:��ͮ��ʦ"),_T("��ʦ��"),MB_OK);
		CDialogEx::OnOK();
	}
	else

	{
		MessageBox(_T("�û������������"),_T("��¼ʧ��"),MB_ICONERROR|MB_OK);
		//password= "";
		//account= "";
		//UpdateData();
		//this->DoModal();
		//CDialogEx::OnYes();
		OnNO();
		//exit(1);
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
}

int LoginInterface::OnNO()
{
	return IDNO;
}
