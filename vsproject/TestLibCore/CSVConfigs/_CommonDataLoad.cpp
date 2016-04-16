﻿/************************************
FileName	:	_CommonDataLoad.cpp
Author		:	generate by tools
HostName	:	DESKTOP-5AT4DK2
IP			:	192.168.16.104
Version		:	0.0.1
Date		:	2016-04-11 23:20:11
Description	:	csv读取文件实现
************************************/
#include "_CommonDataLoad.h"
#include "CUtil/inc/CUtil.h"
#include "CUtil/inc/CSVReader.h"

namespace Config
{
	bool _CommonDataLoad::LoadFrom(const std::string & filepath)
	{
		CUtil::CSVReader csv;
		if(csv.Load(filepath) != 0)
			return false;

		size_t index_id = csv.GetIndex("id", 2);
		MsgAssert_Re0(index_id != (size_t)-1 , "error id");

		size_t index_boolCommon = csv.GetIndex("boolCommon", 2);
		MsgAssert_Re0(index_boolCommon != (size_t)-1 , "error boolCommon");

		size_t index_boolCommon2 = csv.GetIndex("boolCommon2", 2);
		MsgAssert_Re0(index_boolCommon2 != (size_t)-1 , "error boolCommon2");

		size_t index_intCommon = csv.GetIndex("intCommon", 2);
		MsgAssert_Re0(index_intCommon != (size_t)-1 , "error intCommon");

		size_t index_int64Common = csv.GetIndex("int64Common", 2);
		MsgAssert_Re0(index_int64Common != (size_t)-1 , "error int64Common");

		size_t index_doubleCommon = csv.GetIndex("doubleCommon", 2);
		MsgAssert_Re0(index_doubleCommon != (size_t)-1 , "error doubleCommon");

		size_t index_stringCommon = csv.GetIndex("stringCommon", 2);
		MsgAssert_Re0(index_stringCommon != (size_t)-1 , "error stringCommon");

		size_t index_dateCommon = csv.GetIndex("dateCommon", 2);
		MsgAssert_Re0(index_dateCommon != (size_t)-1 , "error dateCommon");

		for (size_t row = 4; row < csv.Count(); ++row)
		{
			S_CommonDataLoad conf;

			conf.id = csv.GetInt32(row , index_id);
			{
				std::vector<std::string> vals;
				std::string __tmp = csv.GetString(row, index_boolCommon);
				CUtil::tokenize(__tmp, vals, "=", "", "\"");
				for (size_t i = 0; i < vals.size(); ++i)
					conf.boolCommon.insert(std::make_pair(vals[0],!!CUtil::atoi(vals[1])));
			}

			{
				std::vector<std::string> vals;
				std::string __tmp = csv.GetString(row, index_boolCommon2);
				CUtil::tokenize(__tmp, vals, "=", "", "\"");
				for (size_t i = 0; i < vals.size(); ++i)
					conf.boolCommon2.insert(std::make_pair(vals[0],!!CUtil::atoi(vals[1])));
			}

			{
				std::vector<std::string> vals;
				std::string __tmp = csv.GetString(row, index_intCommon);
				CUtil::tokenize(__tmp, vals, "=", "", "\"");
				for (size_t i = 0; i < vals.size(); ++i)
					conf.intCommon.insert(std::make_pair(vals[0],(INT32)CUtil::atoi(vals[1])));
			}

			{
				std::vector<std::string> vals;
				std::string __tmp = csv.GetString(row, index_int64Common);
				CUtil::tokenize(__tmp, vals, "=", "", "\"");
				for (size_t i = 0; i < vals.size(); ++i)
					conf.int64Common.insert(std::make_pair(vals[0],(INT64)CUtil::atoi(vals[1])));
			}

			{
				std::vector<std::string> vals;
				std::string __tmp = csv.GetString(row, index_doubleCommon);
				CUtil::tokenize(__tmp, vals, "=", "", "\"");
				for (size_t i = 0; i < vals.size(); ++i)
					conf.doubleCommon.insert(std::make_pair(vals[0],(double)CUtil::atof(vals[1])));
			}

			{
				std::vector<std::string> vals;
				std::string __tmp = csv.GetString(row, index_stringCommon);
				CUtil::tokenize(__tmp, vals, "=", "", "\"");
				for (size_t i = 0; i < vals.size(); ++i)
					conf.stringCommon.insert(std::make_pair(vals[0],vals[1]));
			}

			{
				std::vector<std::string> vals;
				std::string __tmp = csv.GetString(row, index_dateCommon);
				CUtil::tokenize(__tmp, vals, "=", "", "\"");
				for (size_t i = 0; i < vals.size(); ++i)
					conf.dateCommon.insert(std::make_pair(vals[0],Timer::Date(vals[1])));
			}

			m_vtConfigs.push_back(conf);
		}

		return true;
	}

	S_CommonDataLoad & _CommonDataLoad::Get(size_t row)
	{
		return m_vtConfigs.at(row);
	}

}

