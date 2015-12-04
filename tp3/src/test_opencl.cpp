#include <iostream>
#include <vector>

// OpenCL
#ifdef __APPLE__
    #include "OpenCL/opencl.h"
#else
    #include "CL/cl.h"
#endif

using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char** arg) {
	cl_uint platform_count = 0;
	clGetPlatformIDs (0, nullptr, &platform_count);

	std::vector<cl_platform_id> platform_id (platform_count);
	clGetPlatformIDs (platform_count, platform_id.data(), nullptr);

    cout << "There is " << platform_count << " platforms accessible." << endl;
	
	return 0;
}

