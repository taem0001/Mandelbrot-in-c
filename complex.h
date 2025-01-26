#ifndef COMPLEX_H
#define COMPLEX_H

struct Complex {
    double re;
    double im;
};

struct Complex multiply(struct Complex z0, struct Complex z1);
struct Complex add(struct Complex z0, struct Complex z1);
double square(struct Complex z);

#endif