// attention dont't change this line:INT32 nConditionID;std::string strServerCondition;std::string strServerAction;std::string strClientCondition;std::string strClientAction;
/************************************
FileName	:	_ConditionConfig.h
Author		:	generate by tools
HostName	:	DESKTOP-5AT4DK2
IP			:	192.168.16.104
Version		:	0.0.1
Date		:	2016-04-02 12:00:19
Description	:	csv��ȡ�ļ�
************************************/
#ifndef __Config__ConditionConfig_define_h__
#define __Config__ConditionConfig_define_h__
#include "_ConditionConfigLoad.h"

namespace Config
{

	struct S_ConditionConfig
	{
		INT32							nConditionID;	//����ID�������Ϳͻ�����һ��ö����֮һһ��Ӧ(����ļ��ɳ���Ķ�.)
		std::string						strServerCondition;	//�������������������ö��ֵ��ͬ.
		std::string						strServerAction;	//������ִ�ж���
		std::string						strClientCondition;	//�ͻ���������ͻ��˵�ö��ֵ��ͬ.
		std::string						strClientAction;	//�ͻ���ִ�ж���
	};


	class _ConditionConfig
	{
	public:
		typedef std_unordered_map<INT32 , S_ConditionConfig> MapConfigsT;

	public:
		bool LoadFrom(const std::string& filepath);
		S_ConditionConfig * Get_ConditionConfig(INT32 nIndex);

	private:
		MapConfigsT m_mapConfigs;

	};
	extern _ConditionConfig * g_p_ConditionConfig;
}

#endif// end  __Config__ConditionConfig_define_h__
