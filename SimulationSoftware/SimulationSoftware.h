
// SimulationSoftware.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSimulationSoftwareApp: 
// �йش����ʵ�֣������ SimulationSoftware.cpp
//

class CSimulationSoftwareApp : public CWinApp
{
public:
	CSimulationSoftwareApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSimulationSoftwareApp theApp;