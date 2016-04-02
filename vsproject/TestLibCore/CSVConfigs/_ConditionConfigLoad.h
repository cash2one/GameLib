/************************************
FileName	:	_ConditionConfigLoad.h
Author		:	generate by tools
HostName	:	DESKTOP-5AT4DK2
IP			:	192.168.16.104
Version		:	0.0.1
Date		:	2016-04-02 12:00:19
Description	:	csv�����ļ�
************************************/
#ifndef ___ConditionConfigLoad_define_h__
#define ___ConditionConfigLoad_define_h__
#include "CUtil/inc/Common.h "

#include "Timer/inc/Date.h "

namespace Config
{
	struct S_ConditionConfigLoad
	{
		INT32							nConditionID;	//����ID�������Ϳͻ�����һ��ö����֮һһ��Ӧ(����ļ��ɳ���Ķ�.)
		std::string						strServerCondition;	//�������������������ö��ֵ��ͬ.
		std::string						strServerAction;	//������ִ�ж���
		std::string						strClientCondition;	//�ͻ���������ͻ��˵�ö��ֵ��ͬ.
		std::string						strClientAction;	//�ͻ���ִ�ж���
	};


	class _ConditionConfigLoad
	{
	public:
		typedef std::vector<S_ConditionConfigLoad> CollectionConfigsT;

	public:
		bool LoadFrom(const std::string& filename);

	public:
		S_ConditionConfigLoad & Get(size_t row);

	public:
		inline size_t Count(){ return m_vtConfigs.size(); }

	private:
		CollectionConfigsT m_vtConfigs;
	};
}

#endif// end  ___ConditionConfigLoad_define_h__
