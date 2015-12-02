
// cctv.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once
#pragma comment(lib, "winmm")

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.
#include <opencv2\opencv.hpp>
#include "CvvImage.h"
#include <opencv2/ml/ml.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/world.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/xphoto.hpp>
#include <opencv2\latentsvm.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>
#include <stdio.h>
#include <mmsystem.h>

using namespace cv;
using namespace std;
using namespace xphoto;
using namespace lsvm;

// CcctvApp:
// 이 클래스의 구현에 대해서는 cctv.cpp을 참조하십시오.
//

class CcctvApp : public CWinApp
{
public:
	CcctvApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

extern CcctvApp theApp;