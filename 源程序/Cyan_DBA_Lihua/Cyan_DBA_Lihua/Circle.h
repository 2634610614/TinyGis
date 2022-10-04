#pragma once
#include "draw.h"
#include <math.h>




class CCircle :
	public CDraw
{
public:
	DECLARE_SERIAL (CCircle)
	CCircle(void);

	//���캯��
	CCircle(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,BOOL b_Delete,
			float m_CircleX,float m_CircleY,float m_CircleR,short m_Lb);
	/////////////����Բ/////////////////////
	void Draw(CDC *pDC,int Mode,int length = 0,int index =0);
	~CCircle(void);
	////////////�浵//////////////////
	void Serialize(CArchive& ar);
	//////ȷ����Ӿ����������ֵ//////////
	void GetRect(float * m_Xmin,float * m_Ymin,float *m_Xmax,float *m_Ymax);
	///////////��ѡ ///////////////////////////
	bool IsPoint(CDC *pDC,float px,float py);
	///////////��ѡ///////////////////////////
	bool IsRect(CDC *pDC,CRect rect);
protected:
	//Բ������(X,Y)
	float m_CircleX ,m_CircleY;
	//�뾶
	float m_CircleR;
	//���
	short m_Lb;
};

