
// SimulationSoftwareDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SimulationSoftware.h"
#include "SimulationSoftwareDlg.h"
#include "afxdialogex.h"
//#include "TCP_Server.h"
#include <iostream>

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


// CSimulationSoftwareDlg 对话框


CSimulationSoftwareDlg::CSimulationSoftwareDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSimulationSoftwareDlg::IDD, pParent)
	, m_checkState(false)
	, m_isPalcePaper(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    InitCommandParameter();
	serverSocket_ = new TcpSocket;
}

void CSimulationSoftwareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATEBUTTON, m_stateBtn);
	DDX_Check(pDX, IDC_STATEBUTTON, m_checkState);
	DDX_Control(pDX, IDC_CHECK_PALCEPAPER, m_placePaper);
	DDX_Check(pDX, IDC_CHECK_PALCEPAPER, m_isPalcePaper);
	DDX_Control(pDX, IDC_DISPLAY_LIST, m_displayListBox);
}

BEGIN_MESSAGE_MAP(CSimulationSoftwareDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSimulationSoftwareDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_STATEBUTTON, &CSimulationSoftwareDlg::OnBnClickedStatebutton)
	ON_BN_CLICKED(IDC_CHECK_PALCEPAPER, &CSimulationSoftwareDlg::OnBnClickedPalcePaper)
	ON_BN_CLICKED(IDC_FILE_BUTTON, &CSimulationSoftwareDlg::OnBnClickedFileChooseButton)
END_MESSAGE_MAP()


// CSimulationSoftwareDlg 消息处理程序

BOOL CSimulationSoftwareDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSimulationSoftwareDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSimulationSoftwareDlg::OnPaint()
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
HCURSOR CSimulationSoftwareDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSimulationSoftwareDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	
	CDialogEx::OnOK();
}

#include <stdio.h>
void CSimulationSoftwareDlg::OnBnClickedStatebutton()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_checkState)
	{
		m_stateBtn.SetWindowText(L"点钞机打开");
		//m_processing = true;
		
		if (serverSocket_->Listen(L"172.16.100.237", 1234))
		{
			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"点钞机打开，监听生产管理软件的请求...");
			m_displayListBox.AddString(L"点钞机打开，监听生产管理软件的请求...");
		}
		SOCKET s = serverSocket_->Accept(100);
		recvSocker_.Attach(s);
		//recvSocker_.SetRecvBufferSize(1024);

		if (s==INVALID_SOCKET)
		{
			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"点钞机连接到生产管理软件失败...");
			m_displayListBox.AddString(L"点钞机连接到生产管理软件失败...");
		}
		else
		{
			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"点钞机已连接到生产管理软件...");
			m_displayListBox.AddString(L"点钞机已连接到生产管理软件...");
			start();
		//		if (result.GetStatus()==0x8181)
		//		{
		//			SendCommandNoResult(COMMAND_ECHO, 0, 0, 0);
		//		}
		//	//	char szText[256];
		//	//	int nRecv = ::recv(s, szText, strlen(szText), 0);  //判断链接成功的socket收到的回包
		//	//	if (nRecv == SOCKET_ERROR)
		//	//	{
		//	//		TRACE("接收错误...");
		//	//		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"接收错误退出...");
		//	//		break;
		//	//	}
		//	//	if (nRecv > 0)						// （2）可读
		//	//	{
		//	//		szText[nRecv] = '\0';
		//	//		TRACE("接收到数据：%s \n", szText);
		//	//		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"接收到数据,等待发送数据...");
		//	//	//	break;
		//	//	}
		//	//	if (nRecv==0)				      // （3）连接关闭、重启或者中断
		//	//	{
		//	//		::closesocket(s);
		//	//		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"生产管理软件主动断开与服务端的连接...");
		//	//		//m_checkState = false;
		//	//		m_stateBtn.SetWindowText(L"关闭再次开机");
		//	//		TRACE("链接关闭....");
		//	//		//return true;
		//	//		break;
		//	//	}
		//	//	
		//	//	//应该先检验一下收到的包是否正确，然后再send;没有做校验
		//	//	int len_send = send(s, (char*)&cmd, sizeof(cmd), 0);
		//	//	if (len_send==SOCKET_ERROR)
		//	//	{
		//	//		OutputDebugString(L"发送失败....");  //MFC 用trace
		//	//	}
		//	//	
		//	//	int len_send2 = send(s, (char*)&returnTime, sizeof(returnTime), 0);
		//	//	int len_send3 = send(s, (char*)&cisTable, sizeof(cisTable), 0);
		//	//	int len_send4 = send(s, (char*)&updateCmd, sizeof(updateCmd), 0);
		//	//	int len_send5 = send(s, (char*)&upgradeDate, sizeof(upgradeDate), 0);
		//	//	if (len_send3 == SOCKET_ERROR)
		//	//	{
		//	//		OutputDebugString(L"发送失败....");  //MFC 用trace
		//	//	}			
		//   }
		}
	}
	else  //服务端主动关闭  //貌似正常情况下会卡住
	{
		m_stateBtn.SetWindowText(L"点钞机关闭");
		serverSocket_->Close();
		//recvSocker_.Close();
	//	delete serverSocket_;

		//stop(); //卡住
		//m_processing = false;  //不关线程，再次打开点钞机时，还可以正常接收数据，但是这样的话不是真正的关闭,乃在发echo，否则，关闭后再次打开没有开启线程;如果真正关闭，其实socket已经变了，C/S都必须重新启动
		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"点钞机关闭，断开与生产管理软件的连接...");	
		m_displayListBox.AddString(L"点钞机关闭，断开与生产管理软件的连接...");
	}
}

void CSimulationSoftwareDlg::process()
{
	while (m_processing)
	{
		CommandResult result;
		if (!ReadResult(&result))  //没有结果主动和被动关闭都有可能
		{
			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"接收到数据失败...有可能客户端主动关闭连接...");
			m_displayListBox.AddString(L"接收到数据失败...有可能客户端主动关闭连接....");

			serverSocket_->Close();
			//delete serverSocket_;
			//m_stateBtn.SetState(false);
			//m_checkState = false;
			m_stateBtn.SetWindowText(L"关闭-点钞机");
			break;
		}
		else
		{
	//		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"ReadResult为false，当接收到命令时，回复命令...");
	//		m_displayListBox.AddString(L"ReadResult为false，当接收到命令时，才回复命令...");
		}
		if (result.GetStatus() == COMMAND_SET_DEVICE_INFO)    //0x0002
		{
			CriticalSection::ScopedLocker locker(criSec_);
			if (!SendCommandNoResult(COMMAND_SET_DEVICE_INFO, 0, &deviceInfo, sizeof(deviceInfo)))
			{
				serverSocket_->Close();
			}
			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"发送设备信息数据...");
			m_displayListBox.AddString(L"回复 COMMAND_SET_DEVICE_INFO 命令...");
		}
		if (result.GetStatus() == COMMAND_SET_TIME)          //0x0018
		{
			CriticalSection::ScopedLocker locker(criSec_);
			SendCommandNoResult(COMMAND_SET_TIME, 0, 0, 0);
			m_displayListBox.AddString(L"回复 COMMAND_SET_TIME 命令...");
		}
		if (result.GetStatus() == COMMAND_GET_CIS_CORRECTION_TABLE) //0x000d
		{	
			CriticalSection::ScopedLocker locker(criSec_);
			SendCommandNoResult(COMMAND_GET_CIS_CORRECTION_TABLE, 0, &cisCorrectionTable_.data, sizeof(cisCorrectionTable_));
			m_displayListBox.AddString(L"回复 COMMAND_GET_CIS_CORRECTION_TABLE 命令...");
		}
		if (result.GetStatus() == COMMAND_UPGRADE)  //0x0004
		{	
			CriticalSection::ScopedLocker locker(criSec_);
			//更新ini文件的版本，重启时下位机才能更新
			UpgradeRequest request;
			ZeroMemory(&request, sizeof(request));
			//result.GetData(&request, sizeof(request));
			CopyMemory(&request,result.GetData(),sizeof(UpgradeRequest));
			//strncpy( (char*)&request, (char*)result.GetDataBuffer(sizeof(request)), sizeof(request));
			TCHAR temp[128];
		    //strcpy_s(temp, request.newVersion);
			MultiByteToWideChar(CP_ACP, 0, request.newVersion, -1, temp, 100);
			WritePrivateProfileString(L"DeviceInfo", L"firmwareVersion", temp/*(LPCWSTR)request.newVersion*//*L"1.0.15"*/, GetExPath() + L"DEVICEINFO.ini");
			//int length = result.dataLength_; //private
			SendCommandNoResult(COMMAND_UPGRADE, 0, &length_, sizeof(length_));
			m_displayListBox.AddString(L"回复 COMMAND_UPGRADE 命令，接收到newVersion保存ini,下次更新...");
		}
		if (result.GetStatus() == COMMAND_UPGRADE_DATA)  //0x0005
		{	
			CriticalSection::ScopedLocker locker(criSec_);
			//可以接收升级数据			
			if (result.GetDataLength()<sizeof(length_))   //最后一次失败
			{
				TRACE("receive failed...");
			}
			CFile file(_T("f:\\firmware.dat"),  CFile::modeWrite | CFile::typeBinary);  //CFile::modeCreate
			file.SeekToEnd();
			file.Write(result.GetData(), result.GetDataLength());
			file.Close();
			SendCommandNoResult(COMMAND_UPGRADE_DATA, 0, 0, 0);
			m_displayListBox.AddString(L"回复 COMMAND_UPGRADE_DATA 命令，保存更新的数据包dat...");
		}
		if (result.GetStatus() == COMMAND_UPDATE_DEBUG_STATE)  //服务端调试状态怎么计算的？  //0x0003
		{	
			CriticalSection::ScopedLocker locker(criSec_);
			//接收调试状态
			int states[16] = { 0 };
			result.GetData(states, sizeof(states));
			CString strTemp;
			strTemp.Format(L"%d", states[0]);
			WritePrivateProfileString(L"DeviceInfo", L"debugState[1]",/*L"23"*/strTemp, GetExPath() + L"DEVICEINFO.ini");
			
			SendCommandNoResult(COMMAND_UPDATE_DEBUG_STATE, 0, 0, 0);
			m_displayListBox.AddString(L"回复 COMMAND_UPDATE_DEBUG_STATE 命令，保存调试状态ini并更新...");
		}
		if (result.GetStatus() == COMMAND_RESTART)   //0x0006
		{		
			CriticalSection::ScopedLocker locker(criSec_);
			SendCommandNoResult(COMMAND_RESTART, 0, 0, 0);
			m_displayListBox.AddString(L"回复 COMMAND_RESTART 命令，尝试重启点钞机...");
			serverSocket_->Close();
			//delete serverSocket_;	
		    //m_checkState = false;
			m_processing = false;
			m_stateBtn.SetWindowText(L"重启点钞机");
				
			if (!serverSocket_->IsOpened())  //不加需手动重启
			{
				m_displayListBox.AddString(L"正在重启点钞机...重发三条指令...");
				if (serverSocket_->Listen(L"172.16.100.237", 1234))
				{
					GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"点钞机打开，监听生产管理软件的请求...");
					m_displayListBox.AddString(L"点钞机重启成功，进入IR界面...监听生产管理软件的请求...");
				}
				SOCKET s = serverSocket_->Accept(10);
				recvSocker_.Attach(s);
				m_processing = true;
				m_stateBtn.SetWindowText(L"点钞机打开");
				InitCommandParameter();
			}

			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"请放纸校验...");
			m_displayListBox.AddString(L"请放纸校验....！！！！");
		}
		if (result.GetStatus() == COMMAND_ECHO)  //0x8181
		{	
			CriticalSection::ScopedLocker locker(criSec_);
			SendCommandNoResult(COMMAND_ECHO, 0, 0, 0);
			m_displayListBox.AddString(L"回复 COMMAND_ECHO 命令...");
		}
		if (result.GetStatus() == COMMAND_SET_IR_PARAMETERS)   //0x0008
		{
			CriticalSection::ScopedLocker locker(criSec_);
			//获取发射管的值
			emissionValues[IR_COUNT] = { 0 };
			emissionValues_[IR_COUNT] = { 0 };
			if (m_isPalcePaper)   //有纸
			{
				result.GetData(emissionValues, sizeof(emissionValues));
				SendCommandNoResult(COMMAND_SET_IR_PARAMETERS, 0, NULL, 0);
				m_displayListBox.AddString(L"回复 COMMAND_SET_IR_PARAMETERS 命令，保存发射管值，有纸状态...");
			}
			else
			{
				result.GetData(emissionValues_, sizeof(emissionValues_));
				SendCommandNoResult(COMMAND_SET_IR_PARAMETERS, 0, NULL, 0);
				m_displayListBox.AddString(L"回复 COMMAND_SET_IR_PARAMETERS 命令，保存发射管值，无纸状态...");
			}
		}
		if (result.GetStatus() == COMMAND_GET_IR_VALUES)  //0x0007
		{
			CriticalSection::ScopedLocker locker(criSec_);
			//根据发射管的值，线性计算接收管的值
			if (m_isPalcePaper)
			{
				for (int i = 0; i < IR_COUNT; i++)
				{
					collectionValues[i] = (emissionValues[i] - 1300) *100/ 2200 + 650;  //除取整
				}
				SendCommandNoResult(COMMAND_GET_IR_VALUES, 0, collectionValues, IR_COUNT * sizeof(int));
				m_displayListBox.AddString(L"回复 COMMAND_SET_IR_PARAMETERS 命令，有纸状态，发送发射管值...");
			}
			else
			{
				for (int i = 0; i < IR_COUNT; i++)
				{
					collectionValues_[i] = (emissionValues_[i] - 1300)*400 /2200  + 3600;  //除取整
				}
				SendCommandNoResult(COMMAND_GET_IR_VALUES, 0, collectionValues_, IR_COUNT * sizeof(int));
				m_displayListBox.AddString(L"回复 COMMAND_SET_IR_PARAMETERS 命令，无纸状态，发送发射管值...");
			}
		}
		if (result.GetStatus() == COMMAND_START_MOTOR)  //0x0015
		{
			CriticalSection::ScopedLocker locker(criSec_);
			//电机转动指令时，有纸状态变为无纸状态
			m_isPalcePaper = false;
			m_placePaper.SetWindowText(L"无纸状态");
			SendCommandNoResult(COMMAND_START_MOTOR, 0, 0, 0);
			m_displayListBox.AddString(L"回复 COMMAND_START_MOTOR 命令，启动电机，确保无纸状态...");
		}
		if (result.GetStatus() == COMMAND_UPDATE_IR_PARAMETERS)  //0x0009
		{
			CriticalSection::ScopedLocker locker(criSec_);
			//保存更新后的发射参数

			SendCommandNoResult(COMMAND_UPDATE_IR_PARAMETERS, 0, NULL, 0);
			m_displayListBox.AddString(L"回复 COMMAND_UPDATE_IR_PARAMETERS 命令...");
		}
	
		//接收点钞机的指令，进入数据发送模式，保存走抄数据上传的socket地址
		if (result.GetStatus() == COMMAND_START_RUN_CASH_DETECT)  //0x8004
		{
			memset(&datalevel,0,sizeof(DataLevel));
			CopyMemory(&datalevel,result.GetData(),sizeof(DataLevel));
			//sockaddr_in dataClient_Addr;
			//dataClient_Addr = datalevel.hostAddr;
			const char* ip = inet_ntoa(datalevel.hostAddr.sin_addr);
			CString deviceIP;
			//deviceIP.Format(L"%s",ip); //A2T(pChar);
			USES_CONVERSION;
			deviceIP = A2T(ip);
			int devicePort = ntohs(datalevel.hostAddr.sin_port);
			while (true)
			{
				if (!connection_.Connect(deviceIP, devicePort))
				{
					TRACE("----与服务端数据通道连接失败........");
				}
				else
				{
					TRACE("----与服务端数据通道连接成功........");
					break;
				}
			}			
			SendCommandNoResult(COMMAND_START_RUN_CASH_DETECT, 0, 0, 0);
			m_displayListBox.AddString(L"回复 COMMAND_START_RUN_CASH_DETECT 命令...");
			//走钞的流程是：3走钞开始信号--->0主控数据(ADC)--->2图像数据(CIS)---->3钞票信息(info)---->4提钞信号么
			if (SendDataNoResult(ID_BEGIN_BUNDLE, 0, 0, 0))
			{
				m_displayListBox.AddString(L"发送....3走钞开始信号...");
			}
		    //准备好发送数据ADC,CIS...
			char* data = new char[44 + 2 * 100 * 22*2];
			short* dataCount = new short[22];
			short* dataCode = new short[100];
			short* dataVluae = new short[100];
			//memset(dataCount, 100, 22);  //对多字节赋值问题		
			for (int i = 0; i < 22;i++)
			{
				dataCount[i] = 100;
			}
			for (size_t i = 0; i < 100; i++)
			{
				dataCode[i] = 1;
				dataVluae[i] = 2;
			}
			memcpy(data, dataCount, sizeof(short)* 22);
			for (int i = 0; i < 100;i=i+2)
			{
			//	memcpy(data + sizeof(short)* 100 * i + sizeof(short)* 22, dataCode, sizeof(short)* 100);   //有问题？
			//	memcpy(data + sizeof(short)* 100 * i + sizeof(short)* 100 + sizeof(short)* 22, dataVluae, sizeof(short)* 100);
			}
			CFile dataflie(_T("C:\\Users\\ranji\\Desktop\\data.dat"), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
			dataflie.Write(data + 44, 44 + 2 * 2 * 100 * 22);
			dataflie.Close();

			if (SendDataNoResult(ID_ADC_DATA, 0,data,44+2*2*100*22))  //发送数据格式 &deviceInfo, sizeof(deviceInfo)
			{
				m_displayListBox.AddString(L"0主控数据(ADC)...");
			}
			delete[] dataCount;
			delete[] dataCode;
			delete[] dataVluae;
			delete[] data;

			char* cisData = new char[20];
			memset(cisData, 1, 20);
			if (SendDataNoResult(ID_CIS_DATA, 0, cisData, 20))
			{
				m_displayListBox.AddString(L"1：图像数据CIS...");
			}
			delete[] cisData;

			struct CashData{
				int count;  //序号
				int denomination;  //面额
				int version;//版本
				int direction; //方向
				int error; //错误代码
				char sn[32];  //冠字号
				int snImageSize; //冠字号的图像 12*32
				unsigned int snImage[12][32];  //0
			}cashData;
			memset(&cashData, 0, sizeof(CashData));
			if (SendDataNoResult(ID_CASH_INFO, 0, &cashData, sizeof(CashData)))
			{
				m_displayListBox.AddString(L"2：钞票信息数据...");
			}
			//if (SendDataNoResult(ID_END_BUNDLE, 0, 0, 0))
			//{
			//	m_displayListBox.AddString(L"4：提钞信号...");
			//}
		}
	}
}

//发送一个指令 Echo
bool CSimulationSoftwareDlg::SendCommand(int id) {
	return SendCommand(id, NULL, 0);
}
//发送带有负载的指令
bool CSimulationSoftwareDlg::SendCommand(int id, const void *data, int dataLength) {
	return SendCommand(id, 0, data, dataLength);
}
//发送有计数，带负载的指令
bool CSimulationSoftwareDlg::SendCommand(int id, int count, const void *data, int dataLength) {
	CommandResult result;
	if (!SendCommand(id, data, dataLength, &result)) {
		return false;
	}
	if (!result.IsOk()) {
	//	SetLastError(ERROR_DEVICE_RESULT_ERROR);
		return false;
	}
	return true;
}
//发送指令，并检验result
bool CSimulationSoftwareDlg::SendCommand(int id, const void *data, int dataLength, CommandResult *result) {
	return SendCommand(id, 0, data, dataLength, result);
}
//发送指令，计数，检验result
bool CSimulationSoftwareDlg::SendCommand(int id, int count, const void *data, int dataLength, CommandResult *result) {
	ASSERT(result != NULL);

	if (!SendCommandNoResult(id, count, data, dataLength)) {
		return false;
	}
	return ReadResult(result);
}
//发送包头和数据
bool CSimulationSoftwareDlg::SendCommandNoResult(int id, int count, const void *data, int dataLength) {
	PacketHeader hd;
	hd.signatures[0] = 'R';
	hd.signatures[1] = 'P';
	hd.id = (unsigned short)0x0000;  //id根本就没有用了
	hd.count = 0;
	hd.length = dataLength;
	if (!recvSocker_.Send(&hd, sizeof(hd))) {
		return false;
	}
	if (dataLength > 0) {
		if (!recvSocker_.Send(data, dataLength)) {
			return false;
		}
	}
	return true;
}

bool CSimulationSoftwareDlg :: SendDataNoResult(int id,int count,const void* data,int datalength)
{
	PacketHeader hd;
	hd.signatures[0] = 'D';
	hd.signatures[1] = 'T';
	hd.id = (unsigned short)id; //数据通道区分类型
	hd.count = count;
	hd.length = datalength;
	if (!connection_.Send(&hd,sizeof(hd)))
	{
		return false;
	}
	if (datalength>0)
	{
		if (!connection_.Send(data,datalength))
		{
			return false;
		}
	}
	return true;
}

bool CSimulationSoftwareDlg::ReadResult(CommandResult *result) {
	ASSERT(result != NULL);

	PacketHeader hd;
	if (!recvSocker_.ReceiveFully(&hd, sizeof(hd))) {
		return false;
	}
	if (hd.signatures[0] != 'R' || hd.signatures[1] != 'Q') {
	//	SetLastError(ERROR_DEVICE_RESULT_ERROR);
		return false;
	}
	result->SetStatus(hd.status);
	if (hd.length > 0) {
		if (!recvSocker_.ReceiveFully(result->GetDataBuffer(hd.length), hd.length)) {
			return false;
		}
	}
	return true;
}


void CSimulationSoftwareDlg::InitCommandParameter()
{
	//发送DeviceInfo信息
	memset(&deviceInfo, 0, sizeof(deviceInfo));

	//CString deviceInfo_sn;
	//GetPrivateProfileString(L"DeviceInfo", L"sn", L"", deviceInfo_sn.GetBuffer(MAX_PATH), MAX_PATH, GetExPath() + L"DEVICEINFO.ini");
	//deviceInfo_sn.ReleaseBuffer();
	//strncpy_s(deviceInfo.sn, (LPSTR)(LPCTSTR)deviceInfo_sn, sizeof(deviceInfo_sn));
	//GetPrivateProfileString(L"DeviceInfo", L"sn", L"", (LPWSTR)deviceInfo.sn, MAX_PATH, GetExPath() + L"DEVICEINFO.ini");  //以TCHAR的方式
	TCHAR device_sn[128];    GetPrivateProfileString(TEXT("DeviceInfo"), TEXT("sn"), NULL, device_sn, _countof(device_sn), GetExPath() + L"DEVICEINFO.ini"); strcpy_s(deviceInfo.sn,CT2A(device_sn));
	TCHAR device_model[128]; GetPrivateProfileString(L"DeviceInfo", L"model", L"", device_model, sizeof(device_model), GetExPath() + L"DEVICEINFO.ini"); strcpy_s(deviceInfo.model,CT2A(device_model));
	TCHAR deviec_firmV[128]; GetPrivateProfileString(L"DeviceInfo", L"firmwareVersion", L"", deviec_firmV, sizeof(deviec_firmV), GetExPath() + L"DEVICEINFO.ini"); strcpy_s(deviceInfo.firmwareVersion, CT2A(deviec_firmV));

	deviceInfo.numberOfCIS = GetPrivateProfileInt(L"DeviceInfo", L"numberOfCIS", 0, GetExPath() + L"DEVICEINFO.ini");
	deviceInfo.numberOfIR =  GetPrivateProfileInt(L"DeviceInfo", L"numberOfIR", 0, GetExPath() + L"DEVICEINFO.ini");
	deviceInfo.numberOfMH =  GetPrivateProfileInt(L"DeviceInfo", L"numberOfMH", 0, GetExPath() + L"DEVICEINFO.ini");
	deviceInfo.reserved =    GetPrivateProfileInt(L"DeviceInfo", L"reserved", 0, GetExPath() + L"DEVICEINFO.ini");

	deviceInfo.cisColorFlags =  GetPrivateProfileInt(L"DeviceInfo", L"cisColorFlags", 0, GetExPath() + L"DEVICEINFO.ini");
	deviceInfo.cisImageWidth =  GetPrivateProfileInt(L"DeviceInfo", L"cisImageWidth", 0, GetExPath() + L"DEVICEINFO.ini");
	deviceInfo.cisImageHeight = GetPrivateProfileInt(L"DeviceInfo", L"cisImageHeight", 0, GetExPath() + L"DEVICEINFO.ini");
	deviceInfo.selfTestState =  GetPrivateProfileInt(L"DeviceInfo", L"selfTestState", 0, GetExPath() + L"DEVICEINFO.ini");
	deviceInfo.debugState[0] = GetPrivateProfileInt(L"DeviceInfo", L"debugState[1]", 0, GetExPath() + L"DEVICEINFO.ini");; //22

	for (int side = 0; side < CIS_COUNT; side++) {
		for (int color = 0; color < COLOR_COUNT; color++) {
			for (int x = 0; x < CIS_IMAGE_WIDTH; x++) {
				for (int level = 0; level < 256; level++) {
					cisCorrectionTable_.data[side][color][x][level] = level;
				}
			}
		}
	}
	length_.length = 2048;
}

void CSimulationSoftwareDlg::OnBnClickedPalcePaper()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_isPalcePaper)
	{
		m_placePaper.SetWindowText(L"放纸校验");
	}
}


void CSimulationSoftwareDlg::OnBnClickedFileChooseButton()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog fileDlg(TRUE);
	if (IDOK==fileDlg.DoModal())
	{
		fileName = fileDlg.GetPathName();
	}
	CFile file(fileName, CFile::typeBinary | CFile::modeRead);
	int length = (int)file.GetLength();  //199680/8/20=1248
	data_ADC = new char[length];
	UINT ret = file.Read(data_ADC, length);

	//for (int i = 0; i < ADC_CHANNEL_COUNT;i++)
	//{
	//	char* temp = data_ADC;
	//	adcChannels_[i].count = length / 8 / 20;
	//	adcChannels_[i].codes=
	//}

	int channelMap[24] = {
		ADC_CHANNEL_BM, ADC_CHANNEL_IR1, ADC_CHANNEL_EIR5,   //0 12 9
		ADC_CHANNEL_RSM, ADC_CHANNEL_IR2, ADC_CHANNEL_EIR6,  //2 13 10
		ADC_CHANNEL_HD, ADC_CHANNEL_IR3, ADC_CHANNEL_UV,     //21 14 18
		ADC_CHANNEL_LSM, ADC_CHANNEL_IR4, ADC_CHANNEL_UVL,   //1 15 19

		ADC_CHANNEL_BM, ADC_CHANNEL_IR6, ADC_CHANNEL_EIR4,   //0  17 8
		ADC_CHANNEL_RM, ADC_CHANNEL_IR5, ADC_CHANNEL_EIR1,   //4  16 5
		ADC_CHANNEL_HD, ADC_CHANNEL_COUNT, ADC_CHANNEL_EIR3, //21  22 7
		ADC_CHANNEL_LM, ADC_CHANNEL_COUNT, ADC_CHANNEL_EIR2  //3   22 6      //0 22 
	};
	char* temp = data_ADC;
	//while (temp)
	//{
	//	adcChannels_[channel].values
	//	*(short *)tmp = *(value[channelMap[j * 3]] + i);
	//	if (channelMap[j * 3 + 1] != ADC_CHANNEL_COUNT) //channelMap[22] j=7 or channelMap[19] j=6
	//	{
	//		*(short *)(tmp + 4) = *(value[channelMap[j * 3 + 1]] + i);
	//	}
	//	*(short *)(tmp + 6) = 2;
	//	*(short *)(tmp + 8) = *(value[channelMap[j * 3 + 2]] + i);
	//	*(short *)(tmp + 10) = 4;
	//	*(short *)(tmp + 12) = *(code + i);
	//	*(char *)(tmp + 16) = j;  //
	//	tmp = tmp + 20;
	//}


	delete []data_ADC;
}
