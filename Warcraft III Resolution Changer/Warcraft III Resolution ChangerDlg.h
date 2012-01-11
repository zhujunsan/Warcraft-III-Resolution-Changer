// Warcraft III Resolution ChangerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CWarcraftIIIResolutionChangerDlg 对话框
class CWarcraftIIIResolutionChangerDlg : public CDialog
{
// 构造
public:
	CWarcraftIIIResolutionChangerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_WARCRAFTIIIRESOLUTIONCHANGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAbout();
	CButton m_cOK;
	CEdit m_cScreenResolution;
	CEdit m_cWCSR;
	CEdit m_cX;
	CEdit m_cY;
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedOk();
	CStatic m_c169;
	CStatic m_c43;
	afx_msg void OnEnChangeX();
	afx_msg void OnEnChangeY();
	CStatic m_c1610;
};
