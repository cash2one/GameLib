#ifndef __gamedb_orm_helper_h__
#define __gamedb_orm_helper_h__
#include "GameDB/inc/DBCommon.h"
#include "GameDB/inc/Orm.h"

namespace GameDB
{
	//5 ������;,����֪����ʲô.
	enum EORM_MASK
	{
		ORM_NONE = 0,
	};

	enum EORM_OPERATION
	{
		OPERATION_INSERT,
		OPERATION_UPDATE,
		OPERATION_DELETE,

		OPERATION_MAX,
	};
	class OrmHelper
	{
	public:
		template<typename FUNC, typename NodeName, typename Target, typename Source>
		static CErrno OrmInsert(GameDB::Orm * obj, FUNC func, NodeName nodeName, Target target, Source src, EORM_MASK objMask = ORM_NONE)
		{
			MsgAssert_ReF(obj, "OrmInsert error obj.");

			std::string strTable, strKey, strValue;
			strTable = obj->GetTableName();
			strKey = obj->GetKey();
			obj->ToBson(strValue);

			//5 �������ֱ����������д.������ʵ�����ôд�ͻ������.��Ϊ����Ῠס.���Ը�Ϊ�첽д
			INT32 nRes = func(nodeName, target, src, strTable, strKey, strValue, NULL, 0, Msg::SYNC_TYPE_ASYNC);
			if (nRes == -1)
			{
				return CErrno::Failure();
			}
			return CErrno::Success();
		}

		template<typename FUNC, typename NodeName, typename Target, typename Source>
		static CErrno OrmUpdate(GameDB::Orm * obj, FUNC func, NodeName nodeName, Target target, Source src, EORM_MASK objMask = ORM_NONE)
		{
			MsgAssert_ReF(obj, "OrmUpdate error obj.");

			INT64 llOldHash = obj->CurHash();
			INT64 llNewHash = obj->HashMake(DEFAULT_HASH_SEED);

			if (llOldHash == llNewHash)
			{
				gDebugStream("OrmUpdate table: " << obj->GetTableName() << " key:" << obj->GetKey() << "is same hash.");

				return CErrno::Failure();
			}

			obj->HashUpdate(llNewHash);  //5 �и�Ǳ����.�����clone��һ��.��ô���hash��һ����.��ô����Ҫǿ�Ƶ���hashupdate(0)����

			std::string strTable, strKey, strValue;
			strTable = obj->GetTableName();
			strKey = obj->GetKey();
			obj->ToBson(strValue);

			//5 �������ֱ����������д.������ʵ�����ôд�ͻ������.��Ϊ����Ῠס.���Ը�Ϊ�첽д
			INT32 nRes = func(nodeName, target, src, strTable, strKey, strValue, NULL, 0, Msg::SYNC_TYPE_ASYNC);
			if (nRes == -1)
			{
				return CErrno::Failure();
			}
			return CErrno::Success();
		}

		//5 ���ﲻ��Ҫ���õײ��commit.��Ϊfunc��һ��
		template<typename FUNC, typename NodeName, typename Target, typename Source>
		static CErrno OrmDelete(GameDB::Orm * obj , FUNC func, NodeName nodeName, Target target, Source src, EORM_MASK objMask = ORM_NONE)
		{
			MsgAssert_ReF(obj, "OrmDelete error obj.");

			std::string strTable, strKey;
			strTable = obj->GetTableName();
			strKey = obj->GetKey();

			//5 �������ֱ����������д.������ʵ�����ôд�ͻ������.��Ϊ����Ῠס.���Ը�Ϊ�첽д
			func(nodeName, target, src, strTable, strKey, NULL, 0, Msg::SYNC_TYPE_ASYNC);

			return CErrno::Success();
		}
	
		template<typename FUNC, typename NodeName, typename Target, typename Source , typename QFUNC>
		static CErrno OrmQuery(GameDB::Orm * obj , FUNC func, NodeName nodeName, Target target, Source src, QFUNC qfunc, EORM_MASK objMask = ORM_NONE)
		{
			MsgAssert_ReF(obj, "OrmQuery error obj.");

			std::string strTable, strKey;
			strTable = obj->GetTableName();
			strKey = obj->GetKey();

			//5 �������ֱ����������д.������ʵ�����ôд�ͻ������.��Ϊ����Ῠס.���Ը�Ϊ�첽д
			func(nodeName, target, src, strTable, strKey, qfunc, 0, Msg::SYNC_TYPE_ASYNC);

			return CErrno::Success();
		}

		template<typename FUNC, typename NodeName, typename Target, typename Source , typename QFUNC>
		static CErrno OrmQuery(std::string Table, FUNC func, NodeName nodeName, Target target, Source src, QFUNC qfunc, EORM_MASK objMask = ORM_NONE)
		{
			std::string strTable;
			strTable = Table;

			//5 �������ֱ����������д.������ʵ�����ôд�ͻ������.��Ϊ����Ῠס.���Ը�Ϊ�첽д
			func(nodeName, target, src, strTable, qfunc, 0, Msg::SYNC_TYPE_ASYNC);

			return CErrno::Success();
		}

		static std::string GetTableNameFromBson(const char * data, size_t size)
		{
			mongo::BSONObj obj(data);
			MsgAssert_Re(obj.objsize() == size, NULL, "");
			return GetTableNameFromBson(obj);
		}

		static std::string GetTableNameFromBson(bson::bo & obj)
		{
			std::string strTableName;
			mongo::BSONObjIterator iter(obj);
			while (iter.more())
			{
				mongo::BSONElement be = iter.next();
				if (CUtil::strcmp(be.fieldName(), "_T") == 0)
				{
					strTableName = be.str();
					break;
				}
			}
			return strTableName;
		}

	};
}


#endif