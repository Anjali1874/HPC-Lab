#1 Problem Statement 1:Execute the following program and check the properties of your GPGPU.

%%bash
# Save the C code to a file
cat > cuda_info.cu << 'EOF'
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h> // Required for CUDA API calls

int main()
{
    	int deviceCount;
    	cudaError_t err = cudaGetDeviceCount(&deviceCount);
    	if (err != cudaSuccess) {
            fprintf(stderr, "cudaGetDeviceCount failed: %s\n", cudaGetErrorString(err));
            return 1;
        }

    	if (deviceCount == 0)
	{
        	printf("There is no device supporting CUDA\n");
        	return 0; // Exit if no CUDA device
	}

    	int dev;
    	for (dev = 0; dev < deviceCount; ++dev)
	{
        	cudaDeviceProp deviceProp;
        	err = cudaGetDeviceProperties(&deviceProp, dev);
            if (err != cudaSuccess) {
                fprintf(stderr, "cudaGetDeviceProperties failed: %s\n", cudaGetErrorString(err));
                return 1;
            }

        	if (dev == 0)
		{
            		if (deviceProp.major < 1)
                	{
				printf("There is no device supporting CUDA.\n");
			}
            		else if (deviceCount == 1)
			{
                		printf("There is 1 device supporting CUDA\n");
			}
            		else
                	{
				printf("There are %d devices supporting CUDA\n", deviceCount);
			}
        	}
        	printf("\nDevice %d: \"%s\"\n", dev, deviceProp.name);
        	printf("  Major revision number:                         %d\n", deviceProp.major);
        	printf("  Minor revision number:                         %d\n", deviceProp.minor);
        	printf("  Total amount of global memory:                 %lld bytes\n", (long long)deviceProp.totalGlobalMem); // Use long long for memory
        	printf("  Total amount of constant memory:               %d bytes\n", deviceProp.totalConstMem);
        	printf("  Total amount of shared memory per block:       %d bytes\n", deviceProp.sharedMemPerBlock);
        	printf("  Total number of registers available per block: %d\n", deviceProp.regsPerBlock);
        	printf("  Warp size:                                     %d\n", deviceProp.warpSize);
		printf("  Multiprocessor count:                          %d\n",deviceProp.multiProcessorCount );

        	printf("  Maximum number of threads per block:           %d\n", deviceProp.maxThreadsPerBlock);
        	printf("  Maximum sizes of each dimension of a block:    %d x %d x %d\n", deviceProp.maxThreadsDim[0],deviceProp.maxThreadsDim[1], deviceProp.maxThreadsDim[2]);
        	printf("  Maximum sizes of each dimension of a grid:     %d x %d x %d\n", deviceProp.maxGridSize[0], deviceProp.maxGridSize[1],  deviceProp.maxGridSize[2]);
        	printf("  Maximum memory pitch:                          %lld bytes\n", (long long)deviceProp.memPitch); // Use long long for memory
        	printf("  Texture alignment:                             %d bytes\n", deviceProp.textureAlignment);
        	printf("  Clock rate:                                    %d kilohertz\n", deviceProp.clockRate);
    	}
    return 0;
}
EOF

# Compile the CUDA C code
nvcc cuda_info.cu -o cuda_info

# Execute the compiled program
./cuda_info