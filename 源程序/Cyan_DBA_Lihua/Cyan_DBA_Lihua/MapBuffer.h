#pragma once


// MapBuffer �Ի���

class MapBuffer : public CDialogEx
{
	DECLARE_DYNAMIC(MapBuffer)

public:
	MapBuffer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MapBuffer();

// �Ի�������
	enum { IDD = IDD_BufferSet };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ����������
	CString bufferLong;
	// ����
	CString bufferNumber;
};
