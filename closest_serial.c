#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "closest_serial.h"

double combine_lr(struct Point P[], size_t n, struct Point mid_point, double d)
{
    int i, j, index = 0;
    struct Point *p_i = malloc(sizeof(struct Point) * n);  // p_i is the name given by dan = =. indicates the points fits the condition.
    double distance;
    for (i = 0; i < n; i++){
        /*if distance is 0 it is mid_point. If distance < d that is a point we are looking for*/
        // printf("abs: %d, d: %f \n", abs(P[i].x - mid_point.x), d);
        if (abs(P[i].x - mid_point.x) < d){
            p_i[index++] = P[i];
        }
    }
    qsort(p_i, index, sizeof(struct Point), compare_y);
    double result = 0.0;

    for (i = 0; i < index; i++){
        for (j = i + 1; j < index; j++){
            if (p_i[j].y - p_i[i].y < d){
                distance = dist(p_i[i], p_i[j]);
                if (result == 0.0 || (distance < result)){
                    result = distance;
                }
            }
        }
    }
    free(p_i);

    if (result > 0)
        return (result > d) ? d : result;
    return d;
}

double _closest_serial(struct Point P[], size_t n)
{
    // using malloc. Too slow.

    // if (n <= 3)
    //     return brute_force(P, n);
    // int p_mid = n / 2;
    // struct Point *half = malloc(sizeof(struct Point) * (p_mid + 1));
    // int i;
    // for (i = 0; i < p_mid; i++)
    //     half[i] = P[i];
    // double dl = _closest_serial(half, p_mid);
    // free(half);
    // struct Point *half2 = malloc(sizeof(struct Point) * (p_mid + 1));
    // for (i = 0; i < (n - p_mid); i++)
    //     half2[i] = P[i + p_mid];
    // double dr = _closest_serial(half2, n - p_mid);
    // free(half2);
    // double d = (dl > dr) ? dr : dl;
    // // printf("pmid  is :%d\n", p_mid);
    // return combine_lr(P, n, P[p_mid], d);

    // ptr, should be faster.

    if (n <= 3)
        return brute_force(P, n);
    int p_mid = n / 2;
    double dl = _closest_serial(P, p_mid);
    double dr = _closest_serial(P + p_mid, n - p_mid);
    // printf("dl: %f dr: %f \n", dl, dr);
    double d = (dl > dr) ? dr : dl;

    return combine_lr(P, n, P[p_mid], d); // the shortest distance in cross the mid line.
}

double closest_serial(struct Point P[], size_t n)
{
    qsort(P, n, sizeof(struct Point), &compare_x);
    double result = _closest_serial(P, n);
    return result;
}
