
// RobotCtrlDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "DlgShowRobot.h"

class RobotServer;
class RobotGroup;

// CRobotCtrlDlg �Ի���
class CDlgRobotCtrl : public CDialogEx
{
// ����
public:
	CDlgRobotCtrl(CWnd* pParent = NULL);	// ��׼���캯��

public:

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROBOTCTRL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	
// ʵ��
protected:
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL		OnInitDialog();
	afx_msg void		OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void		OnPaint();
	afx_msg HCURSOR		OnQueryDragIcon();
	afx_msg void		OnTimer(UINT_PTR nIDEvent);
	afx_msg void		OnSelchangeListCtrlServer();
	afx_msg void		OnSelchangingTabShowRobot(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void		OnBnClickedStop();
	afx_msg void		OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:
	void				UpdateRobotTab(INT32 nIndex);
	void				UpdateCtrlServer(INT32 nIndex);
	void				OnCreateRobotGroup(RobotServer * pRobotServer, RobotGroup * pRobotGroup);
	void				OnDeleteRobotGroup(RobotServer * pRobotServer, RobotGroup * pRobotGroup);
	void				OnCreateRobotServer(RobotServer * pRobot);
	void				OnDeleteRobotServer(RobotServer * pRobot);

public:
	CDlgShowRobot	&	GetDlgCurShowRobot() { return m_dlgCurShowRobot; }
	INT32				GetCurRobotTabIndex() const { return m_nCurRobotTabIndex; }
	void				SetCurRobotTabIndex(INT32 val) { m_nCurRobotTabIndex = val; }
	INT32				GetCurListCtrlIndex() const { return m_nCurListCtrlIndex; }
	void				SetCurListCtrlIndex(INT32 val) { m_nCurListCtrlIndex = val; }

protected:
	void				InitShowRobotDlg();

protected:
	HICON				m_hIcon;
	CEdit				m_editRobotStartNum;
	CEdit				m_editRobotEndNum;
	CStatic				m_txtTotalRobotNum;
	CStatic				m_txtOnlineRobotNum;
	CStatic				m_txtOfflineRobotNum;
	CStatic				m_txtShowRobotStatue;
	CTabCtrl			m_tabShowRobots;
	CListBox			m_listCtrlServer;			//5 ��������̨��������ӵĻ����˵ĵ���
	CDlgShowRobot		m_dlgCurShowRobot;			//5 ��ʾ��ǰ������״̬��tabҳ

	INT32				m_nCurRobotTabIndex;		//5 ��ǰtabҳ��ʾ�����˵�tab index
	INT32				m_nShowRobotCount;			//5 ��ǰtabҳ������
	INT32				m_nCurListCtrlIndex;		//5 ��ǰlist��ѡ�е����.
};
