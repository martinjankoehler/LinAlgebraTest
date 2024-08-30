#! /bin/bash

for lib in LinAlgebra_orig LinAlgebra_MJK
do
	mkdir -p build_${lib}_Release
	pushd build_${lib}_Release
	cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo ../$lib
	make
	popd
done
