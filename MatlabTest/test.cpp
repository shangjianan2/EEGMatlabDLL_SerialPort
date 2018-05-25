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
	DCB m_dcb;//存放串口配置的结构体
	COMMTIMEOUTS timeout;//设置超时时间

	//解析输入参数
	int num_com = mxGetScalar(prhs[0]);//获取获取串口号

	DWORD buff_length = 0;
	buff_length = mxGetScalar(prhs[1]);//获取读数据的长度


	//输出指针
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

	GetCommState(m_hComm, &m_dcb);//获取原本的串口的配置
	Init_DCB(&m_dcb);//初始化DCB结构体
	SetCommState(m_hComm, &m_dcb);

	//设置串口的超时时间
	Init_TimeOuts(&timeout);
	SetCommTimeouts(m_hComm, &timeout);
	
	//清空读缓冲区,准备读取数据
	PurgeComm(m_hComm, PURGE_RXCLEAR);

	//同步读取串口缓冲区数据
	DWORD len = buff_length;
	char *p_buff = new char[len];
	Read_From_SerialPort(m_hComm, p_buff, &len);

	for (int i = 0; i < buff_length; i++){
		x[i] = p_buff[i];
	}

	mexPrintf("length: %d\n", len);


	delete[] p_buff;//释放空间
	CloseHandle(m_hComm);
	 
}

