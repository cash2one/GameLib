#include "MasterHandler.h"
#include <fstream>
#include "RPCCallFuncs.h"
#include "SlaveRecord.h"

namespace Server
{  
	void MasterHandler::StartSyncToSlave(std::string strDBDir)
	{
		std::vector<std::string> files;
		GameDB::GetDefaultEnv()->GetChildren(strDBDir,&files);

		INT32 nType = 1;
		INT32 nSessionID = -1;
		CUtil::Parameters * pParams = GetInParams();
		if (pParams)
		{
			std::string strDBName = pParams->GetValue<std::string>(0);
			SlaveRecord * pRecord = GetSlaveRecord(strDBName);
			if (pRecord)
			{
				nSessionID = pRecord->GetSlaveSessionID();
			}
		}
		rpc_MasterStartSync(nSessionID, m_pRpcMsgCall->GetProxySrcID() , GetObjectID() , std::string() , nType , nType , CUtil::Chunk());

		for(size_t i = 0; i < files.size(); ++i)
		{
			std::string& filename = files[i];
			if(filename == "." || filename == "..")
				continue;

			SendFile(nSessionID, strDBDir + "/" + filename,filename);
		}

		nType = 2;
		rpc_MasterStartSync(nSessionID, m_pRpcMsgCall->GetProxySrcID() , GetObjectID() , std::string() , nType , nType , CUtil::Chunk());
	}

	bool MasterHandler::SendFile(INT32 nSessionID, const std::string & strFilePath , std::string & strFileName)
	{
		static const size_t cst_buffer_size = 1*1024*1024;

		std::fstream fs;
		fs.open(strFilePath.c_str(),std::ios_base::in | std::ios_base::binary);
		if(!fs.good())
			return false;

		fs.seekg(0,std::ios_base::end);
		INT64 filesize = (INT64)fs.tellg();
		fs.seekg(0,std::ios_base::beg);

		char* tmpbuf = new char[cst_buffer_size]; 

		while(filesize > 0)
		{
			size_t size = __min(filesize,cst_buffer_size);
			fs.read(tmpbuf,size);
			filesize -= (INT64)size; 

			INT32 nType = 0; 
			rpc_MasterStartSync(nSessionID, m_pRpcMsgCall->GetProxySrcID() , GetObjectID() , strFileName , (INT32)filesize , nType , CUtil::Chunk(tmpbuf , (UINT32)size));
			
			gDebugStream("send file:" << strFileName << "send size: " << size );
		}

		delete [] tmpbuf;

		return filesize == 0;

	}

	BOOL MasterHandler::SetSlaveRecordInfo(const std::string & strDBName, GameDB::User & objUser)
	{
		GameDB::UserAuth objAuth(objUser);

		MapSlaveRecordsT::iterator iter = m_mapSlaveRecords.find(strDBName);
		if (iter != m_mapSlaveRecords.end())
		{
			SlaveRecord * pRecord = iter->second;
			if (pRecord)
			{   
				pRecord->SetUserAuth(objAuth);
			}

			return TRUE;
		} 

		return FALSE;
	}

	BOOL MasterHandler::DelSlaveRecord(const std::string & strDBName)
	{
		MapSlaveRecordsT::iterator iter = m_mapSlaveRecords.find(strDBName);
		if (iter != m_mapSlaveRecords.end())
		{
			SAFE_DELETE(iter->second);

			m_mapSlaveRecords.erase(iter);
			return TRUE;
		}

		return FALSE;
	}

	INT32 MasterHandler::CreateSlaveRecord(const std::string & strDBName , INT32 nSessionID)
	{
		MapSlaveRecordsT::iterator iter = m_mapSlaveRecords.find(strDBName);
		if (iter != m_mapSlaveRecords.end())
		{
			SlaveRecord * pRecord = iter->second;
			if (pRecord)
			{ 
				if (pRecord->GetDBName() != strDBName)
				{
					gDebugStream("dbname didn't match old dbname. new=" << strDBName << ":old=" << pRecord->GetDBName());
				}
				pRecord->SetSlaveSessionID(nSessionID);
				pRecord->SetDBName(strDBName);
			}
		}
		else
		{
			SlaveRecord * pRecord = new SlaveRecord(this);
			if (pRecord)
			{ 
				pRecord->SetSlaveSessionID(nSessionID);
				pRecord->SetDBName(strDBName);

				m_mapSlaveRecords.insert(std::make_pair(strDBName , pRecord));
				++m_nRecordCount;
			}
		}

		return m_nRecordCount;
	}

	MasterHandler::~MasterHandler()
	{
		MapSlaveRecordsT::iterator iter = m_mapSlaveRecords.begin();
		for (;iter != m_mapSlaveRecords.end();++iter)
		{
			SAFE_DELETE(iter->second);
		}
		m_mapSlaveRecords.clear();
	}

	SlaveRecord * MasterHandler::GetSlaveRecord(const std::string & strDBName)
	{
		MapSlaveRecordsT::iterator iter = m_mapSlaveRecords.find(strDBName);
		if (iter != m_mapSlaveRecords.end())
		{
			return iter->second;
		}

		return NULL;
	}

	SlaveRecord	* MasterHandler::GetSlaveRecordBySessionID(INT32 nSessionID)
	{
		MapSlaveRecordsT::iterator iter = m_mapSlaveRecords.begin();
		for (;iter != m_mapSlaveRecords.end();++iter)
		{
			if (iter->second->GetSlaveSessionID() == nSessionID)
			{
				return iter->second;
			}
		}

		return NULL;
	}

	SlaveRecord				* MasterHandler::GetSlaveRecordBySlaveID(INT64 nSlaveID)
	{
		MapSlaveRecordsT::iterator iter = m_mapSlaveRecords.begin();
		for (; iter != m_mapSlaveRecords.end(); ++iter)
		{
			if (iter->second->GetSlaveID() == nSlaveID)
			{
				return iter->second;
			}
		}

		return NULL;
	}

	BOOL MasterHandler::SyncDataToSlave(const std::string & strDBName)
	{
		SlaveRecord	* pRecord = GetSlaveRecord(strDBName);
		if (pRecord)
		{
			pRecord->GetSaveCachePos();
		}

		return FALSE;
	}

}