/*
*   �ΰ����� ���� ������ ����
*   ���� : ������
*   ��¥ : 2015/11/23 ~ 2015/12/08
* 
*   nipa0711@gmail.com
*   http://www.nipa0711.net
*/


// cctvDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "cctv.h"
#include "cctvDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CcctvDlg ��ȭ ����

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


// CcctvDlg �޽��� ó����

BOOL CcctvDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
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
	selectChk = 1; // �ʱ� ���ð��� �̹���

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CcctvDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
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

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
			UpdateData(FALSE); // ���� ���� ��Ʈ�ѷ�

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
			//MessageBox(_T("" + strPathName), _T("PATH")); // ��� Ȯ�ο�

			strAddress = strPathName;
			UpdateData(FALSE); // ���� ���� ��Ʈ�ѷ�

			if (!capture.isOpened())
			{
				MessageBox(_T("Error loading Video"), _T("Warning"));
			}
			else
			{
				SetTimer(1, 30, NULL); // ID, �и��ʸ���
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
	if (!motorbike_cascade.load(motobike_cascade_name)) // cascade �ε� Ȯ��
	{
		MessageBox(_T("Error loading Cascade"), _T("Error"));
	}

	std::vector<Rect> motorbike;
	Mat frame_gray;

	cvtColor(input, frame_gray, COLOR_BGR2GRAY); // BGR ������ GRAY �������� ��ȯ
	equalizeHist(frame_gray, frame_gray); // ������׷� �յ�ȭ

	//-- Detect motorbike
	motorbike_cascade.detectMultiScale(frame_gray, motorbike, 1.1, 6, 0 | CASCADE_FIND_BIGGEST_OBJECT, Size(30, 30));  // CASCADE_SCALE_IMAGE
	
	/* 
	InputArray image, vector<Rect>& objects, double scaleFactor=1.1, int minNeighbors=3, int flags=0, Size minSize=Size()

	objects ? Vector of rectangles where each rectangle contains the detected object, the rectangles may be partially outside the original image.
	numDetections ? Vector of detection numbers for the corresponding objects. An object��s number of detections is the number of neighboring positively classified rectangles that were joined together to form the object.
	scaleFactor ? Parameter specifying how much the image size is reduced at each image scale.
	minNeighbors ? Parameter specifying how many neighbors each candidate rectangle should have to retain it.
	flags ? Parameter with the same meaning for an old cascade as in the function cvHaarDetectObjects. It is not used for a new cascade.
	minSize ? Minimum possible object size. Objects smaller than that are ignored.
	*/

	for (size_t i = 0; i < motorbike.size(); i++)
	{
		rectangle(input, Point(motorbike[i].x, motorbike[i].y), Point(motorbike[i].x + motorbike[i].width, motorbike[i].y + motorbike[i].height), Scalar(255, 0, 255), 2, 8, 0); // 2- ���β�, 8- ��Ÿ��
	}

	IplImage1 = input;
	m_CVvImageObj1.CopyOf(&IplImage1);
	m_CVvImageObj1.DrawToHDC(hDC2, &rect2);

	frame_gray.release();
}

string CcctvDlg::CStrToStr(CString str) // CString ���� String ������ ��ȯ
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CButton* pButton = (CButton*)GetDlgItem(IDC_SelectImage);
	pButton->SetCheck(TRUE);
	selectChk = 1;
}


void CcctvDlg::OnBnClickedSelectVideo()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CButton* pButton = (CButton*)GetDlgItem(IDC_SelectVideo);
	pButton->SetCheck(TRUE);
	selectChk = 2;
}

void CcctvDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
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
			KillTimer(1); // Ÿ�̸� ����
			MessageBox(_T("������ ����"), _T("Notice"));
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}
