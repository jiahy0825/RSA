
// RSADlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RSA.h"
#include "RSADlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRSADlg 对话框



CRSADlg::CRSADlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRSADlg::IDD, pParent)
	, str_Origin(_T(""))
	, str_Encode(_T(""))
	, str_Decode(_T(""))
	, str_P(_T(""))
	, str_E(_T(""))
	, str_Q(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRSADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ORIGIN, str_Origin);
	DDX_Text(pDX, IDC_EDIT_ENCODE, str_Encode);
	DDX_Text(pDX, IDC_EDIT_DECODE, str_Decode);
	DDX_Text(pDX, IDC_EDIT_P, str_P);
	DDX_Text(pDX, IDC_EDIT_E, str_E);
	DDX_Text(pDX, IDC_EDIT_Q, str_Q);
	DDX_Control(pDX, IDC_COMBO_KEY, key_len);
}

BEGIN_MESSAGE_MAP(CRSADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ENCODE, &CRSADlg::OnBnClickedButtonEncode)
	ON_BN_CLICKED(IDC_BUTTON_DECODE, &CRSADlg::OnBnClickedButtonDecode)
	ON_BN_CLICKED(IDC_BUTTON_GEN, &CRSADlg::OnBnClickedButtonGen)
	ON_CBN_SELCHANGE(IDC_COMBO_KEY, &CRSADlg::OnCbnSelchangeComboKey)
END_MESSAGE_MAP()


// CRSADlg 消息处理程序

BOOL CRSADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MAXIMIZE);

	// TODO: 在此添加额外的初始化代码
	
	key_len.AddString(_T("RSA-512(not safe)"));   
	key_len.AddString(_T("RSA-768"));   
    key_len.AddString(_T("RSA-1024"));   
    key_len.AddString(_T("RSA-2048"));
	key_len.SetCurSel(0);   
	SetDlgItemText(IDC_COMBO_KEY, _T("RSA-512(not safe)"));
	bit = 256;

	str_E = "6a27";

	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRSADlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRSADlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRSADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRSADlg::OnBnClickedButtonEncode()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string str = CT2A(str_Origin.GetString());
	str_Encode = CA2T(cy.encode(str).c_str());
	UpdateData(FALSE);
}


void CRSADlg::OnBnClickedButtonDecode()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	string str = CT2A(str_Encode.GetString());
	str_Decode = CA2T(cy.decode(str).c_str());
	UpdateData(FALSE);
}


void CRSADlg::OnBnClickedButtonGen()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	cy.generateKey(bit);

	string eStr = CT2A(str_E.GetString());
	LargeInt e;
	e.transform(eStr);
	cy.generateED(e);
	str_P = CA2T(cy.p.toString().c_str());
	str_Q = CA2T(cy.q.toString().c_str());
	str_E = CA2T(cy.e.toString().c_str());

	UpdateData(FALSE);
}


void CRSADlg::OnCbnSelchangeComboKey()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strKey;   
    int nSel;   
  
    // 获取组合框控件的列表框中选中项的索引   
    nSel = key_len.GetCurSel();   
    // 根据选中项索引获取该项字符串   
    key_len.GetLBText(nSel, strKey);   
	if(strKey == "RSA-512(not safe)"){
		bit = 256;
	}else if(strKey == "RSA-768"){
		bit = 384;
	}else if(strKey == "RSA-1024"){
		bit = 512;
	}else{
		bit = 1024;
	}
}
