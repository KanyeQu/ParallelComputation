# Parallel Computation
Multi-processing based computational geometry problem. The program can calculate the closest pair of points among 10000000 points in 1.69188 seconds (on intel i9-12900k). Written in C



## Usage

To compile:

```bash
make
```



Quick start:

```bash
./closest -g 10000000 -d 7
```

This will calculate the shortest distance between 10000000 points, recursion depth is 7 ( $2^{8} \approx 256$ processes invoke).



Usage:

``` bash
./closest [-g npoints] [-f filename] [-v] -d pdepth
```
    -d - Maximum process tree depth
    -g - Number of points to generate
    -f - File name to read or write points from
    -v - Verbose (print extra debugging info)

Usage of optional parameters:
    When -g and -f are not used, the points are read from the default file %s.\n\n", DEFAULT_FILE);
    When -f is used without -g, the points are read from the specified file.\n\n");
    When -g is used without -f, the specified number of points are generated at runtime but not saved.\n\n");
    When -g and -f are used together, the points are generated at runtime and stored in the specified file.\n\n");



To clean:

```bash
make clean
```





## Performance (i9-12900K)

With some experiment, the best performance of this CPU can be achieved by recursion depth of 7( ```-d 7``` )



Find closest within 10000000($10^7$) points. Finishes in 1691.88ms

```bash
hacker@ubuntu$ ./closest -g 10000000 -d 7
Generating 10000000 random points with x- and y-coordinate range between 0 and 2147483647... Done.
Sorted the points in 1339.02ms.
[Multi-Process] The smallest distance is 144.03 (execution time: 1691.88ms; processes created: 254).
[Single-Process] The smallest distance is 144.03 (execution time: 22214.39ms).
```



Find closest within 20000000($2 \times 10^7$) points. Finishes in 3751.19ms

```bash
hacker@ubuntu$ ./closest -g 20000000 -d 7
Generating 20000000 random points with x- and y-coordinate range between 0 and 2147483647... Done.
Sorted the points in 2793.10ms.
[Multi-Process] The smallest distance is 66.89 (execution time: 3751.19ms; processes created: 254).
[Single-Process] The smallest distance is 66.89 (execution time: 67801.87ms).
```



Goes to $3 \times 10^7$, Finishes in 6698.18ms. Compare to Single-Process, the performance is $\frac{145682.45}{6698.18} \approx $ 21 times better

```bash
hacker@ubuntu$ ./closest -g 30000000 -d 7
Generating 30000000 random points with x- and y-coordinate range between 0 and 2147483647... Done.
Sorted the points in 4303.80ms.
[Multi-Process] The smallest distance is 66.89 (execution time: 6698.18ms; processes created: 254).
[Single-Process] The smallest distance is 66.89 (execution time: 145682.45ms).
```

