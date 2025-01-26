#include "complex.h"
#include <math.h>

struct Complex multiply(struct Complex z0, struct Complex z1)
{
    struct Complex result;
    result.re = z0.re * z1.re - z0.im * z1.im;
    result.im = z0.re * z1.im + z1.re * z0.im;
    return result;
}

struct Complex add(struct Complex z0, struct Complex z1)
{
    struct Complex result;
    result.re = z0.re + z1.re;
    result.im = z0.im + z1.im;
    return result;
}

double square(struct Complex z)
{
    return z.re * z.re + z.im * z.im;
}
