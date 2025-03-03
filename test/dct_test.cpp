#include "mdsp.h"
#include <iostream>
#include <cmath>

#define N 64

int main(int argc,char *argv[])
{
    FLOATTYPE x[N];
    FLOATTYPE y[N];
    FLOATTYPE z[N];

    for(int i = 0; i < N; i++)
    {
        x[i] = 1.0 + cos(2 * PI * i / N * 1) + sin(2 * PI * i / N * 16);
    }

    dct(x, y, N);
    idct(y, z, N);

    for(int i = 0; i < N; i++)
    {
        std::cout << x[i] << "," << y[i] << ',' << z[i] << std::endl;
    }

    return 0;
}