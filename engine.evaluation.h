#ifndef EVALUATION_H
#define EVALUATION_H

#include <cmath>

string findRelativeMinMax(array<string> terms, const char &var);
/* The method evaluates the expression. */
double evalExpr(array<string> terms, const double &value, const char &var);
/* The method evaluates a term. */
double eval(string term, const double &value, const char &var);

const double PI = 3.14159265358979323846;
const double e = 2.71828;

double evalExpr(array<string> terms, const double &value, const char &var) {
    double result = 0;
    for (unsigned i = 0; i < terms.length; i++) {
        result += eval(terms[i], value, var);
    }
    return result;
}

double eval(string term, const double &value, const char &var) {
    TermComponents tc(term, var);

    if (!tc.factors.length) {
        if (tc.a) return tc.a;
        else return 0;
    }

    double result = tc.a;
    unsigned divPlace = 0;

    for (unsigned short i = 0; i < tc.factors.length; i++) {
        double preResult;

        switch (tc.factors[i].type) {
            case 0: {
                double chainEval = evalExpr(readExpr(tc.factors[i].u), value, var);
                double n = evalExpr(readExpr(tc.factors[i].n), value, var);

                preResult = pow(chainEval, n);
            } break;
            case 1: {
                double chainEval = evalExpr(readExpr(tc.factors[i].u), value, var);

                if (tc.factors[i].func == "sin")
                    preResult = sin(chainEval * PI / 180);
                else if (tc.factors[i].func == "cos")
                    preResult = cos(chainEval * PI / 180);
                else if (tc.factors[i].func == "tan")
                    preResult = tan(chainEval * PI / 180);
                else if (tc.factors[i].func == "csc")
                    preResult = 1/sin(chainEval * PI / 180);
                else if (tc.factors[i].func == "sec")
                    preResult = 1/cos(chainEval * PI / 180);
                else if (tc.factors[i].func == "cot")
                    preResult = 1/tan(chainEval * PI / 180);
            } break;
            case 2: {
                double chainEval = evalExpr(readExpr(tc.factors[i].u), value, var);
                double logbase = tc.factors[i].func.length == 3 ? 10 : parseNum(tc.factors[i].func.slice(3));

                preResult = tc.factors[i].func.length > 2 ? log(chainEval)/log(logbase) : log(chainEval);
            } break;
            case 3: {
                double chainEval = evalExpr(readExpr(tc.factors[i].u), value, var);

                if (tc.factors[i].func == "sin")
                    preResult = asin(chainEval);
                else if (tc.factors[i].func == "cos")
                    preResult = acos(chainEval);
                else if (tc.factors[i].func == "tan")
                    preResult = atan(chainEval);
                else if (tc.factors[i].func == "csc")
                    preResult = 1/asin(chainEval);
                else if (tc.factors[i].func == "sec")
                    preResult = 1/acos(chainEval);
                else if (tc.factors[i].func == "cot")
                    preResult = 1/atan(chainEval);
            } break;
            case 4: {
                double n = evalExpr(readExpr(tc.factors[i].n), value, var);

                preResult = pow(value, n);
            } break;
            case 5: {
                double n = evalExpr(readExpr(tc.factors[i].n), value, var);

                preResult = pow(parseNum(tc.factors[i].u), n);
            } break;
            default: error("fault at 'eval' function");
        }

        // sum the result
        if (tc.divIndex.length && tc.divIndex[divPlace] == i) {
            result /= preResult;
            divPlace++;
        }
        else {
            result *= preResult;
        }
    }

    return result;
}

#endif