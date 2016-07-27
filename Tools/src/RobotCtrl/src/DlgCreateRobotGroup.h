#pragma once


// CDlgCreateRobotGroup �Ի���

class CDlgShowRobot;

class CDlgCreateRobotGroup : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCreateRobotGroup)

public:
	CDlgCreateRobotGroup(CDlgShowRobot * pDlg, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCreateRobotGroup();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CREATE_ROBOT_GROUP };
#endif

protected:
	virtual void			DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void			OnBnClickedOk();
	afx_msg void			OnBnClickedCancel();
	DECLARE_MESSAGE_MAP()

public:
	UINT					m_editStartNum;
	UINT					m_editEndNum;
	CDlgShowRobot		*	m_pDlgShowRobot;
};
