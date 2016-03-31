// attention dont't change this line:INT32 id;std::map<std::string , bool> boolCommon;std::map<std::string , bool> boolCommon2;std::map<std::string , INT32> intCommon;std::map<std::string , INT64> int64Common;std::map<std::string , double> doubleCommon;std::map<std::string , std::string> stringCommon;std::map<std::string , Timer::Date> dateCommon;
/************************************
FileName	:	_CommonData.h
Author		:	generate by tools
HostName	:	DESKTOP-5AT4DK2
IP			:	192.168.16.104
Version		:	0.0.1
Date		:	2016-03-31 23:58:49
Description	:	csv��ȡ�ļ�
************************************/
#ifndef __Config__CommonData_define_h__
#define __Config__CommonData_define_h__
#include "_CommonDataLoad.h"

namespace Config
{

	struct S_CommonData
	{
		INT32							id;	//��ʱ����
		std::map<std::string , bool>		boolCommon;	//bool����ֵ
		std::map<std::string , bool>		boolCommon2;	//bool����ֵ2
		std::map<std::string , INT32>		intCommon;	//int����ֵ
		std::map<std::string , INT64>		int64Common;	//int64����ֵ
		std::map<std::string , double>		doubleCommon;	//double����ֵ
		std::map<std::string , std::string>		stringCommon;	//string����ֵ
		std::map<std::string , Timer::Date>		dateCommon;	//date����ֵ
	};


	class _CommonData
	{
	public:
		typedef std_unordered_map<INT32 , S_CommonData> MapConfigsT;

	public:
		bool LoadFrom(const std::string& filepath);
		S_CommonData * Get_CommonData(INT32 nIndex);

	private:
		MapConfigsT m_mapConfigs;

	};
	extern _CommonData * g_p_CommonData;
}

#endif// end  __Config__CommonData_define_h__
