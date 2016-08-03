
// SimulationSoftwareDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
//#include "TCP_Server.h"
#include "tcp_socket.h"
#include "common.h"

// class CommandResult
class CommandResult {
public:
	CommandResult();
	virtual ~CommandResult();

	bool IsOk() const;
	int GetStatus() const;
	int GetDataLength() const;
	const void *GetData() const;
	int GetData(void *buffer, int size);
	void *GetDataBuffer(int length);
	void SetStatus(int code);

private:
	enum { STATIC_BUFFER_SIZE = 128 };

	int   status_;
	char  staticBuffer_[STATIC_BUFFER_SIZE];
	char  *dataBuffer_;
	int   dataLength_;
};


// CSimulationSoftwareDlg 对话框
class CSimulationSoftwareDlg : public CDialogEx
{
// 构造
public:
	CSimulationSoftwareDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SIMULATIONSOFTWARE_DIALOG };
	char szText[256];
	void InitCommandParameter();
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

private:
	bool SendCommand(int id);
	bool SendCommand(int id, const void *data, int dataLength);
	bool SendCommand(int id, int count, const void *data, int dataLength);
	bool SendCommand(int id, const void *data, int dataLength, CommandResult *result);
	bool SendCommand(int id, int count, const void *data, int dataLength, CommandResult *result);
	bool SendCommandNoResult(int id, int count, const void *data, int dataLength);
	bool ReadResult(CommandResult *result);
};

