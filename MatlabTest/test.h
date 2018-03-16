#include "matrix.h"
#include "mex.h"


#define TEST_MATLAB_3_EXPORTS
#ifdef TEST_MATLAB_3_EXPORTS
#define MEX_FUNCTION_API __declspec(dllexport)
#else
#define MEX_FUNCTION_API __declspec(dllimport)
#endif
MEX_FUNCTION_API void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]);
//void usb_receive();