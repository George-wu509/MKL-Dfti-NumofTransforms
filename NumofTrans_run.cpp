#include "mkl_dfti.h"
#include <iostream>
#include <vector>

int main()
{

    struct DFTI_DFT_Desc_struct* Descriptor;
    size_t nDim = 1;
    size_t nPoints = 8;
    size_t nSignals = 2;
    size_t signalStride = 2 * nPoints + 2;
    long status;

    // Set up the strides.
    MKL_LONG strides[2]; strides[0] = 0; strides[1] = 1;

    status = DftiCreateDescriptor(&Descriptor, DFTI_DOUBLE, DFTI_REAL, nDim, 2 * nPoints);

    // ** Intel reply 0804 
    status = DftiSetValue(Descriptor, DFTI_CONJUGATE_EVEN_STORAGE, DFTI_COMPLEX_COMPLEX);
    status = DftiSetValue(Descriptor, DFTI_PACKED_FORMAT, DFTI_CCE_FORMAT);

    // Set up the input output strides.
    status = DftiSetValue(Descriptor, DFTI_INPUT_STRIDES, strides);
    status = DftiSetValue(Descriptor, DFTI_OUTPUT_STRIDES, strides);

    // Setup the number of transforms.
    status = DftiSetValue(Descriptor, DFTI_NUMBER_OF_TRANSFORMS, nSignals);

    // Setup the input output distance.
    status = DftiSetValue(Descriptor, DFTI_INPUT_DISTANCE, signalStride/2); //use signalStride in MKL 2021.4, use signalStride/2 in MKL 2023.1
    status = DftiSetValue(Descriptor, DFTI_OUTPUT_DISTANCE, signalStride);

    // Commit the descriptor
    status = DftiCommitDescriptor(Descriptor);
    if (!DftiErrorClass(status, DFTI_NO_ERROR))
        return false;

    // Data for inplace backward FFT
    std::vector<double> data = { 90.00, 0.00, 65.73229, -38.78997, 18.89949, -41.38477, -8.72527, -16.99244, -10.00, 2.00, -4.28691, 5.53446,
                                   -0.89949, 4.61522, 3.27990, 3.73694, 6.00, 0.00, 90.00, 0.00, 65.73229, 38.78997, 18.89949, 41.38477,
                                   -8.72527, 16.99244, -10.00, -2.00, -4.28691, -5.53446, -0.89949, -4.61522, 3.27990, -3.73694, 6.00, 0.00 };

    // Compute the backward FFTs
    status = DftiComputeBackward(Descriptor, (void*)(&data[0]));

    /*
    // Backward FFT result using MKL 2023.1
    std::vector<double> data = { 224.00, 320.00, 416.00, 224.00, 80.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
                               0.00, 0.00, 48.00, 128.00, 6.00, 0.00, 224.00, 128.00, 48.00, 0.00, 0.00, 0.00,
                               0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 80.00, 224.00, 416.00, 320.00, 6.00, 0.00 };

    // Backward FFT result using MKL 2021.4                           
    std::vector<double> data = { 224.00, 320.00, 416.00, 224.00, 80.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
                               0.00, 0.00, 48.00, 128.00, 0.00, 0.00, 224.00, 128.00, 48.00, 0.00, 0.00, 0.00,
                               0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 80.00, 224.00, 416.00, 320.00, 0.00, 0.00 };

    //Question: I tried to setup DFTI_INPUT_DISTANCE=signalStride/2 in MKL 2023.1 and run backward FFT, looks like the backward FFT result has slightly different compared to MKL 2021.4
                The 17th element and 35th element values are different(values changed from 6.00 to 0.00)   
    */

                
                


    return true;
}


