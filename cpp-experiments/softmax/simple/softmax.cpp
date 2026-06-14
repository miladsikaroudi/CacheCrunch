#include "softmax.h"
#include <algorithm>
#include <cmath>

void softmax(const float *input, float *output, int size)
{
    float max_element = *std::max_element(input, input+size);
    float denom = 0.0f;
    for (int i=0; i<size; ++i){
        output[i] = std::exp(input[i]-max_element);
        denom += output[i];
    }
    for (int i=0; i<= size; ++i){
        output[i] /= denom;
    }
}
