
// RobotCtrlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RobotCtrl.h"
#include "DlgRobotCtrl.h"
#include "afxdialogex.h"
#include "RobotCommon.h"
#include "RobotManager.h"
#include "RPCCallFuncs.h"
#include "DlgRobotCommand.h"

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
	ON_BN_CLICKED(ID_STOP, &CDlgRobotCtrl::OnBnClickedStop)
	ON_BN_CLICKED(IDOK, &CDlgRobotCtrl::OnBnClickedOk)
	ON_WM_CLOSE()
	ON_COMMAND(ID_CREATE_ROBOT_GROUP, &CDlgRobotCtrl::OnRBtnListServer)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SHOW_ROBOT, &CDlgRobotCtrl::OnTcnSelchangeTabShowRobot)
	ON_COMMAND(ID_CLOSE_ALL, &CDlgRobotCtrl::OnCloseAll)
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
	
	InitShowRobotDlg();
	Json::Value root;
	Json::JsonParase("RobotCtrl.conf", root);
	RobotManager::GetInstance().Init(root);		//5 �����ʼ��,��������RobotCtrl.cpp�н����ͷ�.cleanup.

	SetTimer(0, 500 , NULL);					//5 ��������

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

	if (nIDEvent == 0)
	{
		RobotManager::GetInstance().Update();
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CDlgRobotCtrl::OnSelchangeListCtrlServer()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateCtrlServer(m_listCtrlServer.GetCurSel());
}

void CDlgRobotCtrl::InitShowRobotDlg()
{
	CWnd *pWnd = this->GetDlgItem(IDC_TAB_SHOW_ROBOT);
	m_dlgCurShowRobot.Create(IDD_DLG_SHOW_ROBOT, &m_tabShowRobots);//������ģʽ�Ի�����ʾͼƬ
	m_dlgCurShowRobot.SetParent(pWnd);
	m_dlgCurShowRobot.ShowWindow(SW_SHOW);

	//5 ������Ҫ���������ú�tab��ǩһ����.���ǵ�һ����Ҫ��tab��ƫ����Ϊ�˴�����ťʹ��.
	CRect rect;
	m_tabShowRobots.GetClientRect(rect);
	rect.top += cnTabYPosOffset;
	m_dlgCurShowRobot.MoveWindow(rect);
	m_dlgCurShowRobot.InitDialog();
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
		OnSelchangeListCtrlServer();

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
	m_nCurRobotTabIndex = nIndex;

	if (nIndex != -1)
	{
		RobotGroup * pRobotGroup = RobotManager::GetInstance().GetRobotGroup(m_nCurListCtrlIndex, m_nCurRobotTabIndex);
		if (pRobotGroup)
		{
			m_dlgCurShowRobot.SetCurRobotTab(m_nCurRobotTabIndex, pRobotGroup);
		}
		else
		{
			MsgAssert(0, "OnSelchangingTabShowRobot err.no this robotgroup index=" << m_nCurRobotTabIndex);
		}
	}
	else
	{
		m_dlgCurShowRobot.SetCurRobotTab(m_nCurRobotTabIndex, NULL);
	}
}

void CDlgRobotCtrl::UpdateCtrlServer(INT32 nIndex)
{
	INT32 nOldIndex = m_nCurListCtrlIndex;
	m_dlgCurShowRobot.SetCurListCtrlIndex(nIndex);
	if (nOldIndex != nIndex)		//5 ֻ���б仯��ʱ��Ÿ���.
	{
		INT32 nRobotGroupCount = 0;
		RobotServer * pServer = RobotManager::GetInstance().GetRobotServer(nIndex);
		if (pServer)
		{
			m_tabShowRobots.DeleteAllItems();
			const RobotServer::MapRobotGroups & mapRobots = pServer->GetMapRobotGroups();
			RobotServer::MapRobotGroups::const_iterator iter = mapRobots.begin();
			for (; iter != mapRobots.end(); ++iter)
			{
				OnCreateRobotGroup(pServer, iter->second);
			}
			nRobotGroupCount = (INT32)mapRobots.size();
		}
		m_nCurListCtrlIndex = nIndex;
		
		if (nRobotGroupCount > 0)
		{
			UpdateRobotTab(0);
		}
		else
		{
			UpdateRobotTab(-1);
		}
	}
}

void CDlgRobotCtrl::OnCreateRobotGroup(RobotServer * pRobotServer, RobotGroup * pRobotGroup, BOOL bUpdate/* = FALSE*/)
{
	if (pRobotGroup && pRobotServer)
	{
		m_nCurRobotTabIndex = pRobotGroup->GetRobotTabIndex() - 1;

		CString str;
		str.Format("Robot %d", m_nCurRobotTabIndex);
		m_tabShowRobots.InsertItem(m_nCurRobotTabIndex, str);
		m_tabShowRobots.SetCurSel(m_nCurRobotTabIndex);
		UpdateWindow();

		if (bUpdate)
		{
			//5 �����µ�robotgroup.������ʱ�����õĻ�Ч�ʱȽϵ�.
			m_dlgCurShowRobot.SetCurRobotTab(m_nCurRobotTabIndex , pRobotGroup);
		}

		//5 ������Ҫ���������ú�tab��ǩһ����.�����ֲ��ܸ���tab��ǩҳ.����Ҫ��ƫ��
		CRect rect;
		m_tabShowRobots.GetClientRect(rect);
		rect.top += cnTabYPosOffset;
		m_dlgCurShowRobot.MoveWindow(rect);
	}
} 

void CDlgRobotCtrl::OnDeleteRobotGroup(RobotServer * pRobotServer, RobotGroup * pRobotGroup)
{
	if (pRobotGroup && pRobotServer)
	{
		INT32 nRobotCount = pRobotServer->GetCurRobotGroupCount();
		INT32 nIndex = pRobotGroup->GetRobotTabIndex() - 1;
		if (m_tabShowRobots.GetItemCount() < nIndex)
		{
			return;
		}

		INT32 nCurSel = m_tabShowRobots.GetCurSel();
		if (nCurSel == nIndex || (nCurSel == -1 && m_tabShowRobots.GetItemCount() > 0))		//5 ���ɾ���˵�ǰ������ʾ��ҳ.��ô����ʾ��һҳ.
		{
			if (m_tabShowRobots.GetItemCount() - 1 > 0)
			{
				m_tabShowRobots.SetCurSel(0);
				m_nCurRobotTabIndex = 0;

				RobotGroup * pServer = RobotManager::GetInstance().GetRobotGroup(m_nCurListCtrlIndex, m_nCurRobotTabIndex);
				if (pServer)
				{
					m_dlgCurShowRobot.SetCurRobotTab(m_nCurRobotTabIndex, pServer); 
				}
				else
				{
					MsgAssert(0, "OnDeleteRobotGroup err.no this robotgroup index=" << m_nCurRobotTabIndex);
				}
			}
			else
			{
				m_nCurRobotTabIndex = -1;
				m_dlgCurShowRobot.SetCurRobotTab(m_nCurRobotTabIndex, NULL);
			}
		}
		m_tabShowRobots.DeleteItem(nIndex);


		//5 ������Ҫ���������ú�tab��ǩһ����
		if (nRobotCount < 1)
		{
			CRect rect;
			m_tabShowRobots.GetClientRect(rect);
			m_dlgCurShowRobot.MoveWindow(rect);
		}
	}
}

void CDlgRobotCtrl::OnTcnSelchangeTabShowRobot(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	INT32 nIndex = m_tabShowRobots.GetCurSel();

	UpdateRobotTab(nIndex);
	*pResult = 0;
}

void CDlgRobotCtrl::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	system("start robotserver.exe");
//	RobotManager::GetInstance().DebugConnect();

// 	CDialogEx::OnOK();
}

void CDlgRobotCtrl::OnBnClickedStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

//	RobotManager::GetInstance().DebugDisconnect();
}


void CDlgRobotCtrl::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	RobotManager::GetInstance().Cleanup();
	CDialogEx::OnClose();
}



void CDlgRobotCtrl::OnRBtnListServer()
{
	// TODO: �ڴ���������������
	RobotServer * pServer = RobotManager::GetInstance().GetRobotServer(m_nCurListCtrlIndex);
	if (pServer)
	{
		//5 ����RobotGroup
		Robot::rpc_HandleRobotGroup(RobotManager::GetInstance(), pServer->GetRobotSessionID(), 0, pServer->GetObjectID(), 0, pServer->GetServerPort());
	}

}


void CDlgRobotCtrl::OnCloseAll()
{
	// TODO: �ڴ���������������

	RobotServer * pServer = RobotManager::GetInstance().GetRobotServer(m_nCurListCtrlIndex);
	if (pServer)
	{
		//5 ����RobotGroup
		pServer->CloseAllRobotGroups();
	}
}
