// TextDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Cyan_DBA_Lihua.h"
#include "TextDlg.h"
#include "afxdialogex.h"

// CTextDlg �Ի���

IMPLEMENT_DYNAMIC(CTextDlg, CDialogEx)

CTextDlg::CTextDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextDlg::IDD, pParent)
	//, SWeight(_T(""))
{

	m_text = _T("");
	m_high = 20;
	m_width = 18;
	m_angle = 0;
	m_weight = 0;
}

CTextDlg::~CTextDlg()
{
}

void CTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITSign, m_text);
	DDX_Text(pDX, IDC_EDITHeight, m_high);
	DDX_Text(pDX, IDC_EDITWeight, m_width);
	DDX_Text(pDX, IDC_EDITAngle, m_angle);
	DDX_Control(pDX, IDC_SLIDERText, m_slider);
	DDX_Slider(pDX, IDC_SLIDERText, m_weight);
	DDV_MinMaxInt(pDX, m_weight, 0, 1000);
	//DDX_Text(pDX, IDC_STATICWeight, SWeight);
	DDX_Control(pDX, IDC_EDITHeight, m_EditHigh);
}


BEGIN_MESSAGE_MAP(CTextDlg, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERText, &CTextDlg::OnNMCustomdrawSlidertext)
	ON_EN_KILLFOCUS(IDC_EDITHeight, &CTextDlg::OnEnKillfocusEditheight)
END_MESSAGE_MAP()


// CTextDlg ��Ϣ�������


void CTextDlg::OnNMCustomdrawSlidertext(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(1);
	///////////��IDC_STATICWeight////////////////////
	this->m_slider.SetRange(0,1000);//���ÿؼ���ΧΪ1-1000
	CSliderCtrl*pSlider=(CSliderCtrl*)GetDlgItem(IDC_SLIDERText);
	SetDlgItemInt(IDC_STATICWeight,pSlider->GetPos());
	///////////////////////////////
	CDC* pDC =GetDC();
	int high,width ,angleText;
	high = this->m_high;
	width =this->m_width;
	angleText =(int)this->m_angle*10;
	if(this->m_high>=30) high =30;
	if(this->m_width>=30) width =30;
	if(this->m_text.GetLength()*width>100) 
	{
		high =10;
		width =10;
	}
	CFont myFont;
	myFont.CreateFont(high,width,angleText,0,this->m_weight,0,0,0,1,OUT_TT_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FIXED_PITCH,_T("myfont"));
	CFont* font = pDC->SelectObject(&myFont);
	CRect rc(250,30,500,250);
	CBrush bkBrush(pDC->GetBkColor());	//���ñ�ˢ��ɫ
	pDC->FillRect(&rc,&bkBrush);
	pDC->SetTextColor(RGB(0,0,0));	//�����ı���ɫ
	//pDC->SetTextColor(pColor);	   //�����ı���ɫ
	pDC->TextOut(375,140,this->m_text);
	/////////////////////
	*pResult = 0;
}

//��m_EditHighʧȥ����
void CTextDlg::OnEnKillfocusEditheight()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CString msg;
	//msg.Format(_T("�ı��߶Ȳ���Ϊ : %d"), m_high);	
    float aa = m_high;
    UpdateData(true);
    if ( 0 == m_high)
    {
        MessageBox(_T("�ı��߶Ȳ���Ϊ 0 "),_T("��ֵ������Χ! "),  MB_ICONERROR|MB_OK);
        m_high = aa;
        UpdateData(false);
	}
}
