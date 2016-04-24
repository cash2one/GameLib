#include "GRpc.h"
#include "MsgLib/inc/RPCMsgCall.h"
#include "OrmHelper.h"

Msg::ObjectMsgCall * Client::GRpc::HandleHGet_RpcClient(INT32 nSessionID , Msg::Object objSrc , std_string & value/* = std::string()*/) 
{
	gDebugStream("HGet value:" << value);

	Msg::RpcCallbackPtr rpcCallback = GetCallback();
	if (rpcCallback)
	{
		STableKeyVal obj;
		obj.strTable = GetInParams()->GetValue<std::string>(0);
		obj.strKey = GetInParams()->GetValue<std::string>(1);
		obj.strVal = value;
		rpcCallback->OnCall(&obj);
	}
	std::cout << "HandleHGet_RpcClient value:" << value << std::endl;
	ReturnNULL;
}

Msg::ObjectMsgCall * Client::GRpc::HandleHGet_RpcTimeout(INT32 nSessionID , Msg::Object objSrc , std_string & table/* = std::string()*/ , std_string & key/* = std::string()*/) 
{


	std::cout << "HandleHGet_RpcTimeout" << std::endl;
	ReturnNULL;
}

