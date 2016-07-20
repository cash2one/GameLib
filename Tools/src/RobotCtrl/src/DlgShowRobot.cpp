// DlgShowRobot.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RobotCtrl.h"
#include "DlgShowRobot.h"
#include "afxdialogex.h"
#include "RobotBtn.h"
#include "DlgRobotCtrl.h"

// CDlgShowRobot �Ի���

IMPLEMENT_DYNAMIC(CDlgShowRobot, CDialogEx)

INT32 GetXBtnNum(CRect rect)
{
	INT32 nXNumber = (rect.BottomRight().x - rect.TopLeft().x) / (cnBtnXLengthSpace + cnBtnXLength);
	return nXNumber;
}

INT32 GetYBtnNum(CRect rect)
{
	INT32 nYNumber = (rect.BottomRight().y - rect.TopLeft().y) / (cnBtnYLengthSpace + cnBtnYLength);
	return nYNumber;
}


BEGIN_MESSAGE_MAP(CDlgShowRobot, CDialogEx)
	ON_WM_VSCROLL()
	ON_WM_CREATE()
//	ON_COMMAND_RANGE(cst_btn_id, cst_btn_id + cst_max_btn_id, OnRobotBtnClicked)     //��Ӧ�Ǹ�����ID����10000��10000 + �����Ǹ�
ON_WM_SIZE()
END_MESSAGE_MAP()

CDlgShowRobot::CDlgShowRobot(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_SHOW_ROBOT, pParent)
	, m_nCurRobotTabIndex(-1)
	, m_nCurListCtrlIndex(-1)
	, m_nBtnCount(0)
	, m_nBtnTopLeftX(0)
	, m_nBtnTopLeftY(0)
	, m_pCurRobotGroup(NULL)
	, m_nCreateBtnIndex(0)
{

}

CDlgShowRobot::~CDlgShowRobot()
{
	ClearRobotBtns();
}

BOOL CDlgShowRobot::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
void CDlgShowRobot::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ROBOT_BASE, m_txtRobotPlatform);
}

void CDlgShowRobot::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	INT32 btnLineSize = cnBtnYLength + cnBtnYLengthSpace + cnBtnYLengthSpace;

	SCROLLINFO si;
	GetScrollInfo(SB_VERT, &si);//��ȡ��������Ϣ��SB_VERTָ��ֱ���������Ի���Ĺ���������һ���ؼ������Ի�����һ��ģ��ٿؼ�
	int nMaxPos = si.nMax - si.nPage;//�ɹ�����Χ���ֵ

	INT32 scrValue = 0;//����ֵ
	switch (nSBCode)
	{
	case SB_LINEUP://�ϰ�ť��������һ��
		if (si.nPos != 0)
		{
			if (si.nPos - btnLineSize < 0)
				scrValue = si.nPos;
			else
				scrValue = btnLineSize;
		}
		break;
	case SB_LINEDOWN://�°�ť��������һ��
		if (si.nPos != nMaxPos)
		{
			scrValue = nMaxPos - si.nPos;
			if (scrValue < btnLineSize)
				scrValue = -scrValue;
			else
				scrValue = -btnLineSize;
		}
		break;
	case SB_PAGEUP: //��������ͨ����������һ��
		if (si.nPos != 0)
		{
			if (si.nPos - si.nPage < 0)//�ɹ������ز���si.nPage
				scrValue = si.nPos;
			else
				scrValue = si.nPage;
		}
		break;
	case SB_PAGEDOWN://��������ͨ����������һ��
		if (si.nPos != nMaxPos)
		{
			scrValue = nMaxPos - si.nPos;
			if (scrValue < (INT32)si.nPage) //�ɹ������ز���si.nPage
				scrValue = -scrValue;
			else
				scrValue = -(INT32)(si.nPage);
		}
		break;
	case SB_THUMBTRACK: //�϶�������������nPos����λ��
		scrValue = si.nPos - nPos;
		break;
	}

// 	if (nMaxPos == nPos)
// 	{
// 		const INT32 cnLastLineSpace = 10;			//5 ���һ����ʾ���Ż�����
// 		scrValue = si.nPos - nPos - cnLastLineSpace;
// 	}
	SetScrollPos(SB_VERT, si.nPos - scrValue);//���ù�����λ��
	ScrollWindow(0, scrValue);//��������

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


int CDlgShowRobot::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}


void CDlgShowRobot::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

	ChangeDlgSize();
}


// CDlgShowRobot ��Ϣ�������

void CDlgShowRobot::SetScrollBarRange()
{
	CRect rect;
	GetClientRect(rect);
	INT32 nXNumber = GetXBtnNum(rect);
//	INT32 nYNumber = GetYBtnNum(rect);

	int nPos = GetScrollPos(SBS_VERT);

	SCROLLINFO si;
	si.nMin		= 0;
	si.nMax		= (m_nBtnCount / nXNumber + 1) * (cnBtnYLengthSpace + cnBtnYLength);
	si.nPage	= rect.Height();//�ɼ����ڸ߶Ⱥ�ҳ��С����һ��
	si.nPos		= nPos;
	si.fMask	= SIF_ALL;
	si.cbSize	= sizeof(SCROLLINFO);
	SetScrollInfo(SBS_VERT, &si);
}

void CDlgShowRobot::ChangeDlgSize()
{
	const int cst_tab_space = 0;
	const int cst_scroll_space = 0;

	//5 ������Ҫ�ı�����Ի����ڲ��ؼ��Ű�ť�Ĵ�С
	CRect rect;
	GetClientRect(rect);
	INT32 nXNumber = GetXBtnNum(rect);
	if (GetDlgItem(IDC_STATIC_ROBOT_BASE))
	{
		GetDlgItem(IDC_STATIC_ROBOT_BASE)->MoveWindow(CRect(rect.TopLeft().x, rect.TopLeft().y + cst_tab_space,
			rect.BottomRight().x - cst_scroll_space, (MAX_ROBOT_BTN_NUM / nXNumber + 1) * (cnBtnYLengthSpace + cnBtnYLength)));
	}
	SetScrollBarRange();
}

void CDlgShowRobot::CreateRobotBtns()
{
	for (INT32 i = 0;i < MAX_ROBOT_BTN_NUM; ++i)
	{
		CreateRobotBtn();
	}
}

BOOL CDlgShowRobot::ClearRobotBtns()
{
	MapRobotBtnT::iterator iter = m_mapRobotBtns.begin();
	for (;iter != m_mapRobotBtns.end();++iter)
	{
		iter->second->DestroyWindow();
		delete iter->second;
	}
	m_mapRobotBtns.clear();

	return TRUE;
}

BOOL CDlgShowRobot::ShowRobotBtns(BOOL bShow/* = FALSE*/)
{
	MapRobotBtnT::iterator iter = m_mapRobotBtns.begin();
	for (; iter != m_mapRobotBtns.end(); ++iter)
	{
		iter->second->ShowWindow(bShow);
	}
	m_mapRobot2BtnIndex.clear();

	m_txtRobotPlatform.Invalidate(TRUE);
	return TRUE;
}

BOOL CDlgShowRobot::ShowRobotBtn(INT32 nIndex, BOOL bShow/* = FALSE*/)
{
	MapRobotBtnT::iterator iter = m_mapRobotBtns.find(nIndex);
	if (iter != m_mapRobotBtns.end())
	{
		iter->second->ShowWindow(bShow);
	}

	SetScrollBarRange();
	return TRUE;
}

void CDlgShowRobot::ShowRobotBtn(CRobot * pRobot)
{
	if (m_nBtnCount < m_nCreateBtnIndex)
	{
		CRobotBtn * pBtn = m_mapRobotBtns[m_nBtnCount];
		if (pBtn)
		{
			pBtn->SetRobot(pRobot);
			pBtn->SetRobotIndex(pRobot->GetRobotIndex());
			pBtn->ShowWindow(TRUE);
			pBtn->Invalidate(TRUE);
			m_mapRobot2BtnIndex.insert(std::make_pair(pRobot->GetRobotIndex(), pBtn->GetRobotIndex()));
			++m_nBtnCount;
		}
	}
	else
	{
		gErrorStream("ShowRobotBtn error. cur btn count=" << m_nBtnCount << " max btn count=" << m_nCreateBtnIndex);
	}

	SetScrollBarRange();
}

BOOL CDlgShowRobot::InitDialog()
{
	ChangeDlgSize();
	CreateRobotBtns();			//5 ��ʼ���ȴ��������еİ�ť.����ͨ������������.

	return TRUE;
}

BOOL CDlgShowRobot::Init(RobotGroup * pRobotGroup /*= NULL*/)
{
	ShowRobotBtns(FALSE);

	if (pRobotGroup)
	{
		RobotGroup::MapRobots mapRobots = pRobotGroup->GetMapRobots();
		RobotGroup::MapRobots::const_iterator iter = mapRobots.begin();
		for (; iter != mapRobots.end(); ++iter)
		{
			ShowRobotBtn(iter->second);
		}
	}

	m_pCurRobotGroup = pRobotGroup;

	return TRUE;
}

BOOL CDlgShowRobot::Cleanup()
{
	ShowRobotBtns(FALSE);

	m_nBtnCount			= 0;
	m_nBtnTopLeftX		= 0;
	m_nBtnTopLeftY		= 0;
	m_pCurRobotGroup	= NULL;
	m_nCurRobotTabIndex = -1;

	SetScrollPos(SBS_VERT, 0);
	SetScrollRange(SBS_VERT, 0, 0);

	SetScrollBarRange();
	return TRUE;
}

void CDlgShowRobot::OnRobotBtnClicked(UINT nBtnID)
{

	MessageBox("����ɹ�.");
}

void CDlgShowRobot::SetCurRobotTab(INT32 nIndex, RobotGroup * pRobot)
{
	if (nIndex != m_nCurRobotTabIndex)
	{
		Cleanup();
		if (nIndex != -1)
		{ 
			m_nCurRobotTabIndex = nIndex;
			Init(pRobot);
		}
	}
}

void CDlgShowRobot::OnCreateRobot(RobotGroup * pRobotGroup, CRobot * pRobot)
{
	CDlgRobotCtrl * pRobotDlg = dynamic_cast<CDlgRobotCtrl*>(theApp.m_pMainWnd);
	if (pRobotDlg)
	{
		if (m_nCurRobotTabIndex == pRobotDlg->GetCurRobotTabIndex() &&
			m_nCurListCtrlIndex == pRobotDlg->GetCurListCtrlIndex() &&
			m_pCurRobotGroup != NULL)
		{
			ShowRobotBtn(pRobot);
		}
	}
}

void CDlgShowRobot::OnDeleteRobot(RobotGroup * pRobotGroup, CRobot * pRobot)
{

}

void CDlgShowRobot::CreateRobotBtn()
{
	m_nBtnTopLeftX += cnBtnXLength + cnBtnXLengthSpace;	//5�������Ͻ�X��λ��.��Ҫ����btn�ĳ��Ⱥ�btn֮��ļ�϶

	CRect rect;
	this->GetClientRect(&rect);
	if (m_nBtnTopLeftX > rect.BottomRight().x)
	{
		m_nBtnTopLeftX = cnBtnXLength + cnBtnXLengthSpace;
		m_nBtnTopLeftY += cnBtnYLength + cnBtnYLengthSpace;
	}

	CRobotBtn * pBtn = new CRobotBtn(NULL);
	CRect pos = CRect(m_nBtnTopLeftX - cnBtnXLength
		, m_nBtnTopLeftY + cnBtnYLengthSpace + rect.top, m_nBtnTopLeftX
		, m_nBtnTopLeftY + cnBtnYLength + cnBtnYLengthSpace + rect.top);
	pBtn->SetRectPos(pos);
	pBtn->SetRobotIndex(-1);

	CString str;
	str.Format("%s", "None");
	pBtn->Create(str, WS_CHILD /*| WS_VISIBLE */| BS_NOTIFY | BS_3STATE,
		pos, &m_txtRobotPlatform, cst_btn_id + m_nCreateBtnIndex); 

	m_mapRobotBtns.insert(std::make_pair(m_nCreateBtnIndex, pBtn));
	++m_nCreateBtnIndex;
}

/*
void CDlgShowRobot::CreateRobotBtn(Robot * pRobot)
{
	INT32 nIndex = pRobot->GetRobotIndex();

	m_nBtnTopLeftX += cnBtnXLength + cnBtnXLengthSpace;	//5�������Ͻ�X��λ��.��Ҫ����btn�ĳ��Ⱥ�btn֮��ļ�϶

	CRect rect;
	this->GetClientRect(&rect);
	if (m_nBtnTopLeftX > rect.BottomRight().x)
	{
		m_nBtnTopLeftX = cnBtnXLength + cnBtnXLengthSpace;
		m_nBtnTopLeftY += cnBtnYLength + cnBtnYLengthSpace;
	}

	CRobotBtn * pBtn = new CRobotBtn(pRobot);
	CRect pos = CRect(m_nBtnTopLeftX - cnBtnXLength
		, m_nBtnTopLeftY + cnBtnYLengthSpace + rect.top, m_nBtnTopLeftX
		, m_nBtnTopLeftY + cnBtnYLength + cnBtnYLengthSpace + rect.top);
	pBtn->SetRectPos(pos);
	pBtn->SetRobotIndex(nIndex);

	CString str;
	str.Format("%s", pRobot->GetName().c_str());
	pBtn->Create(str, WS_CHILD | BS_DEFPUSHBUTTON | WS_VISIBLE | BS_NOTIFY | BS_3STATE,
		pos, &m_txtRobotPlatform, cst_btn_id + nIndex);

	m_mapRobotBtns.insert(std::make_pair(nIndex, pBtn));
	++m_nBtnCount;
}
*/


