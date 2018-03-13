#include <iostream>

struct C {
    C() { std::cout << "Default\n"; }

    C(const C &) { std::cout << "A copy was made.\n"; }
};

C f(bool cond = false) {
    C first;
    C second;
    // the function may return one of two named objects
    // depending on its argument. RVO might not be applied
    return cond ? first : second;
}

int main() {
    C result = f();
}
