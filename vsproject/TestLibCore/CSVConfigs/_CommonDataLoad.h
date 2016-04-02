/************************************
FileName	:	_CommonDataLoad.h
Author		:	generate by tools
HostName	:	DESKTOP-5AT4DK2
IP			:	192.168.16.104
Version		:	0.0.1
Date		:	2016-04-02 12:00:19
Description	:	csv�����ļ�
************************************/
#ifndef ___CommonDataLoad_define_h__
#define ___CommonDataLoad_define_h__
#include "CUtil/inc/Common.h "

#include "Timer/inc/Date.h "

namespace Config
{
	struct S_CommonDataLoad
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


	class _CommonDataLoad
	{
	public:
		typedef std::vector<S_CommonDataLoad> CollectionConfigsT;

	public:
		bool LoadFrom(const std::string& filename);

	public:
		S_CommonDataLoad & Get(size_t row);

	public:
		inline size_t Count(){ return m_vtConfigs.size(); }

	private:
		CollectionConfigsT m_vtConfigs;
	};
}

#endif// end  ___CommonDataLoad_define_h__
