﻿/************************************
FileName	:	ActivityConfigLoad.h
Author		:	generate by tools
HostName	:	devuser-PC
IP			:	10.236.40.128
Version		:	0.0.1
Date		:	2016-05-10 12:12:16
Description	:	csv配置文件
************************************/
#ifndef __ActivityConfigLoad_define_h__
#define __ActivityConfigLoad_define_h__
#include "CUtil/inc/Common.h "
#include "Timer/inc/Date.h "

namespace Config
{
	struct SActivityConfigLoad
	{
		std::string						ActivityId;	//活动id
		std::string						ActivityName;	//活动名称
		INT32							ActivityLevelLow;	//显示等级下限,不到等级（不包括自身）不显示
		INT32							ActivityLevelHigh;	//显示等级上限，超过等级（不包括自身）不显示
		bool							IsShowEntrance;	//是否显示入口图标，入口图标和界面图标是互斥的；入口图标的形式适合单独放在外面的活动，界面图标就是通用活动中的图标
		std::vector<std::string>		EntranceIcon;	//入口图标
		bool							IsShowInterface;	//是否界面中显示，在这里显示，就是通用活动的形式；否则就是在入口图标中显示，显示为单独活动的形式
		std::vector<std::string>		InterfaceIcon;	//界面中图标
		INT32							StartTimeWeek;	//活动开始时间周，即每周的哪一天；这里填写的值优先级最大，与具体开始时间天，结束时间天无关
		INT32							EndTimeWeek;	//活动结束时间周
		INT32							StartTimeDate;	//活动开始时间天，不在此时间内，则活动不会显示
		INT32							EndTimeDate;	//活动结束时间天
		std::string						StartTime;	//活动开始时间点，不在此时间内则活动不显示
		std::string						EndTime;	//活动结束时间点
		INT32							Description;	//活动说明，通用活动界面中的活动描述
		std::string						RewardIcon;	//奖励图标，领奖界面中该活动的领奖图标
		Timer::Date						testdate;	//根据某些condition执行某些action;目前不支持括号和或.全部用&&(与)和!(非)表示满足一个条件可以执行多个action.可以写在一行(支持多个),或者多行.需要保证一个condition和至少一个action.如果没有也没啥.Action:调用玩家的或者帮会等的函数接口.

		//根据某些condition执行某些action;目前不支持括号和或.全部用&&(与)和!(非)表示满足一个条件可以执行多个action.可以写在一行(支持多个),或者多行.需要保证一个condition和至少一个action.如果没有也没啥.Action:调用玩家的或者帮会等的函数接口.
		struct StestDateStruct
		{
			Timer::Date					begin;
			Timer::Date					end;
			INT64	actionConfig;
		}testDateStruct;
		std::vector<Timer::Date>			dateArray;	//根据某些condition执行某些action;目前不支持括号和或.全部用&&(与)和!(非)表示满足一个条件可以执行多个action.可以写在一行(支持多个),或者多行.需要保证一个condition和至少一个action.如果没有也没啥.Action:调用玩家的或者帮会等的函数接口.
		INT64		testConfig;	//测试时间
		INT64		testConfig2;	//测试时间结构体.比如说活动开启结束时间
		std::map<std::string , INT64>		dateCommon;	//测试时间数组

		//嵌套表使用
		struct STestStructArray
		{
			bool						test1;
			INT64						test2;
			double						test3;
			INT32						test4;
			std::string					test5;
			INT64	test6;
		};
		std::vector<STestStructArray>		vecTestStructArray;

		//嵌套表使用
		struct STestStruct
		{
			bool						test1;
			INT64						test2;
			double						test3;
			INT32						test4;
			std::string					test6;
			INT64	test7;
		}TestStruct;
	};


	class ActivityConfigLoad
	{
	public:
		typedef std::vector<SActivityConfigLoad> CollectionConfigsT;

	public:
		bool				LoadFrom(const std::string& filename);

	public:
		SActivityConfigLoad &	Get(size_t row);

	public:
		inline size_t		Count(){ return m_vtConfigs.size(); }

	public:
		BOOL				xxCheckActivityId(SActivityConfigLoad & conf);
		BOOL				xxCheckActivityName(SActivityConfigLoad & conf);
		BOOL				xxCheckActivityLevelLow(SActivityConfigLoad & conf);
		BOOL				xxCheckActivityLevelHigh(SActivityConfigLoad & conf);
		BOOL				xxCheckIsShowEntrance(SActivityConfigLoad & conf);
		BOOL				xxCheckEntranceIcon(SActivityConfigLoad & conf);
		BOOL				xxCheckIsShowInterface(SActivityConfigLoad & conf);
		BOOL				xxCheckInterfaceIcon(SActivityConfigLoad & conf);
		BOOL				xxCheckStartTimeWeek(SActivityConfigLoad & conf);
		BOOL				xxCheckEndTimeWeek(SActivityConfigLoad & conf);
		BOOL				xxCheckStartTimeDate(SActivityConfigLoad & conf);
		BOOL				xxCheckEndTimeDate(SActivityConfigLoad & conf);
		BOOL				xxCheckStartTime(SActivityConfigLoad & conf);
		BOOL				xxCheckEndTime(SActivityConfigLoad & conf);
		BOOL				xxCheckDescription(SActivityConfigLoad & conf);
		BOOL				xxCheckRewardIcon(SActivityConfigLoad & conf);
		BOOL				xxChecktestdate(SActivityConfigLoad & conf);
		BOOL				xxChecktestDateStruct(SActivityConfigLoad & conf);
		BOOL				xxCheckdateArray(SActivityConfigLoad & conf);
		BOOL				xxChecktestConfig(SActivityConfigLoad & conf);
		BOOL				xxChecktestConfig2(SActivityConfigLoad & conf);
		BOOL				xxCheckdateCommon(SActivityConfigLoad & conf);
		BOOL				xxCheckTestStructArray(SActivityConfigLoad & conf);
		BOOL				xxCheckTestStruct(SActivityConfigLoad & conf);
	
	private:
		CollectionConfigsT	m_vtConfigs;
	};
}

#endif// end  __ActivityConfigLoad_define_h__
