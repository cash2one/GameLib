// E:\GitHub\GameLib\Tools\src\RobotCtrl\DlgRobotCommand.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RobotCtrl.h"
#include "DlgRobotCommand.h"
#include "afxdialogex.h"


// CDlgRobotCommand �Ի���

IMPLEMENT_DYNAMIC(CDlgRobotCommand, CDialogEx)

CDlgRobotCommand::CDlgRobotCommand(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_ROBOT_COMMAND, pParent)
{

}

CDlgRobotCommand::~CDlgRobotCommand()
{
}

void CDlgRobotCommand::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgRobotCommand, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgRobotCommand::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgRobotCommand::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgRobotCommand ��Ϣ�������

void CDlgRobotCommand::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}

void CDlgRobotCommand::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
