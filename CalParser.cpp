#include "CalParser.h"

namespace CalParser {
    using namespace std;

    double CalParser::GetNumber(int &pt) {
        pt--;
        double currentNum = 0;
        double currentBase = 1;

        while (isdigit(formula[++pt]))
            currentNum = 10 * currentNum + CharToNum(formula[pt]);

        if (formula[pt] == '.')
            while (isdigit(formula[++pt]))
                currentBase *= 0.1, currentNum += CharToNum(formula[pt]) * currentBase;

        return currentNum;
    }

    CalParser::Operators CalParser::GetOperator(int &pt) {
        switch (formula[pt++]) {
            case '+': return Addition;
            case '-': return Subtraction;
            case '*': return Multiplication;
            case '/': return Division;
            // case '%': return Modulus;
            case '^': return Exponentiation;
            case '(': return BracketLeft;
            case ')': return BracketRight;
            default: pt--;
                return Error;
        }
    }

    void CalParser::CalTillPrevLeftBracket() {
        while (!(Op.empty()) && Op.top() != BracketLeft) {
            CalFirst();
        }
        if (Op.empty())
            return;
        Op.pop();
    }

    void CalParser::CalFirst() {
        double b = number.top();
        number.pop();
        double a = number.top();
        number.pop();
        Operators op = Op.top();
        Op.pop();
        number.push(opMapping[op](a, b));
    }

    double CalParser::Calculate() {
        if (caled) return number.top();
        int pt = 0;
        int state = 0;
        int numberState = 0;

        Operators currentOp;
        while (formula[pt]) {
            ToFirstNoneBlank(pt);
            if (!formula[pt])
                break;


            currentOp = GetOperator(pt);

            if (currentOp == BracketLeft) Op.push(currentOp);

            else if (currentOp == BracketRight) CalTillPrevLeftBracket();

            else if (state == 0 && currentOp != Error) {

                if (currentOp == Addition && numberState == 0) numberState = 1;

                else if (currentOp == Subtraction && numberState == 0) numberState = -1;

                else throw 1;

            } else if (state == 0) {

                number.push(GetNumber(pt) * (numberState == 0 ? 1 : numberState));
                state = 1;

            } else if (state == 1) {

                while (!Op.empty() && Op.top() >= currentOp && Op.top() != BracketLeft) CalFirst();

                Op.push(currentOp);
                numberState = 0;
                state = 0;

            }
        }

        while (!Op.empty()) {
            CalTillPrevLeftBracket();
        }
        caled = true;
        return number.top();
    }
}
