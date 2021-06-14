#include <iostream>
#include <string>
#include <vector>
#include "monomial.h"

// Monomial Tests
using namespace std;
int main() {

    {
        vector<double> v = { 1, 2, 4, 0, 0, 0 };
        Monomial m(4, v); // GOOD
        cout << m << "\n"; // GOOD
    }

    {
        vector<double> v = { 1, 2, 4, 5, 0, 10 };
        Monomial m(4, v); // GOOD
        vector<double> u = { 5, 6, 2, 4, 1, 0, 3 };
        Monomial n(89, u); // GOOD
        // cout << (u == v) << "\n";
        cout << n * m << "\n"; // GOOD
        n *= m;
        cout << n << "\n"; // GOOD
        n = m;
        cout << (n == m) << "\n"; // GOOD
        cout << (n != m) << "\n"; // GOOD
        cout << m.Coef() << "\n"; // GOOD
    } // GOOD

    {
        vector<double> p = { 1, 3, 4.5, 2 };
        Monomial tm(p);
        cout << tm << "\n";
    } // GOOD

    {
        vector<double> p = { 1, 3, 4, 2 };
        Monomial tm(p);
        cout << tm << "\n";
        vector<int> v = { 1 };
        cout << tm(v) << "\n"; // GOOD
        v = { 1, 2, 1, 0 };
        cout << tm(v) << "\n"; // GOOD
        v = { 1, 2, 1, 1 };
        cout << tm(v) << "\n";
        v = { 4, 2, 3, 5 };
        cout << tm(v) << "\n"; // GOOD
        vector<double> u = { 1.5, 1, 4.3, 9.2 };
        cout << tm(u) << "\n"; // GOOD
    } // GOOD

    {
        Monomial k(10);
        cout << k << "\n";
    } // GOOD

    // DIVISION
    {
        vector<int> v = { 4, 8, 0, 4 };
        vector<int> u = { 1, 3, 0, 1 };
        Monomial one(4, v), two(6, u);
        Monomial k = one / two; // GOOD
        cout << k << "\n";
        one /= two;
        cout << one << "\n"; // GOOD
        for (auto elem : k.Degs()) {
            cout << elem << ' ';
        }
        cout << "\n";
    } // GOOD
    // CHECK ANOTHER DIVISION CASES
    cout << "______________________________________________________________\n";
    {
        vector<int> v = { 4, 8, 0, 4, 6, 2, 0, 0 };
        vector<int> u = { 1, 3, 0, 2, 3, 1 };
        Monomial one(4, v), two(6, u);
        Monomial k = one / two;
        cout << k << "\n";
        one /= two;
        cout << one << "\n"; // GOOD
        print(k.Degs()); // NOT GOOD
        cout << "\n";
    }

    {
        vector<int> v = { 4, 8 };
        vector<int> u = { 1, 2 };
        Monomial one(4, v), two(6, u);
        cout << LCM(one, two) << "\n"; // GOOD
        cout << GCD(one, two) << "\n"; // GOOD
        v = u;
        cout << v << "\n"; // GOOD
        v = { 4, 8 };
        u = { 6, 3 };
        one = Monomial(4, v), two = Monomial(6, u);
        cout << one << "  |  " << two << "\n"; // GOOD

        print(one.Degs());
        cout << " |  ";
        print(two.Degs());
        cout << "\n";
        // GOOD

        cout << LCM(one, two) << "\n"; // GOOD
        cout << GCD(one, two) << "\n"; // GOOD
        cout << (LCM(one, two) == LCM(two, one)) << "\n"; // GOOD
        cout << (GCD(one, two) == GCD(two, one)) << "\n"; // GOOD
        v = { 4, 36 };
        u = { 5, 18 };
        one = Monomial(4, v), two = Monomial(6, u);
        cout << LCM(one, two) << "\n"; // GOOD
        cout << GCD(one, two) << "\n"; // GOOD
    }

    {
        vector<int> v = { 4, 36, 0, 0 };
        vector<int> u = { 5, 18, 9, 3 };
        Monomial one(4, v), two(6, u);
        cout << LCM(one, two) << "\n"; // GOOD
        cout << GCD(one, two) << "\n"; // GOOD
        v = { 4, 0, 0, 5, 9, 0 };
        u = { 5, 0, 6, 25, 0, 0, 0, 4 };
        one = Monomial(4, v), two = Monomial(6, u);
        cout << LCM(one, two) << "\n"; // GOOD
        cout << GCD(one, two) << "\n"; // GOOD
        print(LCM(one, two).Degs()); // GOOD
        cout << "\n";
        print(GCD(one, two).Degs()); // GOOD
        cout << "\n";
    }

    {
        vector<int> v = { 4, 36, 0, 0 };
        vector<int> u = { 5, 18, 9, 3, 0, 0 };
        Monomial one(4, v);
        one = u;
        cout << one << "\n";
        print(one.Degs());
        cout << "\n";
        // GOOD
        mon_info(one);
        // mon_info(2 * one);
        // mon_info(one * 4.5);
    }

    {
        vector<int> v = { 4, 6, 0, 2 };
        Monomial one(4, v);
        cout << one << "\n";
        one.Coef() = 8;
        cout << one << "\n"; // GOOD
        cout << one.Coef() * 111 << "\n"; // GOOD
    }

    {
        vector<int> v = { 4, 6, 0, 2 };
        Monomial one(4, v);
        print(one.Degs());
        cout << "\n";
        // 4 6 0 2
        vector<unsigned long int> u = { 1, 6, 2, 0, 6 };
        one.Degs() = u; // GOOD
        print(one.Degs());
        cout << "\n";
        // 1 6 2 0 6

        // YOU CAN'T DO THIS
        // vector<int> k = { 1, 6, 2, 0, 6 };
        // one.Degs() = k;
        // vector<double> t = { 1, 6, 2, 0, 6 };
        // one.Degs() = k;

        // ALL'S GOOD
    }

    {
        vector<int> v = { 4, 6, 0, 2, 10 };
        Monomial one(4.7, v);
        cout << one << "\n";
        // 4.7 * x_1^{4} * x_2^{6} * x_4^{2} * x_5^{10}
        cout << one[4] << ' ' << one[0] << "\n";
        // 10 4
        for (size_t i = 0; i < one.size(); ++i) {
            cout << one[i] << ' ';
        }
        cout << "\n";
        // 4 6 0 2 10
        for (size_t i = 0; i < one.size(); ++i) {
            one[i] = i;
            cout << one[i] << ' ';
        }
        cout << "\n";
        // 0 1 2 3 4
        cout << one << "\n";
        // 4.7 * x_2 * x_3^{2} * x_4^{3} * x_5^{4}
        try { // Check for exception
            cout << one[10] << "\n";
        }
        catch (...) {
            cout << "Got it!\n";
        }
        // Got it!
        // ALL'S GOOD
    }

    {
        vector<int> v = { 4, 6, 0, 2 };
        Monomial one(4, v);
        auto two = one * 3;
        cout << two << "\n";
        one = 5 * two * 5;
        cout << one << "\n";
        two *= 9;
        cout << two << "\n";
        // ALL'S GOOD
    }

    {
        vector<int> v = { 4, 6, 0, 2 };
        Monomial one(120, v);
        auto two = one / 3;
        cout << two << "\n";
        one = 3.5 * two;
        cout << one << "\n";
        two /= 9;
        cout << two << "\n";
        two = two / 0;
        one /= 0;
        cout << two;
        // Error code 2: the vector can't be empty for output!
        cout << one;
        // Error code 2: the vector can't be empty for output!
        // ALL'S GOOD
    }

    {
        vector<unsigned long int> v = { 1, 9, 1, 6 };
        Monomial one(32, v);
        vector<unsigned long int> u = { 1, 9, 0, 300 };
        Monomial two(87, u);
        compare(one, two); // GOOD
        v = { 4, 6, 3, 2 };
        one.Degs() = v;
        two[0] = 5;
        compare(one, two); // GOOD
        vector<unsigned long int> k = { 1, 0, 0 };
        one.Degs() = k;
        vector<unsigned long int> t = { 1, 1, 0, 0 };
        two.Degs() = t;
        compare(one, two); // GOOD
        k = { 3, 4, 2, 6, 9, 5 };
        t = { 3, 4, 4, 0, 0 };
        one.Degs() = k;
        two.Degs() = t;
        print(two.Degs());
        cout << "\n"; // Here's the problem
        // 3, 4, 4, 0, 0
        compare(one, two); // GOOD
    }

    {
        vector<unsigned long int> v = { 1, 9, 1, 6 };
        Monomial one(32, v);
        vector<unsigned long int> u = { 1, 9, 0, 300 };
        Monomial two(87, u);
        compare(one, two); // GOOD
        compare(two, one); // GOOD
        one.Coef() = 1;
        two.Coef() = 4;
        two.Degs() = v;
        compare(one, two); // GOOD
        compare(two, one); // GOOD
    }
    // <=, >= left

    return 0;
}
