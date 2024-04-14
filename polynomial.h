#include <iostream>

#ifndef LAB_4_POLYNOMIAL_H
#define LAB_4_POLYNOMIAL_H

using namespace std;

class Polynomial{
private:
    double *coefficients;
    int size;

public:
    Polynomial();

    Polynomial(const double *coefficients, int size);

    Polynomial(const float *coefficients, int size);

    Polynomial(const int *coefficients, int size);

    Polynomial(Polynomial& other);

    Polynomial(Polynomial&& other) noexcept ;

    double calculate(double x);

    double operator [] (int index) noexcept;

    double at(int index);

    Polynomial operator + (Polynomial& other);

    Polynomial operator + (double other);

    Polynomial operator - (Polynomial& other);

    Polynomial operator - (double other);

    Polynomial operator * (Polynomial& other);

    Polynomial operator * (double other);

    Polynomial operator / (double other);

    Polynomial operator += (Polynomial& other);

    Polynomial operator += (double other);

    Polynomial operator -= (Polynomial& other);

    Polynomial operator -= (double other);

    Polynomial operator *= (Polynomial& other);

    Polynomial operator *= (double other);

    Polynomial operator /= (double other);

    Polynomial operator - ();

    bool operator == (Polynomial& other);

    bool operator >= (Polynomial& other);

    bool operator <= (Polynomial& other);

    bool operator > (Polynomial& other);

    bool operator < (Polynomial& other);

    Polynomial& operator = (Polynomial&& other) noexcept ;

    friend ostream& operator << (ostream& out, Polynomial& polynomial);

    explicit operator string ();

    ~Polynomial();
};

#endif //LAB_4_POLYNOMIAL_H
