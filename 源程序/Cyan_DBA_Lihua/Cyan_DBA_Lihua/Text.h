#ifndef _TEXT_
#define _TEXT_

#pragma once
#include "draw.h"
#include <math.h>
#include <limits>



#define pi (3.14159265358)
class CText :
	public CDraw
{
DECLARE_SERIAL (CText)
public:
	CText(void);
	//���캯��
	CText(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,BOOL b_Delete,
			float m_StartX,float m_StartY,float m_Angle,float m_TextHeight,float m_TextWide,float m_FontWeight,CString m_Text);
	~CText(void);

	/////////////////////////
	//////��������///////////
	void Draw(CDC *pDC,int Mode,int length = 0,int index = 0);
	////////////�浵//////////////////
	void Serialize(CArchive& ar);
	//////ȷ������(��Ӿ�������)����ֵ//////////
	void GetRect(float * m_Xmin,float * m_Ymin,float *m_Xmax,float *m_Ymax);
	/////////��ѡ////////////////
	bool IsPoint(CDC *pDC,float px,float py);
	///////////��ѡ///////////////////////////
	bool IsRect(CDC *pDC,CRect rect);

protected:

	//�ı���������
	float m_StartX;
	//���������
	float m_StartY;
	//��ע�Ƕ�
	float m_Angle;
	//����߶�
	float m_TextHeight;
	//������
	float m_TextWide;
	//��ϸ�̶�
	float m_FontWeight;
	//��ע���ı���Ϣ
	CString m_Text;
	//��ע��Ϣ�ĳ��� �ı��ַ����� 
	int m_TextLong;		   //�÷� :  m_TextLong= m_Text.GetLength();

};

#endif

