
// cctv.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once
#pragma comment(lib, "winmm")

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include <opencv2\opencv.hpp>
#include "CvvImage.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>
#include <stdio.h>
#include <mmsystem.h>

using namespace cv;
using namespace std;

// CcctvApp:
// �� Ŭ������ ������ ���ؼ��� cctv.cpp�� �����Ͻʽÿ�.
//

class CcctvApp : public CWinApp
{
public:
	CcctvApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CcctvApp theApp;