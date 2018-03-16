#include "test.h"
#include <string>
#include "stdlib.h"
#include <iostream>
#include "CyAPI.h"


using namespace std;
extern "C" MEX_FUNCTION_API void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray*prhs[])
{
	CCyUSBDevice *USBDevice = new CCyUSBDevice();
	PUCHAR buf = new UCHAR[1024];
	double *x;
	plhs[0] = mxCreateDoubleMatrix(1, 1024, mxREAL);
	x = mxGetPr(plhs[0]);
	USBDevice->Open(0);
	if (USBDevice->IsOpen()){
		LONG len = 1024;
		USBDevice->BulkInEndPt->XferData(buf, len);
		mexPrintf("USB is open\n");
		for (int i = 0; i < 1024; i++){
			x[i] = buf[i];
		}


	}
	else{
		mexPrintf("USB is not open\n");
	}
	mexPrintf("Done\n"); 
}

//void usb_receive(double* x)
////void usb_receive()
//{
//	CCyUSBDevice *USBDevice = new CCyUSBDevice();
//	PUCHAR buf = new UCHAR[1024];
//	USBDevice->Open(0);
//	if (USBDevice->IsOpen()){
//		LONG len = 1024;
//		USBDevice->BulkInEndPt->XferData(buf, len);
//		mexPrintf("USB is open\n");
//		x = buf
//		
//		
//	}
//	else{
//		mexPrintf("USB is not open\n");
//	}
//}