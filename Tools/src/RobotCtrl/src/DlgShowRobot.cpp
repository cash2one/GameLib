// DlgShowRobot.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RobotCtrl.h"
#include "DlgShowRobot.h"
#include "afxdialogex.h"
#include "RobotBtn.h"
#include "DlgRobotCtrl.h"
#include "RPCCallFuncs.h"
#include "DlgRobotCommand.h"

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
ON_COMMAND(ID_SEND_ROBOT_COMMAND, &CDlgShowRobot::OnSendRobotCommand)
ON_NOTIFY(NM_RCLICK, IDC_LIST_SHOW_ROBOT, &CDlgShowRobot::OnNMRClickListShowRobot)
ON_COMMAND(ID_CREATE_ROBOTS, &CDlgShowRobot::OnCreateRobots)
ON_COMMAND(ID_CLOSE_GROUP, &CDlgShowRobot::OnCloseGroup)
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
	, m_nRobotCount(0)
	, m_dlgRobotCommand(this)
{

}

CDlgShowRobot::~CDlgShowRobot()
{
 	ClearRobotBtns();
}

BOOL CDlgShowRobot::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	 
// 	m_dlgRobotCommand.Create(IDD_DLG_ROBOT_COMMAND, this);//������ģʽ�Ի�����ʾͼƬ
// 	m_dlgRobotCommand.SetParent(this);
// 	m_dlgRobotCommand.ShowWindow(SW_HIDE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
void CDlgShowRobot::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ROBOT_BASE, m_txtRobotPlatform);
	DDX_Control(pDX, IDC_LIST_SHOW_ROBOT, m_listShowRobots);
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
	//5 ������Ҫ�ı�����Ի����ڲ��ؼ��Ű�ť�Ĵ�С//5 ��ʱ���ð�ť��ʾͨ��list����.
	const int cst_tab_space = 0;
	const int cst_scroll_space = 0;
	CRect rect;
	GetClientRect(rect);
	INT32 nXNumber = GetXBtnNum(rect);
	if (GetDlgItem(IDC_STATIC_ROBOT_BASE))
	{
		GetDlgItem(IDC_STATIC_ROBOT_BASE)->MoveWindow(CRect(rect.TopLeft().x, rect.TopLeft().y + cst_tab_space,
			rect.BottomRight().x - cst_scroll_space, (cnMaxRobotBtnNum / nXNumber + 1) * (cnBtnYLengthSpace + cnBtnYLength)));

		GetDlgItem(IDC_STATIC_ROBOT_BASE)->ShowWindow(FALSE);
		SetScrollBarRange();
	}

	//5 List�ؼ����Ĵ�С
	if (GetDlgItem(IDC_LIST_SHOW_ROBOT))
	{
		GetDlgItem(IDC_LIST_SHOW_ROBOT)->MoveWindow(CRect(rect.TopLeft().x, rect.TopLeft().y + cst_tab_space,
			rect.BottomRight().x, rect.BottomRight().y));
	}
}


BOOL CDlgShowRobot::InsertRobotList(RobotGroup * pRobotGroup, CRobot * pRobot)
{
	if (pRobot)
	{
		std::string str;
		INT32 nItem = m_listShowRobots.InsertItem(m_listShowRobots.GetItemCount(), "");
		for (INT32 i = 0;i < LIST_NUM;++i)
		{
			switch (i)
			{
			case LIST_NAME:
			{
				str = (char*)(pRobot->GetRobotInfo().strName.c_str());
			}break;
			case LIST_PROF:
			{
				str = CUtil::itoa(pRobot->GetRobotInfo().nProf).c_str();
			}break;
			case LIST_LEVEL:
			{
				str = CUtil::itoa(pRobot->GetRobotInfo().nLevel).c_str();
			}break;
			case LIST_STATUE:
			{
				str = CUtil::itoa(pRobot->GetRobotInfo().nStatue).c_str();
			}break;
			case LIST_NOTE:
			{
				str = (char*)(pRobot->GetRobotInfo().strNote.c_str());
			}break;
			default:
				break;
			}
			m_listShowRobots.SetItemText(nItem, i, str.c_str());
		}
		pRobot->SetListCtrlIndex(nItem);
		m_listShowRobots.SetItemData(nItem, (DWORD_PTR)pRobot);
//		InsertRobot2ViewIndex(pRobot->GetPeerRobotID() , nItem);
	}
// 	else
// 	{
// 		char * pName = "123123";
// 		LVITEM lvItem;
// 		lvItem.mask = LVIF_TEXT | LVIF_STATE;
// 		lvItem.iItem = 0;
// 		lvItem.iSubItem = 0;
// 		lvItem.pszText = pName;
// 		lvItem.lParam = (LPARAM)pRobot;
// 		INT32 nItem = m_listShowRobots.InsertItem(&lvItem);
// 
// 		m_listShowRobots.SetItemText(nItem, 0, pName);
// 
// 	}

	return TRUE;
}

void CDlgShowRobot::InitListCtrl()
{
	CRect rect;
	GetClientRect(rect);
	INT32 nDlgWidth = rect.right - rect.left;
	float fWidthRatio = (float)nDlgWidth / (float)cnMinRobotDlgWidth;

	INT32 nCount = LIST_START;
	LVCOLUMN lvColumn;

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_CENTER;
	lvColumn.cx = (INT32)(cnColumnWidth * fWidthRatio);
	lvColumn.pszText = (char *)(cAStrListName[nCount].c_str());
	this->m_listShowRobots.InsertColumn(nCount++, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_CENTER;
	lvColumn.cx = (INT32)(cnColumnWidth * fWidthRatio);
	lvColumn.pszText = (char *)(cAStrListName[nCount].c_str());
	this->m_listShowRobots.InsertColumn(nCount++, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_CENTER;
	lvColumn.cx = (INT32)(cnColumnWidth * fWidthRatio);
	lvColumn.pszText = (char *)(cAStrListName[nCount].c_str());
	this->m_listShowRobots.InsertColumn(nCount++, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = (INT32)(cnColumnWidth * 2 * fWidthRatio);
	lvColumn.pszText = (char *)(cAStrListName[nCount].c_str());
	this->m_listShowRobots.InsertColumn(nCount++, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = (INT32)(cnColumnWidth * 2 * fWidthRatio);
	lvColumn.pszText = (char *)(cAStrListName[nCount].c_str());
	this->m_listShowRobots.InsertColumn(nCount++, &lvColumn);

	//�����ߣ�ֻ������report����listctrl��
	//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	this->m_listShowRobots.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
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
			pBtn->SetRobotIndex(pRobot->GetPeerRobotID());
			pBtn->ShowWindow(TRUE);
			pBtn->Invalidate(TRUE);
			m_mapRobot2ViewIndex.insert(std::make_pair(pRobot->GetPeerRobotID(), pBtn->GetRobotIndex()));
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
	InitListCtrl();

	ChangeDlgSize();
//	CreateRobotBtns();			//5 ��ʼ���ȴ��������еİ�ť.����ͨ������������.��ʱ��ͨ����ť��������.

	return TRUE;
}

BOOL CDlgShowRobot::Init(RobotGroup * pRobotGroup /*= NULL*/)
{
//	ShowRobotBtns(FALSE);	//5 ��ʱ������ʾ��ť�ķ�ʽ,��Ϊlist
// 
// 	if (pRobotGroup)
// 	{
// 		RobotGroup::MapRobots mapRobots = pRobotGroup->GetMapRobots();
// 		RobotGroup::MapRobots::const_iterator iter = mapRobots.begin();
// 		for (; iter != mapRobots.end(); ++iter)
// 		{
// 			ShowRobotBtn(iter->second);
// 		}
// 	}

	m_pCurRobotGroup = pRobotGroup;
	if (m_pCurRobotGroup)
	{
		RobotGroup::MapRobots mapRobots = pRobotGroup->GetMapRobots();
		RobotGroup::MapRobots::const_iterator iter = mapRobots.begin();
		for (; iter != mapRobots.end(); ++iter)
		{
			InsertRobotList(pRobotGroup, iter->second);
		}
	}

	return TRUE;
}

BOOL CDlgShowRobot::Cleanup()
{
// 	ShowRobotBtns(FALSE);	//5 ��ʱ������ʾ��ť�ķ�ʽ,��Ϊlist

	m_pCurRobotGroup	= NULL;
	m_nCurRobotTabIndex = -1;
	m_nRobotCount		= 0;

	m_mapRobot2ViewIndex.clear();
	m_listShowRobots.DeleteAllItems();


/*  //5 ��ʱ���ð�ť��ʾͨ��list����.
	m_nBtnCount			= 0;
	m_nBtnTopLeftX		= 0;
	m_nBtnTopLeftY		= 0;
	SetScrollPos(SBS_VERT, 0);
	SetScrollRange(SBS_VERT, 0, 0);

	SetScrollBarRange(); 
*/
	return TRUE;
}

void CDlgShowRobot::OnRobotBtnClicked(UINT nBtnID)
{

	MessageBox("����ɹ�.");
}

void CDlgShowRobot::OnNMRClickListShowRobot(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	POINT   pt;
	GetCursorPos(&pt);

	CMenu temp, *pSubMenu;
	temp.LoadMenu(IDR_MENU_ROBOT_COMMAND);
	pSubMenu = temp.GetSubMenu(0);
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, pt.x, pt.y, this);

	*pResult = 0;
}

void CDlgShowRobot::OnSendRobotCommand()
{
	// TODO: �ڴ���������������
	
	if (m_dlgRobotCommand.DoModal())
	{

	}

}

BOOL CDlgShowRobot::GetAllSelectedItems(std::vector<Msg::Object> & vecItems)
{
	INT32 nSize = m_listShowRobots.GetItemCount();
	for (INT32 i = 0; i < nSize; ++i)
	{
		if (m_listShowRobots.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			CRobot * pRobot = (CRobot*)(m_listShowRobots.GetItemData(i));
			if (pRobot)
			{
				vecItems.push_back(pRobot->GetPeerRobotID());
			}
		}
	}

	return TRUE;
}

void CDlgShowRobot::OnCreateRobots()
{
	// TODO: �ڴ���������������

	if (m_pCurRobotGroup && m_pCurRobotGroup->GetRobotServer())
	{
		RobotServer * pRobotServer = m_pCurRobotGroup->GetRobotServer();
		rpc_CreateRobots(*pRobotServer, m_pCurRobotGroup->GetRobotSessionID(), 0, m_pCurRobotGroup->GetObjectID(), 1, 300);
	}
}

void CDlgShowRobot::OnCloseGroup()
{
	// TODO: �ڴ���������������
	if (m_pCurRobotGroup && m_pCurRobotGroup->GetRobotServer())
	{
		RobotServer * pRobotServer = m_pCurRobotGroup->GetRobotServer();
		rpc_CloseRobotGroup(*pRobotServer, m_pCurRobotGroup->GetRobotSessionID(), 0, m_pCurRobotGroup->GetObjectID());
	}
}

BOOL CDlgShowRobot::InsertRobot2ViewIndex(INT32 nRobotIndex, INT32 nViewIndex , std::string  strName)
{
	MapRobot2ViewIndexT::iterator iter = m_mapRobot2ViewIndex.find(nRobotIndex);
	if (iter == m_mapRobot2ViewIndex.end())
	{
		m_mapRobot2ViewIndex.insert(std::make_pair(nRobotIndex , nViewIndex));
	}
	else
	{
		iter->second = nViewIndex;
		gErrorStream("InsertRobot2ViewIndex is exist.strName=" << strName << ":nRobotIndex=" << nRobotIndex << ":nViewIndex=" << nViewIndex);
	}

	return TRUE;
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

void CDlgShowRobot::OnDeleteRobot(RobotGroup * pRobotGroup, CRobot * pRobot)
{

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
			InsertRobotList(pRobotGroup , pRobot);
			//ShowRobotBtn(pRobot);	//5 ��ʱ������ʾ��ť�ķ�ʽ,��Ϊlist
		}
	}
}

void CDlgShowRobot::CreateRobotBtns()
{
	for (INT32 i = 0; i < cnMaxRobotBtnNum; ++i)
	{
		CreateRobotBtn();
	}
}

BOOL CDlgShowRobot::ClearRobotBtns()
{
	MapRobotBtnT::iterator iter = m_mapRobotBtns.begin();
	for (; iter != m_mapRobotBtns.end(); ++iter)
	{
		iter->second->DestroyWindow();
		delete iter->second;
	}
	m_mapRobotBtns.clear();

	return TRUE;
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
	pBtn->Create(str, WS_CHILD | WS_VISIBLE | BS_NOTIFY | BS_3STATE,
		pos, &m_txtRobotPlatform, cst_btn_id + m_nCreateBtnIndex); 

	m_mapRobotBtns.insert(std::make_pair(m_nCreateBtnIndex, pBtn));
	++m_nCreateBtnIndex;
}

BOOL CDlgShowRobot::ShowRobotBtns(BOOL bShow/* = FALSE*/)
{
	MapRobotBtnT::iterator iter = m_mapRobotBtns.begin();
	for (; iter != m_mapRobotBtns.end(); ++iter)
	{
		iter->second->ShowWindow(bShow);
	}
	m_mapRobot2ViewIndex.clear();

	m_txtRobotPlatform.Invalidate(TRUE);
	return TRUE;
}

