
// SimulationSoftwareDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
//#include "TCP_Server.h"
#include "tcp_socket.h"
#include "common.h"

// CSimulationSoftwareDlg �Ի���
class CSimulationSoftwareDlg : public CDialogEx
{
// ����
public:
	CSimulationSoftwareDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SIMULATIONSOFTWARE_DIALOG };
	char szText[256];
	void InitCommandParameter();
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
private:
	afx_msg void OnBnClickedOk();
	CButton m_stateBtn;
	BOOL m_checkState;
//	TCP_Server *serverSocket;
	TcpSocket *serverSocket_;
	TcpSocket recvSocker_;
	afx_msg void OnBnClickedStatebutton();
private:
	PacketHeader hd;
	DeviceInfo  deviceInfo;
	Response_ cmd;
	PacketHeader returnTime;
	CISTable cisTable;
	updateHeader updateCmd;
	PacketHeader upgradeDate;
};

