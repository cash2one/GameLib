#pragma once
#include "CRobot.h"
#include "json/json.h"
#include "MsgLib/inc/RpcInterface.h" 
#include "MsgLib/inc/IRpcMsgCallableObject.h"
#include "MsgNameDefine.h"  
#include "RpcDefines.h" 

namespace Robot
{
	class RobotServer;

	class RobotGroup : public Msg::IRpcMsgCallableObject
	{
		RPC_DEFINE_RobotGroup;
	public:
		typedef std::map<INT32, INT32>					MapTabToRobot;		//5 ����showRobot�����ϵİ�ť��Robot��ӳ���ϵ
		typedef std::map<INT32, INT32>					MapRobotToTab;
		typedef std_unordered_map<INT32, CRobot*>		MapRobots;

	public:
		RobotGroup(const std::string & val, INT32 nSessionID, RobotServer * pRobotServer , Msg::Object id, Msg::RpcManager * pRpcManager);
		~RobotGroup();

	public:
		virtual CErrno				Init(Json::Value & conf);
		virtual CErrno				Cleanup(void);
		virtual CErrno				Update(void); 

	public:
		INT32						CreateRobot(const RobotInfo & info , Msg::Object objSrc);
		void						OnCreateRobot(CRobot * pRobot);
		CErrno						DeleteRobot(INT32 nSessionID);
		void						OnDeleteRobot(CRobot * pRobot);

	public:
		std::string					GetName() const { return m_strName; }
		void						SetName(std::string val) { m_strName = val; }
		INT32						GetRobotSessionID() const { return m_nRobotSessionID; }
		void						SetRobotSessionID(INT32 val) { m_nRobotSessionID = val; }
		INT32						GetRobotTabIndex() const { return m_nRobotTabIndex; }
		void						SetRobotTabIndex(INT32 val) { m_nRobotTabIndex = val; }
		INT32						GetCurRobotCount() const { return m_nCurRobotCount; }
		const MapRobots		&		GetMapRobots() const { return m_mapRobots; } 
		RobotServer			*		GetRobotServer() { return m_pRobotServer;  }

	protected:
		Json::Value					m_objConf;
		std::string					m_strName;
		INT32						m_nRobotSessionID;
		INT32						m_nRobotTabIndex;		//5 ������Ҫ���������ϵ�Tab��index.ɾ����.
		INT32						m_nCurRobotCount;		//5 ��ǰ�����˵�����.
		MapRobots					m_mapRobots;
		MapTabToRobot				m_mapTabToRobot;
		MapRobotToTab				m_mapRobotToTab;
		RobotServer			*		m_pRobotServer;
	};


// 	class RobotGroupListener : public Msg::IRpcListener
// 	{
// 	public:
// 		RobotGroupListener(RobotGroup * pMaster)
// 			: m_pManager(pMaster)
// 		{
// 
// 		}
// 
// 	public:
// 		virtual CErrno		OnConnected(Msg::RpcInterface * pRpcInterface, INT32 nSessionID, const std::string & strNetNodeName, bool bReconnect = false) override;
// 		virtual CErrno		OnDisconnected(Msg::RpcInterface * pRpcInterface, INT32 nSessionID, INT32 nPeerSessionID) override;
// 
// 	private:
// 		RobotGroup * m_pManager;
// 	};
}