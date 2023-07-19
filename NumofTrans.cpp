#include "mkl_dfti.h"
#include <iostream>

int main()
{

    struct DFTI_DFT_Desc_struct* forwardFftDescriptor;
    size_t nDim = 1;
    size_t nPoints = 8;
    size_t nSignals = 2;
    size_t signalStride = 2 * nPoints + 2;
    long status;

    // Set up the strides.
    int strides[2]; strides[0] = 0; strides[1] = 1;

    status = DftiCreateDescriptor(&forwardFftDescriptor, DFTI_DOUBLE, DFTI_REAL, nDim, 2 * nPoints);

    // Set up the input output strides.
    status = DftiSetValue(forwardFftDescriptor, DFTI_INPUT_STRIDES, strides);
    status = DftiSetValue(forwardFftDescriptor, DFTI_OUTPUT_STRIDES, strides);

    // Setup the number of transforms.
    status = DftiSetValue(forwardFftDescriptor, DFTI_NUMBER_OF_TRANSFORMS, nSignals);

    // Setup the input output distance.
    status = DftiSetValue(forwardFftDescriptor, DFTI_INPUT_DISTANCE, signalStride);
    status = DftiSetValue(forwardFftDescriptor, DFTI_OUTPUT_DISTANCE, signalStride);

    // Commit the descriptor
    status = DftiCommitDescriptor(forwardFftDescriptor);
    if (!DftiErrorClass(status, DFTI_NO_ERROR))
        return false;   // status return = 3

    return true;

}

