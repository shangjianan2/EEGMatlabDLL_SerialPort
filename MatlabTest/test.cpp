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

extern "C" MEX_FUNCTION_API void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray*prhs[])
{
	CCyUSBDevice *USBDevice = new CCyUSBDevice();
	PUCHAR buf = new UCHAR[1024];
	double *x;
	
	
	plhs[0] = mxCreateDoubleMatrix(1, 1024, mxREAL);
	x = mxGetPr(plhs[0]);


	if (USBDevice->IsOpen()){
		mexPrintf("USB has already been open\n");
	}
	else{
		mexPrintf("USB has not  been open yet\n");
		return;
	}
	LONG len = 1024;
		
	USBDevice->BulkInEndPt->XferData(buf, len);
	for (int i = 0; i < 1024; i++){
		x[i] = buf[i];
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