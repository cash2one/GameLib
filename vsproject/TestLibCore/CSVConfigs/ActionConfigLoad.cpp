﻿/************************************
FileName	:	ActionConfigLoad.cpp
Author		:	generate by tools
HostName	:	DESKTOP-5AT4DK2
IP			:	192.168.16.104
Version		:	0.0.1
Date		:	2016-05-21 14:51:04
Description	:	csv读取文件实现
************************************/
#include "ActionConfigLoad.h"
#include "../Condition.h"
#include "CUtil/inc/CUtil.h"
#include "CUtil/inc/CSVReader.h"

namespace Config
{
	bool ActionConfigLoad::LoadFrom(const std::string & filepath)
	{
		if (m_bLoaded)
		{
			return true;
		}
		CUtil::CSVReader csv;
		if(csv.Load(filepath) != 0)
			return false;

		size_t index_curve_id = csv.GetIndex("curve_id", 2);
		MsgAssert_Re0(index_curve_id != (size_t)-1 , "error curve_id");

		size_t index_validStages = csv.GetIndex("validStages", 2);
		MsgAssert_Re0(index_validStages != (size_t)-1 , "error validStages");

		size_t index_wrapMode = csv.GetIndex("wrapMode", 2);
		MsgAssert_Re0(index_wrapMode != (size_t)-1 , "error wrapMode");

		size_t index_InterfaceIcon = csv.GetIndex("InterfaceIcon", 2);
		MsgAssert_Re0(index_InterfaceIcon != (size_t)-1 , "error InterfaceIcon");

		size_t index_attr_mod_val = csv.GetIndex("attr_mod_val", 2);
		MsgAssert_Re0(index_attr_mod_val != (size_t)-1 , "error attr_mod_val");

		size_t index_start_x = csv.GetIndex("start_x", 2);
		MsgAssert_Re0(index_start_x != (size_t)-1 , "error start_x");

		size_t index_col_1 = csv.GetIndex("col_1", 2);
		MsgAssert_Re0(index_col_1 != (size_t)-1 , "error col_1");

		size_t index_isLocal = csv.GetIndex("isLocal", 2);
		MsgAssert_Re0(index_isLocal != (size_t)-1 , "error isLocal");

		size_t index_TestStruct = csv.GetIndex("TestStruct[test1,test2,test3,test4,test6]", 2);
		MsgAssert_Re0(index_TestStruct != (size_t)-1 , "error TestStruct[test1,test2,test3,test4,test6]");

		size_t index_TestStructArray = csv.GetIndex("TestStructArray[test1,test2,test3,test4,test5]", 2);
		MsgAssert_Re0(index_TestStructArray != (size_t)-1 , "error TestStructArray[test1,test2,test3,test4,test5]");

		for (size_t row = 5; row < csv.Count(); ++row)
		{
			SActionConfigLoad conf;

			conf.curve_id = csv.GetInt64(row , index_curve_id);
			{
				std::vector<std::string> vals;
				std::string __tmp = csv.GetString(row, index_validStages);
				CUtil::tokenize(__tmp, vals, ",", "", "\"");
				for (size_t i = 0; i < vals.size(); ++i)
					conf.validStages.push_back((INT32)CUtil::atoi(vals[i].c_str()));
			}

			conf.wrapMode = csv.GetString(row , index_wrapMode);
			{
				std::string __tmp = csv.GetString(row, index_InterfaceIcon);
				CUtil::tokenize(__tmp, conf.InterfaceIcon, ",", "", "\"");
			}

			conf.attr_mod_val = csv.GetDouble(row , index_attr_mod_val);
			{
				std::vector<std::string> vals;
				std::string __tmp = csv.GetString(row, index_start_x);
				CUtil::tokenize(__tmp, vals, ",", "", "\"");
				for (size_t i = 0; i < vals.size(); ++i)
					conf.start_x.push_back((float)CUtil::atof(vals[i].c_str()));
			}

			conf.col_1 = csv.GetInt64(row , index_col_1);
			conf.isLocal = csv.GetBool(row , index_isLocal);
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
						std::string val = vals[i].c_str();
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
				}
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

					SActionConfigLoad::STestStructArray	array;
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
					}
					conf.vecTestStructArray.push_back(array);
				}
			}

			MsgAssert_Re0(xxCheckcurve_id(conf) , "curve_id check error.");
			MsgAssert_Re0(xxCheckvalidStages(conf) , "validStages check error.");
			MsgAssert_Re0(xxCheckwrapMode(conf) , "wrapMode check error.");
			MsgAssert_Re0(xxCheckInterfaceIcon(conf) , "InterfaceIcon check error.");
			MsgAssert_Re0(xxCheckattr_mod_val(conf) , "attr_mod_val check error.");
			MsgAssert_Re0(xxCheckstart_x(conf) , "start_x check error.");
			MsgAssert_Re0(xxCheckcol_1(conf) , "col_1 check error.");
			MsgAssert_Re0(xxCheckisLocal(conf) , "isLocal check error.");
			MsgAssert_Re0(xxCheckTestStruct(conf) , "TestStruct check error.");
			MsgAssert_Re0(xxCheckTestStructArray(conf) , "TestStructArray check error.");
	
			m_vtConfigs.push_back(conf);
		}

		return true;
	}

	SActionConfigLoad & ActionConfigLoad::Get(size_t row)
	{
		return m_vtConfigs.at(row);
	}

	BOOL	ActionConfigLoad::xxCheckcurve_id(SActionConfigLoad & conf)
	{
		return TRUE;
	}
	
	BOOL	ActionConfigLoad::xxCheckvalidStages(SActionConfigLoad & conf)
	{
		return TRUE;
	}
	
	BOOL	ActionConfigLoad::xxCheckwrapMode(SActionConfigLoad & conf)
	{
		return TRUE;
	}
	
	BOOL	ActionConfigLoad::xxCheckInterfaceIcon(SActionConfigLoad & conf)
	{
		return TRUE;
	}
	
	BOOL	ActionConfigLoad::xxCheckattr_mod_val(SActionConfigLoad & conf)
	{
		return TRUE;
	}
	
	BOOL	ActionConfigLoad::xxCheckstart_x(SActionConfigLoad & conf)
	{
		return TRUE;
	}
	
	BOOL	ActionConfigLoad::xxCheckcol_1(SActionConfigLoad & conf)
	{
		return TRUE;
	}
	
	BOOL	ActionConfigLoad::xxCheckisLocal(SActionConfigLoad & conf)
	{
		return TRUE;
	}
	
	BOOL	ActionConfigLoad::xxCheckTestStruct(SActionConfigLoad & conf)
	{
		return TRUE;
	}
	
	BOOL	ActionConfigLoad::xxCheckTestStructArray(SActionConfigLoad & conf)
	{
		return TRUE;
	}
	
	
}

