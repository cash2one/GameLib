#pragma once

#include "RobotGroup.h"
#include "afxwin.h"
#include "afxcmn.h"
#include <string>

// CDlgShowRobot �Ի���

class CRobotBtn;

using namespace Robot;
namespace Robot
{
	class CRobot;
}

class CDlgShowRobot : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowRobot)

public:
	typedef std_unordered_map<INT32, CRobotBtn *>	MapRobotBtnT;
	typedef std_unordered_map<INT32, INT32>			MapRobot2ViewIndexT;	//5 �����Ӧ����,�Ϳ���ͨ��Btn�ҵ�RobotIndex��.

public:
	enum EListColType
	{
		LIST_START = 0,
		LIST_NAME = 0,
		LIST_PROF,
		LIST_LEVEL,
		LIST_STATUE,
		LIST_NOTE,

		LIST_NUM
	};
	const std::string cAStrListName[LIST_NUM] =
	{
		"����",
		"ְҵ",
		"�ȼ�",
		"״̬",
		"��ע",
	};
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

public:
	void				OnCreateRobot(RobotGroup * pRobotGroup, CRobot * pRobot);
	void				OnDeleteRobot(RobotGroup * pRobotGroup, CRobot * pRobot);

public:
	RobotGroup	*		GetCurRobotGroup() const { return m_pCurRobotGroup; }
	void				SetCurRobotTab(INT32 val, RobotGroup * pRobot);
	INT32				GetCurRobotTabIndex() const { return m_nCurRobotTabIndex; }
	INT32				GetCurListCtrlIndex() const { return m_nCurListCtrlIndex; }
	void				SetCurListCtrlIndex(INT32 val) { m_nCurListCtrlIndex = val; }

protected:
	BOOL				InsertRobotList(RobotGroup * pRobotGroup, CRobot * pRobot);
	void				InitListCtrl();

protected://5 ���������԰�ť�Ĺ���,��ʱȥ��.
	void				ShowRobotBtn(CRobot * pRobot);
	BOOL				ClearRobotBtns();
	void				SetScrollBarRange();
	void				ChangeDlgSize();
	void				CreateRobotBtn();
	void				CreateRobotBtns();
	BOOL				ShowRobotBtns(BOOL bShow = FALSE);
	BOOL				ShowRobotBtn(INT32 nIndex, BOOL bShow/* = FALSE*/);
	void				OnRobotBtnClicked(UINT nBtnID);
	BOOL				InsertRobot2ViewIndex(INT32 nRobotIndex , INT32 nViewIndex, std::string strName="");

protected:
	CListCtrl			m_listShowRobots;

	RobotGroup		*	m_pCurRobotGroup;
	INT32				m_nCurRobotTabIndex;		//5 ������������tab��Index�Ƕ�Ӧ��.
	INT32				m_nCurListCtrlIndex;		//5 ��ǰRobotCtrl�е�list�ؼ�ѡ�е����.
	MapRobot2ViewIndexT	m_mapRobot2ViewIndex;		//5 ����������Index��Ӧ��ViewIndex.
	INT32				m_nRobotCount;				//5 �����¼���ǵ�ǰRobotGroup��Ӧ���е�Btn����.

protected://5 ���������԰�ť��,��ʱȥ��.
	CStatic				m_txtRobotPlatform;			// ��ʾ��ť��Ҫ��ô��ƽ̨.
	INT32				m_nBtnCount;				//5 �����¼���ǵ�ǰRobotGroup��Ӧ���е�Btn����.
	INT32				m_nCreateBtnIndex;			//5 ���������һ�δ���Btn��ʱ����������Index��.ֻ�ڵ�һ������..
	INT32				m_nBtnTopLeftX;				//5 ������Ҫ���㰴ť���Ͻǵ�xλ��
	INT32				m_nBtnTopLeftY;				//5 ������Ҫ���㰴ť���Ͻǵ�yλ��
	MapRobotBtnT		m_mapRobotBtns;
public:
	afx_msg void OnSendRobotCommand();
	afx_msg void OnNMRClickListShowRobot(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCreateRobots();
};
