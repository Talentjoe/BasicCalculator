#include <iostream>
#include<cassert>
#include "CalParser.h"

#define DELTA 0.0000001
using namespace std;

double getAnsOfFormula(string a) {
    CalParser::CalParser c(a);
    double res = c.Calculate();
    cout << a << " = " << res << "\n";
    return res;
}

void AssertDoubleEqual(double a, double b) {
    assert(a > b-DELTA*abs( b) && a < b+DELTA*abs(b));
}

template<class R, class T>
void AssertErrorPram(const function<R(T)> &f, const T &b) {
    try {
        f(b);
        cout << "Warning: " << b << " did not through error\n";
        assert(false);
    } catch (...) {
        cout << "Pass: " << b << " did through error\n";
        assert(true);
    }
}

int main() {
    cout << "test Start" << endl;

    assert(getAnsOfFormula("123") == 123);
    assert(getAnsOfFormula("123.2") == 123.2);
    assert(getAnsOfFormula("   123.2") == 123.2);
    assert(getAnsOfFormula("123.2   ") == 123.2);
    assert(getAnsOfFormula("   123.2   ") == 123.2);
    cout << "=========pure number test passed=========\n\n" ;

    AssertDoubleEqual(getAnsOfFormula("-123"), -123);
    AssertDoubleEqual(getAnsOfFormula("(-123)"), -123);
    AssertDoubleEqual(getAnsOfFormula("+123"), 123);
    AssertDoubleEqual(getAnsOfFormula("(+123)"), 123);
    AssertDoubleEqual(getAnsOfFormula("1++123)"), 124);
    cout << "=========Number with Ne and Po Passed=========\n\n" ;

    AssertDoubleEqual(getAnsOfFormula("123 + 123.4"), 246.4);
    AssertDoubleEqual(getAnsOfFormula("123 - 123.4"), -0.4);
    AssertDoubleEqual(getAnsOfFormula("2.1 * 2.2"), 4.62);
    AssertDoubleEqual(getAnsOfFormula("3 / 2"), 1.5);
    AssertDoubleEqual(getAnsOfFormula("3 ^ 2"), 9);
    cout << "=========Basic Operation Passed=========\n\n" ;

    AssertDoubleEqual(getAnsOfFormula("2 + 4 - 5"), 1);
    AssertDoubleEqual(getAnsOfFormula("3 * 6 / 2"), 9);
    AssertDoubleEqual(getAnsOfFormula("2 ^ 2 ^2"), 16);
    cout << "=========Basic Operation Combination Passed=========\n\n";

    AssertDoubleEqual(getAnsOfFormula("3 + 3 * 3"), 12);
    AssertDoubleEqual(getAnsOfFormula("3 ^ 2 + 3 * 3"), 18);
    cout << "=========Operation Combination Passed=========\n\n" ;

    AssertDoubleEqual(getAnsOfFormula("(3 + 3) * 3"), 18);
    AssertDoubleEqual(getAnsOfFormula("3 ^ (2 + 3) * 3"), 729);
    AssertDoubleEqual(getAnsOfFormula("3 ^ ((2 + 3) * 3)"), 14348907);
    cout << "=========Operation Combination with Bracket Passed=========\n\n" ;

    AssertDoubleEqual(getAnsOfFormula("3 ^ (2 + 3) * 3)"), 729);
    AssertDoubleEqual(getAnsOfFormula("(3 ^ (2 + 3) * 3"), 729);
    cout << "=========Auto Fix Passed=========\n\n" ;

    AssertErrorPram<double, string>(getAnsOfFormula, "1+*2");
    AssertErrorPram<double, string>(getAnsOfFormula, "1+++2");
    AssertErrorPram<double, string>(getAnsOfFormula, "1.2.2");
    AssertErrorPram<double, string>(getAnsOfFormula, "1..2");
    AssertErrorPram<double, string>(getAnsOfFormula, "3a");
    AssertErrorPram<double, string>(getAnsOfFormula, "a");
    AssertErrorPram<double, string>(getAnsOfFormula, "(1)*(*1)");
    cout << "=========Error Expression Passed=========\n\n" ;

    return 0;
}
