
// RobotCtrl.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRobotCtrlApp: 
// �йش����ʵ�֣������ RobotCtrl.cpp
//

class CRobotCtrlApp : public CWinApp
{
public:
	CRobotCtrlApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CRobotCtrlApp theApp;