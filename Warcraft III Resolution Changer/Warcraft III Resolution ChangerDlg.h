// Warcraft III Resolution ChangerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CWarcraftIIIResolutionChangerDlg �Ի���
class CWarcraftIIIResolutionChangerDlg : public CDialog
{
// ����
public:
	CWarcraftIIIResolutionChangerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WARCRAFTIIIRESOLUTIONCHANGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
