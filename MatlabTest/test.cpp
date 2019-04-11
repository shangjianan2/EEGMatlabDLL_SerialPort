#include "test.h"
#include <string>
#include "stdlib.h"
#include <iostream>
#include "CyAPI.h"

#define BUFF_LENGTH 3
#define REC_BUFF_SIZE 5*34


using namespace std;

void Init_DCB(DCB *p_DCB)
{
	p_DCB->BaudRate = 230400;
	p_DCB->Parity = NOPARITY;//ʧ��У��λ
	p_DCB->StopBits = ONESTOPBIT;//һλֹͣλ
	p_DCB->ByteSize = 8;//����Ϊ8λ
}

void Read_From_SerialPort(HANDLE handle_tt, char *buff, DWORD *length)//��֪���������Ĵ����Ƿ��ܹ��ɹ�
{
	DWORD temp_length = *length;
	ReadFile(handle_tt, buff, temp_length, length, NULL);
}

void Init_TimeOuts(COMMTIMEOUTS *p_timeouts)
{
	p_timeouts->ReadIntervalTimeout = 10000;
	p_timeouts->ReadTotalTimeoutConstant = 10000;
	p_timeouts->ReadTotalTimeoutMultiplier = 10000;
	//p_timeouts->WriteTotalTimeoutConstant = 
	//p_timeouts->WriteTotalTimeoutMultiplier = 
}

HANDLE connect_com(int num_com_tt)
{
	switch (num_com_tt)
	{
	case 0:
		return CreateFile(TEXT("COM0"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
		break;
	case 1:
		return CreateFile(TEXT("COM1"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
		break;
	case 2:
		return CreateFile(TEXT("COM2"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
		break;
	case 3:
		return CreateFile(TEXT("COM3"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
		break;
	case 4:
		return CreateFile(TEXT("COM4"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
		break;
	case 5:
		return CreateFile(TEXT("COM5"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
		break;
	case 6:
		return CreateFile(TEXT("COM6"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
		break;
	case 7:
		return CreateFile(TEXT("COM7"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
		break;
	case 8:
		return CreateFile(TEXT("COM8"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
		break;
	case 9:
		return CreateFile(TEXT("COM9"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
		break;
	case 10:
		return CreateFile(TEXT("COM10"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
		break;
	case 11:
		return CreateFile(TEXT("COM11"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
		break;
	case 12:
		return CreateFile(TEXT("COM12"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
		break;
	case 13:
		return CreateFile(TEXT("COM13"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
		break;
	case 14:
		return CreateFile(TEXT("COM14"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
		break;
	case 15:
		return CreateFile(TEXT("COM15"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
		break;
	}
}

void Init_send_start_command(PUCHAR p_send_command, PDWORD p_len)
{
	p_send_command[0] = 'S';
	p_send_command[1] = 'S';
	*p_len = 2;
}

void Init_send_fangda_command(PUCHAR p_send_command, PDWORD p_len)//�޸ķŴ���
{
	p_send_command[0] = 0x53;
	p_send_command[1] = 0x54;
	p_send_command[2] = 0x47;
	p_send_command[3] = 0x0;
	p_send_command[4] = 0x0;
	p_send_command[5] = 0x0;
	*p_len = 6;
}

void Init_send_caiyang_command(PUCHAR p_send_command, PDWORD p_len)//�޸Ĳ�����
{
	p_send_command[0] = 0x53;
	p_send_command[1] = 0x54;
	p_send_command[2] = 0x52;
	p_send_command[3] = 0x35;
	p_send_command[4] = 0x45;
	p_send_command[5] = 0x44;
	*p_len = 6;
}


extern "C" MEX_FUNCTION_API void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray*prhs[])
{
	DCB m_dcb;//��Ŵ������õĽṹ��
	COMMTIMEOUTS timeout;//���ó�ʱʱ��

	//�����������
	int num_com = mxGetScalar(prhs[0]);//��ȡ��ȡ���ں�

	DWORD len = 0;//�������ݵĳ���
	PUCHAR p_send_command = new UCHAR[6];//�������ݵ�����



	
	
	HANDLE m_hComm = connect_com(num_com);

	if (m_hComm == (HANDLE)-1)
	{
		mexPrintf("failed to open\n");
		CloseHandle(m_hComm);
		return;
	}
	else
	{
		//mexPrintf("success to open\n");
	}

	GetCommState(m_hComm, &m_dcb);//��ȡԭ���Ĵ��ڵ�����
	Init_DCB(&m_dcb);//��ʼ��DCB�ṹ��
	SetCommState(m_hComm, &m_dcb);

	//���ô��ڵĳ�ʱʱ��
	Init_TimeOuts(&timeout);
	SetCommTimeouts(m_hComm, &timeout);
	
	//���û�������С
	SetupComm(m_hComm, REC_BUFF_SIZE, 1024);//���ֵֻ����65536
	
	Init_send_start_command(p_send_command, &len);
	WriteFile(m_hComm, p_send_command, len, &len, NULL);//���Ϳ�ʼָ��

	Sleep(1000);//��ʱ1��

	Init_send_fangda_command(p_send_command, &len);
	WriteFile(m_hComm, p_send_command, len, &len, NULL);//�޸ķŴ���Ϊ1

	Sleep(1000);//��ʱ1��

	Init_send_caiyang_command(p_send_command, &len);
	WriteFile(m_hComm, p_send_command, len, &len, NULL);//�޸Ĳ�����



	delete[] p_send_command;//�ͷſռ�
	CloseHandle(m_hComm);
	 
}

