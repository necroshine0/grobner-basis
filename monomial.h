#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <ostream>

// STRING VECTOR;
void get_exception(int a) {
    std::cout << "Error code " << a << ": ";
    switch (a) {
    case 0:
        std::cout << "the vector must be of the int type!\n";
        break;
    case 1:
        std::cout << "the vector must contain non-negative int values!\n";
        break;
    case 2:
        std::cout << "the vector can't be empty for output!\n";
        break;
    case 3:
        std::cout << "the monomial's vector has a wrong size!\n";
        break;
    case 4:
        std::cout << "you can not divide by the zero monomial!\n";
        break;
    case 5:
        std::cout << "you can not divide by the monomial of bigger size!\n";
        break;
    case 6:
        std::cout << "you can not divide by zero!\n";
        break;
        /*case 7:
            std::cout << "you can not divide by zero!\n";
            break;*/
    }
}

class Monomial {
private:
    double coef = 0;
    std::vector<unsigned long int> degs;

protected:
    template <typename T>
    double fast_pow(T a, unsigned long int b) {
        if (b == 0) return 1;
        if (b % 2 == 0) {
            double x = fast_pow(a * a, b / 2);
            return x * x;
        }
        return std::pow(fast_pow(a, b - 1), 2) * a;
    }

public:
    Monomial() {}
    Monomial(const size_t n) {
        degs.resize(n);
        std::fill(degs.begin(), degs.end(), 1);
        coef = 1;
    }
    template<typename T, typename R>
    Monomial(const T a, const std::vector<R>& v) {
        coef = double(a);
        for (size_t i = 0; i < v.size(); ++i) {
            try {
                if (int(v[i]) != v[i]) // int check
                    throw 0;
                if (v[i] < R(0))
                    throw 1;
            }
            catch (int k) {
                coef = 0;
                degs.clear();
                get_exception(k); // function
                return;
            }
            degs.push_back(static_cast<unsigned long int>(v[i]));
        }
        while (degs.size() != 0 && degs.back() == 0) {
            degs.pop_back();
        }
    }
    template<typename R>
    Monomial(const std::vector<R>& v) {
        coef = 1;
        for (size_t i = 0; i < v.size(); ++i) {
            try {
                if (int(v[i]) != v[i])
                    throw 0;
                if (v[i] < R(0))
                    throw 1;
            }
            catch (int k) {
                coef = 0;
                degs.clear();
                get_exception(k);
                return;
            }
            degs.push_back(static_cast<unsigned long int>(v[i]));
        }
        while (degs.size() != 0 && degs.back() == 0) {
            degs.pop_back();
        }
    }
    ~Monomial() {
        coef = 0;
        degs.clear();
    }

    bool operator == (const Monomial& mon) const { return degs == mon.degs && coef == mon.coef; }
    bool operator != (const Monomial& mon) const { return !operator == (mon); }
    bool operator < (const Monomial& mon) const {
        try {
            if (this->coef == 0 || mon.coef == 0)
                throw 666;
        }
        catch (...) {
            std::cout << "This monomials are incomparable!\n";
            return false;
        }

        size_t n = this->size(), m = mon.size();
        size_t i = 0;
        while (i < std::min(n, m)) {
            if ((*this)[i] != mon[i]) {
                if ((*this)[i] < mon[i]) return true;
                return false;
            }
            ++i;
        }
        if (n == m) return (this->coef < mon.coef);
        else if (n < m) return true;
        return false;
    }
    bool operator > (const Monomial& mon) const {
        try {
            if (this->coef == 0 || mon.coef == 0)
                throw 666;
        }
        catch (...) {
            std::cout << "This monomials are incomparable!\n";
            return false;
        }

        size_t n = this->size(), m = mon.size();
        size_t i = 0;
        while (i < std::min(n, m)) {
            if ((*this)[i] != mon[i]) {
                if ((*this)[i] > mon[i]) return true;
                return false;
            }
            ++i;
        }
        if (n == m) return (this->coef > mon.coef);
        else if (n > m) return true;
        return false;
    }
    bool operator <= (const Monomial& mon) const {
        return operator < (mon) || operator == (mon);
    }
    bool operator >= (const Monomial& mon) const {
        return operator > (mon) || operator == (mon);
    }

    Monomial& operator = (const Monomial& mon) {
        degs.resize(mon.degs.size());
        for (size_t i = 0; i < mon.degs.size(); ++i)
            degs[i] = mon.degs[i];
        coef = double(mon.coef);
        return *this;
    }
    Monomial operator * (Monomial& mon) {
        size_t n = this->size(), m = mon.size();
        for (size_t i = n; i < std::max(n, m); ++i)
            this->degs.push_back(0);
        for (size_t i = m; i < std::max(n, m); ++i)
            mon.degs.push_back(0);
        std::vector<unsigned long int> multi_degs(std::max(n, m));
        double multi_coef = this->coef * mon.coef;
        for (size_t i = 0; i < std::max(n, m); ++i)
            multi_degs[i] = this->degs[i] + mon.degs[i];
        while (this->degs.size() != 0 && this->degs.back() == 0)
            this->degs.pop_back();
        while (mon.degs.size() != 0 && mon.degs.back() == 0)
            mon.degs.pop_back();

        return Monomial(multi_coef, multi_degs);
    }

    Monomial operator / (const Monomial& mon) {
        size_t n = degs.size();
        size_t m = mon.degs.size();
        try {
            if (mon.coef == 0) { throw 4; }
            if (m > n) { throw 5; }
        }
        catch (int k) {
            get_exception(k);
            return Monomial();
        }

        double new_coef = this->coef;
        std::vector<unsigned long int> new_degs = this->degs,
            tmp_degs = this->degs; // O(2n)
        while (true) { // O(1)
            for (size_t i = 0; i < m; ++i) { // O(m)
                if (tmp_degs[i] < mon.degs[i]) {
                    if (new_degs == this->degs)
                        std::cout << "Division is failed\n"; // O(n) = returning time
                    return Monomial(new_coef, new_degs);
                }
                tmp_degs[i] -= mon.degs[i];
            }
            new_coef /= mon.coef;
            new_degs = tmp_degs; // O(max(n, m)) = O(n)
        }
    }
    Monomial& operator *= (Monomial& mon) {
        *this = *this * mon;
        return *this;
    }
    Monomial& operator /= (const Monomial& mon) {
        *this = *this / mon;
        return *this;
    }

    template <typename T>
    Monomial& operator *= (const T a) {
        this->coef *= a;
        return *this;
    }
    template <typename T>
    Monomial& operator /= (const T a) {
        try {
            if (a == 0) throw 6;
        }
        catch (int k) {
            get_exception(k);
            *this = Monomial();
            return *this;
        }
        this->coef /= a;
        return *this;
    }

    template <typename T>
    double operator () (const std::vector<T>& v) {
        size_t n = degs.size();
        try {
            if (n != v.size())
                throw 3;
        }
        catch (int k) {
            get_exception(k);
            return 0;
        }

        double value = 1;
        for (size_t i = 0; i < n; ++i) {
            value *= fast_pow(v[i], degs[i]);
        }
        value *= coef;
        return value;
    }
    double& Coef() { return coef; }
    const double Coef() const { return coef; }
    std::vector<unsigned long int>& Degs() { return degs; }
    const std::vector<unsigned long int> Degs() const { return degs; }
    unsigned long int& operator [] (const size_t& i) {
        return degs.at(i);
    }
    const unsigned long int& operator [] (const size_t& i) const {
        return degs.at(i);
    }
    const size_t size() const { return degs.size(); }

    template <typename T>
    friend Monomial operator * (const Monomial& mon, const T& a) {
        return Monomial(mon.Coef() * a, mon.Degs());
    }
    template <typename T>
    friend Monomial operator * (const T& a, const Monomial& mon) {
        return Monomial(mon.Coef() * a, mon.Degs());
    }
    template <typename T>
    Monomial operator / (const T& a) {
        try {
            if (a == 0) throw 6;
        }
        catch (int k) {
            get_exception(k);
            return Monomial();
        }
        return Monomial(coef / a, degs);
    }

    friend std::ostream& operator<<(std::ostream& out, const Monomial& mon);
    friend Monomial LCM(Monomial& mon_1, Monomial& mon_2);
    friend Monomial GCD(Monomial& mon_1, Monomial& mon_2);
};

std::ostream& operator<<(std::ostream& out, const Monomial& mon) {
    try { if (mon.degs.empty()) throw 2; }
    catch (int k) {
        get_exception(k);
        out << "";
        return out;
    }

    if (mon.coef == 0) {
        out << 0;
        return out;
    }
    out << mon.coef;
    for (size_t i = 0; i < mon.degs.size(); ++i) {
        if (mon.degs[i] != 0) {
            if (mon.degs[i] == 1) out << " * x_" << i + 1;
            else out << " * x_" << i + 1 << "^{" << mon.degs[i] << "}";
        }
    }
    return out;
}
Monomial LCM(Monomial& mon_1, Monomial& mon_2) {
    size_t n = mon_1.size(), m = mon_2.size();
    for (size_t i = n; i < std::max(n, m); ++i) { mon_1.degs.push_back(0); }
    for (size_t i = m; i < std::max(n, m); ++i) { mon_2.degs.push_back(0); }
    // Now both mons are of equal sizes
    std::vector<unsigned long int> LCM_degs(std::max(n, m));
    double LCM_coef = std::min(mon_1.coef, mon_2.coef);

    for (size_t i = 0; i < std::max(n, m); ++i) // O(max(n, m))
        LCM_degs[i] = std::max(mon_1.degs[i], mon_2.degs[i]);

    while (mon_1.degs.size() != 0 && mon_1.degs.back() == 0)
        mon_1.degs.pop_back();

    while (mon_2.degs.size() != 0 && mon_2.degs.back() == 0)
        mon_2.degs.pop_back();

    return Monomial(LCM_coef, LCM_degs);
}
Monomial GCD(Monomial& mon_1, Monomial& mon_2) {
    size_t n = mon_1.size(), m = mon_2.size();
    for (size_t i = n; i < std::max(n, m); ++i) { mon_1.degs.push_back(0); }
    for (size_t i = m; i < std::max(n, m); ++i) { mon_2.degs.push_back(0); }
    // Now both mons are of equal sizes
    std::vector<unsigned long int> GCD_degs(std::max(n, m));
    double GCD_coef = std::max(mon_1.coef, mon_2.coef);

    for (size_t i = 0; i < std::max(n, m); ++i) // O(max(n, m))
        GCD_degs[i] = std::min(mon_1.degs[i], mon_2.degs[i]);

    while (mon_1.degs.size() != 0 && mon_1.degs.back() == 0)
        mon_1.degs.pop_back();

    while (mon_2.degs.size() != 0 && mon_2.degs.back() == 0)
        mon_2.degs.pop_back();

    return Monomial(GCD_coef, GCD_degs);
}

class Polinomial {
private:
    std::vector<Monomial> pol;
protected:
    //
public:
    //
};

using namespace std;

template<typename T>
void print(vector<T> v) {
    for (auto elem : v) {
        cout << elem << ' ';
    }
}
void mon_info(const Monomial& mon) {
    cout << "----------INFO----------\n";
    cout << "The monomial's size: " << mon.size() << "\n";
    cout << "The coefficient: " << mon.Coef() << "\n";
    cout << "Degrees: ";
    print(mon.Degs());
    cout << "\n";
    cout << mon << "\n";
}
void compare(const Monomial& mon_1, const Monomial& mon_2) {
    cout << "First:  " << mon_1 << "\n";
    cout << "Second:  " << mon_2 << "\n";
    if (mon_1 == mon_2) {
        cout << "Mons are equal\n";
    }
    else if (mon_1 < mon_2) {
        cout << "The second is greater\n";
    }
    else if (mon_1 > mon_2) {
        cout << "The first is greater\n";
    }
    else { cout << "Houston, we have a problem\n"; }
}