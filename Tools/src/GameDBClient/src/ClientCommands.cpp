#include "ClientCommands.h"
#include "RPCCallFuncs.h"
#include "GameDB/inc/User.h"
#include "OrmTest/Orm_TestSlaveCollection.h"
#include "OrmTest/Orm_TestSlave.h"
#include "OrmTest/Orm_TestSlaveTable.h"
#include "OrmTest/Orm_TestSlaveFrom.h"
#include "OrmHelper.h"
#include "DBClient.h"

namespace Client
{ 
#define CHECK_ARGS_GREAT_COUNT(count) if( objParams.size() < count){ std::cout << "need " << count << " args." << std::endl; return ;}
#define CHECK_ARGS_EQUAL_COUNT(count) if( objParams.size() != count){ std::cout << "need least " << count << " args." << std::endl; return ;}

	Client::ClientCommands * g_pClientCommands = new Client::ClientCommands;

	ClientCommands::ClientCommands()
	{
		InitCommands();
	}

	void ClientCommands::InitCommands()
	{
		m_mapCommands["help"] = &ClientCommands::pfnHandleHelp;

		//5 ���ݿ���ز���
		m_mapCommands["selectdb"] = &ClientCommands::pfnHandleSelectDatabase;
		m_mapCommands["createdb"] = &ClientCommands::pfnHandleCreateDatabase;
		m_mapCommands["deletedb"] = &ClientCommands::pfnHandleDeleteDatabase;
		m_mapCommands["showdbs"] = &ClientCommands::pfnHandleShowDatabases;

		//5 ���,ɾ��,�޸��û�Ȩ�� 
		m_mapCommands["showusers"] = &ClientCommands::pfnHandleShowUsers;
		m_mapCommands["createuser"] = &ClientCommands::pfnHandleCreateUser;
		m_mapCommands["deleteuser"] = &ClientCommands::pfnHandleDeleteUser;
		m_mapCommands["modifyuser"] = &ClientCommands::pfnHandleModifyUser;

		//5 ���ݿ������޸�
		m_mapCommands["hset"] = &ClientCommands::pfnHandleHSet;
		m_mapCommands["hget"] = &ClientCommands::pfnHandleHGet;
		m_mapCommands["hsetnx"] = &ClientCommands::pfnHandleHSetNX;
		m_mapCommands["hsetow"] = &ClientCommands::pfnHandleHSetOW;
		m_mapCommands["hdel"] = &ClientCommands::pfnHandleHDel;
		m_mapCommands["hmultiset"] = &ClientCommands::pfnHandleHMultiSet;
		m_mapCommands["hmultiget"] = &ClientCommands::pfnHandleHMultiGet;
		m_mapCommands["hmultidel"] = &ClientCommands::pfnHandleHMultiDel;
		m_mapCommands["hsetincr"] = &ClientCommands::pfnHandleHSetIncr;
		m_mapCommands["hsetincrfloat"] = &ClientCommands::pfnHandleHSetIncrFloat;
		m_mapCommands["hgetkeys"] = &ClientCommands::pfnHandleHGetKeys; 
		m_mapCommands["hgetvals"] = &ClientCommands::pfnHandleHGetVals;
		m_mapCommands["hgetkeyvals"] = &ClientCommands::pfnHandleHKeyVals;
		m_mapCommands["hscan"] = &ClientCommands::pfnHandleHScan;
		m_mapCommands["hcount"] = &ClientCommands::pfnHandleHCount;
		m_mapCommands["hdrop"] = &ClientCommands::pfnHandleHDrop;
		m_mapCommands["hlist"] = &ClientCommands::pfnHandleHList;

		m_mapCommands["zset"] = &ClientCommands::pfnHandleZSet;
		m_mapCommands["zget"] = &ClientCommands::pfnHandleZGet;
		m_mapCommands["ztop"] = &ClientCommands::pfnHandleZTop;
		m_mapCommands["zrtop"] = &ClientCommands::pfnHandleZRTop;
		m_mapCommands["zdel"] = &ClientCommands::pfnHandleZDel;
		m_mapCommands["zdrop"] = &ClientCommands::pfnHandleZDrop;
		m_mapCommands["zcount"] = &ClientCommands::pfnHandleZCount;
		m_mapCommands["zlist"] = &ClientCommands::pfnHandleZList; 

		m_mapCommands["dump"] = &ClientCommands::pfnHandleDump;

		m_mapCommands["ormsetuser"] = &ClientCommands::pfnHandleOrmHSetUser;
		m_mapCommands["oci"] = &ClientCommands::pfnHandleOrmCollectionInsert;
		m_mapCommands["ocu"] = &ClientCommands::pfnHandleOrmCollectionUpdate;
		m_mapCommands["ocd"] = &ClientCommands::pfnHandleOrmCollectionDelete;
		m_mapCommands["ocq"] = &ClientCommands::pfnHandleOrmCollectionQuery;
	} 

	std::string ClientCommands::GetNearestCommand(const std::string & strCommand , INT32 nCount) const
	{
		std::string res;
		if (nCount >= 0)
		{
			std::vector<std::string> vecCommands;
			CollectionClientCommandsT::const_iterator iter = m_mapCommands.begin();
			for (;iter != m_mapCommands.end();++iter)
			{
				if (iter->first.find(strCommand) != std::string::npos)
				{
					vecCommands.push_back(iter->first);
				}
			}

			if (vecCommands.size() > 0)
			{
				nCount %= vecCommands.size();
				res = vecCommands[nCount];
			}
		}

		return res;
	}

	void ClientCommands::Execute(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_GREAT_COUNT(1);

		CollectionClientCommandsT::iterator iter = m_mapCommands.find(objParams[0]);
		if (iter != m_mapCommands.end())
		{
			iter->second(pClient , objParams);
		}
	}

	void ClientCommands::pfnHandleHelp(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		printf("\t""first:showdbs \n"
			"\t""second:selectdb dbname\n"
			"command list: \n"
			"���ݿ���ز���:"                      "\n" 
			"\t""showdbs"                      "\n" 
			"\t""createdb dbname"                      "\n"
			"\t""selectdb dbname"                      "\n"
			"\t""deletedb dbname"                      "\n"
			"\n"
			"���ݿ��û���ز���:"                      "\n" 
			"\t""showusers"                      "\n"
			"\t""createuser name password issys"                      "\n" 
			"\t""deleteuser name"                      "\n"
			"\t""modifyuser name password issys"                      "\n"
			"\n"
			"���ݿ�hash����ز���:"                      "\n" 
			"\t""hget table key"                      "\n"
			"\t""hset table key value"                "\n"
			"\t""hdel table key"                      "\n"
			"\t""hsetnx table key value"              "\n"
			"\t""hmultiset table key1 val1 key2 val2 ..." "\n"
			"\t""hmultiget table key1 key2 ..."       "\n"
			"\t""hmultidel table key1 key2 ..."           "\n"
			"\t""hsetincr table key int64value"            "\n"
			"\t""hsetincrfloat table key doublevalue"      "\n"
			"\t""hgetkeysvals table"                              "\n"
			"\t""hgetkeys table"                              "\n"
			"\t""hgetvals table"                              "\n"
			"\t""hdrop table"                            "\n"
			"\t""hcount table"								"\n"
			"\t""hlist"								"\n"
			"\n" 
			"���ݿ����򼯺���ز���:"                      "\n" 
			"\t""zget table key"                          "\n"
			"\t""zset table key score"                    "\n"
			"\t""zdel table key"                          "\n"
			"\t""ztop table min max(or limit)"                      "\n"
			"\t""zrtop table min max(or limit)"                     "\n"
			"\t""zdrop table"                            "\n"
			"\t""zcount table"                            "\n"
			"\t""zlist "                            "\n"
			"\n"
			"\t""dump"                                   "\n"
			"\t""exit"                                   "\n"
			);
	}

	void ClientCommands::pfnHandleShowDatabases(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(1);

		
		
		Client::rpc_HandleShowDatabases(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , NULL , Msg::SYNC_TYPE_SYNC);
	}

	void ClientCommands::pfnHandleSelectDatabase(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(2);  

		
		
		Client::rpc_HandleSelectDatabase(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1] , NULL, Msg::SYNC_TYPE_SYNC);
	}

	void ClientCommands::pfnHandleCreateDatabase(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(2);

		
		


		Client::rpc_HandleCreateDatabase(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1] , NULL, Msg::SYNC_TYPE_SYNC);
	}

	void ClientCommands::pfnHandleDeleteDatabase(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(2);

		
		 

		Client::rpc_HandleDeleteDatabase(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1], NULL , Msg::SYNC_TYPE_SYNC);
	} 

	void ClientCommands::pfnHandleShowUsers(DBClient * pClient , std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(1);

		
		
		Client::rpc_HandleShowUsers(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0), NULL , Msg::SYNC_TYPE_SYNC);
	}

	void ClientCommands::pfnHandleCreateUser(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(4);

		SINT8 isSys = (SINT8)CUtil::atoi(objParams[3]);
				
		 
		Client::rpc_HandleCreateUser(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1] , objParams[2] , isSys, NULL , Msg::SYNC_TYPE_SYNC);

		gDebugStream( "pfnHandleCreateUser"); 
	}

	void ClientCommands::pfnHandleDeleteUser(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(2);

		
		
		 
		Client::rpc_HandleDeleteUser(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1], NULL , Msg::SYNC_TYPE_SYNC);
	}

	void ClientCommands::pfnHandleModifyUser(DBClient * pClient ,  std::vector<std::string> & objParams)
	{ 
		CHECK_ARGS_EQUAL_COUNT(4);

		SINT8 isSys = (SINT8)CUtil::atoi(objParams[3]);

		
		 
		Client::rpc_HandleCreateUser(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1] , objParams[2] , isSys, NULL , Msg::SYNC_TYPE_SYNC);
	} 

	void ClientCommands::pfnHandleHSet(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(4);

		
		 
		Client::rpc_HandleHSet(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1] , objParams[2] , objParams[3], NULL , Msg::SYNC_TYPE_SYNC);

		gDebugStream( "pfnHandleHSet");
	}

	void ClientCommands::pfnHandleHGet(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(3);

		
		 
		Client::rpc_HandleHGet(pClient->GetServerSessionID(), pClient->GetServerID() , Msg::Object(0) , objParams[1] , objParams[2], NULL , Msg::SYNC_TYPE_SYNC);
		
		gDebugStream( "pfnHandleHGet");
	}


	void ClientCommands::pfnHandleHSetNX(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(4);

		
		 
		Client::rpc_HandleHSetNX(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1] , objParams[2] , objParams[3], NULL , Msg::SYNC_TYPE_SYNC);
		
	}

	void ClientCommands::pfnHandleHSetOW(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(4);

		
		 
		Client::rpc_HandleHSetOW(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1] , objParams[2] , objParams[3], NULL , Msg::SYNC_TYPE_SYNC);

	}

	void ClientCommands::pfnHandleHDel(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(3);

		
		 
		Client::rpc_HandleHDel(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1] , objParams[2], NULL , Msg::SYNC_TYPE_SYNC);

	}

	void ClientCommands::pfnHandleHMultiSet(DBClient * pClient ,  std::vector<std::string> & objParams)
	{

	}

	void ClientCommands::pfnHandleHMultiGet(DBClient * pClient ,  std::vector<std::string> & objParams)
	{

	}

	void ClientCommands::pfnHandleHMultiDel(DBClient * pClient ,  std::vector<std::string> & objParams)
	{

	}

	void ClientCommands::pfnHandleHSetIncr(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(4);

		INT64 llCount = CUtil::atoi(objParams[3]);

		
		 
		Client::rpc_HandleHSetIncr(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1] , objParams[2] ,llCount, NULL , Msg::SYNC_TYPE_SYNC);

	}

	void ClientCommands::pfnHandleHSetIncrFloat(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(4);

		double llCount = CUtil::atof(objParams[3]);

		
		 
		Client::rpc_HandleHSetIncrFloat(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1] , objParams[2] ,llCount, NULL , Msg::SYNC_TYPE_SYNC);

	}

	void ClientCommands::pfnHandleHGetKeys(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(2); 

		
		 
		Client::rpc_HandleHGetKeys(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1], NULL , Msg::SYNC_TYPE_SYNC);

	}

	void ClientCommands::pfnHandleHGetVals(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(2); 

		
		 
		Client::rpc_HandleHGetVals(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1], NULL , Msg::SYNC_TYPE_SYNC);

	}

	void ClientCommands::pfnHandleHKeyVals(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(2); 

		
		 
		Client::rpc_HandleHGetKeyVals(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1], NULL , Msg::SYNC_TYPE_SYNC); 
	}

	void ClientCommands::pfnHandleHScan(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(5); 
		INT64 llLimit = CUtil::atoi(objParams[4]);

		
		 
		Client::rpc_HandleHScan(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1] , objParams[2] , objParams[3] , llLimit, NULL , Msg::SYNC_TYPE_SYNC); 

	}

	void ClientCommands::pfnHandleHCount(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(2); 

		
		 
		Client::rpc_HandleHCount(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1], NULL , Msg::SYNC_TYPE_SYNC); 

	}

	void ClientCommands::pfnHandleHDrop(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(2); 

		
		 
		Client::rpc_HandleHDrop(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1], NULL , Msg::SYNC_TYPE_SYNC); 

	}

	void ClientCommands::pfnHandleHList(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		
		 
		Client::rpc_HandleHList(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0), NULL , Msg::SYNC_TYPE_SYNC); 

	}

	void ClientCommands::pfnHandleDump(DBClient * pClient ,  std::vector<std::string> & objParams)
	{   
		CHECK_ARGS_EQUAL_COUNT(1);

		
		 
		Client::rpc_HandleDump(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0), NULL , Msg::SYNC_TYPE_SYNC);

		gDebugStream( "pfnHandleDump"); 
	}
	
	void ClientCommands::pfnHandleZSet(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(4);

		INT64 llScore = CUtil::atoi(objParams[3]);
		
		 
		Client::rpc_HandleZSet(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1] , objParams[2] , llScore, NULL , Msg::SYNC_TYPE_SYNC);

		gDebugStream( "pfnHandleZSet");

	}

	void ClientCommands::pfnHandleZGet(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(3);

		
		 
		Client::rpc_HandleZGet(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1] , objParams[2], NULL , Msg::SYNC_TYPE_SYNC);

		gDebugStream( "pfnHandleZGet");

	}
	void ClientCommands::pfnHandleZTop(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_GREAT_COUNT(3);

		INT64 llStart = 0, llEnd = 0, llLimit = 0;
		if (objParams.size() == 5)
		{
			llStart = CUtil::atoi(objParams[2]);
			llEnd = CUtil::atoi(objParams[3]);
			llLimit = CUtil::atoi(objParams[4]);
		}
		else
		{
			llLimit = CUtil::atoi(objParams[2]);
		}
		
		Client::rpc_HandleZTop(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1] , llStart  , llEnd , llLimit, NULL , Msg::SYNC_TYPE_SYNC);
		
		gDebugStream( "pfnHandleZTop");

	}
	void ClientCommands::pfnHandleZRTop(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_GREAT_COUNT(3);

		
		

		INT64 llStart = 0, llEnd = 0, llLimit = 0;
		
		if (objParams.size() == 5)
		{
			llStart = CUtil::atoi(objParams[2]);
			llEnd = CUtil::atoi(objParams[3]);
			llLimit = CUtil::atoi(objParams[4]);
		}
		else
		{
			llLimit = CUtil::atoi(objParams[2]);
		} 
		
		Client::rpc_HandleZRTop(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1] , llStart , llEnd , llLimit, NULL , Msg::SYNC_TYPE_SYNC);
		 
		gDebugStream("pfnHandleZRTop"); 
	}

	void ClientCommands::pfnHandleOrmHSetUser(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(3);

		std::string strName = objParams[1];
		std::string strPwd = objParams[2];

		GameDB::User user;
		user.set_name(strName.c_str());
		user.set_pswd(strPwd.c_str());
		user.set_sysuser(true);

		Client::OrmInsert(&user);

		gDebugStream( "pfnHandleOrmHSet");
	}

	static Orm::TestSlaveCollection * s_pCollection = NULL;
	void ClientCommands::pfnHandleOrmCollectionUpdate(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		if (!s_pCollection)
		{
			gErrorStream("pfnHandleOrmCollectionUpdate s_pCollection is NULL. please call pfnHandleOrmCollectionInsert first");
			return;
		}

		//5 ������slave
		Orm::TestSlave * pTest = s_pCollection->GetTestSlave();
		INT64 value = 123;
		pTest->Setvalue(value);
		Client::OrmUpdate(pTest);
		gDebugStream("Insert TestSlave:id=" << pTest->Getid() << ":key=" << pTest->GetKey());
		
		//5 ����slaveFrom
		Orm::TestSlaveFrom * pSlaveFrom = s_pCollection->GetTestSlaveFrom();
		if (pSlaveFrom)
		{
			value = 456;
			pSlaveFrom->Setvalue(value);
			Client::OrmUpdate(pSlaveFrom);
			std::string value;
			pSlaveFrom->ToBson(value);
			gDebugStream("update slavefrom:id=" << pSlaveFrom->Getid() << ":key=" << pSlaveFrom->GetKey() << ":value=" << value);
		}

		int id = 3;
		GameDB::OrmVectorEx< Orm::TestSlaveTable *> & pTable = s_pCollection->GetTestSlaveTable();
		GameDB::OrmVectorEx< Orm::TestSlaveTable *>::iterator iter = pTable.begin();
		for (;iter != pTable.end();++iter)
		{
			Orm::TestSlaveTable * pNew = *iter;
			if (pNew)
			{
				Orm::TestStruct id3;
				id3.p1 = 1;
				id3.p2 = 3;
				id3.p3 = 2;
				id3.p5.push_back(1);
				id3.p5.push_back(3);
				id3.p5.push_back(6);
				pNew->Setid3(id3);
			}
		}

		GameDB::OrmVectorEx<Orm::TestSlaveTable  *> & objItems = s_pCollection->GetTestSlaveTable();
		for (int i = 0; i < objItems.size(); ++i)
		{
			Client::OrmUpdate(objItems[i]);
		}

 		gDebugStream( "pfnHandleOrmCollectionUpdate" );
	}

	void ClientCommands::pfnHandleOrmCollectionInsert(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		INT64 id = 1;
		if (!s_pCollection)
		{
			s_pCollection = new Orm::TestSlaveCollection; //5 ��һ����Ҫ���������ռ���,�������ռ���Ŀǰmasterid�Ƕ���.��Ϊ�����Ҫ�����¶���,��Ҫ��masterid����.
			s_pCollection->SetMasterID(id);
		}

		//5 ������slave
		Orm::TestSlave * pTest = s_pCollection->GetTestSlave();
		INT64 value = 123;
		pTest->Setvalue(value);
		Client::OrmInsert(pTest);
		gDebugStream("Insert TestSlave:id=" << pTest->Getid() << ":key=" << pTest->GetKey());

		//5 ����slavetable
		Orm::TestSlaveTable * pNew = s_pCollection->CreateTestSlaveTable();				
		id += 1;
		pNew->Setid2(CUtil::itoa(id));

		Orm::TestStruct id3;
		id3.p1 = 1;
		id3.p2 = 3;
		id3.p3 = 2; 
		id3.p5.push_back(1);
		id3.p5.push_back(3);
		id3.p5.push_back(6);
		pNew->Setid3(id3);

		GameDB::OrmVectorEx<Orm::TestSlaveTable  *> & objItems = s_pCollection->GetTestSlaveTable();
		for (int i = 0;i < objItems.size();++i)
		{
			Client::OrmInsert(objItems[i]);
			std::string value;
			objItems[i]->ToBson(value);
			gDebugStream("Insert TestSlaveTable:id=" << objItems[i]->Getid() << ":key=" << objItems[i]->GetKey() << ":value=" << value);
		}

		//5 ����slaveFrom
		Orm::TestSlaveFrom * pSlaveFrom = s_pCollection->GetTestSlaveFrom();
		if (pSlaveFrom)
		{
			value = 456;
			pSlaveFrom->Setvalue(value);
			Client::OrmInsert(pSlaveFrom);
			std::string value;
			pSlaveFrom->ToBson(value);
			gDebugStream("Insert slavefrom:id=" << pSlaveFrom->Getid() << ":key=" << pSlaveFrom->GetKey() << ":value=" << value);
		}
		gDebugStream( "pfnHandleOrmCollectionInsert" );
	}

	void ClientCommands::pfnHandleOrmCollectionDelete(DBClient * pClient, std::vector<std::string> & objParams)
	{
		if (!s_pCollection)
		{
			gErrorStream("pfnHandleOrmCollectionDelete s_pCollection is NULL. please call pfnHandleOrmCollectionInsert first");
			return;
		}

		//5 ������slave
		Orm::TestSlave * pTest = s_pCollection->GetTestSlave();
		Client::OrmDelete(pTest);

		GameDB::OrmVectorEx<Orm::TestSlaveTable  *> & objItems = s_pCollection->GetTestSlaveTable();
		for (int i = 0; i < objItems.size(); ++i)
		{
			Client::OrmDelete(objItems[i]);
		}

		//5 ����slaveFrom
		Orm::TestSlaveFrom * pSlaveFrom = s_pCollection->GetTestSlaveFrom();
		if (pSlaveFrom)
		{
			Client::OrmDelete(pSlaveFrom);
			gDebugStream("Delete slavefrom:id=" << pSlaveFrom->Getid() << ":key=" << pSlaveFrom->GetKey());
		}
		gDebugStream("pfnHandleOrmCollectionDelete");
	}

	void ClientCommands::pfnHandleOrmCollectionQuery(DBClient * pClient, std::vector<std::string> & objParams)
	{
		class TestSlaveQuery : public Msg::RpcCallback
		{
		public:
			TestSlaveQuery()
			{
				m_pCollection = new Orm::TestSlaveCollection;
				m_pCollection->SetMasterID(1);
			}
			~TestSlaveQuery()
			{
				SAFE_DELETE(m_pCollection);
			}

		public:
			virtual INT32 OnCall(void * pContext)
			{
				STableKeyVal * pObj = (STableKeyVal *)pContext;
				if (m_pCollection != NULL && pObj != NULL)
				{
					m_pCollection->LoadBson(pObj->strVal.c_str(), pObj->strVal.length());
					gDebugStream("orm query testslave.TestSlave_id=" << m_pCollection->GetTestSlave()->Getvalue() << ":TestSlaveFrom_id=" << m_pCollection->GetTestSlaveFrom()->Getvalue());

					GameDB::OrmVectorEx<Orm::TestSlaveTable  *> & objItems = m_pCollection->GetTestSlaveTable();
					for (int i = 0; i < objItems.size(); ++i)
					{
						gDebugStream("orm query slavetable_id=" << objItems[i]->Getid() << ":slavetable_id=" << objItems[i]->Getid2() << ":id3=" << objItems[i]->Getid3().p5[1] << ":slavetable_id4=" << objItems[i]->Getid4());
					}
				}
				return 0;
			}

		public:
			Orm::TestSlaveCollection * m_pCollection;
		};
		DECLARE_BOOST_POINTERS(TestSlaveQuery);
		TestSlaveQueryPtr pCallback(new TestSlaveQuery);

		//5 ������slave
		Orm::TestSlave * pTest = pCallback->m_pCollection->GetTestSlave();
		Client::OrmQuery(pTest, pCallback);
		Client::OrmQuery(pCallback->m_pCollection->GetTestSlaveFrom(), pCallback);
// 
// 		GameDB::OrmVectorEx<Orm::TestSlaveTable  *> & objItems = s_pCollection->GetTestSlaveTable();
// 		for (int i = 0; i < objItems.size(); ++i)
// 		{
// 			Client::OrmDelete(objItems[i]);
// 		}
// 
// 		//5 ����slaveFrom
// 		Orm::TestSlaveFrom * pSlaveFrom = s_pCollection->GetTestSlaveFrom();
// 		if (pSlaveFrom)
// 		{
// 			Client::OrmDelete(pSlaveFrom);
// 			gDebugStream("Delete slavefrom:id=" << pSlaveFrom->Getid() << ":key=" << pSlaveFrom->GetKey());
// 		}
		gDebugStream("pfnHandleOrmCollectionQuery");
	}

	void ClientCommands::pfnHandleZDel(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(3);

		
		 
		Client::rpc_HandleZDel(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1] , objParams[2], NULL , Msg::SYNC_TYPE_SYNC); 

	}

	void ClientCommands::pfnHandleZDrop(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(2);

		
		 
		Client::rpc_HandleZDrop(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1], NULL , Msg::SYNC_TYPE_SYNC); 
	}

	void ClientCommands::pfnHandleZCount(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(2);

		
		 
		Client::rpc_HandleZCount(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0) , objParams[1], NULL , Msg::SYNC_TYPE_SYNC); 

	}

	void ClientCommands::pfnHandleZList(DBClient * pClient ,  std::vector<std::string> & objParams)
	{
		CHECK_ARGS_EQUAL_COUNT(1);

		
		 
		Client::rpc_HandleZList(pClient->GetServerSessionID() , pClient->GetServerID() , Msg::Object(0), NULL , Msg::SYNC_TYPE_SYNC);  
	}

}