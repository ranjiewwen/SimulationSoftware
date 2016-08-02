
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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    InitCommandParameter();
}

void CSimulationSoftwareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATEBUTTON, m_stateBtn);
	DDX_Check(pDX, IDC_STATEBUTTON, m_checkState);
}

BEGIN_MESSAGE_MAP(CSimulationSoftwareDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSimulationSoftwareDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_STATEBUTTON, &CSimulationSoftwareDlg::OnBnClickedStatebutton)
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
	
	//if (m_checkState)
	//{
	//	m_stateBtn.SetWindowText(L"点钞机打开");
	//	serverSocket = new TCP_Server(1234, inet_addr("172.16.100.174"));
	//	GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"点钞机打开，监听生产管理软件的请求...");	
	//	
	//	if (serverSocket->process()==INVALID_SOCKET)
	//	{
	//		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"点钞机连接到生产管理软件失败...");
	//	}
	//	else
	//	{
	//		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"点钞机已连接到生产管理软件...");
	//	}
 // //      //客户端主动关闭连接
	//	//if (serverSocket->clientIsClose())
	//	//{
	//	//	GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"生产管理软件断开与服务端的连接...");
	//	//	m_checkState = false;
	//	//	m_stateBtn.SetWindowText(L"点钞机关闭");
	//	//}
	//}
	//else
	//{
	//	m_stateBtn.SetWindowText(L"点钞机关闭");
	//	GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"点钞机关闭，断开与生产管理软件的连接...");
	//	serverSocket->Close();
	//}

	if (m_checkState)
	{
		m_stateBtn.SetWindowText(L"点钞机打开");
		serverSocket_ = new TcpSocket;

		if (serverSocket_->Listen(1234))
		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"点钞机打开，监听生产管理软件的请求...");
		SOCKET s = serverSocket_->Accept(100);
		recvSocker_.Attach(s);
		recvSocker_.SetRecvBufferSize(1024);

		if (s==INVALID_SOCKET)
		{
			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"点钞机连接到生产管理软件失败...");
		}
		else
		{
			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"点钞机已连接到生产管理软件...");

			while (TRUE)
			{
				char recvBuffer[256];
				recvSocker_.Receive(recvBuffer,sizeof(recvBuffer));

				char szText[256];
				int nRecv = ::recv(s, szText, strlen(szText), 0);  //判断链接成功的socket收到的回包
				if (nRecv == SOCKET_ERROR)
				{
					TRACE("接收错误...");
					GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"接收错误退出...");
					break;
				}
				if (nRecv > 0)						// （2）可读
				{
					szText[nRecv] = '\0';
					TRACE("接收到数据：%s \n", szText);

					//char Sendbuff[100] = { 0 };
					//sprintf(Sendbuff, "this zhangsan");
					//::send(s, Sendbuff, strlen(Sendbuff + 1), 0);

					GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"接收到数据,等待发送数据...");
				//	break;
				}
				if (nRecv==0)				      // （3）连接关闭、重启或者中断
				{
					::closesocket(s);
					GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"生产管理软件主动断开与服务端的连接...");
					//m_checkState = false;
					m_stateBtn.SetWindowText(L"关闭再次开机");
					TRACE("链接关闭....");
					//return true;
					break;
				}
				
			/*	char* sendBuffer = new char[sizeof(DeviceInfo)];
				memset(sendBuffer, 0, sizeof(sendBuffer));
				memcpy(sendBuffer, &deviceInfo, sizeof(DeviceInfo));
				int len_send=send(s,sendBuffer,sizeof(sendBuffer),0);*/  //有问题
				//应该先检验一下收到的包是否正确，然后再send
				int len_send = send(s, (char*)&cmd, sizeof(cmd), 0);
				if (len_send==SOCKET_ERROR)
				{
					OutputDebugString(L"发送失败....");  //MFC 用trace
				}
				
				int len_send2 = send(s, (char*)&returnTime, sizeof(returnTime), 0);

				int len_send3 = send(s, (char*)&cisTable, sizeof(cisTable), 0);
				
				if (len_send3 == SOCKET_ERROR)
				{
					OutputDebugString(L"发送失败....");  //MFC 用trace
				}
		   }
		}
	}
	else
	{
		m_stateBtn.SetWindowText(L"点钞机关闭");
		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"点钞机关闭，断开与生产管理软件的连接...");
		serverSocket_->Close();
	}
}


void CSimulationSoftwareDlg::InitCommandParameter()
{
	
	hd.signatures[0] = 'R';
	hd.signatures[1] = 'P';
	hd.status = (unsigned short)0x0000;
	hd.count = 0; //请求计数
	hd.length = (unsigned int)0xC8;  //??

	//发送DeviceInfo信息
	memset(&deviceInfo, 0, sizeof(deviceInfo));

	//CString deviceInfo_sn;
	//GetPrivateProfileString(L"DeviceInfo", L"sn", L"", deviceInfo_sn.GetBuffer(MAX_PATH), MAX_PATH, GetExPath() + L"DEVICEINFO.ini");
	//deviceInfo_sn.ReleaseBuffer(); 
	//strncpy_s(deviceInfo.sn, (LPSTR)(LPCTSTR)deviceInfo_sn, sizeof(deviceInfo_sn));

	GetPrivateProfileString(L"DeviceInfo", L"sn", L"", deviceInfo.sn, MAX_PATH, GetExPath() + L"DEVICEINFO.ini");
	GetPrivateProfileString(L"DeviceInfo", L"model", L"", (LPWSTR)deviceInfo.model, sizeof(deviceInfo.model), GetExPath() + L"DEVICEINFO.ini");
	GetPrivateProfileString(L"DeviceInfo", L"firmwareVersion", L"", (LPWSTR)deviceInfo.firmwareVersion, MAX_PATH, GetExPath() + L"DEVICEINFO.ini");

	deviceInfo.numberOfCIS = GetPrivateProfileInt(L"DeviceInfo", L"numberOfCIS", 0, GetExPath() + L"DEVICEINFO.ini");
	deviceInfo.numberOfIR = GetPrivateProfileInt(L"DeviceInfo", L"numberOfIR", 0, GetExPath() + L"DEVICEINFO.ini");
	deviceInfo.numberOfMH = GetPrivateProfileInt(L"DeviceInfo", L"numberOfMH", 0, GetExPath() + L"DEVICEINFO.ini");
	deviceInfo.reserved = GetPrivateProfileInt(L"DeviceInfo", L"reserved", 0, GetExPath() + L"DEVICEINFO.ini");

	deviceInfo.cisColorFlags = GetPrivateProfileInt(L"DeviceInfo", L"cisColorFlags", 0, GetExPath() + L"DEVICEINFO.ini");
	deviceInfo.cisImageWidth = GetPrivateProfileInt(L"DeviceInfo", L"cisImageWidth", 0, GetExPath() + L"DEVICEINFO.ini");
	deviceInfo.cisImageHeight = GetPrivateProfileInt(L"DeviceInfo", L"cisImageHeight", 0, GetExPath() + L"DEVICEINFO.ini");
	deviceInfo.selfTestState = GetPrivateProfileInt(L"DeviceInfo", L"selfTestState", 0, GetExPath() + L"DEVICEINFO.ini");
	deviceInfo.debugState[0] = 22; //

	//TCHAR debugState_[MAX_PATH];
	//GetPrivateProfileString(L"DeviceInfo", L"debugState",L"",debugState, MAX_PATH,GetExPath() + L"DEVICEINFO.ini");
	//CString str;
	//str.Format(L"%s", debugState_);
	////std::string str_(str.GetBuffer()); str.ReleaseBuffer();
	//for (int i = 0; i<sizeof(str); i++)
	//{
	//}

	//设备信息，下位机返回
	cmd.packetHeader_ = hd;
	cmd.deviceInfo_ = deviceInfo;
	//int size = sizeof(TCHAR);  //2字节
	//设置下位机时间，下位机返回
	returnTime.signatures[0] = 'R';
	returnTime.signatures[1] = 'P';
	returnTime.status = (unsigned short)0x0000;
	returnTime.count = 0; //请求计数
	returnTime.length = (unsigned int)0x0000;  //??
	//CIS增益校准表,下位机返回
	cisTable.signatures[0] = 'R';
	cisTable.signatures[1] = 'P';
	cisTable.status = (unsigned short)0x0000;
	cisTable.count = 0;
	cisTable.length = (unsigned int)0xB400;
	for (int side = 0; side < CIS_COUNT; side++) {
		for (int color = 0; color < COLOR_COUNT; color++) {
			for (int x = 0; x < CIS_IMAGE_WIDTH; x++) {
				for (int level = 0; level < 256; level++) {
					cisTable.data[side][color][x][level] = level;
				}
			}
		}
	}

}