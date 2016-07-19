#pragma once
#include "Robot.h"
#include "json/json.h"
#include "MsgLib/inc/RpcInterface.h" 

class RobotServer;

class RobotGroup : Msg::RpcInterface
{
public:
	typedef std::map<INT32, INT32>					MapTabToRobot;		//5 ����showRobot�����ϵİ�ť��Robot��ӳ���ϵ
	typedef std::map<INT32, INT32>					MapRobotToTab;
	typedef std_unordered_map<INT32, Robot*>		MapRobots;

public:
	RobotGroup(const std::string & val, INT32 nSessionID , RobotServer * pRobotServer);
	~RobotGroup();

public:
	virtual CErrno				Init(Json::Value & conf);
	virtual CErrno				Cleanup(void);
	virtual CErrno				Update(void);

public:
	CErrno						CreateRobot(INT32 nSessionID, const std::string & strNetNodeName, bool bReconnect = false);
	void						OnCreateRobot(Robot * pRobot);
	CErrno						DeleteRobot(INT32 nSessionID);
	void						OnDeleteRobot(Robot * pRobot);

public:
	std::string					GetName() const { return m_strName; }
	void						SetName(std::string val) { m_strName = val; }
	INT32						GetSessionID() const { return m_nSessionID; }
	void						SetSessionID(INT32 val) { m_nSessionID = val; }
	INT32						GetRobotTabIndex() const { return m_nRobotTabIndex; }
	void						SetRobotTabIndex(INT32 val) { m_nRobotTabIndex = val; }
	INT32						GetCurRobotCount() const { return m_nCurRobotCount; }
	const MapRobots		&		GetMapRobots() const { return m_mapRobots; }

public:
	void						DebugConnect();
	void						DebugDisconnect();

protected:
	std::string					m_strName;
	INT32						m_nSessionID;
	INT32						m_nRobotTabIndex;		//5 ������Ҫ���������ϵ�Tab��index.ɾ����.
	INT32						m_nCurRobotCount;		//5 ��ǰ�����˵�����.
	MapRobots					m_mapRobots;
	MapTabToRobot				m_mapTabToRobot;
	MapRobotToTab				m_mapRobotToTab;
	RobotServer			*		m_pRobotServer;
};


class RobotListener : public Msg::IRpcListener
{
public:
	RobotListener(RobotGroup * pMaster)
		: m_pManager(pMaster)
	{

	}

public:
	virtual CErrno		OnConnected(Msg::RpcInterface * pRpcInterface, INT32 nSessionID, const std::string & strNetNodeName, bool bReconnect = false) override;
	virtual CErrno		OnDisconnected(Msg::RpcInterface * pRpcInterface, INT32 nSessionID, INT32 nPeerSessionID) override;

private:
	RobotGroup * m_pManager;
};