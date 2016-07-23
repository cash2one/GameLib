
// RobotCtrlDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "DlgShowRobot.h"
#include "ListBoxEx.h"

using namespace Robot;
namespace Robot
{
	class RobotServer;
	class RobotGroup;
}

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
public:
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
	afx_msg void		OnClose();
	afx_msg void		OnRBtnListServer();
	DECLARE_MESSAGE_MAP()

public:
	void				UpdateRobotTab(INT32 nIndex);
	void				UpdateCtrlServer(INT32 nIndex);
	void				OnCreateRobotGroup(RobotServer * pRobotServer, RobotGroup * pRobotGroup , BOOL bUpdate = FALSE);
	void				OnDeleteRobotGroup(RobotServer * pRobotServer, RobotGroup * pRobotGroup);
	void				OnCreateRobotServer(RobotServer * pRobot);
	void				OnDeleteRobotServer(RobotServer * pRobot);

public:
	CDlgShowRobot	&	GetDlgCurShowRobot() { return m_dlgCurShowRobot; }
	INT32				GetCurRobotTabIndex() const { return m_nCurRobotTabIndex; }
	INT32				GetCurListCtrlIndex() const { return m_nCurListCtrlIndex; }

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
	CListBoxEx			m_listCtrlServer;			//5 ��������̨��������ӵĻ����˵ĵ���
	CDlgShowRobot		m_dlgCurShowRobot;			//5 ��ʾ��ǰ������״̬��tabҳ

	INT32				m_nCurRobotTabIndex;		//5 ��ǰtabҳ��ʾ�����˵�tab index
	INT32				m_nShowRobotCount;			//5 ��ǰtabҳ������
	INT32				m_nCurListCtrlIndex;		//5 ��ǰlist��ѡ�е����.
public:
	afx_msg void OnTcnSelchangeTabShowRobot(NMHDR *pNMHDR, LRESULT *pResult);
};
