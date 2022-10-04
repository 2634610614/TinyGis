	// ColorTool.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Cyan_DBA_Lihua.h"
#include "ColorTool.h"
#include "afxdialogex.h"


// ColorTool �Ի���

IMPLEMENT_DYNAMIC(ColorTool, CDialogEx)

ColorTool::ColorTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(ColorTool::IDD, pParent)
	, num(_T(""))
{

	m_slider = 0;
}

ColorTool::~ColorTool()
{
}

void ColorTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBOLineType, type);
	DDX_Control(pDX, IDC_SLIDERWide, slider);
	DDX_Slider(pDX, IDC_SLIDERWide, m_slider);
	DDX_Text(pDX, IDC_STATICNum, num);
}


BEGIN_MESSAGE_MAP(ColorTool, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONPen, &ColorTool::OnBnClickedButtonpen)
	ON_BN_CLICKED(IDC_BUTTONBrush, &ColorTool::OnBnClickedButtonbrush)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERWide, &ColorTool::OnNMCustomdrawSliderwide)
	ON_BN_CLICKED(IDOK, &ColorTool::OnBnClickedOk)
END_MESSAGE_MAP()


// ColorTool ��Ϣ�������

//������ɫ
void ColorTool::OnBnClickedButtonpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//������ɫ
	CDC* pDC =GetDC();
	CColorDialog dlgColor;

	//��ɫ��
	dlgColor.m_cc.Flags|=CC_RGBINIT|CC_FULLOPEN;

	if(IDOK == dlgColor.DoModal())
	{
		pen.DeleteObject();
		penCo1or =dlgColor.GetColor();
		pen.CreatePen(linetype,2,penCo1or);
	}
	//Ԥ����ɫ
	CRect rc(330,100,360,130);
	CBrush bkBrush(this->penCo1or);
	pDC->FillRect(&rc,&bkBrush);
}

//��ˢ��ɫ
void ColorTool::OnBnClickedButtonbrush()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ˢ��ɫ
	CDC* pDC =GetDC();
	CColorDialog dlgColor;

	dlgColor.m_cc.Flags|=CC_RGBINIT|CC_FULLOPEN;

	if(IDOK == dlgColor.DoModal())
	{
		brush.DeleteObject();
		brushCo1or =dlgColor.GetColor();
	}
	//Ԥ����ɫ
	CRect rc(330,160,360,190);
	CBrush bkBrush(this->brushCo1or);
	pDC->FillRect(&rc,&bkBrush);
}

////����///////////
BOOL ColorTool::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  
	CSliderCtrl*pSlider=(CSliderCtrl*)GetDlgItem(IDC_SLIDERWide);
	pSlider->SetRange(0,100);
	pSlider->SetRange(m_slider,100,TRUE);
	pSlider->SetPos(1);
	num ="1";
	type.AddString(_T("ʵ��_____________________"));
	type.AddString(_T("���� _ _ _ _ _ _ _ _ _ _ "));
	type.AddString(_T("˫�㻮�� _ _ __ _ _ ___ _"));
	//type.AddString(_T("�ڿ���_ __ __ __ __  __ _"));	
	type.AddString(_T("        ��  ��           "));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void ColorTool::OnNMCustomdrawSliderwide(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int n =(unsigned char)type.GetCurSel();
	UpdateData(true);
	if((n!=0)&& this->slider.GetPos()!=1)
	{
		this->slider.SetPos(1);
		MessageBox(_T(" �ѽ����ǿ������Ϊ 1 "),_T(" ��ʵ�ߵĿ�Ȳ��ó���1 "), MB_ICONWARNING|MB_OK);
		UpdateData(false);
	}
	
	CSliderCtrl*pSlider=(CSliderCtrl*)GetDlgItem(IDC_SLIDERWide);
	SetDlgItemInt(IDC_STATICNum,pSlider->GetPos());
	*pResult = 0;
}


void ColorTool::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/**************
	CPen(int nPenStyle,int nWidth,COLORREF crColor)��
	������Parameter��	ע�ͣ�Annotation��
	PS_SOLID		����һ��ʵ�߻���
	PS_DASH			����һ�����߻��ʣ���ֵֻ�е����ʿ��С��1���豸��λ���Сʱ����Ч
	PS_DOT			ͬ��
	PS_DASHDOT		ͬ��
	PS_DASHDOTDOT	����һ��˫���߻��ʣ���ֵֻ�е����ʿ��С��1���豸��λ���Сʱ����Ч
	PS_NULL			����һ�����߻���
	PS_INSIDEFRAME	����һ���ڿ��߻��ʣ��û��ʿ�����Windows GDI�����������ľ��α߽������ɵķ��״�ı߿��ڻ���ֱ��
	***********/
	int n =(unsigned char)type.GetCurSel();
	switch(n)
	{
	case 0:
		linetype =PS_SOLID;
		break;
	case 1:
		linetype = PS_DASH;	
		break;
	case 2:
		linetype =	PS_DASHDOTDOT;	
		break;
	//case 3:
	//	linetype=PS_INSIDEFRAME;
	//	break;
	case 3:
		linetype=PS_NULL;
		break;
	default:
		linetype = PS_SOLID;
		break;
	}
	CDialogEx::OnOK();
}
