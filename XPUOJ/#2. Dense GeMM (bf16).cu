#include <stdint.h>
#include <cuda_bf16.h>

__global__ void GEMM(
    const __nv_bfloat16* A,
    const __nv_bfloat16* B,
    __nv_bfloat16* C,
    int64_t M,
    int64_t N,
    int64_t K
) 
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < M && col < N) {
        float sum = 0.0f;
        for (int i = 0; i < K; ++i) {
            sum += __bfloat162float(A[(size_t)row * K + i]) *
                   __bfloat162float(B[(size_t)col * K + i]);
        }
        C[(size_t)row * N + col] = __float2bfloat16(sum);
    }
}

extern "C" void run_kernel(
    const __nv_bfloat16* A,
    const __nv_bfloat16* B,
    __nv_bfloat16* C,
    int64_t M,
    int64_t N,
    int64_t K
) {
    dim3 threads(32, 8);
    dim3 blocks((N + threads.x - 1) / threads.x, (M + threads.y - 1) / threads.y);
    GEMM<<<blocks, threads>>>(A, B, C, M, N, K);
}