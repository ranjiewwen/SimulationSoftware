
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
	if (m_checkState)
	{
		m_stateBtn.SetWindowText(L"�㳮����");
		//m_processing = true;
		
		if (serverSocket_->Listen(L"172.16.100.174", 1234))
		{
			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"�㳮���򿪣����������������������...");
			m_displayListBox.AddString(L"�㳮���򿪣����������������������...");
		}
		SOCKET s = serverSocket_->Accept(100);
		recvSocker_.Attach(s);
		//recvSocker_.SetRecvBufferSize(1024);

		if (s==INVALID_SOCKET)
		{
			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"�㳮�����ӵ������������ʧ��...");
			m_displayListBox.AddString(L"�㳮�����ӵ������������ʧ��...");
		}
		else
		{
			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"�㳮�������ӵ������������...");
			m_displayListBox.AddString(L"�㳮�������ӵ������������...");
			start();
		//		if (result.GetStatus()==0x8181)
		//		{
		//			SendCommandNoResult(COMMAND_ECHO, 0, 0, 0);
		//		}
		//	//	char szText[256];
		//	//	int nRecv = ::recv(s, szText, strlen(szText), 0);  //�ж����ӳɹ���socket�յ��Ļذ�
		//	//	if (nRecv == SOCKET_ERROR)
		//	//	{
		//	//		TRACE("���մ���...");
		//	//		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"���մ����˳�...");
		//	//		break;
		//	//	}
		//	//	if (nRecv > 0)						// ��2���ɶ�
		//	//	{
		//	//		szText[nRecv] = '\0';
		//	//		TRACE("���յ����ݣ�%s \n", szText);
		//	//		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"���յ�����,�ȴ���������...");
		//	//	//	break;
		//	//	}
		//	//	if (nRecv==0)				      // ��3�����ӹرա����������ж�
		//	//	{
		//	//		::closesocket(s);
		//	//		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"����������������Ͽ������˵�����...");
		//	//		//m_checkState = false;
		//	//		m_stateBtn.SetWindowText(L"�ر��ٴο���");
		//	//		TRACE("���ӹر�....");
		//	//		//return true;
		//	//		break;
		//	//	}
		//	//	
		//	//	//Ӧ���ȼ���һ���յ��İ��Ƿ���ȷ��Ȼ����send;û����У��
		//	//	int len_send = send(s, (char*)&cmd, sizeof(cmd), 0);
		//	//	if (len_send==SOCKET_ERROR)
		//	//	{
		//	//		OutputDebugString(L"����ʧ��....");  //MFC ��trace
		//	//	}
		//	//	
		//	//	int len_send2 = send(s, (char*)&returnTime, sizeof(returnTime), 0);
		//	//	int len_send3 = send(s, (char*)&cisTable, sizeof(cisTable), 0);
		//	//	int len_send4 = send(s, (char*)&updateCmd, sizeof(updateCmd), 0);
		//	//	int len_send5 = send(s, (char*)&upgradeDate, sizeof(upgradeDate), 0);
		//	//	if (len_send3 == SOCKET_ERROR)
		//	//	{
		//	//		OutputDebugString(L"����ʧ��....");  //MFC ��trace
		//	//	}			
		//   }
		}
	}
	else  //����������ر�  //ò����������»Ῠס
	{
		m_stateBtn.SetWindowText(L"�㳮���ر�");
		serverSocket_->Close();
		//recvSocker_.Close();
	//	delete serverSocket_;

		//stop(); //��ס
		//m_processing = false;  //�����̣߳��ٴδ򿪵㳮��ʱ�������������������ݣ����������Ļ����������Ĺر�,���ڷ�echo�����򣬹رպ��ٴδ�û�п����߳�;��������رգ���ʵsocket�Ѿ����ˣ�C/S��������������
		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"�㳮���رգ��Ͽ��������������������...");	
		m_displayListBox.AddString(L"�㳮���رգ��Ͽ��������������������...");
	}
}

void CSimulationSoftwareDlg::process()
{
	while (m_processing)
	{
		CommandResult result;
		if (!ReadResult(&result))  //û�н�������ͱ����رն��п���
		{
			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"���յ�����ʧ��...�п��ܿͻ��������ر�����...");
			m_displayListBox.AddString(L"���յ�����ʧ��...�п��ܿͻ��������ر�����....");

			serverSocket_->Close();
			//delete serverSocket_;
			//m_stateBtn.SetState(false);
			//m_checkState = false;
			m_stateBtn.SetWindowText(L"�ر�-�㳮��");
			break;
		}
		else
		{
	//		GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"ReadResultΪfalse�������յ�����ʱ���ظ�����...");
	//		m_displayListBox.AddString(L"ReadResultΪfalse�������յ�����ʱ���Żظ�����...");
		}
		if (result.GetStatus() == 0x0002)
		{
			CriticalSection::ScopedLocker locker(criSec_);
			if (!SendCommandNoResult(COMMAND_SET_DEVICE_INFO, 0, &deviceInfo, sizeof(deviceInfo)))
			{
				serverSocket_->Close();
			}
			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"�����豸��Ϣ����...");
			m_displayListBox.AddString(L"�ظ� COMMAND_SET_DEVICE_INFO ����...");
		}
		if (result.GetStatus() == 0x0018)
		{
			CriticalSection::ScopedLocker locker(criSec_);
			SendCommandNoResult(COMMAND_SET_TIME, 0, 0, 0);
			m_displayListBox.AddString(L"�ظ� COMMAND_SET_TIME ����...");
		}
		if (result.GetStatus() == 0x000d)
		{	
			CriticalSection::ScopedLocker locker(criSec_);
			SendCommandNoResult(COMMAND_GET_CIS_CORRECTION_TABLE, 0, &cisCorrectionTable_.data, sizeof(cisCorrectionTable_));
			m_displayListBox.AddString(L"�ظ� COMMAND_GET_CIS_CORRECTION_TABLE ����...");
		}
		if (result.GetStatus() == 0x0004)
		{	
			CriticalSection::ScopedLocker locker(criSec_);
			//����ini�ļ��İ汾������ʱ��λ�����ܸ���
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
			m_displayListBox.AddString(L"�ظ� COMMAND_UPGRADE ������յ�newVersion����ini,�´θ���...");
		}
		if (result.GetStatus()==0x0005)
		{	
			CriticalSection::ScopedLocker locker(criSec_);
			//���Խ�����������			
			if (result.GetDataLength()<sizeof(length_))   //���һ��ʧ��
			{
				TRACE("receive failed...");
			}
			CFile file(_T("f:\\firmware.dat"),  CFile::modeWrite | CFile::typeBinary);  //CFile::modeCreate
			file.SeekToEnd();
			file.Write(result.GetData(), result.GetDataLength());
			file.Close();
			SendCommandNoResult(COMMAND_UPGRADE_DATA, 0, 0, 0);
			m_displayListBox.AddString(L"�ظ� COMMAND_UPGRADE_DATA ���������µ����ݰ�dat...");
		}
		if (result.GetStatus()==0x0003)  //����˵���״̬��ô����ģ�
		{	
			CriticalSection::ScopedLocker locker(criSec_);
			//���յ���״̬
			int states[16] = { 0 };
			result.GetData(states, sizeof(states));
			CString strTemp;
			strTemp.Format(L"%d", states[0]);
			WritePrivateProfileString(L"DeviceInfo", L"debugState[1]",/*L"23"*/strTemp, GetExPath() + L"DEVICEINFO.ini");
			
			SendCommandNoResult(COMMAND_UPDATE_DEBUG_STATE, 0, 0, 0);
			m_displayListBox.AddString(L"�ظ� COMMAND_UPDATE_DEBUG_STATE ����������״̬ini������...");
		}
		if (result.GetStatus()==0x0006)
		{		
			CriticalSection::ScopedLocker locker(criSec_);
			SendCommandNoResult(COMMAND_RESTART, 0, 0, 0);
			m_displayListBox.AddString(L"�ظ� COMMAND_RESTART ������������㳮��...");
			serverSocket_->Close();
			//delete serverSocket_;	
		    //m_checkState = false;
			m_processing = false;
			m_stateBtn.SetWindowText(L"�����㳮��");
				
			if (!serverSocket_->IsOpened())  //�������ֶ�����
			{
				m_displayListBox.AddString(L"���������㳮��...�ط�����ָ��...");
				if (serverSocket_->Listen(L"172.16.100.174", 1234))
				{
					GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"�㳮���򿪣����������������������...");
					m_displayListBox.AddString(L"�㳮�������ɹ�������IR����...���������������������...");
				}
				SOCKET s = serverSocket_->Accept(10);
				recvSocker_.Attach(s);
				m_processing = true;
				m_stateBtn.SetWindowText(L"�㳮����");
				InitCommandParameter();
			}

			GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(L"���ֽУ��...");
			m_displayListBox.AddString(L"���ֽУ��....��������");
		}
		if (result.GetStatus() == 0x8181)
		{	
			CriticalSection::ScopedLocker locker(criSec_);
			SendCommandNoResult(COMMAND_ECHO, 0, 0, 0);
			m_displayListBox.AddString(L"�ظ� COMMAND_ECHO ����...");
		}
		if (result.GetStatus()==0x0008)
		{
			CriticalSection::ScopedLocker locker(criSec_);
			//��ȡ����ܵ�ֵ
			emissionValues[IR_COUNT] = { 0 };
			emissionValues_[IR_COUNT] = { 0 };
			if (m_isPalcePaper)
			{
				result.GetData(emissionValues, sizeof(emissionValues));
				SendCommandNoResult(COMMAND_SET_IR_PARAMETERS, 0, NULL, 0);
				m_displayListBox.AddString(L"�ظ� COMMAND_SET_IR_PARAMETERS ������淢���ֵ����ֽ״̬...");
			}
			else
			{
				result.GetData(emissionValues_, sizeof(emissionValues_));
				SendCommandNoResult(COMMAND_SET_IR_PARAMETERS, 0, NULL, 0);
				m_displayListBox.AddString(L"�ظ� COMMAND_SET_IR_PARAMETERS ������淢���ֵ����ֽ״̬...");
			}
		}
		if (result.GetStatus()==0x0007)
		{
			CriticalSection::ScopedLocker locker(criSec_);
			//���ݷ���ܵ�ֵ�����Լ�����չܵ�ֵ
			if (m_isPalcePaper)
			{
				for (int i = 0; i < IR_COUNT; i++)
				{
					collectionValues[i] = (emissionValues[i] - 1300) *100/ 2200 + 650;  //��ȡ��
				}
				SendCommandNoResult(COMMAND_GET_IR_VALUES, 0, collectionValues, IR_COUNT * sizeof(int));
				m_displayListBox.AddString(L"�ظ� COMMAND_SET_IR_PARAMETERS �����ֽ״̬�����ͷ����ֵ...");
			}
			else
			{
				for (int i = 0; i < IR_COUNT; i++)
				{
					collectionValues_[i] = (emissionValues_[i] - 1300)*400 /2200  + 3600;  //��ȡ��
				}
				SendCommandNoResult(COMMAND_GET_IR_VALUES, 0, collectionValues_, IR_COUNT * sizeof(int));
				m_displayListBox.AddString(L"�ظ� COMMAND_SET_IR_PARAMETERS �����ֽ״̬�����ͷ����ֵ...");
			}
		}
		if (result.GetStatus()==0x0015)
		{
			CriticalSection::ScopedLocker locker(criSec_);
			//���ת��ָ��ʱ����ֽ״̬��Ϊ��ֽ״̬
			m_isPalcePaper = false;
			m_placePaper.SetWindowText(L"��ֽ״̬");
			SendCommandNoResult(COMMAND_START_MOTOR, 0, 0, 0);
			m_displayListBox.AddString(L"�ظ� COMMAND_START_MOTOR ������������ȷ����ֽ״̬...");
		}
		if (result.GetStatus()==0x0009)
		{
			CriticalSection::ScopedLocker locker(criSec_);
			//������º�ķ������

			SendCommandNoResult(COMMAND_UPDATE_IR_PARAMETERS, 0, NULL, 0);
			m_displayListBox.AddString(L"�ظ� COMMAND_UPDATE_IR_PARAMETERS ����...");
		}
	

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
	hd.id = (unsigned short)0x0000;  //id������û������
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
	//����DeviceInfo��Ϣ
	memset(&deviceInfo, 0, sizeof(deviceInfo));

	//CString deviceInfo_sn;
	//GetPrivateProfileString(L"DeviceInfo", L"sn", L"", deviceInfo_sn.GetBuffer(MAX_PATH), MAX_PATH, GetExPath() + L"DEVICEINFO.ini");
	//deviceInfo_sn.ReleaseBuffer();
	//strncpy_s(deviceInfo.sn, (LPSTR)(LPCTSTR)deviceInfo_sn, sizeof(deviceInfo_sn));
	//GetPrivateProfileString(L"DeviceInfo", L"sn", L"", (LPWSTR)deviceInfo.sn, MAX_PATH, GetExPath() + L"DEVICEINFO.ini");  //��TCHAR�ķ�ʽ
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_isPalcePaper)
	{
		m_placePaper.SetWindowText(L"��ֽУ��");
	}
}
