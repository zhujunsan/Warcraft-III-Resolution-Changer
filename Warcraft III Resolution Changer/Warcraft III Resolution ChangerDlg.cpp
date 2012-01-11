// Warcraft III Resolution ChangerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Warcraft III Resolution Changer.h"
#include "Warcraft III Resolution ChangerDlg.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CWarcraftIIIResolutionChangerDlg �Ի���




CWarcraftIIIResolutionChangerDlg::CWarcraftIIIResolutionChangerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWarcraftIIIResolutionChangerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWarcraftIIIResolutionChangerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OK, m_cOK);
	DDX_Control(pDX, IDC_SR, m_cScreenResolution);
	DDX_Control(pDX, IDC_WCSR, m_cWCSR);
	DDX_Control(pDX, IDC_X, m_cX);
	DDX_Control(pDX, IDC_Y, m_cY);
	DDX_Control(pDX, IDC_169, m_c169);
	DDX_Control(pDX, IDC_43, m_c43);
	DDX_Control(pDX, IDC_1610, m_c1610);
}

BEGIN_MESSAGE_MAP(CWarcraftIIIResolutionChangerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_ABOUT, &CWarcraftIIIResolutionChangerDlg::OnBnClickedAbout)
	ON_BN_CLICKED(ID_EXIT, &CWarcraftIIIResolutionChangerDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_OK, &CWarcraftIIIResolutionChangerDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_X, &CWarcraftIIIResolutionChangerDlg::OnEnChangeX)
	ON_EN_CHANGE(IDC_Y, &CWarcraftIIIResolutionChangerDlg::OnEnChangeY)
END_MESSAGE_MAP()


// CWarcraftIIIResolutionChangerDlg ��Ϣ�������

BOOL CWarcraftIIIResolutionChangerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
//		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//�õ�, �ҿ�ʼ��ʼ����
	CString temp;
	unsigned int m_WarX = 0;
	unsigned int m_WarY = 0;
	//��ȡ��Ļ�ֱ���
	int m_ScreenX=GetSystemMetrics(SM_CXSCREEN);
	int m_ScreenY=GetSystemMetrics(SM_CYSCREEN);
	//����Ļ�ֱ����ı�������ʾ
	temp.Format(_T("%d��%d"), m_ScreenX, m_ScreenY);
	m_cScreenResolution.SetWindowTextW(temp);
	//�趨X, Y�ı���Ϊ��ǰ��Ļ�ֱ���
	temp.Format(_T("%d"), m_ScreenY);
	m_cY.SetWindowTextW(temp);
	temp.Format(_T("%d"), m_ScreenX);
	m_cX.SetWindowTextW(temp);
	//��ȡע�����ħ��III�ķֱ���
	HKEY hKey;
	if(RegOpenKeyEx(HKEY_CURRENT_USER, _T(""), NULL, KEY_READ, &hKey) != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("�޷�����ע���!\r\n��ȷ�����������㹻��Ȩ��, Vista �� 7 �û���Ҫ�Թ���Ա����."), MB_ICONEXCLAMATION);
		SendMessage(WM_CLOSE);
	}
	else
	{
		if(RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III\\Video"), NULL, KEY_READ, &hKey) != ERROR_SUCCESS)
		{
			AfxMessageBox(_T("δ����ħ������III��ע�����!\r\n�����Ƿ�װ���˳�����ڰ�װ����������һ��."), MB_ICONEXCLAMATION);
			SendMessage(WM_CLOSE);
		}
		else
		{
			DWORD dwType, cbData, dwData;
			if (RegQueryValueEx(hKey, _T("reswidth"), NULL, &dwType, NULL, &cbData) == ERROR_SUCCESS)
				{
					if   (dwType == REG_DWORD)
					{   
					  dwData = (DWORD)-1;
					  ASSERT(cbData == 4);
					  if (RegQueryValueEx(hKey, _T("reswidth"), NULL, &dwType, (LPBYTE)&dwData, &cbData) == ERROR_SUCCESS)
					  {
						m_WarX = dwData;
					  }
					  else
					  {
						AfxMessageBox(_T("�޷���ȡ��ע���\"HKEY_CURRENT_USER\\Software\\Blizzard Entertainment\\Warcraft III\\Video\\reswidth\"��\r\n��������ע����ֵ."), MB_ICONEXCLAMATION);
						SendMessage(WM_CLOSE);
					  }
					}
				}
			if (RegQueryValueEx(hKey, _T("resheight"), NULL, &dwType, NULL, &cbData) == ERROR_SUCCESS)
				{
					if   (dwType == REG_DWORD)
					{   
					  dwData = (DWORD)-1;
					  ASSERT(cbData == 4);
					  if (RegQueryValueEx(hKey, _T("resheight"), NULL, &dwType, (LPBYTE)&dwData, &cbData) == ERROR_SUCCESS)
					  {
						m_WarY = dwData;
					  }
					  else
					  {
						AfxMessageBox(_T("�޷���ȡ��ע���\"HKEY_CURRENT_USER\\Software\\Blizzard Entertainment\\Warcraft III\\Video\\resheight\"��\r\n��������ע����ֵ."), MB_ICONEXCLAMATION);
						SendMessage(WM_CLOSE);
					  }
					}
				}

		}
	}
	RegCloseKey(hKey);
	//����Ļħ��III�ֱ�������ʾ
	temp.Format(_T("%d��%d"), m_WarX, m_WarY);
	m_cWCSR.SetWindowTextW(temp);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CWarcraftIIIResolutionChangerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWarcraftIIIResolutionChangerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CWarcraftIIIResolutionChangerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWarcraftIIIResolutionChangerDlg::OnBnClickedAbout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CWarcraftIIIResolutionChangerDlg::OnBnClickedExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SendMessage(WM_CLOSE);
}

void CWarcraftIIIResolutionChangerDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString temp;
	DWORD m_WarX = 0, m_WarY = 0;
	HKEY hKey;
	//ת���ı������ݵ�����
	m_cX.GetWindowTextW(temp);
	m_WarX = _wtoi(temp);
	m_cY.GetWindowTextW(temp);
	m_WarY = _wtoi(temp);
	//д��ע���
	if(RegOpenKeyEx(HKEY_CURRENT_USER, _T(""), NULL, KEY_READ, &hKey) != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("�޷�����ע���!\r\n��ȷ�����������㹻��Ȩ��, Vista �� 7 �û���Ҫ�Թ���Ա����."), MB_ICONEXCLAMATION);
		SendMessage(WM_CLOSE);
	}
	else
	{
		if(RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III\\Video"), NULL, KEY_WRITE|KEY_READ, &hKey) != ERROR_SUCCESS)
		{
			AfxMessageBox(_T("δ����ħ������III��ע�����!\r\n�����Ƿ�װ���˳�����ڰ�װ����������һ��."), MB_ICONEXCLAMATION);
			SendMessage(WM_CLOSE);
		}
		else
		{
		  if (RegSetValueEx(hKey, _T("reswidth"), NULL, REG_DWORD, (LPBYTE)&m_WarX, 4) != ERROR_SUCCESS)
			AfxMessageBox(_T("�޷�д���ע���\"HKEY_CURRENT_USER\\Software\\Blizzard Entertainment\\Warcraft III\\Video\\reswidth\"��\r\n��������ע����ֵ."), MB_ICONEXCLAMATION);
		  if (RegSetValueEx(hKey, _T("resheight"), NULL, REG_DWORD, (LPBYTE)&m_WarY, 4) != ERROR_SUCCESS)
			AfxMessageBox(_T("�޷�д���ע���\"HKEY_CURRENT_USER\\Software\\Blizzard Entertainment\\Warcraft III\\Video\\resheight\"��\r\n��������ע����ֵ."), MB_ICONEXCLAMATION);
		}
	}
	RegCloseKey(hKey);
	
	//д���˶�һ��:��ȡע�����ħ��III�ķֱ���
	if(RegOpenKeyEx(HKEY_CURRENT_USER, _T(""), NULL, KEY_READ, &hKey) != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("�޷�����ע���!\r\n��ȷ�����������㹻��Ȩ��, Vista �� 7 �û���Ҫ�Թ���Ա����."), MB_ICONEXCLAMATION);
		SendMessage(WM_CLOSE);
	}
	else
	{
		if(RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III\\Video"), NULL, KEY_READ, &hKey) != ERROR_SUCCESS)
		{
			AfxMessageBox(_T("δ����ħ������III��ע�����!\r\n�����Ƿ�װ���˳�����ڰ�װ����������һ��."), MB_ICONEXCLAMATION);
			SendMessage(WM_CLOSE);
		}
		else
		{
			DWORD dwType, cbData, dwData;
			if (RegQueryValueEx(hKey, _T("reswidth"), NULL, &dwType, NULL, &cbData) == ERROR_SUCCESS)
				{
					if   (dwType == REG_DWORD)
					{   
					  dwData = (DWORD)-1;
					  ASSERT(cbData == 4);
					  if (RegQueryValueEx(hKey, _T("reswidth"), NULL, &dwType, (LPBYTE)&dwData, &cbData) == ERROR_SUCCESS)
					  {
						m_WarX = dwData;
					  }
					  else
					  {
						AfxMessageBox(_T("�޷���ȡ��ע���\"HKEY_CURRENT_USER\\Software\\Blizzard Entertainment\\Warcraft III\\Video\\reswidth\"��\r\n��������ע����ֵ."), MB_ICONEXCLAMATION);
						SendMessage(WM_CLOSE);
					  }
					}
				}
			if (RegQueryValueEx(hKey, _T("resheight"), NULL, &dwType, NULL, &cbData) == ERROR_SUCCESS)
				{
					if   (dwType == REG_DWORD)
					{   
					  dwData = (DWORD)-1;
					  ASSERT(cbData == 4);
					  if (RegQueryValueEx(hKey, _T("resheight"), NULL, &dwType, (LPBYTE)&dwData, &cbData) == ERROR_SUCCESS)
					  {
						m_WarY = dwData;
					  }
					  else
					  {
						AfxMessageBox(_T("�޷���ȡ��ע���\"HKEY_CURRENT_USER\\Software\\Blizzard Entertainment\\Warcraft III\\Video\\resheight\"��\r\n��������ע����ֵ."), MB_ICONEXCLAMATION);
						SendMessage(WM_CLOSE);
					  }
					}
				}

		}
	}
	RegCloseKey(hKey);
	//����Ļħ��III�ֱ�������ʾ
	temp.Format(_T("%d��%d"), m_WarX, m_WarY);
	m_cWCSR.SetWindowTextW(temp);
}

void CWarcraftIIIResolutionChangerDlg::OnEnChangeX()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int i;
	CString temp;
	m_cX.GetWindowTextW(temp);
	i = _wtoi(temp);
	temp.Format(_T("%d��%d"), i, (int)(i / 4.0 * 3) );
	m_c43.SetWindowTextW(temp);
	temp.Format(_T("%d��%d"), i, (int)(i / 16.0 * 9) );
	m_c169.SetWindowTextW(temp);
	temp.Format(_T("%d��%d"), i, (int)(i / 16.0 * 10) );
	m_c1610.SetWindowTextW(temp);}

void CWarcraftIIIResolutionChangerDlg::OnEnChangeY()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int i;
	CString temp;
	m_cY.GetWindowTextW(temp);
	i = _wtoi(temp);
	temp.Format(_T("%d��%d"), (int)(i * 4.0 / 3), i);
	m_c43.SetWindowTextW(temp);
	temp.Format(_T("%d��%d"), (int)(i * 16.0 / 9), i);
	m_c169.SetWindowTextW(temp);
	temp.Format(_T("%d��%d"), (int)(i * 16.0 / 10), i);
	m_c1610.SetWindowTextW(temp);
}
