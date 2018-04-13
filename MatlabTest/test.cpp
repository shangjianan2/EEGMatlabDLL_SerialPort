#include "test.h"
#include <string>
#include "stdlib.h"
#include <iostream>
#include "CyAPI.h"


using namespace std;


void begin_command(CCyUSBDevice *USBDevice_tt)
{
	UCHAR array_begin[6];
	PUCHAR p_array_begin = array_begin;
	LONG len_begin;
	array_begin[0] = 'T';
	array_begin[1] = 'S';
	array_begin[2] = 219;
	
	array_begin[4] = 182;
	array_begin[5] = 109;
	
	len_begin = 6;

	array_begin[3] = 'G';
	if (USBDevice_tt->BulkOutEndPt->XferData(p_array_begin, len_begin) == true){
		mexPrintf("FangDa is send G\n");
	}
	else{
		mexPrintf("FangDa is not send\n");
	}

	array_begin[3] = 'H';
	if (USBDevice_tt->BulkOutEndPt->XferData(p_array_begin, len_begin) == true){
		mexPrintf("FangDa is send H\n");
	}
	else{
		mexPrintf("FangDa is not send\n");
	}

	array_begin[3] = 'I';
	if (USBDevice_tt->BulkOutEndPt->XferData(p_array_begin, len_begin) == true){
		mexPrintf("FangDa is send I\n");
	}
	else{
		mexPrintf("FangDa is not send\n");
	}

	array_begin[3] = 'J';
	if (USBDevice_tt->BulkOutEndPt->XferData(p_array_begin, len_begin) == true){
		mexPrintf("FangDa is send J\n");
	}
	else{
		mexPrintf("FangDa is not send\n");
	}

	array_begin[3] = 'K';
	if (USBDevice_tt->BulkOutEndPt->XferData(p_array_begin, len_begin) == true){
		mexPrintf("FangDa is send K\n");
	}
	else{
		mexPrintf("FangDa is not send\n");
	}
}

extern "C" MEX_FUNCTION_API void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray*prhs[])
{
	CCyUSBDevice *USBDevice = new CCyUSBDevice();
	//PUCHAR buf = new UCHAR[1024];
	//double *x;
	//
	//
	//plhs[0] = mxCreateDoubleMatrix(1, 1024, mxREAL);
	//x = mxGetPr(plhs[0]);


	//if (USBDevice->IsOpen()){
	//	mexPrintf("USB has already been open\n");
	//}
	//else{
	//	mexPrintf("USB has not  been open yet\n");
	//	USBDevice->Open(0);
		begin_command(USBDevice);
	//}

	//

	//if (USBDevice->IsOpen()){
	//	LONG len = 1024;
	//	
	//	USBDevice->BulkInEndPt->XferData(buf, len);
	//	for (int i = 0; i < 1024; i++){
	//		x[i] = buf[i];
	//	}


	//}
	//else{
	//	mexPrintf("USB is not open\n");
	//}
	//mexPrintf("Done\n"); 
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