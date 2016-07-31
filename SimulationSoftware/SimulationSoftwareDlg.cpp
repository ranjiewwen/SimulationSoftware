
// SimulationSoftwareDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SimulationSoftware.h"
#include "SimulationSoftwareDlg.h"
#include "afxdialogex.h"
//#include "TCP_Server.h"

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

		if (serverSocket_->Accept(100)==INVALID_SOCKET)
		{
			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"点钞机连接到生产管理软件失败...");
		}
		else
		{
			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"点钞机已连接到生产管理软件...");
		}
		serverSocket_->SetRecvBufferSize(1024);
	    //客户端主动关闭连接
		while (TRUE)
		{	
			int nRecv = serverSocket_->Receive(szText,strlen(szText));
			if (nRecv==0)
			{
				GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"生产管理软件断开与服务端的连接...");
				m_checkState = false;
				m_stateBtn.SetWindowText(L"点钞机关闭");
				break;
			}
			if ((nRecv == SOCKET_ERROR) && (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR))
			{
				printf("recv fail...");
				serverSocket_->Close();
				//break;
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
