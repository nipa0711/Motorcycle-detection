/*
*   인공지능 수업 마지막 과제
*   제작 : 조현민
*   날짜 : 2015/11/23 ~ 2015/12/08
*
*   nipa0711@gmail.com
*   http://www.nipa0711.net
*/

// cctvDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CcctvDlg 대화 상자
class CcctvDlg : public CDialogEx
{
// 생성입니다.
public:
	CcctvDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CCTV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedConfirm();
	CString strAddress;
	CStatic ShowCCTV_Frame;
	string CStrToStr(CString str);
	CBitmap* IplImageToCBitmap(IplImage* img);
	CvvImage m_CVvImageObj1;
	IplImage IplImage1;

	CRect rect, rect2;
	int picWidth, picWidth2;
	int picHeight, picHeight2;
	CDC *pDC1, *pDC2;
	HDC hDC1, hDC2;

	Mat FRAME;
	Mat OriginalMat, ProcessedMat;
	void Process(Mat input);
	
	afx_msg void OnBnClickedSelectImage();
	int selectChk = 1;
	afx_msg void OnBnClickedSelectVideo();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic Show_Processed;
	CString strPathName;

	String motobike_cascade_name = "cascade.xml"; // cascade 불러오기
	CascadeClassifier motorbike_cascade;
	VideoCapture capture;
};
