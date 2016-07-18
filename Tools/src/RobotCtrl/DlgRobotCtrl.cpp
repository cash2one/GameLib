
// RobotCtrlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RobotCtrl.h"
#include "DlgRobotCtrl.h"
#include "afxdialogex.h"
#include "RobotCommon.h"
#include "CUtil/inc/CUtil.h"
#include "RobotManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRobotCtrlDlg 对话框



CDlgRobotCtrl::CDlgRobotCtrl(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ROBOTCTRL_DIALOG, pParent)
	, m_nCurRobotTabIndex(-1)
	, m_nCurListCtrlIndex(-1)
	, m_nShowRobotCount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlgRobotCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SHOW_ROBOT, m_tabShowRobots);
	DDX_Control(pDX, IDC_EDIT_ROBOT_NUM_BEGIN, m_editRobotStartNum);
	DDX_Control(pDX, IDC_EDIT_ROBOT_NUM_END, m_editRobotEndNum);
	DDX_Control(pDX, IDC_STATIC_TOTAL_ROBOT_NUM, m_txtTotalRobotNum);
	DDX_Control(pDX, IDC_STATIC_ONLINE_ROBOT_NUM, m_txtOnlineRobotNum);
	DDX_Control(pDX, IDC_STATIC_OFFLINE_ROBOT_NUM, m_txtOfflineRobotNum);
	DDX_Control(pDX, IDC_STATIC_STATUE, m_txtShowRobotStatue);
	DDX_Control(pDX, IDC_LIST_CTRL_SERVER, m_listCtrlServer);
}

BEGIN_MESSAGE_MAP(CDlgRobotCtrl, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_LBN_SELCHANGE(IDC_LIST_CTRL_SERVER, &CDlgRobotCtrl::OnSelchangeListCtrlServer)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_SHOW_ROBOT, &CDlgRobotCtrl::OnSelchangingTabShowRobot)
	ON_BN_CLICKED(ID_STOP, &CDlgRobotCtrl::OnBnClickedStop)
	ON_BN_CLICKED(IDOK, &CDlgRobotCtrl::OnBnClickedOk)
END_MESSAGE_MAP()


// CRobotCtrlDlg 消息处理程序

BOOL CDlgRobotCtrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CUtil::Init();
	InitShowRobotDlg();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDlgRobotCtrl::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDlgRobotCtrl::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDlgRobotCtrl::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDlgRobotCtrl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
}


void CDlgRobotCtrl::OnSelchangeListCtrlServer()
{
	// TODO: 在此添加控件通知处理程序代码

	m_nCurListCtrlIndex = m_listCtrlServer.GetCurSel();
	UpdateCtrlServer(m_nCurListCtrlIndex);

	m_dlgCurShowRobot.SetCurListCtrlIndex(m_nCurListCtrlIndex);
}

void CDlgRobotCtrl::InitShowRobotDlg()
{
	CWnd *pWnd = this->GetDlgItem(IDC_TAB_SHOW_ROBOT);
	m_dlgCurShowRobot.Create(IDD_DLG_SHOW_ROBOT, &m_tabShowRobots);//创建非模式对话框，显示图片
	m_dlgCurShowRobot.SetParent(pWnd);
	m_dlgCurShowRobot.ShowWindow(SW_SHOW);

	//5 这里需要将窗口设置和tab标签一样大.
	CRect rect;
	m_tabShowRobots.GetClientRect(rect);
	m_dlgCurShowRobot.MoveWindow(rect);
}

void CDlgRobotCtrl::OnCreateRobotServer(RobotServer * pRobot)
{
	if (pRobot)
	{
		//5 这里增加一条List记录
		INT32 nLastCount = RobotManager::GetInstance().GetCurRobotServerCount();
		m_listCtrlServer.InsertString(nLastCount , CString(pRobot->GetName().c_str()));
		m_listCtrlServer.SetCurSel(nLastCount);
		m_nCurListCtrlIndex = nLastCount;

		pRobot->SetListCtrlIndex(nLastCount);
	}

}

void CDlgRobotCtrl::OnDeleteRobotServer(RobotServer * pRobot)
{
	if (pRobot)
	{
		if (m_listCtrlServer.GetCurSel() == pRobot->GetListCtrlIndex())
		{
			if (m_listCtrlServer.GetCount() - 1 > 0)
			{
				m_nCurListCtrlIndex = 0;
				m_listCtrlServer.SetCurSel(m_nCurListCtrlIndex);
				OnSelchangeListCtrlServer();
			}
			else
			{
				m_nCurListCtrlIndex = -1;
			} 
		}
		m_listCtrlServer.DeleteString(pRobot->GetListCtrlIndex());
	}
}

void CDlgRobotCtrl::UpdateRobotTab(INT32 nIndex)
{
	RobotGroup * pServer = RobotManager::GetInstance().OnUpdateRobotTab(m_nCurListCtrlIndex , m_nCurRobotTabIndex);
	if (pServer)
	{
		int nIndex = 20;
		while (nIndex--)
		{
			pServer->DebugConnect();
		}
		pServer->DebugConnect();
	}

//	RobotGroup * pRobotGroup = RobotManager::GetInstance().OnUpdateRobotTab(m_nCurListCtrlIndex , nIndex);
//	if (pRobotGroup)
	{
		//todo 清空ShowRobot的界面

	}
}

void CDlgRobotCtrl::UpdateCtrlServer(INT32 nIndex)
{
	RobotServer * pServer = RobotManager::GetInstance().OnUpdateCtrlServer(nIndex);
	if (pServer)
	{
		int nIndex = 2;
		while (nIndex--)
		{
			pServer->DebugConnect();
		}

		m_tabShowRobots.DeleteAllItems();
		const RobotServer::MapRobotGroups & mapRobots = pServer->GetMapRobotGroups();
		RobotServer::MapRobotGroups::const_iterator iter = mapRobots.begin();
		for (;iter != mapRobots.end();++iter)
		{
			OnCreateRobotGroup(pServer, iter->second);
		}
	}
}

void CDlgRobotCtrl::OnCreateRobotGroup(RobotServer * pRobotServer, RobotGroup * pRobotGroup)
{
	if (pRobotGroup && pRobotServer)
	{
		INT32 nRobotCount = pRobotServer->GetCurRobotGroupCount();

		m_nCurRobotTabIndex = pRobotGroup->GetRobotTabIndex();

		CString str;
		str.Format(L"Robot %d", m_nCurRobotTabIndex);
		m_tabShowRobots.InsertItem(m_nCurRobotTabIndex, str);
		m_tabShowRobots.SetCurSel(m_nCurRobotTabIndex);
		m_dlgCurShowRobot.Invalidate(TRUE);
		m_dlgCurShowRobot.SetCurRobotTabIndex(m_nCurRobotTabIndex); 
		 

		//5 这里需要将窗口设置和tab标签一样大.但是又不能覆盖tab标签页.所以要做偏移
		if (nRobotCount == 0)
		{
			CRect rect;
			m_tabShowRobots.GetClientRect(rect);
			rect.top += cnTabYPosOffset;
			m_dlgCurShowRobot.MoveWindow(rect);
		}
	}
} 

void CDlgRobotCtrl::OnDeleteRobotGroup(RobotServer * pRobotServer, RobotGroup * pRobotGroup)
{
	if (pRobotGroup && pRobotServer)
	{
		INT32 nRobotCount = pRobotServer->GetCurRobotGroupCount();
		INT32 nIndex = pRobotGroup->GetRobotTabIndex();
		if (m_tabShowRobots.GetItemCount() < nIndex)
		{
			return;
		}

		if (m_tabShowRobots.GetCurSel() == nIndex)		//5 如果删除了当前正在显示的页.那么则显示第一页.
		{
			if (m_tabShowRobots.GetItemCount() - 1 > 0)
			{
				m_tabShowRobots.SetCurSel(0);
				m_nCurRobotTabIndex = 0;
			}
			else
			{
				m_nCurRobotTabIndex = -1;
			}
			m_dlgCurShowRobot.SetCurRobotTabIndex(m_nCurRobotTabIndex);
		}
		m_tabShowRobots.DeleteItem(nIndex);


		//5 这里需要将窗口设置和tab标签一样大
		if (nRobotCount <= 0)
		{
			CRect rect;
			m_tabShowRobots.GetClientRect(rect);
			m_dlgCurShowRobot.MoveWindow(rect);
		}
	}
}

void CDlgRobotCtrl::OnSelchangingTabShowRobot(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码

	m_nCurRobotTabIndex = m_tabShowRobots.GetCurSel();
	m_dlgCurShowRobot.SetCurRobotTabIndex(m_nCurRobotTabIndex);

	UpdateRobotTab(m_nCurRobotTabIndex);

	*pResult = 0;
}

void CDlgRobotCtrl::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	RobotManager::GetInstance().DebugConnect();

// 	CDialogEx::OnOK();
}

void CDlgRobotCtrl::OnBnClickedStop()
{
	// TODO: 在此添加控件通知处理程序代码

	RobotManager::GetInstance().DebugDisconnect();
}
