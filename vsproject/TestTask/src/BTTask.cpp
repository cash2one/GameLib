#include "BTTask.h"
#include "LogLib/inc/Log.h"

namespace Task
{

	void BTTask::SetName(behaviac::string strName)
	{
		m_strName = strName;
		gDebugStream("BTTask::SetName=" << m_strName);
	}

	INT32 BTTask::GetCircleTaskCount(INT32 nIndex)
	{
		return 5;
	}

	void BTTask::ClearCircleTaskCount(INT32 nIndex)
	{
	}

	void BTTask::DecCircleTaskCount(INT32 nIndex , INT32 nCount)
	{
	}

	void BTTask::RecordCircleTaskID(INT32 nIndex, INT32 nID)
	{

	}

	void BTTask::NotifyClientCircleID(INT32 nIndex)
	{

	}

	bool BTTask::IsTaskFinished(INT32 nTaskID)
	{
		static INT32 nCount = 0;
		return  nCount++ % 2 == 0;
	}

	void BTTask::UpdateCircleTaskCount(INT32 & nIndex)
	{
		static INT32 nCount = 0;
		++nCount;
		nIndex = nCount;

	}



	BEGIN_PROPERTIES_DESCRIPTION(BTTask)
	{
		CLASS_DISPLAYNAME(L"BTTask����")
		CLASS_DESC(L"�������������������")
		REGISTER_METHOD(SetName).DESC(L"������������").DISPLAYNAME(L"������").PARAM_DISPLAY_INFO(L"������" , L"����������" , DefaultParam_t(L"���ר��"));
		REGISTER_METHOD(GetCircleTaskCount).DESC(L"���ѭ������Ĵ���").DISPLAYNAME(L"ѭ������").PARAM_DISPLAY_INFO(L"���ѭ���������", L"����ѭ����������ID", DefaultParam_t((INT32)0) , 1 , 1000);
		REGISTER_METHOD(ClearCircleTaskCount).DESC(L"���ѭ������Ĵ���").DISPLAYNAME(L"���ѭ������Ĵ���").PARAM_DISPLAY_INFO(L"���ѭ������Ĵ���", L"����ѭ����������ID", DefaultParam_t((INT32)0), 1, 1000);
		REGISTER_METHOD(DecCircleTaskCount).DESC(L"����ѭ������Ĵ���").DISPLAYNAME(L"����ѭ������Ĵ���").PARAM_DISPLAY_INFO(L"����ѭ������Ĵ���", L"����ѭ����������ID", DefaultParam_t((INT32)0), 1, 1000);
		REGISTER_METHOD(RecordCircleTaskID).DESC(L"��¼�����������ID").DISPLAYNAME(L"��¼�����������").PARAM_DISPLAY_INFO(L"��¼�����������", L"����ѭ����������ID", DefaultParam_t((INT32)0), 1, 1000);
		REGISTER_METHOD(NotifyClientCircleID).DESC(L"֪ͨ�ͻ��������������").DISPLAYNAME(L"֪ͨ�ͻ��������������").PARAM_DISPLAY_INFO(L"֪ͨ�ͻ��������������", L"����ѭ����������ID", DefaultParam_t((INT32)0), 1, 1000);
		REGISTER_METHOD(IsTaskFinished).DESC(L"�����Ƿ����").DISPLAYNAME(L"�����Ƿ����").PARAM_DISPLAY_INFO(L"����ID", L"����ID", DefaultParam_t((INT32)0), 1, 1000);
		REGISTER_METHOD(UpdateCircleTaskCount).DESC(L"��������ƴ�").DISPLAYNAME(L"��������ƴ�").PARAM_DISPLAY_INFO(L"����ID", L"����ID", DefaultParam_t((INT32)0), 1, 1000);

	}
	END_PROPERTIES_DESCRIPTION()
}