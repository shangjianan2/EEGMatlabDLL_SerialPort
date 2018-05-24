#include "test.h"
#include <string>
#include "stdlib.h"
#include <iostream>
#include "CyAPI.h"


using namespace std;
extern "C" MEX_FUNCTION_API void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray*prhs[])
{
	HANDLE m_hComm = CreateFile(TEXT("COM2"),						// communication port string (COMX)
		GENERIC_READ | GENERIC_WRITE,	// read/write types
		0,								// comm devices must be opened with exclusive access
		NULL,							// no security attributes
		OPEN_EXISTING,					// comm devices must use OPEN_EXISTING
		FILE_FLAG_OVERLAPPED,			// Async I/O
		0);							// template must be 0 for comm devices
	if (m_hComm == (HANDLE)-1)
	{
		mexPrintf("failed to open\n");
	}
	else
	{
		mexPrintf("success to open\n");
	}

	CloseHandle(m_hComm);
	 
}