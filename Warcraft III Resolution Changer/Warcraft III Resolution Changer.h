// Warcraft III Resolution Changer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWarcraftIIIResolutionChangerApp:
// �йش����ʵ�֣������ Warcraft III Resolution Changer.cpp
//

class CWarcraftIIIResolutionChangerApp : public CWinApp
{
public:
	CWarcraftIIIResolutionChangerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWarcraftIIIResolutionChangerApp theApp;