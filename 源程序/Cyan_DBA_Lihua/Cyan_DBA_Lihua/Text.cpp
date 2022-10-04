#include "StdAfx.h"
#include "Text.h"
#include "Draw.h"
IMPLEMENT_SERIAL (CText,CObject,1)
CText::CText(void)
{
}
 //	float m_StartX,float m_StartY ,m_TextHeight,m_TextWide,m_FontWeight  ����ʱΪʵ��(����)����
CText::CText(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,BOOL b_Delete,
			float m_StartX,float m_StartY,float m_Angle,float m_TextHeight,float m_TextWide,float m_FontWeight,CString m_Text): CDraw(m_ColorPen,m_ColorBrush,m_LineWide,m_LineType,m_id_only,b_Delete)
{
	this->m_StartX = m_StartX;
	this->m_StartY = m_StartY;
	this->m_Angle = m_Angle;
	this->m_TextHeight = m_TextHeight;
	this->m_TextWide = m_TextWide;
	this->m_FontWeight = m_FontWeight;
	this->m_TextLong = m_Text.GetLength();			//��ȡ��ע��Ϣ�ĳ���
	this->m_Text = m_Text;
	
}


CText::~CText(void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//////��������///////////
void CText::Draw(CDC *pDC,int Mode,int length,int index)
{
	if(this->b_Delete)
	{
		return ;
	}
	//�趨���ǵĻ���ģʽ
	pDC->SetROP2(R2_COPYPEN);
	//�������ֵı���Ϊ��	/��͸��
	pDC->SetBkMode(TRANSPARENT);
	CFont myFont; //����һ������ģ��
	int high,wide,weight,x,y,angleText;	//ת����10���Ƕȷ��㴫��
	float x1,y1,angleLine;
	//if(high<3||high>200) return;	//����̫���̫С����ʾ
	high = DLtoVL(this->m_TextHeight);
	wide = DLtoVL(this->m_TextWide)/2;
	weight = DLtoVL(this->m_FontWeight);
	angleLine = (float)(this->m_Angle*pi/180);	//ת���ɻ���
	////���λ��Ϊ���½�ʵ������//////////////
	//�ȱ�����Ͻǣ�Ȼ�����ʵ��ת�߼�
	x1 = this->m_StartX - this->m_TextHeight*(float)sin(angleLine);
	y1 = this->m_StartY + this->m_TextHeight*(float)cos(angleLine);
	/////////////�߼������������ڲ�����ת��,��бת����/////
	angleText = (int)(this->m_Angle*10);
	//wide =this->m_TextWide;
	//x0 =x1;
	//y0 =y1;
	/////////��������ת����ʵ��ת�߼�///////////	
	DPtoVP(x1,y1,&x,&y);			  //����ת��
	///////////////////////////////


	myFont.CreateFont(high,wide,angleText,0,weight,0,0,0,1,OUT_TT_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,FIXED_PITCH,_T("myfont"));
	CFont* font = pDC->SelectObject(&myFont);
	if(Mode ==1)
	{
		pDC->SetBkMode(OPAQUE);		//����
		pDC->SetBkColor(RGB(0,191,255));	//����ɫ     //����ɫRGB(0,191,255)
	}
	pDC->SetTextColor(this->m_ColorPen);
	pDC->TextOutW(x,y,this->m_Text);	//x,y���������Ͻǵĵ�
	pDC->SelectObject(font);	//�ָ�����ģ��


}

//////ȷ������(��Ӿ�������)����ֵ//////////
void CText::GetRect(float* m_Xmin,float* m_Ymin,float* m_Xmax,float* m_Ymax)
{
	 float x[4],y[4];
	 double angle = this->m_Angle* pi /180;
	 x[0] = this->m_StartX;
	 y[0] = this->m_StartY;
	 x[1] = this->m_StartX + this->m_TextWide*this->m_TextLong*(float)cos(angle);
	 y[1] = this->m_StartY + this->m_TextWide*this->m_TextLong*(float)sin(angle);
	 x[2] =	x[1] - this->m_TextHeight*(float)sin(angle); 
	 y[2] =	y[1] + this->m_TextHeight*(float)cos(angle);
	 x[3] = this->m_StartX - this->m_TextHeight*(float)sin(angle);
	 y[3] =	this->m_StartY + this->m_TextHeight*(float)cos(angle);
	 *m_Xmin = FLT_MAX;		//��С�ĸ����ֵ
	 *m_Ymin = FLT_MAX;
	 *m_Xmax = FLT_MIN;		//���ĸ���Сֵ
	 *m_Ymax = FLT_MIN;
	 for(int i =0;i<4;++i)
	 {
		//��ȡ��С����
		*m_Xmin =min(*m_Xmin,x[i]);
		*m_Ymin =min(*m_Ymin,y[i]);
		//��ȡ�������
		*m_Xmax =max(*m_Xmax,x[i]);
		*m_Ymax =max(*m_Ymax,y[i]);

	 }
}



////////////�浵//////////////////
void CText::Serialize(CArchive& ar)
{
	CDraw::Serialize( ar );
	if(ar.IsStoring())
	{
		ar << m_StartX << m_StartY << m_Angle << m_TextHeight << m_TextWide<< m_FontWeight << m_Text;
	}else
	{
		ar >> m_StartX >> m_StartY >> m_Angle >> m_TextHeight >> m_TextWide>> m_FontWeight >> m_Text;
	}
}



//////////��ѡ////////////////
bool CText::IsPoint(CDC *pDC,float px,float py)
{
	if(this->b_Delete)
	{
		return FALSE;
	}
	CRgn rgn;
	float x1,y1,x2,y2;
	int x3,y3,x4,y4;
	int i ;
	GetRect(&x1,&y1,&x2,&y2);
	DPtoVP(x1,y1,&x3,&y3);
	DPtoVP(x2,y2,&x4,&y4);
	rgn.CreateRectRgn(x3,y3,x4,y4);
	i = rgn.PtInRegion(px,py);
	rgn.DeleteObject();
	return i;
}


///////////��ѡ///////////////////////////
bool CText::IsRect(CDC *pDC,CRect rect)
{
   if(this->b_Delete)
	{
		return FALSE;
	}
	CRgn rgn;
	float x1,y1,x2,y2;
	int x3,y3,x4,y4;
	int i ;
	GetRect(&x1,&y1,&x2,&y2);
	DPtoVP(x1,y1,&x3,&y3);
	DPtoVP(x2,y2,&x4,&y4);
	rgn.CreateRectRgn(x3,y3,x4,y4);
	i=rgn.RectInRegion(&rect);	
	rgn.DeleteObject();
	return i;
}



