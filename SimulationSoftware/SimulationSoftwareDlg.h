
// SimulationSoftwareDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "tcp_socket.h"
#include "common.h"
#include "CommandResult.h"
#include<iostream>
#include <thread>

// CSimulationSoftwareDlg 对话框
class CSimulationSoftwareDlg : public CDialogEx
{
// 构造
public:
	CSimulationSoftwareDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CSimulationSoftwareDlg()
	{
		stop();
	}
// 对话框数据
	enum { IDD = IDD_SIMULATIONSOFTWARE_DIALOG };
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
	afx_msg void OnBnClickedStatebutton();
	CButton m_stateBtn;
	BOOL m_checkState;
	TcpSocket *serverSocket_;
	TcpSocket recvSocker_;
	
	//SOCKET s;
private:
	
	DeviceInfo  deviceInfo;
	CISCorrectionTable  cisCorrectionTable_;
	upgradeLength length_;
private:
	bool SendCommand(int id);
	bool SendCommand(int id, const void *data, int dataLength);
	bool SendCommand(int id, int count, const void *data, int dataLength);
	bool SendCommand(int id, const void *data, int dataLength, CommandResult *result);
	bool SendCommand(int id, int count, const void *data, int dataLength, CommandResult *result);
	bool SendCommandNoResult(int id, int count, const void *data, int dataLength);
	bool ReadResult(CommandResult *result);
public:
	char szText[256];
	void InitCommandParameter();
	enum{ IR_COUNT = 6 };
	int emissionValues[IR_COUNT];
	int emissionValues_[IR_COUNT];
	int collectionValues[IR_COUNT];
	int collectionValues_[IR_COUNT];

protected:
	bool m_processing{ false }; //线程退出标识
	std::thread m_thrProcess;//线程句柄

public:
	void process();
	//启动
	virtual bool start() {
		if (m_processing)
			return false;
		m_processing = true;
		m_thrProcess = std::thread([this](){this->process(); });
		return true;
	}
	//停止
	virtual void stop() {
		m_processing = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		if (m_thrProcess.joinable())
			m_thrProcess.join();  //可被 joinable 的 std::thread 对象必须在他们销毁之前被主线程 join 或者将其设置为 detached.
	
	}
public:
	afx_msg void OnBnClickedPalcePaper();
	CButton m_placePaper;
	BOOL m_isPalcePaper;
};

