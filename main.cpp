#include <iostream>
#include "polynomial.h"

using namespace std;

int main(){
    auto *array1 = new double[7]{-1, -3.43, -1, 9, -3.657, 0, 1};
    auto *array2 = new double[10]{9.434, -4, 87, 9.3, -2.55, 4, -2, 459, 5, 55.33};
    Polynomial p1 = Polynomial(array1, 7);
    Polynomial p2 = Polynomial(array2, 10);
    string str = (string)p1;

    Polynomial add = p1 + p2;
    Polynomial sub = p1 - p2;
    Polynomial mul = p1 * p2;
    Polynomial mul_n = p1 * 5;
    Polynomial sub_n = p1 / 6.6;

    cout << p1 << endl;
    cout << p2 << "\n\n";
    cout << add << endl;
    cout << sub << endl;
    cout << mul << endl;
    cout << mul_n << endl;
    cout << sub_n << "\n\n";

    cout << p1[6] << endl;
    cout << p2.at(9) << endl;
    cout << "X = 5: " << p1.calculate(5) << endl;
    cout << "X = 5.5: " << p1.calculate(5.5) << "\n\n";

    bool f = p1 > p2;
    cout << f << endl;
    f = p1 < p2;
    cout << f << endl;
    f = p1 >= p2;
    cout << f << endl;
    f = p1 <= p2;
    cout << f << endl;
    f = p1 == p2;
    cout << f << "\n\n";

    Polynomial p3 = -p1;
    cout << p3 << endl;

    p1 *= p2;
    cout << p1 << endl;

    delete[] array1;
    delete[] array2;
    return 0;
}
