// TestLibCore.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "CUtil/inc/CUtil.h"
#include "json/json.h"
#include "Timer/inc/TimerHelp.h"
#include "RobotServer.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CUtil::Init();

	Json::Value root;
	Json::JsonParase("RobotServer.conf", root);

	Robot::RobotServer::GetInstance().Init(root);

	while (true)
	{ 
		Robot::RobotServer::GetInstance().Update();
		Timer::sleep(1);
	}

	Robot::RobotServer::GetInstance().Cleanup();

	CUtil::Cleanup();
	return 0;
}

