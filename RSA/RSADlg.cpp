
// RSADlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RSA.h"
#include "RSADlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRSADlg �Ի���



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


// CRSADlg ��Ϣ�������

BOOL CRSADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//ShowWindow(SW_MAXIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	key_len.AddString(_T("RSA-512(not safe)"));   
	key_len.AddString(_T("RSA-768"));   
    key_len.AddString(_T("RSA-1024"));   
    key_len.AddString(_T("RSA-2048"));
	key_len.SetCurSel(0);   
	SetDlgItemText(IDC_COMBO_KEY, _T("RSA-512(not safe)"));
	bit = 256;

	str_E = "6a27";

	UpdateData(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRSADlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRSADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRSADlg::OnBnClickedButtonEncode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	string str = CT2A(str_Origin.GetString());
	str_Encode = CA2T(cy.encode(str).c_str());
	UpdateData(FALSE);
}


void CRSADlg::OnBnClickedButtonDecode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	string str = CT2A(str_Encode.GetString());
	str_Decode = CA2T(cy.decode(str).c_str());
	UpdateData(FALSE);
}


void CRSADlg::OnBnClickedButtonGen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strKey;   
    int nSel;   
  
    // ��ȡ��Ͽ�ؼ����б����ѡ���������   
    nSel = key_len.GetCurSel();   
    // ����ѡ����������ȡ�����ַ���   
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
