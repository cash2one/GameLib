#pragma once

#include "RobotGroup.h"
#include "afxwin.h"

// CDlgShowRobot �Ի���

class CRobotBtn;

class CDlgShowRobot : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowRobot)

public:
	typedef std_unordered_map<int, CRobotBtn *>	MapRobotButtonT;

public:
	CDlgShowRobot(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgShowRobot();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SHOW_ROBOT };
#endif

protected:
	virtual void		DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL		OnInitDialog();
	afx_msg void		OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	BOOL				Cleanup();
	void				SetScrollBarRange();
	BOOL				ClearRobotBtns();
	void				OnRobotBtnClicked(UINT nBtnID);
public:
	RobotGroup	*		GetCurRobotGroup() const { return m_pCurRobotGroup; }
	INT32				GetCurRobotTabIndex() const { return m_nCurRobotTabIndex; }
	void				SetCurRobotTabIndex(INT32 val) { m_nCurRobotTabIndex = val; }
	INT32				GetCurListCtrlIndex() const { return m_nCurListCtrlIndex; }
	void				SetCurListCtrlIndex(INT32 val) { m_nCurListCtrlIndex = val; }

public:
	void				OnCreateRobot(RobotGroup * pRobotGroup, Robot * pRobot);
	void				OnDeleteRobot(RobotGroup * pRobotGroup, Robot * pRobot);

protected:
	void				CreateRobotBtn(Robot * pRobot);

protected:
	CStatic				m_txtRobotPlatform;			// ��ʾ��ť��Ҫ��ô��ƽ̨.

	INT32				m_nBtnCount;
	INT32				m_nBtnTopLeftX;				//5 ������Ҫ���㰴ť���Ͻǵ�xλ��
	INT32				m_nBtnTopLeftY;				//5 ������Ҫ���㰴ť���Ͻǵ�yλ��
	INT32				m_nCurRobotTabIndex;		//5 ������������tab��Index�Ƕ�Ӧ��.
	INT32				m_nCurListCtrlIndex;		//5 ��ǰlist��ѡ�е����.
	RobotGroup		*	m_pCurRobotGroup;
	MapRobotButtonT		m_mapRobotBtns;

};
