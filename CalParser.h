#ifndef CALPARSER_H
#define CALPARSER_H

#include<stack>
#include<string>
#include<functional>
#include<unordered_map>
#include<cmath>

namespace CalParser {

class CalParser {
    enum Operators {
        Addition,
        Subtraction,
        Multiplication,
        Division,
        Exponentiation,
        BracketLeft,
        BracketRight,
        Error,
    };

    std::unordered_map<Operators,std::function<double(double,double)>> opMapping{
        {Addition, std::plus<double>() },
        {Subtraction,std::minus<double>()},
        {Multiplication,std::multiplies<double>()},
        {Division,std::divides<double>()},
        {Exponentiation, [](double a, double b)->double {return exp(log(a)*b) ;} },
    };

    const std::string & formula;
    std::stack<double> number;
    std::stack<Operators> Op;
    bool Caled;

    void ToFirstNoneBlank(int &pt) { while (std::isspace(formula[pt])) pt++; }
    char CharToNum(char a) {return a-'0';}
    double GetNumber(int& pt);
    Operators getOperators(int &pt);
    void CalTillPrevLeftBracket();
    void CalFirst();

public:
    CalParser(const std::string& formula) : formula(formula), Caled(false){}
    double Calculate();


};

}

#endif
