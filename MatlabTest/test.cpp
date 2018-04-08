#include "test.h"
#include <string>
#include "stdlib.h"
#include <iostream>
#include "CyAPI.h"


using namespace std;

#define SIZE_READ 18432
// #define DUANCENG 18432

void output_ZhenTou(PUCHAR buf_tt, double *x_tt)
{
	int temp_Size = SIZE_READ / 128;
	int temp_Size1 = SIZE_READ - temp_Size;
	for (int i = 0; i < temp_Size; i++){
		x_tt[i] = buf_tt[i * 128 + 4]*65536 + buf_tt[i * 128 + 5]*256 + buf_tt[ i * 128 + 6 ];
		//if (x_tt[i] > 1000)
		//	mexPrintf("Larger Than 1000");
	}
}



extern "C" MEX_FUNCTION_API void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray*prhs[])
{
	CCyUSBDevice *USBDevice = new CCyUSBDevice();
	PUCHAR buf = new UCHAR[SIZE_READ];
	double *x;
	
	
	plhs[0] = mxCreateDoubleMatrix(1, SIZE_READ / 128, mxREAL);
	x = mxGetPr(plhs[0]);


	if (USBDevice->IsOpen()){
		mexPrintf("USB has already been open\n");
	}
	else{
		mexPrintf("USB has not  been open yet\n");
		return;
	}
	LONG len = SIZE_READ;
		
	USBDevice->BulkInEndPt->XferData(buf, len);
#ifdef DUANCENG
	output_ZhenTou(buf, x);
#else
	for (int i = 0; i < SIZE_READ; i++){
		x[i] = buf[i];
	}
#endif
	mexPrintf("Done\n"); 
}

//void usb_receive(double* x)
////void usb_receive()
//{
//	CCyUSBDevice *USBDevice = new CCyUSBDevice();
//	PUCHAR buf = new UCHAR[SIZE_READ];
//	USBDevice->Open(0);
//	if (USBDevice->IsOpen()){
//		LONG len = SIZE_READ;
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