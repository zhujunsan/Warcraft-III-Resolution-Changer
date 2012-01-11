// Warcraft III Resolution ChangerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Warcraft III Resolution Changer.h"
#include "Warcraft III Resolution ChangerDlg.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CWarcraftIIIResolutionChangerDlg 对话框




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


// CWarcraftIIIResolutionChangerDlg 消息处理程序

BOOL CWarcraftIIIResolutionChangerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//好的, 我开始初始化了
	CString temp;
	unsigned int m_WarX = 0;
	unsigned int m_WarY = 0;
	//获取屏幕分辨率
	int m_ScreenX=GetSystemMetrics(SM_CXSCREEN);
	int m_ScreenY=GetSystemMetrics(SM_CYSCREEN);
	//在屏幕分辨率文本框上显示
	temp.Format(_T("%d×%d"), m_ScreenX, m_ScreenY);
	m_cScreenResolution.SetWindowTextW(temp);
	//设定X, Y文本框为当前屏幕分辨率
	temp.Format(_T("%d"), m_ScreenY);
	m_cY.SetWindowTextW(temp);
	temp.Format(_T("%d"), m_ScreenX);
	m_cX.SetWindowTextW(temp);
	//读取注册表中魔兽III的分辨率
	HKEY hKey;
	if(RegOpenKeyEx(HKEY_CURRENT_USER, _T(""), NULL, KEY_READ, &hKey) != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("无法访问注册表!\r\n请确定本程序有足够的权限, Vista 或 7 用户需要以管理员运行."), MB_ICONEXCLAMATION);
		SendMessage(WM_CLOSE);
	}
	else
	{
		if(RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III\\Video"), NULL, KEY_READ, &hKey) != ERROR_SUCCESS)
		{
			AfxMessageBox(_T("未发现魔兽争霸III的注册表项!\r\n请检查是否安装过此程序或在安装后至少运行一次."), MB_ICONEXCLAMATION);
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
						AfxMessageBox(_T("无法读取该注册表\"HKEY_CURRENT_USER\\Software\\Blizzard Entertainment\\Warcraft III\\Video\\reswidth\"项\r\n请检查您的注册表该值."), MB_ICONEXCLAMATION);
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
						AfxMessageBox(_T("无法读取该注册表\"HKEY_CURRENT_USER\\Software\\Blizzard Entertainment\\Warcraft III\\Video\\resheight\"项\r\n请检查您的注册表该值."), MB_ICONEXCLAMATION);
						SendMessage(WM_CLOSE);
					  }
					}
				}

		}
	}
	RegCloseKey(hKey);
	//在屏幕魔兽III分辨率上显示
	temp.Format(_T("%d×%d"), m_WarX, m_WarY);
	m_cWCSR.SetWindowTextW(temp);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWarcraftIIIResolutionChangerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CWarcraftIIIResolutionChangerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWarcraftIIIResolutionChangerDlg::OnBnClickedAbout()
{
	// TODO: 在此添加控件通知处理程序代码
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CWarcraftIIIResolutionChangerDlg::OnBnClickedExit()
{
	// TODO: 在此添加控件通知处理程序代码
	SendMessage(WM_CLOSE);
}

void CWarcraftIIIResolutionChangerDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString temp;
	DWORD m_WarX = 0, m_WarY = 0;
	HKEY hKey;
	//转换文本框内容到数字
	m_cX.GetWindowTextW(temp);
	m_WarX = _wtoi(temp);
	m_cY.GetWindowTextW(temp);
	m_WarY = _wtoi(temp);
	//写入注册表
	if(RegOpenKeyEx(HKEY_CURRENT_USER, _T(""), NULL, KEY_READ, &hKey) != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("无法访问注册表!\r\n请确定本程序有足够的权限, Vista 或 7 用户需要以管理员运行."), MB_ICONEXCLAMATION);
		SendMessage(WM_CLOSE);
	}
	else
	{
		if(RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III\\Video"), NULL, KEY_WRITE|KEY_READ, &hKey) != ERROR_SUCCESS)
		{
			AfxMessageBox(_T("未发现魔兽争霸III的注册表项!\r\n请检查是否安装过此程序或在安装后至少运行一次."), MB_ICONEXCLAMATION);
			SendMessage(WM_CLOSE);
		}
		else
		{
		  if (RegSetValueEx(hKey, _T("reswidth"), NULL, REG_DWORD, (LPBYTE)&m_WarX, 4) != ERROR_SUCCESS)
			AfxMessageBox(_T("无法写入该注册表\"HKEY_CURRENT_USER\\Software\\Blizzard Entertainment\\Warcraft III\\Video\\reswidth\"项\r\n请检查您的注册表该值."), MB_ICONEXCLAMATION);
		  if (RegSetValueEx(hKey, _T("resheight"), NULL, REG_DWORD, (LPBYTE)&m_WarY, 4) != ERROR_SUCCESS)
			AfxMessageBox(_T("无法写入该注册表\"HKEY_CURRENT_USER\\Software\\Blizzard Entertainment\\Warcraft III\\Video\\resheight\"项\r\n请检查您的注册表该值."), MB_ICONEXCLAMATION);
		}
	}
	RegCloseKey(hKey);
	
	//写完了读一遍:读取注册表中魔兽III的分辨率
	if(RegOpenKeyEx(HKEY_CURRENT_USER, _T(""), NULL, KEY_READ, &hKey) != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("无法访问注册表!\r\n请确定本程序有足够的权限, Vista 或 7 用户需要以管理员运行."), MB_ICONEXCLAMATION);
		SendMessage(WM_CLOSE);
	}
	else
	{
		if(RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III\\Video"), NULL, KEY_READ, &hKey) != ERROR_SUCCESS)
		{
			AfxMessageBox(_T("未发现魔兽争霸III的注册表项!\r\n请检查是否安装过此程序或在安装后至少运行一次."), MB_ICONEXCLAMATION);
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
						AfxMessageBox(_T("无法读取该注册表\"HKEY_CURRENT_USER\\Software\\Blizzard Entertainment\\Warcraft III\\Video\\reswidth\"项\r\n请检查您的注册表该值."), MB_ICONEXCLAMATION);
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
						AfxMessageBox(_T("无法读取该注册表\"HKEY_CURRENT_USER\\Software\\Blizzard Entertainment\\Warcraft III\\Video\\resheight\"项\r\n请检查您的注册表该值."), MB_ICONEXCLAMATION);
						SendMessage(WM_CLOSE);
					  }
					}
				}

		}
	}
	RegCloseKey(hKey);
	//在屏幕魔兽III分辨率上显示
	temp.Format(_T("%d×%d"), m_WarX, m_WarY);
	m_cWCSR.SetWindowTextW(temp);
}

void CWarcraftIIIResolutionChangerDlg::OnEnChangeX()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	int i;
	CString temp;
	m_cX.GetWindowTextW(temp);
	i = _wtoi(temp);
	temp.Format(_T("%d×%d"), i, (int)(i / 4.0 * 3) );
	m_c43.SetWindowTextW(temp);
	temp.Format(_T("%d×%d"), i, (int)(i / 16.0 * 9) );
	m_c169.SetWindowTextW(temp);
	temp.Format(_T("%d×%d"), i, (int)(i / 16.0 * 10) );
	m_c1610.SetWindowTextW(temp);}

void CWarcraftIIIResolutionChangerDlg::OnEnChangeY()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	int i;
	CString temp;
	m_cY.GetWindowTextW(temp);
	i = _wtoi(temp);
	temp.Format(_T("%d×%d"), (int)(i * 4.0 / 3), i);
	m_c43.SetWindowTextW(temp);
	temp.Format(_T("%d×%d"), (int)(i * 16.0 / 9), i);
	m_c169.SetWindowTextW(temp);
	temp.Format(_T("%d×%d"), (int)(i * 16.0 / 10), i);
	m_c1610.SetWindowTextW(temp);
}
