#include <chrono>
#include <iostream>
#include <vector>

#include "Vect.h"
#include "Mtx.h"

//------------------------------------------------------------------



//------------------------------------------------------------------

void log(const std::chrono::steady_clock::time_point &begin,
         const std::chrono::steady_clock::time_point &end)
{
    //    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    //    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
    std::cout << "Time difference = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]"
              << " || "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "[ns]"
              << std::endl << std::endl;
}

void test_vector() {
    const size_t N = 100000000;
    
    std::cout << "Preparing vectors of size " << N << "…" << std::endl << std::endl;
    
    std::vector<double> a, b;
    a.resize(N);
    b.resize(N);
    for (size_t i=0; i < N; i++) {
        a[i] = 1.0 * i;
        b[i] = 2.0 * i;
    }
    
    {
        std::cout << "Testing dot_prod(A,B)…" << std::endl;
        
        CLin_Vector A(N, a.data());
        CLin_Vector B(N, b.data());
        
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        double result = dot_prod(A, B);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Result: " << result << std::endl;
        log(begin, end);
    }
    
    // NOTE: those did not profit from BLAS...
    
    //    {
    //        std::cout << "Testing A*B…" << std::endl;
    //
    //        CLin_Vector A(N, a.data());
    //        CLin_Vector B(N, b.data());
    //
    //        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    //        CLin_Vector C = A * B;
    //        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    //        std::cout << "Result: mod(C)=" << mod(C) << std::endl;
    //        log(begin, end);
    //    }
    //
    //    {
    //        std::cout << "Testing A*11.0…" << std::endl;
    //
    //        CLin_Vector A(N, a.data());
    //        CLin_Vector B(N, b.data());
    //
    //        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    //        CLin_Vector C = A * 11.0;
    //        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    //        std::cout << "Result: mod(C)=" << mod(C) << std::endl;
    //        log(begin, end);
    //    }
    //
    //    {
    //        std::cout << "Testing 11.0*A…" << std::endl;
    //
    //        CLin_Vector A(N, a.data());
    //        CLin_Vector B(N, b.data());
    //
    //        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    //        CLin_Vector C = 11.0 * A;
    //        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    //        std::cout << "Result: mod(C)=" << mod(C) << std::endl;
    //        log(begin, end);
    //    }
    //
    //    {
    //        std::cout << "Testing A/11.0…" << std::endl;
    //
    //        CLin_Vector A(N, a.data());
    //        CLin_Vector B(N, b.data());
    //
    //        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    //        CLin_Vector C = A / 11.0;
    //        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    //        std::cout << "Result: mod(C)=" << mod(C) << std::endl;
    //        log(begin, end);
    //    }
    //
    //
    //    {
    //        std::cout << "Testing A+B…" << std::endl;
    //
    //        CLin_Vector A(N, a.data());
    //        CLin_Vector B(N, b.data());
    //
    //        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    //        CLin_Vector C = A + B;
    //        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    //        std::cout << "Result: mod(C)=" << mod(C) << std::endl;
    //        log(begin, end);
    //    }
    //
    //    {
    //        std::cout << "Testing A-B…" << std::endl;
    //
    //        CLin_Vector A(N, a.data());
    //        CLin_Vector B(N, b.data());
    //
    //        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    //        CLin_Vector C = A - B;
    //        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    //        std::cout << "Result: mod(C)=" << mod(C) << std::endl;
    //        log(begin, end);
    //    }
}

void test_matrix() {
    const size_t N = 1000;
    std::cout << "Preparing matrix of size " << N << "…" << std::endl << std::endl;

    CLin_Matrix M(N, N, 0.0);
    for (size_t i=0; i < N; i++) {
        for (size_t j=0; j < N; j++) {
            M[i][j] = 1.0 * i + 3.0 * j;
        }
    }
    
    CLin_Vector K(N);
    for (size_t i=0; i < N; i++) {
        K[i] = 1.0 * i;
    }
    
    {
        std::cout << "Testing matrix multiplication: matmult(M, M)…" << std::endl;
        
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        CLin_Matrix C = matmult(M, M);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Result: " << C[0][0] << ", " << C[0][N-1] << ", " << C[N-1][N-1] << std::endl;
        log(begin, end);
        
        std::cout << "Testing matrix multiplication matmult(C, M, M)…" << std::endl;
        
        begin = std::chrono::steady_clock::now();
        matmult(C, M, M);
        end = std::chrono::steady_clock::now();
        std::cout << "Result: " << C[0][0] << ", " << C[0][N-1] << ", " << C[N-1][N-1] << std::endl;
        log(begin, end);

    }

    {
        std::cout << "Testing matrix/vector matmult(M, k)…" << std::endl;
        
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        CLin_Vector C = matmult(M, K);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Result: " << C[0] << ", " << C[N-1] << std::endl;
        log(begin, end);
    }

    {
        std::cout << "Testing frobenius norm Fnorm(M)…" << std::endl;
        
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        double result = FNorm(M);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Result: " << result << std::endl;
        log(begin, end);
    }
    
    {
        std::cout << "Testing frobenius norm Fnorm(M)…" << std::endl;
        
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        double result = FNorm(M, M);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Result: " << result << std::endl;
        log(begin, end);
    }
}

int main(int argc, char **argv) {
    test_vector();
    test_matrix();
    
    return 0;
}

