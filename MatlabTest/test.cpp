#include "test.h"
#include <string>
#include "stdlib.h"
#include <iostream>
#include "CyAPI.h"

#define BUFF_LENGTH 3


using namespace std;

void Init_DCB(DCB *p_DCB)
{
	p_DCB->BaudRate = CBR_9600;
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
	}
}


extern "C" MEX_FUNCTION_API void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray*prhs[])
{
	DCB m_dcb;//��Ŵ������õĽṹ��
	COMMTIMEOUTS timeout;//���ó�ʱʱ��

	//�����������
	int num_com = mxGetScalar(prhs[0]);//��ȡ��ȡ���ں�

	DWORD buff_length = 0;
	buff_length = mxGetScalar(prhs[1]);//��ȡ�����ݵĳ���


	//���ָ��
	double *x;
	plhs[0] = mxCreateDoubleMatrix(1, buff_length, mxREAL);
	x = mxGetPr(plhs[0]);
	
	HANDLE m_hComm = connect_com(num_com);

	if (m_hComm == (HANDLE)-1)
	{
		mexPrintf("failed to open\n");
		CloseHandle(m_hComm);
		return;
	}
	else
	{
		mexPrintf("success to open\n");
	}

	GetCommState(m_hComm, &m_dcb);//��ȡԭ���Ĵ��ڵ�����
	Init_DCB(&m_dcb);//��ʼ��DCB�ṹ��
	SetCommState(m_hComm, &m_dcb);

	//���ô��ڵĳ�ʱʱ��
	Init_TimeOuts(&timeout);
	SetCommTimeouts(m_hComm, &timeout);
	
	//��ն�������,׼����ȡ����
	PurgeComm(m_hComm, PURGE_RXCLEAR);

	//ͬ����ȡ���ڻ���������
	DWORD len = buff_length;
	char *p_buff = new char[len];
	Read_From_SerialPort(m_hComm, p_buff, &len);

	for (int i = 0; i < buff_length; i++){
		x[i] = p_buff[i];
	}

	mexPrintf("length: %d\n", len);


	delete[] p_buff;//�ͷſռ�
	CloseHandle(m_hComm);
	 
}

