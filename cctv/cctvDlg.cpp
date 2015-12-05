/*
*   인공지능 수업 마지막 과제
*   제작 : 조현민
*   날짜 : 2015/11/23 ~ 2015/12/08
* 
*   nipa0711@gmail.com
*   http://www.nipa0711.net
*/


// cctvDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "cctv.h"
#include "cctvDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CcctvDlg 대화 상자

CcctvDlg::CcctvDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CCTV_DIALOG, pParent)
	, strAddress(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcctvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, strAddress);
	DDX_Control(pDX, IDC_ShowCCTV, ShowCCTV_Frame);
	DDX_Control(pDX, IDC_ShowProcessed, Show_Processed);
}

BEGIN_MESSAGE_MAP(CcctvDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Confirm, &CcctvDlg::OnBnClickedConfirm)
	ON_BN_CLICKED(IDC_SelectImage, &CcctvDlg::OnBnClickedSelectImage)
	ON_BN_CLICKED(IDC_SelectVideo, &CcctvDlg::OnBnClickedSelectVideo)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CcctvDlg 메시지 처리기

BOOL CcctvDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CStatic *staticSize = (CStatic *)GetDlgItem(IDC_ShowCCTV);
	CStatic *staticSize2 = (CStatic *)GetDlgItem(IDC_ShowProcessed);

	staticSize->GetClientRect(rect);
	picWidth = rect.Width();
	picHeight = rect.Height();

	staticSize2->GetClientRect(rect2);
	picWidth2 = rect2.Width();
	picHeight2 = rect2.Height();

	CButton* pButton = (CButton*)GetDlgItem(IDC_SelectImage);
	pButton->SetCheck(TRUE);
	selectChk = 1; // 초기 선택값은 이미지

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CcctvDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CcctvDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		rect = CRect(0, 0, picWidth, picHeight);
		pDC1 = ShowCCTV_Frame.GetDC();
		hDC1 = pDC1->GetSafeHdc();

		rect2 = CRect(0, 0, picWidth2, picHeight2);
		pDC2 = Show_Processed.GetDC();
		hDC2 = pDC2->GetSafeHdc();

		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CcctvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CcctvDlg::OnBnClickedConfirm()
{
	switch (selectChk)
	{
	case 1:
	{
		CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Image(*.BMP,*.JPG,*.PNG)|*.BMP;*.JPG;*.PNG|All Files(*.*)|*.*||"));
		if (IDOK == dlg.DoModal())
		{
			strPathName = dlg.GetPathName();
			OriginalMat = imread(CStrToStr(strPathName));
			strAddress = strPathName;
			UpdateData(FALSE); // 변수 값을 컨트롤로

			IplImage1 = OriginalMat;
			m_CVvImageObj1.CopyOf(&IplImage1);
			m_CVvImageObj1.DrawToHDC(hDC1, &rect);

			if (!motorbike_cascade.load(motobike_cascade_name))
			{
				MessageBox(_T("Error loading motorbike cascade"), _T("Warning"));
			}
			else
			{
				Process(OriginalMat);
			}
		}
	}
	break;

	case 2:
	{
		Mat temp;

		CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Video(*.MP4,*.AVI)|*.MP4;*.AVI;|All Files(*.*)|*.*||"));
		if (IDOK == dlg.DoModal())
		{
			strPathName = dlg.GetPathName();

			capture.open(CStrToStr(strPathName));
			//MessageBox(_T("" + strPathName), _T("PATH")); // 경로 확인용

			strAddress = strPathName;
			UpdateData(FALSE); // 변수 값을 컨트롤로

			if (!capture.isOpened())
			{
				MessageBox(_T("Error loading Video"), _T("Warning"));
			}
			else
			{
				SetTimer(1, 30, NULL); // ID, 밀리초마다
			}
		}		
	}

	break;

	default:
		break;
	}
}

void CcctvDlg::Process(Mat input)
{
	if (!motorbike_cascade.load(motobike_cascade_name)) // cascade 로딩 확인
	{
		MessageBox(_T("Error loading Cascade"), _T("Error"));
	}

	std::vector<Rect> motorbike;
	Mat frame_gray;

	cvtColor(input, frame_gray, COLOR_BGR2GRAY); // BGR 영상을 GRAY 영상으로 변환
	equalizeHist(frame_gray, frame_gray); // 히스토그램 균등화

	//-- Detect motorbike
	motorbike_cascade.detectMultiScale(frame_gray, motorbike, 1.1, 6, 0 | CASCADE_FIND_BIGGEST_OBJECT, Size(30, 30));  // CASCADE_SCALE_IMAGE
	
	/* 
	InputArray image, vector<Rect>& objects, double scaleFactor=1.1, int minNeighbors=3, int flags=0, Size minSize=Size()

	objects ? Vector of rectangles where each rectangle contains the detected object, the rectangles may be partially outside the original image.
	numDetections ? Vector of detection numbers for the corresponding objects. An object’s number of detections is the number of neighboring positively classified rectangles that were joined together to form the object.
	scaleFactor ? Parameter specifying how much the image size is reduced at each image scale.
	minNeighbors ? Parameter specifying how many neighbors each candidate rectangle should have to retain it.
	flags ? Parameter with the same meaning for an old cascade as in the function cvHaarDetectObjects. It is not used for a new cascade.
	minSize ? Minimum possible object size. Objects smaller than that are ignored.
	*/

	for (size_t i = 0; i < motorbike.size(); i++)
	{
		rectangle(input, Point(motorbike[i].x, motorbike[i].y), Point(motorbike[i].x + motorbike[i].width, motorbike[i].y + motorbike[i].height), Scalar(255, 0, 255), 2, 8, 0); // 2- 선두께, 8- 선타입
	}

	IplImage1 = input;
	m_CVvImageObj1.CopyOf(&IplImage1);
	m_CVvImageObj1.DrawToHDC(hDC2, &rect2);

	frame_gray.release();
}

string CcctvDlg::CStrToStr(CString str) // CString 형을 String 형으로 변환
{
	string outputStr = string(CT2CA(str.operator LPCWSTR()));
	return outputStr;
}

CBitmap* CcctvDlg::IplImageToCBitmap(IplImage* img)
{
	CDC dc;
	CDC memDC;

	if (!dc.CreateDC(L"DISPLAY", NULL, NULL, NULL))
		return NULL;

	if (!memDC.CreateCompatibleDC(&dc))
		return NULL;

	CBitmap* bmp = new CBitmap();
	CBitmap* pOldBitmap;

	bmp->CreateCompatibleBitmap(&dc, img->width, img->height);
	pOldBitmap = memDC.SelectObject(bmp);

	CvvImage cvImage; // you will need OpenCV_2.2.0- to use CvvImage 
	cvImage.CopyOf(img);
	cvImage.Show(memDC.m_hDC, 0, 0, img->width, img->height, 0, 0);
	cvImage.Destroy();

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	dc.DeleteDC();

	return bmp;
}

void CcctvDlg::OnBnClickedSelectImage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CButton* pButton = (CButton*)GetDlgItem(IDC_SelectImage);
	pButton->SetCheck(TRUE);
	selectChk = 1;
}


void CcctvDlg::OnBnClickedSelectVideo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CButton* pButton = (CButton*)GetDlgItem(IDC_SelectVideo);
	pButton->SetCheck(TRUE);
	selectChk = 2;
}

void CcctvDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (nIDEvent == 1)
	{
		capture >> FRAME;
		OriginalMat = FRAME;

		if (!FRAME.empty())
		{
			IplImage1 = OriginalMat;
			m_CVvImageObj1.CopyOf(&IplImage1);
			m_CVvImageObj1.DrawToHDC(hDC1, &rect);

			Process(FRAME);
		}
		else
		{
			KillTimer(1); // 타이머 종료
			MessageBox(_T("동영상 종료"), _T("Notice"));
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}
