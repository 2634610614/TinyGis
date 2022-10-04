#include "StdAfx.h"
#include "Draw.h"


CDraw::CDraw(void)
{
}

//��6�������Ĺ��캯��
CDraw::CDraw(COLORREF m_ColorPen,COLORREF m_ColorBrush,short m_LineWide,short m_LineType,int m_id_only,BOOL b_Delete)
{
	this->m_ColorPen = m_ColorPen;
	this->m_ColorBrush = m_ColorBrush;
	this->m_LineWide = m_LineWide;
	this->m_LineType = m_LineType;
	this->m_id_only = m_id_only;
	this->b_Delete =b_Delete;
}
////////////////////////

CDraw::~CDraw(void)
{
}

 ///////��ȡID//////
int CDraw::GetID()
{
	return this->m_id_only;	//��Ϊ�����˽�еģ�ֻ���������ܵ��ó���
}


 ////////////�浵//////////////////
void CDraw::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		ar << this->b_Delete << this->m_ColorPen << this->m_ColorBrush << this->m_LineWide << this->m_LineType << this->m_id_only;
	}
	else
	{
		ar >> this->b_Delete >> this->m_ColorPen >> this->m_ColorBrush >> this->m_LineWide >> this->m_LineType >> this->m_id_only;
	}
}



///////////ɾ��ͼ��///////////////////
void CDraw::Delete(BOOL Is)
{
	if(Is)
	{
		this->b_Delete = TRUE;
	}
	else
	{
		this->b_Delete = FALSE;
	}
}
////////////�鿴�Ƿ�ɾ��/////////////
BOOL CDraw::IsDelete()
{
	return this->b_Delete;
}
