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
	p_DCB->Parity = NOPARITY;//失能校验位
	p_DCB->StopBits = ONESTOPBIT;//一位停止位
	p_DCB->ByteSize = 8;//数据为8位
}

void Read_From_SerialPort(HANDLE handle_tt, char *buff, DWORD *length)//不知道这里句柄的传参是否能够成功
{
	DWORD temp_length = *length;
	ReadFile(handle_tt, buff, temp_length, length, NULL);
}


extern "C" MEX_FUNCTION_API void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray*prhs[])
{
	DCB m_dcb;//存放串口配置的结构体

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

	GetCommState(m_hComm, &m_dcb);//获取原本的串口的配置
	Init_DCB(&m_dcb);//初始化DCB结构体
	SetCommState(m_hComm, &m_dcb);

	//清空读缓冲区,准备读取数据
	PurgeComm(m_hComm, PURGE_RXCLEAR);

	//同步读取串口缓冲区数据
	DWORD len = BUFF_LENGTH;
	char *p_buff = new char[len];
	Read_From_SerialPort(m_hComm, p_buff, &len);

	for (int i = 0; i < BUFF_LENGTH; i++){
		x[i] = p_buff[i];
	}

	mexPrintf("length: %d\n", len);


	delete[] p_buff;//释放空间
	CloseHandle(m_hComm);
	 
}

