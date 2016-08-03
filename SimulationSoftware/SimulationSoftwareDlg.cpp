
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

// device control command IDs
#define COMMAND_GET_SN                      0x0001
#define COMMAND_SET_DEVICE_INFO             0x0002
#define COMMAND_UPDATE_DEBUG_STATE          0x0003
#define COMMAND_UPGRADE                     0x0004
#define COMMAND_UPGRADE_DATA                0x0005
#define COMMAND_RESTART                     0x0006
#define COMMAND_ECHO                        0x8181
//#define COMMAND_GET_IR_PARAMETERS           0x0003
#define COMMAND_GET_IR_VALUES               0x0007
#define COMMAND_SET_IR_PARAMETERS           0x0008
#define COMMAND_UPDATE_IR_PARAMETERS        0x0009
#define COMMAND_START_MASTER_SIGNAL_DETECT  0x0006
#define COMMAND_GET_CIS_PARAMETER           0x0009
#define COMMAND_TAKE_CIS_IMAGE              0x000a
#define COMMAND_SET_CIS_PARAMETER           0x000b
#define COMMAND_UPDATE_CIS_PARAMETER        0x000c
#define COMMAND_GET_CIS_CORRECTION_TABLE    0x000d
#define COMMAND_UPDATE_CIS_CORRECTION_TABLE 0x000e
#define COMMAND_GET_MAC						0x0011
#define COMMAND_GET_STUDY_COMPLETED_STATE   0x0012
#define COMMAND_SET_AGING_TIME              0x0013
#define COMMAND_START_TAPE_STUDY            0x0014
#define COMMAND_START_MOTOR                 0x0015
#define COMMAND_START_RUN_CASH_DETECT       0x8004
#define COMMAND_START_SIGNAL_COLLECT        0x0016
#define COMMAND_DISABLE_DEBUG               0x0017
#define COMMAND_SET_TIME                    0x0018
#define COMMAND_GET_TIME                    0x0019
#define COMMAND_LIGHT_CIS                   0x0020
#define COMMAND_SET_SN                      0x0021
#define COMMAND_TAPE_LEARNING				0x0022


// CommandResult
CommandResult::CommandResult()
: dataLength_(0)
, status_(0) {
	dataBuffer_ = staticBuffer_;
}

CommandResult::~CommandResult() {
	if (dataBuffer_ != staticBuffer_) {
		delete[] dataBuffer_;
	}
}

bool CommandResult::IsOk() const {
	return status_ == 0;
}

int CommandResult::GetStatus() const {
	return status_;
}

int CommandResult::GetDataLength() const {
	return dataLength_;
}

const void *CommandResult::GetData() const {
	return dataBuffer_;
}

int CommandResult::GetData(void *buffer, int size) {
	if (size > dataLength_) {
		size = dataLength_;
	}
	if (size > 0) {
		memcpy(buffer, dataBuffer_, size);
	}
	return size;
}

void *CommandResult::GetDataBuffer(int length) {
	if (dataBuffer_ != staticBuffer_) {
		delete[] dataBuffer_;
	}
	if (length > STATIC_BUFFER_SIZE) {
		dataBuffer_ = new char[length];
	}
	else {
		dataBuffer_ = staticBuffer_;
	}
	dataLength_ = length;

	return dataBuffer_;
}

void CommandResult::SetStatus(int code) {
	status_ = code;
}


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

		if (serverSocket_->Listen(L"172.16.100.174",1234))
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
				//char recvBuffer[256];
				//recvSocker_.Receive(recvBuffer,sizeof(recvBuffer)); //����

				CommandResult result;
				if (!ReadResult(&result))
				{
					GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"���յ�����ʧ��...");
					break;
				}
				GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"���յ�����,�ȴ���������...");
				if (result.GetStatus() == 0x0002)
				{
					if (!SendCommandNoResult(COMMAND_SET_DEVICE_INFO, 0, &deviceInfo, sizeof(deviceInfo)))
					{
						recvSocker_.Close();
					}				
					GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"�����豸��Ϣ����...");
				}
				if (result.GetStatus() == 0x0018)
				{
					SendCommandNoResult(COMMAND_SET_TIME, 0, 0, 0);
				}
				if (result.GetStatus()==0x000d)
				{
					SendCommandNoResult(COMMAND_GET_CIS_CORRECTION_TABLE,0,&cisTable.data,sizeof(cisTable.data));
				}

				if (result.GetStatus()==0x8181)
				{
					SendCommandNoResult(COMMAND_ECHO, 0, 0, 0);
				}
			//	char szText[256];
			//	int nRecv = ::recv(s, szText, strlen(szText), 0);  //�ж����ӳɹ���socket�յ��Ļذ�
			//	if (nRecv == SOCKET_ERROR)
			//	{
			//		TRACE("���մ���...");
			//		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"���մ����˳�...");
			//		break;
			//	}
			//	if (nRecv > 0)						// ��2���ɶ�
			//	{
			//		szText[nRecv] = '\0';
			//		TRACE("���յ����ݣ�%s \n", szText);

			//		//char Sendbuff[100] = { 0 };
			//		//sprintf(Sendbuff, "this zhangsan");
			//		//::send(s, Sendbuff, strlen(Sendbuff + 1), 0);

			//		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"���յ�����,�ȴ���������...");
			//	//	break;
			//	}
			//	if (nRecv==0)				      // ��3�����ӹرա����������ж�
			//	{
			//		::closesocket(s);
			//		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"����������������Ͽ������˵�����...");
			//		//m_checkState = false;
			//		m_stateBtn.SetWindowText(L"�ر��ٴο���");
			//		TRACE("���ӹر�....");
			//		//return true;
			//		break;
			//	}
			//	
			///*	char* sendBuffer = new char[sizeof(DeviceInfo)];
			//	memset(sendBuffer, 0, sizeof(sendBuffer));
			//	memcpy(sendBuffer, &deviceInfo, sizeof(DeviceInfo));
			//	int len_send=send(s,sendBuffer,sizeof(sendBuffer),0);*/  //������
			//	
			//	//Ӧ���ȼ���һ���յ��İ��Ƿ���ȷ��Ȼ����send;û����У��
			//	int len_send = send(s, (char*)&cmd, sizeof(cmd), 0);
			//	if (len_send==SOCKET_ERROR)
			//	{
			//		OutputDebugString(L"����ʧ��....");  //MFC ��trace
			//	}
			//	
			//	int len_send2 = send(s, (char*)&returnTime, sizeof(returnTime), 0);

			//	int len_send3 = send(s, (char*)&cisTable, sizeof(cisTable), 0);

			//	int len_send4 = send(s, (char*)&updateCmd, sizeof(updateCmd), 0);

			//	int len_send5 = send(s, (char*)&upgradeDate, sizeof(upgradeDate), 0);

			//	if (len_send3 == SOCKET_ERROR)
			//	{
			//		OutputDebugString(L"����ʧ��....");  //MFC ��trace
			//	}			
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
//����һ��ָ�� Echo
bool CSimulationSoftwareDlg::SendCommand(int id) {
	return SendCommand(id, NULL, 0);
}
//���ʹ��и��ص�ָ��
bool CSimulationSoftwareDlg::SendCommand(int id, const void *data, int dataLength) {
	return SendCommand(id, 0, data, dataLength);
}
//�����м����������ص�ָ��
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
//����ָ�������result
bool CSimulationSoftwareDlg::SendCommand(int id, const void *data, int dataLength, CommandResult *result) {
	return SendCommand(id, 0, data, dataLength, result);
}
//����ָ�����������result
bool CSimulationSoftwareDlg::SendCommand(int id, int count, const void *data, int dataLength, CommandResult *result) {
	ASSERT(result != NULL);

	if (!SendCommandNoResult(id, count, data, dataLength)) {
		return false;
	}
	return ReadResult(result);
}
//���Ͱ�ͷ������
bool CSimulationSoftwareDlg::SendCommandNoResult(int id, int count, const void *data, int dataLength) {
	PacketHeader hd;
	hd.signatures[0] = 'R';
	hd.signatures[1] = 'P';
	hd.id = (unsigned short)0x0000;
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
	
	hd.signatures[0] = 'R';
	hd.signatures[1] = 'P';
	hd.status = (unsigned short)0x0000;
	hd.count = 0; //�������
	hd.length = (unsigned int)0xC8;  //200

	//����DeviceInfo��Ϣ
	memset(&deviceInfo, 0, sizeof(deviceInfo));

	/*CString deviceInfo_sn;
	GetPrivateProfileString(L"DeviceInfo", L"sn", L"", deviceInfo_sn.GetBuffer(MAX_PATH), MAX_PATH, GetExPath() + L"DEVICEINFO.ini");
	deviceInfo_sn.ReleaseBuffer();
	strncpy_s(deviceInfo.sn, (LPSTR)(LPCTSTR)deviceInfo_sn, sizeof(deviceInfo_sn));*/

	GetPrivateProfileString(L"DeviceInfo", L"sn", L"", (LPWSTR)deviceInfo.sn, MAX_PATH, GetExPath() + L"DEVICEINFO.ini");
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
	cisTable.length = (unsigned int)0xB4000;
	for (int side = 0; side < CIS_COUNT; side++) {
		for (int color = 0; color < COLOR_COUNT; color++) {
			for (int x = 0; x < CIS_IMAGE_WIDTH; x++) {
				for (int level = 0; level < 256; level++) {
					cisTable.data[side][color][x][level] = level;
				}
			}
		}
	}
	//�����̼�����λ������
	updateCmd.signatures[0] = 'R';
	updateCmd.signatures[1] = 'P';
	updateCmd.status = (unsigned short)0x0000;
	updateCmd.count = 0;
	updateCmd.length = 4;
	updateCmd.numOfBlock = 4;

	//�������ݰ�����λ������
	upgradeDate.signatures[0] = 'R';
	upgradeDate.signatures[1] = 'P';
	upgradeDate.status = (unsigned short)0x0000;
	upgradeDate.count = 0; //�������
	upgradeDate.length = (unsigned int)0x0000;  
}