// DlgRobotCommand.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RobotCtrl.h"
#include "DlgRobotCommand.h"
#include "afxdialogex.h"
#include "CUtil/inc/CUtil.h"
#include "DlgShowRobot.h"
#include "RPCCallFuncs.h"

// CDlgRobotCommand �Ի���

IMPLEMENT_DYNAMIC(CDlgRobotCommand, CDialogEx)

CDlgRobotCommand::CDlgRobotCommand(CDlgShowRobot * pDlg, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_ROBOT_COMMAND, pParent)
	, m_nCurParamsCount(0)
	, m_pDlgShowRobot(pDlg)
{

}

CDlgRobotCommand::~CDlgRobotCommand()
{
}

void CDlgRobotCommand::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SELECT_COMMAND, m_cobSelectCommand);

	//5 IDC_COMMAND_TXT1��Ҫ��֤���ǵ�Index����������.
	for (INT32 i = 0; i < cnCommandParamCount; i++)
	{
		DDX_Control(pDX, IDC_COMMAND_TXT1 + i, m_txtCommandType[i]);
		DDX_Control(pDX, IDC_COMMAND_EDIT1 + i, m_editCommandValue[i]);
		DDX_Control(pDX, IDC_COMMAND_NOTE1 + i, m_txtCommandNote[i]);
	}
}

BEGIN_MESSAGE_MAP(CDlgRobotCommand, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgRobotCommand::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgRobotCommand::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_SELECT_COMMAND, &CDlgRobotCommand::OnCbnSelchangeComboSelectCommand)
END_MESSAGE_MAP()


// CDlgRobotCommand ��Ϣ�������

void CDlgRobotCommand::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CDlgShowRobot* pDlg = dynamic_cast<CDlgShowRobot*>(m_pDlgShowRobot);
	if (pDlg)
	{
		RobotGroup * pRobot = pDlg->GetCurRobotGroup();
		if (pRobot)
		{
			std::vector<Msg::Object>  vecItems;
			pDlg->GetAllSelectedItems(vecItems);
			if (vecItems.size() <= 0)
			{
				return;
			}

			CUtil::CStream cs;
			INT32 nIndex = m_cobSelectCommand.GetCurSel();
			cs << nIndex;

			for (INT32 i = 0;i < m_nCurParamsCount;++i)
			{
				INT32 nIndex = m_mapRobotParamType[i];
				switch (nIndex)
				{
				case ROBOT_TYPE_DOUBLE:
				{
					CString str;
					m_editCommandValue[i].GetWindowTextA(str);
					double value = (double)(CUtil::atof(str.GetBuffer()));
					cs << value;
				}break;
				case ROBOT_TYPE_STRING:
				{
					CString str;
					m_editCommandValue[i].GetWindowTextA(str);
					std::string value = std::string(str.GetBuffer());
					cs << value;
				}break;
				default:
					break;
				}
			}
			
			CUtilChunk & chunk = cs.GetData();
			rpc_SendRobotCommand(*(pRobot->GetRobotServer()), pRobot->GetRobotSessionID(), vecItems, pRobot->GetObjectID() , chunk);
		}
	}

	CDialogEx::OnOK();
}

void CDlgRobotCommand::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

BOOL CDlgRobotCommand::InitDialog()
{
	ShowDlgCtrls(cnCommandParamCount, FALSE);

	MapRobotCommands::iterator iter = RobotCommands::sRobotCommands.begin();
	for (;iter != RobotCommands::sRobotCommands.end(); ++iter)
	{
		INT32 nIndex = m_cobSelectCommand.AddString(iter->second.command.c_str());
		m_mapIndex2ConfigIndex.insert(std::make_pair(nIndex, iter->first));
	}
	
	return TRUE;
}

void CDlgRobotCommand::ShowDlgCtrls(INT32 nCount , BOOL bShow)
{
	for (INT32 i = 0; i < cnCommandParamCount; ++i)
	{
		m_txtCommandNote[i].ShowWindow(FALSE);
		m_txtCommandType[i].ShowWindow(FALSE);
		m_editCommandValue[i].ShowWindow(FALSE);
		m_nCurParamsCount = 0;
	}

	for (INT32 i = 0; i < nCount; ++i)
	{
		m_txtCommandNote[i].ShowWindow(bShow);
		m_txtCommandType[i].ShowWindow(bShow);
		m_editCommandValue[i].ShowWindow(bShow);
		if (bShow)
		{
			++m_nCurParamsCount;
		}
	}
}

BOOL CDlgRobotCommand::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgRobotCommand::OnCbnSelchangeComboSelectCommand()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	INT32 nIndex = m_cobSelectCommand.GetCurSel();
	MapIndexToConfigIndex::iterator iter = m_mapIndex2ConfigIndex.find(nIndex);
	if (iter != m_mapIndex2ConfigIndex.end())
	{
		nIndex = iter->second;
		MapRobotCommands::iterator iter2 = RobotCommands::sRobotCommands.find(nIndex);
		if (iter2 != RobotCommands::sRobotCommands.end())
		{
			RobotCommand & robot = iter2->second;

			ShowDlgCtrls(INT32(robot.mapRobotParams.size()), TRUE);
			for (INT32 i = 0; i < robot.mapRobotParams.size(); ++i)
			{
				m_txtCommandNote[i].SetWindowText(robot.mapRobotParams[i].note.c_str());
				m_mapRobotParamType.insert(std::make_pair(i , robot.mapRobotParams[i].type));
				m_txtCommandType[i].SetWindowText(RobotCommands::sRobotTypes[robot.mapRobotParams[i].type].c_str());
				m_editCommandValue[i].SetWindowText(robot.mapRobotParams[i].default.c_str());
			}
		}
	}
}
