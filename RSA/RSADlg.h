
// RSADlg.h : 头文件
//
#include "Crypt.h"

#pragma once


// CRSADlg 对话框
class CRSADlg : public CDialogEx
{
// 构造
public:
	CRSADlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_RSA_DIALOG };

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
	CString str_Origin;
	afx_msg void OnBnClickedButtonEncode();
	CString str_Encode;
	CString str_Decode;
	Crypt cy;

	afx_msg void OnBnClickedButtonDecode();
	CString str_P;
	CString str_E;
	CString str_Q;
	afx_msg void OnBnClickedButtonGen();

	CComboBox key_len;
	afx_msg void OnCbnSelchangeComboKey();

	int bit;
};
