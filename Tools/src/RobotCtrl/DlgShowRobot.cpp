// DlgShowRobot.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RobotCtrl.h"
#include "DlgShowRobot.h"
#include "afxdialogex.h"


// CDlgShowRobot �Ի���

IMPLEMENT_DYNAMIC(CDlgShowRobot, CDialogEx)

CDlgShowRobot::CDlgShowRobot(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_SHOW_ROBOT, pParent)
	, m_nCurRobotIndex(-1)
{

}

CDlgShowRobot::~CDlgShowRobot()
{
}

void CDlgShowRobot::SetCurRobotIndex(INT32 val)
{ 
	m_nCurRobotIndex = val;
}

void CDlgShowRobot::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgShowRobot, CDialogEx)
END_MESSAGE_MAP()


// CDlgShowRobot ��Ϣ�������
