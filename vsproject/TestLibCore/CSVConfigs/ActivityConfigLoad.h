/************************************
FileName	:	ActivityConfigLoad.h
Author		:	generate by tools
HostName	:	DESKTOP-5AT4DK2
IP			:	192.168.16.104
Version		:	0.0.1
Date		:	2016-03-27 12:57:27
Description	:	csv�����ļ�
************************************/
#ifndef __ActivityConfigLoad_define_h__
#define __ActivityConfigLoad_define_h__
#include "CUtil/inc/Common.h "

#include "Timer/inc/Date.h "

namespace Config
{
	struct SActivityConfigLoad
	{
		INT32							ActivityId;	//�id
		std::string						ActivityName;	//�����
		INT32							ActivityLevelHigh;	//��ʾ�ȼ����ޣ������ȼ�����������������ʾ
		bool							IsShowEntrance;	//�Ƿ���ʾ���ͼ�꣬���ͼ��ͽ���ͼ���ǻ���ģ����ͼ�����ʽ�ʺϵ�����������Ļ������ͼ�����ͨ�û�е�ͼ��
		std::vector<std::string>		EntranceIcon;	//���ͼ��
		bool							IsShowInterface;	//�Ƿ��������ʾ����������ʾ������ͨ�û����ʽ��������������ͼ������ʾ����ʾΪ���������ʽ
		std::vector<std::string>		InterfaceIcon;	//������ͼ��
		INT32							StartTimeWeek;	//���ʼʱ���ܣ���ÿ�ܵ���һ�죻������д��ֵ���ȼ��������忪ʼʱ���죬����ʱ�����޹�
		INT32							EndTimeWeek;	//�����ʱ����
		INT32							StartTimeDate;	//���ʼʱ���죬���ڴ�ʱ���ڣ���������ʾ
		INT32							EndTimeDate;	//�����ʱ����
		std::string						StartTime;	//���ʼʱ��㣬���ڴ�ʱ����������ʾ
		std::string						EndTime;	//�����ʱ���
		INT32							Description;	//�˵����ͨ�û�����еĻ����
		std::string						RewardIcon;	//����ͼ�꣬�콱�����иû���콱ͼ��
		Timer::Date						testdate;	//����ĳЩconditionִ��ĳЩaction;Ŀǰ��֧�����źͻ�.ȫ����&&(��)��!(��)��ʾ����һ����������ִ�ж��action.����д��һ��(֧�ֶ��),���߶���.��Ҫ��֤һ��condition������һ��action.���û��Ҳûɶ.Action:������ҵĻ��߰��ȵĺ����ӿ�.

		//����ʱ��
		struct StestDateStruct
		{
			Timer::Date					begin;
			Timer::Date					end;
		}testDateStruct;
		std::vector<Timer::Date>			dateArray;	//����ʱ��ṹ��.����˵���������ʱ��
	};


	class ActivityConfigLoad
	{
	public:
		typedef std::vector<SActivityConfigLoad> CollectionConfigsT;

	public:
		bool LoadFrom(const std::string& filename);

	public:
		SActivityConfigLoad & Get(size_t row);

	public:
		inline size_t Count(){ return m_vtConfigs.size(); }

	private:
		CollectionConfigsT m_vtConfigs;
	};
}

#endif// end  __ActivityConfigLoad_define_h__
