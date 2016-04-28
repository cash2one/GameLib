﻿/************************************
FileName	:	ActivityConfigLoad.cpp
Author		:	generate by tools
HostName	:	devuser-PC
IP			:	10.236.40.128
Version		:	0.0.1
Date		:	2016-04-28 14:59:17
Description	:	csv读取文件实现
************************************/
#include "ActivityConfigLoad.h"
#include "CUtil/inc/CUtil.h"
#include "CUtil/inc/CSVReader.h"

namespace Config
{
	bool ActivityConfigLoad::LoadFrom(const std::string & filepath)
	{
		CUtil::CSVReader csv;
		if(csv.Load(filepath) != 0)
			return false;

		size_t index_ActivityId = csv.GetIndex("ActivityId", 2);
		MsgAssert_Re0(index_ActivityId != (size_t)-1 , "error ActivityId");

		size_t index_ActivityName = csv.GetIndex("ActivityName", 2);
		MsgAssert_Re0(index_ActivityName != (size_t)-1 , "error ActivityName");

		size_t index_ActivityLevelHigh = csv.GetIndex("ActivityLevelHigh", 2);
		MsgAssert_Re0(index_ActivityLevelHigh != (size_t)-1 , "error ActivityLevelHigh");

		size_t index_IsShowEntrance = csv.GetIndex("IsShowEntrance", 2);
		MsgAssert_Re0(index_IsShowEntrance != (size_t)-1 , "error IsShowEntrance");

		size_t index_EntranceIcon = csv.GetIndex("EntranceIcon", 2);
		MsgAssert_Re0(index_EntranceIcon != (size_t)-1 , "error EntranceIcon");

		size_t index_IsShowInterface = csv.GetIndex("IsShowInterface", 2);
		MsgAssert_Re0(index_IsShowInterface != (size_t)-1 , "error IsShowInterface");

		size_t index_InterfaceIcon = csv.GetIndex("InterfaceIcon", 2);
		MsgAssert_Re0(index_InterfaceIcon != (size_t)-1 , "error InterfaceIcon");

		size_t index_StartTimeWeek = csv.GetIndex("StartTimeWeek", 2);
		MsgAssert_Re0(index_StartTimeWeek != (size_t)-1 , "error StartTimeWeek");

		size_t index_EndTimeWeek = csv.GetIndex("EndTimeWeek", 2);
		MsgAssert_Re0(index_EndTimeWeek != (size_t)-1 , "error EndTimeWeek");

		size_t index_StartTimeDate = csv.GetIndex("StartTimeDate", 2);
		MsgAssert_Re0(index_StartTimeDate != (size_t)-1 , "error StartTimeDate");

		size_t index_EndTimeDate = csv.GetIndex("EndTimeDate", 2);
		MsgAssert_Re0(index_EndTimeDate != (size_t)-1 , "error EndTimeDate");

		size_t index_StartTime = csv.GetIndex("StartTime", 2);
		MsgAssert_Re0(index_StartTime != (size_t)-1 , "error StartTime");

		size_t index_EndTime = csv.GetIndex("EndTime", 2);
		MsgAssert_Re0(index_EndTime != (size_t)-1 , "error EndTime");

		size_t index_Description = csv.GetIndex("Description", 2);
		MsgAssert_Re0(index_Description != (size_t)-1 , "error Description");

		size_t index_RewardIcon = csv.GetIndex("RewardIcon", 2);
		MsgAssert_Re0(index_RewardIcon != (size_t)-1 , "error RewardIcon");

		size_t index_testdate = csv.GetIndex("testdate", 2);
		MsgAssert_Re0(index_testdate != (size_t)-1 , "error testdate");

		size_t index_testDateStruct = csv.GetIndex("testDateStruct[begin,end,actionConfig]", 2);
		MsgAssert_Re0(index_testDateStruct != (size_t)-1 , "error testDateStruct[begin,end,actionConfig]");

		size_t index_dateArray = csv.GetIndex("dateArray", 2);
		MsgAssert_Re0(index_dateArray != (size_t)-1 , "error dateArray");

		size_t index_testConfig = csv.GetIndex("testConfig", 2);
		MsgAssert_Re0(index_testConfig != (size_t)-1 , "error testConfig");

		size_t index_testConfig2 = csv.GetIndex("testConfig2", 2);
		MsgAssert_Re0(index_testConfig2 != (size_t)-1 , "error testConfig2");

		size_t index_dateCommon = csv.GetIndex("dateCommon", 2);
		MsgAssert_Re0(index_dateCommon != (size_t)-1 , "error dateCommon");

		size_t index_TestStructArray = csv.GetIndex("TestStructArray[test1,test2,test3,test4,test5,test6]", 2);
		MsgAssert_Re0(index_TestStructArray != (size_t)-1 , "error TestStructArray[test1,test2,test3,test4,test5,test6]");

		size_t index_TestStruct = csv.GetIndex("TestStruct[test1,test2,test3,test4,test6,test7]", 2);
		MsgAssert_Re0(index_TestStruct != (size_t)-1 , "error TestStruct[test1,test2,test3,test4,test6,test7]");

		for (size_t row = 4; row < csv.Count(); ++row)
		{
			SActivityConfigLoad conf;

			conf.ActivityId = csv.GetString(row , index_ActivityId);
			conf.ActivityName = csv.GetString(row , index_ActivityName);
			conf.ActivityLevelHigh = csv.GetInt32(row , index_ActivityLevelHigh);
			conf.IsShowEntrance = csv.GetBool(row , index_IsShowEntrance);
			{
				std::string __tmp = csv.GetString(row, index_EntranceIcon);
				CUtil::tokenize(__tmp, conf.EntranceIcon, ",", "", "\"");
			}

			conf.IsShowInterface = csv.GetBool(row , index_IsShowInterface);
			{
				std::string __tmp = csv.GetString(row, index_InterfaceIcon);
				CUtil::tokenize(__tmp, conf.InterfaceIcon, ",", "", "\"");
			}

			conf.StartTimeWeek = csv.GetInt32(row , index_StartTimeWeek);
			conf.EndTimeWeek = csv.GetInt32(row , index_EndTimeWeek);
			conf.StartTimeDate = csv.GetInt32(row , index_StartTimeDate);
			conf.EndTimeDate = csv.GetInt32(row , index_EndTimeDate);
			conf.StartTime = csv.GetString(row , index_StartTime);
			conf.EndTime = csv.GetString(row , index_EndTime);
			conf.Description = csv.GetInt32(row , index_Description);
			conf.RewardIcon = csv.GetString(row , index_RewardIcon);
			conf.testdate = csv.GetDate(row , index_testdate);
			{
				std::vector<std::string> vals;
				std::string __tmp = csv.GetString(row, index_testDateStruct);
				CUtil::tokenize(__tmp, vals, ",", "", "\"");
				for (size_t i = 0; i < vals.size(); ++i)
				{
					if(i == 0)
					{
						Timer::Date val(vals[i]);
						conf.testDateStruct.begin = val;
					}
					if(i == 1)
					{
						Timer::Date val(vals[i]);
						conf.testDateStruct.end = val;
					}
					if(i == 2)
					{
						INT64 val = (INT64)CUtil::atoi(vals[i].c_str());
						conf.testDateStruct.actionConfig = val;
					}
				}
			}

			{
				std::vector<std::string> vals;
				std::string __tmp = csv.GetString(row, index_dateArray);
				CUtil::tokenize(__tmp, vals, ",", "", "\"");
				for (size_t i = 0; i < vals.size(); ++i)
					conf.dateArray.push_back(Timer::Date(vals[i]));
			}

			conf.testConfig = csv.GetInt64(row , index_testConfig);
			conf.testConfig2 = csv.GetInt64(row , index_testConfig2);
			{
				std::vector<std::string> vals;
				std::string __tmp = csv.GetString(row, index_dateCommon);
				CUtil::tokenize(__tmp, vals, "=", "", "\"");
				for (size_t i = 0; i < vals.size(); ++i)
					conf.dateCommon.insert(std::make_pair(vals[0],(INT64)CUtil::atoi(vals[1])));
			}

			{
				std::vector<std::string> vals;
				std::string __tmp = csv.GetString(row, index_TestStructArray);
				CUtil::tokenize(__tmp, vals, "]", "", "\"");
				for (size_t i = 0; i < vals.size(); ++i)
				{
					std::string strVal = vals[i];
					if (strVal[0] == '[')
						strVal.assign(vals[i], 1, vals[i].length() - 1);

					SActivityConfigLoad::STestStructArray	array;
					std::vector<std::string> vals2;
					CUtil::tokenize(strVal, vals2, ",", "", "\"");
					for (size_t j = 0; j < vals2.size(); ++j)
					{
						if(j == 0)
						{
							bool val = CUtil::strtobool(vals2[j].c_str()) >= 1;
							array.test1 = val;
						}
						if(j == 1)
						{
							INT64 val = (INT64)CUtil::atoi(vals2[j].c_str());
							array.test2 = val;
						}
						if(j == 2)
						{
							double val = (float)CUtil::atof(vals2[j].c_str());
							array.test3 = val;
						}
						if(j == 3)
						{
							INT32 val = (INT32)CUtil::atoi(vals2[j].c_str());
							array.test4 = val;
						}
						if(j == 4)
						{
							std::string val = vals2[j].c_str();
							array.test5 = val;
						}
						if(j == 5)
						{
							INT64 val = (INT64)CUtil::atoi(vals2[j].c_str());
							array.test6 = val;
						}
					}
					conf.vecTestStructArray.push_back(array);
				}
			}

			{
				std::vector<std::string> vals;
				std::string __tmp = csv.GetString(row, index_TestStruct);
				CUtil::tokenize(__tmp, vals, ",", "", "\"");
				for (size_t i = 0; i < vals.size(); ++i)
				{
					if(i == 0)
					{
						bool val = CUtil::strtobool(vals[i].c_str()) >= 1;
						conf.TestStruct.test1 = val;
					}
					if(i == 1)
					{
						INT64 val = (INT64)CUtil::atoi(vals[i].c_str());
						conf.TestStruct.test2 = val;
					}
					if(i == 2)
					{
						double val = (float)CUtil::atof(vals[i].c_str());
						conf.TestStruct.test3 = val;
					}
					if(i == 3)
					{
						INT32 val = (INT32)CUtil::atoi(vals[i].c_str());
						conf.TestStruct.test4 = val;
					}
					if(i == 4)
					{
						std::string val = vals[i].c_str();
						conf.TestStruct.test6 = val;
					}
					if(i == 5)
					{
						INT64 val = (INT64)CUtil::atoi(vals[i].c_str());
						conf.TestStruct.test7 = val;
					}
				}
			}

			m_vtConfigs.push_back(conf);
		}

		return true;
	}

	SActivityConfigLoad & ActivityConfigLoad::Get(size_t row)
	{
		return m_vtConfigs.at(row);
	}

}

