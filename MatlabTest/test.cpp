#include "test.h"
#include <string>
#include "stdlib.h"
#include <iostream>
#include "CyAPI.h"


using namespace std;


//void begin_command(CCyUSBDevice *USBDevice_tt)
//{
//	UCHAR array_begin[2];
//	PUCHAR p_array_begin = array_begin;
//	LONG len_begin;
//	array_begin[0] = 'S';
//	array_begin[1] = 'S';
//	len_begin = 2;
//	if (USBDevice_tt->BulkOutEndPt->XferData(p_array_begin, len_begin) == true){
//		mexPrintf("begin is send\n");
//	}
//	else{
//		mexPrintf("begin is not send\n");
//	}
//}

#define SIZE_READ 16384

extern "C" MEX_FUNCTION_API void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray*prhs[])
{
	CCyUSBDevice *USBDevice = new CCyUSBDevice();
	PUCHAR buf = new UCHAR[SIZE_READ];
	double *x;
	
	
	plhs[0] = mxCreateDoubleMatrix(1, SIZE_READ, mxREAL);
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
	for (int i = 0; i < SIZE_READ; i++){
		x[i] = buf[i];
	}
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