#pragma once
#include "CUtil/inc/Common.h"

const INT32 cnBtnXLengthSpace		= 5;		//5 �����˰�ť��X��Ŀ�϶����
const INT32 cnBtnYLengthSpace		= 7;		//5 �����˰�ť��X��Ŀ�϶����
const INT32 cnTabYPosOffset			= 21;		//5 �Ի����tab��ǩ�ĸ߶�ƫ��
const INT32 cnBtnXLength			= 30;		//5 �����˵İ�ťX�᳤��			
const INT32 cnBtnYLength			= 21;		//5 �����˵İ�ťY�᳤��
const INT32 cst_btn_id				= 10000;	//5 �����˵İ�ťID���ĸ�����ʼ.
const INT32 cnMaxRobotBtnNum		= 2000;		//5 ��ʼ���������˰�ť�ĸ���.
const INT32 cnColumnWidth			= 60;		//5 ��ʾ������ÿһ�еĿ��
const INT32 cnMinRobotDlgWidth		= cnColumnWidth * 7;	//5 �Ի������С���
const INT32 cnRobotStartID			= 10000;	//5 �����˵���ŴӶ��ٿ�ʼ.

enum EListColType
{
	LIST_START = 0,
	LIST_NAME = 0,
	LIST_PROF,
	LIST_LEVEL,
	LIST_STATUE,
	LIST_NOTE,

	LIST_NUM
};

//5 �滻�򵥵�Mapĳ��Key�������ұߵ�ֵ.һ��������ĳ��Key��ɾ����,����Ļ�����ǰ��.��һҪ��֤�����map,�ڶ�����Ҫ�����ͷŵ�map
template<typename MAP , typename Key>
void		ReplaceSimpleMapRightKey(MAP &map1, MAP &map2 , Key key)
{
	MAP temp;
	MAP::iterator iter = map1.find(key);
	if (iter != map1.end())
	{
		if (iter != map1.begin())
		{
			temp.insert(map1.begin(), iter);
		}
		
		for (++iter; iter != map1.end(); ++iter)
		{
			key = iter->first;
			temp.insert(std::make_pair(key - 1, iter->second));
		}

		if (temp.size() >= 0)
		{
			map2.clear();
			map2.swap(temp);
		}
	}
	temp.clear();
}

//5 ����ĺ����滻��,������Ե�Ҳ��Ҫ�滻.
template<typename MAP1, typename MAP2>
void		ResetMapKey(MAP1 & map1, MAP2 & map2)
{
	map2.clear();
	MAP1::iterator iter = map1.begin();
	for (; iter != map1.end();++iter)
	{
		map2.insert(std::make_pair(iter->second , iter->first));
	}
}