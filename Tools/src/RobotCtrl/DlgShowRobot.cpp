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
	INT32 nXNumber = (rect.BottomRight().x - rect.TopLeft().x) / (cst_btn_pos_x_space + cst_btn_pos_x_length);
	return nXNumber;
}

INT32 GetYBtnNum(CRect rect)
{
	INT32 nYNumber = (rect.BottomRight().y - rect.TopLeft().y) / (cst_btn_pos_y_space + cst_btn_pos_y_length);
	return nYNumber;
}


BEGIN_MESSAGE_MAP(CDlgShowRobot, CDialogEx)
	ON_WM_VSCROLL()
	ON_WM_CREATE()
//	ON_COMMAND_RANGE(cst_btn_id, cst_btn_id + cst_max_btn_id, OnRobotBtnClicked)     //��Ӧ�Ǹ�����ID����10000��10000 + �����Ǹ�
END_MESSAGE_MAP()

CDlgShowRobot::CDlgShowRobot(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_SHOW_ROBOT, pParent)
	, m_nCurRobotTabIndex(-1)
	, m_nCurListCtrlIndex(-1)
	, m_nBtnCount(0)
	, m_nBtnTopLeftX(0)
	, m_nBtnTopLeftY(0)
	, m_pCurRobotGroup(NULL)
{

}

CDlgShowRobot::~CDlgShowRobot()
{
	Cleanup();
}

BOOL CDlgShowRobot::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CRect rect;
	GetClientRect(rect);
	INT32 nXNumber = GetXBtnNum(rect);
	GetDlgItem(IDC_STATIC_ROBOT_BASE)->MoveWindow(CRect(0, -5, rect.BottomRight().x + 20, (MAX_ROBOT_BTN_NUM / nXNumber + 1) * (cst_btn_pos_y_space + cst_btn_pos_y_length)));

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

	INT32 btnLineSize = cst_btn_pos_y_length + cst_btn_pos_y_space + cst_btn_pos_y_space;

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
	si.nMax		= (m_nBtnCount / nXNumber + 1) * (cst_btn_pos_y_space + cst_btn_pos_y_length);
	si.nPage	= rect.Height();//�ɼ����ڸ߶Ⱥ�ҳ��С����һ��
	si.nPos		= nPos;
	si.fMask	= SIF_ALL;
	si.cbSize	= sizeof(SCROLLINFO);
	SetScrollInfo(SBS_VERT, &si);
}

BOOL CDlgShowRobot::ClearRobotBtns()
{
	MapRobotButtonT::iterator iter = m_mapRobotBtns.begin();
	for (;iter != m_mapRobotBtns.end();++iter)
	{
		iter->second->DestroyWindow();
		delete iter->second;
	}
	m_mapRobotBtns.clear();

	return TRUE;
}

BOOL CDlgShowRobot::Cleanup()
{
	ClearRobotBtns();
	m_nBtnCount = 0;
	m_nBtnTopLeftX = 0;
	m_nBtnTopLeftY = 0;

	SetScrollPos(SBS_VERT, 0);
	SetScrollRange(SBS_VERT, 0, 0);

	return TRUE;
}

void CDlgShowRobot::OnRobotBtnClicked(UINT nBtnID)
{

	MessageBox(L"����ɹ�.");
}

void CDlgShowRobot::OnCreateRobot(RobotGroup * pRobotGroup, Robot * pRobot)
{
	CDlgRobotCtrl * pRobotDlg = dynamic_cast<CDlgRobotCtrl*>(theApp.m_pMainWnd);
	if (pRobotDlg)
	{
		if (m_nCurRobotTabIndex == pRobotDlg->GetCurRobotTabIndex() &&
			m_nCurListCtrlIndex == pRobotDlg->GetCurListCtrlIndex())
		{
			CreateRobotBtn(pRobot);
			SetScrollBarRange(); 
		}
	}
}

void CDlgShowRobot::OnDeleteRobot(RobotGroup * pRobotGroup, Robot * pRobot)
{

}

void CDlgShowRobot::CreateRobotBtn(Robot * pRobot)
{
	INT32 nIndex = pRobot->GetRobotIndex();

	m_nBtnTopLeftX += cst_btn_pos_x_length + cst_btn_pos_x_space;	//5�������Ͻ�X��λ��.��Ҫ����btn�ĳ��Ⱥ�btn֮��ļ�϶

	CRect rect;
	m_txtRobotPlatform.GetClientRect(&rect);
	if (m_nBtnTopLeftX > rect.BottomRight().x)
	{
		m_nBtnTopLeftX = cst_btn_pos_x_length + cst_btn_pos_x_space;
		m_nBtnTopLeftY += cst_btn_pos_y_length + cst_btn_pos_y_space;
	}

	CRobotBtn * pBtn = new CRobotBtn(pRobot);
	CRect pos = CRect(m_nBtnTopLeftX - cst_btn_pos_x_length
		, m_nBtnTopLeftY + cst_btn_pos_y_space + rect.top, m_nBtnTopLeftX
		, m_nBtnTopLeftY + cst_btn_pos_y_length + cst_btn_pos_y_space + rect.top);
	pBtn->SetRectPos(pos);
	pBtn->SetRobotIndex(nIndex);

	CString str;
	str.Format(L"%s", pRobot->GetName().c_str());
	pBtn->Create(str, WS_CHILD | BS_DEFPUSHBUTTON | WS_VISIBLE | BS_NOTIFY,
		pos, &m_txtRobotPlatform, cst_btn_id + nIndex);

	m_mapRobotBtns.insert(std::make_pair(nIndex, pBtn));
	++m_nBtnCount;
}



