
// SimulationSoftwareDlg.cpp : ʵ���ļ�
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

#include <stdio.h>
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
		SOCKET s = serverSocket_->Accept(100);
		recvSocker_.Attach(s);
		recvSocker_.SetRecvBufferSize(1024);

		if (s==INVALID_SOCKET)
		{
			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"�㳮�����ӵ������������ʧ��...");
		}
		else
		{
			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"�㳮�������ӵ������������...");

			while (TRUE)
			{
				char recvBuffer[256];
				recvSocker_.Receive(recvBuffer,sizeof(recvBuffer));

				char szText[256];
				int nRecv = ::recv(s, szText, strlen(szText), 0);  //�ж����ӳɹ���socket�յ��Ļذ�
				if (nRecv == SOCKET_ERROR)
				{
					TRACE("���մ���...");
					GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"���մ����˳�...");
					break;
				}
				if (nRecv > 0)						// ��2���ɶ�
				{
					szText[nRecv] = '\0';
					TRACE("���յ����ݣ�%s \n", szText);

					//char Sendbuff[100] = { 0 };
					//sprintf(Sendbuff, "this zhangsan");
					//::send(s, Sendbuff, strlen(Sendbuff + 1), 0);

					GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"���յ�����,�ȴ���������...");
				//	break;
				}
				if (nRecv==0)				      // ��3�����ӹرա����������ж�
				{
					::closesocket(s);
					GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"����������������Ͽ������˵�����...");
					//m_checkState = false;
					m_stateBtn.SetWindowText(L"�ر��ٴο���");
					TRACE("���ӹر�....");
					//return true;
					break;
				}
				
			/*	char* sendBuffer = new char[sizeof(DeviceInfo)];
				memset(sendBuffer, 0, sizeof(sendBuffer));
				memcpy(sendBuffer, &deviceInfo, sizeof(DeviceInfo));
				int len_send=send(s,sendBuffer,sizeof(sendBuffer),0);*/  //������
				//Ӧ���ȼ���һ���յ��İ��Ƿ���ȷ��Ȼ����send
				int len_send = send(s, (char*)&cmd, sizeof(cmd), 0);
				if (len_send==SOCKET_ERROR)
				{
					OutputDebugString(L"����ʧ��....");  //MFC ��trace
				}
				
				int len_send2 = send(s, (char*)&returnTime, sizeof(returnTime), 0);

				int len_send3 = send(s, (char*)&cisTable, sizeof(cisTable), 0);
				
				if (len_send3 == SOCKET_ERROR)
				{
					OutputDebugString(L"����ʧ��....");  //MFC ��trace
				}
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


void CSimulationSoftwareDlg::InitCommandParameter()
{
	
	hd.signatures[0] = 'R';
	hd.signatures[1] = 'P';
	hd.status = (unsigned short)0x0000;
	hd.count = 0; //�������
	hd.length = (unsigned int)0xC8;  //??

	//����DeviceInfo��Ϣ
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

	//�豸��Ϣ����λ������
	cmd.packetHeader_ = hd;
	cmd.deviceInfo_ = deviceInfo;
	//int size = sizeof(TCHAR);  //2�ֽ�
	//������λ��ʱ�䣬��λ������
	returnTime.signatures[0] = 'R';
	returnTime.signatures[1] = 'P';
	returnTime.status = (unsigned short)0x0000;
	returnTime.count = 0; //�������
	returnTime.length = (unsigned int)0x0000;  //??
	//CIS����У׼��,��λ������
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