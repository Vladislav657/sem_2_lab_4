#include <iostream>
#include "polynomial.h"

using namespace std;

int main(){
    auto *array = new double[7]{8.4, -3.43, -1, 9, -3.657, 0, 7};
    Polynomial p = Polynomial(array, 7);
    double res = p.calculate(5);
    string str = (string)p;
    cout << str << endl;
    cout << p << endl;
    cout << "X = 5: " << res;
    delete[] array;
    return 0;
}
