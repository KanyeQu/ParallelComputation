#include <math.h>
#include "closest_helpers.h"

int verbose = 0;

int compare_x(const void* a, const void* b) 
{
    struct Point* aptr = (struct Point*)a;
    struct Point* bptr = (struct Point*)b;
    return aptr->x - bptr->x;
} 

int compare_y(const void* a, const void* b) 
{ 
    struct Point* aptr = (struct Point*)a;
    struct Point* bptr = (struct Point*)b;
    return aptr->y - bptr->y;
} 

double dist(struct Point p1, struct Point p2) 
{
    long x = pow(p1.x - p2.x, 2);
    long y = pow(p1.y - p2.y, 2);
    return (double)pow(x + y, 0.5);
} 
