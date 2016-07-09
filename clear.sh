make clean 2>/dev/null
find . -name "CMakeFiles" | xargs rm -Rf
find . -name "CMakeCache*" | xargs rm
find . -name "Makefile*" | xargs rm
find . -name "cmake_install*" | xargs rm
find . -name "*.so*" | xargs rm 
find . -name "lib" | xargs rmdir 
