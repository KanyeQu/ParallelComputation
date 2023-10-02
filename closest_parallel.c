#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "closest_parallel.h"

int curr_depth = 0;

double _closest_parallel(struct Point P[], size_t n, int pdmax, int *pcount)
{
    static int num_forks = 0;
    if (pdmax == 0 || n <= 3)
        return closest_serial(P, n);
    // int i;
    int mid_index = n / 2;
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    int f1 = fork();
    if (f1 < 0){
        perror("fork1");
        exit(1);
    }
    else if (f1 == 0){
        close(fd1[0]);
        // struct Point *half3 = malloc(sizeof(struct Point) * (mid_index + 1));
        // for (i = 0; i < mid_index; i++)
        //     half3[i] = P[i];
        // double dl = _closest_parallel(half3, mid_index, pdmax - 1, pcount);
        double dl = _closest_parallel(P, mid_index, pdmax - 1, pcount);
        if(write(fd1[1], &dl, sizeof(double)) == -1){
            perror("write1 error");
            exit(1);
        }
        // free(half3);
        close(fd1[1]);
        // printf("%d \n", num_forks);
        exit(num_forks);
    }
    close(fd1[1]);

    int f2 = fork();
    if (f2 < 0){
        perror("fork2");
        exit(1);
    }
    else if(f2 == 0){
        close(fd2[0]);
        // struct Point *half4 = malloc(sizeof(struct Point) * (mid_index + 1));
        // for (i = 0; i < (n - mid_index); i++)
        //     half4[i] = P[i + mid_index];
        // double dr = _closest_parallel(half4, n - mid_index, pdmax - 1, pcount);
        double dr = _closest_parallel(&P[mid_index], n - mid_index, pdmax - 1, pcount);
        // free(half4);
        if(write(fd2[1], &dr, sizeof(double)) == -1){
            perror("write1 error");
            exit(1);
        }
        close(fd2[1]);
        exit(num_forks);
    }
    close(fd2[1]);

    int status1 = 0, status2 = 0;
    wait(&status1);
    wait(&status2);
    num_forks += 2;
    // printf("in parent %d, %d \n", WEXITSTATUS(status1), WEXITSTATUS(status2));
    num_forks += WEXITSTATUS(status1);
    num_forks += WEXITSTATUS(status2);
    
    double l, r;
    if (read(fd1[0], &l, sizeof(double)) == -1|| read(fd2[0], &r, sizeof(double)) == -1){
        perror("read from parent error");
        exit(1);
    }
    close(fd1[0]);
    close(fd2[0]);
    double d = (l > r) ? r : l;

    *pcount = num_forks;
    return combine_lr(P, n, P[mid_index], d);
}

double closest_parallel(struct Point P[], size_t n, int pdmax, int *pcount)
{
    qsort(P, n, sizeof(struct Point), compare_x);
    double result = _closest_parallel(P, n, pdmax, pcount);
    return result;
}
