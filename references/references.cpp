#include <iostream>

static void f(const int &x) {
    std::cout << x << std::endl;
}

int main() {
    int *p = new int(5);
    int &x = *p;
    delete p;
    int *q = new int(6);
    f(x);
    return 0;
}
