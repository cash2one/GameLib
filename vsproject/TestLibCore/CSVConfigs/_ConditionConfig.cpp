﻿// attention dont't change this line:INT32 nConditionID;std::string strServerCondition;std::string strServerAction;std::string strClientCondition;std::string strClientAction;
/************************************
FileName	:	_ConditionConfig.cpp
Author		:	generate by tools
HostName	:	DESKTOP-5AT4DK2
IP			:	192.168.16.104
Version		:	0.0.1
Date		:	2016-04-05 00:29:30
Description	:	csv读取数据文件实现
************************************/
#include "_ConditionConfig.h"
#include "LogLib/inc/Log.h"

namespace Config
{
	bool _ConditionConfig::LoadFrom(const std::string & filepath)
	{
		if (m_bLoaded)
		{
			return false;
		}
		Config::_ConditionConfigLoad loadConfig;
		MsgAssert_Re0(loadConfig.LoadFrom(filepath + "_ConditionConfig.tabcsv") , "Error _ConditionConfigLoadFrom " << filepath + "_ConditionConfig.tabcsv");

		for(size_t i = 0; i < loadConfig.Count(); ++i)
		{
			Config::S_ConditionConfigLoad& config = loadConfig.Get(i);
			Config::S_ConditionConfig data;
			data.nConditionID = config.nConditionID;
			data.strServerCondition = config.strServerCondition;
			data.strServerAction = config.strServerAction;
			data.strClientCondition = config.strClientCondition;
			data.strClientAction = config.strClientAction;
			m_mapConfigs.insert(std::make_pair(data.nConditionID,data));
		}

		m_bLoaded = true;
		return true;
	}

	S_ConditionConfig * _ConditionConfig::Get_ConditionConfig(INT32 id , std::string strFilePath/* = ""*/)
	{
		if (!m_bLoaded)
		{
			LoadFrom(strFilePath);
		}
		MapConfigsT::iterator iter = m_mapConfigs.find(id);
		if(iter == m_mapConfigs.end())
		{
			gWarniStream( "_ConditionConfig::Get_ConditionConfig NotFound " << id);
			return NULL;
		}

		return &iter->second;
	}

	_ConditionConfig * g_p_ConditionConfig = NULL;
}

