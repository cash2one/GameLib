// DlgCreateRobotGroup.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RobotCtrl.h"
#include "DlgCreateRobotGroup.h"
#include "afxdialogex.h"
#include "DlgShowRobot.h"
#include "RPCCallFuncs.h"

// CDlgCreateRobotGroup �Ի���

IMPLEMENT_DYNAMIC(CDlgCreateRobotGroup, CDialogEx)

CDlgCreateRobotGroup::CDlgCreateRobotGroup(CDlgShowRobot * pDlg, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_CREATE_ROBOT_GROUP, pParent)
	, m_editStartNum(1)
	, m_editEndNum(3)
	, m_pDlgShowRobot(pDlg)
{

}

CDlgCreateRobotGroup::~CDlgCreateRobotGroup()
{
}

void CDlgCreateRobotGroup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITSTART_NUM, m_editStartNum);
	DDX_Text(pDX, IDC_EDIT_END_EDIT, m_editEndNum);
}


BEGIN_MESSAGE_MAP(CDlgCreateRobotGroup, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgCreateRobotGroup::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgCreateRobotGroup::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgCreateRobotGroup ��Ϣ�������


void CDlgCreateRobotGroup::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	UpdateData(FALSE);

	CDlgShowRobot* pDlg = dynamic_cast<CDlgShowRobot*>(m_pDlgShowRobot);
	if (pDlg)
	{
		RobotGroup * pRobot = pDlg->GetCurRobotGroup();
		if (pRobot && pRobot->GetRobotServer())
		{
			RobotServer * pRobotServer = pRobot->GetRobotServer();
			rpc_CreateRobots(*pRobotServer, pRobot->GetRobotSessionID(), 0, pRobot->GetObjectID(), m_editStartNum, m_editEndNum);
		}
	}


	CDialogEx::OnOK();
}


void CDlgCreateRobotGroup::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
