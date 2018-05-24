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


extern "C" MEX_FUNCTION_API void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray*prhs[])
{
	DCB m_dcb;//��Ŵ������õĽṹ��

	double *x;
	plhs[0] = mxCreateDoubleMatrix(1, BUFF_LENGTH, mxREAL);
	x = mxGetPr(plhs[0]);
	
	HANDLE m_hComm = CreateFile(TEXT("COM2"),						// communication port string (COMX)
		GENERIC_READ | GENERIC_WRITE,	// read/write types
		0,								// comm devices must be opened with exclusive access
		NULL,							// no security attributes
		OPEN_EXISTING,					// comm devices must use OPEN_EXISTING
		0,			// Async I/O
		0);							// template must be 0 for comm devices
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

	//��ն�������,׼����ȡ����
	PurgeComm(m_hComm, PURGE_RXCLEAR);

	//ͬ����ȡ���ڻ���������
	DWORD len = BUFF_LENGTH;
	char *p_buff = new char[len];
	Read_From_SerialPort(m_hComm, p_buff, &len);

	for (int i = 0; i < BUFF_LENGTH; i++){
		x[i] = p_buff[i];
	}

	mexPrintf("length: %d\n", len);


	delete[] p_buff;//�ͷſռ�
	CloseHandle(m_hComm);
	 
}

