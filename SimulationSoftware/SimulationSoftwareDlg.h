
// SimulationSoftwareDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "tcp_socket.h"
#include "common.h"
#include "CommandResult.h"
#include<iostream>
#include <thread>

// CSimulationSoftwareDlg �Ի���
class CSimulationSoftwareDlg : public CDialogEx
{
// ����
public:
	CSimulationSoftwareDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CSimulationSoftwareDlg()
	{
		stop();
	}
// �Ի�������
	enum { IDD = IDD_SIMULATIONSOFTWARE_DIALOG };
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
	bool m_processing{ false }; //�߳��˳���ʶ
	std::thread m_thrProcess;//�߳̾��

public:
	void process();
	//����
	virtual bool start() {
		if (m_processing)
			return false;
		m_processing = true;
		m_thrProcess = std::thread([this](){this->process(); });
		return true;
	}
	//ֹͣ
	virtual void stop() {
		m_processing = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		if (m_thrProcess.joinable())
			m_thrProcess.join();  //�ɱ� joinable �� std::thread �����������������֮ǰ�����߳� join ���߽�������Ϊ detached.
	
	}
public:
	afx_msg void OnBnClickedPalcePaper();
	CButton m_placePaper;
	BOOL m_isPalcePaper;
};

