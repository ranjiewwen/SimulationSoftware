
// SimulationSoftwareDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SimulationSoftware.h"
#include "SimulationSoftwareDlg.h"
#include "afxdialogex.h"
//#include "TCP_Server.h"

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


// CSimulationSoftwareDlg �Ի���



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


// CSimulationSoftwareDlg ��Ϣ�������

BOOL CSimulationSoftwareDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSimulationSoftwareDlg::OnPaint()
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
HCURSOR CSimulationSoftwareDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSimulationSoftwareDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	CDialogEx::OnOK();
}


void CSimulationSoftwareDlg::OnBnClickedStatebutton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	
	//if (m_checkState)
	//{
	//	m_stateBtn.SetWindowText(L"�㳮����");
	//	serverSocket = new TCP_Server(1234, inet_addr("172.16.100.174"));
	//	GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"�㳮���򿪣����������������������...");	
	//	
	//	if (serverSocket->process()==INVALID_SOCKET)
	//	{
	//		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"�㳮�����ӵ������������ʧ��...");
	//	}
	//	else
	//	{
	//		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"�㳮�������ӵ������������...");
	//	}
 // //      //�ͻ��������ر�����
	//	//if (serverSocket->clientIsClose())
	//	//{
	//	//	GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"������������Ͽ������˵�����...");
	//	//	m_checkState = false;
	//	//	m_stateBtn.SetWindowText(L"�㳮���ر�");
	//	//}
	//}
	//else
	//{
	//	m_stateBtn.SetWindowText(L"�㳮���ر�");
	//	GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"�㳮���رգ��Ͽ��������������������...");
	//	serverSocket->Close();
	//}

	if (m_checkState)
	{
		m_stateBtn.SetWindowText(L"�㳮����");
		serverSocket_ = new TcpSocket;

		if (serverSocket_->Listen(1234))
		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"�㳮���򿪣����������������������...");

		if (serverSocket_->Accept(100)==INVALID_SOCKET)
		{
			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"�㳮�����ӵ������������ʧ��...");
		}
		else
		{
			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"�㳮�������ӵ������������...");
		}
		serverSocket_->SetRecvBufferSize(1024);
	    //�ͻ��������ر�����
		while (TRUE)
		{	
			int nRecv = serverSocket_->Receive(szText,strlen(szText));
			if (nRecv==0)
			{
				GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"������������Ͽ������˵�����...");
				m_checkState = false;
				m_stateBtn.SetWindowText(L"�㳮���ر�");
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
		m_stateBtn.SetWindowText(L"�㳮���ر�");
		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"�㳮���رգ��Ͽ��������������������...");
		serverSocket_->Close();
	}
}
