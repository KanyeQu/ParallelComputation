#include <stdlib.h>
#include <stdio.h>
#include "closest_brute.h"

double brute_force(struct Point P[], size_t n) 
{ 
    double result = -1;
    int i, j;
    for (i = 0; i < n; i++){
        for (j = i + 1; j < n; j++){
            if (result == -1 || dist(P[i], P[j]) < result)
                result = dist(P[i], P[j]);
        }
    }  
    if (result == -1){
        perror("brute force");
        exit(1);
    }
    return result; 
} 
