# MKL-Dfti-NumofTransforms
Example to calculate Forward FFT using MKL DftiComputeForward with DFTI_NUMBER_OF_TRANSFORMS setting

Add MKL library into project in VS:

Add MKL library "include" directory into project property > C/C++ > General > Additional Include Directories
Add MKL library "lib" directory into project property > Linker > General > Additional Library Directories
Add mkl_core_dll.lib, mkl_intel_lp64_dll.lib, and mkl_intel_thread_dll.lib into project property > Linker > Input > Additional Dependencies
