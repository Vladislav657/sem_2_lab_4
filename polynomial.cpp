#include "polynomial.h"

template <typename T>
T pow(T a, int b){ // b >= 0
    T result = 1;
    for (int i = 0; i < b; ++i) result *= a;
    return result;
}

template <typename T>
int reduce(T* array, int size){
    for (int i = size - 1; i >= 0; --i) {
        if (array[i] == 0 && i != 0) size--;
        else break;
    }
    return size;
}

template <typename T>
Polynomial<T>::Polynomial():size(1){
    this->coefficients = new T[1]{0};
    this->size = 1;
}

template <typename T>
Polynomial<T>::Polynomial(T *coefficients, int size): size(size) {
    this->size = reduce(coefficients, size);
    this->coefficients = new T[this->size];
    for (int i = 0; i < this->size; ++i) this->coefficients[i] = coefficients[i];
}

template <typename T>
Polynomial<T>::Polynomial(Polynomial<T> &other): size(other.size) {
    this->coefficients = new T[other.size];
    for (int i = 0; i < size; ++i) this->coefficients[i] = other.coefficients[i];
    this->size = other.size;
}

template <typename T>
Polynomial<T>::Polynomial(Polynomial<T> &&other) noexcept : size(other.size) {
    this->coefficients = other.coefficients;
    this->size = other.size;
}

template <typename T>
T Polynomial<T>::calculate(T x) {
    T result = 0;
    for (int i = 0; i < this->size; ++i) result += this->coefficients[i] * pow(x, i);
    return result;
}

template <typename T>
T Polynomial<T>::operator[](int index) noexcept {
    if (index >= this->size || index < 0) return 0;
    return this->coefficients[index];
}

template <typename T>
T Polynomial<T>::at(int index) {
    if (index >= this->size || index < 0) throw range_error("Incorrect index");
    return this->coefficients[index];
}

template <typename T>
Polynomial<T> Polynomial<T>::operator+(Polynomial<T> &other) {
    int newSize;
    T *newCoefficients;
    if (this->size > other.size){
        newCoefficients = new T[this->size];
        for (int i = 0; i < this->size; ++i) newCoefficients[i] = this->coefficients[i];
        for (int i = 0; i < other.size; ++i) newCoefficients[i] += other.coefficients[i];
        newSize = this->size;
    } else {
        newCoefficients = new T[other.size];
        for (int i = 0; i < other.size; ++i) newCoefficients[i] = other.coefficients[i];
        for (int i = 0; i < this->size; ++i) newCoefficients[i] += this->coefficients[i];
        newSize = other.size;
    }
    newSize = reduce(newCoefficients, newSize);
    return Polynomial<T>(newCoefficients, newSize);
}

template <typename T>
Polynomial<T> Polynomial<T>::operator+(T other) {
    T *newCoefficients = new T[this->size];
    for (int i = 0; i < this->size; ++i) newCoefficients[i] = this->coefficients[i];
    newCoefficients[0] += other;
    return Polynomial<T>{newCoefficients, this->size};
}

template <typename T>
Polynomial<T> Polynomial<T>::operator-(Polynomial<T> &other) {
    int newSize;
    T *newCoefficients;
    if (this->size > other.size){
        newCoefficients = new T[this->size];
        for (int i = 0; i < this->size; ++i) newCoefficients[i] = this->coefficients[i];
        for (int i = 0; i < other.size; ++i) newCoefficients[i] -= other.coefficients[i];
        newSize = this->size;
    } else {
        newCoefficients = new T[other.size];
        for (int i = 0; i < other.size; ++i) newCoefficients[i] = -other.coefficients[i];
        for (int i = 0; i < this->size; ++i) newCoefficients[i] += this->coefficients[i];
        newSize = other.size;
    }
    newSize = reduce(newCoefficients, newSize);
    return Polynomial<T>(newCoefficients, newSize);
}

template <typename T>
Polynomial<T> Polynomial<T>::operator-(T other) {
    T *newCoefficients = new T[this->size];
    for (int i = 0; i < this->size; ++i) newCoefficients[i] = this->coefficients[i];
    newCoefficients[0] -= other;
    return Polynomial<T>{newCoefficients, this->size};
}

template <typename T>
Polynomial<T> Polynomial<T>::operator*(Polynomial<T> &other) {
    int newSize = this->size + other.size;
    T *newCoefficients = new T[newSize]{0};
    for (int i = 0; i < this->size; ++i)
        for (int j = 0; j < other.size; ++j)
            newCoefficients[i + j] += this->coefficients[i] * other.coefficients[j];
    newSize = reduce(newCoefficients, newSize);
    return Polynomial<T>(newCoefficients, newSize);
}

template <typename T>
Polynomial<T> Polynomial<T>::operator*(T other) {
    T *newCoefficients = new T[this->size];
    for (int i = 0; i < this->size; ++i) newCoefficients[i] = this->coefficients[i] * other;
    int newSize = reduce(newCoefficients, this->size);
    return Polynomial<T>{newCoefficients, newSize};
}

template <typename T>
Polynomial<T> Polynomial<T>::operator/(T other) {
    if (other == 0) return Polynomial<T>();
    T *newCoefficients = new T[this->size];
    for (int i = 0; i < this->size; ++i) newCoefficients[i] = this->coefficients[i] / other;
    return Polynomial<T>{newCoefficients, this->size};
}

template <typename T>
Polynomial<T> Polynomial<T>::operator+=(Polynomial<T> &other) {
    int newSize;
    T *newCoefficients;
    if (this->size > other.size){
        newCoefficients = new T[this->size];
        for (int i = 0; i < this->size; ++i) newCoefficients[i] = this->coefficients[i];
        for (int i = 0; i < other.size; ++i) newCoefficients[i] += other.coefficients[i];
        newSize = this->size;
    } else {
        newCoefficients = new T[other.size];
        for (int i = 0; i < other.size; ++i) newCoefficients[i] = other.coefficients[i];
        for (int i = 0; i < this->size; ++i) newCoefficients[i] += this->coefficients[i];
        newSize = other.size;
    }
    this->size = reduce(newCoefficients, newSize);
    delete[] this->coefficients;
    this->coefficients = newCoefficients;
    return *this;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator+=(T other) {
    this->coefficients[0] += other;
    return *this;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator-=(Polynomial<T> &other) {
    int newSize;
    T *newCoefficients;
    if (this->size > other.size){
        newCoefficients = new T[this->size];
        for (int i = 0; i < this->size; ++i) newCoefficients[i] = this->coefficients[i];
        for (int i = 0; i < other.size; ++i) newCoefficients[i] -= other.coefficients[i];
        newSize = this->size;
    } else {
        newCoefficients = new T[other.size];
        for (int i = 0; i < other.size; ++i) newCoefficients[i] = -other.coefficients[i];
        for (int i = 0; i < this->size; ++i) newCoefficients[i] += this->coefficients[i];
        newSize = other.size;
    }
    this->size = reduce(newCoefficients, newSize);
    delete[] this->coefficients;
    this->coefficients = newCoefficients;
    return *this;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator-=(T other) {
    this->coefficients[0] -= other;
    return *this;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator*=(Polynomial<T> &other) {
    int newSize = this->size + other.size;
    T *newCoefficients = new T[newSize]{0};
    for (int i = 0; i < this->size; ++i)
        for (int j = 0; j < other.size; ++j)
            newCoefficients[i + j] += this->coefficients[i] * other.coefficients[j];
    this->size = reduce(newCoefficients, newSize);
    delete[] this->coefficients;
    this->coefficients = newCoefficients;
    return *this;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator*=(T other) {
    for (int i = 0; i < this->size; ++i) this->coefficients[i] *= other;
    this->size = reduce(this->coefficients, this->size);
    return *this;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator/=(T other) {
    if (other == 0) return *this;
    for (int i = 0; i < this->size; ++i) this->coefficients[i] /= other;
    return *this;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator-() {
    T *newCoefficients = new T[this->size];
    for (int i = 0; i < this->size; ++i) newCoefficients[i] = -this->coefficients[i];
    return Polynomial<T>(newCoefficients, this->size);
}

template <typename T>
Polynomial<T> Polynomial<T>::operator==(Polynomial<T> &other) {
    if (this->size != other.size) return false;
    for (int i = 0; i < this->size; ++i)
        if (this->coefficients[i] != other.coefficients[i]) return false;
    return true;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator>=(Polynomial<T> &other) {
    if (this->size > other.size){
        if (this->coefficients[this->size - 1] < 0) return false;
        else return true;
    } else if (this->size < other.size){
        if (other.coefficients[other.size - 1] < 0) return true;
        else return false;
    }
    for (int i = this->size - 1; i >= 0; --i) {
        if (this->coefficients[i] > other.coefficients[i]) return true;
        else if (this->coefficients[i] < other.coefficients[i]) return false;
    }
    return true;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator<=(Polynomial<T> &other) {
    if (this->size > other.size){
        if (this->coefficients[this->size - 1] < 0) return true;
        else return false;
    } else if (this->size < other.size){
        if (other.coefficients[other.size - 1] < 0) return false;
        else return true;
    }
    for (int i = this->size - 1; i >= 0; --i) {
        if (this->coefficients[i] > other.coefficients[i]) return false;
        else if (this->coefficients[i] < other.coefficients[i]) return true;
    }
    return true;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator>(Polynomial<T> &other) {
    if (this->size > other.size){
        if (this->coefficients[this->size - 1] < 0) return false;
        else return true;
    } else if (this->size < other.size){
        if (other.coefficients[other.size - 1] < 0) return true;
        else return false;
    }
    for (int i = this->size - 1; i >= 0; --i) {
        if (this->coefficients[i] > other.coefficients[i]) return true;
        else if (this->coefficients[i] < other.coefficients[i]) return false;
    }
    return false;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator<(Polynomial<T> &other) {
    if (this->size > other.size){
        if (this->coefficients[this->size - 1] < 0) return true;
        else return false;
    } else if (this->size < other.size){
        if (other.coefficients[other.size - 1] < 0) return false;
        else return true;
    }
    for (int i = this->size - 1; i >= 0; --i) {
        if (this->coefficients[i] > other.coefficients[i]) return false;
        else if (this->coefficients[i] < other.coefficients[i]) return true;
    }
    return false;
}

template <typename T>
Polynomial<T>& Polynomial<T>::operator=(Polynomial<T> &&other) noexcept {
    this->coefficients = new T[other.size];
    for (int i = 0; i < size; ++i) this->coefficients[i] = other.coefficients[i];
    this->size = other.size;
    return *this;
}

template <typename T>
ostream &operator<<(ostream &out, Polynomial<T> &polynomial) {
    for (int i = polynomial.size - 1; i >= 0; --i) {
        if (polynomial.coefficients[i] != 0) {
            if (i > 0) polynomial.coefficients[i] > 0 ? out << " + " : out << " - ";
            out << polynomial.coefficients[i];
            if (i == 1) out << 'X';
            else if (i > 1) out << "X^" << i;
        }
    }
    return out;
}

template <typename T>
Polynomial<T>::operator string() {
    string polynomial;
    for (int i = this->size - 1; i >= 0; --i) {
        if (this->coefficients[i] != 0) {
            if (i > 0) polynomial += this->coefficients[i] > 0 ? " + " : " - ";
            polynomial += to_string((double)this->coefficients[i]);
            if (i == 1) polynomial += 'X';
            else if (i > 1) polynomial += "X^" + to_string(i);
        }
    }
    return polynomial;
}

template <typename T>
Polynomial<T>::~Polynomial() {
    delete[] this->coefficients;
}
