#include <iostream>

using namespace std;

int main(){
    int *a = new int[10]{0};
    for (int i = 0; i < 10; ++i) {
//        a[i] = i;
        cout << a[i] << ' ';
    }
    delete[] a;
    return 0;
}
