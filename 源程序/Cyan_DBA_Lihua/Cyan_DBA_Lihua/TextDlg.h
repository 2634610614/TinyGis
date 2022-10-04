#ifndef _TEXTDLG_
#define _TEXTDLG_
#pragma once
#include <iostream>
#include "afxwin.h"

// CTextDlg �Ի���

class CTextDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTextDlg)

public:
	CTextDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTextDlg();

// �Ի�������
	enum { IDD = IDD_DIALOGText };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//Eidt�ı�����ı�
	CString m_text;
	//����߶�
	CEdit m_EditHigh;
	UINT m_high;
	//���
	UINT m_width;
	//�Ƕ�
	UINT m_angle;
	//����
	CSliderCtrl m_slider;
	int m_weight;	 //��ϸ
	//������ɫ		
	COLORREF pColor;
	//���������¼�����
	afx_msg void OnNMCustomdrawSlidertext(NMHDR *pNMHDR, LRESULT *pResult);
	//��m_EditHighʧȥ����
	afx_msg void OnEnKillfocusEditheight();
};
#endif
