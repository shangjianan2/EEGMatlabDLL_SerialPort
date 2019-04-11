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

void Init_send_fangda_command(PUCHAR p_send_command, PDWORD p_len)//修改放大倍数
{
	p_send_command[0] = 0x53;
	p_send_command[1] = 0x54;
	p_send_command[2] = 0x47;
	p_send_command[3] = 0x0;
	p_send_command[4] = 0x0;
	p_send_command[5] = 0x0;
	*p_len = 6;
}

void Init_send_caiyang_command(PUCHAR p_send_command, PDWORD p_len)//修改采样率
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
	DCB m_dcb;//存放串口配置的结构体
	COMMTIMEOUTS timeout;//设置超时时间

	//解析输入参数
	int num_com = mxGetScalar(prhs[0]);//获取获取串口号

	DWORD len = 0;//发送数据的长度
	PUCHAR p_send_command = new UCHAR[6];//发送数据的数组



	
	
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

	GetCommState(m_hComm, &m_dcb);//获取原本的串口的配置
	Init_DCB(&m_dcb);//初始化DCB结构体
	SetCommState(m_hComm, &m_dcb);

	//设置串口的超时时间
	Init_TimeOuts(&timeout);
	SetCommTimeouts(m_hComm, &timeout);
	
	//设置缓冲区大小
	SetupComm(m_hComm, REC_BUFF_SIZE, 1024);//最大值只能是65536
	
	Init_send_start_command(p_send_command, &len);
	WriteFile(m_hComm, p_send_command, len, &len, NULL);//发送开始指令

	Sleep(1000);//延时1秒

	Init_send_fangda_command(p_send_command, &len);
	WriteFile(m_hComm, p_send_command, len, &len, NULL);//修改放大倍数为1

	Sleep(1000);//延时1秒

	Init_send_caiyang_command(p_send_command, &len);
	WriteFile(m_hComm, p_send_command, len, &len, NULL);//修改采样率



	delete[] p_send_command;//释放空间
	CloseHandle(m_hComm);
	 
}

