#pragma once


// ColorTool �Ի���
#include<string.h>

class ColorTool : public CDialogEx
{
	DECLARE_DYNAMIC(ColorTool)

public:
	ColorTool(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ColorTool();

// �Ի�������
	enum { IDD = IDD_DIALOGAttr };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()

private:
	//����
	CComboBox type;
	//Slider
	CSliderCtrl slider;
	

public:
	//����
	CString num;

	//Slider (Value)
	int m_slider;
	//����
	short linetype;
	//��ɫ
	COLORREF penCo1or;
	//��ˢɫ
	COLORREF brushCo1or;
	//����
	CPen pen;
	//��ˢ
	CBrush brush;

	afx_msg void OnBnClickedButtonpen();
	afx_msg void OnBnClickedButtonbrush();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMCustomdrawSliderwide(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
