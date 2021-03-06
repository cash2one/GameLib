#include "ServerHandler.h"
#include "RPCCallFuncs.h"

Msg::ObjectMsgCall * Server::ServerHandler::HandleHSetOW_RpcServer(INT32 nSessionID , Msg::Object objSrc , std_string &table/* = std::string()*/ , std_string & key/* = std::string()*/ , std_string & value/* = std::string()*/  )
{
	INT32 res = -1;

	if (key.size() == 0 || table.size() == 0 || !this->GetDataBase())
	{
		Return(res);
	}

	GameDB::Database * pDB = this->GetDataBase(); 

	GameDB::Operate oper;
	GameDB::HashTable::HSetOW(*pDB , oper , table , key , value);
	if (oper.IsSuccess())
	{
		SyncDataToSlave(oper);

		res = 0;
		gDebugStream("table:" << table << "key:" << key << "value:" << value << "success."); 
	} 

	gDebugStream("HandleHSetOW_RpcServer "<< res);
	Return(res);
}

