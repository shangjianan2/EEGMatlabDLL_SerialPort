#include "test.h"
#include <string>
#include "stdlib.h"
#include <iostream>
#include "CyAPI.h"


using namespace std;
extern "C" MEX_FUNCTION_API void mexFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray*prhs[])
{
	
	usb_receive();
	mexPrintf("Done\n"); 
}

//void usb_receive(double x[])
void usb_receive()
{
	CCyUSBDevice *USBDevice = new CCyUSBDevice();
	USBDevice->Open(0);
	if (USBDevice->IsOpen()){
		mexPrintf("USB is open\n");
	}
	else{
		mexPrintf("USB is not open\n");
	}
}