#include <iostream>

#ifndef LAB_4_POLYNOMIAL_H
#define LAB_4_POLYNOMIAL_H

using namespace std;

template <typename T>
class Polynomial{
private:
    T *coefficients;
    int size;

public:
    Polynomial();

    Polynomial(T *coefficients, int size);

    Polynomial(Polynomial& other);

    Polynomial(Polynomial&& other) noexcept ;

    T calculate(T x);

    T operator [] (int index) noexcept;

    T at(int index);

    Polynomial operator + (Polynomial& other);

    Polynomial operator + (T other);

    Polynomial operator - (Polynomial& other);

    Polynomial operator - (T other);

    Polynomial operator * (Polynomial& other);

    Polynomial operator * (T other);

    Polynomial operator / (T other);

    Polynomial operator += (Polynomial& other);

    Polynomial operator += (T other);

    Polynomial operator -= (Polynomial& other);

    Polynomial operator -= (T other);

    Polynomial operator *= (Polynomial& other);

    Polynomial operator *= (T other);

    Polynomial operator /= (T other);

    Polynomial operator - ();

    Polynomial operator == (Polynomial& other);

    Polynomial operator >= (Polynomial& other);

    Polynomial operator <= (Polynomial& other);

    Polynomial operator > (Polynomial& other);

    Polynomial operator < (Polynomial& other);

    Polynomial<T>& operator = (Polynomial<T> &&other) noexcept ;

    friend ostream& operator << (ostream& out, Polynomial& polynomial);

    explicit operator string ();

    ~Polynomial();
};

#endif //LAB_4_POLYNOMIAL_H
