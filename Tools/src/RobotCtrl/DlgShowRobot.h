#pragma once

#include "RobotGroup.h"
#include "afxwin.h"

// CDlgShowRobot �Ի���

class CRobotBtn;

class CDlgShowRobot : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowRobot)

public:
	typedef std_unordered_map<INT32, CRobotBtn *>	MapRobotBtnT;
	typedef std_unordered_map<INT32, INT32>			MapRobot2BtnIndexT;	//5 �����Ӧ����,�Ϳ���ͨ��Btn�ҵ�RobotIndex��.

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
	afx_msg void		OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

public:
	BOOL				InitDialog();				//5 ����ǽ���Ի������OnInitDialog�Ⱥ�����.
	BOOL				Init(RobotGroup * pRobotGroup = NULL);
	BOOL				Cleanup();
	void				OnRobotBtnClicked(UINT nBtnID);
	BOOL				ShowRobotBtns(BOOL bShow = FALSE);
	BOOL				ShowRobotBtn(INT32 nIndex, BOOL bShow/* = FALSE*/);

public:
	void				OnCreateRobot(RobotGroup * pRobotGroup, Robot * pRobot);
	void				OnDeleteRobot(RobotGroup * pRobotGroup, Robot * pRobot);

public:
	RobotGroup	*		GetCurRobotGroup() const { return m_pCurRobotGroup; }
	void				SetCurRobotTab(INT32 val, RobotGroup * pRobot);
	INT32				GetCurRobotTabIndex() const { return m_nCurRobotTabIndex; }
	INT32				GetCurListCtrlIndex() const { return m_nCurListCtrlIndex; }
	void				SetCurListCtrlIndex(INT32 val) { m_nCurListCtrlIndex = val; }

protected:
	void				CreateRobotBtns();
	void				CreateRobotBtn();
	void				ShowRobotBtn(Robot * pRobot);
	BOOL				ClearRobotBtns();
	void				SetScrollBarRange();
	void				ChangeDlgSize();

protected:
	CStatic				m_txtRobotPlatform;			// ��ʾ��ť��Ҫ��ô��ƽ̨.

	INT32				m_nBtnCount;				//5 �����¼���ǵ�ǰRobotGroup��Ӧ���е�Btn����.
	INT32				m_nCreateBtnIndex;			//5 ���������һ�δ���Btn��ʱ����������Index��.ֻ�ڵ�һ������..
	INT32				m_nBtnTopLeftX;				//5 ������Ҫ���㰴ť���Ͻǵ�xλ��
	INT32				m_nBtnTopLeftY;				//5 ������Ҫ���㰴ť���Ͻǵ�yλ��
	INT32				m_nCurRobotTabIndex;		//5 ������������tab��Index�Ƕ�Ӧ��.
	INT32				m_nCurListCtrlIndex;		//5 ��ǰlist��ѡ�е����.
	RobotGroup		*	m_pCurRobotGroup;
	MapRobotBtnT		m_mapRobotBtns;
	MapRobot2BtnIndexT	m_mapRobot2BtnIndex;		//5 ����������Index��Ӧ��BtnIndex.

};
