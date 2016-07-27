#pragma once
#include "afxwin.h"
#include "RobotCommon.h"
#include "RobotCommand.h"

// CDlgRobotCommand �Ի���

class CDlgRobotCommand : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRobotCommand)

public:
	typedef std::map<INT32, INT32>			MapIndexToConfigIndex;
	typedef std::map<INT32, INT32>			MapRobotParamType;

public:
	CDlgRobotCommand(CDlgShowRobot * pDlg , CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgRobotCommand();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ROBOT_COMMAND };
#endif

protected:
	afx_msg void			OnBnClickedOk();
	afx_msg void			OnBnClickedCancel();
	virtual BOOL			OnInitDialog();
	afx_msg void			OnCbnSelchangeComboSelectCommand();
	virtual void			DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()

public:
	BOOL					InitDialog();
	void					ShowDlgCtrls(INT32 nCount, BOOL bShow = FALSE);
	
protected:
	CStatic					m_txtCommandType[cnCommandParamCount];	//5 IDC_COMMAND_TXT1��Ҫ��֤���ǵ�Index����������.
	CStatic					m_txtCommandNote[cnCommandParamCount];
	CEdit					m_editCommandValue[cnCommandParamCount];
	CComboBox				m_cobSelectCommand;
	MapIndexToConfigIndex	m_mapIndex2ConfigIndex;
	INT32					m_nCurParamsCount;
	MapRobotParamType		m_mapRobotParamType;
	CDlgShowRobot		*	m_pDlgShowRobot;

};
