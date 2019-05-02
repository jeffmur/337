// Jeffrey Murray CSS 343 B SP19
// Created: 4/4/19
// Last Modified: 4/6/19

#ifndef POLY_H
#define POLY_H
#include <iostream>
using namespace std;

class Poly {
    friend ostream& operator<< (ostream& output, const Poly& r);
    friend istream& operator>> (istream& input, Poly& r );

private:
    double *coeffPtr;
    int size = 0;

public:
    ~Poly();
    Poly(int co, int exp );
    Poly(int co);
    Poly(Poly& A);
    Poly();
    int getCoeff(int power);
    void setCoeff(int co, int exp);
    void resize(int newSize);
    void fill();
    void integrate();
    Poly operator+(const Poly &) const;
    Poly operator-(const Poly &) const;
    Poly operator*(const Poly &) const;
    Poly& operator=(const Poly &) ;
    Poly& operator+=(const Poly &);
    Poly& operator-=(const Poly &);
    Poly& operator*=(const Poly &);
    bool operator==(const Poly &) const;
    bool operator!=(const Poly &) const;
};
#endif     /* POLY_H */
