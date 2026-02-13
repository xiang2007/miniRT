# Code Citations

## License: unknown
https://github.com/brunozampirom/ppd-trabalho-cuda/blob/e3884f8af25cca6a02c2a7650e975e8cf4cd1fb3/paralelo.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
```


## License: unknown
https://github.com/AndreyBychkov/gpu-research/blob/cb0755d92abaf2b45e4123c115b7f378ed431ad8/cpp-cuda/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++)
```


## License: unknown
https://github.com/brunozampirom/ppd-trabalho-cuda/blob/e3884f8af25cca6a02c2a7650e975e8cf4cd1fb3/paralelo.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
```


## License: unknown
https://github.com/AndreyBychkov/gpu-research/blob/cb0755d92abaf2b45e4123c115b7f378ed431ad8/cpp-cuda/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++)
```


## License: unknown
https://github.com/VadVergasov/ACS/blob/8e2d846d1697e363bea7347c1d927f760c7b085f/Project/Project/MatrixMultiply/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++) {
            sum += A[row
```


## License: unknown
https://github.com/brunozampirom/ppd-trabalho-cuda/blob/e3884f8af25cca6a02c2a7650e975e8cf4cd1fb3/paralelo.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
```


## License: unknown
https://github.com/AndreyBychkov/gpu-research/blob/cb0755d92abaf2b45e4123c115b7f378ed431ad8/cpp-cuda/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++)
```


## License: unknown
https://github.com/VadVergasov/ACS/blob/8e2d846d1697e363bea7347c1d927f760c7b085f/Project/Project/MatrixMultiply/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++) {
            sum += A[row
```


## License: unknown
https://github.com/brunozampirom/ppd-trabalho-cuda/blob/e3884f8af25cca6a02c2a7650e975e8cf4cd1fb3/paralelo.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
```


## License: unknown
https://github.com/AndreyBychkov/gpu-research/blob/cb0755d92abaf2b45e4123c115b7f378ed431ad8/cpp-cuda/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++)
```


## License: unknown
https://github.com/VadVergasov/ACS/blob/8e2d846d1697e363bea7347c1d927f760c7b085f/Project/Project/MatrixMultiply/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++) {
            sum += A[row
```


## License: unknown
https://github.com/brunozampirom/ppd-trabalho-cuda/blob/e3884f8af25cca6a02c2a7650e975e8cf4cd1fb3/paralelo.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
```


## License: unknown
https://github.com/AndreyBychkov/gpu-research/blob/cb0755d92abaf2b45e4123c115b7f378ed431ad8/cpp-cuda/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++)
```


## License: unknown
https://github.com/VadVergasov/ACS/blob/8e2d846d1697e363bea7347c1d927f760c7b085f/Project/Project/MatrixMultiply/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++) {
            sum += A[row
```


## License: unknown
https://github.com/brunozampirom/ppd-trabalho-cuda/blob/e3884f8af25cca6a02c2a7650e975e8cf4cd1fb3/paralelo.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
```


## License: unknown
https://github.com/AndreyBychkov/gpu-research/blob/cb0755d92abaf2b45e4123c115b7f378ed431ad8/cpp-cuda/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++)
```


## License: unknown
https://github.com/VadVergasov/ACS/blob/8e2d846d1697e363bea7347c1d927f760c7b085f/Project/Project/MatrixMultiply/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++) {
            sum += A[row
```


## License: unknown
https://github.com/brunozampirom/ppd-trabalho-cuda/blob/e3884f8af25cca6a02c2a7650e975e8cf4cd1fb3/paralelo.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
```


## License: unknown
https://github.com/AndreyBychkov/gpu-research/blob/cb0755d92abaf2b45e4123c115b7f378ed431ad8/cpp-cuda/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++)
```


## License: unknown
https://github.com/VadVergasov/ACS/blob/8e2d846d1697e363bea7347c1d927f760c7b085f/Project/Project/MatrixMultiply/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++) {
            sum += A[row
```


## License: unknown
https://github.com/brunozampirom/ppd-trabalho-cuda/blob/e3884f8af25cca6a02c2a7650e975e8cf4cd1fb3/paralelo.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
```


## License: unknown
https://github.com/AndreyBychkov/gpu-research/blob/cb0755d92abaf2b45e4123c115b7f378ed431ad8/cpp-cuda/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++)
```


## License: unknown
https://github.com/VadVergasov/ACS/blob/8e2d846d1697e363bea7347c1d927f760c7b085f/Project/Project/MatrixMultiply/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++) {
            sum += A[row
```


## License: unknown
https://github.com/brunozampirom/ppd-trabalho-cuda/blob/e3884f8af25cca6a02c2a7650e975e8cf4cd1fb3/paralelo.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++)
```


## License: unknown
https://github.com/AndreyBychkov/gpu-research/blob/cb0755d92abaf2b45e4123c115b7f378ed431ad8/cpp-cuda/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++)
```


## License: unknown
https://github.com/VadVergasov/ACS/blob/8e2d846d1697e363bea7347c1d927f760c7b085f/Project/Project/MatrixMultiply/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++) {
            sum += A[row
```


## License: unknown
https://github.com/brunozampirom/ppd-trabalho-cuda/blob/e3884f8af25cca6a02c2a7650e975e8cf4cd1fb3/paralelo.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++)
```


## License: unknown
https://github.com/AndreyBychkov/gpu-research/blob/cb0755d92abaf2b45e4123c115b7f378ed431ad8/cpp-cuda/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++)
```


## License: unknown
https://github.com/VadVergasov/ACS/blob/8e2d846d1697e363bea7347c1d927f760c7b085f/Project/Project/MatrixMultiply/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++) {
            sum += A[row
```


## License: unknown
https://github.com/brunozampirom/ppd-trabalho-cuda/blob/e3884f8af25cca6a02c2a7650e975e8cf4cd1fb3/paralelo.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++) {
            sum += A[row
```


## License: unknown
https://github.com/AndreyBychkov/gpu-research/blob/cb0755d92abaf2b45e4123c115b7f378ed431ad8/cpp-cuda/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++) {
            sum += A[row
```


## License: unknown
https://github.com/VadVergasov/ACS/blob/8e2d846d1697e363bea7347c1d927f760c7b085f/Project/Project/MatrixMultiply/kernel.cu

```
Here's a complete CUDA matrix multiplication example with different optimization levels:

## Basic Matrix Multiplication (Naive)

```cuda
#include <stdio.h>
#include <cuda_runtime.h>

// Naive kernel: each thread computes one element
__global__ void matmul_naive(float *A, float *B, float *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++) {
            sum += A[row
```

