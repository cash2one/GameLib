﻿// attention dont't change this line:std::string ActivityId;std::string ActivityName;INT32 ActivityLevelLow;INT32 ActivityLevelHigh;bool IsShowEntrance;std::vector<std::string> EntranceIcon;bool IsShowInterface;std::vector<std::string> InterfaceIcon;INT32 StartTimeWeek;INT32 EndTimeWeek;INT32 StartTimeDate;INT32 EndTimeDate;std::string StartTime;std::string EndTime;INT32 Description;std::string RewardIcon;Timer::Date testdate;testDateStructTimer::Date begin;Timer::Date end;std_unordered_map<INT64 , SActionConfig *> actionConfig;std::vector<Timer::Date> dateArray;ActionConfig testConfig;ActionConfig testConfig2;std::map<std::string , INT64> dateCommon;TestStructArraybool test1;INT64 test2;double test3;INT32 test4;std::string test5;std_unordered_map<INT64 , SActionConfig *> test6;TestStructbool test1;INT64 test2;double test3;INT32 test4;std::string test6;std_unordered_map<INT64 , SActionConfig *> test7;
/************************************
FileName	:	ActivityConfig.cpp
Author		:	generate by tools
HostName	:	DESKTOP-5AT4DK2
IP			:	192.168.16.104
Version		:	0.0.1
Date		:	2016-05-09 23:54:53
Description	:	csv读取数据文件实现
************************************/
#include "ActivityConfig.h"
#include "LogLib/inc/Log.h"
#include "ActionConfig.h"

namespace Config
{
	ActivityConfig * g_pActivityConfig = NULL;

	//tools after data load success , call OnLoad;
	BOOL ActivityConfig::OnLoad()
	{
		return FALSE;
	}
}

