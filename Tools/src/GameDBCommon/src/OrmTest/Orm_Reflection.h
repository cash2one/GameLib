/************************************
FileName	:	Orm_Reflection.h
Author		:	generate by tools
HostName	:	devuser-PC
IP			:	10.236.40.128
Version		:	0.0.1
Date		:	2016-04-29 17:20:53
Description	:	���slave�����������.
************************************/
#ifndef __Orm_Orm__feflection_h__
#define __Orm_Orm__feflection_h__
#include "GameDB/inc/Orm.h"

namespace Orm
{
	extern const char * cst_slaves_of_TestSlave[];
	extern INT64 cst_slaves_hash_of_TestSlave[];

	extern GameDB::Orm * CreateObject(bson::bo & obj , std::string & metaname);
	extern GameDB::Orm * CreateObject(const char * data,size_t size , std::string & metaname);
	extern GameDB::Orm * CreateObject(bson::bo & obj , std::string & metaname);
	extern BOOL GetSlaveTableMasterIDFromBson(const char * data,size_t size , const std::string & strTableName ,const std::string & key , INT64 & intValue , std::string & strValue);
	extern BOOL GetSlaveTableMasterIDFromBson(bson::bo & obj , const std::string & strTableName ,const std::string & key , INT64 & intValue , std::string & strValue);
	
}//Orm

#endif
