#include "stats.h"

#include <stddef.h>
#include <float.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

// Checks for valid input and acceptable value ranges (0-100000)
DataValidityStatus checkValueAbsurdity(const float* numbers, int count) {
    // Check for null pointer, negative count, or overflow
    if (numbers == NULL || count <= 0) {
        return INVALID_INPUT;
    }
    
    // Check for potential integer overflow when calculating memory size
    if (count > (INT_MAX / (int)sizeof(float))) {
        return INVALID_INPUT;
    }

    // Check each value in the array
    for (int i = 0; i < count; i++) {
        // Skip NaN values as they're handled separately
        if (isnan(numbers[i])) {
            continue;
        }
        
        // Check for absurd values
        if (numbers[i] < 0.0f || numbers[i] > 100000.0f) {
            return ABSURD_VALUE;
        }
    }
    
    return VALID_DATA;
}

// Sets all statistics fields to NaN
void setStatisticsToNaN(struct Stats* statistics) {
    if (statistics != NULL) {
        statistics->min = NAN;
        statistics->max = NAN;
        statistics->average = NAN;
    }
}

// Computes min, max, and average from array, ignoring NaN values
struct Stats compute_statistics(const float* numbers, int count) {
    struct Stats stats;
    
    // Initialize with NaN to handle error cases
    setStatisticsToNaN(&stats);
    
    // Validate input data
    DataValidityStatus status = checkValueAbsurdity(numbers, count);
    if (status != VALID_DATA) {
        return stats;
    }

    // Process numbers
    float sum = 0.0f;
    int validValuesCount = 0;
    stats.min = FLT_MAX;
    stats.max = -FLT_MAX;
    
    for (int i = 0; i < count; i++) {
        if (isnan(numbers[i])) {
            continue; // Skip NaN values
        }
        
        validValuesCount++;
        
        // Update min and max
        if (numbers[i] < stats.min) {
            stats.min = numbers[i];
        }
        if (numbers[i] > stats.max) {
            stats.max = numbers[i];
        }
        
        sum += numbers[i];
    }

    // Compute average only if we have valid values
    if (validValuesCount > 0) {
        stats.average = sum / validValuesCount;
    }
    
    return stats;
}