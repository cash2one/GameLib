#pragma once


// CDlgRobotCommand �Ի���

class CDlgRobotCommand : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRobotCommand)

public:
	CDlgRobotCommand(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgRobotCommand();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ROBOT_COMMAND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
