#pragma once


// CDlgShowRobot �Ի���

class CDlgShowRobot : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowRobot)

public:
	CDlgShowRobot(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgShowRobot();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SHOW_ROBOT };
#endif

public:
	INT32				GetCurRobotIndex() const { return m_nCurRobotIndex; }
	void				SetCurRobotIndex(INT32 val);

protected:
	virtual void		DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

protected:
	INT32				m_nCurRobotIndex;			//5 ������������tab��Index�Ƕ�Ӧ��.
};
