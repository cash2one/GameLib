#include "stdafx.h"
#include "RobotManager.h"
#include "RobotCtrl.h"
#include "DlgRobotCtrl.h"
#include "LogLib/inc/Log.h"

RobotManager::RobotManager()
	: m_nCurRobotServerCount(0)
{
	m_pRpcListener = new RobotServerListener(this);
}

RobotManager::~RobotManager()
{
}

RobotManager & RobotManager::GetInstance()
{
	static RobotManager instance;
	return instance;
}

CErrno RobotManager::Init(Json::Value & conf)
{
	return RpcInterface::Init(conf);
}

CErrno RobotManager::Cleanup(void)
{
	MapRobotServerToTab temp = m_mapRobotServerToTab; //5 ɾ����ʱ��.�ײ��ɾ��key,����������Ҫ��temp
	MapRobotServerToTab::iterator iter = temp.begin();
	for (; iter != temp.end(); ++iter)
	{
		DeleteRobotServer(iter->first);
	}

	return RpcInterface::Cleanup();
}

CErrno RobotManager::Update(void)
{
	return RpcInterface::Update();
}

CErrno RobotManager::CreateRobotServer(INT32 nSessionID, const std::string & strNetNodeName, bool bReconnect/* = false*/)
{
	if (!bReconnect)
	{
		MapRobotServers::iterator iter = m_mapRobotServers.find(nSessionID);
		if (iter == m_mapRobotServers.end())
		{
			RobotServer * pRobot = new RobotServer(strNetNodeName , nSessionID);
			m_mapRobotServers.insert(std::make_pair(nSessionID , pRobot));

			m_mapTabToRobotServer.insert(std::make_pair(m_nCurRobotServerCount, nSessionID));
			m_mapRobotServerToTab.insert(std::make_pair(nSessionID, m_nCurRobotServerCount));

			OnCreateRobotServer(pRobot);

			++m_nCurRobotServerCount;
		}
		else
		{
			gErrorStream("CreateRobotServer err , it already exist. sessionID=" << nSessionID);
			return CErrno::Failure();
		}
	}
	return CErrno::Success();
}

void RobotManager::OnCreateRobotServer(RobotServer * pRobot)
{
	if (pRobot)
	{
		CDlgRobotCtrl * pRobotDlg = dynamic_cast<CDlgRobotCtrl*>(theApp.m_pMainWnd);
		if (pRobotDlg)
		{
			pRobotDlg->OnCreateRobotServer(pRobot);
		}
	}

}

CErrno RobotManager::DeleteRobotServer(INT32 nSessionID)
{
	MapRobotServers::iterator iter = m_mapRobotServers.find(nSessionID);
	if (iter != m_mapRobotServers.end())
	{
		OnDeleteRobotServer(iter->second);

		delete iter->second;
		m_mapRobotServers.erase(iter);

		--m_nCurRobotServerCount;

	}
	else
	{
		MsgAssert_ReF(0 , "DeleteRobotServer err , it not exist. sessionID=" << nSessionID);
	}
	return CErrno::Success();
}

void RobotManager::OnDeleteRobotServer(RobotServer * pRobot)
{
	if (pRobot)
	{
		INT32 nIndex = pRobot->GetListCtrlIndex();
		ReplaceSimpleMapRightKey(m_mapTabToRobotServer, m_mapTabToRobotServer, nIndex);
		ResetMapKey(m_mapTabToRobotServer , m_mapRobotServerToTab);
		ResetRobotServerIndex();

		pRobot->Cleanup();

		CDlgRobotCtrl * pRobotDlg = dynamic_cast<CDlgRobotCtrl*>(theApp.m_pMainWnd);
		if (pRobotDlg)
		{
			pRobotDlg->OnDeleteRobotServer(pRobot);
		}
	}
}

void RobotManager::ResetRobotServerIndex()
{
	MapRobotServerToTab::iterator iter = m_mapRobotServerToTab.begin();
	for (; iter != m_mapRobotServerToTab.end(); ++iter)
	{
		MapRobotServers::iterator iter2 = m_mapRobotServers.find(iter->first);
		if (iter2 != m_mapRobotServers.end())
		{
			RobotServer * pRobot = iter2->second;
			pRobot->SetListCtrlIndex(iter->second);
		}
		else
		{
			MsgAssert(0 , "ResetRobotServerIndex err , it not exist. sessionID=" << iter->first);
		}
	}
}

void RobotManager::DebugConnect()
{
	int nIndex = rand() % 123123;
	CString str;
	str.Format("%d", nIndex);
	m_pRpcListener->OnConnected(this, nIndex, (const char*)(str.GetBuffer()), false);
}

void RobotManager::DebugDisconnect()
{
	INT32 nIndex = m_mapRobotServerToTab.begin() != m_mapRobotServerToTab.end() ? m_mapRobotServerToTab.begin()->first : 0;
	if (nIndex != 0)
	{
		m_pRpcListener->OnDisconnected(this, nIndex, 0);
	}
}

RobotServer * RobotManager::OnUpdateCtrlServer(INT32 nIndex)
{
	MapTabToRobotServer::iterator iter = m_mapTabToRobotServer.find(nIndex);
	MsgAssert_Re0(iter != m_mapTabToRobotServer.end(), "OnUpdateCtrlServer MapTabToRobotServer listctrl index not exist. index=" << nIndex);

	MapRobotServers::iterator iter2 = m_mapRobotServers.find(iter->second);
	MsgAssert_Re0(iter2 != m_mapRobotServers.end(), "OnUpdateCtrlServer MapRobotServers listctrl index not exist. index=" << iter->second);

	return iter2->second;
}

RobotGroup			* RobotManager::OnUpdateRobotTab(INT32 nListCtrlIndex, INT32 nRobotTabIndex)
{
	RobotServer * pRobot = OnUpdateCtrlServer(nListCtrlIndex);
	MsgAssert_Re0(pRobot, "OnUpdateRobotTab listctrl index not exist.index = " << nListCtrlIndex);
	
	return pRobot->OnUpdateRobotTab(nRobotTabIndex);

}

CErrno RobotServerListener::OnConnected(Msg::RpcInterface * pRpcInterface, INT32 nSessionID, const std::string & strNetNodeName, bool bReconnect/* = false*/)
{
	if (m_pManager)
	{
		m_pManager->CreateRobotServer(nSessionID, strNetNodeName , bReconnect);
	}

	gDebugStream("connected from sessionID=" << nSessionID);
	return CErrno::Success();
}

CErrno RobotServerListener::OnDisconnected(Msg::RpcInterface * pRpcInterface, INT32 nSessionID, INT32 nPeerSessionID)
{
	if (m_pManager)
	{
		m_pManager->DeleteRobotServer(nSessionID);
	}

	gDebugStream("disconnected from sessionID=" << nPeerSessionID);
	return CErrno::Success();
}
