/************************************
FileName	:	GlableRpc.h
Author		:	generate by tools
HostName	:	devuser-PC
IP			:	10.236.37.66
Version		:	0.0.1
Description	:	��̬����,�޶���ʱͨ������ദ��.
************************************/
#ifndef __Robot_global_rpc_h__
#define __Robot_global_rpc_h__
#include "MsgLib/inc/IRpcMsgCallableObject.h" 
#include "RpcDefines.h" 

namespace Robot
{
	class GRpc : public Msg::IRpcMsgCallableObject
	{
		RPC_DEFINE_GRpc;
	public:
		GRpc(Msg::Object nID , Msg::RpcManager * pRpcManager)
			: Msg::IRpcMsgCallableObject(nID , pRpcManager)
		{
			GRpc::InitObjectFuncs();
		}
	public:
	};

}

#endif
