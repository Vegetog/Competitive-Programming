#include <stdint.h>
#include <cuda_fp16.h>

__global__ void add(__half* A, const __half* B, int64_t numel) {
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    if (id < numel) {
        A[id] += B[id];
    }
}

extern "C" void run_kernel(__half* A, const __half* B, int64_t numel){
    int threads = 256;
    int blocks = (numel + threads - 1) / threads;
    add<<<blocks, threads>>>(A, B, numel);
}