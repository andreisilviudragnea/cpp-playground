//
// Created by andre on 15.03.2018.
//

#include <iostream>

int n;

struct C {
    int x;
    C() {
        x = n++;
        std::cout << "C::C " << x << "\n";
    }

    C(const C &c) {
        x = n++;
        std::cout << "C::C(const C &) " << x << "\n";
    }
//    C(const C &) = delete;

    C(C &&c) noexcept {
        x = n++;
        std::cout << "C::C(const C &&) " << x << "\n";
    }
//    C(const C &&) = delete;

    C &operator=(const C &c) {
        x = n++;
        std::cout << "C::operator=(const C&) " << x << "\n";
        return *this;
    }

    C &operator=(C &&c) noexcept {
        x = n++;
        std::cout << "C::operator=(const C &&) " << x << "\n";
        return *this;
    }

    ~C() {
        std::cout << "C::~C " << x << "\n";
    }
};

C f() {
    C c = C();
    std::cout << "f()\n";
    return c;
}

int main() {
    try {
        C c;
        for (int i = 0; i < 3; i++) {
            c = f();
            throw C();
            std::cout << "Loop\n";
        }
    } catch (C &c) {
        std::cout << "Caught\n";
    }

    return 0;
}
