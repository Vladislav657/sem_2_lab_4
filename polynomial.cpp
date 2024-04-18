#include "polynomial.h"

double pow(double a, int b){ // b >= 0
    double result = 1;
    for (int i = 0; i < b; ++i) result *= a;
    return result;
}

int reduce(const double* array, int size){
    for (int i = size - 1; i >= 0; --i) {
        if (array[i] == 0 && i != 0) size--;
        else break;
    }
    return size;
}

Polynomial::Polynomial():size(1){
    this->coefficients = new double[1]{0};
    this->size = 1;
}

Polynomial::Polynomial(const double *coefficients, int size): size(size) {
    this->coefficients = new double[size];
    for (int i = 0; i < size; ++i) this->coefficients[i] = coefficients[i];
    this->size = reduce(this->coefficients, size);
}

Polynomial::Polynomial(const float *coefficients, int size): size(size) {
    this->coefficients = new double[size];
    for (int i = 0; i < size; ++i) this->coefficients[i] = (double) coefficients[i];
    this->size = reduce(this->coefficients, size);
}

Polynomial::Polynomial(const int *coefficients, int size): size(size) {
    this->coefficients = new double[size];
    for (int i = 0; i < size; ++i) this->coefficients[i] = (double) coefficients[i];
    this->size = reduce(this->coefficients, size);
}

Polynomial::Polynomial(Polynomial &other): size(other.size) {
    this->coefficients = new double[other.size];
    for (int i = 0; i < size; ++i) this->coefficients[i] = other.coefficients[i];
    this->size = other.size;
}

Polynomial::Polynomial(Polynomial &&other) noexcept : size(other.size) {
    this->coefficients = other.coefficients;
    this->size = other.size;
}

double Polynomial::calculate(double x) {
    double result = 0;
    for (int i = 0; i < this->size; ++i) result += this->coefficients[i] * pow(x, i);
    return result;
}

double Polynomial::calculate(float x) {
    double result = 0;
    for (int i = 0; i < this->size; ++i) result += this->coefficients[i] * pow((double)x, i);
    return result;
}

double Polynomial::calculate(int x) {
    double result = 0;
    for (int i = 0; i < this->size; ++i) result += this->coefficients[i] * pow((double)x, i);
    return result;
}

double Polynomial::operator[](int index) noexcept {
    if (index >= this->size || index < 0) return 0;
    return this->coefficients[index];
}

double Polynomial::at(int index) {
    if (index >= this->size || index < 0) throw range_error("Incorrect index");
    return this->coefficients[index];
}

Polynomial Polynomial::operator+(Polynomial &other) {
    int newSize;
    double *newCoefficients;
    if (this->size > other.size){
        newCoefficients = new double[this->size];
        for (int i = 0; i < this->size; ++i) newCoefficients[i] = this->coefficients[i];
        for (int i = 0; i < other.size; ++i) newCoefficients[i] += other.coefficients[i];
        newSize = this->size;
    } else {
        newCoefficients = new double[other.size];
        for (int i = 0; i < other.size; ++i) newCoefficients[i] = other.coefficients[i];
        for (int i = 0; i < this->size; ++i) newCoefficients[i] += this->coefficients[i];
        newSize = other.size;
    }
    newSize = reduce(newCoefficients, newSize);
    return {newCoefficients, newSize};
}

Polynomial Polynomial::operator+(double other) {
    auto *newCoefficients = new double[this->size];
    for (int i = 0; i < this->size; ++i) newCoefficients[i] = this->coefficients[i];
    newCoefficients[0] += other;
    return Polynomial{newCoefficients, this->size};
}

Polynomial Polynomial::operator-(Polynomial &other) {
    int newSize;
    double *newCoefficients;
    if (this->size > other.size){
        newCoefficients = new double[this->size];
        for (int i = 0; i < this->size; ++i) newCoefficients[i] = this->coefficients[i];
        for (int i = 0; i < other.size; ++i) newCoefficients[i] -= other.coefficients[i];
        newSize = this->size;
    } else {
        newCoefficients = new double[other.size];
        for (int i = 0; i < other.size; ++i) newCoefficients[i] = -other.coefficients[i];
        for (int i = 0; i < this->size; ++i) newCoefficients[i] += this->coefficients[i];
        newSize = other.size;
    }
    newSize = reduce(newCoefficients, newSize);
    return {newCoefficients, newSize};
}

Polynomial Polynomial::operator-(double other) {
    auto *newCoefficients = new double[this->size];
    for (int i = 0; i < this->size; ++i) newCoefficients[i] = this->coefficients[i];
    newCoefficients[0] -= other;
    return Polynomial{newCoefficients, this->size};
}

Polynomial Polynomial::operator*(Polynomial &other) {
    int newSize = this->size + other.size;
    auto *newCoefficients = new double[newSize]{0};
    for (int i = 0; i < this->size; ++i)
        for (int j = 0; j < other.size; ++j)
            newCoefficients[i + j] += this->coefficients[i] * other.coefficients[j];
    newSize = reduce(newCoefficients, newSize);
    return {newCoefficients, newSize};
}

Polynomial Polynomial::operator*(double other) {
    auto *newCoefficients = new double[this->size];
    for (int i = 0; i < this->size; ++i) newCoefficients[i] = this->coefficients[i] * other;
    int newSize = reduce(newCoefficients, this->size);
    return Polynomial{newCoefficients, newSize};
}

Polynomial Polynomial::operator/(double other) {
    if (other == 0) return {};
    auto *newCoefficients = new double[this->size];
    for (int i = 0; i < this->size; ++i) newCoefficients[i] = this->coefficients[i] / other;
    return Polynomial{newCoefficients, this->size};
}

Polynomial Polynomial::operator+=(Polynomial &other) {
    int newSize;
    double *newCoefficients;
    if (this->size > other.size){
        newCoefficients = new double[this->size];
        for (int i = 0; i < this->size; ++i) newCoefficients[i] = this->coefficients[i];
        for (int i = 0; i < other.size; ++i) newCoefficients[i] += other.coefficients[i];
        newSize = this->size;
    } else {
        newCoefficients = new double[other.size];
        for (int i = 0; i < other.size; ++i) newCoefficients[i] = other.coefficients[i];
        for (int i = 0; i < this->size; ++i) newCoefficients[i] += this->coefficients[i];
        newSize = other.size;
    }
    this->size = reduce(newCoefficients, newSize);
    delete[] this->coefficients;
    this->coefficients = newCoefficients;
    return *this;
}

Polynomial Polynomial::operator+=(double other) {
    this->coefficients[0] += other;
    return *this;
}

Polynomial Polynomial::operator-=(Polynomial &other) {
    int newSize;
    double *newCoefficients;
    if (this->size > other.size){
        newCoefficients = new double[this->size];
        for (int i = 0; i < this->size; ++i) newCoefficients[i] = this->coefficients[i];
        for (int i = 0; i < other.size; ++i) newCoefficients[i] -= other.coefficients[i];
        newSize = this->size;
    } else {
        newCoefficients = new double[other.size];
        for (int i = 0; i < other.size; ++i) newCoefficients[i] = -other.coefficients[i];
        for (int i = 0; i < this->size; ++i) newCoefficients[i] += this->coefficients[i];
        newSize = other.size;
    }
    this->size = reduce(newCoefficients, newSize);
    delete[] this->coefficients;
    this->coefficients = newCoefficients;
    return *this;
}

Polynomial Polynomial::operator-=(double other) {
    this->coefficients[0] -= other;
    return *this;
}

Polynomial Polynomial::operator*=(Polynomial &other) {
    int newSize = this->size + other.size;
    auto *newCoefficients = new double[newSize]{0};
    for (int i = 0; i < this->size; ++i)
        for (int j = 0; j < other.size; ++j)
            newCoefficients[i + j] += this->coefficients[i] * other.coefficients[j];
    this->size = reduce(newCoefficients, newSize);
    delete[] this->coefficients;
    this->coefficients = newCoefficients;
    return *this;
}

Polynomial Polynomial::operator*=(double other) {
    for (int i = 0; i < this->size; ++i) this->coefficients[i] *= other;
    this->size = reduce(this->coefficients, this->size);
    return *this;
}

Polynomial Polynomial::operator/=(double other) {
    if (other == 0) return *this;
    for (int i = 0; i < this->size; ++i) this->coefficients[i] /= other;
    return *this;
}

Polynomial Polynomial::operator-() {
    auto *newCoefficients = new double[this->size];
    for (int i = 0; i < this->size; ++i) newCoefficients[i] = -this->coefficients[i];
    return {newCoefficients, this->size};
}

bool Polynomial::operator==(Polynomial &other) {
    if (this->size != other.size) return false;
    for (int i = 0; i < this->size; ++i)
        if (this->coefficients[i] != other.coefficients[i]) return false;
    return true;
}

bool Polynomial::operator>=(Polynomial &other) {
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

bool Polynomial::operator<=(Polynomial &other) {
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

bool Polynomial::operator>(Polynomial &other) {
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

bool Polynomial::operator<(Polynomial &other) {
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

Polynomial& Polynomial::operator=(Polynomial &&other) noexcept {
    this->coefficients = new double[other.size];
    for (int i = 0; i < size; ++i) this->coefficients[i] = other.coefficients[i];
    this->size = other.size;
    return *this;
}

ostream &operator<<(ostream &out, Polynomial &polynomial) {
    for (int i = polynomial.size - 1; i >= 0; --i) {
        if (polynomial.coefficients[i] != 0) {
            if (i == polynomial.size - 1) {
                if (polynomial.coefficients[i] != 1 && polynomial.coefficients[i] != -1)
                    out << polynomial.coefficients[i];
                else if (polynomial.coefficients[i] == -1)
                    out << '-';
            }
            else if (i == 0)
                polynomial.coefficients[i] > 0 ?
                out << " + " <<  polynomial.coefficients[i]: out << " - " << -polynomial.coefficients[i];
            else {
                polynomial.coefficients[i] > 0 ? out << " + " : out << " - ";
                if (polynomial.coefficients[i] < 0 && polynomial.coefficients[i] != -1)
                    out << -polynomial.coefficients[i];
                else if (polynomial.coefficients[i] > 0 && polynomial.coefficients[i] != 1)
                    out << polynomial.coefficients[i];
            }
            if (i == 1) out << "X";
            else if (i > 1) out << "X^" << i;
        }
    }
    return out;
}

Polynomial::operator string() {
    string polynomial;
    for (int i = this->size - 1; i >= 0; --i) {
        if (this->coefficients[i] != 0) {
            if (i == this->size - 1) {
                if (this->coefficients[i] != 1 && this->coefficients[i] != -1)
                    polynomial += to_string(this->coefficients[i]);
                else if (this->coefficients[i] == -1)
                    polynomial += '-';
            }
            else if (i == 0)
                this->coefficients[i] > 0 ?
                polynomial += " + " + to_string(this->coefficients[i]) :
                            polynomial += " - " + to_string(-this->coefficients[i]);
            else {
                this->coefficients[i] > 0 ? polynomial += " + " : polynomial += " - ";
                if (this->coefficients[i] < 0 && this->coefficients[i] != -1)
                    polynomial += to_string(-this->coefficients[i]);
                else if (this->coefficients[i] > 0 && this->coefficients[i] != 1)
                    polynomial += to_string(this->coefficients[i]);
            }
            if (i == 1) polynomial += "X";
            else if (i > 1) polynomial += "X^" + to_string(i);
        }
    }
    return polynomial;
}

Polynomial::~Polynomial() {
    delete[] this->coefficients;
}
