
// RobotCtrlDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CRobotCtrlDlg �Ի���



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


// CRobotCtrlDlg ��Ϣ�������

BOOL CDlgRobotCtrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	CUtil::Init();
	InitShowRobotDlg();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDlgRobotCtrl::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDlgRobotCtrl::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDlgRobotCtrl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnTimer(nIDEvent);
}


void CDlgRobotCtrl::OnSelchangeListCtrlServer()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_nCurListCtrlIndex = m_listCtrlServer.GetCurSel();
	UpdateCtrlServer(m_nCurListCtrlIndex);
}

void CDlgRobotCtrl::InitShowRobotDlg()
{
	CWnd *pWnd = this->GetDlgItem(IDC_TAB_SHOW_ROBOT);
	m_dlgCurShowRobot.Create(IDD_DLG_SHOW_ROBOT, &m_tabShowRobots);//������ģʽ�Ի�����ʾͼƬ
	m_dlgCurShowRobot.SetParent(pWnd);
	m_dlgCurShowRobot.ShowWindow(SW_SHOW);

	//5 ������Ҫ���������ú�tab��ǩһ����.
	CRect rect;
	m_tabShowRobots.GetClientRect(rect);
	m_dlgCurShowRobot.MoveWindow(rect);
}

void CDlgRobotCtrl::OnCreateRobotServer(RobotServer * pRobot)
{
	if (pRobot)
	{
		//5 ��������һ��List��¼
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
	RobotServer * pServer = RobotManager::GetInstance().OnUpdateCtrlServer(m_nCurListCtrlIndex);
	if (pServer)
	{
		pServer->DebugDisconnect();
	}
//	RobotGroup * pRobotGroup = RobotManager::GetInstance().OnUpdateRobotTab(m_nCurListCtrlIndex , nIndex);
//	if (pRobotGroup)
	{
		//todo ���ShowRobot�Ľ���

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
		m_dlgCurShowRobot.SetCurRobotIndex(m_nCurRobotTabIndex);
		 

		//5 ������Ҫ���������ú�tab��ǩһ����.�����ֲ��ܸ���tab��ǩҳ.����Ҫ��ƫ��
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

		if (m_tabShowRobots.GetCurSel() == nIndex)		//5 ���ɾ���˵�ǰ������ʾ��ҳ.��ô����ʾ��һҳ.
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
			m_dlgCurShowRobot.SetCurRobotIndex(m_nCurRobotTabIndex);
		}
		m_tabShowRobots.DeleteItem(nIndex);


		//5 ������Ҫ���������ú�tab��ǩһ����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_nCurRobotTabIndex = m_tabShowRobots.GetCurSel();
	UpdateRobotTab(m_nCurRobotTabIndex);

	*pResult = 0;
}

void CDlgRobotCtrl::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	RobotManager::GetInstance().DebugConnect();

// 	CDialogEx::OnOK();
}

void CDlgRobotCtrl::OnBnClickedStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	RobotManager::GetInstance().DebugDisconnect();
}
