
// RSADlg.h : ͷ�ļ�
//
#include "Crypt.h"

#pragma once


// CRSADlg �Ի���
class CRSADlg : public CDialogEx
{
// ����
public:
	CRSADlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_RSA_DIALOG };

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
