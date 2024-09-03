# Compare LinAlgebra implementations 

The capacitance field solver [FasterCap](https://github.com/ediloren/FasterCap) uses the [LinAlgebra](https://github.com/ediloren/LinAlgebra) library.

The original implementation of the `CLi_Vector` and `CLi_Matrix` headers use regular for-loops for dot product, matrix multiplication, etc.

In this repo I've made some experiments rewriting those using BLAS and compare run times, etc.

## Build instructions

Linux Dependencies:
```bash
sudo apt install libopenblas-dev
```
(on macOS, the system `Accelerate.framework` is used)

Linux and Mac:
```bash
git clone https://github.com/martinjankoehler/LinAlgebraTest --recursive
cd LinAlgebraTest
make
```

## Example test run

Here's the first result on a MacBook Pro M3 with 11 cores, using Apple's Accelerate Framework (which contains BLAS implementations):

| Function                          | FasterCap (Original) | FasterCap (BLAS mods) |
| --------------------------------- | -------------------- | ------------------------- |
| dot_prod(Vector, Vector)          | 126ms                | 39ms                      |
| matmult(Matrix, Matrix)           | 1024ms               | 5ms                       |
| matmult(Matrix, Matrix, Matrix)   | 1021ms               | 5ms                       |
| matmult(Matrix, Vector)           | 1024µs               | 911µs                     |

```
------------------
---  ORIGINAL  ---
------------------
./linalgebra_test_orig
Preparing vectors of size 100000000…

Testing dot_prod(A,B)…
Result: 6.66667e+23
Time difference = 126[ms] || 126334541[ns]

Preparing matrix of size 1000…

Testing matrix multiplication: matmult(M, M)…
Result: 9.98500e+08, 5.48950e+09, 8.98251e+09
Time difference = 1024[ms] || 1024715583[ns]

Testing matrix multiplication matmult(C, M, M)…
Result: 9.98500e+08, 5.48950e+09, 8.98251e+09
Time difference = 1012[ms] || 1012083875[ns]

Testing matrix/vector matmult(M, k)…
Result: 9.98500e+08, 1.4975e+09
Time difference = 1[ms] || 1013500[ns]

Testing frobenius norm Fnorm(M)…
Result: 2.19666e+06
Time difference = 1[ms] || 1079416[ns]

Testing frobenius norm Fnorm(M)…
Result: 3.10655e+06
Time difference = 0[ms] || 754584[ns]

------------------
---     MJK    ---
------------------
./linalgebra_test_MJK
Preparing vectors of size 100000000…

Testing dot_prod(A,B)…
Result: 6.66667e+23
Time difference = 39[ms] || 39921375[ns]

Preparing matrix of size 1000…

Testing matrix multiplication: matmult(M, M)…
Result: 9.98500e+08, 5.48950e+09, 8.98251e+09
Time difference = 5[ms] || 5914375[ns]

Testing matrix multiplication matmult(C, M, M)…
Result: 9.98500e+08, 5.48950e+09, 8.98251e+09
Time difference = 5[ms] || 5412958[ns]

Testing matrix/vector matmult(M, k)…
Result: 9.98500e+08, 1.4975e+09
Time difference = 0[ms] || 91125[ns]

Testing frobenius norm Fnorm(M)…
Result: 2.19666e+06
Time difference = 1[ms] || 1109417[ns]

Testing frobenius norm Fnorm(M)…
Result: 3.10655e+06
Time difference = 0[ms] || 774708[ns]
```
