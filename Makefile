UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	BLAS_OPTIONS = -DLINALG_USE_ACCELERATE=1 -DACCELERATE_NEW_LAPACK=1 -DACCELERATE_LAPACK_ILP64=1 -framework Accelerate 
else
	BLAS_OPTIONS = -lblas
endif


all: build_libs test diff

build_libs:
	./build-libs.sh

linalgebra_test_orig: LinAlgebraTest.cpp build_LinAlgebra_orig_Release/libLinAlgebra.a
	$(CXX) -O3 \
		-ILinAlgebra_orig \
		-o $@ $^


linalgebra_test_mjk: LinAlgebraTest.cpp build_LinAlgebra_MJK_Release/libLinAlgebra.a
	$(CXX) -O3 \
		-ILinAlgebra_MJK \
		-o $@ $^ \
		$(BLAS_OPTIONS)


TESTS = dot_prod matmult_C_M_M matmult_M_K matmult_M_M

test: linalgebra_test_orig linalgebra_test_mjk
	@echo "------------------"
	@echo "---  ORIGINAL  ---"
	@echo "------------------"
	./linalgebra_test_orig result_orig_
	
	@echo "------------------"
	@echo "---     MJK    ---"
	@echo "------------------"
	./linalgebra_test_mjk result_mjk_


diff:
	$(foreach test,$(TESTS),@diff result_mjk_$(test) result_orig_$(test) && echo "PASS: result data matches for $(test)" || echo "ERROR: result data mismatch for $(test)")

clean:
	rm -rf  \
		linalgebra_test_orig \
		linalgebra_test_MJK \
		build_LinAlgebra_MJK_Release \
		build_LinAlgebra_orig_Release
