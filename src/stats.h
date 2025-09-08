#pragma once

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

// Status codes for data validation
typedef enum {
    VALID_DATA = 0,     // Valid data
    INVALID_INPUT = -1, // Null pointer or invalid count
    ABSURD_VALUE = 1    // Values outside acceptable range
} DataValidityStatus;

// Statistics structure
struct Stats {
    float average;
    float min;
    float max;
};

// Computes min, max, and average from a float array
struct Stats compute_statistics(const float* numbers, int count);

// Validates input data and checks for absurd values
DataValidityStatus checkValueAbsurdity(const float* numbers, int count);

// Sets all statistics fields to NaN
void setStatisticsToNaN(struct Stats* statistics);

#ifdef __cplusplus
}
#endif